/////////////////////////////////////////////////////////////////////////////
// Name:        abstractwindow.h
// Purpose:     
// Author:      Ray Burgemeestre
// Modified by: 
// Created:     04/04/2011 19:32:52
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _ABSTRACTWINDOW_H_
#define _ABSTRACTWINDOW_H_


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

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_ABSTRACTWINDOW 10000
#define SYMBOL_ABSTRACTWINDOW_STYLE wxFRAME_NO_TASKBAR|wxSTAY_ON_TOP|wxNO_BORDER|wxWANTS_CHARS
#define SYMBOL_ABSTRACTWINDOW_TITLE _("AbstractWindow")
#define SYMBOL_ABSTRACTWINDOW_IDNAME ID_ABSTRACTWINDOW
#define SYMBOL_ABSTRACTWINDOW_SIZE wxSize(400, 300)
#define SYMBOL_ABSTRACTWINDOW_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * AbstractWindow class declaration
 */

class AbstractWindow: public wxFrame
{    
    DECLARE_CLASS( AbstractWindow )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    AbstractWindow();
    AbstractWindow( wxWindow* parent, wxWindowID id = SYMBOL_ABSTRACTWINDOW_IDNAME, const wxString& caption = SYMBOL_ABSTRACTWINDOW_TITLE, const wxPoint& pos = SYMBOL_ABSTRACTWINDOW_POSITION, const wxSize& size = SYMBOL_ABSTRACTWINDOW_SIZE, long style = SYMBOL_ABSTRACTWINDOW_STYLE );

    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_ABSTRACTWINDOW_IDNAME, const wxString& caption = SYMBOL_ABSTRACTWINDOW_TITLE, const wxPoint& pos = SYMBOL_ABSTRACTWINDOW_POSITION, const wxSize& size = SYMBOL_ABSTRACTWINDOW_SIZE, long style = SYMBOL_ABSTRACTWINDOW_STYLE );

    /// Destructor
    ~AbstractWindow();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin AbstractWindow event handler declarations

////@end AbstractWindow event handler declarations

////@begin AbstractWindow member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end AbstractWindow member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin AbstractWindow member variables
////@end AbstractWindow member variables
};

#endif
    // _ABSTRACTWINDOW_H_
