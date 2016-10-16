//
// Bonus.hpp for  in /home/trambe_m/tek2/cpp/cpp_indie_studio/src/Class/GameObject
// 
// Made by Manuel Trambert
// Login   <trambe_m@epitech.net>
// 
// Started on  Sun May 29 02:29:51 2016 Manuel Trambert
// Last update Sun Jun  5 10:02:20 2016 Manuel Trambert
//

#ifndef __BONUS_HPP__
#define __BONUS_HPP__

#include <irrlicht.h>
#include <chrono>
#include "GameObject.hpp"

namespace bm {
  class Game;
};

enum bonusType
  {
    RANGE = 0,
    SPEED,
    NBBOMB
  };

namespace bm
{
  class Bonus: public GameObject
  {
  public:
    Bonus(float size, const bm::Game &info, const irr::core::vector3df &pos, int type);
    ~Bonus();
  
  public:
    bonusType	getType() const;
    void        createBonus(const irr::core::vector3df &pos, const bm::Game &info);
    std::chrono::time_point<std::chrono::system_clock>	getTimer() const;
  
  protected:
    unsigned int	_timer;
    bonusType	_bonusType;
    std::chrono::time_point<std::chrono::system_clock> _start;
  };
};

#endif /* !BONUS_HPP_ */
