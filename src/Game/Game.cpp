//
// game.cpp for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/cpp_indie_studio/src/graphics/game
//
// Made by
// Login   <@epitech.net>
//
// Started on  Wed May  4 16:35:21 2016
// Last update Sun Jun  5 18:27:14 2016 Manuel Trambert
//

#include <iostream>
#include "Instance.hpp"
#include "Texture.hpp"
#include "Game.hpp"

bm::Game::Game(bm::GameConfig &config, bm::Texture &bbmanTexture,
	       int width, int height, bool fullWindow, bool vAsync): _config(config),
								     _width(width),
								     _height(height),
								     _fullWin(fullWindow),
								     _vAsync(vAsync),
								     _texture(bbmanTexture)
{
	_MAX_MOVESPEED = 100;
	if (_config.gameMode == GameConfig::GameMode::GM_URF) {
		_MAX_BOMB = 6;
		_MAX_RANGE = 6;
	}
	else {
		_MAX_BOMB = 3;
		_MAX_RANGE = 3;
	}
  _start = std::chrono::system_clock::now();
  _pause = false;
  _pause_gui = NULL;
  _startAI = false;
  _particle = new std::vector<bm::Particle*>;
  _humanPlayers = _config.humanPlayers;
  for (int i = 0; i < _humanPlayers; i += 1) {
    bm::Character *tmp = new Character(_config.antialiasing, true);

    _character.push_back(tmp);
  }
  for (int i = 0; i < (4 - _config.humanPlayers); i += 1) {
    AI *tmpAI = new AI;

    _character.push_back(tmpAI);
  }
  _objects = new std::vector < std::vector < bm::GameObject * > * >;
  _device = irr::createDevice(irr::video::EDT_OPENGL,
			      irr::core::dimension2d<irr::u32>(_width, _height),
			      32, _fullWin, true, 0, &_receiver);
  _driver = _device->getVideoDriver();
  _texture.setDriver(_driver);
  _texture.loadTexture();
  _sceneManager = _device->getSceneManager();
  _wait = 39000;
  if (config.skipIntro == true)
    _wait = 2000;
  introduction(!config.skipIntro);
  Instance	init;

  init.initGame(this, &_texture);
}

bm::Game::~Game() {
  if (this->isFinished() == false)
    saveGame();
  else
    delSave();
  if (_particle && _particle->empty() == false) {
    _particle->clear();
  }
  if (_particle)
    delete _particle;
  if (_character.empty() == false)
    _character.clear();
  if (_objects->empty() == false)
    _objects->clear();
  _device->drop();
}

void	bm::Game::saveGame() const
{
  std::ofstream	_fileSave;

  _fileSave.open(std::string("data/profile/") + _config.currentProfile + "/game.save");
  if (_fileSave.is_open())
    {
      for (int x = 0; x <= MAP_X; ++x)
	{
	  for (int y = 0; y < MAP_Y; ++y)
	    {
	      _fileSave << "o:";
	      if ((*(*_objects)[x])[y] == NULL)
		_fileSave << "0" << std::endl;
	      else
		_fileSave << ((*(*_objects)[x])[y])->getId() << std::endl;
	    }
	}
      for (auto &it : _character)
	{
	  _fileSave << "c:";
	  _fileSave << (int)it->getPos().X << "," << (int)it->getPos().Z << ",";
	  _fileSave << (it->isPlayer() ? 1 : 0) << ",";
	  _fileSave << (int)it->getMoveSpeed() << ","
		    << (int)it->getBombRange() << ","
		    << (int)it->getMaxBomb() << ","
		    << (int)it->getScore() << ","
		    << (it->getAlive() ? 1 : 0) << std::endl;
	}
    }
  else
    std::cerr << "Error while opening save file" << std::endl;
}

void	bm::Game::delSave() const
{
  remove((std::string("data/profile/") + _config.currentProfile + "/game.save").c_str());
}

