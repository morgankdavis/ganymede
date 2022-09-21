//
// Created by mkd on 9/16/22.
//

#include "WindowManager.h"

#include <math.h>


// documentation: https://developer-old.gnome.org/libwnck/stable/core.html


using namespace ganymede;
using namespace std;


WindowManager::WindowManager() {}

void WindowManager::tile(WnckScreen& screen,
						 WnckWindow& window,
						 unsigned widthDivision,
						 unsigned xDivision,
						 unsigned xOffset,
						 unsigned heightDivision,
						 unsigned yDivision,
						 unsigned yOffset) {
	printf("WindowManager::tile(\nwidthDivision: %u\nxDivision: %u\nxOffset: %u\nheightDivision: %u\nyDivision: %u\nyOffset: %u)\n",
		   widthDivision, xDivision, xOffset, heightDivision, yDivision, yOffset);


	int clientActiveX, clientActiveY, clientActiveWidth, clientActiveHeight;
	wnck_window_get_client_window_geometry(&window, &clientActiveX, &clientActiveY, &clientActiveWidth, &clientActiveHeight);
	printf("[CLIENT ACTIVE]\nclientActiveX: %d\nclientActiveY: %d\nclientActiveWidth: %d\nclientActiveHeight: %d\n",
		   clientActiveX, clientActiveY, clientActiveWidth, clientActiveHeight);


	int activeX, activeY, activeWidth, activeHeight;
	wnck_window_get_geometry(&window, &activeX, &activeY, &activeWidth, &activeHeight);
	printf("[ACTIVE]\nactiveX: %d\nactiveY: %d\nactiveWidth: %d\nactiveHeight: %d\n",
		   activeX, activeY, activeWidth, activeHeight);








	// temporary
	GdkRectangle boundingRect = {0, 0, 1920, 1200-24};

	float width = (float)boundingRect.width / (float)widthDivision;
	float xColumnSize = (float)boundingRect.width / (float)xDivision;
	float xPosition = (xColumnSize * (float)xOffset) + (float)boundingRect.x;

	float height = (float)boundingRect.height / (float)heightDivision;
	float yColumnSize = (float)boundingRect.height / (float)yDivision;
	float yPosition = (yColumnSize * (float)yOffset) + (float)boundingRect.y;

	// if the bottom or right edges of the window are next to the screen edge, round them so they line up nicely.
//	if (((xPosition + width) - (float)(boundingRect.x + boundingRect.width)) < 0.5f) {
//		printf("*** RIGHT-EDGE GAP ***\n");
//		width += 0.5f;
//	}
//	if (((yPosition + height) - (float)(boundingRect.y + boundingRect.height)) < 0.5f) {
//		printf("*** BOTTOM-EDGE GAP ***\n");
//		height += 0.5f;
//	}

	if (wnck_window_is_fullscreen(&window)) wnck_window_set_fullscreen(&window, false);
	if (wnck_window_is_maximized(&window)) wnck_window_unmaximize(&window);

	int finalX = (int)round(xPosition);
	int finalY = (int)round(yPosition);
	int finalWidth = (int)round(width);
	int finalHeight = (int)round(height);

	printf("[PLACING]\nfinalX: %d\nfinalY: %d\nfinalWidth: %d\nfinalHeight: %d\n",
		   finalX, finalY, finalWidth, finalHeight);

	wnck_window_set_geometry(&window,
							 WNCK_WINDOW_GRAVITY_STATIC,
							 (WnckWindowMoveResizeMask)
									 (WNCK_WINDOW_CHANGE_X
									  | WNCK_WINDOW_CHANGE_Y
									  | WNCK_WINDOW_CHANGE_WIDTH
									  | WNCK_WINDOW_CHANGE_HEIGHT),
							 finalX, finalY, finalWidth, finalHeight);
}