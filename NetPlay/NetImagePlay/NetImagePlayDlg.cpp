
// NetImagePlayDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "NetImagePlay.h"
#include "NetImagePlayDlg.h"
#include "afxdialogex.h"
#include <iostream>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif



#define _IMAGE_SIZE_X 640
#define _IMAGE_SIZE_Y 480

#define _UDP_TX_BUF_RATE	1

#define _IMAGE_LINE_MAX  _IMAGE_SIZE_Y
#define _UDP_TX_BUF_SIZE	_IMAGE_SIZE_X*2

unsigned short gImageBuffer[1280*960];
unsigned int  m_gCamBufferIndex = 0;
int gFlag_Ai = 0;
double gThrVal = 80;


//#define _UDP_TX_BUF_SIZE	1456
#define _CMD_CAM_START		0xFE
#define _CMD_CAM_STOP		0xFD
#define _CMD_CAM_SIZE		0xFC
#define _CMD_CAM_LINE		0xFB
#define _CMD_CAM_FRAME		0xFA
#define _CMD_LED			0xF0

#define PARENT_CLASS CNetImagePlayDlg

DWORD  CaptureThread(LPVOID lpData)
{
	PARENT_CLASS* cpCap = (PARENT_CLASS*)lpData;

	while (cpCap->gCapFlag)
	{
		cpCap->OnThreadProc();
		::Sleep(2);
	}
	//CloseHandle(os.hEvent);
	//pEdit->m_ComuPort.m_hThreadWatchComm = NULL;
	return TRUE;
}
// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CNetImagePlayDlg 대화 상자



CNetImagePlayDlg::CNetImagePlayDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NETIMAGEPLAY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNetImagePlayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNetImagePlayDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CNetImagePlayDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CNetImagePlayDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CNetImagePlayDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CNetImagePlayDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON6, &CNetImagePlayDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CNetImagePlayDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CNetImagePlayDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON5, &CNetImagePlayDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON9, &CNetImagePlayDlg::OnBnClickedButton9)
END_MESSAGE_MAP()


// CNetImagePlayDlg 메시지 처리기

BOOL CNetImagePlayDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_NetPort = 3000;
	//m_IpAddress = _T("192.168.10.184");
	//m_IpAddress = _T("172.30.1.104");
	m_IpAddress = _T("192.168.1.104");

	SetDlgItemInt(IDC_EDIT1, m_NetPort);
	SetDlgItemText(IDC_IPADDRESS1, m_IpAddress);

	//m_ClientSocket.Create();

	m_ImageSizeX = _IMAGE_SIZE_X;
	m_ImageSizeY = _IMAGE_SIZE_Y;


	m_DisplayImg.create(m_ImageSizeY, m_ImageSizeX, CV_8UC3);

	gCapFlag = TRUE;
	AfxBeginThread((AFX_THREADPROC)CaptureThread, (LPVOID)this);

	m_DisplayImg.setTo(cv::Scalar(0, 0, 255));
	cv::moveWindow("Sensor", 50, 100);




	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CNetImagePlayDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CNetImagePlayDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CNetImagePlayDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


unsigned int grx_cnt = 0;
CString gstr_buf;
unsigned int g_cline = 0;
unsigned int g_oline = 0;
int CNetImagePlayDlg::OnUdpReceive(unsigned char* pDataBuffer)
{
	// TODO: 여기에 구현 코드 추가.
	CString str;
	int cmd;
	int i;
	int page = 0;


	unsigned int size = _IMAGE_SIZE_X * 2 * _UDP_TX_BUF_RATE;

	cmd = pDataBuffer[0];
	page = pDataBuffer[2] << 8 | pDataBuffer[3];

	unsigned short data;
	int index = 0;



	if (cmd == _CMD_CAM_LINE)
	{
		if (m_gCamBufferIndex < _IMAGE_SIZE_Y)
		{
			memcpy((unsigned char*)&gImageBuffer[m_gCamBufferIndex * _IMAGE_SIZE_X * 1 * _UDP_TX_BUF_RATE], (unsigned char*)&pDataBuffer[4], _IMAGE_SIZE_X * 2 + _UDP_TX_BUF_RATE);
			m_gCamBufferIndex++;
		}
	}
	else if (cmd == _CMD_CAM_FRAME)
	{
		{
			str.Format(L"%x, %d, 0, %d", cmd, page, m_gCamBufferIndex);
			
			gstr_buf += str + L"\r\n";

			SetDlgItemText(IDC_EDIT2, gstr_buf);

			m_gCamBufferIndex = 0;

			DisplayCamImag(gImageBuffer, _IMAGE_SIZE_Y, _IMAGE_SIZE_X);
			memset(gImageBuffer, 0, _IMAGE_SIZE_X * 1 *_IMAGE_SIZE_Y);
		}
	}
	else
	{
	}
	

	return 0;
}


void CNetImagePlayDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL ret;

	m_NetPort = GetDlgItemInt(IDC_EDIT1, NULL, TRUE);
	GetDlgItemText(IDC_IPADDRESS1, m_IpAddress);
	

	if (m_FlagConnect)
	{
		m_ClientSocket.Close();
		m_FlagConnect = FALSE;

		SetDlgItemText(IDC_BUTTON1, L"Connect");
	}
	else
	{
		m_ClientSocket.Create();
		ret = m_ClientSocket.Connect(m_IpAddress, m_NetPort);

		if (ret == TRUE)
		{
			AfxMessageBox(L"Failed Create Socket");
		}
		else
		{
			m_FlagConnect = TRUE;

			SetDlgItemText(IDC_BUTTON1, L"Close");
		}
	}
}