void	bm::Game::setGraphChar(int idx)
{
  if (idx - 1 == 0)
    {
      _character[idx - 1]->setGraphic(_sceneManager->addAnimatedMeshSceneNode(_texture.getMesh(ROBOT)));
      _character[idx - 1]->getGraphic()->setMaterialTexture(0, _texture.getTexture(ROBOT_TEXT));
      _character[idx - 1]->getGraphic()->setScale(irr::core::vector3df(0.3, 0.3, 0.3));
    }
  else if (idx - 1 == 1)
    {
      _character[idx - 1]->setGraphic(_sceneManager->addAnimatedMeshSceneNode(_texture.getMesh(MARVIN)));
      _character[idx - 1]->getGraphic()->setMaterialTexture(0, _texture.getTexture(MARVIN_TEXT));
      _character[idx - 1]->getGraphic()->setScale(irr::core::vector3df(0.4, 0.4, 0.4));
    }
  else if (idx - 1 == 2)
    {
      _character[idx - 1]->setGraphic(_sceneManager->addAnimatedMeshSceneNode(_texture.getMesh(POTATOR)));
      _character[idx - 1]->getGraphic()->setMaterialTexture(0, _texture.getTexture(POTATOR_TEXT));
      _character[idx - 1]->getGraphic()->setScale(irr::core::vector3df(0.3, 0.3, 0.3));
    }
  else if (idx - 1 == 3)
    {
      _character[idx - 1]->setGraphic(_sceneManager->addAnimatedMeshSceneNode(_texture.getMesh(SQUELETTE)));
      _character[idx - 1]->getGraphic()->setMaterialTexture(0, _texture.getTexture(SQUELETTE_TEXT));
      _character[idx - 1]->getGraphic()->setScale(irr::core::vector3df(0.5, 0.5, 0.5));
    }
}

bool	bm::Game::parseSave()
{
  std::string	_rdLine;
  std::string	_word;
  std::ifstream	_fileSave;
  bool	_char(false);
  bool	_obj(false);
  int	i(0);
  int	x(0), y(0);
  int	typeChar(0);
  int	ms(0), br(0), mb(0);
  bool	alive(true);
  int	score(0);
  int	nb(1);

  _fileSave.open(std::string("data/profile/") + _config.currentProfile + "/game.save");
  if (_fileSave.is_open())
    {
      _humanPlayers = 0;
      _character.clear();
      _objects = new std::vector < std::vector < bm::GameObject * > * >;
      for (int i = 0; i <= MAP_X; i++)
	{
	  std::vector < bm::GameObject * > *column = new std::vector<bm::GameObject *>(MAP_Y);
	  _objects->push_back(column);
	}
      while (std::getline(_fileSave, _rdLine))
	{
	  if (_rdLine.size() < 2)
	    {
	      std::cerr << "error getline" << std::endl;
	      return (false);
	    }
	  if (_rdLine[0] == 'c' && _rdLine[1] == ':')
	    {
	      if (nb >= 5)
	      	{
	      	  std::cerr << "too much char" << std::endl;
	      	  return (false);
	      	}
	      std::stringstream	_stream(&_rdLine[2]);
	      size_t		i = 0;
	      while (std::getline(_stream, _word, ','))
		{
		  try {
		    int	value;

		    value = std::stoi(_word);
		    switch (i)
		      {
		      case 0:
			x = value;
			break;
		      case 1:
			y = value;
			break;
		      case 2:
			typeChar = value;
			break;
		      case 3:
			ms = value;
			break;
		      case 4:
			br = value;
			break;
		      case 5:
			mb = value;
			break;
		      case 6:
			score = value;
			break;
		      case 7:
			alive = (value ? true : false);
			if (x < 10 || x > 190 || y > 130 || y < 10)
			  break;
			if (typeChar) {
			  _humanPlayers += 1;
			  _character.push_back(new Character(_config.antialiasing, true));
			}
			else if (typeChar == 0) {
			  _character.push_back(new AI);
			}
			if (typeChar == 1)
			  {
			    setGraphChar(nb);
			    if (x > 190 || y > 130)
			      {
				std::cerr << "Char out of map" << std::endl;
				return (false);
			      }
			    if (nb == 1)
			      _character[nb - 1]->init(x, y, nb, _config.exp);
			    else
			      _character[nb - 1]->init(x, y, nb, 1);
			  }
			else if (typeChar == 0) {
			  setGraphChar(nb);
			  _character[nb - 1]->init(x, y, nb, 1);
			}
			_character[nb - 1]->setAlive(alive);
			if (ms >= 50 && ms <= 100)
			  _character[nb - 1]->setMoveSpeed(ms);
			else
			  _character[nb - 1]->setMoveSpeed(50);
			if (br >= 1 && br <= 3)
			  _character[nb - 1]->setBombRange(br);
			else
			  _character[nb - 1]->setBombRange(1);
			if (mb >= 1 && mb <= 3)
			  _character[nb - 1]->setMaxBomb(mb);
			else
			  _character[nb - 1]->setMaxBomb(1);
			if (score >= 0)
			  _character[nb - 1]->setScore(score);
			else
			  _character[nb - 1]->setScore(0);
			break;
		      }
		    i++;
		  } catch (const std::invalid_argument& e) {
		    std::cerr << e.what() << std::endl;
		    return false;
		  } catch (const std::out_of_range& e) {
		    std::cerr << e.what() << std::endl;
		    return false;
		  }
		}
	      if (i != 8)
		{
		  std::cerr << "ParseError" << std::endl;
		  return false;
		}
	      nb++;
	    }
	  else if (_rdLine[0] == 'o' && _rdLine[1] == ':')
	    {
	      if (y > 21)
		{
		  std::cerr << "too much object" << std::endl;
		  return (false);
		}
	      try {
		int	value;

		value = std::stoi(&_rdLine[2]);
		if (value == -1)
		  (*(*_objects)[x])[y] = new bm::Block(10,
						       value,
						       irr::core::vector3df(x * 10, 2.5, y * 10),
						       _config.antialiasing,
						       _sceneManager,
						       getTexture().getTexture(UNBREAKABLE));
		else if (value == 1)
		  (*(*_objects)[x])[y] = new bm::Block(10,
						       value,
						       irr::core::vector3df(x * 10, 2.5, y * 10),
						       _config.antialiasing,
						       _sceneManager,
						       getTexture().getTexture(BREAKABLE));
		y++;
		if (y == 15)
		  {
		    y = 0;
		    x++;
		  }
	      } catch (const std::invalid_argument& e) {
		std::cerr << e.what() << std::endl;
		return false;
	      } catch (const std::out_of_range& e) {
		std::cerr << e.what() << std::endl;
		return false;
	      }
	    }
	}
      _ground = new bm::Block(150, -1, irr::core::vector3df(75. * (21. / 15.), -75 - 2.5, 75),
			      _config.antialiasing, _sceneManager, getTexture().getTexture(GROUND));
      _ground->getBlock()->setScale(irr::core::vector3df(21. / 15., 1, 1));
      _ground->getBlock()->getMaterial(0).getTextureMatrix(0).setTextureScale(3, 3);
      _ground2 = new bm::Block(4000, -1, irr::core::vector3df(0., -2000 - 2.6, 75.),
			       _config.antialiasing, _sceneManager, getTexture().getTexture(GROUND));
      _ground2->getBlock()->getMaterial(0).getTextureMatrix(0).setTextureScale(20, 20);
      if (_character.size() != 4)
	{
	  _character.clear();
	  return (false);
	}
      return (true);
    }
  return (false);
}

