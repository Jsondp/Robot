
// KSJRobotURDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "KSJRobotUR.h"
#include "KSJRobotURDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CKSJRobotURDlg 对话框



CKSJRobotURDlg::CKSJRobotURDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CKSJRobotURDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pEthernet = new CEthernet;

	TCHAR   szPath[MAX_PATH] = { '\0' };
	GetCurrentDirectory(MAX_PATH, szPath);
	lstrcat(szPath, _T("\\KSJSWAP.ini"));
	KSJINI_Init(&m_hKSJIni, szPath);
	m_pszCommand = new TCHAR[128];
	InitializeCriticalSection(&m_cs);
}

CKSJRobotURDlg::~CKSJRobotURDlg()
{
	delete m_pEthernet;
	m_pEthernet = NULL;

	KSJINI_UnInit(&m_hKSJIni);
	delete[]m_pszCommand;
	m_pszCommand = NULL;
	DeleteCriticalSection(&m_cs);
}

void CKSJRobotURDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CKSJRobotURDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK_CONNECT, &CKSJRobotURDlg::OnBnClickedCheckConnect)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CKSJRobotURDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_RUN, &CKSJRobotURDlg::OnBnClickedButtonRun)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CKSJRobotURDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_GET_POSITION, &CKSJRobotURDlg::OnBnClickedButtonGetPosition)
	ON_LBN_SELCHANGE(IDC_LIST_COMMAND, &CKSJRobotURDlg::OnLbnSelchangeListCommand)
	ON_BN_CLICKED(IDC_BUTTON_CHENCH, &CKSJRobotURDlg::OnBnClickedButtonChench)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CKSJRobotURDlg::OnDeltaposSpin1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, &CKSJRobotURDlg::OnDeltaposSpin2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN3, &CKSJRobotURDlg::OnDeltaposSpin3)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN4, &CKSJRobotURDlg::OnDeltaposSpin4)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN5, &CKSJRobotURDlg::OnDeltaposSpin5)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN6, &CKSJRobotURDlg::OnDeltaposSpin6)
	ON_BN_CLICKED(IDC_BUTTON_EXTCUTE, &CKSJRobotURDlg::OnBnClickedButtonExtcute)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, &CKSJRobotURDlg::OnCbnSelchangeComboType)
	ON_BN_CLICKED(IDCANCEL, &CKSJRobotURDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CKSJRobotURDlg 消息处理程序

BOOL CKSJRobotURDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	GetDlgItem(IDC_EDIT6)->SetWindowText(_T("180"));
	GetDlgItem(IDC_EDIT7)->SetWindowText(_T("0"));
	GetDlgItem(IDC_EDIT8)->SetWindowText(_T("0"));
	CSpinButtonCtrl * pSpinCtrl = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN1);
	pSpinCtrl->SetBase(10);
	pSpinCtrl->SetRange32(-1000, 1000);
	pSpinCtrl = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN2);
	pSpinCtrl->SetBase(10);
	pSpinCtrl->SetRange32(-1000, 1000);
	pSpinCtrl = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN3);
	pSpinCtrl->SetBase(10);
	pSpinCtrl->SetRange32(-1000, 1000);
	pSpinCtrl = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN4);
	pSpinCtrl->SetBase(10);
	pSpinCtrl->SetRange32(-100, 100);
	pSpinCtrl = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN5);
	pSpinCtrl->SetBase(10);
	pSpinCtrl->SetRange32(-100, 100);
	pSpinCtrl = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN6);
	pSpinCtrl->SetBase(10);
	pSpinCtrl->SetRange32(-100, 100);

	ReadIni();
	CComboBox    *pComboBox = NULL;
	pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_TYPE);
	pComboBox->ResetContent();
	CString strType[4] = { _T("movej"), _T("movel"), _T("movep"), _T("movec") };
	for (int i = 0; i < 2; i++)
	{
		pComboBox->AddString(strType[i]);
	}

	pComboBox->SetCurSel(0);

	pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_WAY);
	pComboBox->ResetContent();
	CString strMove[2] = { _T("坐标移动"), _T("轴移动") };
	for (int i = 0; i < 2; i++)
	{
		pComboBox->AddString(strMove[i]);
	}

	pComboBox->SetCurSel(0);
	SetDlgItemInt(IDC_EDIT_INTERVAL, 2000);
	LoadCommand();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CKSJRobotURDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	SaveCommand();
	WriteIni();
}


void CKSJRobotURDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CKSJRobotURDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CKSJRobotURDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CKSJRobotURDlg::OnBnClickedCheckConnect()//连接断开服务器，通过网络类实现
{
	BOOL bCheck = ((CButton*)GetDlgItem(IDC_CHECK_CONNECT))->GetCheck();
	if (bCheck)
	{
		if (m_hGetPoseExitEvent != NULL)
		{
			SetEvent(m_hGetPoseExitEvent);
		}

		if (m_hGetPoseThread != NULL)
		{
			if (WAIT_OBJECT_0 != WaitForSingleObject(m_hGetPoseThread, 3000))
			{
				TerminateThread(m_hGetPoseThread, 0);
			}
			CloseHandle(m_hGetPoseThread);
			m_hGetPoseThread = NULL;
		}

		m_pEthernet->Client_Connect("", 0, false);
		((CButton*)GetDlgItem(IDC_CHECK_CONNECT))->SetWindowText(_T("连接服务器"));
		((CButton*)GetDlgItem(IDC_CHECK_CONNECT))->SetCheck(FALSE);
		GetDlgItem(IDC_STATIC_SERVER)->SetWindowText(_T("断开服务器连接!"));
	}
	else
	{
		unsigned char ucIp[4];
		((CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS_SERVER))->GetAddress(ucIp[0], ucIp[1], ucIp[2], ucIp[3]);
		if (ucIp[0] == 0 || ucIp[0] == 127 || ucIp[0] == 255)
		{
			GetDlgItem(IDC_STATIC_SERVER)->SetWindowText(_T("请输入合理的服务器ip"));
			return;
		}

		CString str;
		GetDlgItem(IDC_EDIT_PORT)->GetWindowText(str);
		if (str.IsEmpty())
		{
			GetDlgItem(IDC_STATIC_SERVER)->SetWindowText(_T("请输入服务器端口"));
			return;
		}

		CString strIP;
		((CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS_SERVER))->GetWindowText(strIP);
		m_pEthernet->Client_Connect((char*)strIP.GetString(), GetDlgItemInt(IDC_EDIT_PORT), true);
		((CButton*)GetDlgItem(IDC_CHECK_CONNECT))->SetWindowText(_T("断开连接"));
		((CButton*)GetDlgItem(IDC_CHECK_CONNECT))->SetCheck(TRUE);
		GetDlgItem(IDC_STATIC_SERVER)->SetWindowText(_T("连接服务器成功!"));

		DWORD dwThreadID;
		ResetEvent(m_hGetPoseExitEvent);
		m_hGetPoseThread = (HANDLE)_beginthreadex(NULL, 0, (PBEGINTHREADEX_FUNC)CKSJRobotURDlg::GetPoseThread, this, 0, (PBEGINTHREADEX_ID)&dwThreadID);
	}
}


void CKSJRobotURDlg::OnBnClickedButtonAdd()//将脚本添加到列表中
{
	TCHAR szMove[256] = { 0 };
	TCHAR szPara[8][16];
	for (int i = 0; i < 8; i++)
	{
		GetDlgItem(IDC_EDIT1 + i)->GetWindowText(szPara[i], 16);
	}

	CComboBox    *pComboBox = NULL;
	pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_TYPE);
	CString MoveType;
	pComboBox->GetLBText(pComboBox->GetCurSel(), MoveType);

	pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_WAY);
	CString MoveWay;
	pComboBox->GetLBText(pComboBox->GetCurSel(), MoveWay);

	sprintf(szMove, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s",
		MoveType, MoveWay, szPara[0], szPara[1], szPara[2], szPara[3], szPara[4], szPara[5], szPara[6], szPara[7]);
	
	int count = 0;
	count = ((CListBox*)GetDlgItem(IDC_LIST_COMMAND))->GetCount();
	((CListBox*)GetDlgItem(IDC_LIST_COMMAND))->InsertString(count, szMove);
}


