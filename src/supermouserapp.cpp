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
#include "peripheral_api.h"
#include <wx/utils.h>

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

EVT_HOTKEY(wxID_ANY, SuperMouserApp::OnHotKey)

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
	AbstractWindow* mainWindow = new AbstractWindow( NULL );
	mainWindow->Show(true);
////@end SuperMouserApp initialisation

	mainWindow->Show(false);
	mainWindow_ = mainWindow;

	windowUp_ = new AbstractWindow(NULL);
	windowDown_ = new AbstractWindow(NULL);
	windowLeft_ = new AbstractWindow(NULL);
	windowRight_ = new AbstractWindow(NULL);

	windowUp_->SetTransparent(128);
    windowDown_->SetTransparent(128);
    windowLeft_->SetTransparent(128);
    windowRight_->SetTransparent(128);

    // Create timer and set the interval
    static const int INTERVAL = 30; // milliseconds
    timer_ = new wxTimer(this, wxID_ANY);
    timer_->Start(INTERVAL);
    timer_->Stop();

    register_hotkey(mainWindow_);
    
    return true;
}


/*
 * Cleanup for SuperMouserApp
 */

int SuperMouserApp::OnExit()
{    
    timer_->Stop();
    mainWindow_->Destroy();
    windowUp_->Destroy();
    windowDown_->Destroy();
    windowLeft_->Destroy();
    windowRight_->Destroy();

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

    mainWindow_->SetPosition(wxPoint(currentPos_.x - 2, currentPos_.y - 2));
    mainWindow_->SetSize(5, 5);
    mainWindow_->SetFocus();

    timer_->Start();
}

void SuperMouserApp::OnTimer(wxTimerEvent& event)
{
	switch (state_) {
		case InMouserState:
			mainWindow_->SetPosition(wxPoint(currentPos_.x - 2, currentPos_.y - 2));
			mainWindow_->Show();

			if (wxGetKeyState(WXK_ESCAPE)) {
				state_ = AbortMouserState;
				break;
			}

            if (wxGetKeyState(wxKeyCode('Q'))) {
                timer_->Stop();
                wxMessageBox("Exiting");
                Exit();
                return;
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
            timer_->Stop();
 			break;
	}
}
