/////////////////////////////////////////////////////////////////////////////
// Name:        settingswindow.h
// Purpose:     
// Author:      Ray Burgemeestre
// Modified by: 
// Created:     06/04/2011 23:30:49
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _SETTINGSWINDOW_H_
#define _SETTINGSWINDOW_H_


/*!
 * Includes
 */

////@begin includes
#include "wx/frame.h"
#include "wx/clrpicker.h"
#include "wx/statusbr.h"
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
class wxColourPickerCtrl;
class wxStatusBar;
////@end forward declarations
class SuperMouserApp;
class wxTaskBarIcon;
/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_SETTINGSWINDOW 10001
#define ID_PANEL 10002
#define ID_TEXTCTRL1 10004
#define ID_COLOURCTRL 10014
#define ID_CHECKBOX 10015
#define ID_SLIDER 10016
#define ID_TEXTCTRL 10005
#define ID_TEXTCTRL2 10006
#define ID_TEXTCTRL3 10007
#define ID_TEXTCTRL4 10008
#define ID_TEXTCTRL5 10009
#define ID_TEXTCTRL6 10000
#define ID_TEXTCTRL7 10010
#define ID_BUTTON_SAVE_SETTINGS 10011
#define ID_STATUSBAR 10003
#define SYMBOL_SETTINGSWINDOW_STYLE wxCAPTION|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_SETTINGSWINDOW_TITLE _("SettingsWindow")
#define SYMBOL_SETTINGSWINDOW_IDNAME ID_SETTINGSWINDOW
#define SYMBOL_SETTINGSWINDOW_SIZE wxSize(400, 500)
#define SYMBOL_SETTINGSWINDOW_POSITION wxDefaultPosition
////@end control identifiers

/*!
 * SettingsWindow class declaration
 */

class SettingsWindow : public wxFrame {
	DECLARE_CLASS(SettingsWindow)
	DECLARE_EVENT_TABLE()

public:
	/// Constructors
	SettingsWindow();
	SettingsWindow(wxWindow* parent, wxWindowID id = SYMBOL_SETTINGSWINDOW_IDNAME, const wxString& caption = SYMBOL_SETTINGSWINDOW_TITLE, const wxPoint& pos = SYMBOL_SETTINGSWINDOW_POSITION, const wxSize& size = SYMBOL_SETTINGSWINDOW_SIZE, long style = SYMBOL_SETTINGSWINDOW_STYLE);

	bool Create(wxWindow* parent, wxWindowID id = SYMBOL_SETTINGSWINDOW_IDNAME, const wxString& caption = SYMBOL_SETTINGSWINDOW_TITLE, const wxPoint& pos = SYMBOL_SETTINGSWINDOW_POSITION, const wxSize& size = SYMBOL_SETTINGSWINDOW_SIZE, long style = SYMBOL_SETTINGSWINDOW_STYLE);

	/// Destructor
	~SettingsWindow();

	/// Initialises member variables
	void Init();

	/// Creates the controls and sizers
	void CreateControls();

	void UpdateShortcutKeys();

	void SetApplication(SuperMouserApp *app);

	void RemoveTrayIcon();

	////@begin SettingsWindow event handler declarations

	/// wxEVT_CLOSE_WINDOW event handler for ID_SETTINGSWINDOW
	void OnCloseWindow(wxCloseEvent& event);

#if defined(__WXMSW__) || defined(__WXGTK__)
	/// wxEVT_KEY_DOWN event handler for ID_TEXTCTRL1
	void OnKeyDown(wxKeyEvent& event);

	/// wxEVT_KEY_UP event handler for ID_TEXTCTRL1
	void OnKeyUp(wxKeyEvent& event);

#endif
	/// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON_SAVE_SETTINGS
	void OnButtonSaveSettingsClick(wxCommandEvent& event);

	////@end SettingsWindow event handler declarations

	////@begin SettingsWindow member function declarations

	/// Retrieves bitmap resources
	wxBitmap GetBitmapResource(const wxString& name);

	/// Retrieves icon resources
	wxIcon GetIconResource(const wxString& name);
	////@end SettingsWindow member function declarations

	/// Should we show tooltips?
	static bool ShowToolTips();

	////@begin SettingsWindow member variables
#if defined(__WXMSW__) || defined(__WXGTK__)
	wxTextCtrl* textctrlControlKeys;
#endif
	wxColourPickerCtrl* colourctrl;
	wxCheckBox* checkboxTransparency;
	wxSlider* sliderTransparency;
	wxTextCtrl* textctrlKeyUp;
	wxTextCtrl* textctrlKeyLeft;
	wxTextCtrl* textctrlKeyRight;
	wxTextCtrl* textctrlKeyUndo;
	wxTextCtrl* textctrlKeyDown;
	wxTextCtrl* textctrlMouseLeftClick;
	wxTextCtrl* textctrlMouseDoubleClick;
	wxTextCtrl* textctrlMouseRight;
	wxButton* buttonSave;
	wxStatusBar* statusbar;
	////@end SettingsWindow member variables

	bool isDownControl;
	bool isDownAlt;
	bool isDownWindows;
	bool isDownShift;

	bool isShortcutDownControl;
	bool isShortcutDownAlt;
	bool isShortcutDownWindows;
	bool isShortcutDownShift;

	char keyNavUp;
	char keyNavDown;
	char keyNavLeft;
	char keyNavRight;
	char keyNavUndo;
	char keyMouseSingleClick;
	char keyMouseDoubleClick;
	char keyMouseRightClick;

	char shortcutKey;

	SuperMouserApp *app_;
	wxTaskBarIcon *taskbarIcon_;
};

#endif
// _SETTINGSWINDOW_H_
