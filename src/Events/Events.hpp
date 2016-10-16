/*
** Events.hpp for cpp_indie_studio
**
** Made by	Julian Vives
** Login	vives_j
**
** Started on	Wed May 18 14:44:50 2016 Julian Vives
** Last update	Sat Jun 04 22:04:03 2016 Julian Vives
*/

#ifndef _EVENTS_HPP_
# define _EVENTS_HPP_

# include 	<irrlicht.h>
# include 	<unordered_map>

namespace 	bm {
  enum 			Movements : int16_t {
    NONE = -1,
      UP = 0,
      RIGHT = 1,
      DOWN = 2,
      LEFT = 3,
      SPACE = 4,
      ESCAPE = 5,
      UP2 = 6,
      DOWN2 = 7,
      LEFT2 = 8,
      RIGHT2 = 9,
      BOMB2 = 10,
  };

  class	Events : public irr::IEventReceiver {
  private:
    const	std::unordered_map<int, enum Movements>	_KEY_CONVERTER = {
      {irr::EKEY_CODE::KEY_UP, 		UP},
      {irr::EKEY_CODE::KEY_DOWN, 	DOWN},
      {irr::EKEY_CODE::KEY_RIGHT, RIGHT},
      {irr::EKEY_CODE::KEY_LEFT, 	LEFT},
      {irr::EKEY_CODE::KEY_RETURN, SPACE},
      {irr::EKEY_CODE::KEY_ESCAPE, ESCAPE},
      {irr::EKEY_CODE::KEY_KEY_Z, UP2},
      {irr::EKEY_CODE::KEY_KEY_Q, LEFT2},
      {irr::EKEY_CODE::KEY_KEY_S, DOWN2},
      {irr::EKEY_CODE::KEY_KEY_D, RIGHT2},
      {irr::EKEY_CODE::KEY_SPACE, BOMB2},
      {0, NONE}
    };
    bool	_tabKeys[irr::KEY_KEY_CODES_COUNT];
    irr::core::array<irr::SJoystickInfo>	_joystickinfo;
    const size_t													_BUTTON_PS3_X = 16384;
  public:
    Events();
    virtual ~Events();
    virtual bool	OnEvent(const irr::SEvent &event);
    const bool		(&getKeyCodes()  const)[irr::KEY_KEY_CODES_COUNT];
    irr::core::array<irr::SJoystickInfo>	&getJoystickInfo();
    void		setStateAt(const enum Movements &keyCode, const bool value);
  };
};
#endif
