//
// Instance.hpp for  in /home/trambe_m/tek2/cpp/cpp_indie_studio/src/Game
// 
// Made by Manuel Trambert
// Login   <trambe_m@epitech.net>
// 
// Started on  Sun Jun  5 12:31:39 2016 Manuel Trambert
// Last update Sun Jun  5 13:27:25 2016 Manuel Trambert
//

#ifndef __INSTANCE_HPP__
#define __INSTANCE_HPP__

#include "Texture.hpp"

namespace bm {
  class Game;
};

namespace bm
{
  class Instance
  {
  public:
    Instance();
    ~Instance();

  public:
    void	initPerso(int i, const enum TEXTURE_NAME &text, const enum MESH_NAME &mesh, bm::Game *info);
    void        initBord(int x, int z, bm::Game *info);
    void	initGame(bm::Game *info, Texture *);
  private:
  };
};

#endif /* !INSTANCE_HPP */
