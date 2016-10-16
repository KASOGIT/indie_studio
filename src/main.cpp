//
// main.cpp for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/cpp_indie_studio
//
// Made by
// Login   <@epitech.net>
//
// Started on  Tue May  3 19:05:33 2016
// Last update Sun Jun  5 14:44:29 2016 Manuel Trambert
//

#include <iostream>
#include <stdexcept>

#include "Launcher/Launcher.hpp"

int main() {
  try {
    bm::Launcher launcher;

    launcher.run();
  }
  catch (std::runtime_error const &e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}
