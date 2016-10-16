//
// Texture.cpp for  in /home/trambe_m/tek2/cpp/cpp_indie_studio
//
// Made by Manuel Trambert
// Login   <trambe_m@epitech.net>
//
// Started on  Fri Jun  3 15:22:08 2016 Manuel Trambert
// Last update Sun Jun  5 13:14:51 2016 Manuel Trambert
//

#include "Texture.hpp"

bm::Texture::Texture()
{
  bm::CFGParser	parser(_PATH_FILE_TEXTURE);
  bm::CFGParser	parserMesh(_PATH_FILE_MESH);


  _TAB_PATH_TEXTURE =  parser.parse();
  _TAB_PATH_MESH =  parserMesh.parse();
}

bm::Texture::~Texture() {

}

std::unordered_map<std::string, std::string>	bm::Texture::getTabPathTexture() const
{
  return (_TAB_PATH_TEXTURE);
}

std::unordered_map<std::string, std::string>	bm::Texture::getTabPathMesh() const
{
  return (_TAB_PATH_MESH);
}

irr::video::ITexture			*bm::Texture::getTexture(const enum TEXTURE_NAME var) const
{
  return (_TAB_TEXTURE.at(var));
}

irr::scene::IAnimatedMesh			*bm::Texture::getMesh(const enum MESH_NAME var) const
{
  return (_TAB_MESH.at(var));
}

void				bm::Texture::setDriver(irr::video::IVideoDriver *driver)
{
  _driver = driver;
}

void				bm::Texture::setScene(irr::scene::ISceneManager *scene)
{
  _sceneManager = scene;
}

void				bm::Texture::loadTexture()
{
  for (auto it : TAB_CONFIG_TEXTURE) {
    _TAB_TEXTURE.insert(std::pair<int, irr::video::ITexture *>(it.first,
							       _driver->getTexture(_TAB_PATH_TEXTURE[TAB_CONFIG_TEXTURE.at(it.first)].c_str())));
  }
}

void				bm::Texture::loadMesh()
{
  for (auto it : TAB_CONFIG_MESH) {
    irr::scene::IAnimatedMesh	*Mesh = _sceneManager->getMesh(_TAB_PATH_MESH[TAB_CONFIG_MESH.at(it.first)].c_str());
    if (Mesh == NULL)
      throw std::runtime_error("Mesh could not be loaded.");
    _TAB_MESH.insert(std::pair<int, irr::scene::IAnimatedMesh *>(it.first,
								 _sceneManager->getMesh(_TAB_PATH_MESH[TAB_CONFIG_MESH.at(it.first)].c_str())));
  }
}
