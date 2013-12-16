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

#ifdef __WXMSW__

#include "AbstractWindow.h"

void init_screensize(int *width, int *height)
{
	wxDisplaySize(width, height);
}

void register_hotkey(AbstractWindow *window)
{
	window->RegisterHotKey(wxID_ANY, wxMOD_CONTROL | wxMOD_SHIFT, 'M');
}

void move_to(int x, int y)
{
	SetCursorPos(x, y);
}

void click_left(int x, int y)
{
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

void click_right(int x, int y)
{
	mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
}

void click_double(int x, int y)
{
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	GetDoubleClickTime;
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}
#endif // __WXMSW__