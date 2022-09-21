#ifndef GANYMEDE_WINDOWMANAGER_H
#define GANYMEDE_WINDOWMANAGER_H


#include <memory>

#include <libwnck/libwnck.h>


namespace ganymede {


	class WindowManager {

	public:

		WindowManager();

		void tile(WnckScreen& screen,
				  WnckWindow& window,
				  unsigned widthDivision,
				  unsigned xDivision,
				  unsigned xOffset,
				  unsigned heightDivision,
				  unsigned yDivision,
				  unsigned yOffset);
	private:

//		std::shared_ptr<WnckScreen> _screen;
	};
}

#endif //GANYMEDE_WINDOWMANAGER_H
