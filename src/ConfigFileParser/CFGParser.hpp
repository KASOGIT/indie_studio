/*
** CFGParser.hpp for cpp_indie_studio
**
** Made by	Julian Vives
** Login	vives_j
**
** Started on	Wed May 18 23:36:45 2016 Julian Vives
** Last update	Thu May 19 14:34:23 2016 Julian Vives
*/

#ifndef _CFGPARSER_HPP_
# define _CFGPARSER_HPP_

#include <unordered_map>
#include <string>
#include <iterator>
#include <fstream>
#include <sstream>
#include <iostream>

#define 	CONFIG_PATH	"config"
#define		ASSET_PATH	"assets"

namespace bm {
  class			CFGParser {
  private:
    const	char				_TOKEN = '=';
    std::string				_fileToParse;

    std::string				getKey(const std::string &line);
    std::string				getValue(const std::string &line);

  public:
    CFGParser();
    CFGParser(const std::string &fileToParse);
    ~CFGParser();

    /**
    * @brief	Parses file set before.
    * @param	void
    * @return	Associative array with [KEY]=[VALUE] as contained in the CFG file.
    */
    std::unordered_map<std::string, std::string>	parse();

    /**
    * @brief	Sets the file to parse
    * @param  fileToParse 	path to the file
    * @return             	void
    */
    void    		setFileToParse(const std::string &fileToParse);

    /**
    * @brief	Gets the path to the file.
    * @return 							string
    */
    const std::string															&getFileToParse() const;
  };
};

#endif
