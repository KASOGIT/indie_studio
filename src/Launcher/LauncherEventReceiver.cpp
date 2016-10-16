//
// LauncherEventReceiver.cpp for Bomberman in /home/oliva/_workspace_indiestudio/Launcher
// 
// Made by Clement Oliva
// Login   <oliva@epitech.net>
// 
// Started on  Fri May 27 19:25:31 2016 Clement Oliva
// Last update Sun Jun  5 16:39:01 2016 Clement Oliva
//

#include <iostream>

#include "LauncherEventReceiver.hpp"
#include "GUI/GUIUtil.hpp"
#include "Launcher.hpp"
#include "Loader/Loader.hpp"
#include "Loader/GameConfig.hpp"

bm::LauncherEventReceiver::LauncherEventReceiver(bm::IrrWindowContext &context, void *data):
  _context(context), _launcher(static_cast<bm::Launcher *>(data)) {
  
}

bm::LauncherEventReceiver::~LauncherEventReceiver() {
  
}

bool bm::LauncherEventReceiver::OnEvent(const irr::SEvent &event) {
  if (event.EventType == irr::EET_GUI_EVENT)
    return this->handleGUIEvent(event);
  else if (event.EventType == irr::EET_LOG_TEXT_EVENT)
    return true;
  return false;
}

bool bm::LauncherEventReceiver::handleGUIEvent(const irr::SEvent &event) {
  if (event.GUIEvent.Caller->getParent()) {
    switch (event.GUIEvent.Caller->getParent()->getID()) {
    case bm::Launcher::GUI_QUIT_POPUP:
      return this->handleQuitPopupEvent(event);
    case bm::Launcher::GUI_OPTION_POPUP:
      return this->handleOptionPopupEvent(event);
    case bm::Launcher::GUI_ADDPROFILE_POPUP:
      return this->handleAddProfilePopupEvent(event);
    case bm::Launcher::GUI_DELPROFILE_POPUP:
      return this->handleDelProfilePopupEvent(event);
    case bm::Launcher::GUI_RANKING_POPUP:
      return this->handleRankingPopupEvent(event);
    default:
      break;
    }
  }
  switch (event.GUIEvent.EventType) {
  case irr::gui::EGET_BUTTON_CLICKED:
    return this->handleGUIButtonClick(event);
  case irr::gui::EGET_ELEMENT_HOVERED:
  case irr::gui::EGET_ELEMENT_LEFT:
    if (event.GUIEvent.Caller->getType() == irr::gui::EGUIET_BUTTON) {
      _launcher->buttonIsHovered
	(event.GUIEvent.Caller->getID(),
	 (event.GUIEvent.EventType == irr::gui::EGET_ELEMENT_HOVERED));
      return true;
    }
    break;
  default:
    break;
  }
  return false;
}

bool	bm::LauncherEventReceiver::handleQuitPopupEvent(const irr::SEvent &event) {
  if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
    switch(event.GUIEvent.Caller->getID()) {
    case bm::Launcher::GUI_QUIT_YES:
      _context.device->closeDevice();
      return true;
    case bm::Launcher::GUI_QUIT_NO:
      _launcher->closePopup();
      return true;
    default:
      break;
    }
  }
  return false;
}

bool	bm::LauncherEventReceiver::handleOptionPopupEvent(const irr::SEvent &event) {
  if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
    switch(event.GUIEvent.Caller->getID()) {
    case bm::Launcher::GUI_OPTION_SAVE:
      _launcher->saveOptions();
      return true;
    case bm::Launcher::GUI_OPTION_RESET:
      _launcher->resetOptions();
      return true;
    case bm::Launcher::GUI_OPTION_ADDPROFILE:
      _launcher->openAddProfilePopup();
      return true;
    case bm::Launcher::GUI_OPTION_DELPROFILE: {
      irr::gui::IGUIListBox *list = static_cast<irr::gui::IGUIListBox *>
	(_launcher->getElement(bm::Launcher::GUI_OPTION_TABLE));
      if (bm::Util::toString(list->getListItem(list->getSelected())) !=
	  bm::GameConfig::DEFAULT_PROFILE)
	_launcher->openDelProfilePopup(bm::Util::toString
				       (list->getListItem(list->getSelected())));
      return true;
    }
    default:
      break;
    }
  }
  else if (event.GUIEvent.EventType == irr::gui::EGET_LISTBOX_CHANGED) {
    _launcher->changeProfile();
  }
  return false;
}

