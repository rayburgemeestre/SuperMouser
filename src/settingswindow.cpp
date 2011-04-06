/////////////////////////////////////////////////////////////////////////////
// Name:        settingswindow.cpp
// Purpose:     
// Author:      Ray Burgemeestre
// Modified by: 
// Created:     06/04/2011 23:30:49
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

#include "settingswindow.h"
#include "abstractwindow.h"
#include <string>
using std::string;

////@begin XPM images
////@end XPM images


/*
 * SettingsWindow type definition
 */

IMPLEMENT_CLASS( SettingsWindow, wxFrame )


/*
 * SettingsWindow event table definition
 */

BEGIN_EVENT_TABLE( SettingsWindow, wxFrame )

////@begin SettingsWindow event table entries
    EVT_BUTTON( ID_BUTTON_SAVE_SETTINGS, SettingsWindow::OnButtonSaveSettingsClick )

////@end SettingsWindow event table entries

END_EVENT_TABLE()


/*
 * SettingsWindow constructors
 */

SettingsWindow::SettingsWindow()
{
    Init();
}

SettingsWindow::SettingsWindow( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create( parent, id, caption, pos, size, style );
}


/*
 * SettingsWindow creator
 */

bool SettingsWindow::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin SettingsWindow creation
    wxFrame::Create( parent, id, caption, pos, size, style );

    CreateControls();
    Centre();
////@end SettingsWindow creation
    return true;
}


/*
 * SettingsWindow destructor
 */

SettingsWindow::~SettingsWindow()
{
////@begin SettingsWindow destruction
////@end SettingsWindow destruction
}


/*
 * Member initialisation
 */

void SettingsWindow::Init()
{
////@begin SettingsWindow member initialisation
    textctrlControlKeys = NULL;
    textctrlKeyUp = NULL;
    textctrlKeyLeft = NULL;
    textctrlKeyRight = NULL;
    textctrlKeyDown = NULL;
    textctrlMouseLeftClick = NULL;
    textctrlMouseDoubleClick = NULL;
    textctrlMouseRight = NULL;
    statusbar = NULL;
////@end SettingsWindow member initialisation
	isDownControl = false;
	isDownAlt = false;
	isDownWindows = false;
	isDownShift = false;

	isShortcutDownControl = true;
	isShortcutDownAlt = false;
	isShortcutDownWindows = false;
	isShortcutDownShift = true;
	shortcutKey = 'M';

	keyNavUp = 'k';
	keyNavDown = 'j';
	keyNavLeft = 'h';
	keyNavRight = 'l';
	keyMouseSingleClick = 'f';
	keyMouseDoubleClick = 'd';
	keyMouseRightClick = 'g';
}


/*
 * Control creation for SettingsWindow
 */

