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

#ifndef _SUPERMOUSERAPP_H_
#define _SUPERMOUSERAPP_H_


/*!
 * Includes
 */

////@begin includes
#include "wx/image.h"
#include "abstractwindow.h"
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
////@end control identifiers

enum State {
	WaitForShortcut,
	InMouserState,
	MouseLeftClick,
	MouseRightClick,
	MouseDoubleClick,
	AbortMouserState
};

/*!
 * SuperMouserApp class declaration
 */

class SuperMouserApp: public wxApp
{    
    DECLARE_CLASS( SuperMouserApp )
    DECLARE_EVENT_TABLE()

public:
    /// Constructor
    SuperMouserApp();

    void Init();

    /// Initialises the application
    virtual bool OnInit();

    /// Called on exit
    virtual int OnExit();

	//void OnKeyDown(wxKeyEvent& event);
	void OnTimer(wxTimerEvent& event);
    void OnHotKey(wxKeyEvent& event);

	void Activate();
    
////@begin SuperMouserApp event handler declarations

////@end SuperMouserApp event handler declarations

////@begin SuperMouserApp member function declarations

////@end SuperMouserApp member function declarations

////@begin SuperMouserApp member variables
////@end SuperMouserApp member variables

	wxTimer *timer_;
	State state_;
	wxPoint beginPos_;
	wxPoint currentPos_;
	int screenWidth_;
	int screenHeight_;

	int travelUpDown_;
	int travelLeftRight_;

	AbstractWindow* mainWindow_;
	AbstractWindow* windowUp_;
	AbstractWindow* windowDown_;
	AbstractWindow* windowLeft_;
	AbstractWindow* windowRight_;
};

/*!
 * Application instance declaration 
 */

////@begin declare app
DECLARE_APP(SuperMouserApp)
////@end declare app

#endif
    // _SUPERMOUSERAPP_H_
