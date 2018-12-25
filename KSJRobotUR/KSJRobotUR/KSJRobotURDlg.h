
// KSJRobotURDlg.h : ͷ�ļ�
//
#include "Ethernet.h"

#pragma once
#define WM_FAIL WM_USER + 100

// CKSJRobotURDlg �Ի���
class CKSJRobotURDlg : public CDialogEx
{
// ����
public:
	CKSJRobotURDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CKSJRobotURDlg();
// �Ի�������
	enum { IDD = IDD_KSJROBOTUR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

private:
	static UINT WINAPI GetPoseThread(LPVOID pParam);//�̲߳��϶�ȡ�����˷��ص����ݰ�
	void GetPose();
	void GetAbsolutePosition(char *pszCommand, float *pfX, float *pfY, float *pfZ, float *pfRX, float *pfRY, float *pfRZ);
	void SetAbsolutePosition(ROBOT_MOVE_TYPE MoveType, float fX, float fY, float fZ, float fRX, float fRY, float fRZ, float fSpeed, float fAcceleration, char **pszCmd, int *pnBytes);
	HANDLE m_hGetPoseExitEvent;
	HANDLE m_hGetPoseThread;
	CEthernet* m_pEthernet;//����ͨѶ��
	HANDLE m_hKSJIni;
	TCHAR *m_pszCommand;
	char m_szMsg[32];
	char m_szPose[48];//���������6��λ�����������
	CRITICAL_SECTION m_cs;//�ٽ�����
// ʵ��
protected:
	HICON m_hIcon;
	FD_SET m_SocketSet;
	// ���ɵ���Ϣӳ�亯��
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
