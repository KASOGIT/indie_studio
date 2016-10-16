//
// GameObject.cpp for  in /home/trambe_m/tek2/cpp/cpp_indie_studio/src/class
// 
// Made by Manuel Trambert
// Login   <trambe_m@epitech.net>
// 
// Started on  Mon May  9 13:07:07 2016 Manuel Trambert
// Last update Sat Jun  4 16:32:20 2016 benjamin rascol
//

#include "GameObject.hpp"

bm::GameObject::GameObject(int id)
{
  _id = id;
}

bm::GameObject::~GameObject()
{
}

void				bm::GameObject::setBlock(irr::scene::IMeshSceneNode *cube)
{
  _block = cube;
}

irr::scene::IMeshSceneNode	*bm::GameObject::getBlock() const
{
  return (_block);
}

irr::scene::IAnimatedMeshSceneNode	*bm::GameObject::getGraphic() const
{
  return (_graphic);
}

void		        bm::GameObject::setGraphic(irr::scene::IAnimatedMeshSceneNode *charac)
{
  _graphic = charac;
}

int			bm::GameObject::getId() const
{
  return (_id);
}

void			bm::GameObject::setId(const int id)
{
  _id = id;
}

irr::core::vector3df	bm::GameObject::getPos() const
{
  return (_pos);
}

irr::video::ITexture	*bm::GameObject::getTexture() const
{
  return (_texture);
}
