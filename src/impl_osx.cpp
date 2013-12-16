/////////////////////////////////////////////////////////////////////////////
// Name:        abstractwindow.cpp
// Purpose:     
// Author:      Marijn Koesen
// Modified by: 
// Created:     04/04/2011 19:32:52
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#include "peripheral_api.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#ifdef __WXMAC__

#include "abstractwindow.h"
#include "supermouserapp.h"

#import <ApplicationServices/ApplicationServices.h>
#import <Carbon/carbon.h>

void init_screensize(int *width, int *height)
{
	wxDisplaySize(width, height);
}

OSStatus OnHotKeyEvent(EventHandlerCallRef nextHandler, EventRef theEvent, void *userData)
{
	EventHotKeyID hkCom;

	GetEventParameter(theEvent, kEventParamDirectObject, typeEventHotKeyID, NULL, sizeof (hkCom), NULL, &hkCom);
	SuperMouserApp *app = (SuperMouserApp*) userData;

	app->Activate();

	return noErr;
}

void register_hotkey(CursorWindow *window, HotKeyHandler *superMouser)
{
	EventHotKeyRef gMyHotKeyRef;
	EventHotKeyID gMyHotKeyID;
	EventTypeSpec eventType;
	eventType.eventClass = kEventClassKeyboard;
	eventType.eventKind = kEventHotKeyPressed;

	InstallApplicationEventHandler(&OnHotKeyEvent, 1, &eventType, (void *) superMouser, NULL);

	gMyHotKeyID.signature = 'htk1';
	gMyHotKeyID.id = 1;
	// windows+shift+space
	RegisterEventHotKey(49, cmdKey + shiftKey, gMyHotKeyID, GetApplicationEventTarget(), 0, &gMyHotKeyRef);
}

void move_to(int x, int y)
{
	CGPoint newloc;
	CGEventRef eventRef;
	newloc.x = x;
	newloc.y = y;

	eventRef = CGEventCreateMouseEvent(NULL, kCGEventMouseMoved, newloc, kCGMouseButtonCenter);

	//Apparently, a bug in xcode requires this next line
	CGEventSetType(eventRef, kCGEventMouseMoved); // Apparently, a bug in xcode requires this line
	CGEventPost(kCGSessionEventTap, eventRef);
	CFRelease(eventRef);
}

void click_left(int x, int y)
{
	CGPoint newloc;
	CGEventRef eventRef;
	newloc.x = x;
	newloc.y = y;

	// Mouse down
	eventRef = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseDown, newloc, kCGMouseButtonLeft);
	CGEventSetType(eventRef, kCGEventLeftMouseDown); // Apparently, a bug in xcode requires this line
	CGEventPost(kCGSessionEventTap, eventRef);
	CFRelease(eventRef);

	usleep(100);

	// Mouse up
	eventRef = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseUp, newloc, kCGMouseButtonLeft);
	CGEventSetType(eventRef, kCGEventLeftMouseUp); // Apparently, a bug in xcode requires this line
	CGEventPost(kCGSessionEventTap, eventRef);
	CFRelease(eventRef);
}

void click_right(int x, int y)
{
	CGPoint newloc;
	CGEventRef eventRef;
	newloc.x = x;
	newloc.y = y;

	// Mouse down
	eventRef = CGEventCreateMouseEvent(NULL, kCGEventRightMouseDown, newloc, kCGMouseButtonRight);
	CGEventSetType(eventRef, kCGEventRightMouseDown); // Apparently, a bug in xcode requires this line
	CGEventPost(kCGSessionEventTap, eventRef);
	CFRelease(eventRef);

	usleep(100);

	// Mouse up
	eventRef = CGEventCreateMouseEvent(NULL, kCGEventRightMouseUp, newloc, kCGMouseButtonRight);
	CGEventSetType(eventRef, kCGEventRightMouseUp); // Apparently, a bug in xcode requires this line
	CGEventPost(kCGSessionEventTap, eventRef);
	CFRelease(eventRef);
}

void click_double(int x, int y)
{
	CGEventRef theEvent = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseDown, CGPointMake(x, y), kCGMouseButtonLeft);
	CGEventPost(kCGHIDEventTap, theEvent);
	CGEventSetType(theEvent, kCGEventLeftMouseUp);
	CGEventPost(kCGHIDEventTap, theEvent);

	CGEventSetIntegerValueField(theEvent, kCGMouseEventClickState, 2);

	CGEventSetType(theEvent, kCGEventLeftMouseDown);
	CGEventPost(kCGHIDEventTap, theEvent);

	CGEventSetType(theEvent, kCGEventLeftMouseUp);
	CGEventPost(kCGHIDEventTap, theEvent);

	CFRelease(theEvent);
}

#endif //__WXMAC__
