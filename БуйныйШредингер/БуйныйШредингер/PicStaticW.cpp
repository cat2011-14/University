#include "stdafx.h"
#include "БуйныйШредингер.h"
#include "PicStaticW.h"

#include<math.h>

// PicStaticW

IMPLEMENT_DYNAMIC(PicStaticW, CStatic)
ULONG_PTR tokenStaticW;
PicStaticW::PicStaticW()
{
	GdiplusStartupInput input;
	Status s;
	s = GdiplusStartup(&tokenStaticW, &input, NULL);
	if (s != Ok) {
		MessageBox(L"ERROR", L"Message", MB_OK);
	}
	Xmin = -1.0;
	Xmax = 1.0;
	Ymin = 0.0;
	Ymax = 30.0;
}

PicStaticW::~PicStaticW()
{
	GdiplusShutdown(tokenStaticW);
}


BEGIN_MESSAGE_MAP(PicStaticW, CStatic)
END_MESSAGE_MAP()



// обработчики сообщений PicStaticW

void PicStaticW::Масштабирование(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	Kx = fabs((double)(lpDrawItemStruct->rcItem.right - lpDrawItemStruct->rcItem.left)) / (Xmax - Xmin);
	Ky = -fabs((double)(lpDrawItemStruct->rcItem.top - lpDrawItemStruct->rcItem.bottom)) / (Ymax - Ymin);
}

REAL PicStaticW::KoordX(double X)
{
	return (REAL)(Kx*(X - Xmin));
}

REAL PicStaticW::KoordY(double Y)
{
	return (REAL)(Ky*(Y - Ymax));
}

void PicStaticW::Параметры(vector<double>Данные, double R0max)
{
	Xmax = R0max;
	Xmin = -R0max;
	vector<double>::iterator ПамятьИтератор;
	ПамятьИтератор = max_element(Данные.begin(), Данные.end());
	double Max = *ПамятьИтератор;
	Ymax = Max;
	ПамятьИтератор = min_element(Данные.begin(), Данные.end());
	double Min = *ПамятьИтератор;
	Ymin = Min;

	for (int i = 0; i<(Данные.size()); i++)
	{
		PointF БуферТочка((REAL)(Xmin + (double)i*(Xmax - Xmin) / (Данные.size() - 1)), (REAL)Данные[i]);
		Память.push_back(БуферТочка);
	}
	Invalidate();
}

void PicStaticW::Прорисовка(Graphics &БитКарта)
{
	Pen osi(Color::White, 0.0001f);

	БитКарта.DrawLine(&osi, KoordX(Xmin), KoordY(0.0), KoordX(Xmax), KoordY(0.0));
	БитКарта.DrawLine(&osi, KoordX(0.0), KoordY(Ymin), KoordX(0.0), KoordY(Ymax));

	FontFamily fontFamily(L"Arial");
	Gdiplus::Font font(&fontFamily, 8);
	SolidBrush brush(Color(255, 255, 255));
	CString str;
	FontFamily fontFamily1(L"Arial Black");
	Gdiplus::Font font1(&fontFamily1, 10);
	str.Format(_T("|W|"));
	PointF PtY(KoordX(0.04*(Xmax - Xmin)), KoordY(0.95*Ymax));
	БитКарта.DrawString(str, str.GetLength(), &font1, PtY, &brush);
	str.Format(_T("R"));
	PointF PtX(KoordX(0.97*Xmax), KoordY(0.11*(Ymax - Ymin)));
	БитКарта.DrawString(str, str.GetLength(), &font1, PtX, &brush);
	for (double i = Ymin; i<Ymax; i += (Ymax - Ymin) / 10.0)
	{
		PointF pt(KoordX(0.0f), KoordY(i + 0.035*(Ymax - Ymin)));
		str.Format(_T("%.3f"), i);
		if (fabs(i)>(Ymax - Ymin) / 20) БитКарта.DrawString(str, str.GetLength(), &font, pt, &brush);
	}
	for (double j = Xmin; j<Xmax; j += (Xmax - Xmin) / 10.0)
	{
		PointF pt(KoordX(j), KoordY(0.035*(Ymax - Ymin)));
		str.Format(_T("%.3f"), j);
		if (fabs(j)>(Xmax - Xmin) / 20) БитКарта.DrawString(str, str.GetLength(), &font, pt, &brush);
	}
	PointF pt(KoordX(0.0f), KoordY(0.035*(Ymax - Ymin)));
	str.Format(_T("%.3f"), 0.0f);
	БитКарта.DrawString(str, str.GetLength(), &font, pt, &brush);
}


void PicStaticW::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	Graphics graphic(lpDrawItemStruct->hDC);
	Bitmap memory(lpDrawItemStruct->rcItem.right + 1, lpDrawItemStruct->rcItem.bottom + 1, &graphic);
	Graphics bmp(&memory);

	Pen PenWhite(Color::White, 1);
	//Pen PenBlue(Color::Blue, 4);

	bmp.Clear(Color::Black);

	Масштабирование(lpDrawItemStruct);

	Прорисовка(bmp);//Оси, их подписи и прочие шаблоны

	if (Память.size()>1)//Сам График
	{
		for (int i = 0; i<(Память.size() - 1); i++)
		{
			bmp.DrawLine(&PenWhite, KoordX(Память[i].X), KoordY(Память[i].Y), KoordX(Память[i + 1].X), KoordY(Память[i + 1].Y));
		}
		Память.clear();
	}

	graphic.DrawImage(&memory, 0, 0);
	// TODO:  Добавьте исходный код для отображения указанного элемента
}