void			bm::Game::introduction(bool isIntro)
{
  bm::Sound	sound;
  std::chrono::time_point<std::chrono::system_clock> start, end;
  int	timeElapsed(0);
  int	i = 35;
  int	a = 0;
  bool	step = false;

  if (isIntro == false)
    return ;
  _camera = _sceneManager->addCameraSceneNode(0, irr::core::vector3df(100., 110., 30.),
  					      irr::core::vector3df(100., 0., 55.));
  irr::scene::IParticleSystemSceneNode* particleSystem = _sceneManager->addParticleSystemSceneNode(true);
  irr::scene::IParticleEmitter* emitter = particleSystem->createBoxEmitter(irr::core::aabbox3d<irr::f32>(-10,-10,10,200,100,100),
									   irr::core::vector3df(0.0f,0.06f,0.0f),
									   5000, 20000,
									   irr::video::SColor(0,50,50,50),
									   irr::video::SColor(0,200,200,200),
									   500,1000,
									   360,
									   irr::core::dimension2df(0.2f,0.2f),
									   irr::core::dimension2df(0.3f,0.3f));
  particleSystem->setEmitter(emitter);
  particleSystem->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  particleSystem->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, true);
  particleSystem->setMaterialTexture(0, _driver->getTexture("lib/irrlicht-1.8.3/media/smoke.bmp"));
  particleSystem->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
  sound.play(AMBIANT_INTRO, true, 0.3);
  sound.play(INTRO_BREATH, true, 0.2);
  sound.play(INTRO_ORAL, false);
  while (_device->run() && timeElapsed <= TIME_INTRO)
    {
      start = std::chrono::system_clock::now();
      if (timeElapsed < TIME_INTRO - 2000)
	{
	  if (bm::Character::get_rand_bonus(2, 15) != -1)
	    {
	      if (!step)
		i++;
	      else
		i--;
	    }
	  std::this_thread::sleep_for(std::chrono::microseconds(10000));
	  if (i >= 55)
	    step = true;
	  else if (i <= 35)
	    step = false;
	}
      else
	{
	  i--;
	  if (i < 0)
	    i = 0;
	  a = i;
	}
      _driver->beginScene(true, true, irr::video::SColor(0, i, i, a));
      _sceneManager->drawAll();
      _driver->endScene();
      end = std::chrono::system_clock::now();
      timeElapsed += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }
}

