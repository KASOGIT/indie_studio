//
// GUIContext.hpp for Bomberman in /home/oliva/_workspace_indiestudio/Launcher/GUI
// 
// Made by Clement Oliva
// Login   <oliva@epitech.net>
// 
// Started on  Tue May 24 16:07:43 2016 Clement Oliva
// Last update Sat Jun  4 19:00:50 2016 Clement Oliva
//

#ifndef BOMBERMAN_GUICONTEXT_HPP
#define BOMBERMAN_GUICONTEXT_HPP

#include <string>
#include <cstddef>

#include <irrlicht.h>

#ifdef _IRR_WINDOWS_
#pragma comment(lib, Irrlicht.lib)
#endif

#include "IrrWindowContext.hpp"

namespace bm {
  class GUIContext {
  public:
    GUIContext(const std::size_t width = 640,
	       const std::size_t height = 480,
	       std::wstring const &windowCaption = L"");
    ~GUIContext();

  public:
    IrrWindowContext		*getWindowContext();
    irr::video::IVideoDriver	*getDriver();
    irr::gui::IGUIEnvironment	*getEnv();
    irr::IrrlichtDevice		*getDevice();
    irr::gui::IGUISkin		*getSkin();
    void			setSkin(irr::gui::IGUISkin *skin);
    irr::IEventReceiver		*getEventReceiver() const;
    std::size_t			getWindowWidth() const;
    std::size_t			getWindowHeight() const;

  public:
    template <class EventReceiver> void    setEventReceiver(void *data) {
      if (_eventReceiver)
	delete _eventReceiver;
      _eventReceiver = new EventReceiver(_context, data);
      _context.device->setEventReceiver(_eventReceiver);
    };
    void	stopEventReceiver();
    void	restoreEventReceiver();
    void	setWindowCaption(std::wstring const &windowCaption);
    void	setBuiltinFont(const irr::gui::EGUI_DEFAULT_FONT font);
    irr::gui::IGUIFont	*setBitmapFont(std::string const &file);
    void	setFont(irr::gui::IGUIFont *font);

  public:
    bool	run();
    bool	beginScene(irr::video::SColor const &color =
			   irr::video::SColor(0, 200, 200, 200));
    bool	endScene();
    void	drawAll();   

  public:
    bool	driverExists() const;
    bool	isActive() const;
    
  public:
    irr::gui::IGUIStaticText	*addStaticText(std::wstring const &text,
					       irr::core::rect<irr::s32> const &rect,
					       irr::gui::IGUIElement *parent = 0);
    irr::gui::IGUIImage		*addImage(irr::core::rect<irr::s32> const &rect,
					  irr::gui::IGUIElement *parent = 0);
    irr::gui::IGUIImage		*addImage(irr::video::ITexture *texture,
					  irr::core::dimension2d<irr::s32> const &pos,
					  irr::gui::IGUIElement *parent = 0);
    irr::gui::IGUIImage		*addImageFromFile(std::string const &file,
						  const int x, const int y,
						  irr::gui::IGUIElement *parent = 0);
    irr::gui::IGUIButton	*addButton(irr::core::rect<irr::s32> const &rect,
					   const int buttonId,
					   std::wstring const &caption = L"",
					   std::wstring const &desc = L"",
					   irr::gui::IGUIElement *parent = 0);
    irr::gui::IGUIContextMenu	*addContextMenu(irr::core::rect<irr::s32> const &rect,
						const int menuId,
						irr::gui::IGUIElement *parent = 0);
    irr::gui::IGUIScrollBar	*addScrollBar(irr::core::rect<irr::s32> const &rest,
					      const bool orientation,
					      const int scrollBarId,
					      irr::gui::IGUIElement *parent = 0);
    irr::gui::IGUIWindow	*addWindow(irr::core::rect<irr::s32> const &rect,
					   const int windowId,
					   const bool blocking = false,
					   std::wstring const &text = L"",
					   irr::gui::IGUIElement *parent = 0);
    irr::gui::IGUITable		*addTable(irr::core::rect<irr::s32> const &rect,
					  const int tableId,
					  const bool background = false,
					  irr::gui::IGUIElement *parent = 0);
    irr::gui::IGUIListBox	*addListBox(irr::core::rect<irr::s32> const &rect,
					    const int listId,
					    const bool background = false,
					    irr::gui::IGUIElement *parent = 0);
    irr::gui::IGUIEditBox	*addEditBox(irr::core::rect<irr::s32> const &rect,
					    const int boxId,
					    std::wstring const &text = L"",
					    const bool border = true,
					    irr::gui::IGUIElement *parent = 0);
    irr::gui::IGUICheckBox	*addCheckBox(irr::core::rect<irr::s32> const &rect,
					     const int boxId,
					     std::wstring const &text = L"",
					     const bool checked = false,
					     irr::gui::IGUIElement *parent = 0);
    irr::gui::IGUISpinBox	*addSpinBox(irr::core::rect<irr::s32> const &rect,
					    const int boxId,
					    std::wstring const &text = L"",
					    const bool border = false,
					    irr::gui::IGUIElement *parent = 0);
    irr::gui::IGUIComboBox	*addComboBox(irr::core::rect<irr::s32> const &rect,
					     const int boxId,
					     irr::gui::IGUIElement *parent = 0);
  private:
    void	init(const std::size_t width, const std::size_t height,
		     std::wstring const &windowCaption);
    void	initIrrWindowContext(irr::u32 width, irr::u32 height);
    
  private:
    IrrWindowContext		_context;
    irr::IEventReceiver		*_eventReceiver;
    std::size_t			_windowWidth;
    std::size_t			_windowHeight;
  };
};
  
#endif /* !BOMBERMAN_GUICONTEXT_HPP */
