/////////////////////////////////////////////////////////////////////////////
// Name:        cursorwindow.h
// Purpose:     
// Author:      Ray Burgemeestre
// Modified by: 
// Created:     07/04/2011 20:49:45
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _CURSORWINDOW_H_
#define _CURSORWINDOW_H_

/*!
 * Includes
 */

////@begin includes
#include "wx/frame.h"
////@end includes


/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

class SuperMouserApp;

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_CURSORWINDOW 10012
#define ID_TEXTCTRL 10013
#define SYMBOL_CURSORWINDOW_STYLE wxFRAME_NO_TASKBAR|wxSTAY_ON_TOP|wxNO_BORDER
#define SYMBOL_CURSORWINDOW_TITLE _("CursorWindow")
#define SYMBOL_CURSORWINDOW_IDNAME ID_CURSORWINDOW
#define SYMBOL_CURSORWINDOW_SIZE wxSize(400, 300)
#define SYMBOL_CURSORWINDOW_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * CursorWindow class declaration
 */

class CursorWindow: public wxFrame
{    
    DECLARE_CLASS( CursorWindow )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    CursorWindow();
    CursorWindow( wxWindow* parent, wxWindowID id = SYMBOL_CURSORWINDOW_IDNAME, const wxString& caption = SYMBOL_CURSORWINDOW_TITLE, const wxPoint& pos = SYMBOL_CURSORWINDOW_POSITION, const wxSize& size = SYMBOL_CURSORWINDOW_SIZE, long style = SYMBOL_CURSORWINDOW_STYLE );

    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_CURSORWINDOW_IDNAME, const wxString& caption = SYMBOL_CURSORWINDOW_TITLE, const wxPoint& pos = SYMBOL_CURSORWINDOW_POSITION, const wxSize& size = SYMBOL_CURSORWINDOW_SIZE, long style = SYMBOL_CURSORWINDOW_STYLE );

    /// Destructor
    ~CursorWindow();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

	void SetApplication2(SuperMouserApp *app);
    
////@begin CursorWindow event handler declarations

    /// wxEVT_COMMAND_TEXT_UPDATED event handler for ID_TEXTCTRL
    void OnTextctrlTextUpdated( wxCommandEvent& event );

    /// wxEVT_CHAR event handler for ID_TEXTCTRL
    void OnChar( wxKeyEvent& event );

    /// wxEVT_KEY_DOWN event handler for ID_TEXTCTRL
    void OnKeyDown( wxKeyEvent& event );

////@end CursorWindow event handler declarations

////@begin CursorWindow member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end CursorWindow member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin CursorWindow member variables
    wxTextCtrl* textctrl;
////@end CursorWindow member variables

	SuperMouserApp *app_;
};

#endif
    // _CURSORWINDOW_H_
