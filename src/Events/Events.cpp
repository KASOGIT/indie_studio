/*
** Events.cpp for cpp_indie_studio
**
** Made by	Julian Vives
** Login	vives_j
**
** Started on	Wed May 18 14:46:05 2016 Julian Vives
** Last update	Sun Jun 05 05:54:31 2016 Julian Vives
*/

#include "Events.hpp"
#include <iostream>

bm::Events::Events() {
  for (size_t i = 0; i < irr::KEY_KEY_CODES_COUNT; i++)
    _tabKeys[i] = false;
}

bm::Events::~Events() {
}

bool	bm::Events::OnEvent(const irr::SEvent &event) {

  if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT
      && event.JoystickEvent.Joystick == 0) {

    if (event.JoystickEvent.Axis[0] != 0 && event.JoystickEvent.Axis[1] != 0) {
      const irr::f32 DEAD_ZONE = 0.05f;

      irr::f32 moveHorizontal = static_cast<irr::f32> (event.JoystickEvent.Axis[irr::SEvent::SJoystickEvent::AXIS_X] / 32767.f);
      irr::f32 moveVertical = static_cast<irr::f32>(event.JoystickEvent.Axis[irr::SEvent::SJoystickEvent::AXIS_Y] / -32767.f);

      this->setStateAt(Movements::RIGHT, false);
      this->setStateAt(Movements::UP, false);
      this->setStateAt(Movements::DOWN, false);
      this->setStateAt(Movements::LEFT, false);
      // UP
      if (moveVertical == 1.f ||
          (fabs(moveHorizontal) < DEAD_ZONE && moveVertical == 1.f)) {

	this->setStateAt(Movements::UP, true);
      } // DOWN
      else if (moveVertical == -1.f ||
	       (fabs(moveHorizontal) < DEAD_ZONE && moveVertical == -1.f)) {
	this->setStateAt(Movements::DOWN, true);
      } // RIGHT
      else if (moveHorizontal == 1.f ||
	       (fabs(moveVertical) < DEAD_ZONE && moveHorizontal == 1.f)) {
	this->setStateAt(Movements::RIGHT, true);
      } // LEFT
      else if (moveHorizontal == -1.f ||
	       (fabs(moveVertical) < DEAD_ZONE && moveHorizontal == -1.f)) {
	this->setStateAt(Movements::LEFT, true);
      }
    }
    this->setStateAt(Movements::SPACE, false);
    if (event.JoystickEvent.ButtonStates == _BUTTON_PS3_X)
      this->setStateAt(Movements::SPACE, true);
  }
  if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
    if (_KEY_CONVERTER.count(event.KeyInput.Key)) {
      this->setStateAt(_KEY_CONVERTER.at(event.KeyInput.Key),
		       event.KeyInput.PressedDown);
    }
  }
  if (event.EventType == irr::EET_LOG_TEXT_EVENT) {
    return true;
  }
  return false;
}

const bool (&bm::Events::getKeyCodes() const)[irr::KEY_KEY_CODES_COUNT] {
  return _tabKeys;
}

void	bm::Events::setStateAt(const enum Movements &keyCode, const bool value) {
  _tabKeys[keyCode] = value;
}

irr::core::array<irr::SJoystickInfo>			&bm::Events::getJoystickInfo() {
  return _joystickinfo;
}
