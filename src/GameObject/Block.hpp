//
// Block.hpp for  in /home/trambe_m/tek2/cpp/cpp_indie_studio/src/class/GameObject
// 
// Made by Manuel Trambert
// Login   <trambe_m@epitech.net>
// 
// Started on  Wed May 18 16:55:07 2016 Manuel Trambert
// Last update Sun Jun  5 10:41:00 2016 Manuel Trambert
//

#ifndef __BLOCK_HPP__
#define __BLOCK_HPP__

namespace bm {
  class Game;
};

#include "Texture.hpp"
#include "GameObject.hpp"
#include <irrlicht.h>

namespace bm
{
  class Block : public GameObject
  {
  public:
    Block(float size, int id, const irr::core::vector3df &pos, bool anti,
	  irr::scene::ISceneManager *sceneManager, irr::video::ITexture *);
    ~Block();
  
  public:
    void        createBlock(irr::scene::ISceneManager *manager,
			    const irr::core::vector3df &pos);
  private:
    bool		_antialiasing;
  };
};

#endif /* !BLOCK_HPP_ */
