//
// Loader.hpp for Bomberman in /home/oliva/_workspace_indiestudio/Launcher/Loader
// 
// Made by Clement Oliva
// Login   <oliva@epitech.net>
// 
// Started on  Fri May 27 19:18:22 2016 Clement Oliva
// Last update Sun Jun  5 02:36:32 2016 Clement Oliva
//

#ifndef BOMBERMAN_LOADER_HPP
#define BOMBERMAN_LOADER_HPP

#include <string>
#include <vector>
#include <unordered_map>

#ifdef _WIN32
	#include <io.h>
#else
	#include <unistd.h>
#endif // _WIN32
#include <irrlicht.h>

#include "GameConfig.hpp"

namespace bm {
  class Loader {
    
    /*
     * Directories and files used by the Launcher
     */
    
  public:
    static constexpr const char *DATA_DIRECTORY = "data/";
    static constexpr const char *CONFIG_FILE = "config.cfg";
    static constexpr const char *LASTPROFILE_FILE = ".lastProfile";
    static constexpr const char *PROFILE_DIRECTORY = "profile/";
    static constexpr const char *FONT_DIRECTORY = "fonts/";
    static constexpr const char *GFX_DIRECTORY = "gfx/";

    /*
     * Keys used in config files
     */
    
  public:
    static constexpr const char *CONFIG_SEPARATOR = "=";
    static constexpr const char *CONFIG_ANTIALIASING = "antialiasing";
    static constexpr const char *CONFIG_SKIPINTRO = "skipintro";
    static constexpr const char *CONFIG_HUMANPLAYERS = "humans";
    static constexpr const char *CONFIG_EXPERIENCE = "experience";
    static constexpr const char *CONFIG_HIGHSCORE = "highscore";
    static constexpr const char *CONFIG_TOTALSCORE = "totalscore";
    static constexpr const char *CONFIG_GAMEMODE = "gamemode";
    static constexpr const char *CONFIG_DENSITY = "density";
    
  public:
    Loader();
    ~Loader();
    
  public:
    // Ensures that "data/", "data/profile" and "data/profile/Guest" directories are created.
    static void	initDataDirectories();
    
  public:
    // The following functions load the requested element from "data/fonts" or "data/gfx"
    static irr::gui::IGUIFont *loadBMPFont(irr::gui::IGUIEnvironment *env,
					   std::string const &name);
    static irr::video::ITexture *loadImage(irr::video::IVideoDriver *driver,
					   std::string const &name);
    
  public:
    static std::vector<std::string> getProfiles();
    static bool	addProfile(std::string const &name);
    static bool readConfig(bm::GameConfig &config);
    static void	saveConfig(bm::GameConfig const &config);
    static void	updateLastProfile(std::string const &name);
    static std::string getLastProfile();
  };

  namespace LoaderUtil {
    bool	strToBool(std::string const &str);
    std::string	boolToStr(const bool b);
    std::vector<std::string> getFilesInDir(std::string const &path);
    bool	isDirectory(std::string const &file);
    bool	isFile(std::string const &file);
    bool	isReadable(std::string const &file);
    bool	isWriteable(std::string const &file);
    bool	createDir(std::string const &file);
    bool	fileExists(std::string const &file);
    bool	directoryExists(std::string const &file);
    bool	createDir(std::string const &path);
    bool	deleteDirRec(std::string const &path);
    inline bool deleteProfile(std::string const &name) {
      if (name == bm::GameConfig::DEFAULT_PROFILE || name.length() == 0)
	return false;
      std::string str = bm::Loader::DATA_DIRECTORY;
      str += bm::Loader::PROFILE_DIRECTORY;
      str += name;
      return bm::LoaderUtil::deleteDirRec(str);
    }
  };
};

#endif /* !BOMBERMAN_LOADER_HPP */
