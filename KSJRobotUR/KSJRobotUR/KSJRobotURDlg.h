
// KSJRobotURDlg.h : 头文件
//
#include "Ethernet.h"

#pragma once
#define WM_FAIL WM_USER + 100

// CKSJRobotURDlg 对话框
class CKSJRobotURDlg : public CDialogEx
{
// 构造
public:
	CKSJRobotURDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CKSJRobotURDlg();
// 对话框数据
	enum { IDD = IDD_KSJROBOTUR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private:
	static UINT WINAPI GetPoseThread(LPVOID pParam);//线程不断读取机器人返回的数据包
	void GetPose();
	void GetAbsolutePosition(char *pszCommand, float *pfX, float *pfY, float *pfZ, float *pfRX, float *pfRY, float *pfRZ);
	void SetAbsolutePosition(ROBOT_MOVE_TYPE MoveType, float fX, float fY, float fZ, float fRX, float fRY, float fRZ, float fSpeed, float fAcceleration, char **pszCmd, int *pnBytes);
	HANDLE m_hGetPoseExitEvent;
	HANDLE m_hGetPoseThread;
	CEthernet* m_pEthernet;//网络通讯类
	HANDLE m_hKSJIni;
	TCHAR *m_pszCommand;
	char m_szMsg[32];
	char m_szPose[48];//保存机器人6个位置坐标的数组
	CRITICAL_SECTION m_cs;//临界区锁
// 实现
protected:
	HICON m_hIcon;
	FD_SET m_SocketSet;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheckConnect();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonRun();
	void WriteIni();
	void ReadIni();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonGetPosition();
	void SaveCommand();
	void LoadCommand();
	afx_msg void OnLbnSelchangeListCommand();
	afx_msg void OnBnClickedButtonChench();

	afx_msg void OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin5(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin6(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonExtcute();
	afx_msg void OnCbnSelchangeComboType();
	afx_msg void OnBnClickedCheckListen();
	afx_msg LRESULT OnMsgFail(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedCancel();
};
