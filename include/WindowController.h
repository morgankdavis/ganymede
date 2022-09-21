#ifndef GANYMEDE_WINDOWCONTROLLER_H
#define GANYMEDE_WINDOWCONTROLLER_H


#include <memory>

#include <libwnck/libwnck.h>


namespace ganymede {


	class WindowController {

	public:

		WindowController();

		void position(WnckWindow& window,
					  WnckScreen& screen,
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

#endif //GANYMEDE_WINDOWCONTROLLER_H
