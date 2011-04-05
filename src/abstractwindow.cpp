/////////////////////////////////////////////////////////////////////////////
// Name:        abstractwindow.cpp
// Purpose:     
// Author:      Ray Burgemeestre
// Modified by: 
// Created:     04/04/2011 19:32:52
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

#include "abstractwindow.h"

////@begin XPM images
////@end XPM images


/*
 * AbstractWindow type definition
 */

IMPLEMENT_CLASS( AbstractWindow, wxFrame )


/*
 * AbstractWindow event table definition
 */

BEGIN_EVENT_TABLE( AbstractWindow, wxFrame )

////@begin AbstractWindow event table entries
////@end AbstractWindow event table entries

END_EVENT_TABLE()


/*
 * AbstractWindow constructors
 */

AbstractWindow::AbstractWindow()
{
    Init();
}

AbstractWindow::AbstractWindow( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create( parent, id, caption, pos, size, style );
}


/*
 * AbstractWindow creator
 */

bool AbstractWindow::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin AbstractWindow creation
    wxFrame::Create( parent, id, caption, pos, size, style );

    this->SetBackgroundColour(wxColour(0, 64, 128));
    CreateControls();
    Centre();
////@end AbstractWindow creation
    return true;
}


/*
 * AbstractWindow destructor
 */

AbstractWindow::~AbstractWindow()
{
////@begin AbstractWindow destruction
////@end AbstractWindow destruction
}


/*
 * Member initialisation
 */

void AbstractWindow::Init()
{
////@begin AbstractWindow member initialisation
////@end AbstractWindow member initialisation
}


/*
 * Control creation for AbstractWindow
 */

void AbstractWindow::CreateControls()
{    
////@begin AbstractWindow content construction
    AbstractWindow* itemFrame1 = this;

////@end AbstractWindow content construction
}


/*
 * Should we show tooltips?
 */

bool AbstractWindow::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap AbstractWindow::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin AbstractWindow bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end AbstractWindow bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon AbstractWindow::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin AbstractWindow icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end AbstractWindow icon retrieval
}
