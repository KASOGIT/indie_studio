//
// Launcher.cpp for Bomberman in /home/oliva/_workspace_indiestudio
// 
// Made by Clement Oliva
// Login   <oliva@epitech.net>
// 
// Started on  Tue May 31 22:47:33 2016 Clement Oliva
// Last update Sun Jun  5 20:23:52 2016 Clement Oliva
//

#include <stdexcept>
#include <iostream>

#include <irrlicht.h>

#include "Launcher.hpp"
#include "Loader/Loader.hpp"
#include "GUI/GUIUtil.hpp"
#include "Exceptions/InitError.hpp"
#include "Game.hpp"

bm::Launcher::Launcher() {
  std::clog << "Creating launcher..." << std::endl;
  bm::Loader::initDataDirectories();
  _config.currentProfile = bm::Loader::getLastProfile();
  _appContext = new bm::GUIContext(bm::Launcher::WINDOW_WIDTH,
				   bm::Launcher::WINDOW_HEIGHT,
				   bm::Launcher::WINDOW_CAPTION);
  if (_appContext) {
    _appContext->getDevice()->setResizable(false);
    this->loadLauncherAssets();
    this->playSplashScreen();
    _appContext->setEventReceiver<bm::LauncherEventReceiver>(this);
    this->initGUI();
  }
  else
    throw bm::InitError("Could not create GUIContext for Launcher.");
  if (!bm::Loader::readConfig(_config)) {
    std::cerr << "Creating default config file for \"" << _config.currentProfile
	      << "\"" << std::endl;
    bm::Loader::saveConfig(_config);
  }
}

bm::Launcher::~Launcher() {
  if (_appContext)
    delete _appContext;
}

void	bm::Launcher::loadLauncherAssets() {
  _fontCourier = bm::Loader::loadBMPFont(_appContext->getEnv(), "fontcourier.bmp");
  _imgLogo = bm::Loader::loadImage(_appContext->getDriver(), bm::Launcher::IMG_LOGO_FILE);
  _imgIrrLogo = bm::Loader::loadImage(_appContext->getDriver(),
				      bm::Launcher::IMG_IRRLOGO_FILE);
  _imgSubtitle = bm::Loader::loadImage(_appContext->getDriver(),
				       bm::Launcher::IMG_SUBTITLE_FILE);  
  _buttonImages[bm::Launcher::GUI_OPTION_BUTTON][NO_HOVER] =
    bm::Loader::loadImage(_appContext->getDriver(), bm::Launcher::IMG_OPTIONS_FILE);
  _buttonImages[bm::Launcher::GUI_OPTION_BUTTON][HOVER] =
    bm::Loader::loadImage(_appContext->getDriver(), bm::Launcher::IMG_OPTIONS_HOVER_FILE);
  _buttonImages[bm::Launcher::GUI_QUIT_BUTTON][NO_HOVER] =
    bm::Loader::loadImage(_appContext->getDriver(), bm::Launcher::IMG_QUIT_FILE);
  _buttonImages[bm::Launcher::GUI_QUIT_BUTTON][HOVER] =
    bm::Loader::loadImage(_appContext->getDriver(), bm::Launcher::IMG_QUIT_HOVER_FILE);
  _buttonImages[bm::Launcher::GUI_PLAY_BUTTON][NO_HOVER] =
    bm::Loader::loadImage(_appContext->getDriver(), bm::Launcher::IMG_PLAY_FILE);
  _buttonImages[bm::Launcher::GUI_PLAY_BUTTON][HOVER] =
    bm::Loader::loadImage(_appContext->getDriver(), bm::Launcher::IMG_PLAY_HOVER_FILE);
  _buttonImages[bm::Launcher::GUI_RANKING_BUTTON][NO_HOVER] =
    bm::Loader::loadImage(_appContext->getDriver(), bm::Launcher::IMG_RANKING_FILE);
  _buttonImages[bm::Launcher::GUI_RANKING_BUTTON][HOVER] =
    bm::Loader::loadImage(_appContext->getDriver(), bm::Launcher::IMG_RANKING_HOVER_FILE);
}

