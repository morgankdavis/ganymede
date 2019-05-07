
#include <libwnck/libwnck.h>

#include "Ganymede.h"

/*
#include <stdlib.h>
#include <glib.h>
#include <glib/gi18n.h>
*/
//#include <gdk/gdkx.h>
//#include <libwnck/libwnck.h>


//#ifdef ENABLE_UNIQUE
//#include <unique/unique.h>
//#endif /* ENABLE_UNIQUE */

#define VERSION "0.1" // MOVE

#define START_DELAY 0.5 // this is lame


using namespace ganymede;
using namespace std;



Ganymede::Ganymede() {

}


float Ganymede::runTime() {
	auto now = chrono::high_resolution_clock::now();
	return (chrono::duration<float>(now - m_startTime)).count();
}

void Ganymede::debugPrintApplicationInfo(WnckApplication* application) {

	const char* appName = g_strdup(wnck_application_get_name(application));
	printf("appName: %s\n", appName);

	// TODO: free strings - put in std::string
}

void Ganymede::debugPrintWindowInfo(WnckWindow* window) {

	WnckApplication* application = wnck_window_get_application(window);
	const char* appName = g_strdup(wnck_application_get_name(application));
	printf("appName: %s\n", appName);

	const char* winName = g_strdup(wnck_window_get_name(window));
	printf("winName: %s\n", winName);

	const char* winClass = g_strdup(wnck_class_group_get_res_class(wnck_window_get_class_group(window)));
	printf("winClass: %s\n", winClass);

	// TODO: free strings - put in std::string
}

void Ganymede::window_opened_cb(
		WnckScreen* screen,
		WnckWindow* window,
		Ganymede* ganymede) {

	if (ganymede->runTime() > START_DELAY) {
		printf("window_opened_cb()\n");
		ganymede->debugPrintWindowInfo(window);


//		wnck_window_set_window_type(window, WNCK_WINDOW_MENU);
//		typedef enum
//		{
//			WNCK_WINDOW_NORMAL,       /* document/app window */
//			WNCK_WINDOW_DESKTOP,      /* desktop background */
//			WNCK_WINDOW_DOCK,         /* panel */
//			WNCK_WINDOW_DIALOG,       /* dialog */
//			WNCK_WINDOW_TOOLBAR,      /* tearoff toolbar */
//			WNCK_WINDOW_MENU,         /* tearoff menu */
//			WNCK_WINDOW_UTILITY,      /* palette/toolbox window */
//			WNCK_WINDOW_SPLASHSCREEN  /* splash screen */
//		} WnckWindowType;

//		wnck_window_make_below(window);
//
//		wnck_window_close(window, 0); // works but the window briefly flickers on screen

		//wnck_window_set_geometry()

//		wnck_window_move_to_workspace(window, nullptr);
//		void           wnck_window_move_to_workspace (WnckWindow    *window,
//													  WnckWorkspace *space);
	}
}

void Ganymede::window_closed_cb(
		WnckScreen* screen,
		WnckWindow* window,
		Ganymede* ganymede) {

	if (ganymede->runTime() > START_DELAY) {
		printf("window_closed_cb()\n");
		ganymede->debugPrintWindowInfo(window);
	}
}

void Ganymede::application_opened_cb(
		WnckScreen* screen,
		WnckApplication* application,
		Ganymede* ganymede) {

	if (ganymede->runTime() > START_DELAY) {
		printf("application_opened_cb()\n");
		ganymede->debugPrintApplicationInfo(application);
	}
}

void Ganymede::application_closed_cb(
		WnckScreen* screen,
		WnckApplication* application,
		Ganymede* ganymede) {

	if (ganymede->runTime() > START_DELAY) {
		printf("application_closed_cb()\n");
		ganymede->debugPrintApplicationInfo(application);
	}
}




int Ganymede::start(int argc, char **argv) {

	m_startTime = chrono::high_resolution_clock::now();

	printf("Hello from Ganymede!\n");

	/* Initialise i18n */
//	bindtextdomain (GETTEXT_PACKAGE, LOCALEDIR);
//	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
//	textdomain (GETTEXT_PACKAGE);



	gdk_init(&argc, &argv);




	static const GOptionEntry options[] = {
//			{ "apply-to-existing", 'a', 0, G_OPTION_ARG_NONE, &apply_to_existing, N_("Apply to all existing windows instead of just new windows."), NULL },
//			{ "debug", 'd', 0, G_OPTION_ARG_NONE, &debug, N_("Output debug information"), NULL },
//			{ G_OPTION_REMAINING, '\0', 0, G_OPTION_ARG_FILENAME_ARRAY, &files, N_("Configuration files to use"), NULL },
//			{ NULL }
	};

	GError* error = nullptr;
	GOptionContext* context;

	context = g_option_context_new("Ganymede" VERSION);
//	g_option_context_add_main_entries (context, options, nullptr);
//	g_option_context_parse (context, &argc, &argv, &error);

	//WnckWorkspace* workspace = nullptr;

	// TODO: check this periodically (example: connect laptop to external displays)
	int num_screens = gdk_display_get_n_screens(gdk_display_get_default());
	printf("num_screens: %d\n", num_screens);
	for (int i=0; i<num_screens; ++i) {
		WnckScreen* screen = wnck_screen_get(i);
		g_signal_connect(screen, "window-opened", (GCallback)window_opened_cb, this);
		g_signal_connect(screen, "window-closed", (GCallback)window_opened_cb, this);
		g_signal_connect(screen, "application-opened", (GCallback)application_opened_cb, this);
		g_signal_connect(screen, "application-closed", (GCallback)application_closed_cb, this);

		//workspace = wnck_screen_get_workspace(screen, 2);
	}

	m_mainLoop = g_main_loop_new(nullptr, true);
	g_main_loop_run(m_mainLoop);

	return 0;
}

