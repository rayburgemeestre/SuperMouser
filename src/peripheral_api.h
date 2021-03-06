#ifndef __PERIPHERAL_API_H__
#define __PERIPHERAL_API_H__


extern void move_to(int x, int y);
extern void click_left(int x, int y);
extern void click_right(int x, int y);
extern void click_double(int x, int y);

class CursorWindow;
class HotkeyHandler;

extern void register_hotkey(CursorWindow *window, HotkeyHandler *superMouser);
extern void init_screensize(int *width, int *height);
#endif // __PERIPHERAL_API_H__
