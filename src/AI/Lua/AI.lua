-- Data

gameData = {
    max_y = 0, -- nb line
    max_x = 0, -- line size
    my_x = 0,
    my_y = 0,
    nbOwnedBomb = 0,
    nbMaxBomb = 0,
}

result = {
    target_y = 0,
    target_x = 0,
    action = 0,
}

-- Enum

EntityType = {
    UNBREAKABLE_WALL = 0,
    BREAKABLE_WALL = 1,
    AIR = 2,
    ENEMY = 3,
    BOMB = 4,
}

MovementType = {
    STANDBY = -1,
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3,
    SPACE = 4,
}

Mode = {
    AGGRESSIVE = 1,
    SURVIVE = 2,
}

-- UTILS : MAP

indexToPosition = function(index)
    return { y = math.floor(index / gameData.max_x), x = index % gameData.max_x }
end

positionToIndex = function(y, x)
    return (y * gameData["max_x"]) + x
end

-- UTILS : DATA

getMapDataIndex = function(index)
    if index > #map then
        local pos = indexToPosition(index)
        print("Warning ! To far in pos : x=[", pos["x"], "], y=[", pos["y"], "]")
        return 0
    end
    return map[index]
end

getMapDataPos = function(y, x)
    local data = getMapDataIndex(positionToIndex(y, x))
    return data
end

-- Utils : MAP CHECKER

containPos = function(positions, y, x)
    for k, v in pairs(positions) do
        if v["y"] == y and v["x"] == x then
            return true
        end
    end
    return false
end

-- AVAILABLE POSITION

getAvailablePositionsRec = function(positions, y, x)
    local PosData = getMapDataPos(y, x)
    if (#positions == 0 or (PosData == EntityType["AIR"] or PosData == EntityType["ENEMY"])
            and containPos(positions, y, x) == false) then
        table.insert(positions, { y = y, x = x })
        getAvailablePositionsRec(positions, y + 1, x)
        getAvailablePositionsRec(positions, y - 1, x)
        getAvailablePositionsRec(positions, y, x + 1)
        getAvailablePositionsRec(positions, y, x - 1)
    end
end

getAvailablePositions = function(y, x)
    -- get safe positions
    local positions = {}
    getAvailablePositionsRec(positions, y, x)
    return positions
end

-- BOMB

getBombsPositions = function()
    local bombsPositions = {}
    for i = 0, #map do
        if map[i] >= EntityType["BOMB"] then
            table.insert(bombsPositions, indexToPosition(i))
        end
    end
    return bombsPositions
end

getBombRadius = function(posData)
    return posData - EntityType.BOMB + 1
end

-- DAMAGED POSITION

fillDamagedPositions = function(bombPosition, damagedPositions)
    local bombRadius = getBombRadius(getMapDataPos(bombPosition.y, bombPosition.x))
    for x = 1, bombRadius do
        local posData = getMapDataPos(bombPosition["y"], bombPosition["x"] + x)
        if posData == EntityType.UNBREAKABLE_WALL then
            break
        end
        table.insert(damagedPositions, { y = bombPosition["y"], x = bombPosition["x"] + x })
    end
    for x = -1, -bombRadius, -1 do
        local posData = getMapDataPos(bombPosition["y"], bombPosition["x"] + x)
        if posData == EntityType.UNBREAKABLE_WALL then
            break
        end
        table.insert(damagedPositions, { y = bombPosition["y"], x = bombPosition["x"] + x })
    end
    for y = 1, bombRadius do
        local posData = getMapDataPos(bombPosition["y"] + y, bombPosition["x"])
        if posData == EntityType.UNBREAKABLE_WALL then
            break
        end
        table.insert(damagedPositions, { y = bombPosition["y"] + y, x = bombPosition["x"] })
    end
    for y = -1, -bombRadius, -1 do
        local posData = getMapDataPos(bombPosition["y"] + y, bombPosition["x"])
        if posData == EntityType.UNBREAKABLE_WALL then
            break
        end
        table.insert(damagedPositions, { y = bombPosition["y"] + y, x = bombPosition["x"] })
    end
    return damagedPositions
end

getUnsafePositions = function()
    -- get all damaged positions
    local unsafePosition = {}
    local bombsPositions = getBombsPositions()
    for i = 1, #bombsPositions do
        --        print("bomb n°", i, " : x=", bombsPositions[i].x, " & y=", bombsPositions[i].y)
        table.insert(unsafePosition, bombsPositions[i])
        fillDamagedPositions(bombsPositions[i], unsafePosition)
    end
    return unsafePosition
