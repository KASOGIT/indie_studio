//
// FileError.hpp for Bomberman in /home/oliva/_workspace_indiestudio/Launcher/Exceptions
// 
// Made by Clement Oliva
// Login   <oliva@epitech.net>
// 
// Started on  Sun May 29 16:59:52 2016 Clement Oliva
// Last update Sun May 29 17:00:28 2016 Clement Oliva
//

#ifndef BOMBERMAN_FILEERROR_HPP
#define BOMBERMAN_FILEERROR_HPP

#include <string>
#include <stdexcept>

namespace bm {
  class FileError: public std::runtime_error {
  public:
    explicit FileError(std::string const &msg): std::runtime_error(msg) {
      _what = "FileError: " + msg;
    };

  public:
    const char *what() const noexcept {
      return _what.c_str();
    };

  private:
    std::string	_what;
  };
};

#endif /* !BOMBERMAN_FILEERROR_HPP */
