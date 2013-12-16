#include "peripheral_api.h"

#ifdef __WXGTK__
#include <X11/Xlib.h>

#include<X11/extensions/Xrandr.h>


#include <signal.h>
#include <stdio.h>

Display                 *dpy;
Window                  root;
int                     num_sizes;
XRRScreenSize           *xrrs;
XRRScreenConfiguration  *conf;
short                   possible_frequencies[64][64];
short                   original_rate;
Rotation                original_rotation;
SizeID                  original_size_id;

void init_screensize(int *width, int *height)
{
	// Connect to X-server, get root window id
	dpy    = XOpenDisplay(NULL);
	root   = RootWindow(dpy, 0);

	// Get possible screen resolutions
	xrrs   = XRRSizes(dpy, 0, &num_sizes);

	// Loop through all possible resolutions, getting the selectable display frequencies
	for(int i = 0; i < num_sizes; i ++) {
		short   *rates;
		int     num_rates;

		printf("\n\t%2i : %4i x %4i   (%4imm x%4imm ) ", i, xrrs[i].width, xrrs[i].height, xrrs[i].mwidth, xrrs[i].mheight);

		rates = XRRRates(dpy, 0, i, &num_rates);

		for(int j = 0; j < num_rates; j ++) {
			possible_frequencies[i][j] = rates[j];
			printf("%4i ", rates[j]);
		}
	}

	printf("\n");
	// Get current resolution and frequency
	conf                   = XRRGetScreenInfo(dpy, root);
	original_rate          = XRRConfigCurrentRate(conf);
	original_size_id       = XRRConfigCurrentConfiguration(conf, &original_rotation);

	// Output some stuff
	printf("\n\tCURRENT SIZE ID  : %i\n", original_size_id);
	printf("\tCURRENT ROTATION : %i \n", original_rotation);
	printf("\tCURRENT RATE     : %i Hz\n\n", original_rate);

	// Write the correct width/height.
	*width = xrrs[original_size_id].width;
	*height = xrrs[original_size_id].height;

}

#include <signal.h>
#include <unistd.h>
#include <iostream>
#include "hotkeyhandler.h"

HotkeyHandler *globalHandler = NULL;

void register_hotkey(CursorWindow *window, HotkeyHandler *app)
{
	std::cout << "Registering hotkey" << std::endl;
	// I couldn't find any linux equivalent code for registering system wide hotkeys.
	// So after giving it a lot of thought I decided to use signals instead.
	// Use `kill -SIGINT <supermouser pid>' instead.
	// I use SIGINT because somehow I couldn't get it to work with SIGUSR1 or SIGUSR2 :-}

	globalHandler = app;

	signal(SIGINT, [&](int sig) -> void { 
		std::cout << "Signal triggered" << std::endl;
		// I tried capturing `app' in the lambda itself, it failed to compile..
		//app->HandleHotkey();
		if (globalHandler) {
			globalHandler->HandleHotkey();
		}
	});
}

void move_to(int x, int y) 
{
	printf("move_to(%d, %d)\n", x, y);
    Display *display = XOpenDisplay(0);
    Window root = XRootWindow(display, 0);
    XSelectInput(display, root, KeyReleaseMask);
    XWarpPointer(display, NULL, root, 0, 0, 0, 0, x, y);
	XFlush(display);
}

#include <string.h> // memset

void mouseClick(int button, bool doubleclick)
{
	Display *display = XOpenDisplay(NULL);

	XEvent event;
	
	if (display == NULL) {
		fprintf(stderr, "Error opening display\n");
		exit(EXIT_FAILURE);
	}
	
	for (int i=0; i<(doubleclick? 2 : 1); i++) {

		memset(&event, 0x00, sizeof(event));

		event.type = ButtonPress;
		event.xbutton.button = button;
		event.xbutton.same_screen = True;
		
		XQueryPointer(
			display,
			RootWindow(display, DefaultScreen(display)),
			&event.xbutton.root,
			&event.xbutton.window,
			&event.xbutton.x_root,
			&event.xbutton.y_root,
			&event.xbutton.x,
			&event.xbutton.y,
			&event.xbutton.state
		);
		
		event.xbutton.subwindow = event.xbutton.window;
		
		while(event.xbutton.subwindow) {
			event.xbutton.window = event.xbutton.subwindow;
			XQueryPointer(
				display,
				event.xbutton.window,
				&event.xbutton.root,
				&event.xbutton.subwindow,
				&event.xbutton.x_root,
				&event.xbutton.y_root,
				&event.xbutton.x,
				&event.xbutton.y,
				&event.xbutton.state
			);
		}
		
		if (XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0)
			fprintf(stderr, "Error\n");
		
		XFlush(display);
		
		usleep(100000);
		
		event.type = ButtonRelease;
		event.xbutton.state = 0x100;
		
		if (XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0)
			fprintf(stderr, "Error\n");

		if (doubleclick && !i) {
			std::cout << "double cl\n";
			usleep(80000);
		}
	}
	
	XFlush(display);
	
	XCloseDisplay(display);
}

void click_left(int x, int y) 
{
	mouseClick(Button1, false);
}

void click_right(int x, int y) 
{
	mouseClick(Button2, false);
}

void click_double(int x, int y) 
{
	mouseClick(Button1, true);
}
#endif // __WXGTK__
