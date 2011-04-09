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
#include <wx/taskbar.h>

#ifdef __WXMAC__
#import <ApplicationServices/ApplicationServices.h>
#import <Carbon/carbon.h>
#endif 

#include "settingswindow.h"
#include "cursorwindow.h"
#include "supermouserapp.h"
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
    EVT_CLOSE( SettingsWindow::OnCloseWindow )

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
    SetIcon(GetIconResource(wxT("IDR_ICO_MAIN")));
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
#if defined(__WXMSW__) || defined(__WXGTK__)
    textctrlControlKeys = NULL;
#endif
    colourctrl = NULL;
    checkboxTransparency = NULL;
    sliderTransparency = NULL;
    textctrlKeyUp = NULL;
    textctrlKeyLeft = NULL;
    textctrlKeyRight = NULL;
    textctrlKeyDown = NULL;
    textctrlMouseLeftClick = NULL;
    textctrlMouseDoubleClick = NULL;
    textctrlMouseRight = NULL;
    buttonSave = NULL;
    statusbar = NULL;
////@end SettingsWindow member initialisation
	isDownControl = false;
	isDownAlt = false;
	isDownWindows = false;
	isDownShift = false;

    #ifndef __WXMAC__
	isShortcutDownControl = true;
	isShortcutDownAlt = true;
	isShortcutDownWindows = false;
	isShortcutDownShift = false;
	shortcutKey = 'M';

	keyNavUp = 'K';
	keyNavDown = 'J';
	keyNavLeft = 'H';
	keyNavRight = 'L';
	keyMouseSingleClick = 'F';
	keyMouseDoubleClick = 'D';
	keyMouseRightClick = 'G';
    #endif

    #ifdef __WXMAC__
	isShortcutDownControl = false;
	isShortcutDownAlt = false;
	isShortcutDownWindows = true;
	isShortcutDownShift = true;
	shortcutKey = 'm';

	keyNavUp = 'k';
	keyNavDown = 'j';
	keyNavLeft = 'h';
	keyNavRight = 'l';
	keyMouseSingleClick = 'f';
	keyMouseDoubleClick = 'd';
	keyMouseRightClick = 'g';
    #endif

	taskbarIcon_ = new wxTaskBarIcon;
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
    itemBoxSizer3->Add(itemStaticBoxSizer4, 1, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    itemStaticBoxSizer4->Add(itemBoxSizer5, 0, wxGROW|wxALL, 5);

    wxStaticText* itemStaticText6 = new wxStaticText( itemPanel2, wxID_STATIC, _("Activate mouser:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer5->Add(itemStaticText6, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

#if defined(__WXMSW__) || defined(__WXGTK__)
    textctrlControlKeys = new wxTextCtrl( itemPanel2, ID_TEXTCTRL1, _("Ctrl+Alt+M"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer5->Add(textctrlControlKeys, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

#endif

    wxBoxSizer* itemBoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
    itemStaticBoxSizer4->Add(itemBoxSizer8, 0, wxGROW|wxALL, 5);

    wxStaticText* itemStaticText9 = new wxStaticText( itemPanel2, wxID_STATIC, _("Color:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer8->Add(itemStaticText9, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    colourctrl = new wxColourPickerCtrl( itemPanel2, ID_COLOURCTRL, wxColour(0, 64, 128), wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
    itemBoxSizer8->Add(colourctrl, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    checkboxTransparency = new wxCheckBox( itemPanel2, ID_CHECKBOX, _("Transparency"), wxDefaultPosition, wxDefaultSize, 0 );
    checkboxTransparency->SetValue(true);
    itemBoxSizer8->Add(checkboxTransparency, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    sliderTransparency = new wxSlider( itemPanel2, ID_SLIDER, 128, 0, 255, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_LABELS|wxSL_INVERSE );
    itemBoxSizer8->Add(sliderTransparency, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemStaticBoxSizer4->Add(5, 5, 1, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer14 = new wxBoxSizer(wxHORIZONTAL);
    itemStaticBoxSizer4->Add(itemBoxSizer14, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    textctrlKeyUp = new wxTextCtrl( itemPanel2, ID_TEXTCTRL, _("K"), wxDefaultPosition, wxDefaultSize, 0 );
    textctrlKeyUp->SetMaxLength(1);
    itemBoxSizer14->Add(textctrlKeyUp, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer16 = new wxBoxSizer(wxHORIZONTAL);
    itemStaticBoxSizer4->Add(itemBoxSizer16, 0, wxALIGN_CENTER_HORIZONTAL|wxLEFT|wxRIGHT, 5);

    textctrlKeyLeft = new wxTextCtrl( itemPanel2, ID_TEXTCTRL2, _("H"), wxDefaultPosition, wxDefaultSize, 0 );
    textctrlKeyLeft->SetMaxLength(1);
    itemBoxSizer16->Add(textctrlKeyLeft, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText18 = new wxStaticText( itemPanel2, wxID_STATIC, _("Navigation keys"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer16->Add(itemStaticText18, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    textctrlKeyRight = new wxTextCtrl( itemPanel2, ID_TEXTCTRL3, _("L"), wxDefaultPosition, wxDefaultSize, 0 );
    textctrlKeyRight->SetMaxLength(1);
    itemBoxSizer16->Add(textctrlKeyRight, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer20 = new wxBoxSizer(wxHORIZONTAL);
    itemStaticBoxSizer4->Add(itemBoxSizer20, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    textctrlKeyDown = new wxTextCtrl( itemPanel2, ID_TEXTCTRL4, _("J"), wxDefaultPosition, wxDefaultSize, 0 );
    textctrlKeyDown->SetMaxLength(1);
    itemBoxSizer20->Add(textctrlKeyDown, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemStaticBoxSizer4->Add(5, 5, 1, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer23 = new wxBoxSizer(wxHORIZONTAL);
    itemStaticBoxSizer4->Add(itemBoxSizer23, 0, wxGROW|wxLEFT|wxRIGHT, 5);

    wxStaticText* itemStaticText24 = new wxStaticText( itemPanel2, wxID_STATIC, _("Mouse left click:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer23->Add(itemStaticText24, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    textctrlMouseLeftClick = new wxTextCtrl( itemPanel2, ID_TEXTCTRL5, _("F"), wxDefaultPosition, wxDefaultSize, 0 );
    textctrlMouseLeftClick->SetMaxLength(1);
    itemBoxSizer23->Add(textctrlMouseLeftClick, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer26 = new wxBoxSizer(wxHORIZONTAL);
    itemStaticBoxSizer4->Add(itemBoxSizer26, 0, wxGROW|wxLEFT|wxRIGHT, 5);

    wxStaticText* itemStaticText27 = new wxStaticText( itemPanel2, wxID_STATIC, _("Mouse double click:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer26->Add(itemStaticText27, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    textctrlMouseDoubleClick = new wxTextCtrl( itemPanel2, ID_TEXTCTRL6, _("D"), wxDefaultPosition, wxDefaultSize, 0 );
    textctrlMouseDoubleClick->SetMaxLength(1);
    itemBoxSizer26->Add(textctrlMouseDoubleClick, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer29 = new wxBoxSizer(wxHORIZONTAL);
    itemStaticBoxSizer4->Add(itemBoxSizer29, 0, wxGROW|wxLEFT|wxRIGHT, 5);

    wxStaticText* itemStaticText30 = new wxStaticText( itemPanel2, wxID_STATIC, _("Mouse right click:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer29->Add(itemStaticText30, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    textctrlMouseRight = new wxTextCtrl( itemPanel2, ID_TEXTCTRL7, _("G"), wxDefaultPosition, wxDefaultSize, 0 );
    textctrlMouseRight->SetMaxLength(1);
    itemBoxSizer29->Add(textctrlMouseRight, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemStaticBoxSizer4->Add(5, 5, 1, wxGROW|wxALL, 5);

    buttonSave = new wxButton( itemPanel2, ID_BUTTON_SAVE_SETTINGS, _("Save settings"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticBoxSizer4->Add(buttonSave, 0, wxALIGN_RIGHT|wxALL, 5);

    statusbar = new wxStatusBar( itemFrame1, ID_STATUSBAR, wxST_SIZEGRIP|wxNO_BORDER );
    statusbar->SetFieldsCount(2);
    itemFrame1->SetStatusBar(statusbar);

    // Connect events and objects
#if defined(__WXMSW__) || defined(__WXGTK__)
    textctrlControlKeys->Connect(ID_TEXTCTRL1, wxEVT_KEY_DOWN, wxKeyEventHandler(SettingsWindow::OnKeyDown), NULL, this);
    textctrlControlKeys->Connect(ID_TEXTCTRL1, wxEVT_KEY_UP, wxKeyEventHandler(SettingsWindow::OnKeyUp), NULL, this);
#endif
////@end SettingsWindow content construction


#ifdef __WXMAC__
	textctrlKeyUp->SetValue(_(new wxChar(keyNavUp)));
	textctrlKeyDown->SetValue(_(new wxChar(keyNavDown)));
	textctrlKeyLeft->SetValue(_(new wxChar(keyNavLeft)));
	textctrlKeyRight->SetValue(_(new wxChar(keyNavRight)));

	textctrlMouseLeftClick->SetValue(_(new wxChar(keyMouseSingleClick)));
	textctrlMouseDoubleClick->SetValue(_(new wxChar(keyMouseDoubleClick)));
	textctrlMouseRight->SetValue(_(new wxChar(keyMouseRightClick)));
#else
	textctrlKeyUp->SetValue(keyNavUp);
	textctrlKeyDown->SetValue(keyNavDown);
	textctrlKeyLeft->SetValue(keyNavLeft);
	textctrlKeyRight->SetValue(keyNavRight);

	textctrlMouseLeftClick->SetValue(keyMouseSingleClick);
	textctrlMouseDoubleClick->SetValue(keyMouseDoubleClick);
	textctrlMouseRight->SetValue(keyMouseRightClick);
#endif

    buttonSave->SetFocus();
}

void SettingsWindow::RemoveTrayIcon()
{
	taskbarIcon_->RemoveIcon();
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
    if (name == _T("IDR_ICO_MAIN"))
    {
        wxIcon icon(_T("IDR_ICO_MAIN"), wxBITMAP_TYPE_ICO_RESOURCE);
        return icon;
    }
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

#ifdef __WXMSW__
	if (isShortcutDownAlt)
		modifiers |= wxMOD_ALT;
	if (isShortcutDownControl)
		modifiers |= wxMOD_CONTROL;
	if (isShortcutDownShift)
		modifiers |= wxMOD_SHIFT;
	if (isShortcutDownWindows)
		modifiers |= wxMOD_WIN;

	app_->SettingsCallback(modifiers, shortcutKey);
#endif __WXMSW__

#ifdef __WXMAC__
	if (isShortcutDownAlt)
		modifiers |= optionKey;
	if (isShortcutDownControl)
		modifiers |= controlKey;
	if (isShortcutDownShift)
		modifiers |= shiftKey;
	if (isShortcutDownWindows)
		modifiers |= cmdKey;

	app_->SettingsCallback(modifiers, shortcutKey);
#endif __WXMSW__

	Show(false);
}

void SettingsWindow::SetApplication(SuperMouserApp *app)
{
	app_ = app;
}

/*
 * wxEVT_CLOSE_WINDOW event handler for ID_SETTINGSWINDOW
 */

void SettingsWindow::OnCloseWindow( wxCloseEvent& event )
{
    Hide();
}
