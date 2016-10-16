//
// GameConfig.hpp for Bomberman in /home/oliva/_workspace_indiestudio/Launcher/Loader
// 
// Made by Clement Oliva
// Login   <oliva@epitech.net>
// 
// Started on  Wed Jun  1 18:31:58 2016 Clement Oliva
// Last update Sun Jun  5 06:13:33 2016 Clement Oliva
//

#ifndef BOMBERMAN_GAMECONFIG_HPP
#define BOMBERMAN_GAMECONFIG_HPP

#include <string>

namespace bm {
  class GameConfig {
  public:
    enum GameMode {
      GM_NORMAL = 0,
      GM_DARK = 1,
	GM_URF = 2
    };
    
  public:
    static constexpr const char		*DEFAULT_PROFILE = "Guest";
    static constexpr const unsigned int	PROFILE_MAXLEN = 20;
    static constexpr const bool		DEFAULT_ANTIALIASING = false;
    static constexpr const bool		DEFAULT_SKIPINTRO = false;
    static constexpr const unsigned int	DEFAULT_DENSITY = 6;
    static constexpr const unsigned int	MAX_DENSITY = 10;
    static constexpr const unsigned int	DEFAULT_EXP = 0;
    static constexpr const unsigned int	DEFAULT_HIGHSCORE = 0;
    static constexpr const unsigned int	DEFAULT_TOTALSCORE = 0;
    static constexpr const unsigned int	DEFAULT_HUMANPLAYERS = 1;
    static constexpr const unsigned int MAX_HUMANPLAYERS = 2;
    static constexpr const GameMode	DEFAULT_GAMEMODE = GM_NORMAL;
    static constexpr const unsigned int MAX_GAMEMODE = GM_URF;
    
  public:
    GameConfig(std::string const &profile = DEFAULT_PROFILE):
      currentProfile(profile),
      antialiasing(DEFAULT_ANTIALIASING),
      skipIntro(DEFAULT_SKIPINTRO),
      density(DEFAULT_DENSITY),
      humanPlayers(DEFAULT_HUMANPLAYERS),
      gameMode(DEFAULT_GAMEMODE),
      exp(DEFAULT_EXP),
      highscore(DEFAULT_HIGHSCORE),
      totalscore(DEFAULT_TOTALSCORE) {};
    ~GameConfig() {};

  public:
    inline void		resetOptions() {
      antialiasing = DEFAULT_ANTIALIASING;
      skipIntro = DEFAULT_SKIPINTRO;
      density = DEFAULT_DENSITY;
      gameMode = DEFAULT_GAMEMODE;
      humanPlayers = DEFAULT_HUMANPLAYERS;
    }

  public:
    std::string		currentProfile;
    bool		antialiasing;
    bool		skipIntro;
    unsigned int        humanPlayers;
    GameMode		gameMode;
    unsigned int	density;
    unsigned int	exp;
    unsigned int	level;
    unsigned int	highscore;
    unsigned int	totalscore;
  };
};

#endif /* BOMBERMAN_GAMECONFIG_HPP */