void CKSJRobotURDlg::OnBnClickedButtonChench()//修改在列表中选中的脚本
{
	int nIndex = ((CListBox*)GetDlgItem(IDC_LIST_COMMAND))->GetCurSel();
	if (nIndex>=0)
	{
		((CListBox*)GetDlgItem(IDC_LIST_COMMAND))->DeleteString(nIndex);
		TCHAR szMove[256] = { 0 };
		TCHAR szPara[8][16];
		for (int i = 0; i < 8; i++)
		{
			GetDlgItem(IDC_EDIT1 + i)->GetWindowText(szPara[i], 16);
		}

		CComboBox    *pComboBox = NULL;
		pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_TYPE);
		CString MoveType;
		pComboBox->GetLBText(pComboBox->GetCurSel(), MoveType);

		pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_WAY);
		CString MoveWay;
		pComboBox->GetLBText(pComboBox->GetCurSel(), MoveWay);

		sprintf(szMove, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s",
			MoveType, MoveWay, szPara[0], szPara[1], szPara[2], szPara[3], szPara[4], szPara[5], szPara[6], szPara[7]);

		((CListBox*)GetDlgItem(IDC_LIST_COMMAND))->InsertString(nIndex, szMove);
	}

}


CStringArray* DivString(CString test)
{
	CStringArray* m_result = new CStringArray;
	while (TRUE)
	{
		int index = test.Find(_T(","));
		if (index == -1)
		{
			m_result->Add(test);
			return m_result;
		}
		CString test1 = test.Left(index);
		m_result->Add(test1);
		test = test.Right(test.GetLength() - index - 1);
	}

}

void CKSJRobotURDlg::OnBnClickedButtonRun()//连续运行列表中的脚本
{
	BOOL bCheck = ((CButton*)GetDlgItem(IDC_CHECK_CONNECT))->GetCheck();
	if (!bCheck)
	{
		AfxMessageBox("请连接机器人! ");
		return;
	}
	char szType[4][16] = { "movej", "movel", "movep", "movec" };
	CString strType[4] = { "movej", "movel", "movep", "movec" };
	CString strMove[2] = { "坐标移动", "轴移动" };
	CString strParam[10];
	CString strTemp;
	int count = 0;
	ROBOT_POSITION Position;
	ROBOT_PARAM Param;
	ROBOT_MOVE_TYPE type;
	int nLen = 0;
	float RX, RY, RZ;
	Param.fRadius = 0;

	count = ((CListBox*)GetDlgItem(IDC_LIST_COMMAND))->GetCount();
	for (int i = 0; i < count; i++)
	{
		((CListBox*)GetDlgItem(IDC_LIST_COMMAND))->GetText(i, strTemp);
		CStringArray* result = DivString(strTemp);
		for (int j = 0; j < 10;j++)
		{
			strParam[j] = result->GetAt(j);
		}

		Position.fXdata = atof(strParam[2]);
		Position.fYdata = atof(strParam[3]);
		Position.fZdata = atof(strParam[4]);
		Param.fSpeed = atof(strParam[5]);
		Param.fAcceleration = atof(strParam[6]);
		Position.fRXdata = atof(strParam[7]);
		Position.fRYdata = atof(strParam[8]);
		Position.fRZdata = atof(strParam[9]);

		for (int j = 0; j < 4;j++)
		{
			if (strParam[0] == strType[j])
			{
				type = (ROBOT_MOVE_TYPE)j;
				break;
			}
		}

		if (strParam[1] == strMove[0])
		{
			SetAbsolutePosition(type, Position.fXdata, Position.fYdata, Position.fZdata,
				Position.fRXdata, Position.fRYdata, Position.fRZdata, Param.fSpeed, Param.fAcceleration, &m_pszCommand, &nLen);
			m_pEthernet->Client_Send(m_pszCommand, nLen);
		}
		else
		{
			//m_RobotUR.Command_Operate_MoveAxis(Position, Param, type);
		}

		delete result;
		result = NULL;
		Sleep(GetDlgItemInt(IDC_EDIT_INTERVAL));
	}
}


void CKSJRobotURDlg::WriteIni()
{
	int nTemp;
	nTemp = GetDlgItemInt(IDC_EDIT_PORT);
	KSJINI_SetInt(m_hKSJIni, _T("TCP_SERVER"), _T("PORT"), nTemp);
	CString strIP;
	((CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS_SERVER))->GetWindowText(strIP);
	KSJINI_SetString(m_hKSJIni, _T("TCP_SERVER"), _T("IP"), strIP);
}


