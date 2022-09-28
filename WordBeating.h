
// WordBeating.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CWordBeatingApp:
// See WordBeating.cpp for the implementation of this class
//

class CWordBeatingApp : public CWinApp
{
public:
	CWordBeatingApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CWordBeatingApp theApp;