void	bm::Game::setLight()
{
  for (int i = 0; i < _character.size(); i += 1) {
    irr::core::vector3df tmp_pos = _character[i]->getGraphic()->getPosition();

    tmp_pos.Y += 30;
    tmp_pos.X -= 30;
    _character[i]->setLight(_sceneManager->addLightSceneNode(0, tmp_pos, irr::video::SColorf(1, 1, 1), 10));
  }
  _camera = _sceneManager->addCameraSceneNode(0, irr::core::vector3df(100., 110., 30.),
					      irr::core::vector3df(100., 0., 55.));

}

void	bm::Game::setGUI()
{
  _gui->addImage(_texture.getTexture(BLOOD), irr::core::position2d<irr::s32>(1, 1), true, 0);
  _gui->addImage(_texture.getTexture(PLAYER1), irr::core::position2d<irr::s32>(0, 50), true, 0);
  _gui->addImage(_texture.getTexture(HUD_RANGE), irr::core::position2d<irr::s32>(8, 80), true, 0);
  _gui->addImage(_texture.getTexture(HUD_BOMB), irr::core::position2d<irr::s32>(8, 130), true, 0);
  _gui->addImage(_texture.getTexture(HUD_SPEED), irr::core::position2d<irr::s32>(8, 180), true, 0);
  _gui->addImage(_texture.getTexture(PLAYER2), irr::core::position2d<irr::s32>(0, 210), true, 0);
  _gui->addImage(_texture.getTexture(HUD_RANGE), irr::core::position2d<irr::s32>(8, 240), true, 0);
  _gui->addImage(_texture.getTexture(HUD_BOMB), irr::core::position2d<irr::s32>(8, 290), true, 0);
  _gui->addImage(_texture.getTexture(HUD_SPEED), irr::core::position2d<irr::s32>(8, 340), true, 0);
  _gui->addImage(_texture.getTexture(PLAYER3), irr::core::position2d<irr::s32>(0, 360), true, 0);
  _gui->addImage(_texture.getTexture(HUD_RANGE), irr::core::position2d<irr::s32>(8, 390), true, 0);
  _gui->addImage(_texture.getTexture(HUD_BOMB), irr::core::position2d<irr::s32>(8, 440), true, 0);
  _gui->addImage(_texture.getTexture(HUD_SPEED), irr::core::position2d<irr::s32>(8, 490), true, 0);
  _gui->addImage(_texture.getTexture(PLAYER4), irr::core::position2d<irr::s32>(8, 530), true, 0);
  _gui->addImage(_texture.getTexture(HUD_RANGE), irr::core::position2d<irr::s32>(8, 550), true, 0);
  _gui->addImage(_texture.getTexture(HUD_BOMB), irr::core::position2d<irr::s32>(8, 600), true, 0);
  _gui->addImage(_texture.getTexture(HUD_SPEED), irr::core::position2d<irr::s32>(8, 650), true, 0);
}

irr::gui::IGUIEnvironment			*bm::Game::getGUI() const
{
  return (_gui);
}

bool	bm::Game::isFinished()
{
  unsigned int	nbPlayerAlive = 0;

  for (auto it = _character.begin(); it != _character.end(); ++it) {
    if ((*it)->getAlive() == true)
      nbPlayerAlive += 1;
  }
  if (nbPlayerAlive == 1 || nbPlayerAlive == 0)
    return (true);
  return (false);
}

bool	bm::Game::getPause() const
{
  return (_pause);
}