void	bm::Launcher::initGUI() {
  _appContext->setSkin(_appContext->getEnv()->createSkin(irr::gui::EGST_BURNING_SKIN));
  bm::Util::setSkinTransparency(255, _appContext->getSkin());
  if (_fontCourier)
    _appContext->setFont(_fontCourier);
  _hidingImage = NULL;
  if (_imgLogo) {
    _guiImgLogo = _appContext->addImage(_imgLogo, irr::core::dimension2d<irr::s32>
					(bm::Launcher::WINDOW_WIDTH / 2
					 - _imgLogo->getSize().Width / 2, 5));
    
    if (_imgSubtitle)
      _guiImgSubtitle = _appContext->addImage(_imgSubtitle,
					      irr::core::dimension2d<irr::s32>
					      (bm::Launcher::WINDOW_WIDTH / 2
					       - _imgSubtitle->getSize().Width / 2,
					       _imgLogo->getSize().Height - 50));
  }
  if (_imgIrrLogo)
    _guiImgIrrLogo = _appContext->addImage(_imgIrrLogo,
					   irr::core::dimension2d<irr::s32>
					   (bm::Launcher::WINDOW_WIDTH
					    - _imgIrrLogo->getSize().Width,
					    bm::Launcher::WINDOW_HEIGHT
					    - _imgIrrLogo->getSize().Height));
  _buttonPlay = _appContext->addButton(bm::Util::getRectFromPosAndSize<irr::s32>
				       ((bm::Launcher::WINDOW_WIDTH / 2)
					- (bm::Launcher::BUTTON_WIDTH / 2),
					(bm::Launcher::WINDOW_HEIGHT / 2)
					+ (bm::Launcher::BUTTON_WIDTH / 2),
					bm::Launcher::BUTTON_WIDTH,
					bm::Launcher::BUTTON_HEIGHT),
				       bm::Launcher::GUI_PLAY_BUTTON);
  this->buttonIsHovered(bm::Launcher::GUI_PLAY_BUTTON, NO_HOVER);
  _buttonOptions = _appContext->addButton(bm::Util::getRectFromPosAndSize<irr::s32>
					  (bm::Launcher::WINDOW_WIDTH / 2
					   - bm::Launcher::BUTTON_WIDTH * 1.5,
					   bm::Launcher::WINDOW_HEIGHT / 2 + 250,
					   bm::Launcher::BUTTON_WIDTH,
					   bm::Launcher::BUTTON_HEIGHT),
					  bm::Launcher::GUI_OPTION_BUTTON);
  this->buttonIsHovered(bm::Launcher::GUI_OPTION_BUTTON, NO_HOVER);
  _buttonQuit = _appContext->addButton(bm::Util::getRectFromPosAndSize<irr::s32>
				       (bm::Launcher::WINDOW_WIDTH / 2
					- bm::Launcher::BUTTON_WIDTH / 2,
					bm::Launcher::WINDOW_HEIGHT / 2 + 250,
					bm::Launcher::BUTTON_WIDTH,
					bm::Launcher::BUTTON_HEIGHT),
				       bm::Launcher::GUI_QUIT_BUTTON);
  this->buttonIsHovered(bm::Launcher::GUI_QUIT_BUTTON, NO_HOVER);
  _buttonRanking = _appContext->addButton(bm::Util::getRectFromPosAndSize<irr::s32>
					  (bm::Launcher::WINDOW_WIDTH / 2
					   + bm::Launcher::BUTTON_WIDTH / 2,
					   bm::Launcher::WINDOW_HEIGHT / 2 + 250,
					   bm::Launcher::BUTTON_WIDTH,
					   bm::Launcher::BUTTON_HEIGHT),
					  bm::Launcher::GUI_RANKING_BUTTON);
  this->buttonIsHovered(bm::Launcher::GUI_RANKING_BUTTON, NO_HOVER);
  _popup = NULL;
}

