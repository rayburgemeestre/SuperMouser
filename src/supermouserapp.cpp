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
#include <wx/display.h>
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

#if wxUSE_DISPLAY
    unsigned count = wxDisplay::GetCount();
    for (unsigned i=0; i<count; i++)
    {
        wxDisplay display(i);
        wxRect r = display.GetGeometry();
        /*wxMessageBox(wxString::Format(_T("Display #%u \"%s\" = ( %i, %i, %i, %i ) @ %i bits"),
            i, display.GetName().c_str(), r.GetLeft(), r.GetTop(), r.GetWidth(), r.GetHeight(),
            display.GetCurrentMode().GetDepth() ));*/
            
        // TBD, store known displays in vector.
        // TBD, keep reference to current display (determine using GetCursorPos)
        // TBD, create toggle key, i.e., 'm', get x,y on current screen, normalize, move to next screen
        // TBD, toggle updates screenWidth & -Height, some function simply adds the 
        //  top & left of the new screen onto the position of the windows & cursor.
    }
#endif

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
        windowSettings_->Show();
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

    click_left(currentPos_.x, currentPos_.y);
        
    ClearWindowStateHistory();
    PushWindowState();

	//mainWindow_->textctrl->SetFocus();
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

	if (code == wxKeyCode(windowSettings_->keyNavUndo)) {
        RestoreWindowState();
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

        PushWindowState();
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

        PushWindowState();
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

        PushWindowState();
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

        PushWindowState();
	}

	move_to(currentPos_.x, currentPos_.y);
#ifndef __WXMSW__
    mainWindow_->Show(false);
    mainWindow_->Show(true);
#endif
	mainWindow_->SetPosition(wxPoint(currentPos_.x + 2, currentPos_.y + 2));
	mainWindow_->SetFocus();

#ifdef __WXMAC__
	mainWindow_->textctrl->SetFocus();
#endif

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

void SuperMouserApp::PushWindowState()
{
    WindowState thisState;
    thisState.leftPos = windowLeft_->GetPosition();
    thisState.rightPos = windowRight_->GetPosition();
    thisState.upPos = windowUp_->GetPosition();
    thisState.downPos = windowDown_->GetPosition();

    thisState.leftSize = windowLeft_->GetSize();
    thisState.rightSize = windowRight_->GetSize();
    thisState.upSize = windowUp_->GetSize();
    thisState.downSize = windowDown_->GetSize();

    thisState.mousePosition = currentPos_;

    windowStateHistory.push(thisState);
}

void SuperMouserApp::RestoreWindowState()
{
    if (!windowStateHistory.empty()) {
        // First pop the current state, as we want to go back to the previous state
        windowStateHistory.pop();
    }

    if (!windowStateHistory.empty()) {
        WindowState previousState = windowStateHistory.top();

        windowLeft_->SetPosition(previousState.leftPos);
        windowRight_->SetPosition(previousState.rightPos);
        windowUp_->SetPosition(previousState.upPos);
        windowDown_->SetPosition(previousState.downPos);

        windowLeft_->SetSize(previousState.leftSize);
        windowRight_->SetSize(previousState.rightSize);
        windowUp_->SetSize(previousState.upSize);
        windowDown_->SetSize(previousState.downSize);

        currentPos_.x = previousState.mousePosition.x;
        currentPos_.y = previousState.mousePosition.y;
        move_to(currentPos_.x, currentPos_.y);
    } else {
        //printf("Cannot undo.. stack empty\n");
    }
}

void SuperMouserApp::ClearWindowStateHistory()
{
    while(!windowStateHistory.empty()) {
        windowStateHistory.pop();
    }
}