void	bm::Game::setPause() {
  _pause = !_pause;
}

void	bm::Game::manageParticle() {
  std::chrono::time_point<std::chrono::system_clock> end
    = std::chrono::system_clock::now();

  if (_particle && _particle->size() > 0) {
    auto it = _particle->begin();
    while (it != _particle->end()) {
      int timeSpent =
	std::chrono::duration_cast<std::chrono::milliseconds> (end - (*it)->getTimer()).count();
      if (timeSpent >= LIFETIME_PARTICLE) {
	(*it)->getSystem()->remove();
	(*it)->getEmitter()->drop();
	it = _particle->erase(it);
      }
      if (it != _particle->end())
	it++;
    }
  }
}

void	bm::Game::managePlayer(const bool *keyCodes, const float frameDeltaTime) {
  for (int i = 0; i < _character.size(); i += 1) {
    if (_character[i]->isPlayer() == true) {
      _character[i]->manageObjects(&_character, this);
      if (_character[i]->getAlive() == true) {
	_character[i]->exec_command(keyCodes, frameDeltaTime, this);
	_character[i]->getGraphic()->setPosition(_character[i]->getPos());
	_character[i]->getLight()->setPosition(_character[i]->getGraphic()->getPosition());
      }
    }
  }
}

void	bm::Game::manageAI(const float frameDeltaTime) {
  for (int i = 0; i < _character.size(); i += 1) {
    if (_character[i]->isPlayer() == false) {
      _character[i]->manageObjects(&_character, this);
      if (_character[i]->getAlive() == true) {
	_character[i]->exec_command((dynamic_cast<AI *>(_character[i]))->survive(*this),
				    frameDeltaTime, this);
	_character[i]->getGraphic()->setPosition(_character[i]->getPos());
	_character[i]->getLight()->setPosition(_character[i]->getGraphic()->getPosition());
      }
    }
  }
}

void	bm::Game::drawScore(irr::gui::IGUIStaticText **scores, wchar_t msg[1024]) {
  swprintf(msg, 1024, L"        %d\n%d\n\n%d\n\n%d\n        %d\n%d\n\n%d\n\n%d\n        %d\n%d\n\n%d\n\n%d\n        %d\n%d\n\n%d\n\n%d\n",
	   _character[0]->getScore(), _character[0]->getBombRange(), _character[0]->getMaxBomb(), (int)((_character[0]->getMoveSpeed() - 50) / 10),
	   _character[1]->getScore(), _character[1]->getBombRange(), _character[1]->getMaxBomb(), (int)((_character[1]->getMoveSpeed() - 50) / 10),
	   _character[2]->getScore(), _character[2]->getBombRange(), _character[2]->getMaxBomb(), (int)((_character[2]->getMoveSpeed() - 50) / 10),
	   _character[3]->getScore(), _character[3]->getBombRange(), _character[3]->getMaxBomb(), (int)((_character[3]->getMoveSpeed() - 50) / 10));
  *scores = _gui->addStaticText(msg, irr::core::rect<irr::s32>(60,60,290,710), false, true, 0, -1, false);
  _font = _gui->getFont("assets/fonts/myfont.xml");
  (*scores)->setOverrideFont(_font);
  (*scores)->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
}

void	bm::Game::endGame() {
  bool	hasFinished = false;

  if (isFinished() == true) {
    for (auto it = _character.begin(); it != _character.end(); ++it) {
      if ((*it)->getAlive() == true && ((*it)->isPlayer() == true)) {
	_gui->addImage(_texture.getTexture(VICTORY), irr::core::position2d<irr::s32>(0, 0), true, 0);
	_driver->beginScene(true, true, irr::video::SColor(255, 255, 255, 255));
	_sceneManager->drawAll();
	_gui->drawAll();
	_driver->endScene();
	hasFinished = true;
	std::this_thread::sleep_for(std::chrono::seconds(2));
      }
      else if ((*it)->getAlive() == true) {
	_gui->addImage(_texture.getTexture(DEFEAT), irr::core::position2d<irr::s32>(0, 0), true, 0);
	_driver->beginScene(true, true, irr::video::SColor(255, 255, 255, 255));
	_sceneManager->drawAll();
	_gui->drawAll();
	_driver->endScene();
	hasFinished = true;
	std::this_thread::sleep_for(std::chrono::seconds(2));
      }
    }
  }
  if (isFinished() == true && hasFinished == false) {
    _gui->addImage(_texture.getTexture(DEFEAT), irr::core::position2d<irr::s32>(0, 0), true, 0);
    _driver->beginScene(true, true, irr::video::SColor(255, 255, 255, 255));
    _sceneManager->drawAll();
    _gui->drawAll();
    _driver->endScene();
	std::this_thread::sleep_for(std::chrono::seconds(2));
  }
  _config.exp = _character[0]->getScore();
  if (_character[0]->getScore() > _config.highscore)
    _config.highscore = _character[0]->getScore();
  _config.totalscore += _character[0]->getScore();
}

