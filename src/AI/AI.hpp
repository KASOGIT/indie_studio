//
// AI.hpp for  in /home/trambe_m/tek2/cpp/cpp_indie_studio
// 
// Made by Manuel Trambert
// Login   <trambe_m@epitech.net>
// 
// Started on  Wed Jun  1 13:55:28 2016 Manuel Trambert
// Last update Wed Jun  1 14:12:30 2016 Manuel Trambert
//

#ifndef AI_HPP_
#define AI_HPP_

extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}

#include <LuaBridge.h>
#include <iostream>
#include <vector>
#include "Character.hpp"

class Game;

namespace bm {
    class AI : public Character {
    private:
        enum ObjectType {
            UNBREAKABLE_WALL = 0,
            BREAKABLE_WALL = 1,
            AIR = 2,
            ENEMY = 3,
            BOMB = 4
        };

        lua_State *_L;
        bm::Movements _move;
        irr::core::vector3df *_lastPos;
        int _moveCount;
    public:
        AI();

        ~AI();

        bm::Movements survive(Game &game);

    private:
        void updateWorld(Game &game);

        bool needNewMovement();

        //std::vector <std::vector<GameObject *>> &map);
        void dumpLuaMap();

        void lastWhisper(int count);

        int toInt(Game &game, GameObject *gameObject, int x, int y);
    };
};

#endif
