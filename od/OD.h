// OD.h : main header file for the OD application
//

#if !defined(AFX_OD_H__A4B7ACFD_94F8_430D_916A_43BCB1595340__INCLUDED_)
#define AFX_OD_H__A4B7ACFD_94F8_430D_916A_43BCB1595340__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "GdiPlus.h"
using namespace Gdiplus;

/////////////////////////////////////////////////////////////////////////////
// CODApp:
// See OD.cpp for the implementation of this class
//

class CODApp : public CWinApp
{
public:
	CODApp();
	~CODApp();
private:
	ULONG_PTR m_gdiplusToken;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CODApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CODApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OD_H__A4B7ACFD_94F8_430D_916A_43BCB1595340__INCLUDED_)
