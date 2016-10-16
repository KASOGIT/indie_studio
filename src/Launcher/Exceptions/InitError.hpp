//
// InitError.hpp for Bomberman in /home/oliva/_workspace_indiestudio/Launcher/Exceptions
// 
// Made by Clement Oliva
// Login   <oliva@epitech.net>
// 
// Started on  Tue May 24 19:29:55 2016 Clement Oliva
// Last update Tue May 24 21:52:33 2016 Clement Oliva
//

#ifndef BOMBERMAN_INITERROR_HPP
#define BOMBERMAN_INITERROR_HPP

#include <string>
#include <stdexcept>

namespace bm {
  class InitError: public std::runtime_error {
  public:
    explicit InitError(std::string const &msg): std::runtime_error(msg) {
      _what = "InitError: " + msg;
    };

  public:
    const char *what() const noexcept {
      return _what.c_str();
    };

  private:
    std::string	_what;
  };
};

#endif /* !BOMBERMAN_INITERROR_HPP */
