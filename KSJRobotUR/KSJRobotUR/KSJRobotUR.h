
// KSJRobotUR.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CKSJRobotURApp: 
// �йش����ʵ�֣������ KSJRobotUR.cpp
//

class CKSJRobotURApp : public CWinApp
{
public:
	CKSJRobotURApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CKSJRobotURApp theApp;