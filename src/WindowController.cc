//
// Created by mkd on 9/16/22.
//

#include "WindowController.h"


using namespace ganymede;
using namespace std;


WindowController::WindowController() {}

void WindowController::position(WnckWindow& window,
								WnckScreen& screen,
								unsigned widthDivision,
								unsigned xDivision,
								unsigned xOffset,
								unsigned heightDivision,
								unsigned yDivision,
								unsigned yOffset) {
	printf("WindowController::position()\n");

	static bool set = true;

	// temporary since the window just opened in our test and is not active
	//sleep(1);

	//WnckWindow* activeWin = wnck_screen_get_active_window(&screen);
	WnckWindow* activeWin = &window;
	WnckWindow* prevWindow = NULL;

	printf("active class group name: %s\n", wnck_window_get_class_group_name(activeWin));

//	int activeX, activeY, activeW, activeH;
//	wnck_window_get_geometry(activeWin, &activeX, &activeY, &activeW, &activeH);

//	wnck_window_set_geometry(activeWin,
//							 WNCK_WINDOW_GRAVITY_CURRENT,
//							 (WnckWindowMoveResizeMask)
//							 	(WNCK_WINDOW_CHANGE_X
//								 | WNCK_WINDOW_CHANGE_Y
//								 | WNCK_WINDOW_CHANGE_WIDTH
//								 | WNCK_WINDOW_CHANGE_HEIGHT),
//							 activeX, activeY, activeW, activeH);

if (set) {
	wnck_window_set_geometry(activeWin,
							 WNCK_WINDOW_GRAVITY_CURRENT,
							 (WnckWindowMoveResizeMask)
									 (WNCK_WINDOW_CHANGE_X
									  | WNCK_WINDOW_CHANGE_Y
									  | WNCK_WINDOW_CHANGE_WIDTH
									  | WNCK_WINDOW_CHANGE_HEIGHT),
							 128, 128, 800, 1024);

	printf("pre wnck_screen_force_update\n");
	fflush(stdout);
	wnck_screen_force_update(&screen);
	printf("post wnck_screen_force_update\n");
	fflush(stdout);

	prevWindow = activeWin;
}
else {
	int activeX, activeY, activeW, activeH;
	//wnck_window_get_geometry
	//wnck_window_get_client_window_geometry
	wnck_window_get_geometry(prevWindow, &activeX, &activeY, &activeW, &activeH);


	printf("%d %d %d %d\n", wnck_screen_get_height(&screen) - activeX, activeY, activeW, activeH);
}

set = !set;

//	wnck_window_set_geometry(activeWin,
//							 WNCK_WINDOW_GRAVITY_CURRENT,
//							 (WnckWindowMoveResizeMask)
//									 (WNCK_WINDOW_CHANGE_X
//									  | WNCK_WINDOW_CHANGE_Y
//									  | WNCK_WINDOW_CHANGE_WIDTH
//									  | WNCK_WINDOW_CHANGE_HEIGHT),
//							 activeX, activeY, activeW, activeH);
}