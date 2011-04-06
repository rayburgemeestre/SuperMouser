#include "peripheral_api.h"

#ifdef __WXGTK__
#include <X11/Xlib.h>

void init_screensize(int *width, int *height)
{
	// TBD, find alternative for wxDisplaySize()
	width = 1280;
	height = 1024;
}

void register_hotkey(AbstractWindow *window)
{
}

void move_to(int x, int y) 
{
    Display *display = XOpenDisplay(0);
    Window root = XRootWindow(display, 0);
    XSelectInput(display, root, KeyReleaseMask);
    XWarpPointer(display, NULL, root, 0, 0, 0, 0, x, y);
}

void click_left(int x, int y) 
{
}

void click_right(int x, int y) 
{
}

void click_double(int x, int y) 
{
}
#endif // __WXGTK__