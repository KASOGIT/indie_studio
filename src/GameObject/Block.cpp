//
// Block.cpp for  in /home/trambe_m/tek2/cpp/cpp_indie_studio/src/class/GameObject
// 
// Made by Manuel Trambert
// Login   <trambe_m@epitech.net>
// 
// Started on  Wed May 18 18:17:32 2016 Manuel Trambert
// Last update Sun Jun  5 10:45:04 2016 Manuel Trambert
//

#include "Game.hpp"
#include "Block.hpp"

bm::Block::Block(float size, int id, const irr::core::vector3df &pos, bool anti,
		 irr::scene::ISceneManager *sceneManager, irr::video::ITexture *texture)
  :GameObject(id)
{
  _timer = 0;
  _texture = texture;
  _size = size;
  _antialiasing = anti;
  createBlock(sceneManager, pos);
}

bm::Block::~Block()
{

}

void	bm::Block::createBlock(irr::scene::ISceneManager *manager,
			       const irr::core::vector3df &pos)
{
  _block = manager->addCubeSceneNode(_size, 0, -1, pos);
  _block->setMaterialTexture(0, _texture);
  _block->setMaterialFlag(irr::video::EMF_LIGHTING, true);
  _block->setMaterialFlag(irr::video::EMF_ANTI_ALIASING, _antialiasing);
}