void CKSJRobotURDlg::ReadIni()
{
	int nTemp;
	KSJINI_GetDWORD(m_hKSJIni, _T("TCP_SERVER"), _T("PORT"), 0, (DWORD*)&nTemp);
	SetDlgItemInt(IDC_EDIT_PORT, nTemp);
	TCHAR szTemp[32] = { 0 };
	KSJINI_GetString(m_hKSJIni, _T("TCP_SERVER"), _T("IP"), _T(""), szTemp);
	((CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS_SERVER))->SetWindowText(szTemp);
}

void CKSJRobotURDlg::OnBnClickedButtonClear()
{
	((CListBox*)GetDlgItem(IDC_LIST_COMMAND))->ResetContent();
}
//设置当前坐标
void CKSJRobotURDlg::SetAbsolutePosition(ROBOT_MOVE_TYPE MoveType, float fX, float fY, float fZ, float fRX, float fRY, float fRZ, float fSpeed, float fAcceleration, char **pszCmd, int *pnBytes)
{
	char strType[4][16] = { "movej", "movel", "movep", "movec" };
	float RX, RY, RZ;
	RX = fRX / 180 * 3.1415;
	RY = fRY / 180 * 3.1415;
	RZ = fRZ / 180 * 3.1415;
	sprintf(*pszCmd, "%s(p[%.3f/1000,%.3f/1000,%.3f/1000, %.3f, %.3f,%.3f],a=%.3f,v=%.3f)\n",
		strType[MoveType], fX, fY, fZ, RX, RY, RZ, fAcceleration, fSpeed);
	*pnBytes = strlen(*pszCmd);
}
//获取当前坐标
void CKSJRobotURDlg::GetAbsolutePosition(char *pszCommand, float *pfX, float *pfY, float *pfZ, float *pfRX, float *pfRY, float *pfRZ)
{
	double dTemp[6];
	for (int i = 0; i < 6; i++)
	{
		unsigned char* p = (unsigned char*)&dTemp[i];
		for (int j = 0; j < 8; j++)
		{
			p[7 - j] = pszCommand[i * 8 + j];
		}
	}

	*pfX = dTemp[0] * 1000;
	*pfY = dTemp[1] * 1000;
	*pfZ = dTemp[2] * 1000;
	*pfRX = dTemp[3] / 3.1415 * 180;
	*pfRY = dTemp[4] / 3.1415 * 180;
	*pfRZ = dTemp[5] / 3.1415 * 180;
}

void CKSJRobotURDlg::OnBnClickedButtonGetPosition()//获取当前位置
{
	BOOL bCheck = ((CButton*)GetDlgItem(IDC_CHECK_CONNECT))->GetCheck();
	if (!bCheck)
	{
		AfxMessageBox("请连接机器人! ");
		return;
	}

	float fX = 0, fY = 0, fZ = 0;
	float fRX = 0, fRY = 0, fRZ = 0;
	EnterCriticalSection(&m_cs);
	GetAbsolutePosition(m_szPose, &fX, &fY, &fZ, &fRX, &fRY, &fRZ);
	LeaveCriticalSection(&m_cs);
	TCHAR szPosition[128] = { 0 };
	sprintf(szPosition, "X：%.3f,Y：%.3f,Z：%.3f,RX：%.3f,RY：%.3f,RZ：%.3f", fX, fY, fZ, fRX, fRY, fRZ);
	SetDlgItemText(IDC_EDIT_POSE, szPosition);
}


void CKSJRobotURDlg::SaveCommand()
{
	int count = 0;
	count = ((CListBox*)GetDlgItem(IDC_LIST_COMMAND))->GetCount();
	CString SaveInformation;
	CString strTemp;
	CFile file;
	file.Open("Command.txt", CFile::modeCreate | CFile::modeWrite);

	for (int i = 0; i < count; i++)
	{
		((CListBox*)GetDlgItem(IDC_LIST_COMMAND))->GetText(i, strTemp);
		SaveInformation = strTemp + "\r\n";
		file.Write(SaveInformation, SaveInformation.GetLength());
	}

	file.Close();
}


