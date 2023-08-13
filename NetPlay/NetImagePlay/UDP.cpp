// UDP.cpp : implementation file
//

//#include "NBTSTAT.h"

#include "pch.h"
#include "UDP.h"

//#include "NBTSTATDlg.h"

#include "NetImagePlayDlg.h"
#include "NetImagePlay.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUDP
//-----------------------------------------------
//extern CNBTSTATDlg* pDlg;
//-----------------------------------------------
extern CNetImagePlayDlg* pDlg;

CUDP::CUDP()
{
}

CUDP::~CUDP()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CUDP, CSocket)
	//{{AFX_MSG_MAP(CUDP)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CUDP member functions

void CUDP::OnReceive(int nErrorCode) 
{
    /*
    static int i = 0;

    i++;

    TCHAR buff[4096];
    int nRead;

    CString strSendersIp;

    UINT uSendersPort;

    // Could use Receive here if you don't need the senders address & port
    nRead = ReceiveFromEx(buff, 1460, strSendersIp, uSendersPort);

    switch (nRead)
    {
    case 0:       // Connection was closed.
        Close();
        break;
    case SOCKET_ERROR:
        if (GetLastError() != WSAEWOULDBLOCK)
        {
            AfxMessageBox("Error occurred");
            Close();
        }
        break;
    default: // Normal case: Receive() returned the # of bytes received.
        buff[nRead] = 0; //terminate the string (assuming a string for this example)
        CString strReceivedData(buff);       // This is the input data    

        //((CEthernetHostDlg*)AfxGetMainWnd())->OnUdpReceive();
        //((CEthernetHostDlg*)AfxGetMainWnd())->SetDlgItemText(IDC_EDIT2, strReceivedData);
    }
    CAsyncSocket::OnReceive(nErrorCode);

	*/
	// TODO: Add your specialized code here and/or call the base class
	unsigned char Data[2048] = { 0, };

    //unsigned int size = IMAGE_SIZE_X * 2 * _UDP_TX_BUF_RATE;
	Receive((unsigned char*)Data, (640*2+4));
	//CString szTmp;
	//szTmp.Format("%s", Data);

	//pDlg->OnUdpReceive(Data, );
	//pDlg->SetDlgItemText(IDC_EDIT2, szTmp);
    ((CNetImagePlayDlg*)AfxGetMainWnd())->OnUdpReceive(Data);
	CSocket::OnReceive(nErrorCode);
}


