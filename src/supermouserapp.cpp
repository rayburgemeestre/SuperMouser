#define COMPILE_MULTIMON_STUBS
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

#include <wx/utils.h>
#include "supermouserapp.h"
#include "peripheral_api.h"
#include "settingswindow.h"

////@begin XPM images
////@end XPM images


/*
 * Application instance implementation
 */

////@begin implement app
IMPLEMENT_APP( SuperMouserApp )
////@end implement app

/*
 * SuperMouserApp event table definition
 */

BEGIN_EVENT_TABLE( SuperMouserApp, wxApp )

////@begin SuperMouserApp event table entries
////@end SuperMouserApp event table entries

EVT_TIMER(wxID_ANY, SuperMouserApp::OnTimer)

#ifdef __WXMSW__
EVT_HOTKEY(wxID_ANY, SuperMouserApp::OnHotKey)
#endif

END_EVENT_TABLE()


/*
 * SuperMouserApp type definition
 */

IMPLEMENT_CLASS( SuperMouserApp, wxApp )


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
#include <algorithm>
using std::min;
using std::max;

#include <windows.h>
#include "multimon.h"

BOOL CALLBACK MyMonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
{
	MONITORINFO monitorInfo;
	if (GetMonitorInfo(
		hMonitor,
		&monitorInfo)) 
	{
		wxMessageBox("test");
		monitorInfo;
	}
	return true;
}

void SuperMouserApp::Init()
{
////@begin SuperMouserApp member initialisation
////@end SuperMouserApp member initialisation

    timer_ = NULL;
	state_ = WaitForShortcut;
	screenWidth_ = 0;
	screenHeight_ = 0;

    init_screensize(&screenWidth_, &screenHeight_);

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
	CursorWindow* mainWindow = new CursorWindow( NULL );
	mainWindow->Show(true);
////@end SuperMouserApp initialisation

	mainWindow->Show(false);
	mainWindow->SetApplication(this);
	mainWindow_ = mainWindow;


	EnumDisplayMonitors(NULL, NULL, MyMonitorEnumProc, 0);


	windowUp_ = new AbstractWindow(NULL);
	windowDown_ = new AbstractWindow(NULL);
	windowLeft_ = new AbstractWindow(NULL);
	windowRight_ = new AbstractWindow(NULL);

	windowUp_->SetTransparent(128);
    windowDown_->SetTransparent(128);
    windowLeft_->SetTransparent(128);
    windowRight_->SetTransparent(128);

	/*
    // Create timer and set the interval
    static const int INTERVAL = 30; // milliseconds
    timer_ = new wxTimer(this, wxID_ANY);
    timer_->Start(INTERVAL);
    timer_->Stop();
	*/

	windowSettings_ = new SettingsWindow(NULL);
	windowSettings_->SetApplication(this);

	#ifdef __WXMSW__
		windowSettings_->Show();
	#else
		register_hotkey(mainWindow_, this);
	#endif
    
    return true;
}


/*
 * Cleanup for SuperMouserApp
 */

int SuperMouserApp::OnExit()
{    
//    timer_->Stop();
    mainWindow_->Destroy();
    windowUp_->Destroy();
    windowDown_->Destroy();
    windowLeft_->Destroy();
    windowRight_->Destroy();

	windowSettings_->RemoveTrayIcon();
	windowSettings_->Destroy();

////@begin SuperMouserApp cleanup
	return wxApp::OnExit();
////@end SuperMouserApp cleanup
}

void SuperMouserApp::OnHotKey(wxKeyEvent& event)
{
    Activate();
}

void SuperMouserApp::Activate()
{
    state_ = InMouserState;

    beginPos_ = wxGetMousePosition();
    currentPos_ = wxGetMousePosition();

    travelUpDown_ = -1;
    travelLeftRight_ = -1;

	windowLeft_->SetPosition(wxPoint(currentPos_.x - 10, currentPos_.y - 5));
	windowLeft_->SetSize(3, 10);
	windowLeft_->Show();
	windowRight_->SetPosition(wxPoint(currentPos_.x + 7, currentPos_.y - 5));
	windowRight_->SetSize(3, 10);
	windowRight_->Show();
	windowUp_->SetPosition(wxPoint(currentPos_.x - 5, currentPos_.y - 10));
	windowUp_->SetSize(10, 3);
	windowUp_->Show();
	windowDown_->SetPosition(wxPoint(currentPos_.x - 5, currentPos_.y + 8));
	windowDown_->SetSize(10, 3);
	windowDown_->Show();

	mainWindow_->SetPosition(wxPoint(currentPos_.x - 2, currentPos_.y - 2));
	mainWindow_->SetSize(5, 5);
	mainWindow_->Show();
	mainWindow_->SetFocus();
	mainWindow_->textctrl->SetFocus();

}

