
#include <libwnck/libwnck.h>

#include "Ganymede.h"


#define VERSION "0.1" // MOVE


using namespace std;
using namespace std::placeholders;

using namespace ganymede;


void Ganymede::OnDBusServerTileCallback(DBusServer& dbusServer,
										unsigned widthDivision,
										unsigned xDivision,
										unsigned xOffset,
										unsigned heightDivision,
										unsigned yDivision,
										unsigned yOffset) {
	printf("OnDBusServerTileCallback(widthDivision: %u\nxDivision: %u\nxOffset: %u\nheightDivision: %u\nyDivision: %u\nyOffset: %u)\n",
		   widthDivision, xDivision, xOffset, heightDivision, yDivision, yOffset);

	WnckScreen* screen = wnck_screen_get_default();
	WnckWindow* activeWin = wnck_screen_get_active_window(screen);

	_windowManager->tile(*screen,
						 *activeWin,
						 widthDivision, xDivision, xOffset,
						 heightDivision, yDivision, yOffset);
}

Ganymede::Ganymede() {

	_dbusServer = make_unique<DBusServer>();
	_dbusServer->tileCallback(bind(&Ganymede::OnDBusServerTileCallback, this, _1, _2, _3, _4, _5, _6, _7));

	_windowManager = make_unique<WindowManager>();
}

WindowManager& Ganymede::getSplitManager() {
	return *_windowManager;
};

bool Ganymede::isMainLoopRunning() {
	return g_main_loop_is_running(_mainLoop);
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
	printf("window_opened_cb()\n");
	printf("opened class group name: %s\n", wnck_window_get_class_group_name(window));

	if (ganymede->isMainLoopRunning()) {
		//ganymede->debugPrintWindowInfo(window);
	}
	else {
		printf("Ignoring event during initialization.\n");
	}
}

void Ganymede::window_closed_cb(
		WnckScreen* screen,
		WnckWindow* window,
		Ganymede* ganymede) {
	printf("window_closed_cb()\n");

	if (ganymede->isMainLoopRunning()) {
		//ganymede->debugPrintWindowInfo(window);
	}
	else {
		printf("Ignoring event during initialization.\n");
	}
}

void Ganymede::application_opened_cb(
		WnckScreen* screen,
		WnckApplication* application,
		Ganymede* ganymede) {
	printf("application_opened_cb()\n");

	if (ganymede->isMainLoopRunning()) {
		//ganymede->debugPrintApplicationInfo(application);
	}
	else {
		printf("Ignoring event during initialization.\n");
	}
}

void Ganymede::application_closed_cb(
		WnckScreen* screen,
		WnckApplication* application,
		Ganymede* ganymede) {
	printf("application_closed_cb()\n");

	if (ganymede->isMainLoopRunning()) {
		//ganymede->debugPrintApplicationInfo(application);
	}
	else {
		printf("Ignoring event during initialization.\n");
	}
}

int Ganymede::start(int argc, char **argv) {

	// https://developer-old.gnome.org/libwnck/stable/getting-started.html

	printf("Hello from Ganymede!\n");

	gdk_init(&argc, &argv);

	GError* error = nullptr;
	GOptionContext* context;

	context = g_option_context_new("Ganymede" VERSION);

	_mainLoop = g_main_loop_new(nullptr, true);

	// TODO: check this periodically (example: connect laptop to external displays)
	int num_screens = gdk_display_get_n_screens(gdk_display_get_default());
	printf("num_screens: %d\n", num_screens);

	for (int i=0; i<num_screens; ++i) {
		WnckScreen* screen = wnck_screen_get(i);

		int width = wnck_screen_get_width(screen);
		int height = wnck_screen_get_height(screen);
		printf("width: %d, height: %d\n", width, height);

		g_signal_connect(screen, "window-opened", (GCallback)window_opened_cb, this);
		g_signal_connect(screen, "window-closed", (GCallback)window_opened_cb, this);
		g_signal_connect(screen, "application-opened", (GCallback)application_opened_cb, this);
		g_signal_connect(screen, "application-closed", (GCallback)application_closed_cb, this);

		wnck_screen_force_update(screen);
	}

	printf("starting loop\n");

	g_main_loop_run(_mainLoop);
	g_main_loop_unref(_mainLoop);

	return 0;
}

