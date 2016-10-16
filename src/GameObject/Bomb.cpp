//
// Bomb.cpp for  in /home/trambe_m/tek2/cpp/cpp_indie_studio/src/class/GameObject
// 
// Made by Manuel Trambert
// Login   <trambe_m@epitech.net>
// 
// Started on  Thu May 12 15:00:07 2016 Manuel Trambert
// Last update Sun Jun  5 09:14:07 2016 Manuel Trambert
//

#include "Game.hpp"
#include "Texture.hpp"
#include "Bomb.hpp"

bm::Bomb::Bomb(bm::Character *owner, const irr::core::vector3df &pos, const bm::Game &info)
  :GameObject(0)
{
  _owner = owner;
  _start = std::chrono::system_clock::now();
  _graphic = info.getScene()->addAnimatedMeshSceneNode(info.getTexture().getMesh(BOMBMESH));
  _graphic->setMaterialTexture(0, info.getTexture().getTexture(BOMB));
  _graphic->setMaterialFlag(irr::video::EMF_LIGHTING, true);
  _graphic->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
  _graphic->setMaterialFlag(irr::video::EMF_ANTI_ALIASING, true);
  _graphic->setScale(irr::core::vector3df(0.2, 0.2, 0.2));
  _graphic->setPosition(pos);
  _pos = pos;

}

int bm::Bomb::getRange() const {
  return _owner->getBombRange();
}

bm::Bomb::~Bomb()
{
}

std::chrono::time_point<std::chrono::system_clock>	bm::Bomb::getTimer() const
{
  return (_start);
}

void		bm::Bomb::setPos(const irr::core::vector3df &pos)
{
  _pos = pos;
}

irr::core::vector3df	bm::Bomb::getPos() const
{
  return (_pos);
}

bm::Character		*bm::Bomb::getOwner() const {
  return (_owner);
}

bm::Character		*bm::Bomb::getOwnerUnconst() {
  return (_owner);
}