void SuperMouserApp::pre_click()
{
	mainWindow_->Hide();
	windowLeft_->Hide();
	windowRight_->Hide();
	windowUp_->Hide();
	windowDown_->Hide();
}
void SuperMouserApp::Test(int code)
{
	if (code == wxKeyCode('M')) {
		mainWindow_->GetHandle();
	}

	if (code == wxKeyCode(windowSettings_->keyNavLeft)) {
#ifdef __WXGTK__
		windowLeft_->Hide();
#endif
		windowLeft_->SetSize(screenWidth_ - currentPos_.x, screenHeight_);
		windowLeft_->SetPosition(wxPoint(currentPos_.x, 0));
		windowLeft_->Show();

		if (travelLeftRight_ == -1) {
			travelLeftRight_ = currentPos_.x / 2.0;
		} else {
			travelLeftRight_ /= 2.0;
		}
		currentPos_.x -= travelLeftRight_;
		while (wxGetKeyState(wxKeyCode(windowSettings_->keyNavLeft)));
	}
	if (code == wxKeyCode(windowSettings_->keyNavDown)) {
#ifdef __WXGTK__
		windowDown_->Hide();
#endif
		windowDown_->SetSize(screenWidth_, currentPos_.y);
		windowDown_->SetPosition(wxPoint(0, 0));
		windowDown_->Show();

		if (travelUpDown_ == -1) {
			travelUpDown_ = (screenHeight_ - currentPos_.y) / 2.0;
		} else {
			travelUpDown_ /= 2.0;
		}
		currentPos_.y += travelUpDown_;
		while (wxGetKeyState(wxKeyCode(windowSettings_->keyNavDown)));
	}
	if (code == wxKeyCode(windowSettings_->keyNavUp)) {
#ifdef __WXGTK__
		windowUp_->Hide();
#endif
		windowUp_->SetSize(screenWidth_, screenHeight_ - currentPos_.y);
		windowUp_->SetPosition(wxPoint(0, currentPos_.y));
		windowUp_->Show();

		if (travelUpDown_ == -1) {
			travelUpDown_ = (currentPos_.y) / 2.0;
		} else {
			travelUpDown_ /= 2.0;
		}
		currentPos_.y -= travelUpDown_;
		while (wxGetKeyState(wxKeyCode(windowSettings_->keyNavUp)));
	}
	if (code == wxKeyCode(windowSettings_->keyNavRight)) {
#ifdef __WXGTK__
		windowRight_->Hide();
#endif
		windowRight_->SetSize(0, 0, currentPos_.x, screenHeight_);
		windowRight_->SetPosition(wxPoint(0, 0));
		windowRight_->Show();
		if (travelLeftRight_ == -1) {
			travelLeftRight_ = (screenWidth_ - currentPos_.x) / 2.0;
		} else {
			travelLeftRight_ /= 2.0;
		}
		currentPos_.x += travelLeftRight_;
		while (wxGetKeyState(wxKeyCode(windowSettings_->keyNavRight)));
	}

	move_to(currentPos_.x, currentPos_.y);
    #ifndef __WXMSW__
    mainWindow_->Show(false);
    mainWindow_->Show(true);
    #endif
	mainWindow_->SetPosition(wxPoint(currentPos_.x + 2, currentPos_.y + 2));
	mainWindow_->SetSize(wxSize(1, 1));
	mainWindow_->SetFocus();
	mainWindow_->textctrl->SetFocus();

	if (code == 27 /* ESC */) {
		pre_click();
	}

	if (code == wxKeyCode('C')) {
		windowSettings_->Show();
	}

	if (code == wxKeyCode('Q')) {
		wxMessageBox("Exiting");
		Exit();
		return;
	}

	if (code == wxKeyCode(windowSettings_->keyMouseSingleClick)) {
		pre_click();
		click_left(currentPos_.x, currentPos_.y);
	}
	else if (code == wxKeyCode(windowSettings_->keyMouseRightClick)) {
		pre_click();
		click_right(currentPos_.x, currentPos_.y);
	}
	else if (code == wxKeyCode(windowSettings_->keyMouseDoubleClick)) {
		pre_click();
		click_double(currentPos_.x, currentPos_.y);
	}
}