void CKSJRobotURDlg::LoadCommand()
{
	CStdioFile file;
	file.Open("Command.txt", CFile::modeRead);
	CString strValue = "";
	int count = 0;
	while (file.ReadString(strValue))
	{
		count = ((CListBox*)GetDlgItem(IDC_LIST_COMMAND))->GetCount();
		((CListBox*)GetDlgItem(IDC_LIST_COMMAND))->InsertString(count, strValue.GetString());
	}

	file.Close();
}

void CKSJRobotURDlg::OnLbnSelchangeListCommand()
{
	CString   strText;
	((CListBox*)GetDlgItem(IDC_LIST_COMMAND))->GetText(((CListBox*)GetDlgItem(IDC_LIST_COMMAND))->GetCurSel(), strText);
	CString strParam[10];
	CStringArray* result = DivString(strText);
	for (int j = 0; j < 10; j++)
	{
		strParam[j] = result->GetAt(j);
	}

	for (int i = 0; i < 8;i++)
	{
		GetDlgItem(IDC_EDIT1 + i)->SetWindowText(strParam[i + 2]);
	}

	delete result;
	result = NULL;
}


////////////////////以下为xyz和rxyz的微调
void CKSJRobotURDlg::OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult)
{
	BOOL bCheck = ((CButton*)GetDlgItem(IDC_CHECK_CONNECT))->GetCheck();
	if (!bCheck)
	{
		AfxMessageBox("请连接机器人! ");
		return;
	}

	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	float fx = 0;
	TCHAR   szText[32];
	GetDlgItemText(IDC_EDIT1, szText, 32);
	fx = atof(szText) + 0.1 * pNMUpDown->iDelta;
	sprintf(szText, "%.1f", fx);
	SetDlgItemText(IDC_EDIT1, szText);
	*pResult = 0;
	ROBOT_MOVE_TYPE type;
	CComboBox    *pComboBox = NULL;
	pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_TYPE);
	type = (ROBOT_MOVE_TYPE)pComboBox->GetCurSel();
	TCHAR szPara[8][16];
	for (int i = 0; i < 8; i++)
	{
		GetDlgItem(IDC_EDIT1 + i)->GetWindowText(szPara[i], 16);
	}

	
	int nLen = 0;
	SetAbsolutePosition(type, atof(szPara[0]), atof(szPara[1]), atof(szPara[2]),
		atof(szPara[5]), atof(szPara[6]), atof(szPara[7]), atof(szPara[3]), atof(szPara[4]), &m_pszCommand, &nLen);
	m_pEthernet->Client_Send(m_pszCommand, nLen);
}


void CKSJRobotURDlg::OnDeltaposSpin2(NMHDR *pNMHDR, LRESULT *pResult)
{
	BOOL bCheck = ((CButton*)GetDlgItem(IDC_CHECK_CONNECT))->GetCheck();
	if (!bCheck)
	{
		AfxMessageBox("请连接机器人! ");
		return;
	}

	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	float fy = 0;
	TCHAR   szText[32];
	GetDlgItemText(IDC_EDIT2, szText, 32);
	fy = atof(szText) + 0.1 * pNMUpDown->iDelta;
	sprintf(szText, "%.1f", fy);
	SetDlgItemText(IDC_EDIT2, szText);
	*pResult = 0;

	ROBOT_MOVE_TYPE type;
	CComboBox    *pComboBox = NULL;
	pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_TYPE);
	type = (ROBOT_MOVE_TYPE)pComboBox->GetCurSel();

	TCHAR szPara[8][16];
	for (int i = 0; i < 8; i++)
	{
		GetDlgItem(IDC_EDIT1 + i)->GetWindowText(szPara[i], 16);
	}

	int nLen = 0;
	SetAbsolutePosition(type, atof(szPara[0]), atof(szPara[1]), atof(szPara[2]),
		atof(szPara[5]), atof(szPara[6]), atof(szPara[7]), atof(szPara[3]), atof(szPara[4]), &m_pszCommand, &nLen);
	m_pEthernet->Client_Send(m_pszCommand, nLen);
}