bool bm::LauncherEventReceiver::handleRankingPopupEvent(const irr::SEvent &event) {
  if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
    switch (event.GUIEvent.Caller->getID()) {
    case bm::Launcher::GUI_RANKING_CLOSE:
      _launcher->closePopup();
      return true;
    default:
      break;
    }
  }
  return false;
}

bool bm::LauncherEventReceiver::handleAddProfilePopupEvent(const irr::SEvent &event) {
  if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
    switch (event.GUIEvent.Caller->getID()) {
    case bm::Launcher::GUI_ADDPROFILE_ADD:
      this->addProfile(event);
      return true;
    case bm::Launcher::GUI_ADDPROFILE_CANCEL:
      _launcher->closeSecondPopup();
      return true;
    default:
      break;
    }
  }
  else if (event.GUIEvent.EventType == irr::gui::EGET_EDITBOX_ENTER) {
    this->addProfile(event);
    return true;
  }
  return false;
}

void bm::LauncherEventReceiver::addProfile(const irr::SEvent &event) {
  std::string newProfile = bm::Util::toString
    (event.GUIEvent.Caller->getParent()->getElementFromId
     (bm::Launcher::GUI_ADDPROFILE_EDITBOX)->getText());
  if (bm::Loader::addProfile(newProfile)) {
    irr::gui::IGUIListBox *list = _launcher->getElement<irr::gui::IGUIListBox>
      (bm::Launcher::GUI_OPTION_TABLE);
    if (list) {
      list->setSelected(list->addItem(bm::Util::toWString(newProfile).c_str()));
      _launcher->changeProfile();
    }
    _launcher->closeSecondPopup();
  }
}

bool bm::LauncherEventReceiver::handleDelProfilePopupEvent(const irr::SEvent &event) {
  if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
    switch (event.GUIEvent.Caller->getID()) {
    case bm::Launcher::GUI_DELPROFILE_DELETE: {
      irr::gui::IGUIListBox *list = static_cast<irr::gui::IGUIListBox *>
	(_launcher->getElement(bm::Launcher::GUI_OPTION_TABLE));
      if (list) {
	std::wstring tmp = list->getListItem(list->getSelected());
	if (tmp.length()) {
	  if (bm::LoaderUtil::deleteProfile(bm::Util::toString(tmp))) {
	    list->removeItem(list->getSelected());
	    if (_launcher->getConfig().currentProfile == bm::Util::toString(tmp))
	      _launcher->getConfig().currentProfile = bm::GameConfig::DEFAULT_PROFILE;
	  }
	}
	list->setSelected(bm::Util::toWString(bm::GameConfig::DEFAULT_PROFILE).c_str());
	_launcher->changeProfile();
      }
      _launcher->closeSecondPopup();
      return true;
    }
    case bm::Launcher::GUI_DELPROFILE_CANCEL:
      _launcher->closeSecondPopup();
      return true;
    default:
      break;
    }
  }
  return false;
}

bool bm::LauncherEventReceiver::handleGUIButtonClick(const irr::SEvent &event) {
  switch (event.GUIEvent.Caller->getID()) {
  case bm::Launcher::GUI_QUIT_BUTTON:
    _launcher->openQuitPopup();
    return true;
  case bm::Launcher::GUI_PLAY_BUTTON:
    _launcher->launchGame();
    return true;
  case bm::Launcher::GUI_OPTION_BUTTON:
    _launcher->openOptionsPopup();
    return true;
  case bm::Launcher::GUI_RANKING_BUTTON:
    _launcher->openRankingPopup();
    return true;
  default:
    break;
  }
  return false;
}
