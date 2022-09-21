#ifndef GANYMEDE_SPLITMANAGER_H
#define GANYMEDE_SPLITMANAGER_H


#include <memory>

#include <libwnck/libwnck.h>


namespace ganymede {


	class SplitManager {

	public:

		SplitManager();

		void position(WnckWindow& window,
					  WnckScreen& screen,
					  unsigned xDivision,
					  unsigned xDivisionPosition,
					  unsigned xDivisionOffset,
					  unsigned yDivision,
					  unsigned yDivisionPosition,
					  unsigned yDivisionOffset);

	private:

//		std::shared_ptr<WnckScreen> _screen;
	};
}

#endif //GANYMEDE_SPLITMANAGER_H
