/*
** Sound.cpp for cpp_indie_studio
**
** Made by	Julian Vives
** Login	vives_j
**
** Started on	Thu May 19 01:20:32 2016 Julian Vives
** Last update	Sun Jun 05 08:40:21 2016 Julian Vives
*/

#include "Sound.hpp"

bm::Sound::Sound() {
  bm::CFGParser		parser(CFG_SOUND);

  this->setTabPathSound(parser.parse());
  _sound = irrklang::createIrrKlangDevice();
  _ambientSound = irrklang::createIrrKlangDevice();
}

bm::Sound::~Sound() {
  _sound->removeAllSoundSources();
  _sound->drop();
  _ambientSound->removeAllSoundSources();
  _ambientSound->drop();
}

void	bm::Sound::setTabPathSound(const std::unordered_map<std::string, std::string> &tabPathSound) {
  _TAB_PATH_SOUND = tabPathSound;
}

const std::unordered_map<std::string, std::string>	&bm::Sound::getTabPathSound() const {
  return _TAB_PATH_SOUND;
}

void				bm::Sound::playAmbientMusic() {
  if (!_ambientSound->isMultiThreaded())
    _ambientSound->update();
  _ambientSound->play2D(_TAB_PATH_SOUND[bm::TAB_SOUND.at(AMBIENT_MUSIC)].c_str(),
  true);
}

void				bm::Sound::__overridePlay2D(const enum SOUND_NAME &nameSound, bool loop, const float volume) {
  try {
    irrklang::ISound *sound =  _sound->play2D(_TAB_PATH_SOUND[bm::TAB_SOUND.at(nameSound)].c_str(), loop, true);

    if (sound == NULL)
      throw std::runtime_error("Error: sound could not be played");
    sound->setVolume(volume);
    sound->setIsPaused(false);
  }
  catch (std::runtime_error const &e) {
    std::cerr << e.what() << std::endl;
  }
}

void				bm::Sound::play(const enum SOUND_NAME &nameSound, bool loop, const float volume) {
  if (!bm::TAB_SOUND.count(nameSound))
    std::cerr << "ERROR : type of sound doesn't exist." << std::endl;
  else {
    Thread    threadSound(&bm::Sound::__overridePlay2D, this, nameSound, loop, volume);

    threadSound.launch();
  }
}
