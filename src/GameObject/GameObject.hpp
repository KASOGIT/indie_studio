//
// GameObject.hpp for  in /home/trambe_m/tek2/cpp/cpp_indie_studio/src/class
// 
// Made by Manuel Trambert
// Login   <trambe_m@epitech.net>
// 
// Started on  Mon May  9 13:04:12 2016 Manuel Trambert
// Last update Sat Jun  4 16:32:13 2016 benjamin rascol
//

#ifndef __GAMEOBJECT_HPP__
#define __GAMEOBJECT_HPP__

#include <string>
#include <iostream>
#include <irrlicht.h>
#include <map>

namespace bm
{
  class GameObject
  {
  public:
    GameObject(int hp = -1);
    virtual ~GameObject();

  public:
    void				setGraphic(irr::scene::IAnimatedMeshSceneNode *ninja);
    irr::scene::IAnimatedMeshSceneNode	*getGraphic() const;
    irr::core::vector3df		getPos() const;
    int					getId() const;
    irr::scene::IMeshSceneNode		*getBlock() const;
    void				setBlock(irr::scene::IMeshSceneNode *cube);
    void				setId(const int);
    irr::video::ITexture		*getTexture() const;
  
  protected:
    irr::video::ITexture				*_texture;
    float						_size;
    unsigned int					_timer;
    int							_id;
    irr::core::vector3df				_pos;
    float						_moveSpeed;
    irr::scene::IAnimatedMeshSceneNode			*_graphic;
    irr::scene::IMeshSceneNode				*_block;
    unsigned int					_waitFrame;
  };
};

#endif /* !GAMEOBJECT_HPP_ */
