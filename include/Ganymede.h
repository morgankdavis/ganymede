
#ifndef Ganymede_h
#define Ganymede_h

#include <chrono>
#include <memory>
#include <gdk/gdkx.h>
#include <libwnck/libwnck.h>

#include "DBusServer.h"
#include "WindowController.h"

//struct WnckScreen;
//struct WnckWindow;


namespace ganymede {


	//class WindowController;


	class Ganymede {

	public:

		Ganymede();

		int start(int argc, char **argv);

		WindowController& getSplitManager();
		bool isMainLoopRunning();

	protected:

		static void window_opened_cb(
				WnckScreen* screen,
				WnckWindow* window,
				Ganymede* ganymede);
		static void window_closed_cb(
				WnckScreen* screen,
				WnckWindow* window,
				Ganymede* ganymede);
		static void application_opened_cb(
				WnckScreen* screen,
				WnckApplication* app,
				Ganymede* ganymede);
		static void application_closed_cb(
				WnckScreen* screen,
				WnckApplication* app,
				Ganymede* ganymede);

	private:

		float runTime(); // should be const
		static void debugPrintApplicationInfo(WnckApplication* application); // should be const
		static void debugPrintWindowInfo(WnckWindow* window); // should be const

		std::chrono::system_clock::time_point _startTime;
		GMainLoop *_mainLoop;

		std::unique_ptr<DBusServer>	_dbusServer;
		std::unique_ptr<WindowController> _windowController;
	};
}

#endif /* Ganymede_h */
