//
// AI.cpp for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/cpp_indie_studio
// 
// Made by 
// Login   <@epitech.net>
// 
// Started on  Sun Jun  5 06:05:05 2016 
// Last update Sun Jun  5 06:05:38 2016 
//

#include <stdexcept>
#include "Game.hpp"
#include "AI.hpp"

bm::AI::AI() : _L(luaL_newstate()),
	       _move(bm::NONE),
	       _lastPos(NULL),
	       _moveCount(0),
	       Character(true, false)
{
  if (luaL_dofile(_L, "src/AI/Lua/AI.lua")) {
    throw std::runtime_error("Error : can't load AI.lua");
  }
  luaL_openlibs(_L);
  lua_pcall(_L, 0, 0, 0);
}

bm::AI::~AI() {

}

bm::Movements bm::AI::survive(bm::Game &game) {
//    std::clog << "############################################## IA START" << std::endl;

//    std::clog << "cur pos : x=[" << getPos().X << "] & y=[" << getPos().Z << "]" << std::endl;
    _moveCount++;
    if (_lastPos == NULL || _move == bm::SPACE || needNewMovement()) {
        _moveCount = 0;
        updateWorld(game);
//        dumpLuaMap();
        luabridge::LuaRef getMovement = luabridge::getGlobal(_L, "getMovement");
//        std::clog << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~ LUA START" << std::endl;
        _move = (bm::Movements) ((luabridge::LuaRef) getMovement()).cast<int>();
//        std::clog << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~ LUA END" << std::endl;
        delete _lastPos;
        _lastPos = new irr::core::vector3df();
        _lastPos->X = ((int) (getPos().X + 2.5)) - (((int) (getPos().X + 2.5)) % 10);
        _lastPos->Z = ((int) (getPos().Z + 2.5)) - (((int) (getPos().Z + 2.5)) % 10);
    }
    if (_moveCount > 30) {
        lastWhisper(30);
    }
//    std::clog << "############################################## IA END" << std::endl;
    return _move;
}

void bm::AI::lastWhisper(int count) {
    if (_move == bm::UP || _move == bm::DOWN) {
        if (_moveCount < count + 5)
            _move = bm::RIGHT;
        else if (_moveCount < count + 10)
            _move = bm::LEFT;
        else
            _lastPos == NULL;
    }
    else {
        if (_moveCount < count + 5)
            _move = bm::UP;
        else if (_moveCount < count + 10)
            _move = bm::DOWN;
        else
            _lastPos == NULL;
    }
}

bool bm::AI::needNewMovement() {

    switch (_move)
    {
        case bm::UP :
            return (getPos().Z >= _lastPos->Z + 7 || getPos().Z + 3 >= 130);
        case bm::DOWN :
            return (getPos().Z <= _lastPos->Z - 7 || getPos().Z - 3 <= 0);
        case bm::RIGHT :
            return (getPos().X >= _lastPos->X + 7 || getPos().X + 3 >= 190);
        case bm::LEFT :
            return (getPos().X <= _lastPos->X - 7 || getPos().X - 3 <= 0);
        default :
            return true;
    }
//    std::clog << "cur move : " << _move << std::endl;
    if (_move == bm::UP) {
//        std::clog << "MOVE UP | target pos : x=[" << _lastPos->X << "] & y=[" << _lastPos->Z + 7 << "]" << std::endl;
        return (getPos().Z >= _lastPos->Z + 7 || getPos().Z + 3 >= 130);
    }
    else if (_move == bm::DOWN) {
//        std::clog << "MOVE DOWN | target pos : x=[" << _lastPos->X << "] & y=[" << _lastPos->Z - 7 << "]" << std::endl;
        return (getPos().Z <= _lastPos->Z - 7 || getPos().Z - 3 <= 0);
    }
    else if (_move == bm::RIGHT) {
//        std::clog << "MOVE RIGHT | target pos : x=[" << _lastPos->X + 10 << "] & y=[" << _lastPos->Z << "]" << std::endl;
        return (getPos().X >= _lastPos->X + 7 || getPos().X + 3 >= 190);
    }
    else if (_move == bm::LEFT) {
//        std::clog << "MOVE LEFT | target pos : x=[" << _lastPos->X - 10 << "] & y=[" << _lastPos->Z << "]" << std::endl;
        return (getPos().X <= _lastPos->X - 7 || getPos().X - 3 <= 0);
    }
    else if (_move == bm::NONE) {
//        std::clog << "MOVE NONE | target pos = STANDBY, Always true" << std::endl;
        return true;
    }
//    std::cerr << "AI error : undefined movement sent to needNewMovement()." << std::endl;
    return true;
}

void bm::AI::updateWorld(bm::Game &game) {
    std::vector < std::vector < GameObject * > * > *map = game.getMap();

    if (map->size() == 0 || (*map)[0]->size() == 0) {
        std::cerr << "AI error : Updating an empty map." << std::endl;
        return;
    }

    luabridge::LuaRef gameData = luabridge::getGlobal(_L, "gameData");
    gameData["max_x"] = map->size();
    gameData["max_y"] = (*map)[0]->size();
    irr::core::vector3df pos = getPos();
    gameData["my_x"] = (int) (pos.X / 10 + 0.25);
    gameData["my_y"] = (int) (pos.Z / 10 + 0.25);
    gameData["nbOwnedBomb"] = getBomb().size();
    gameData["nbMaxBomb"] = getMaxBomb();

    lua_newtable(_L);
    int newTable = lua_gettop(_L);
    int index = 0;
    for (size_t y = 0; y < (*map)[0]->size(); y++) {
        for (size_t x = 0; x < map->size(); x++) {
            lua_pushnumber(_L, toInt(game, (*(*map)[x])[y], x, y));
            lua_rawseti(_L, newTable, index);
            ++index;
        }
    }
    lua_setglobal(_L, "map");
}

int bm::AI::toInt(bm::Game &game, GameObject *gameObject, int x, int y) {
    std::vector < Character * > characters = game.getCharacters();
    for (auto it = characters.begin(); it != characters.end(); it++) {
        irr::core::vector3df characterPos = (*it)->getPos();
        if ((*it)->getAlive() && this != *it && (int) (characterPos.X / 10 + 0.5) == x &&
            (int) (characterPos.Z / 10 + 0.5) == y) {
            return ENEMY;
        }
        std::vector < Bomb * > characterBombs = (*it)->getBomb();
        for (auto bIt = characterBombs.begin(); bIt != characterBombs.end(); bIt++) {
            irr::core::vector3df bombPos = (*bIt)->getPos();
            if ((int) (bombPos.X / 10 + 0.5) == x && (int) (bombPos.Z / 10 + 0.5) == y) {
                return BOMB + (*bIt)->getRange() - 1;
            }
        }
    }
    if (gameObject == NULL)
        return AIR;
    int hp = gameObject->getId();
    if (hp == -1)
        return UNBREAKABLE_WALL;
    if (hp >= 0)
        return BREAKABLE_WALL;
    return AIR;
}

void bm::AI::dumpLuaMap() {
    luabridge::LuaRef dumpWorld = luabridge::getGlobal(_L, "dumpWorld");
    dumpWorld();
}