void SettingsWindow::CreateControls()
{    
////@begin SettingsWindow content construction
    SettingsWindow* itemFrame1 = this;

    wxPanel* itemPanel2 = new wxPanel( itemFrame1, ID_PANEL, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxTAB_TRAVERSAL );

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxVERTICAL);
    itemPanel2->SetSizer(itemBoxSizer3);

    wxStaticBox* itemStaticBoxSizer4Static = new wxStaticBox(itemPanel2, wxID_ANY, _("Keyboard"));
    wxStaticBoxSizer* itemStaticBoxSizer4 = new wxStaticBoxSizer(itemStaticBoxSizer4Static, wxVERTICAL);
    itemBoxSizer3->Add(itemStaticBoxSizer4, 0, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    itemStaticBoxSizer4->Add(itemBoxSizer5, 0, wxGROW|wxALL, 5);

    wxStaticText* itemStaticText6 = new wxStaticText( itemPanel2, wxID_STATIC, _("Activate mouser:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer5->Add(itemStaticText6, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    textctrlControlKeys = new wxTextCtrl( itemPanel2, ID_TEXTCTRL1, _("Ctrl+Shift+M"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer5->Add(textctrlControlKeys, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
    itemStaticBoxSizer4->Add(itemBoxSizer8, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    textctrlKeyUp = new wxTextCtrl( itemPanel2, ID_TEXTCTRL, _("k"), wxDefaultPosition, wxDefaultSize, 0 );
    textctrlKeyUp->SetMaxLength(1);
    itemBoxSizer8->Add(textctrlKeyUp, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer10 = new wxBoxSizer(wxHORIZONTAL);
    itemStaticBoxSizer4->Add(itemBoxSizer10, 0, wxALIGN_CENTER_HORIZONTAL|wxLEFT|wxRIGHT, 5);

    textctrlKeyLeft = new wxTextCtrl( itemPanel2, ID_TEXTCTRL2, _("h"), wxDefaultPosition, wxDefaultSize, 0 );
    textctrlKeyLeft->SetMaxLength(1);
    itemBoxSizer10->Add(textctrlKeyLeft, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText12 = new wxStaticText( itemPanel2, wxID_STATIC, _("Navigation keys"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer10->Add(itemStaticText12, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    textctrlKeyRight = new wxTextCtrl( itemPanel2, ID_TEXTCTRL3, _("l"), wxDefaultPosition, wxDefaultSize, 0 );
    textctrlKeyRight->SetMaxLength(1);
    itemBoxSizer10->Add(textctrlKeyRight, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer14 = new wxBoxSizer(wxHORIZONTAL);
    itemStaticBoxSizer4->Add(itemBoxSizer14, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    textctrlKeyDown = new wxTextCtrl( itemPanel2, ID_TEXTCTRL4, _("j"), wxDefaultPosition, wxDefaultSize, 0 );
    textctrlKeyDown->SetMaxLength(1);
    itemBoxSizer14->Add(textctrlKeyDown, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer16 = new wxBoxSizer(wxHORIZONTAL);
    itemStaticBoxSizer4->Add(itemBoxSizer16, 0, wxGROW|wxLEFT|wxRIGHT, 5);

    wxStaticText* itemStaticText17 = new wxStaticText( itemPanel2, wxID_STATIC, _("Mouse left click:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer16->Add(itemStaticText17, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    textctrlMouseLeftClick = new wxTextCtrl( itemPanel2, ID_TEXTCTRL5, _("f"), wxDefaultPosition, wxDefaultSize, 0 );
    textctrlMouseLeftClick->SetMaxLength(1);
    itemBoxSizer16->Add(textctrlMouseLeftClick, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer19 = new wxBoxSizer(wxHORIZONTAL);
    itemStaticBoxSizer4->Add(itemBoxSizer19, 0, wxGROW|wxLEFT|wxRIGHT, 5);

    wxStaticText* itemStaticText20 = new wxStaticText( itemPanel2, wxID_STATIC, _("Mouse double click:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer19->Add(itemStaticText20, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    textctrlMouseDoubleClick = new wxTextCtrl( itemPanel2, ID_TEXTCTRL6, _("d"), wxDefaultPosition, wxDefaultSize, 0 );
    textctrlMouseDoubleClick->SetMaxLength(1);
    itemBoxSizer19->Add(textctrlMouseDoubleClick, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer22 = new wxBoxSizer(wxHORIZONTAL);
    itemStaticBoxSizer4->Add(itemBoxSizer22, 0, wxGROW|wxLEFT|wxRIGHT, 5);

    wxStaticText* itemStaticText23 = new wxStaticText( itemPanel2, wxID_STATIC, _("Mouse right click:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer22->Add(itemStaticText23, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    textctrlMouseRight = new wxTextCtrl( itemPanel2, ID_TEXTCTRL7, _("g"), wxDefaultPosition, wxDefaultSize, 0 );
    textctrlMouseRight->SetMaxLength(1);
    itemBoxSizer22->Add(textctrlMouseRight, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* itemButton25 = new wxButton( itemPanel2, ID_BUTTON_SAVE_SETTINGS, _("Save settings"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticBoxSizer4->Add(itemButton25, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    statusbar = new wxStatusBar( itemFrame1, ID_STATUSBAR, wxST_SIZEGRIP|wxNO_BORDER );
    statusbar->SetFieldsCount(2);
    itemFrame1->SetStatusBar(statusbar);

    // Connect events and objects
    textctrlControlKeys->Connect(ID_TEXTCTRL1, wxEVT_KEY_DOWN, wxKeyEventHandler(SettingsWindow::OnKeyDown), NULL, this);
    textctrlControlKeys->Connect(ID_TEXTCTRL1, wxEVT_KEY_UP, wxKeyEventHandler(SettingsWindow::OnKeyUp), NULL, this);
////@end SettingsWindow content construction
}


/*
 * Should we show tooltips?
 */

bool SettingsWindow::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap SettingsWindow::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin SettingsWindow bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end SettingsWindow bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon SettingsWindow::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin SettingsWindow icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end SettingsWindow icon retrieval
}


/*
 * wxEVT_KEY_DOWN event handler for ID_TEXTCTRL1
 */

enum SpecialKeyCodes
{
	Control = 308,
	Alt = 307,
	Windows = 393,
	Shift = 306
};

void SettingsWindow::OnKeyDown( wxKeyEvent& event )
{
    int keyCode = event.GetKeyCode();
	switch (keyCode) {
		case SpecialKeyCodes(Control):
			isDownControl = true;
			break;
		case SpecialKeyCodes(Alt):
			isDownAlt = true;
			break;
		case SpecialKeyCodes(Windows):
			isDownWindows = true;
			break;
		case SpecialKeyCodes(Shift):
			isDownShift = true;
			break;
		default:
			if (keyCode < 255) {
				shortcutKey = static_cast<char>(keyCode);
				isShortcutDownAlt = isDownAlt;
				isShortcutDownControl = isDownControl;
				isShortcutDownShift = isDownShift;
				isShortcutDownWindows = isDownWindows;
			}
			break;
	}
	UpdateShortcutKeys();
}


/*
 * wxEVT_KEY_UP event handler for ID_TEXTCTRL1
 */

void SettingsWindow::OnKeyUp( wxKeyEvent& event )
{
	int keyCode = event.GetKeyCode();
	switch (keyCode) {
	case SpecialKeyCodes(Control):
		isDownControl = false;
		break;
	case SpecialKeyCodes(Alt):
		isDownAlt = false;
		break;
	case SpecialKeyCodes(Windows):
		isDownWindows = false;
		break;
	case SpecialKeyCodes(Shift):
		isDownShift = false;
		break;
	default:
		break;
	}
	UpdateShortcutKeys();
}

void SettingsWindow::UpdateShortcutKeys()
{
	string s;

	if (isDownControl)
		s.append("Ctrl+");
	if (isDownAlt)
		s.append("Alt+");
	if (isDownShift)
		s.append("Shift+");
	if (isDownWindows)
		s.append("Win+");
	s.push_back(shortcutKey);

	statusbar->SetStatusText(s.c_str(), 0);
	statusbar->SetStatusText(shortcutKey, 1);

	s = "";
	if (isShortcutDownControl)
		s.append("Ctrl+");
	if (isShortcutDownAlt)
		s.append("Alt+");
	if (isShortcutDownShift)
		s.append("Shift+");
	if (isShortcutDownWindows)
		s.append("Win+");
	s.push_back(shortcutKey);
	
	textctrlControlKeys->SetValue(s.c_str());
}


/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON_SAVE_SETTINGS
 */

void SettingsWindow::OnButtonSaveSettingsClick( wxCommandEvent& event )
{
	keyNavUp = textctrlKeyUp->GetValue()[0];
	keyNavDown = textctrlKeyDown->GetValue()[0];
	keyNavLeft = textctrlKeyLeft->GetValue()[0];
	keyNavRight = textctrlKeyRight->GetValue()[0];
	keyMouseSingleClick = textctrlMouseLeftClick->GetValue()[0];
	keyMouseDoubleClick = textctrlMouseDoubleClick->GetValue()[0];
	keyMouseRightClick = textctrlMouseRight->GetValue()[0];

	int modifiers = NULL;

	if (isShortcutDownAlt)
		modifiers |= wxMOD_ALT;
	if (isShortcutDownControl)
		modifiers |= wxMOD_CONTROL;
	if (isShortcutDownShift)
		modifiers |= wxMOD_SHIFT;
	if (isShortcutDownWindows)
		modifiers |= wxMOD_WIN;

	mainWindow->UnregisterHotKey(wxID_ANY);
	mainWindow->RegisterHotKey(wxID_ANY, modifiers, shortcutKey);

	Show(false);
}

void SettingsWindow::SetParentWindow(AbstractWindow *window)
{
	mainWindow = window;
}