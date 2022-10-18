#ifndef GANYMEDE_WINDOWMANAGER_H
#define GANYMEDE_WINDOWMANAGER_H


#include <memory>

#include <libwnck/libwnck.h>
#include <X11/Xlib.h>


namespace ganymede {


	class WindowManager {

	public:

		WindowManager();

		void tile(WnckScreen& screen,
				  WnckWindow& window,
				  unsigned widthDivision,
				  unsigned widthMultiplier,
				  unsigned xDivision,
				  unsigned xMultiplier,
				  unsigned xOffset,
				  unsigned heightDivision,
				  unsigned heightMultiplier,
				  unsigned yDivision,
				  unsigned yMultiplier,
				  unsigned yOffset);
	private:

		Display* 		_xDisplay;
//		std::shared_ptr<WnckScreen> _screen;
	};
}

#endif //GANYMEDE_WINDOWMANAGER_H
