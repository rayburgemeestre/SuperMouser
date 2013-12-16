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
#include "cursorwindow.h"
////@end includes
#include "abstractwindow.h"
#include <stack>
using std::stack;
#include <vector>
using std::vector;

// Interfaces
#include "hotkeyhandler.h"

/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

class SettingsWindow;

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

struct WindowState {
	wxPoint leftPos;
	wxPoint rightPos;
	wxPoint upPos;
	wxPoint downPos;

	wxSize leftSize;
	wxSize rightSize;
	wxSize upSize;
	wxSize downSize;

	wxPoint mousePosition;

	int travelUpDown;
	int travelLeftRight;
};

struct Display {
	wxPoint topLeft;
	wxPoint bottomRight;

	int width;
	int height;
};

/*!
 * Application instance declaration 
 */

////@begin declare app
DECLARE_APP(SuperMouserApp)
////@end declare app


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
	void OnHotKey(wxKeyEvent& event);

	void HandleHotkey();

	void Activate();

	void SettingsCallback(int modifiers, char shortcutKey);

	void Test(int code);

	void pre_click();

	void PushWindowState();
	void RestoreWindowState();
	void ClearWindowStateHistory();

	void InitDisplay();
	void SetCurrentDisplay(bool ignoreCursor = false);
	void ToggleDisplay();

////@begin SuperMouserApp event handler declarations

////@end SuperMouserApp event handler declarations

////@begin SuperMouserApp member function declarations

////@end SuperMouserApp member function declarations

////@begin SuperMouserApp member variables
////@end SuperMouserApp member variables



	stack<WindowState> windowStateHistory;
	vector<Display> monitors;
	int currentMonitorIdx;
	bool toggleDisplay;

	State state_;
	wxPoint beginPos_;
	wxPoint currentPos_;
	int screenWidth_;
	int screenHeight_;

	int travelUpDown_;
	int travelLeftRight_;

	CursorWindow* mainWindow_;
	AbstractWindow* windowUp_;
	AbstractWindow* windowDown_;
	AbstractWindow* windowLeft_;
	AbstractWindow* windowRight_;

	SettingsWindow * windowSettings_;
};

#endif
// _SUPERMOUSERAPP_H_
