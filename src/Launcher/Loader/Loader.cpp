//
// Loader.cpp for Bomerman in /home/oliva/_workspace_indiestudio/Launcher/Loader
// 
// Made by Clement Oliva
// Login   <oliva@epitech.net>
// 
// Started on  Fri May 27 19:19:33 2016 Clement Oliva
// Last update Sun Jun  5 02:24:54 2016 Clement Oliva
//

#include <iostream>
#include <stdexcept>

#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#ifdef _WIN32
	#include <io.h>
	#include <direct.h>
#else
	#include <unistd.h>
#endif // _WIN32

#include "Loader.hpp"
#include "../../ConfigFileParser/CFGParser.hpp"
#include "../Exceptions/FileError.hpp"

bm::Loader::Loader() {

}

bm::Loader::~Loader() {

}

void				bm::Loader::initDataDirectories() {
  std::string			dataDir = bm::Loader::DATA_DIRECTORY;

  if (!bm::LoaderUtil::fileExists(dataDir) &&
      !bm::LoaderUtil::createDir(dataDir))
    throw bm::FileError(dataDir + " creation failed");
  if (!bm::LoaderUtil::fileExists(dataDir + bm::Loader::PROFILE_DIRECTORY) &&
      !bm::LoaderUtil::createDir(dataDir + bm::Loader::PROFILE_DIRECTORY))
    throw bm::FileError(dataDir + bm::Loader::PROFILE_DIRECTORY + " creation failed");
  if (!bm::LoaderUtil::fileExists(dataDir + bm::Loader::PROFILE_DIRECTORY + bm::GameConfig::DEFAULT_PROFILE + "/") &&
      !bm::LoaderUtil::createDir(dataDir + bm::Loader::PROFILE_DIRECTORY + bm::GameConfig::DEFAULT_PROFILE + "/"))
    throw bm::FileError
      (dataDir + bm::Loader::PROFILE_DIRECTORY + "Guest/ creation failed");
}

std::vector<std::string>	bm::Loader::getProfiles() {
  std::vector<std::string>	profiles;
  std::vector<std::string>	tmp;
  std::string			path = bm::Loader::DATA_DIRECTORY;
  
  path += bm::Loader::PROFILE_DIRECTORY;
  tmp = bm::LoaderUtil::getFilesInDir(path);
  for (std::vector<std::string>::const_iterator it = tmp.begin();
       it != tmp.end(); it++) {
    if ((*it)[0] != '.' && bm::LoaderUtil::isDirectory(path + *it))
      profiles.push_back(*it);
  }
  return profiles;
}

bool				bm::Loader::addProfile(std::string const &name) {
  std::string			dataDir = bm::Loader::DATA_DIRECTORY;
  
  dataDir += bm::Loader::PROFILE_DIRECTORY;
  if (name[0] != '.' && bm::LoaderUtil::fileExists(dataDir) &&
      !bm::LoaderUtil::fileExists(dataDir + name)) {
    if (bm::LoaderUtil::createDir(dataDir + name)) {
      saveConfig(bm::GameConfig(name));
      return true;
    }
  }
  return false;
}

bool		bm::Loader::readConfig(bm::GameConfig &config) {
  initDataDirectories();

  bm::CFGParser parser(std::string(DATA_DIRECTORY) + PROFILE_DIRECTORY
		       + config.currentProfile + "/" + CONFIG_FILE);
  std::unordered_map<std::string, std::string> data = parser.parse();

  try {
    config.antialiasing = LoaderUtil::strToBool(data.at(CONFIG_ANTIALIASING));
    config.humanPlayers = std::stoi(data.at(CONFIG_HUMANPLAYERS));
    if (config.humanPlayers > bm::GameConfig::MAX_HUMANPLAYERS)
      config.humanPlayers = bm::GameConfig::MAX_HUMANPLAYERS;
    if (config.humanPlayers == 0)
      config.humanPlayers = bm::GameConfig::DEFAULT_HUMANPLAYERS;
    config.gameMode = static_cast<bm::GameConfig::GameMode>
      (std::stoi(data.at(CONFIG_GAMEMODE)));
    if (config.gameMode > bm::GameConfig::MAX_GAMEMODE)
      config.gameMode = bm::GameConfig::DEFAULT_GAMEMODE;
    config.density = std::stoi(data.at(CONFIG_DENSITY));
    if (config.density > bm::GameConfig::MAX_DENSITY)
      config.density = bm::GameConfig::MAX_DENSITY;
    config.exp = std::stoi(data.at(CONFIG_EXPERIENCE));
    config.highscore = std::stoi(data.at(CONFIG_HIGHSCORE));
    config.totalscore = std::stoi(data.at(CONFIG_TOTALSCORE));
    config.skipIntro = LoaderUtil::strToBool(data.at(CONFIG_SKIPINTRO));
  }
  catch (std::out_of_range const &e) {
    return false;
  }
  return true;
}

