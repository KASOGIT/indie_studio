/*
** Sound.hpp for cpp_indie_studio
**
** Made by	Julian Vives
** Login	vives_j
**
** Started on	Thu May 19 01:20:37 2016 Julian Vives
** Last update	Sat Jun 04 14:24:32 2016 Julian Vives
*/


#ifndef __SOUND_HPP__
#define __SOUND_HPP__

#include <iostream>
#include <irrKlang.h>
#include <functional>
#include "CFGParser.hpp"
#include "Thread.hpp"

#define 	SOUND_PATH	"sounds"
#define		CFG_SOUND	"./" CONFIG_PATH "/sounds.cfg"

namespace bm {
  enum		SOUND_NAME {
    EXPLOSION,
    BOMB_PLANTED,
    ITEM_GET,
    FIRE,
    BOMB_UP,
    START,
    AMBIENT_MUSIC,
    AMBIANT_INTRO,
    INTRO_BREATH,
    INTRO_ORAL
  };

  const	std::unordered_map<int, std::string>	TAB_SOUND = {
    {START, "Start"},
    {EXPLOSION, "Explosion"},
    {BOMB_PLANTED, "Bomb_planted"},
    {ITEM_GET, "Item_get"},
    {FIRE, "Fire_bonus"},
    {BOMB_UP, "Bomb_up_bonus"},
    {AMBIENT_MUSIC, "Ambient_music"},
    {AMBIANT_INTRO, "Ambiant_intro"},
    {INTRO_BREATH, "Intro_breath"},
    {INTRO_ORAL, "Intro_oral"}
  };

  class Sound {
  private:
    std::unordered_map<std::string, std::string>	_TAB_PATH_SOUND;
    irrklang::ISoundEngine				*_sound;
    irrklang::ISoundEngine				*_ambientSound;

    void	setSound(const std::string &path);
    void	__overridePlay2D(const enum SOUND_NAME &nameSound, bool loop, const float volume);
  public:
      Sound();
      ~Sound();

      void	setTabPathSound(const std::unordered_map<std::string, std::string> &tabPathSound);
      const std::unordered_map<std::string, std::string>	&getTabPathSound() const;
    void							play(const enum SOUND_NAME &nameSound, bool loop = false, const float volume = 1.0f);
      void							loadSound();
      void							playAmbientMusic();
    };
};

#endif /* !SOUND_HPP_ */