void	bm::Launcher::openOptionsPopup() {
  std::vector<std::string> profiles;
  irr::gui::IGUISpinBox	*humansSpinBox, *densitySpinBox;
  irr::gui::IGUIComboBox *gamemodeDropDown;

  if (!bm::Loader::readConfig(_config))
    std::cerr << "Could not load config file for \"" << _config.currentProfile
	      << "\"" << std::endl;
  _secondPopup = NULL;
  _popup = _appContext->addWindow(bm::Util::getRectFromPosAndSize<irr::s32>
				  (bm::Launcher::WINDOW_WIDTH / 2 - 320,
				   bm::Launcher::WINDOW_HEIGHT / 2 - 240,
				   640, 480), bm::Launcher::GUI_OPTION_POPUP,
				  true, L"Options");
  _appContext->addButton(bm::Util::getRectFromPosAndSize<irr::s32>(505, 410, 125, 50),
			 bm::Launcher::GUI_OPTION_SAVE, L"Save", L"Save options", _popup);
  _appContext->addButton(bm::Util::getRectFromPosAndSize<irr::s32>(505, 35, 125, 50),
			 bm::Launcher::GUI_OPTION_ADDPROFILE, L"Add profile",
			 L"Add a profile", _popup);
  _appContext->addButton(bm::Util::getRectFromPosAndSize<irr::s32>(505, 95, 125, 50),
			 bm::Launcher::GUI_OPTION_DELPROFILE, L"Delete profile",
			 L"Delete a profile", _popup);
  _appContext->addButton(bm::Util::getRectFromPosAndSize<irr::s32>(505, 155, 125, 50),
			 bm::Launcher::GUI_OPTION_RESET, L"Reset",
			 L"Reset profile options", _popup);
  _appContext->addCheckBox(bm::Util::getRectFromPosAndSize<irr::s32>(20, 405, 120, 20),
			   bm::Launcher::GUI_OPTION_ANTIALIAS, L"Antialiasing",
			   _config.antialiasing, _popup);
  _appContext->addCheckBox(bm::Util::getRectFromPosAndSize<irr::s32>(190, 405, 120, 20),
			   bm::Launcher::GUI_OPTION_SKIPINTRO, L"Skip intro",
			   _config.skipIntro, _popup);
  _appContext->addStaticText(L"Human players",
			     bm::Util::getRectFromPosAndSize<irr::s32>(20, 440, 130, 20),
			     _popup);
  _appContext->addStaticText(L"Map density",
			     bm::Util::getRectFromPosAndSize<irr::s32>(190, 440, 100, 20),
			     _popup);
  _appContext->addStaticText(L"Game mode",
  			     bm::Util::getRectFromPosAndSize<irr::s32>(505, 227, 90, 20),
  			     _popup);
  humansSpinBox = _appContext->addSpinBox(bm::Util::getRectFromPosAndSize<irr::s32>
				    (130, 440, 30, 15), bm::Launcher::GUI_OPTION_HUMANS,
				    L"", false, _popup);
  humansSpinBox->setDecimalPlaces(0);
  humansSpinBox->setRange(bm::GameConfig::DEFAULT_HUMANPLAYERS,
			  bm::GameConfig::MAX_HUMANPLAYERS);
  humansSpinBox->setValue(_config.humanPlayers);
  densitySpinBox = _appContext->addSpinBox(bm::Util::getRectFromPosAndSize<irr::s32>
					   (285, 440, 40, 15),
					   bm::Launcher::GUI_OPTION_DENSITY, L"",
					   false, _popup);
  densitySpinBox->setDecimalPlaces(0);
  densitySpinBox->setRange(0, bm::GameConfig::MAX_DENSITY);
  densitySpinBox->setValue(_config.density);
  gamemodeDropDown = _appContext->addComboBox(bm::Util::getRectFromPosAndSize<irr::s32>
					      (505, 245, 100, 20),
					      bm::Launcher::GUI_OPTION_GAMEMODE,
					      _popup);
  gamemodeDropDown->addItem(L"Normal", bm::GameConfig::GM_NORMAL);
  gamemodeDropDown->addItem(L"Dark", bm::GameConfig::GM_DARK);
  gamemodeDropDown->addItem(L"Urf", bm::GameConfig::GM_URF);
  gamemodeDropDown->setSelected(gamemodeDropDown->getIndexForItemData(_config.gameMode));
  _profilesList = _appContext->addListBox(bm::Util::getRectFromPosAndSize<irr::s32>
					  (20, 35, 470, 360),
					  bm::Launcher::GUI_OPTION_TABLE, true, _popup);
  profiles = bm::Loader::getProfiles();
  for (std::vector<std::string>::iterator it = profiles.begin();
       it != profiles.end(); it++) {
    _profilesList->addItem(bm::Util::toWString(*it).c_str());
    if (*it == _config.currentProfile)
      _profilesList->setSelected(it - profiles.begin());
  }
}

