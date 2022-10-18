
#ifndef Ganymede_h
#define Ganymede_h

#include <chrono>
#include <memory>
#include <gdk/gdkx.h>
#include <libwnck/libwnck.h>

#include "DBusServer.h"
#include "WindowManager.h"

//struct WnckScreen;
//struct WnckWindow;


namespace ganymede {


	//class WindowManager;


	class Ganymede {

	public:

		Ganymede();

		int start(int argc, char **argv);

		WindowManager& getSplitManager();
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

		GMainLoop *_mainLoop;
		WnckHandle *_wnckHandle;

		std::unique_ptr<DBusServer>	_dbusServer;
		std::unique_ptr<WindowManager> _windowManager;

		void OnDBusServerTileCallback(DBusServer& dbusServer,
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
//		void OnDBusServerMaximizeCallback(DBusServer& dbusServer,
//										  POSITIONAL_FLAG flags);

	};
}

#endif /* Ganymede_h */
