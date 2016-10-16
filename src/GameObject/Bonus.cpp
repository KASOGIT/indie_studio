//
// Bonus.cpp for  in /home/trambe_m/tek2/cpp/cpp_indie_studio/src/Class/GameObject
// 
// Made by Manuel Trambert
// Login   <trambe_m@epitech.net>
// 
// Started on  Sun May 29 02:32:22 2016 Manuel Trambert
// Last update Sun Jun  5 10:04:09 2016 Manuel Trambert
//

#include <time.h>
#include <stdlib.h>
#include "Texture.hpp"
#include "Game.hpp"
#include "Bonus.hpp"

bm::Bonus::Bonus(float size, const bm::Game &info, const irr::core::vector3df &pos, int type)
  :GameObject(-500)
{
  _start = std::chrono::system_clock::now();
  _timer = -1;
  _size = size;
  if (type == 0)
    _bonusType = RANGE;
  else if (type == 1)
    _bonusType = SPEED;
  else
    _bonusType = NBBOMB;
  createBonus(pos, info);
}

bm::Bonus::~Bonus()
{

}

void	bm::Bonus::createBonus(const irr::core::vector3df &pos, const bm::Game &info)
{
  _block = info.getScene()->addCubeSceneNode(10, 0, -1, pos);
  if (_bonusType == RANGE)
    _block->setMaterialTexture(0, info.getTexture().getTexture(BONUSRANGE));
  else if (_bonusType == NBBOMB)
    _block->setMaterialTexture(0, info.getTexture().getTexture(BONUSMAXBOMB));
  else if (_bonusType == SPEED)
    _block->setMaterialTexture(0, info.getTexture().getTexture(BONUSSPEED));
  _block->setRotation(irr::core::vector3df(0., 270., 0.));
  _block->setMaterialFlag(irr::video::EMF_LIGHTING, true);
}

bonusType	bm::Bonus::getType() const
{
  return (_bonusType);
}

std::chrono::time_point<std::chrono::system_clock>	bm::Bonus::getTimer() const
{
  return (_start);
}
