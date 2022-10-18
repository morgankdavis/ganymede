//
// Created by mkd on 9/16/22.
//

#include "WindowManager.h"

#include <math.h>

#include <X11/Xatom.h>


// documentation: https://developer-old.gnome.org/libwnck/stable/core.html


using namespace ganymede;
using namespace std;


typedef struct {
	int x;
	int y;
	int width;
	int height;
} Rect;

typedef struct {
	unsigned long left;
	unsigned long right;
	unsigned long top;
	unsigned long bottom;
} Extents;


void GetWindowCSDExtents(Display& display, WnckWindow& window, Extents** extents) {

	auto decorationExtents = (Extents*)malloc(sizeof(Extents));
	memset(decorationExtents, 0, sizeof(Extents));

	unsigned long *cardinals_p;
	int n_cardinals_p;
	Atom type;
	int format;
	unsigned int i;
	unsigned long n_cardinals;
	unsigned long bytes_after;
	unsigned char *propertyData;
	// TRY THIS: https://gitlab.xfce.org/xfce/xfce4-panel/-/blob/1a202bf2961db5c2481fbf9fe851aa15ed13dfc3/panel/panel-window.c#L2485
	Atom gtkFrameExtentAtom = XInternAtom(&display, "_GTK_FRAME_EXTENTS", false);
	int status = XGetWindowProperty(&display, wnck_window_get_xid(&window),
									gtkFrameExtentAtom,
									0, G_MAXLONG,
									FALSE,
									XA_CARDINAL,
									&type, &format,
									&n_cardinals, &bytes_after,
									(unsigned char **)&propertyData);

	if ((status == Success) && (propertyData != NULL) && (type != None)) {

		auto cardinals = (unsigned long*)propertyData;

		for (int i=0; i<n_cardinals; ++i) {
//			unsigned long item = cardinals[i] & ((1LL << format) - 1);
//			printf("d[%d]: %d\n", i, item);

			((unsigned long*)(decorationExtents))[i] = cardinals[i] & ((1LL << format) - 1);
		}
	}
	else {
		printf("*** Couldn't get _GTK_FRAME_EXTENTS atom ***\n");
	}

	XFree(propertyData);

	*extents = decorationExtents;
}

WindowManager::WindowManager() {
	_xDisplay = XOpenDisplay(NULL);
//	if (_xDisplay == NULL){
//		printf("fail\n");
//		exit(1);
//	}
//	else {
//		printf("success\n");
//	}
}

void WindowManager::tile(WnckScreen& screen,
						 WnckWindow& window,
						 unsigned widthDivision,
						 unsigned widthMultiplier,
						 unsigned xDivision,
						 unsigned xMultiplier,
						 unsigned xOffset,
						 unsigned heightDivision,
						 unsigned heightMultiplier,
						 unsigned yDivision,
						 unsigned yMultiplier,
						 unsigned yOffset) {

	printf("WindowManager::tile(\n"
		   "\tscreen: %p\n"
		   "\twindow: %p\n"
		   "\twidthDivision: %u\n"
		   "\twidthMultiplier: %u\n"
		   "\txDivision: %u\n"
		   "\txMultiplier: %u\n"
		   "\txOffset: %u\n"
		   "\theightDivision: %u\n"
		   "\theightMultiplier: %u\n"
		   "\tyDivision: %u\n"
		   "\tyMultiplier: %u\n"
		   "\tyOffset: %u)",
		   &screen, &window,
		   widthDivision, widthMultiplier, xDivision, xMultiplier, xOffset,
		   heightDivision, heightMultiplier, yDivision, yMultiplier, yOffset);

	static const int PANEL_HEIGHT = 24;
	Rect boundingRect = {
			0, 0, // PANEL_HEIGHT?
			wnck_screen_get_width(&screen), wnck_screen_get_height(&screen)-PANEL_HEIGHT };

	Extents* csdExtents;
	GetWindowCSDExtents(*_xDisplay, window, &csdExtents);
	printf("[csdExtents]\nleft: %lu\nright: %lu\ntop: %lu\nbottom: %lu\n",
		   csdExtents->left, csdExtents->right,
		   csdExtents->top, csdExtents->bottom);

	float width = ((float)boundingRect.width / (float)widthDivision) * (float)widthMultiplier;
	float xColumnSize = ((float)boundingRect.width / (float)xDivision) * (float)xMultiplier;
	float xPosition = (xColumnSize * (float)xOffset) + (float)boundingRect.x;

	float height = ((float)boundingRect.height / (float)heightDivision) * (float)heightMultiplier;
	float yColumnSize = ((float)boundingRect.height / (float)yDivision) * (float)yMultiplier;
	float yPosition = (yColumnSize * (float)yOffset) + (float)boundingRect.y;

	Rect rectWithDecorations {
			(int)round(xPosition),
			(int)round(yPosition),
			(int)round(width),
			(int)round(height),
	};

	printf("[rectWithDecorations]\nx: %d\ny: %d\nw: %d\nh: %d\n",
		   rectWithDecorations.x, rectWithDecorations.y,
		   rectWithDecorations.width, rectWithDecorations.height);

	Rect csdAdjustedRect {
			rectWithDecorations.x + boundingRect.x - (int)csdExtents->left,
			rectWithDecorations.y + boundingRect.y - (int)csdExtents->top,
			rectWithDecorations.width + (int)csdExtents->left + (int)csdExtents->right,
			rectWithDecorations.height + (int)csdExtents->top + (int)csdExtents->bottom
	};

	Rect finalRect = csdAdjustedRect;

	printf("[finalRect]\nx: %d\ny: %d\nw: %d\nh: %d\n",
		   finalRect.x, finalRect.y, finalRect.width, finalRect.height);

	if (wnck_window_is_fullscreen(&window)) wnck_window_set_fullscreen(&window, false);
	if (wnck_window_is_maximized(&window)) wnck_window_unmaximize(&window);

	wnck_window_set_geometry(&window,
							 WNCK_WINDOW_GRAVITY_STATIC,
							 (WnckWindowMoveResizeMask)
									 (WNCK_WINDOW_CHANGE_X
									  | WNCK_WINDOW_CHANGE_Y
									  | WNCK_WINDOW_CHANGE_WIDTH
									  | WNCK_WINDOW_CHANGE_HEIGHT),
							 finalRect.x, finalRect.y, finalRect.width, finalRect.height);

	free(csdExtents);
}