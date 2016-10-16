//
// GUIContext.cpp for Bomberman in /home/oliva/_workspace_indiestudio/Launcher/GUI
// 
// Made by Clement Oliva
// Login   <oliva@epitech.net>
// 
// Started on  Tue May 24 15:53:19 2016 Clement Oliva
// Last update Sat Jun  4 19:02:39 2016 Clement Oliva
//

#include "GUIContext.hpp"
#include "../Exceptions/InitError.hpp"

bm::GUIContext::GUIContext(const std::size_t width, const std::size_t height,
	       std::wstring const &windowCaption) {
  this->init(width, height, windowCaption);
}

bm::GUIContext::~GUIContext() {
  if (_eventReceiver)
    delete _eventReceiver;
  _context.device->closeDevice();
  _context.device->drop();
}

/*
 * Init functions
 */

void	bm::GUIContext::init(const std::size_t width, const std::size_t height,
			     std::wstring const &windowCaption) {
  _eventReceiver = NULL;
  this->initIrrWindowContext(width, height);
  this->setWindowCaption(windowCaption);
  this->setBuiltinFont(irr::gui::EGDF_MENU);
}

void	bm::GUIContext::initIrrWindowContext(irr::u32 width, irr::u32 height) {
  _context.device = irr::createDevice(irr::video::EDT_SOFTWARE,
				      irr::core::dimension2d<irr::u32>(width, height),
				      16, false, false, false, 0);
  if (_context.device == NULL)
    throw bm::InitError("irr::createDevice failed");
  _windowWidth = width;
  _windowHeight = height;
  _context.driver = _context.device->getVideoDriver();
  _context.sceneManager = _context.device->getSceneManager();
  _context.guiEnv = _context.device->getGUIEnvironment();
  _context.guiSkin = _context.guiEnv->getSkin();
}

/*
 * Execution functions
 */

bool	bm::GUIContext::run() {
  return _context.device->run();
}

void	bm::GUIContext::drawAll() {
  _context.guiEnv->drawAll();
}

bool	bm::GUIContext::beginScene(irr::video::SColor const &color) {
  return _context.driver->beginScene(true, true, color);
}

bool	bm::GUIContext::endScene() {
  return _context.driver->endScene();
}

/*
 * Conditions functions
 */

bool	bm::GUIContext::driverExists() const {
  return _context.driver != NULL;
}

bool	bm::GUIContext::isActive() const {
  return _context.device->isWindowActive();
}

/*
 * Getters
 */

bm::IrrWindowContext	*bm::GUIContext::getWindowContext() {
  return &_context;
}

irr::video::IVideoDriver	*bm::GUIContext::getDriver() {
  return _context.driver;
}

irr::gui::IGUIEnvironment	*bm::GUIContext::getEnv() {
  return _context.guiEnv;
}

irr::gui::IGUISkin	*bm::GUIContext::getSkin() {
  return _context.guiSkin;
}

irr::IrrlichtDevice	*bm::GUIContext::getDevice() {
  return _context.device;
}

void			bm::GUIContext::setSkin(irr::gui::IGUISkin *skin) {
  _context.guiEnv->setSkin(skin);
  _context.guiSkin = _context.guiEnv->getSkin();
}

irr::IEventReceiver	*bm::GUIContext::getEventReceiver() const {
  return _eventReceiver;
}

std::size_t		bm::GUIContext::getWindowWidth() const {
  return _windowWidth;
}

std::size_t		bm::GUIContext::getWindowHeight() const {
  return _windowWidth;
}

/*
 * Setters
 */

void	bm::GUIContext::setWindowCaption(std::wstring const &windowCaption) {
  _context.device->setWindowCaption(windowCaption.c_str()); 
}

void	bm::GUIContext::setBuiltinFont(const irr::gui::EGUI_DEFAULT_FONT font) {
  _context.guiSkin->setFont(_context.guiEnv->getBuiltInFont(), font);
}

irr::gui::IGUIFont	*bm::GUIContext::setBitmapFont(std::string const &file) {
  irr::gui::IGUIFont	*font;

  if ((font = _context.guiEnv->getFont(file.c_str())))
    _context.guiSkin->setFont(font);
  return font;
}

void	bm::GUIContext::setFont(irr::gui::IGUIFont *font) {
  _context.guiSkin->setFont(font);
}

/*
 * GUI Elements
 */

