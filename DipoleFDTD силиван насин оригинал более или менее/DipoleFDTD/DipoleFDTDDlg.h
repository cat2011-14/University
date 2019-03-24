
// DipoleFDTDDlg.h : файл заголовка
//

#pragma once

#include "Draw.h"
#include "InitializingTheDrawingWindow.h"
#include "Triangulation.h"
#define _USE_MATH_DEFINES			// для M_PI


#include <math.h>

//#define IE 60
//#define JE 60

//#define IE 150
//#define JE 150

// диалоговое окно CDipoleFDTDDlg
class CDipoleFDTDDlg : public CDialogEx
{
	// Создание
public:
	CDipoleFDTDDlg(CWnd* pParent = NULL);	// стандартный конструктор

	// Данные диалогового окна
	enum { IDD = IDD_DIPOLEFDTD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


	// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	Draw draw;
	InitializingTheDrawingWindow win;
	Triangulation triangulation;
	void Solve();
	afx_msg void OnBnClickedSolve();

	int IE = 101;
	int JE = 101;

	//void FindRadiattionPattern(double(&massE)[IE][JE]);

	void FindRadiattionPattern(vector<vector <double>>massHx, vector<vector <double>>massHy, vector<vector <double>>massEz);
	bool InsideTheTriangle(Point p1, Point p2, Point p3, Point p);
};
