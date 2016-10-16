//
// Texture.hpp for  in /home/trambe_m/tek2/cpp/cpp_indie_studio
//
// Made by Manuel Trambert
// Login   <trambe_m@epitech.net>
//
// Started on  Fri Jun  3 15:15:28 2016 Manuel Trambert
// Last update Sun Jun  5 16:39:37 2016 benjamin rascol
//

#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__

#include <irrlicht.h>
#include <utility>
#include "CFGParser.hpp"

namespace bm
{
  enum  TEXTURE_NAME {
    BLOOD,
    PLAYER1,
    PLAYER2,
    PLAYER3,
    PLAYER4,
    HUD_RANGE,
    HUD_BOMB,
    HUD_SPEED,
    BREAKABLE,
    UNBREAKABLE,
    GROUND,
    BONUSRANGE,
    BONUSMAXBOMB,
    BONUSSPEED,
    BOMB,
    ROBOT_TEXT,
    MARVIN_TEXT,
    POTATOR_TEXT,
    SQUELETTE_TEXT,
    VICTORY,
    DEFEAT,
    PAUSE,
  };

  enum  MESH_NAME {
    NINJA,
    BOMBMESH,
    ROBOT,
    MARVIN,
    POTATOR,
    SQUELETTE,
  };

  const std::unordered_map<int, std::string> TAB_CONFIG_TEXTURE = {
    {BLOOD, "Blood"},
    {PLAYER1, "Player1"},
    {PLAYER2, "Player2"},
    {PLAYER3, "Player3"},
    {PLAYER4, "Player4"},
    {HUD_RANGE, "HUD_BonusRange"},
    {HUD_BOMB, "HUD_BonusBomb"},
    {HUD_SPEED, "HUD_BonusSpeed"},
    {BREAKABLE, "Breakable"},
    {UNBREAKABLE, "Unbreakable"},
    {GROUND, "Ground"},
    {BONUSRANGE, "BonusRange"},
    {BONUSMAXBOMB, "BonusNbBomb"},
    {BONUSSPEED, "BonusMoveSpeed"},
    {BOMB, "Bomb"},
    {ROBOT_TEXT, "Robot"},
    {MARVIN_TEXT, "Marvin"},
    {POTATOR_TEXT, "Potator"},
    {SQUELETTE_TEXT, "Squelette"},
    {VICTORY, "Victory"},
    {DEFEAT, "Defeat"},
    {PAUSE, "Pause"},
  };

  const std::unordered_map<int, std::string> TAB_CONFIG_MESH = {
    {NINJA, "Ninja"},
    {BOMBMESH, "Bomb"},
    {ROBOT, "Robot"},
    {MARVIN, "Marvin"},
    {POTATOR, "Potator"},
    {SQUELETTE, "Squelette"},
  };

  class Texture
  {
  public:
    Texture();
    ~Texture();
    std::unordered_map<std::string, std::string>	getTabPathTexture() const;
    std::unordered_map<std::string, std::string>	getTabPathMesh() const;
    irr::video::ITexture				*getTexture(const enum TEXTURE_NAME) const;
    irr::scene::IAnimatedMesh				*getMesh(const enum MESH_NAME) const;
    void						setDriver(irr::video::IVideoDriver *);
    void						setScene(irr::scene::ISceneManager*);
    void						loadTexture();
    void						loadMesh();

  private:
    irr::scene::ISceneManager					*_sceneManager;
    const std::string					_PATH_FILE_TEXTURE = "config/texture.cfg";
    const std::string					_PATH_FILE_MESH = "config/mesh.cfg";
    std::unordered_map<std::string, std::string>	        _TAB_PATH_TEXTURE;
    std::unordered_map<std::string, std::string>	        _TAB_PATH_MESH;
    irr::video::IVideoDriver					*_driver;
    std::unordered_map<int, irr::video::ITexture*>		_TAB_TEXTURE;
    std::unordered_map<int, irr::scene::IAnimatedMesh*>		_TAB_MESH;
  };
};

#endif /* !TEXTURE_HPP_ */