void CKSJRobotURDlg::OnDeltaposSpin3(NMHDR *pNMHDR, LRESULT *pResult)
{
	BOOL bCheck = ((CButton*)GetDlgItem(IDC_CHECK_CONNECT))->GetCheck();
	if (!bCheck)
	{
		AfxMessageBox("请连接机器人! ");
		return;
	}

	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	float fz = 0;
	TCHAR   szText[32];
	GetDlgItemText(IDC_EDIT3, szText, 32);
	fz = atof(szText) + 0.1 * pNMUpDown->iDelta;
	sprintf(szText, "%.1f", fz);
	SetDlgItemText(IDC_EDIT3, szText);
	*pResult = 0;

	ROBOT_MOVE_TYPE type;
	CComboBox    *pComboBox = NULL;
	pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_TYPE);
	type = (ROBOT_MOVE_TYPE)pComboBox->GetCurSel();

	TCHAR szPara[8][16];
	for (int i = 0; i < 8; i++)
	{
		GetDlgItem(IDC_EDIT1 + i)->GetWindowText(szPara[i], 16);
	}

	int nLen = 0;
	SetAbsolutePosition(type, atof(szPara[0]), atof(szPara[1]), atof(szPara[2]),
		atof(szPara[5]), atof(szPara[6]), atof(szPara[7]), atof(szPara[3]), atof(szPara[4]), &m_pszCommand, &nLen);
	m_pEthernet->Client_Send(m_pszCommand, nLen);
}


void CKSJRobotURDlg::OnDeltaposSpin4(NMHDR *pNMHDR, LRESULT *pResult)
{
	BOOL bCheck = ((CButton*)GetDlgItem(IDC_CHECK_CONNECT))->GetCheck();
	if (!bCheck)
	{
		AfxMessageBox("请连接机器人! ");
		return;
	}

	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	float frx = 0;
	TCHAR   szText[32];
	GetDlgItemText(IDC_EDIT6, szText, 32);
	frx = atof(szText) + pNMUpDown->iDelta;
	sprintf(szText, "%.1f", frx);
	SetDlgItemText(IDC_EDIT6, szText);
	*pResult = 0;

	ROBOT_MOVE_TYPE type;
	CComboBox    *pComboBox = NULL;
	pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_TYPE);
	type = (ROBOT_MOVE_TYPE)pComboBox->GetCurSel();

	TCHAR szPara[8][16];
	for (int i = 0; i < 8; i++)
	{
		GetDlgItem(IDC_EDIT1 + i)->GetWindowText(szPara[i], 16);
	}

	int nLen = 0;
	SetAbsolutePosition(type, atof(szPara[0]), atof(szPara[1]), atof(szPara[2]),
		atof(szPara[5]), atof(szPara[6]), atof(szPara[7]), atof(szPara[3]), atof(szPara[4]), &m_pszCommand, &nLen);
	m_pEthernet->Client_Send(m_pszCommand, nLen);
}


void CKSJRobotURDlg::OnDeltaposSpin5(NMHDR *pNMHDR, LRESULT *pResult)
{
	BOOL bCheck = ((CButton*)GetDlgItem(IDC_CHECK_CONNECT))->GetCheck();
	if (!bCheck)
	{
		AfxMessageBox("请连接机器人! ");
		return;
	}

	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	float fry = 0;
	TCHAR   szText[32];
	GetDlgItemText(IDC_EDIT7, szText, 32);
	fry = atof(szText) + pNMUpDown->iDelta;
	sprintf(szText, "%.1f", fry);
	SetDlgItemText(IDC_EDIT7, szText);
	*pResult = 0;

	ROBOT_MOVE_TYPE type;
	CComboBox    *pComboBox = NULL;
	pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_TYPE);
	type = (ROBOT_MOVE_TYPE)pComboBox->GetCurSel();

	TCHAR szPara[8][16];
	for (int i = 0; i < 8; i++)
	{
		GetDlgItem(IDC_EDIT1 + i)->GetWindowText(szPara[i], 16);
	}

	int nLen = 0;
	SetAbsolutePosition(type, atof(szPara[0]), atof(szPara[1]), atof(szPara[2]),
		atof(szPara[5]), atof(szPara[6]), atof(szPara[7]), atof(szPara[3]), atof(szPara[4]), &m_pszCommand, &nLen);
	m_pEthernet->Client_Send(m_pszCommand, nLen);
}