end


isSafe = function(unsafePositions, y, x)
    for i = 1, #unsafePositions do
        if unsafePositions[i].x == x and unsafePositions[i].y == y then
            return false
        end
    end
    return true
end

-- Utils : Distance

getSquaredDistance = function(pos1, pos2)
    local distance = (math.pow(pos1.y - pos2.y, 2) + math.pow(pos1.x - pos2.x, 2))
    return distance
end

-- Utils : position

isJoinable = function(y, x)
    local posData = getMapDataPos(y, x)
    --    print("isJoignable check pos : x = ", x, "and y = ", y, " with data =", getMapDataPos(y, x))
    return (posData == EntityType.AIR or posData == EntityType.ENEMY)
end

-- Enemy

getEnemiesPositions = function()
    local enemiesPositions = {}
    for i = 0, #map do
        if map[i] == EntityType.ENEMY then
            table.insert(enemiesPositions, indexToPosition(i))
        end
    end
    return enemiesPositions
end

getClosestEnemyPosition = function()
    local enemyPosition
    local myPos = { y = gameData.my_y, x = gameData.my_x }
    for i = 0, #map do
        if map[i] == EntityType.ENEMY and (enemyPosition == nil or
                getSquaredDistance(myPos, indexToPosition(i)) < getSquaredDistance(myPos, enemyPosition)) then
            enemyPosition = indexToPosition(i)
        end
    end
    return enemyPosition
end

-- Safe
-- TODO améliorer en comptant le nombre de case pour y arriver
getClosestSafePosition = function()
    local myPos = { y = gameData.my_y, x = gameData.my_x }
    local availablePositions = getAvailablePositions(gameData.my_y, gameData.my_x)
    local closestPosition

    for i = 0, #availablePositions do
        if closestPosition == nil or
                getSquaredDistance(myPos, indexToPosition(i)) < getSquaredDistance(myPos, closestPosition) then
            closestPosition = availablePositions[i]
        end
    end
    return closestPosition
end

-- POSITION FINDER

getSafetyPathRec = function(path, y, x, unsafePositions)
    local PosData = getMapDataPos(y, x)
    --    print("~~~~ Get safety path Rec for x = ", x, ", and y = ", y, ", data = ", getMapDataPos(y, x))
    if (PosData == EntityType.AIR or PosData == EntityType.ENEMY)
            and containPos(path, y, x) == false then
        table.insert(path, { y = y, x = x })
        if isSafe(unsafePositions, y, x) == true then
            --            print("is safe")
            return true
        end
        return (getSafetyPathRec(path, y + 1, x, unsafePositions)
                or getSafetyPathRec(path, y - 1, x, unsafePositions)
                or getSafetyPathRec(path, y, x + 1, unsafePositions)
                or getSafetyPathRec(path, y, x - 1, unsafePositions))
    end
    return false
end

getSafetyPath = function(y, x, unsafePositions)
    local path = {}
    if (getSafetyPathRec(path, y, x, unsafePositions) == true) then
        return path
    end
    return nil
end