void    bm::Game::run() {
  const bool *keyCodes;

  _camera->setFarValue(10000.0f);
  unsigned int then = _device->getTimer()->getTime();
  _sound.play(bm::START, false, VOL_START);
  _sound.playAmbientMusic();
  irr::gui::IGUIStaticText *scores = NULL;
  wchar_t	msg[1024];
  _pause_gui = _gui->addImage(_texture.getTexture(PAUSE), irr::core::position2d<irr::s32>(0, 0), true, 0);
  while (_device->run() && isFinished() == false) {
    std::chrono::time_point<std::chrono::system_clock> end
      = std::chrono::system_clock::now();
    int timeSpent =
      std::chrono::duration_cast<std::chrono::milliseconds> (end - _start).count();

    if (_startAI == false
	&& timeSpent >= _wait) {
      _startAI = true;
    }
    const float frameDeltaTime = (float) (_device->getTimer()->getTime() - then) / 1000.f;
    then = _device->getTimer()->getTime();
    keyCodes = _receiver.getKeyCodes();
    if (keyCodes[bm::ESCAPE] == true
	&& _pause == false) {
      while (_device->run() && keyCodes[bm::ESCAPE] == true) {
	_pause_gui->setVisible(true);
        _driver->beginScene(true, true, irr::video::SColor(255, 255, 255, 255));
        _sceneManager->drawAll();
        _gui->drawAll();
	_driver->endScene();
	keyCodes = _receiver.getKeyCodes();
      }
      _pause = true;
    }
    else if (keyCodes[bm::ESCAPE] == true && _pause == true) {
      while (_device->run() && keyCodes[bm::ESCAPE] == true) {
	keyCodes = _receiver.getKeyCodes();
      }
      _pause = false;
    }
    if (_pause == false)
      {
	_pause_gui->setVisible(false);
	managePlayer(keyCodes, frameDeltaTime);
	if (_startAI == true)
	  manageAI(frameDeltaTime);
	manageParticle();
	if (scores != NULL)
	  scores->remove();
	drawScore(&scores, msg);
      }
    _driver->beginScene(true, true, irr::video::SColor(255, 255, 255, 255));
    _sceneManager->drawAll();
    _gui->drawAll();
    _driver->endScene();
  }
  endGame();
}

std::vector<std::vector<bm::GameObject * > * >	*bm::Game::getMap() const {
    return _objects;
}

bm::GameConfig					&bm::Game::getConfig() const
{
  return (_config);
}

std::vector<bm::Character *>	bm::Game::getCharacters() const {
    return _character;
}

irr::IrrlichtDevice		*bm::Game::getDevice() const
{
  return (_device);
}

irr::video::IVideoDriver	*bm::Game::getDriver() const
{
  return (_driver);
}

irr::scene::ISceneManager	*bm::Game::getScene() const
{
  return (_sceneManager);
}

bm::Texture			bm::Game::getTexture() const
{
  return (_texture);
}

std::vector<bm::Particle*>	*bm::Game::getParticle() const
{
  return (_particle);
}

void				bm::Game::setGUI(irr::gui::IGUIEnvironment *gui) {
  _gui = gui;
}

int				bm::Game::getNbHumanPlayers() const
{
  return (_humanPlayers);
}

std::vector<bm::Character*>	*bm::Game::getPtrCharacters() {
  return (&_character);
}

void				bm::Game::setHumanPlayers(int humanPlayers) {
  _humanPlayers = humanPlayers;
}

int					bm::Game::getMaxBomb() const {
	return (_MAX_BOMB);
}

int					bm::Game::getMaxRange() const {
	return (_MAX_RANGE);
}

int					bm::Game::getMaxMoveSpeed() const {
	return (_MAX_MOVESPEED);
}