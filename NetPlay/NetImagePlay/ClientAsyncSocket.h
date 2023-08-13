#if !defined(AFX_CLIENTASYNCSOCKET_H__4B9D5E01_CC9A_11D2_BFE5_0020E00EF9DE__INCLUDED_)
#define AFX_CLIENTASYNCSOCKET_H__4B9D5E01_CC9A_11D2_BFE5_0020E00EF9DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClientAsyncSocket.h : header file
//

#include "pch.h"

/////////////////////////////////////////////////////////////////////////////
// CClientAsyncSocket command target

class CClientAsyncSocket : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	CClientAsyncSocket();
	virtual ~CClientAsyncSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientAsyncSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CClientAsyncSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTASYNCSOCKET_H__4B9D5E01_CC9A_11D2_BFE5_0020E00EF9DE__INCLUDED_)
