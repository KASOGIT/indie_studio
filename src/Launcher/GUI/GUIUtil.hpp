//
// GUIUtil.hpp for Bomberman in /home/oliva/_workspace_indiestudio/Launcher/GUI
// 
// Made by Clement Oliva
// Login   <oliva@epitech.net>
// 
// Started on  Wed May 25 21:27:42 2016 Clement Oliva
// Last update Sun Jun  5 05:28:59 2016 Clement Oliva
//

#ifndef BOMBERMAN_GUIUTIL_HPP
#define BOMBERMAN_GUIUTIL_HPP

#include <bitset>
#include <chrono>
#include <thread>

#ifndef _WIN32
# include <unistd.h>
#else
# include <Windows.h>
#endif

#include <irrlicht.h>

namespace bm {
  namespace Util {
    template <typename T>
    irr::core::rect<T>	getRectFromPosAndSize(T x, T y, T width, T height) {
      return irr::core::rect<T>(x, y, x + width, y + height);
    };

    inline void setSkinTransparency(irr::s32 alpha, irr::gui::IGUISkin *skin) {
      for (irr::s32 i = 0; i < irr::gui::EGDC_COUNT; ++i) {
	irr::video::SColor col = skin->getColor((irr::gui::EGUI_DEFAULT_COLOR)i);
	col.setAlpha(alpha);
	skin->setColor((irr::gui::EGUI_DEFAULT_COLOR)i, col);
      }
    };
    
    inline std::wstring	toWString(std::string const &str) {
      return std::wstring(str.begin(), str.end());
    };
      
    inline std::string toString(std::wstring const &str) {
      return std::string(str.begin(), str.end());
    };

    inline void	wait(unsigned int ms) {
		std::this_thread::sleep_for(std::chrono::microseconds(ms * 1000));
    }
  };
};

#endif /* !BOMBERMAN_GUIUTIL_HPP */
