
// DipoleFDTD.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������


// CDipoleFDTDApp:
// � ���������� ������� ������ ��. DipoleFDTD.cpp
//

class CDipoleFDTDApp : public CWinApp
{
public:
	CDipoleFDTDApp();

// ���������������
public:
	virtual BOOL InitInstance();

// ����������

	DECLARE_MESSAGE_MAP()
};

extern CDipoleFDTDApp theApp;