void SuperMouserApp::OnTimer(wxTimerEvent& event)
{
	switch (state_) {
		case InMouserState:
			//Test();
			break;
		case MouseLeftClick:
		case MouseRightClick:
		case MouseDoubleClick:
		case AbortMouserState:

 			break;
	}
}

void SuperMouserApp::SettingsCallback(int modifiers, char shortcutKey)
{
#ifdef __WXMSW__
	mainWindow_->UnregisterHotKey(wxID_ANY);
	mainWindow_->RegisterHotKey(wxID_ANY, modifiers, shortcutKey);
#endif

	const wxColor &color = windowSettings_->colourctrl->GetColour();
	windowLeft_->SetBackgroundColour(color);
	windowRight_->SetBackgroundColour(color);
	windowUp_->SetBackgroundColour(color);
	windowDown_->SetBackgroundColour(color);
	
	wxByte trans(windowSettings_->sliderTransparency->GetValue());
	if (!windowSettings_->checkboxTransparency->GetValue())
		trans = 255;

	windowUp_->SetTransparent(trans);
	windowDown_->SetTransparent(trans);
	windowLeft_->SetTransparent(trans);
	windowRight_->SetTransparent(trans);
}


/*

#include <algorithm>
using std::min;
using std::max;

#include <windows.h>
#include "multimon.h"    

#define MONITOR_CENTER     0x0001        // center rect to monitor 
#define MONITOR_CLIP     0x0000        // clip rect to monitor 
#define MONITOR_WORKAREA 0x0002        // use monitor work area 
#define MONITOR_AREA     0x0000        // use monitor entire area 

// 
//  ClipOrCenterRectToMonitor 
// 
//  The most common problem apps have when running on a 
//  multimonitor system is that they "clip" or "pin" windows 
//  based on the SM_CXSCREEN and SM_CYSCREEN system metrics. 
//  Because of app compatibility reasons these system metrics 
//  return the size of the primary monitor. 
// 
//  This shows how you use the multi-monitor functions 
//  to do the same thing. 
// 
void ClipOrCenterRectToMonitor(LPRECT prc, UINT flags)
{
	HMONITOR hMonitor;
	MONITORINFO mi;
	RECT        rc;
	int         w = prc->right  - prc->left;
	int         h = prc->bottom - prc->top;

	// 
	// get the nearest monitor to the passed rect. 
	// 
	hMonitor = MonitorFromRect(prc, MONITOR_DEFAULTTONEAREST);

	// 
	// get the work area or entire monitor rect. 
	// 
	mi.cbSize = sizeof(mi);
	GetMonitorInfo(hMonitor, &mi);

	if (flags & MONITOR_WORKAREA)
		rc = mi.rcWork;
	else
		rc = mi.rcMonitor;

	// 
	// center or clip the passed rect to the monitor rect 
	// 
	if (flags & MONITOR_CENTER)
	{
		prc->left   = rc.left + (rc.right  - rc.left - w) / 2;
		prc->top    = rc.top  + (rc.bottom - rc.top  - h) / 2;
		prc->right  = prc->left + w;
		prc->bottom = prc->top  + h;
	}
	else
	{
		prc->left   = max(rc.left, min(rc.right-w,  prc->left));
		prc->top    = max(rc.top,  min(rc.bottom-h, prc->top));
		prc->right  = prc->left + w;
		prc->bottom = prc->top  + h;
	}
}

void ClipOrCenterWindowToMonitor(HWND hwnd, UINT flags)
{
	RECT rc;
	GetWindowRect(hwnd, &rc);
	ClipOrCenterRectToMonitor(&rc, flags);
	SetWindowPos(hwnd, NULL, rc.left, rc.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
}
*/