getSafePosition = function(unsafePositions)
    -- get safe positions
    local joinablePositions = {
        { y = math.floor(gameData.my_y), x = math.floor(gameData.my_x + 1), move = MovementType.RIGHT },
        { y = math.floor(gameData.my_y), x = math.floor(gameData.my_x - 1), move = MovementType.LEFT },
        { y = math.floor(gameData.my_y + 1), x = math.floor(gameData.my_x), move = MovementType.UP },
        { y = math.floor(gameData.my_y - 1), x = math.floor(gameData.my_x), move = MovementType.DOWN }
    }
    local joinablePosByPath
    for i = 1, #joinablePositions do
        local safetyPath = getSafetyPath(joinablePositions[i].y, joinablePositions[i].x, unsafePositions)
        if safetyPath ~= nil and (joinablePosByPath == nil
                or #safetyPath < #(joinablePosByPath.safetyPath))
        then
            --            print("find a path with length of : ", #safetyPath)
            joinablePosByPath = { joinablePosition = joinablePositions[i], safetyPath = safetyPath }
        end
    end
    if joinablePosByPath == nil then
        return nil
    end
    return joinablePosByPath.joinablePosition
end

getClosestAvailablePosition = function(targetPosition, mode, joinablePositions, unsafePositions)
    local closestPosition
    for i = 1, #joinablePositions do
        if mode == Mode.SURVIVE then
            if closestPosition == nil or (isSafe(unsafePositions, joinablePositions[i].y, joinablePositions[i].x) and isSafe(unsafePositions, closestPosition.y, closestPosition.x) == false)
                    or getSquaredDistance(targetPosition, joinablePositions[i]) < getSquaredDistance(targetPosition, closestPosition)
            then
                closestPosition = joinablePositions[i]
            end
        else
            -- AGGRESSIVE
            if isSafe(unsafePositions, joinablePositions[i].y, joinablePositions[i].x)
                    and (closestPosition == nil
                    or getSquaredDistance(targetPosition, joinablePositions[i]) < getSquaredDistance(targetPosition, closestPosition))
            then
                closestPosition = joinablePositions[i]
            end
        end
    end
    return closestPosition
end

getTargetPosition = function(mode, unsafePositions)
    local pos
    if mode == Mode.AGGRESSIVE then
        pos = getClosestEnemyPosition()
    else
        --        pos = getClosestSafePosition()
        pos = getSafePosition(unsafePositions)
    end
    return pos
end

getMovementType = function(unsafePositions, mode)
    local joinablePositions = {
        { y = math.floor(gameData.my_y), x = math.floor(gameData.my_x + 1), move = MovementType.RIGHT },
        { y = math.floor(gameData.my_y), x = math.floor(gameData.my_x - 1), move = MovementType.LEFT },
        { y = math.floor(gameData.my_y + 1), x = math.floor(gameData.my_x), move = MovementType.UP },
        { y = math.floor(gameData.my_y - 1), x = math.floor(gameData.my_x), move = MovementType.DOWN }
    }
    local i = 1
    while i <= #joinablePositions do
        if isJoinable(joinablePositions[i].y, joinablePositions[i].x) == false then
            table.remove(joinablePositions, i)
        else
            i = i + 1
        end
    end

    local targetPos = getTargetPosition(mode, unsafePositions)

    -- When no target is found
    if targetPos == nil then
        return MovementType.STANDBY
    end
    local closestPosition = getClosestAvailablePosition(targetPos, mode, joinablePositions, unsafePositions)

    -- Movement return
    -- if no position is found
    if closestPosition == nil then
        return MovementType.STANDBY
    end

    -- Check for bomb put
    local myPos = { y = gameData.my_y, x = gameData.my_x }
    if mode == Mode.AGGRESSIVE and (getSquaredDistance(myPos, targetPos) <= 1 or getSquaredDistance(myPos, targetPos)
            < getSquaredDistance(closestPosition, targetPos))
    then
        return MovementType.SPACE
    end
    return closestPosition.move
end

-- MAIN FUNCTION

getMovement = function()
    local movement
    local unsafePositions = getUnsafePositions()
    if isSafe(unsafePositions, gameData.my_y, gameData.my_x) then
        movement = getMovementType(unsafePositions, Mode.AGGRESSIVE)
    else
        movement = getMovementType(unsafePositions, Mode.SURVIVE)
    end
    if movement == nil or (movement == MovementType.SPACE and gameData.nbOwnedBomb >= gameData.nbMaxBomb) then--or (movement == MovementType.SPACE and gameData.nbOwnedBomb > 0) then
        movement = MovementType.STANDBY
    end
    return movement
end

-- EXTERN FUNCTION

dumpWorld = function()
    if gameData["max_y"] ~= 0 and gameData["max_x"] ~= 0 then
        print("Dump map starting ...")
        -- Fill tab
        local tab = {}
        for i = 0, gameData["max_y"] * gameData["max_x"] - 1, gameData["max_x"] do
            local line = {}
            for j = i, i + gameData["max_x"] - 1 do
                local pos = indexToPosition(j)
                table.insert(line, "[" .. "{" .. pos.x .. "," .. pos.y .. "}:" .. map[j] .. "] ")
            end
            table.insert(tab, line)
        end
        -- display
        for i = #tab, 1, -1 do
            for j = 1, #tab[i] do
                io.write(tab[i][j])
            end
            print()
        end
        print("Dump map Ended ...")
    end
end