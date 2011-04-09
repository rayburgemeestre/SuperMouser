/////////////////////////////////////////////////////////////////////////////
// Name:        cursorwindow.cpp
// Purpose:     
// Author:      Ray Burgemeestre
// Modified by: 
// Created:     07/04/2011 20:49:45
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

#include "cursorwindow.h"
#include "supermouserapp.h"

////@begin XPM images
////@end XPM images


/*
 * CursorWindow type definition
 */

IMPLEMENT_CLASS( CursorWindow, wxFrame )


/*
 * CursorWindow event table definition
 */

BEGIN_EVENT_TABLE( CursorWindow, wxFrame )

////@begin CursorWindow event table entries
    EVT_TEXT( ID_TEXTCTRL, CursorWindow::OnTextctrlTextUpdated )

////@end CursorWindow event table entries

END_EVENT_TABLE()


/*
 * CursorWindow constructors
 */

CursorWindow::CursorWindow()
{
    Init();
}

CursorWindow::CursorWindow( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create( parent, id, caption, pos, size, style );
}


/*
 * CursorWindow creator
 */

bool CursorWindow::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin CursorWindow creation
    wxFrame::Create( parent, id, caption, pos, size, style );

    this->SetBackgroundColour(wxColour(255, 0, 0));
    CreateControls();
    Centre();
////@end CursorWindow creation
    return true;
}


/*
 * CursorWindow destructor
 */

CursorWindow::~CursorWindow()
{
////@begin CursorWindow destruction
////@end CursorWindow destruction
}


/*
 * Member initialisation
 */

void CursorWindow::Init()
{
////@begin CursorWindow member initialisation
    textctrl = NULL;
////@end CursorWindow member initialisation

	app_ = NULL;
}


/*
 * Control creation for CursorWindow
 */

void CursorWindow::CreateControls()
{    
////@begin CursorWindow content construction
    CursorWindow* itemFrame1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    itemFrame1->SetSizer(itemBoxSizer2);

    textctrl = new wxTextCtrl( itemFrame1, ID_TEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer2->Add(textctrl, 1, wxALIGN_TOP|wxALL, 5);

    // Connect events and objects
    textctrl->Connect(ID_TEXTCTRL, wxEVT_CHAR, wxKeyEventHandler(CursorWindow::OnChar), NULL, this);
    textctrl->Connect(ID_TEXTCTRL, wxEVT_KEY_DOWN, wxKeyEventHandler(CursorWindow::OnKeyDown), NULL, this);
////@end CursorWindow content construction
}


/*
 * Should we show tooltips?
 */

bool CursorWindow::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap CursorWindow::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin CursorWindow bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end CursorWindow bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon CursorWindow::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin CursorWindow icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end CursorWindow icon retrieval
}


/*
 * wxEVT_COMMAND_TEXT_UPDATED event handler for ID_TEXTCTRL
 */

void CursorWindow::OnTextctrlTextUpdated( wxCommandEvent& event )
{
	//textctrl->SetValue("");
	event.Skip();
}


/*
 * wxEVT_KEY_DOWN event handler for ID_TEXTCTRL
 */

void CursorWindow::OnKeyDown( wxKeyEvent& event )
{
	wxString value(wxString::Format("%d,", event.GetKeyCode()));
	value.Append(textctrl->GetValue());
	textctrl->SetValue(value);
	app_->Test(event.GetKeyCode());
}

void CursorWindow::SetApplication(SuperMouserApp *app)
{
    app_ = app;
}


/*
 * wxEVT_CHAR event handler for ID_TEXTCTRL
 */

void CursorWindow::OnChar( wxKeyEvent& event )
{
    ///app_->Test(event.GetKeyCode());
}

