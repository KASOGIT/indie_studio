//
// LauncherEventReceiver.hpp for Bomberman in /home/oliva/_workspace_indiestudio
// 
// Made by Clement Oliva
// Login   <oliva@epitech.net>
// 
// Started on  Fri May 27 19:26:45 2016 Clement Oliva
// Last update Sun Jun  5 00:48:00 2016 Clement Oliva
//

#ifndef BOMBERMAN_LAUNCHEREVENTRECEIVER_HPP
#define BOMBERMAN_LAUNCHEREVENTRECEIVER_HPP

#include <irrlicht.h>

#include "GUI/IrrWindowContext.hpp"
#include "Launcher.hpp"

namespace bm {
  class Launcher;
};

namespace bm {
  class LauncherEventReceiver: public irr::IEventReceiver {
  public:
    LauncherEventReceiver(bm::IrrWindowContext &context, void *launcher);
    ~LauncherEventReceiver();

  public:
    virtual bool       	OnEvent(const irr::SEvent &event);

  private:
    bool		handleGUIEvent(const irr::SEvent &event);
    bool		handleGUIButtonClick(const irr::SEvent &event);
    bool		handleQuitPopupEvent(const irr::SEvent &event);
    bool		handleOptionPopupEvent(const irr::SEvent &event);
    bool		handleAddProfilePopupEvent(const irr::SEvent &event);
    bool		handleRankingPopupEvent(const irr::SEvent &event);
    void		addProfile(const irr::SEvent &event);
    bool		handleDelProfilePopupEvent(const irr::SEvent &event);
    
  private:
    bm::Launcher		*_launcher;
    bm::IrrWindowContext	&_context;
  };
};

#endif /* !BOMBERMAN_LAUNCHEREVENTRECEIVER_HPP */
