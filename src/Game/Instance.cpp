//
// Instance.cpp for  in /home/trambe_m/tek2/cpp/cpp_indie_studio/src/Game
// 
// Made by Manuel Trambert
// Login   <trambe_m@epitech.net>
// 
// Started on  Sun Jun  5 12:32:18 2016 Manuel Trambert
// Last update Sun Jun  5 18:27:12 2016 Manuel Trambert
//

#include "Game.hpp"
#include "Instance.hpp"

bm::Instance::Instance()
{

}

bm::Instance::~Instance()
{

}

void	bm::Instance::initPerso(int i, const enum TEXTURE_NAME &text, const enum MESH_NAME &mesh, bm::Game *info) {
  (*info->getPtrCharacters())[i]->setGraphic(info->getScene()->addAnimatedMeshSceneNode(info->getTexture().getMesh(mesh)));
  (*info->getPtrCharacters())[i]->getGraphic()->setMaterialTexture(0, info->getTexture().getTexture(text));
  if (i == 0) {
    (*info->getPtrCharacters())[i]->getGraphic()->setScale(irr::core::vector3df(0.3, 0.3, 0.3));
    (*info->getPtrCharacters())[i]->init(190, 130, 1, info->getConfig().exp);
  }
  else if (i == 1) {
    (*info->getPtrCharacters())[i]->getGraphic()->setScale(irr::core::vector3df(0.4, 0.4, 0.4));
    (*info->getPtrCharacters())[i]->init(10, 10, 2, 1);
  }
  else if (i == 2) {
    (*info->getPtrCharacters())[i]->getGraphic()->setScale(irr::core::vector3df(0.3, 0.3, 0.3));
    (*info->getPtrCharacters())[i]->init(190, 10, 3, 1);
  }
  else {
    (*info->getPtrCharacters())[i]->getGraphic()->setScale(irr::core::vector3df(0.5, 0.5, 0.5));
    (*info->getPtrCharacters())[i]->init(10, 130, 4, 1);
  }
  if (info->getConfig().gameMode == GameConfig::GameMode::GM_URF) {
	  (*info->getPtrCharacters())[i]->setBombRange(4);
	  (*info->getPtrCharacters())[i]->setMaxBomb(4);
  }
}

void        bm::Instance::initBord(int x, int z, bm::Game *info) {
    for (int i = 0; i <= x; i++) {
        std::vector < bm::GameObject * > *column = new std::vector<bm::GameObject *>(z);
        info->getMap()->push_back(column);
    }
    for (int j = 0; j < (x * z); j++) {
        if ((j % x) == 0 || (j / x) == 0 || (j % x) == (x - 1) || (j / x) == (z - 1) ||
            (((j % x) % 2) == 0 && ((j / x) % 2) == 0)) {
	  (*(*info->getMap())[j % x])[j / x] = new bm::Block(10,  -1, irr::core::vector3df((j % x) * 10, 2.5, (j / x) * 10), info->getConfig().antialiasing, info->getScene(),
							     info->getTexture().getTexture(UNBREAKABLE));
        }
        else if ((j % x > 2 && j % x < 18)
                 || (j / x > 2 && j / x < 12)) {

	  if (bm::Character::get_rand_bonus(1, info->getConfig().density * 10) > -1) {
	    (*(*info->getMap())[j % x])[j / x] = new bm::Block(10, 1, irr::core::vector3df((j % x) * 10, 2.5, (j / x) * 10), info->getConfig().antialiasing, info->getScene(), info->getTexture().getTexture(BREAKABLE));
	  }
        }
    }
    Block *_ground = new bm::Block(150,  -1, irr::core::vector3df(75. * (21. / 15.), -75 - 2.5, 75), info->getConfig().antialiasing, info->getScene(), info->getTexture().getTexture(GROUND));
    _ground->getBlock()->setScale(irr::core::vector3df(21. / 15., 1, 1));
    _ground->getBlock()->getMaterial(0).getTextureMatrix(0).setTextureScale(3, 3);
    Block *_ground2 = new bm::Block(4000,  -1, irr::core::vector3df(0., -2000 - 2.6, 75.), info->getConfig().antialiasing, info->getScene(), info->getTexture().getTexture(GROUND));
    _ground2->getBlock()->getMaterial(0).getTextureMatrix(0).setTextureScale(20, 20);
}

void		bm::Instance::initGame(bm::Game *info, Texture *text)
{
  text->setScene(info->getScene());
  text->loadMesh();
  info->getDevice()->getCursorControl()->setVisible(false);
  info->getDevice()->setWindowCaption(irr::core::stringw("Bomberman").c_str());
  info->setGUI(info->getDevice()->getGUIEnvironment());
  if (info->parseSave() == false) {
    info->getPtrCharacters()->clear();
    info->setHumanPlayers(info->getConfig().humanPlayers);
    info->getMap()->clear();
    initBord(21, 15, info);
    for (int i = 0; i < info->getConfig().humanPlayers; i += 1) {
      bm::Character *tmp = new Character(info->getConfig().antialiasing, true);

      info->getPtrCharacters()->push_back(tmp);
    }
    for (int i = 0; i < (4 - info->getConfig().humanPlayers); i += 1) {
      AI *tmpAI = new AI;

      info->getPtrCharacters()->push_back(tmpAI);
    }
    for (int i = 0; i < 4; i += 1) {
      initPerso(i, static_cast<enum TEXTURE_NAME>(i + 15),
		static_cast<enum MESH_NAME>(i + 2), info);
    }
  }
  info->setLight();
  if (info->getConfig().gameMode != bm::GameConfig::GM_DARK) {
    info->getScene()->setAmbientLight(irr::video::SColorf(0.2, 0.2, 0.2));
    info->getScene()->addLightSceneNode(0, irr::core::vector3df(100, 160, 0), irr::video::SColorf(1, 1, 1), 50);
  }
  info->setGUI();
  for (auto &it : info->getCharacters()) {
    if (it->getAlive() == false)
      it->getGraphic()->remove();
  }
}
