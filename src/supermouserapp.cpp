/////////////////////////////////////////////////////////////////////////////
// Name:        supermouserapp.cpp
// Purpose:     
// Author:      Ray Burgemeestre
// Modified by: 
// Created:     04/04/2011 19:32:00
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

////@begin includes
////@end includes

#include "supermouserapp.h"

////@begin XPM images
////@end XPM images


/*
 * Application instance implementation
 */

////@begin implement app
IMPLEMENT_APP( SuperMouserApp )
////@end implement app


/*
 * SuperMouserApp type definition
 */

IMPLEMENT_CLASS( SuperMouserApp, wxApp )


/*
 * SuperMouserApp event table definition
 */

BEGIN_EVENT_TABLE( SuperMouserApp, wxApp )

////@begin SuperMouserApp event table entries
////@end SuperMouserApp event table entries

EVT_TIMER(1000, SuperMouserApp::OnTimer)

END_EVENT_TABLE()


#ifdef __WXMSW__
void move_to(int x, int y) 
{
    SetCursorPos(x, y);
}

void click_left(int x, int y) 
{
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

void click_right(int x, int y) 
{
    mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
}

void click_double(int x, int y) 
{
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    GetDoubleClickTime;
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}
#endif // __WXMSW__

#ifdef __WXGTK__
#include <X11/Xlib.h>
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

#ifdef __WXMAC__
#import <ApplicationServices/ApplicationServices.h>

void move_to(int x, int y) 
{
    CGPoint newloc;
    CGEventRef eventRef;
    newloc.x = x;
    newloc.y = y;

    eventRef = CGEventCreateMouseEvent(NULL, kCGEventMouseMoved, newloc, kCGMouseButtonCenter);

    //Apparently, a bug in xcode requires this next line
    CGEventSetType(eventRef, kCGEventMouseMoved); // Apparently, a bug in xcode requires this line
    CGEventPost(kCGSessionEventTap, eventRef);
    CFRelease(eventRef);
}

void click_left(int x, int y) 
{
    CGPoint newloc;
    CGEventRef eventRef;
    newloc.x = x;
    newloc.y = y;

    // Mouse down
    eventRef = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseDown, newloc, kCGMouseButtonLeft);
    CGEventSetType(eventRef, kCGEventLeftMouseDown); // Apparently, a bug in xcode requires this line
    CGEventPost(kCGSessionEventTap, eventRef);
    CFRelease(eventRef);

    usleep(100);

    // Mouse up
    eventRef = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseUp, newloc, kCGMouseButtonLeft);
    CGEventSetType(eventRef, kCGEventLeftMouseUp); // Apparently, a bug in xcode requires this line
    CGEventPost(kCGSessionEventTap, eventRef);
    CFRelease(eventRef);
}

void click_right(int x, int y) 
{
    CGPoint newloc;
    CGEventRef eventRef;
    newloc.x = x;
    newloc.y = y;

    // Mouse down
    eventRef = CGEventCreateMouseEvent(NULL, kCGEventRightMouseDown, newloc, kCGMouseButtonRight);
    CGEventSetType(eventRef, kCGEventRightMouseDown); // Apparently, a bug in xcode requires this line
    CGEventPost(kCGSessionEventTap, eventRef);
    CFRelease(eventRef);

    usleep(100);

    // Mouse up
    eventRef = CGEventCreateMouseEvent(NULL, kCGEventRightMouseUp, newloc, kCGMouseButtonRight);
    CGEventSetType(eventRef, kCGEventRightMouseUp); // Apparently, a bug in xcode requires this line
    CGEventPost(kCGSessionEventTap, eventRef);
    CFRelease(eventRef);
}

void click_double(int x, int y) 
{
    CGEventRef theEvent = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseDown, CGPointMake(x, y), kCGMouseButtonLeft);  
    CGEventPost(kCGHIDEventTap, theEvent);  
    CGEventSetType(theEvent, kCGEventLeftMouseUp);  
    CGEventPost(kCGHIDEventTap, theEvent);  

    CGEventSetIntegerValueField(theEvent, kCGMouseEventClickState, 2);

    CGEventSetType(theEvent, kCGEventLeftMouseDown);  
    CGEventPost(kCGHIDEventTap, theEvent);  

    CGEventSetType(theEvent, kCGEventLeftMouseUp); 
    CGEventPost(kCGHIDEventTap, theEvent); 

    CFRelease(theEvent); 
}
#endif //__WXMAC__


/*
 * Constructor for SuperMouserApp
 */

SuperMouserApp::SuperMouserApp()
{
    Init();
}


/*
 * Member initialisation
 */

void SuperMouserApp::Init()
{
////@begin SuperMouserApp member initialisation
////@end SuperMouserApp member initialisation

	timer_ = NULL;
	state_ = WaitForShortcut;
	screenWidth_ = 0;
	screenHeight_ = 0;

    #ifndef __WXGTK__
	wxDisplaySize(&screenWidth_, &screenHeight_);
    #else
    // TBD, find alternative for wxDisplaySize(), becuase it crashes the program.
    screenWidth_ = 1280;
    screenHeight_ = 1024;
    #endif

	mainWindow_ = NULL;
	windowUp_ = NULL;
	windowDown_ = NULL;
	windowLeft_ = NULL;
	windowRight_ = NULL;

	travelUpDown_ = 0;
	travelLeftRight_ = 0;
}

/*
 * Initialisation for SuperMouserApp
 */