void	bm::Loader::saveConfig(bm::GameConfig const &config) {  
  if (config.currentProfile.length()) {
    std::string	file = bm::Loader::DATA_DIRECTORY;
    file += bm::Loader::PROFILE_DIRECTORY;
    file += config.currentProfile + "/" + bm::Loader::CONFIG_FILE;
    
    std::ofstream stream(file);
    
    if (stream.is_open()) {
      stream << CONFIG_ANTIALIASING << CONFIG_SEPARATOR
	     << LoaderUtil::boolToStr(config.antialiasing) << std::endl;
      stream << CONFIG_HUMANPLAYERS << CONFIG_SEPARATOR
	     << config.humanPlayers << std::endl;
      stream << CONFIG_GAMEMODE << CONFIG_SEPARATOR
	     << static_cast<int>(config.gameMode) << std::endl;
      stream << CONFIG_DENSITY << CONFIG_SEPARATOR
	     << config.density << std::endl;
      stream << CONFIG_EXPERIENCE << CONFIG_SEPARATOR
	     << config.exp << std::endl;
      stream << CONFIG_HIGHSCORE << CONFIG_SEPARATOR
	     << config.highscore << std::endl;
      stream << CONFIG_TOTALSCORE << CONFIG_SEPARATOR
	     << config.totalscore << std::endl;
      stream << CONFIG_SKIPINTRO << CONFIG_SEPARATOR
	     << LoaderUtil::boolToStr(config.skipIntro) << std::endl;
      stream.close();
    }
    bm::Loader::updateLastProfile(config.currentProfile);
  }
}

void	bm::Loader::updateLastProfile(std::string const &str) {
  std::string	file = bm::Loader::DATA_DIRECTORY;
  file += bm::Loader::PROFILE_DIRECTORY;
  file += bm::Loader::LASTPROFILE_FILE;
  
  std::ofstream stream(file);

  if (stream.is_open()) {
    stream << str << std::endl;
    stream.close();
  }
}

std::string bm::Loader::getLastProfile() {
  std::string	path = bm::Loader::DATA_DIRECTORY;
  path += bm::Loader::PROFILE_DIRECTORY;

  std::ifstream stream(path + bm::Loader::LASTPROFILE_FILE);

  if (stream.is_open()) {
    std::string buf;
    
    stream >> buf;
    if (buf[0] != '.' && bm::LoaderUtil::fileExists(path + buf)
	&& bm::LoaderUtil::isDirectory(path + buf)) {
      stream.close();
      return buf;
    }
    stream.close();
  }
  bm::Loader::updateLastProfile(bm::GameConfig::DEFAULT_PROFILE);
  return bm::GameConfig::DEFAULT_PROFILE;
}

/*
 * Irrlicht loading functions
 */

irr::gui::IGUIFont	*bm::Loader::loadBMPFont(irr::gui::IGUIEnvironment *env,
						 std::string const &name) {
  std::string path = std::string(bm::Loader::DATA_DIRECTORY) + bm::Loader::FONT_DIRECTORY + name;
  
  return env->getFont(path.c_str());
}

irr::video::ITexture *bm::Loader::loadImage(irr::video::IVideoDriver *driver,
					    std::string const &name) {
  std::string path = std::string(bm::Loader::DATA_DIRECTORY) + bm::Loader::GFX_DIRECTORY + name;
  
  return driver->getTexture(path.c_str());
}

/*
 * bm::LoaderUtil functions
 */

bool	bm::LoaderUtil::strToBool(std::string const &str) {
  return str == "true";
}

std::string	bm::LoaderUtil::boolToStr(const bool b) {
  return b ? "true" : "false";
}

std::vector<std::string>	bm::LoaderUtil::getFilesInDir(std::string const &path) {
  std::vector<std::string>	files;
  DIR				*dir;
  struct dirent			*ent;

  dir = opendir(path.c_str());
  if (dir == NULL)
    throw bm::FileError("Could not open directory \"" + path + "\"");
  while ((ent = readdir(dir))) {
    files.push_back(ent->d_name);
  }
  closedir(dir);
  return files;
}

bool				bm::LoaderUtil::isDirectory(std::string const &file) {
  struct stat			file_stat;

  if (stat(file.c_str(), &file_stat) < 0) {
    return false;
  }
  return S_ISDIR(file_stat.st_mode);
}

bool				bm::LoaderUtil::isFile(std::string const &file) {
  struct stat			file_stat;

  if (stat(file.c_str(), &file_stat) < 1)
    return false;
  return S_ISREG(file_stat.st_mode);
}

inline bool		bm::LoaderUtil::isReadable(std::string const &file) {
#ifdef _WIN32
	return _access(file.c_str(), 06) == 0;
#else
	return access(file.c_str(), R_OK) == 0;
#endif // _WIN32
}

inline bool		bm::LoaderUtil::isWriteable(std::string const &file) {
#ifdef _WIN32
	return _access(file.c_str(), 06) == 0;
#else
  return access(file.c_str(), W_OK) == 0;
#endif	// _WIN32
}

inline bool    		bm::LoaderUtil::fileExists(std::string const &file) {
#ifdef _WIN32
	return _access(file.c_str(), 00) != -1;
#else
  return access(file.c_str(), F_OK) != -1;
#endif	// _WIN32
}

/*
 * File manipulation
 */

inline bool		bm::LoaderUtil::createDir(std::string const &path) {
#ifdef _WIN32
	return _mkdir(path.c_str()) == 0;
#else
	return mkdir(path.c_str(), 0755) == 0;
#endif // _WIN32
}
