// ClientAsyncSocket.cpp : implementation file
//

#include "pch.h"
#include "ClientAsyncSocket.h"

#include "NetImagePlayDlg.h"
#include "NetImagePlay.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientAsyncSocket

CClientAsyncSocket::CClientAsyncSocket()
{
}

CClientAsyncSocket::~CClientAsyncSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CClientAsyncSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CClientAsyncSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CClientAsyncSocket member functions


void CClientAsyncSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	unsigned char Data[2048] = { 0, };

	//unsigned int size = IMAGE_SIZE_X * 2 * _UDP_TX_BUF_RATE;
	Receive((unsigned char*)Data, (640 * 2 + 4));
/*
	CString szTmp;
	szTmp.Format("%s", Data);

	((CEthernetHostDlg*)AfxGetMainWnd())->m_strRecive += szTmp;
	((CEthernetHostDlg*)AfxGetMainWnd())->UpdateData(FALSE);*/
	((CNetImagePlayDlg*)AfxGetMainWnd())->OnUdpReceive(Data);

	CAsyncSocket::OnReceive(nErrorCode);
}


void CClientAsyncSocket::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	Close();

	//((CEthernetHostDlg*)AfxGetMainWnd())->m_strRecive += "\r\nClose Server\r\n";
	//((CEthernetHostDlg*)AfxGetMainWnd())->UpdateData(FALSE);
	
	CAsyncSocket::OnClose(nErrorCode);
}