void CKSJRobotURDlg::OnDeltaposSpin6(NMHDR *pNMHDR, LRESULT *pResult)
{
	BOOL bCheck = ((CButton*)GetDlgItem(IDC_CHECK_CONNECT))->GetCheck();
	if (!bCheck)
	{
		AfxMessageBox("请连接机器人! ");
		return;
	}

	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	float frz = 0;
	TCHAR   szText[32];
	GetDlgItemText(IDC_EDIT8, szText, 32);
	frz = atof(szText) + pNMUpDown->iDelta;
	sprintf(szText, "%.1f", frz);
	SetDlgItemText(IDC_EDIT8, szText);
	*pResult = 0;

	ROBOT_MOVE_TYPE type;
	CComboBox    *pComboBox = NULL;
	pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_TYPE);
	type = (ROBOT_MOVE_TYPE)pComboBox->GetCurSel();

	TCHAR szPara[8][16];
	for (int i = 0; i < 8; i++)
	{
		GetDlgItem(IDC_EDIT1 + i)->GetWindowText(szPara[i], 16);
	}

	int nLen = 0;
	SetAbsolutePosition(type, atof(szPara[0]), atof(szPara[1]), atof(szPara[2]),
		atof(szPara[5]), atof(szPara[6]), atof(szPara[7]), atof(szPara[3]), atof(szPara[4]), &m_pszCommand, &nLen);
	m_pEthernet->Client_Send(m_pszCommand, nLen);
}


void CKSJRobotURDlg::OnBnClickedButtonExtcute()//移动机器人到当前设置好的坐标
{
	BOOL bCheck = ((CButton*)GetDlgItem(IDC_CHECK_CONNECT))->GetCheck();
	if (!bCheck)
	{
		AfxMessageBox("请连接机器人! ");
		return;
	}

	ROBOT_MOVE_TYPE type;
	CComboBox    *pComboBox = NULL;
	pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_TYPE);
	type = (ROBOT_MOVE_TYPE)pComboBox->GetCurSel();

	TCHAR szPara[8][16];
	for (int i = 0; i < 8; i++)
	{
		GetDlgItem(IDC_EDIT1 + i)->GetWindowText(szPara[i], 16);
	}

	int nLen = 0;
	SetAbsolutePosition(type, atof(szPara[0]), atof(szPara[1]), atof(szPara[2]),
		atof(szPara[5]), atof(szPara[6]), atof(szPara[7]), atof(szPara[3]), atof(szPara[4]), & m_pszCommand, &nLen);
	m_pEthernet->Client_Send(m_pszCommand, nLen);
}


void CKSJRobotURDlg::OnCbnSelchangeComboType()
{
	CComboBox    *pComboBox = NULL;
	pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_TYPE);
	int nIndex = pComboBox->GetCurSel();
	if (nIndex == 0)
	{
		GetDlgItem(IDC_STATIC_SPEED)->SetWindowText("°/s");
		GetDlgItem(IDC_STATIC_ACC)->SetWindowText("°/s2");
	}
	else
	{
		GetDlgItem(IDC_STATIC_SPEED)->SetWindowText("m/s");
		GetDlgItem(IDC_STATIC_ACC)->SetWindowText("m/s2");
	}
}

UINT WINAPI CKSJRobotURDlg::GetPoseThread(LPVOID pParam)
{
	CKSJRobotURDlg *pKSJDlg = (CKSJRobotURDlg*)pParam;
	pKSJDlg->GetPose();

	return 0;
}

void CKSJRobotURDlg::GetPose()
{
	char buff[1108];
	while (1)
	{
		if (WaitForSingleObject(m_hGetPoseExitEvent, 0) == 0)
		{
			break;
		}

		
		m_pEthernet->Client_Recv(buff, 1108, 1000);
		EnterCriticalSection(&m_cs);
		memcpy(m_szPose, buff + 444, 48);
		LeaveCriticalSection(&m_cs);
	}

}

void CKSJRobotURDlg::OnBnClickedCancel()
{
	BOOL bCheck = ((CButton*)GetDlgItem(IDC_CHECK_CONNECT))->GetCheck();
	if (bCheck)
	{
		AfxMessageBox("请断开服务器连接! ");
		return;
	}

	CDialogEx::OnCancel();
}
