#include "���������������.h"
#include "stdafx.h"
#include "crazyw.h"

#include<math.h>

// CrazyW

IMPLEMENT_DYNAMIC(CrazyW, CStatic)
ULONG_PTR tokenCrazy;
CrazyW::CrazyW()
{
	GdiplusStartupInput input;
	Status s;
	s = GdiplusStartup(&tokenCrazy, &input, NULL);
	if (s != Ok) {
		MessageBox(L"ERROR", L"Message", MB_OK);
	}
	Xmin = -1.0;
	Xmax = 1.0;
	Ymin = 0.0;
	Ymax = 30.0;
}

CrazyW::~CrazyW()
{
	������.clear();
	GdiplusShutdown(tokenCrazy);
}


BEGIN_MESSAGE_MAP(CrazyW, CStatic)
	//	ON_WM_TIMER()
END_MESSAGE_MAP()



// ����������� ��������� CrazyW

void CrazyW::���������������(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	Kx = fabs((double)(lpDrawItemStruct->rcItem.right - lpDrawItemStruct->rcItem.left)) / (Xmax - Xmin);
	Ky = -fabs((double)(lpDrawItemStruct->rcItem.top - lpDrawItemStruct->rcItem.bottom)) / (Ymax - Ymin);
}

REAL CrazyW::KoordX(double X)
{
	return (REAL)(Kx*(X - Xmin));
}

REAL CrazyW::KoordY(double Y)
{
	return (REAL)(Ky*(Y - Ymax));
}

void CrazyW::���������(vector<double>������, double R0max)
{
	Xmax = R0max;
	Xmin = -R0max;
	vector<double>::iterator ��������������;
	�������������� = max_element(������.begin(), ������.end());
	double Max = *��������������;
	Ymax = Max;
	�������������� = min_element(������.begin(), ������.end());
	double Min = *��������������;
	Ymin = Min;
	������.clear();
	for (int i = 0; i<(������.size()); i++)
	{
		PointF ����������((REAL)(Xmin + (double)i*(Xmax - Xmin) / (������.size() - 1)), (REAL)������[i]);
		������.push_back(����������);
	}
	Invalidate(false);
}

void CrazyW::����������(Graphics &��������)
{
	Pen osi(Color::White, 0.0001f);

	��������.DrawLine(&osi, KoordX(Xmin), KoordY(0.0), KoordX(Xmax), KoordY(0.0));
	��������.DrawLine(&osi, KoordX(0.0), KoordY(Ymin), KoordX(0.0), KoordY(Ymax));

	FontFamily fontFamily(L"Arial");
	Gdiplus::Font font(&fontFamily, 8);
	SolidBrush brush(Color(255, 255, 255));
	CString str;
	FontFamily fontFamily1(L"Arial Black");
	Gdiplus::Font font1(&fontFamily1, 10);
	str.Format(_T("|W|"));
	PointF PtY(KoordX(0.04*(Xmax - Xmin)), KoordY(0.95*Ymax));
	��������.DrawString(str, str.GetLength(), &font1, PtY, &brush);
	str.Format(_T("R"));
	PointF PtX(KoordX(0.97*Xmax), KoordY(0.11*(Ymax - Ymin)));
	��������.DrawString(str, str.GetLength(), &font1, PtX, &brush);
	for (double i = Ymin; i<Ymax; i += (Ymax - Ymin) / 10.0)
	{
		PointF pt(KoordX(0.0f), KoordY(i + 0.035*(Ymax - Ymin)));
		str.Format(_T("%.3f"), i);
		if (fabs(i)>(Ymax - Ymin) / 20) ��������.DrawString(str, str.GetLength(), &font, pt, &brush);
	}
	for (double j = Xmin; j<Xmax; j += (Xmax - Xmin) / 10.0)
	{
		PointF pt(KoordX(j), KoordY(0.035*(Ymax - Ymin)));
		str.Format(_T("%.3f"), j);
		if (fabs(j)>(Xmax - Xmin) / 20) ��������.DrawString(str, str.GetLength(), &font, pt, &brush);
	}
	PointF pt(KoordX(0.0f), KoordY(0.035*(Ymax - Ymin)));
	str.Format(_T("%.3f"), 0.0f);
	��������.DrawString(str, str.GetLength(), &font, pt, &brush);
}

void CrazyW::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	Graphics graphic(lpDrawItemStruct->hDC);
	Bitmap memory(lpDrawItemStruct->rcItem.right + 1, lpDrawItemStruct->rcItem.bottom + 1, &graphic);
	Graphics bmp(&memory);

	Pen PenWhite(Color::White, 1);
	//Pen PenBlue(Color::Blue, 4);

	bmp.Clear(Color::Black);

	���������������(lpDrawItemStruct);

	����������(bmp);//���, �� ������� � ������ �������

	if (������.size()>1)//��� ������
	{
		for (int i = 0; i<(������.size() - 1); i++)
		{
			bmp.DrawLine(&PenWhite, KoordX(������[i].X), KoordY(������[i].Y), KoordX(������[i + 1].X), KoordY(������[i + 1].Y));
		}
	}

	graphic.DrawImage(&memory, 0, 0);
	// TODO:  �������� �������� ��� ��� ����������� ���������� ��������
}