void	bm::Launcher::buttonIsHovered(const int id, const bool hover) {
  irr::gui::IGUIButton	*button = NULL;

  if ((button = this->getElement<irr::gui::IGUIButton>(id))
      && _buttonImages[id][hover ? 1 : 0]) {
    button->setImage(_buttonImages[id][hover ? 1 : 0]);
  }
}

void	bm::Launcher::openAddProfilePopup() {
  _secondPopup = _appContext->addWindow(bm::Util::getRectFromPosAndSize<irr::s32>
					(bm::Launcher::WINDOW_WIDTH / 2 - 125,
					 bm::Launcher::WINDOW_HEIGHT / 2 - 75, 250, 150),
					bm::Launcher::GUI_ADDPROFILE_POPUP,
					true, L"New profile");
  _appContext->addEditBox(bm::Util::getRectFromPosAndSize<irr::s32>
			  (15, 35, 220, 30), bm::Launcher::GUI_ADDPROFILE_EDITBOX, L"",
			  false, _secondPopup)->setMax(bm::GameConfig::PROFILE_MAXLEN);
  _appContext->addButton(bm::Util::getRectFromPosAndSize<irr::s32>
			 (20, 85, 95, 45), bm::Launcher::GUI_ADDPROFILE_ADD, L"Add", L"",
			 _secondPopup);
  _appContext->addButton(bm::Util::getRectFromPosAndSize<irr::s32>
			 (135, 85, 95, 45), bm::Launcher::GUI_ADDPROFILE_CANCEL,
			 L"Cancel", L"", _secondPopup);
}

void	bm::Launcher::openDelProfilePopup(std::string const &text) {
  _secondPopup = _appContext->addWindow(bm::Util::getRectFromPosAndSize<irr::s32>
					(bm::Launcher::WINDOW_WIDTH / 2 - 125,
					 bm::Launcher::WINDOW_HEIGHT / 2 - 75, 250, 150),
					bm::Launcher::GUI_DELPROFILE_POPUP,
					true, L"Delete profile");
  _appContext->addStaticText(std::wstring(L"Are you sure you want to delete ") +
			     bm::Util::toWString(text) + L"?",
			     bm::Util::getRectFromPosAndSize<irr::s32>
			     (20, 30, 210, 30), _secondPopup);
  _appContext->addButton(bm::Util::getRectFromPosAndSize<irr::s32>
			 (20, 85, 95, 45), bm::Launcher::GUI_DELPROFILE_DELETE,
			 L"Delete", L"", _secondPopup);
  _appContext->addButton(bm::Util::getRectFromPosAndSize<irr::s32>
			 (135, 85, 95, 45), bm::Launcher::GUI_DELPROFILE_CANCEL,
			 L"Cancel", L"", _secondPopup);
}

