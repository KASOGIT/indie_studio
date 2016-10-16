//
// game.hpp for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/cpp_indie_studio/src/graphics/game
//
// Made by
// Login   <@epitech.net>
//
// Started on  Wed May  4 16:34:15 2016
// Last update Sun Jun  5 17:52:34 2016 Manuel Trambert
//

#ifndef GAME_HPP_
#define GAME_HPP_

namespace bm
{
  class Game;
  class Particle;
};

#ifdef	_WIN32
	#include <io.h>
#else
	#include <unistd.h>
#endif	//_WIN32

#include <sstream>
#include <iostream>
#include <irrlicht.h>
#include <chrono>
#include <thread>
#include <vector>
#include "AI.hpp"
#include "Particle.hpp"
#include "Character.hpp"
#include "Block.hpp"
#include "Events.hpp"
#include "Sound.hpp"
#include "../Launcher/Loader/GameConfig.hpp"
#include "Particle.hpp"

#define MAP_X	21
#define MAP_Y	15
#define	TIME_INTRO	36000
#define	LIFETIME_PARTICLE	500

namespace bm
{
  class Texture;

  class Game
  {
  public:
    Game(bm::GameConfig &config, Texture &,  int width = 1920, int height = 1080,
	 bool fullWindow = false, bool vasync = false);
    ~Game();
    std::vector<bm::Character*>			*getPtrCharacters();
    int						getNbHumanPlayers() const;
    bm::GameConfig				&getConfig() const;
    void					run();
    irr::gui::IGUIEnvironment			*getGUI() const;
    void					setGUI(irr::gui::IGUIEnvironment*);
    irr::IrrlichtDevice				*getDevice() const;
    irr::video::IVideoDriver			*getDriver() const;
    irr::scene::ISceneManager			*getScene() const;
    std::vector<std::vector<GameObject * > * >	*getMap() const;
    std::vector<bm::Character*>			getCharacters() const;
    Texture					getTexture() const;
    std::vector<bm::Particle*>			*getParticle() const;
    void					setPause();
    void					setPauseIsSet();
    bool					getPause() const;
    void				        initPerso(int i, const enum TEXTURE_NAME &text, const enum MESH_NAME &mesh);
    void				        setGUI();
    void					setLight();
    bool					parseSave();
    void				        setHumanPlayers(int humanPlayers);
	int						getMaxBomb() const;
	int						getMaxRange() const;
	int						getMaxMoveSpeed() const;


  private:
    void	endGame();
    void        drawScore(irr::gui::IGUIStaticText **scores, wchar_t msg[1024]);
    void        managePlayer(const bool *keyCodes, const float);
    void        manageAI(const float);
    void        manageParticle();
    bool	isFinished();
    void	initWin();
    void	introduction(bool isIntro);
    void	saveGame() const;
    void	delSave() const;
    void	setGraphChar(int idx);
    
  private:
    std::chrono::time_point<std::chrono::system_clock>	_start;
    bool					_startAI;
	int						_MAX_BOMB;
	int						_MAX_RANGE;
	int						_MAX_MOVESPEED;
	irr::IrrlichtDevice				*_device;
    irr::video::IVideoDriver			*_driver;
    irr::scene::ISceneManager			*_sceneManager;
    irr::gui::IGUIEnvironment			*_gui;
    std::vector<std::vector<GameObject * > * >	*_objects;
    Block					*_ground;
    Block					*_ground2;
    std::vector<bm::Character*>			_character;
    irr::scene::ICameraSceneNode		*_camera;
    Sound					_sound;
    Events					_receiver;
    int						_width;
    int						_height;
    bool					_fullWin;
    bool					_vAsync;
    bm::GameConfig				&_config;
    bm::Texture					&_texture;
    std::vector<bm::Particle*>			*_particle;
    bool					_pause;
    irr::gui::IGUIFont				*_font;
    irr::gui::IGUIImage				*_pause_gui;
    int						_wait;
    int						_humanPlayers;
  };
};

#endif /* !GAME_HPP_ */