irr::gui::IGUIStaticText *bm::GUIContext::addStaticText(std::wstring const &text,
							irr::core::rect<irr::s32>
							const &rect,
							irr::gui::IGUIElement *parent) {
  return _context.guiEnv->addStaticText(text.c_str(), rect, false, true, parent);
}

irr::gui::IGUIImage *bm::GUIContext::addImage(irr::core::rect<irr::s32> const &rect,
					      irr::gui::IGUIElement *parent) {
  return _context.guiEnv->addImage(rect, parent);
}

irr::gui::IGUIImage *bm::GUIContext::addImage(irr::video::ITexture *texture,
					      irr::core::dimension2d<irr::s32> const &pos,
					      irr::gui::IGUIElement *parent) {
  return _context.guiEnv->addImage(texture, pos, true, parent);
}

irr::gui::IGUIImage *bm::GUIContext::addImageFromFile(std::string const &file,
						      const int x, const int y,
						      irr::gui::IGUIElement *parent) {
  return _context.guiEnv->addImage(_context.driver->getTexture(file.c_str()),
				   irr::core::position2d<int>(x, y), true, parent);
}

irr::gui::IGUIButton *bm::GUIContext::addButton(irr::core::rect<irr::s32> const &rect,
						const int buttonId,
						std::wstring const &caption,
						std::wstring const &desc,
						irr::gui::IGUIElement *parent) {
  return _context.guiEnv->addButton(rect, parent, buttonId, caption.c_str(), desc.c_str());
}

irr::gui::IGUIContextMenu *bm::GUIContext::addContextMenu(irr::core::rect<irr::s32>
							   const &rect,
							   const int menuId,
							   irr::gui::IGUIElement *parent) {
  return _context.guiEnv->addContextMenu(rect, parent, menuId);
}

irr::gui::IGUIScrollBar *bm::GUIContext::addScrollBar(irr::core::rect<irr::s32> const &rect,
						      const bool orientation,
						      const int scrollBarId,
						      irr::gui::IGUIElement *parent) {
  return _context.guiEnv->addScrollBar(orientation, rect, parent, scrollBarId);
}

irr::gui::IGUIWindow	*bm::GUIContext::addWindow(irr::core::rect<irr::s32> const &rect,
						   const int windowId,
						   const bool blocking,
						   std::wstring const &text,
						   irr::gui::IGUIElement *parent) {
  return _context.guiEnv->addWindow(rect, blocking, text.c_str(), parent, windowId);
}

irr::gui::IGUITable	*bm::GUIContext::addTable(irr::core::rect<irr::s32> const &rect,
						  const int tableId,
						  const bool background,
						  irr::gui::IGUIElement *parent) {
  return _context.guiEnv->addTable(rect, parent, tableId, background);
}

irr::gui::IGUIListBox	*bm::GUIContext::addListBox(irr::core::rect<irr::s32> const &rect,
						    const int listId,
						    const bool background,
						    irr::gui::IGUIElement *parent) {
  return _context.guiEnv->addListBox(rect, parent, listId, background);
}

irr::gui::IGUIEditBox	*bm::GUIContext::addEditBox(irr::core::rect<irr::s32> const &rect,
						    const int boxId,
						    std::wstring const &text,
						    const bool border,
						    irr::gui::IGUIElement *parent) {
  return _context.guiEnv->addEditBox(text.c_str(), rect, border, parent, boxId);
}

irr::gui::IGUICheckBox	*bm::GUIContext::addCheckBox(irr::core::rect<irr::s32> const &rect,
						     const int boxId,
						     std::wstring const &text,
						     const bool checked,
						     irr::gui::IGUIElement *parent) {
  return _context.guiEnv->addCheckBox(checked, rect, parent, boxId, text.c_str());
}

irr::gui::IGUISpinBox	*bm::GUIContext::addSpinBox(irr::core::rect<irr::s32> const &rect,
						    const int boxId,
						    std::wstring const &text,
						    const bool border,
						    irr::gui::IGUIElement *parent) {
  return _context.guiEnv->addSpinBox(text.c_str(), rect, border, parent, boxId);
}

irr::gui::IGUIComboBox	*bm::GUIContext::addComboBox(irr::core::rect<irr::s32> const &rect,
						     const int boxId,
						     irr::gui::IGUIElement *parent) {
  return _context.guiEnv->addComboBox(rect, parent, boxId);
}

/*
 * Other
 */

void		bm::GUIContext::stopEventReceiver() {
  _context.device->setEventReceiver(NULL);
}

void		bm::GUIContext::restoreEventReceiver() {
  _context.device->setEventReceiver(_eventReceiver);
}
