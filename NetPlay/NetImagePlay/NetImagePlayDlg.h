
// NetImagePlayDlg.h: 헤더 파일
//

#pragma once
#include "UDP.h"
#include "ClientAsyncSocket.h"

// CNetImagePlayDlg 대화 상자
class CNetImagePlayDlg : public CDialogEx
{
// 생성입니다.
public:
	CNetImagePlayDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	CUDP m_UDPSocket;
	CClientAsyncSocket m_ClientSocket;

	UINT m_NetPort;
	BOOL m_FlagConnect;
	BOOL m_FlagMode;

	CString m_IpAddress;


	cv::Mat m_DisplayImg;
	BOOL gCapFlag;
	unsigned long m_imgSize;
	unsigned long m_RegImgSize;
	unsigned int m_TotalImageSize;
	unsigned int m_ImageSizeX;
	unsigned int m_ImageSizeY;
	
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NETIMAGEPLAY_DIALOG };
#endif
	

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int OnUdpReceive(unsigned char* pDataBuffer);
	afx_msg void OnBnClickedButton1();
	int OnThreadProc();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	int DisplayCamImag(unsigned short* Buf, unsigned int X, unsigned int Y);
	int CNetImagePlayDlg::SendCommand(unsigned int Cmd, unsigned int Para);
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton9();
};