void	bm::Launcher::openRankingPopup() {
  irr::gui::IGUITable		*table;
  std::vector<std::string>	profiles;
  bm::GameConfig		tmp;
  
  _popup = _appContext->addWindow(bm::Util::getRectFromPosAndSize<irr::s32>
				  (bm::Launcher::WINDOW_WIDTH / 2 - 320,
				   bm::Launcher::WINDOW_HEIGHT / 2 - 240,
				   640, 480), bm::Launcher::GUI_RANKING_POPUP,
				  true, L"Ranking");
  table = _appContext->addTable(bm::Util::getRectFromPosAndSize<irr::s32>
				(20, 35, 600, 370), bm::Launcher::GUI_RANKING_TABLE,
				false, _popup);
  table->addColumn(L"Profile", 0);
  table->addColumn(L"Total score", 1);
  table->addColumn(L"Highest score", 2);
  table->setResizableColumns(false);
  table->setColumnWidth(0, 200);
  table->setColumnWidth(1, 200);
  table->setColumnWidth(2, 199);
  profiles = bm::Loader::getProfiles();
  for (std::vector<std::string>::const_iterator it = profiles.begin();
       it != profiles.end(); it++) {
    tmp.currentProfile = *it;
    if (bm::Loader::readConfig(tmp)) {
      int id = it - profiles.begin();
      table->addRow(id);
      table->setCellText(id, 0, bm::Util::toWString(*it).c_str());
      table->setCellText(id, 1, bm::Util::toWString
			 (std::to_string(tmp.totalscore)).c_str());
      table->setCellText(id, 2, bm::Util::toWString
			 (std::to_string(tmp.highscore)).c_str());
    }
  }
  table->setActiveColumn(1, true);
  _appContext->addButton(bm::Util::getRectFromPosAndSize<irr::s32>
			 (270, 420, 100, 50), bm::Launcher::GUI_RANKING_CLOSE,
			 L"Close", L"", _popup);
}

void	bm::Launcher::openQuitPopup() {
  _popup = _appContext->addWindow(bm::Util::getRectFromPosAndSize<irr::s32>
				  (bm::Launcher::WINDOW_WIDTH / 2 - 125,
				   bm::Launcher::WINDOW_HEIGHT / 2 - 75,
				   250, 150), bm::Launcher::GUI_QUIT_POPUP,
				  true, L"Quit");
  _appContext->addStaticText(L"Do you really want to quit?",
			     bm::Util::getRectFromPosAndSize<irr::s32>(15, 35, 220, 20),
			     _popup);
  _appContext->addButton(bm::Util::getRectFromPosAndSize<irr::s32>(15, 85, 95, 50),
			 bm::Launcher::GUI_QUIT_YES, L"Yes", L"", _popup);
  _appContext->addButton(bm::Util::getRectFromPosAndSize<irr::s32>(140, 85, 95, 50),
			 bm::Launcher::GUI_QUIT_NO, L"No", L"", _popup);
}

void	bm::Launcher::closePopup() {
  _popup->remove();
  _popup = NULL;
}

void	bm::Launcher::closeSecondPopup() {
  _secondPopup->remove();
  _secondPopup = NULL;
}

void	bm::Launcher::changeProfile() {
  if (_popup && _popup->getID() == bm::Launcher::GUI_OPTION_POPUP &&
      _profilesList->getSelected() != -1) {
    _config.currentProfile = bm::Util::toString(_profilesList->getListItem
						(_profilesList->getSelected()));
    bm::Loader::readConfig(_config);
    bm::Loader::updateLastProfile(_config.currentProfile);
  }
  this->updateOptionsPopup();
}

void	bm::Launcher::updateOptionsPopup() {
  irr::gui::IGUIComboBox	*mode = NULL;
  
  if (_popup && _popup->getID() == bm::Launcher::GUI_OPTION_POPUP) {
    this->getElement<irr::gui::IGUICheckBox>
      (bm::Launcher::GUI_OPTION_ANTIALIAS)->setChecked(_config.antialiasing);
    this->getElement<irr::gui::IGUICheckBox>
      (bm::Launcher::GUI_OPTION_SKIPINTRO)->setChecked(_config.skipIntro);
    this->getElement<irr::gui::IGUISpinBox>
      (bm::Launcher::GUI_OPTION_HUMANS)->setValue(_config.humanPlayers);
    this->getElement<irr::gui::IGUISpinBox>
      (bm::Launcher::GUI_OPTION_DENSITY)->setValue(_config.density);
    mode = this->getElement<irr::gui::IGUIComboBox>(bm::Launcher::GUI_OPTION_GAMEMODE);
    mode->setSelected(mode->getIndexForItemData(_config.gameMode));
  }
}

void	bm::Launcher::resetOptions() {
  if (_popup && _popup->getID() == bm::Launcher::GUI_OPTION_POPUP) {
    _config.resetOptions();
    this->updateOptionsPopup();
  }
}