int CNetImagePlayDlg::OnThreadProc()
{
	// TODO: 여기에 구현 코드 추가.
	Mat scale_img;
	int i;

#if 1
	Mat gray_image;
	Mat in_image;
	
	cv::rotate(m_DisplayImg, in_image, ROTATE_90_COUNTERCLOCKWISE);
	//cv::rotate(img, img, ROTATE_180);
	

	//m_DisplayImg.setTo(cv::Scalar(255, 0, 0));
	cv::waitKey(10);

	cv::imshow("Sensor", in_image);

	if (gFlag_Ai == 1)
	{

	}
	else if (gFlag_Ai == 2)
	{

		Mat img_edge;

		cvtColor(in_image, gray_image, COLOR_BGR2GRAY);             //convert image from grey to color

		Mat thresh;
		threshold(gray_image, thresh, gThrVal, 255, THRESH_BINARY);

		cv::imshow("img_edge", thresh);



		// detect the contours on the binary image using cv2.CHAIN_APPROX_NONE
		vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;
		findContours(thresh, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
		// draw contours on the original image
		Mat image_copy = in_image.clone();
		drawContours(image_copy, contours, -1, Scalar(0, 255, 0), 2);
		cv::imshow("None approximation", image_copy);
	}
	else if (gFlag_Ai == 3)
	{
		string obj_class[] = { "background", "aeroplane", "bicycle", "bird", "boat",
			"bottle", "bus", "car", "cat", "chair", "cow", "diningtable",
			"dog", "horse", "motorbike", "person", "pottedplant", "sheep",
			"sofa", "train", "tvmonitor" };

		Net net = readNetFromCaffe("MobileNetSSD_deploy.prototxt.txt", "MobileNetSSD_deploy.caffemodel");
		Mat blob = blobFromImage(in_image, 0.007843, Size(300, 300), Scalar(127.5, 127.5, 127.5));
		net.setInput(blob);
		
		Mat detection = net.forward();

		Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());
		for (int i = 0; i < detectionMat.rows; i++)
		{
			float confidence = detectionMat.at<float>(i, 2);

			if (confidence > 0.4)
			{
				int id = (int)(detectionMat.at<float>(i, 1));
				int x1 = static_cast<int>(detectionMat.at<float>(i, 3) * in_image.cols);
				int y1 = static_cast<int>(detectionMat.at<float>(i, 4) * in_image.rows);
				int x2 = static_cast<int>(detectionMat.at<float>(i, 5) * in_image.cols);
				int y2 = static_cast<int>(detectionMat.at<float>(i, 6) * in_image.rows);

				rectangle(in_image, Point(x1, y1), Point(x2, y2), Scalar(0, 255, 0), 2);

				String label = format("%s: %.2f", obj_class[id].c_str(), confidence);

				int base;
				Size label_size = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &base);

				rectangle(in_image, Point(x1, y1 - label_size.height), Point(x1 + label_size.width, y1), Scalar(0, 255, 0), -1);
				putText(in_image, label, Point(x1, y1), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0), 1);
			}
		}


		cv::imshow("result", in_image);
	}
	
#endif
	return 0;

}


void CNetImagePlayDlg::OnBnClickedButton2()
{
	SendCommand(_CMD_LED, 1);
}


void CNetImagePlayDlg::OnBnClickedButton3()
{
	m_TotalImageSize = m_ImageSizeX * m_ImageSizeY * 2;

	SendCommand(_CMD_CAM_START, m_TotalImageSize);
}


void CNetImagePlayDlg::OnBnClickedButton4()
{
	gFlag_Ai = 2;
}


int CNetImagePlayDlg::DisplayCamImag(unsigned short* Buf, unsigned int X, unsigned int Y)
{
	unsigned int index = 0;

	for (int row = 0; row < m_DisplayImg.rows; row++)
	{
		uchar* pointer_row = m_DisplayImg.ptr<uchar>(row);

		for (int col = 0; col < m_DisplayImg.cols; col++)
		{
			pointer_row[col * 3 + 0] = (Buf[index] & 0x001F) << 3;
			pointer_row[col * 3 + 1] = (Buf[index] & 0x07E0) >> 3;
			pointer_row[col * 3 + 2] = (Buf[index] & 0xF800) >> 8;
			index++;
		}
	}

	return 0;
}

int CNetImagePlayDlg::SendCommand(unsigned int Cmd, unsigned int Para)
{
	CString str;

	unsigned char buf[4];
	buf[0] = Cmd;
	buf[1] = 0;
	buf[2] = Para >> 8;
	buf[3] = Para;

	m_ClientSocket.Send(buf, sizeof(buf));

	return 0;
}

void CNetImagePlayDlg::OnBnClickedButton6()
{
	SendCommand(_CMD_LED, 0);
}


void CNetImagePlayDlg::OnBnClickedButton7()
{
	SendCommand(_CMD_CAM_STOP, 0);
}


void CNetImagePlayDlg::OnBnClickedButton8()
{
	gFlag_Ai = 3;
}


void CNetImagePlayDlg::OnBnClickedButton5()
{
	gThrVal = GetDlgItemInt(IDC_EDIT3);
}


void CNetImagePlayDlg::OnBnClickedButton9()
{
	gFlag_Ai = 1;
}
