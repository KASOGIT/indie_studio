#ifndef BOMBERMAN_LAUNCHER_HPP
#define BOMBERMAN_LAUNCHER_HPP

#include <string>
#include <irrlicht.h>

#include "Texture.hpp"
#include "GUI/GUIContext.hpp"
#include "LauncherEventReceiver.hpp"
#include "Loader/GameConfig.hpp"

#define NO_HOVER	0
#define HOVER		1

namespace bm {  
  class Launcher {
  public:
    enum ButtonID {
      GUI_QUIT_BUTTON = 0,
      GUI_PLAY_BUTTON = 1,
      GUI_RANKING_BUTTON = 2,
      GUI_RANKING_POPUP,
      GUI_RANKING_TABLE,
      GUI_RANKING_CLOSE,
      GUI_OPTION_BUTTON = 3,
      GUI_OPTION_POPUP,
      GUI_OPTION_TABLE,
      GUI_OPTION_SAVE,
      GUI_OPTION_ADDPROFILE,
      GUI_OPTION_DELPROFILE,
      GUI_OPTION_RESET,
      GUI_OPTION_ANTIALIAS,
      GUI_OPTION_SKIPINTRO,
      GUI_OPTION_DENSITY,
      GUI_OPTION_GAMEMODE,
      GUI_OPTION_HUMANS,
      GUI_ADDPROFILE_POPUP,
      GUI_ADDPROFILE_EDITBOX,
      GUI_ADDPROFILE_ADD,
      GUI_ADDPROFILE_CANCEL,
      GUI_DELPROFILE_POPUP,
      GUI_DELPROFILE_DELETE,
      GUI_DELPROFILE_CANCEL,
      GUI_QUIT_POPUP,
      GUI_QUIT_YES,
      GUI_QUIT_NO
    };
    
  private:
    static constexpr const wchar_t *WINDOW_CAPTION = L"BOOMBERMAN Launcher";
    static constexpr const unsigned int	WINDOW_HEIGHT = 720;
    static constexpr const unsigned int WINDOW_WIDTH = 1280;
    static constexpr const unsigned int	BUTTON_HEIGHT = 100;
    static constexpr const unsigned int BUTTON_WIDTH = 250;
    static constexpr const char	*IMG_BACKGROUND_FILE = "launcher_background.jpg";
    static constexpr const char	*IMG_LOGO_FILE = "bomberman_title.png";
    static constexpr const char	*IMG_SUBTITLE_FILE = "bomberman_poufsouffle.png";
    static constexpr const char	*IMG_IRRLOGO_FILE = "irrlicht_logo.png";
    static constexpr const char	*IMG_GAMERUNNING_FILE = "launcher_gamerunning.png";
    static constexpr const char	*IMG_PLAY_FILE = "launcher_play.png";
    static constexpr const char	*IMG_PLAY_HOVER_FILE = "launcher_play_hover.png";
    static constexpr const char	*IMG_QUIT_FILE = "launcher_quit.png";
    static constexpr const char	*IMG_QUIT_HOVER_FILE = "launcher_quit_hover.png";
    static constexpr const char	*IMG_OPTIONS_FILE = "launcher_options.png";
    static constexpr const char	*IMG_OPTIONS_HOVER_FILE = "launcher_options_hover.png";
    static constexpr const char	*IMG_RANKING_FILE = "launcher_ranking.png";
    static constexpr const char	*IMG_RANKING_HOVER_FILE = "launcher_ranking_hover.png";
    
  public:
    Launcher();
    ~Launcher();

  public:
    void			run();
    void			playSplashScreen();

  public:
    void			openOptionsPopup();
    void			updateOptionsPopup();
    void			openAddProfilePopup();
    void			openDelProfilePopup(std::string const &text);
    void			openQuitPopup();
    void			openRankingPopup();
    void			buttonIsHovered(const int id, const bool hover = true);
    void			closePopup();
    void			closeSecondPopup();
    void			launchGame();
    void			saveOptions();
    void			resetOptions();
    bm::GameConfig		&getConfig();
    void			changeProfile();

  public:
    template <class T = irr::gui::IGUIElement>
    T	*getElement(const irr::s32 id) {
      return static_cast<T *>
	(_appContext->getEnv()->getRootGUIElement()->getElementFromId(id, true));
    }
    
  private:
    void			initGUI();
    void			loadLauncherAssets();
    void			activateLauncherHiding();

  private:
    bm::GUIContext	       	*_appContext;
    bm::GameConfig		_config;

  private:
    irr::gui::IGUIFont		*_fontCourier;
    irr::video::ITexture	*_imgLogo;
    irr::video::ITexture	*_imgIrrLogo;
    irr::video::ITexture	*_imgSubtitle;
    irr::video::ITexture	*_buttonImages[4][2];

  private:
    irr::gui::IGUIButton	*_buttonPlay;
    irr::gui::IGUIButton	*_buttonQuit;
    irr::gui::IGUIButton	*_buttonOptions;
    irr::gui::IGUIButton	*_buttonRanking;
    irr::gui::IGUIImage		*_guiImgSubtitle;
    irr::gui::IGUIImage		*_guiImgLogo;
    irr::gui::IGUIImage		*_hidingImage;
    irr::gui::IGUIImage		*_guiImgIrrLogo;
    irr::gui::IGUIWindow	*_popup;
    irr::gui::IGUIWindow	*_secondPopup;
    irr::gui::IGUIListBox	*_profilesList;
  };
};

#endif /* !BOMBERMAN_LAUNCHER_HPP */
