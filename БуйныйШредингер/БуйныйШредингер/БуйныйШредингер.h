
// ЅуйныйЎредингер.h : главный файл заголовка дл€ приложени€ PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включени€ этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CЅуйныйЎредингерApp:
// ќ реализации данного класса см. ЅуйныйЎредингер.cpp
//

class CЅуйныйЎредингерApp : public CWinApp
{
public:
	CЅуйныйЎредингерApp();

// ѕереопределение
public:
	virtual BOOL InitInstance();

// –еализаци€

	DECLARE_MESSAGE_MAP()
};

extern CЅуйныйЎредингерApp theApp;