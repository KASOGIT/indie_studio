//
// IrrWindowContext.hpp for Bomberman in /home/oliva/_workspace_indiestudio/Launcher/GUI
// 
// Made by Clement Oliva
// Login   <oliva@epitech.net>
// 
// Started on  Fri May 27 20:01:30 2016 Clement Oliva
// Last update Tue May 31 16:04:34 2016 Clement Oliva
//

#ifndef BOMBERMAN_IRRWINDOW_CONTEXT
#define BOMBERMAN_IRRWINDOW_CONTEXT

namespace bm{
  struct IrrWindowContext {
    irr::IrrlichtDevice         *device;
    irr::video::IVideoDriver    *driver;
    irr::scene::ISceneManager   *sceneManager;
    irr::gui::IGUIEnvironment   *guiEnv;
    irr::gui::IGUISkin          *guiSkin;
  };
}

#endif /* !BOMBERMAN_IRRWINDOW_CONTEXT */
