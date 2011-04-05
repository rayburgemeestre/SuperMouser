/////////////////////////////////////////////////////////////////////////////
// Name:        trackballerapp.cpp
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

#include "trackballerapp.h"

////@begin XPM images
////@end XPM images


/*
 * Application instance implementation
 */

////@begin implement app
IMPLEMENT_APP( TrackballerApp )
////@end implement app


/*
 * TrackballerApp type definition
 */

IMPLEMENT_CLASS( TrackballerApp, wxApp )


/*
 * TrackballerApp event table definition
 */

BEGIN_EVENT_TABLE( TrackballerApp, wxApp )

////@begin TrackballerApp event table entries
////@end TrackballerApp event table entries

EVT_TIMER(1000, TrackballerApp::OnTimer)

END_EVENT_TABLE()


/*
 * Constructor for TrackballerApp
 */

TrackballerApp::TrackballerApp()
{
    Init();
}


/*
 * Member initialisation
 */

void TrackballerApp::Init()
{
////@begin TrackballerApp member initialisation
////@end TrackballerApp member initialisation

	timer_ = NULL;
	state_ = WaitForShortcut;
	screenWidth_ = 0;
	screenHeight_ = 0;

	wxDisplaySize(&screenWidth_, &screenHeight_);

	mainWindow_ = NULL;
	windowUp_ = NULL;
	windowDown_ = NULL;
	windowLeft_ = NULL;
	windowRight_ = NULL;

	travelUpDown_ = 0;
	travelLeftRight_ = 0;
}

/*
 * Initialisation for TrackballerApp
 */
#include <wx/utils.h>
bool TrackballerApp::OnInit()
{    
////@begin TrackballerApp initialisation
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
////@end TrackballerApp initialisation

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
 * Cleanup for TrackballerApp
 */

int TrackballerApp::OnExit()
{    
////@begin TrackballerApp cleanup
	return wxApp::OnExit();
////@end TrackballerApp cleanup
}

void TrackballerApp::OnTimer(wxTimerEvent& event)
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
			SetCursorPos(currentPos_.x, currentPos_.y);
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
					mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
					mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
					break;
				case MouseRightClick:
					mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
					mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
					break;
				case MouseDoubleClick:
					mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
					mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
					GetDoubleClickTime;
					mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
					mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
					break;
			}
			state_ = WaitForShortcut;
 			break;
	}
	timer_->Start();
}
