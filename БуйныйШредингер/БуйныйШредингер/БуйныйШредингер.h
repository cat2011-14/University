
// ���������������.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������


// C���������������App:
// � ���������� ������� ������ ��. ���������������.cpp
//

class C���������������App : public CWinApp
{
public:
	C���������������App();

// ���������������
public:
	virtual BOOL InitInstance();

// ����������

	DECLARE_MESSAGE_MAP()
};

extern C���������������App theApp;