void	bm::Launcher::saveOptions() {
  irr::gui::IGUIComboBox	*mode = NULL;
  
  std::clog << "Saving options..." << std::endl;
  if (_popup && _popup->getID() == bm::Launcher::GUI_OPTION_POPUP) {
    if (_profilesList->getSelected() != -1) {
      _config.currentProfile = bm::Util::toString(_profilesList->getListItem
						  (_profilesList->getSelected()));
      bm::Loader::readConfig(_config);
    }
    _config.antialiasing = (this->getElement<irr::gui::IGUICheckBox>
			    (bm::Launcher::GUI_OPTION_ANTIALIAS))->isChecked();
    _config.skipIntro = (this->getElement<irr::gui::IGUICheckBox>
			 (bm::Launcher::GUI_OPTION_SKIPINTRO))->isChecked();
    _config.humanPlayers = (this->getElement<irr::gui::IGUISpinBox>
			    (bm::Launcher::GUI_OPTION_HUMANS))->getValue();
    _config.density = (this->getElement<irr::gui::IGUISpinBox>
		       (bm::Launcher::GUI_OPTION_DENSITY))->getValue();
    mode = this->getElement<irr::gui::IGUIComboBox>(bm::Launcher::GUI_OPTION_GAMEMODE);
    _config.gameMode = static_cast<bm::GameConfig::GameMode>
      (mode->getItemData(mode->getSelected()));
  }
  bm::Loader::saveConfig(_config);
}

void	bm::Launcher::run() {
  std::clog << "Running launcher..." << std::endl;
  while (_appContext->run() && _appContext->driverExists()) {
    if (_appContext->beginScene(irr::video::SColor(255, 0, 0, 0))) {
      _appContext->drawAll();
      _appContext->endScene();
    }
  }
  std::clog << "Launcher finished running." << std::endl;
}

void	bm::Launcher::activateLauncherHiding() {
  _hidingImage = _appContext->addImage(bm::Loader::loadImage
				       (_appContext->getDriver(),
					bm::Launcher::IMG_GAMERUNNING_FILE),
				       irr::core::dimension2d<irr::s32>(0, 0));
  if (_appContext->beginScene(irr::video::SColor(255, 0, 0, 0))) {
    _hidingImage->draw();
    _appContext->endScene();
  }
}

void	bm::Launcher::launchGame() {
  std::clog << "Starting game..." << std::endl;
  Texture	bbmanTexture;
  
  this->activateLauncherHiding();
  _appContext->stopEventReceiver();
  _appContext->getDevice()->clearSystemMessages();
  bm::Game game(_config, bbmanTexture);
  game.run();
  bm::Loader::saveConfig(_config);
  _appContext->getDevice()->clearSystemMessages();
  _appContext->getDevice()->closeDevice();
  std::clog << "Game ended..." << std::endl;
}

bm::GameConfig		&bm::Launcher::getConfig() {
  return _config;
}

/*
 * Splash screen
 */


void	bm::Launcher::playSplashScreen() {
  irr::gui::IGUIImage	*logo;
  int			alpha = 0;
  
  if (_imgLogo) {
  int			ypos = (bm::Launcher::WINDOW_HEIGHT / 2
				- _imgLogo->getSize().Height / 2);

    logo = _appContext->addImage(_imgLogo, irr::core::dimension2d<irr::s32>
				 (bm::Launcher::WINDOW_WIDTH / 2
				  - _imgLogo->getSize().Width / 2, ypos));
    logo->setUseAlphaChannel(true);
    while (_appContext->run() && _appContext->driverExists() && ypos > 5) {
      if (_appContext->beginScene(irr::video::SColor(255, 0, 0, 0))) {
	_appContext->drawAll();
	bm::Util::wait(3);
	_appContext->endScene();
	logo->setColor(irr::video::SColor(alpha, alpha, alpha, alpha));
	if (alpha >= 255) {
	  ypos -= 2;
	  logo->setRelativePosition(irr::core::position2di(bm::Launcher::WINDOW_WIDTH / 2
							   - _imgLogo->getSize().Width / 2,
							   ypos));
	}
	else
	  alpha += 3;
	_appContext->endScene();
      }
    }
  }
}
