//
// Bomb.hpp for  in /home/trambe_m/tek2/cpp/cpp_indie_studio/src/class/GameObject
// 
// Made by Manuel Trambert
// Login   <trambe_m@epitech.net>
// 
// Started on  Thu May 12 14:59:02 2016 Manuel Trambert
// Last update Sun Jun  5 09:12:37 2016 Manuel Trambert
//

#ifndef __BOMB_HPP__
#define __BOMB_HPP__

#include <chrono>
#include <irrlicht.h>
#include <iostream>
#include "GameObject.hpp"

namespace bm {
  class Bomb;
  class Character;
};

namespace bm
{
  class Bomb: public GameObject
  {
  public:
    Bomb(bm::Character *, const irr::core::vector3df &, const bm::Game &);
    ~Bomb();

  public:
    std::chrono::time_point<std::chrono::system_clock>	getTimer() const;
    void							setPos(const irr::core::vector3df &);
    irr::core::vector3df					getPos() const;
    bm::Character						*getOwner() const;
    bm::Character						*getOwnerUnconst();
    int							           getRange() const;

  private:
    bm::Character		*_owner;
    irr::core::vector3df	_pos;
    std::chrono::time_point<std::chrono::system_clock> _start;
  };
};

#endif /* !BOMB_HPP_ */
