
#ifndef Ganymede_h
#define Ganymede_h

#include <chrono>
#include <memory>
#include <gdk/gdkx.h>
#include <libwnck/libwnck.h>

//struct WnckScreen;
//struct WnckWindow;


namespace ganymede {

	class Ganymede {

	public:

		Ganymede();

		int start(int argc, char **argv);

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

		std::chrono::system_clock::time_point m_startTime;
		GMainLoop *m_mainLoop;
	};
}

#endif /* Ganymede_h */