#include <wx/utils.h>
bool SuperMouserApp::OnInit()
{    
////@begin SuperMouserApp initialisation
	// Remove the comment markers above and below this block
	// to make permanent changes to the code.

#if wxUSE_XPM
	wxImage::AddHandler(new wxXPMHandler);
#endif
#if wxUSE_LIBPNG
	wxImage::AddHandler(new wxPNGHandler);
#endif
#if wxUSE_LIBJPEG
	wxImage::AddHandler(new wxJPEGHandler);
#endif
#if wxUSE_GIF
	wxImage::AddHandler(new wxGIFHandler);
#endif
	AbstractWindow* mainWindow = new AbstractWindow( NULL );
	mainWindow->Show(true);
////@end SuperMouserApp initialisation

	mainWindow->Show(false);

	mainWindow_ = mainWindow;

	windowUp_ = new AbstractWindow(NULL);
	windowDown_ = new AbstractWindow(NULL);
	windowLeft_ = new AbstractWindow(NULL);
	windowRight_ = new AbstractWindow(NULL);

	static const int INTERVAL = 30; // milliseconds
	timer_ = new wxTimer(this, 1000);
	timer_->Start(INTERVAL);

    return true;
}


/*
 * Cleanup for SuperMouserApp
 */

int SuperMouserApp::OnExit()
{    
////@begin SuperMouserApp cleanup
	return wxApp::OnExit();
////@end SuperMouserApp cleanup
}

void SuperMouserApp::OnTimer(wxTimerEvent& event)
{
	timer_->Stop();
	
	switch (state_) {
		case WaitForShortcut:
			if (wxGetKeyState(WXK_CONTROL) && wxGetKeyState(WXK_SHIFT) && wxGetKeyState(wxKeyCode('M'))) {
				state_ = InMouserState;
				
				beginPos_ = wxGetMousePosition();
				currentPos_ = wxGetMousePosition();

				travelUpDown_ = -1;
				travelLeftRight_ = -1;

				mainWindow_->SetSize(5, 5);
				mainWindow_->SetPosition(wxPoint(currentPos_.x - 2, currentPos_.y - 2));
				mainWindow_->Show(true);
			}
			break;
		case InMouserState:
			mainWindow_->SetPosition(wxPoint(currentPos_.x - 2, currentPos_.y - 2));
			mainWindow_->Show();


			if (wxGetKeyState(WXK_ESCAPE)) {
				state_ = AbortMouserState;
				break;
			}

			if (wxGetKeyState(wxKeyCode('H'))) {
                #ifdef __WXGTK__
                windowLeft_->Hide();
                #endif
				windowLeft_->SetSize(currentPos_.x, 0, screenWidth_ - currentPos_.x, screenHeight_);
				windowLeft_->Show();

				if (travelLeftRight_ == -1) {
					travelLeftRight_ = currentPos_.x / 2.0;
				} else {
					travelLeftRight_ /= 2.0;
				}
				currentPos_.x -= travelLeftRight_;
				while (wxGetKeyState(wxKeyCode('H')));
			}
			if (wxGetKeyState(wxKeyCode('J'))) {
                #ifdef __WXGTK__
                windowDown_->Hide();
                #endif
				windowDown_->SetSize(0, 0, screenWidth_, currentPos_.y);
				windowDown_->Show();
				
				if (travelUpDown_ == -1) {
					travelUpDown_ = (screenHeight_ - currentPos_.y) / 2.0;
				} else {
					travelUpDown_ /= 2.0;
				}
				currentPos_.y += travelUpDown_;
				while (wxGetKeyState(wxKeyCode('J')));
			}
			if (wxGetKeyState(wxKeyCode('K'))) {
                #ifdef __WXGTK__
                windowUp_->Hide();
                #endif
				windowUp_->SetSize(0, currentPos_.y, screenWidth_, screenHeight_ - currentPos_.y);
				windowUp_->Show();

				if (travelUpDown_ == -1) {
					travelUpDown_ = (currentPos_.y) / 2.0;
				} else {
					travelUpDown_ /= 2.0;
				}
				currentPos_.y -= travelUpDown_;
				while (wxGetKeyState(wxKeyCode('K')));
			}
			if (wxGetKeyState(wxKeyCode('L'))) {
                #ifdef __WXGTK__
                windowRight_->Hide();
                #endif
				windowRight_->SetSize(0, 0, currentPos_.x, screenHeight_);
				windowRight_->Show();
				if (travelLeftRight_ == -1) {
					travelLeftRight_ = (screenWidth_ - currentPos_.x) / 2.0;
				} else {
					travelLeftRight_ /= 2.0;
				}
				currentPos_.x += travelLeftRight_;
				while (wxGetKeyState(wxKeyCode('L')));
			}
			if (wxGetKeyState(wxKeyCode('F'))) {
				state_ = MouseLeftClick;
			}
			if (wxGetKeyState(wxKeyCode('D'))) {
				state_ = MouseDoubleClick;
			}
			if (wxGetKeyState(wxKeyCode('G'))) {
				state_ = MouseRightClick;
			}
            move_to(currentPos_.x, currentPos_.y);
			break;
		case MouseLeftClick:
		case MouseRightClick:
		case MouseDoubleClick:
		case AbortMouserState:
			windowLeft_->Hide();
			windowRight_->Hide();
			windowUp_->Hide();
			windowDown_->Hide();
			mainWindow_->Hide();

			switch (state_) {
				case MouseLeftClick:
                    click_left(currentPos_.x, currentPos_.y);
					break;
				case MouseRightClick:
                    click_right(currentPos_.x, currentPos_.y);
					break;
				case MouseDoubleClick:
                    click_double(currentPos_.x, currentPos_.y);
					break;
			}
			state_ = WaitForShortcut;
 			break;
	}
	timer_->Start();
}
