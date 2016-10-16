/*
** CFGParser.cpp for cpp_indie_studio
**
** Made by	Julian Vives
** Login	vives_j
**
** Started on	Wed May 18 23:46:26 2016 Julian Vives
** Last update	Thu May 19 15:56:57 2016 Julian Vives
*/

#include "CFGParser.hpp"

bm::CFGParser::CFGParser() {

}

bm::CFGParser::CFGParser(const std::string &fileToParse) {
  _fileToParse = fileToParse;
}

bm::CFGParser::~CFGParser() {

}

void							bm::CFGParser::setFileToParse(const std::string &fileToParse) {
  _fileToParse = fileToParse;
}

const std::string &bm::CFGParser::getFileToParse() const {
  return _fileToParse;
}

std::string				bm::CFGParser::getKey(const std::string &line) {
  size_t					pos = line.find(_TOKEN);

  if (pos == std::string::npos)
    return "";
  return line.substr(0, pos);
}

std::string				bm::CFGParser::getValue(const std::string &line) {
  size_t					pos = line.find(_TOKEN);

  if (pos == std::string::npos)
    return "";
  return line.substr(pos + 1);
}

std::unordered_map<std::string, std::string>	bm::CFGParser::parse() {
  std::ifstream												inFile(this->getFileToParse());

  if (!inFile.is_open()) {
    std::cerr << "ParseError : File " << this->getFileToParse() << " not opened" << std::endl;
    return {{"", ""}};
  }

  std::string																		line;
  std::unordered_map<std::string, std::string>	tabParsed;
  size_t																				i = 1;
  while (std::getline(inFile, line)) {
    std::string			value(this->getValue(line));
    std::string			key(this->getKey(line));

    if (value.empty())
      std::cerr << "ParseError : on line " << i << " : Value is empty" << std::endl;
    else if (key.empty())
      std::cerr << "ParseError : on line " << i << " : Key is empty" << std::endl;
    else
      tabParsed.insert(std::make_pair<std::string, std::string>(this->getKey(line), this->getValue(line)));
    i++;
  }
  return tabParsed;
}
