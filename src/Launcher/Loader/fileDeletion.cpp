//
// fileDeletion.cpp for Bomberman in /home/oliva/_workspace_indiestudio/Launcher/Loader
// 
// Made by Clement Oliva
// Login   <oliva@epitech.net>
// 
// Started on  Thu Jun  2 16:50:41 2016 Clement Oliva
// Last update Sat Jun  4 02:36:09 2016 Clement Oliva
//

#include <string>
#include <iostream>

#include "Loader.hpp"

#if defined __linux__ || defined __unix__
#include <unistd.h>
#include <dirent.h>
#include <cstdlib>
#include <cstring>
#include <sys/stat.h>
#include <sys/types.h>

static bool    	deleteDirRec_unix(std::string const &path) {
  DIR			*directory = opendir(path.c_str());
  std::string		buf;
  struct dirent		*ent = NULL;
  struct stat		statbuf;

  if (directory) {
    while ((ent = readdir(directory))) {
      if (strcmp(ent->d_name, ".") && strcmp(ent->d_name, "..")) {
	buf = path + "/" +  ent->d_name;
	if (!stat(buf.c_str(), &statbuf)) {
	  if (S_ISDIR(statbuf.st_mode))
	    deleteDirRec_unix(buf);
	  else if (S_ISREG(statbuf.st_mode))
	    std::remove(buf.c_str()) == 0;
	  else
	    unlink(buf.c_str()) == 0;
	}
      }
    }
    closedir(directory);
  }
  return rmdir(path.c_str()) == 0;
}

#elif defined _WIN32
#include <Windows.h>

static bool    	deleteDirRec_windows(std::string const &path) {
  (void)path;
  return false;
}

#endif

bool	bm::LoaderUtil::deleteDirRec(std::string const &path) {
#if defined __linux__ || defined __unix__
  return deleteDirRec_unix(path);
#elif defined _WIN32
  return deleteDirRec_windows(path);
#endif
}
