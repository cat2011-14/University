#include "stdafx.h"
#include "Draw.h"

double Draw::scale_X(double x, CRect w, double xMin, double xMax)
{
	double x0 = -xMin;
	double W = 0.9*w.Width();
	int shift = int((w.Width() - W)) / 2;
	double xScale = W / (xMax - xMin);		//xScale-масштабный коэффициент по  оси х
	int X = shift + (int)(xScale * (x + x0));
	return X;
}
//масштабирование по оси y и сдвиг центра координат
double Draw::scale_Y(double y, CRect w, double yMax, double yMin)
{

	double y0 = -yMax;
	double H = 0.9*w.Height();
	int shift = int((w.Height() - H)) / 2;
	double yScale = H / (yMax - yMin);		//yScale-масштабный коэффициент по оси y
	int Y = shift - (int)(yScale * (y + y0));
	return Y;
}
//прорисовка  графика 
void Draw::DrawGraph(vector <double>mas, vector <double> step, CString str, double xMin, double xMax, double yMax, double yMin, int rad, COLORREF color, CDC* pMemDC, CRect w)
{
	CPen pen;
	pen.CreatePen(PS_SOLID, rad, color);
	CPen *oldpen;
	oldpen = pMemDC->SelectObject(&pen);
	pMemDC->SelectObject(&pen);
	pMemDC->MoveTo((int)scale_X(step[0], w, xMin, xMax), (int)scale_Y(mas[0], w, yMax, yMin));
	if (mas.size() > 2)
	{
		for (int i = 0; i < mas.size()-1; i++)
		{
			pMemDC->LineTo((int)scale_X(step[i], w, xMin, xMax), (int)scale_Y(mas[i], w, yMax, yMin));
		}
		pMemDC->TextOut((int)scale_X(step[mas.size() - 2], w, xMin, xMax) - 10, (int)scale_Y(mas[mas.size()-2], w, yMax, yMin), str);
	}
}
//прорисовка сетки
void Draw::DrawGrid(vector <double> &mas, double xMin, double xMax, double yMax, double yMin, CDC* pMemDC, CRect w)					//прорисовка сетки
{
	CPen penGray, *oldpen;
	penGray.CreatePen(PS_SOLID, 1, RGB(32, 32, 32));	//серый
	oldpen = pMemDC->SelectObject(&penGray);

	double step_x = (xMax - xMin) / NumberVertical;
	double step_y = (yMax - yMin) / NumberHorizontal;
	double x, y;
	x = 0;
	for (int i = 0; i <= (int)(abs(xMax) / step_x); i++)
	{
		pMemDC->MoveTo((int)scale_X(x, w, xMin, xMax), (int)scale_Y(yMin, w, yMax, yMin));
		pMemDC->LineTo((int)scale_X(x, w, xMin, xMax), (int)scale_Y(yMax, w, yMax, yMin));
		x += step_x;
	}
	x = 0;
	for (int i = 0; i <= (int)(abs(xMin) / step_x); i++)
	{
		x -= step_x;
		pMemDC->MoveTo((int)scale_X(x, w, xMin, xMax), (int)scale_Y(yMin, w, yMax, yMin));
		pMemDC->LineTo((int)scale_X(x, w, xMin, xMax), (int)scale_Y(yMax, w, yMax, yMin));
	}
	y = 0;
	for (int i = 0; i <= (int)(abs(yMax) / step_y); i++)
	{
		pMemDC->MoveTo((int)scale_X(xMin, w, xMin, xMax), (int)scale_Y(y, w, yMax, yMin));
		pMemDC->LineTo((int)scale_X(xMax, w, xMin, xMax), (int)scale_Y(y, w, yMax, yMin));
		y += step_y;
	}
	y = 0;
	for (int i = 0; i <= (int)(abs(yMin) / step_y); i++)
	{
		y -= step_y;
		pMemDC->MoveTo((int)scale_X(xMin, w, xMin, xMax), (int)scale_Y(y, w, yMax, yMin));
		pMemDC->LineTo((int)scale_X(xMax, w, xMin, xMax), (int)scale_Y(y, w, yMax, yMin));
	}
}
void Draw::SetFont(int size, int angle, CWnd* frameWnd)
{
	HWND hwd = frameWnd->GetSafeHwnd();
	HDC hDC = GetDC(hwd);
	int nHeight = -MulDiv(size, GetDeviceCaps(hDC, LOGPIXELSY), 72);
	Font.CreateFont(
		nHeight, 			//высота шрифта
		0, 					//средняя ширина символа
		angle * 10,					//угол наклона
		0,			//угол ориентации базисной линии
		FW_NORMAL,			//толщина шрифта
		FALSE,				//описатель параметра курсивного шрифта
		FALSE,				//описатель параметра подчеркивания
		0,					//описатель параметра зачеркивания
		ANSI_CHARSET,		//идентификатор наборов символа
		OUT_DEFAULT_PRECIS,	//точность вывода
		CLIP_DEFAULT_PRECIS, //точность отсечения
		DEFAULT_QUALITY,	//качество вывода
		DEFAULT_PITCH | FF_SWISS,	//шаг между символами шрифта и семейство
		_T("Arial")	//имя гарнитуры шрифта
		);
}

//прорисовка осей OX и OY 
void Draw::DrawAxis(vector <double> &mas, double xMin, double xMax, double yMax, double yMin, CWnd* frameWnd, CDC* pMemDC, CRect w)
{
	double x = 0, y = 0;
	CPen penWhite, *oldpen;
	penWhite.CreatePen(PS_SOLID, 2, RGB(255,255,255));
	oldpen = pMemDC->SelectObject(&penWhite);
	//ось ОУ
	pMemDC->MoveTo((int)scale_X(x, w, xMin, xMax), (int)scale_Y(yMin, w, yMax, yMin));
	pMemDC->LineTo((int)scale_X(x, w, xMin, xMax), (int)scale_Y(yMax, w, yMax, yMin) - 5);

	//стрелка
	POINT * polygon = new POINT[4];
	polygon[0].x = scale_X(x, w, xMin, xMax);
	polygon[0].y = scale_Y(yMax, w, yMax, yMin) - 5;

	polygon[1].x = scale_X(x, w, xMin, xMax) - 5;
	polygon[1].y = scale_Y(yMax, w, yMax, yMin);

	polygon[2].x = scale_X(x, w, xMin, xMax);
	polygon[2].y = scale_Y(yMax, w, yMax, yMin) - 15;

	polygon[3].x = scale_X(x, w, xMin, xMax) + 5;
	polygon[3].y = scale_Y(yMax, w, yMax, yMin);
	CBrush brush(RGB(255, 255, 255));
	pMemDC->SelectObject(brush);
	pMemDC->Polygon(polygon, 4);
	delete[]polygon;

	//ось ОХ
	pMemDC->MoveTo((int)scale_X(xMin, w, xMin, xMax), (int)scale_Y(y, w, yMax, yMin));
	pMemDC->LineTo((int)scale_X(xMax, w, xMin, xMax) + 5, (int)scale_Y(y, w, yMax, yMin));

	//стрелка
	polygon = new POINT[4];
	polygon[0].x = scale_X(xMax, w, xMin, xMax) + 5;
	polygon[0].y = scale_Y(y, w, yMax, yMin);

	polygon[1].x = scale_X(xMax, w, xMin, xMax);
	polygon[1].y = scale_Y(y, w, yMax, yMin) - 5;

	polygon[2].x = scale_X(xMax, w, xMin, xMax) + 15;
	polygon[2].y = scale_Y(y, w, yMax, yMin);

	polygon[3].x = scale_X(xMax, w, xMin, xMax);
	polygon[3].y = scale_Y(y, w, yMax, yMin) + 5;

	pMemDC->Polygon(polygon, 4);
	delete[]polygon;

	int FontSize = 10;
	SetFont(FontSize, 0, frameWnd);
	pMemDC->SetTextAlign(TA_CENTER);
	pMemDC->SelectObject(&Font);
	CString Str;
	Str = "U";
	pMemDC->TextOut((int)scale_X(xMax, w, xMin, xMax), (int)scale_Y(0, w, yMax, yMin) - 25, Str);
	Font.DeleteObject();
	SetFont(14, 0, frameWnd);
	pMemDC->SelectObject(&Font);
	Str = "I";
	pMemDC->TextOut((int)scale_X(0, w, xMin, xMax) - 10, (int)scale_Y(yMax, w, yMax, yMin) + 20, Str);
	Font.DeleteObject();
}
//ставим значения на осях
void Draw::DrawTextAxis(vector <double> &mas, double xMin, double xMax, double yMax, double yMin, CDC* pMemDC, CRect w)
{
	pMemDC->SetTextColor(RGB(255, 255, 255));
	CFont Font;
	Font.CreateFont(
		14, 			
		0, 				
		0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
		_T("Arial")
		);

	double step_x = (xMax - xMin) / NumberVertical;
	double step_y = (yMax - yMin) / NumberHorizontal;

	pMemDC->FillSolidRect(&w, RGB(0, 0, 0)); //закрашенный в черный прямоугольник
	pMemDC->SelectObject(&Font);
	double x, y;
	x = 0;
	for (int i = 0; i <= (int)(abs(xMax) / step_x); i++)
	{
		CString xStr;
		xStr.Format(_T("%10.1f"), x);
		pMemDC->TextOutW((int)scale_X(x, w, xMin, xMax) - 30, (int)scale_Y(0, w, yMax, yMin), xStr);
		x += step_x;
	}
	x = 0;
	for (int i = 0; i <= (int)(abs(xMin) / step_x); i++)
	{
		CString xStr;
		xStr.Format(_T("%10.1f"), x);
		pMemDC->TextOutW((int)scale_X(x, w, xMin, xMax) - 30, (int)scale_Y(0, w, yMax, yMin), xStr);
		x -= step_x;
	}
	y = 0;
	for (int i = 0; i <= (int)(abs(yMax) / step_y); i++)
	{
		CString yStr;
		yStr.Format(_T("%10.3f"), y);
		pMemDC->TextOutW((int)scale_X(xMin, w, xMin, xMax), (int)scale_Y(y, w, yMax, yMin) - 7, yStr);
		y += step_y;
	}
	y = 0;
	for (int i = 0; i <= (int)(abs(yMin) / step_y); i++)
	{
		CString yStr;
		yStr.Format(_T("%10.3f"), y);
		pMemDC->TextOutW((int)scale_X(xMin, w, xMin, xMax), (int)scale_Y(y, w, yMax, yMin) - 7, yStr);
		y -= step_y;
	}
}
//рисуем линию
void Draw::DrawLine(double x1, double y1, double x2, double y2, double xMin, double xMax, double yMin, double yMax, int rad, COLORREF color, CDC* pMemDC, CRect w)
{
	CPen pen;
	pen.CreatePen(PS_SOLID, rad, color);
	CPen *oldpen;
	oldpen = pMemDC->SelectObject(&pen);

	pMemDC->SelectObject(&pen);
	pMemDC->MoveTo((int)scale_X(x1, w, xMin, xMax), (int)scale_Y(y1, w, yMax, yMin));
	pMemDC->LineTo((int)scale_X(x1, w, xMin, xMax), (int)scale_Y(y1, w, yMax, yMin));
	pMemDC->LineTo((int)scale_X(x2, w, xMin, xMax), (int)scale_Y(y2, w, yMax, yMin));
}
void Draw::DrawCircle(double xc, double yc, double rc, double xMin, double xMax, double yMin, double yMax, CPen &pen, CDC* pMemDC, CRect w)
{
	CPen *oldpen;
	oldpen = pMemDC->SelectObject(&pen);
	CBrush BlackBrush;
	BlackBrush.CreateSolidBrush(RGB(0, 0, 0));
	pMemDC->SelectObject(&BlackBrush);
	pMemDC->SelectObject(&pen);
	pMemDC->Ellipse(scale_X(xc - rc, w, xMin, xMax), scale_Y(yc - rc, w, yMin, yMax), scale_X(xc + rc, w, xMin, xMax), scale_Y(yc + rc, w, yMin, yMax));
}
void Draw::DrawAll(CDC* pMemDC, CRect w)
{
	pMemDC->FillSolidRect(&w, RGB(0, 0, 0)); //закрашенный в черный прямоугольник
}
void Draw::DrawTriangle(double x1, double y1, double x2, double y2, double x3, double y3, double xMin, double xMax, double yMin, double yMax, CPen &pen, CDC* pMemDC, CRect w)
{
	CPen *oldpen;
	oldpen = pMemDC->SelectObject(&pen);
	pMemDC->SelectObject(&pen);
	pMemDC->MoveTo((int)scale_X(x1, w, xMin, xMax), (int)scale_Y(y1, w, yMax, yMin));
	pMemDC->LineTo((int)scale_X(x2, w, xMin, xMax), (int)scale_Y(y2, w, yMax, yMin));
	pMemDC->LineTo((int)scale_X(x3, w, xMin, xMax), (int)scale_Y(y3, w, yMax, yMin));
	pMemDC->LineTo((int)scale_X(x1, w, xMin, xMax), (int)scale_Y(y1, w, yMax, yMin));
}
void Draw::DrawPoints(double x, double y, int rad, double xMin, double xMax, double yMin, double yMax, COLORREF color, CDC* pMemDC, CRect w)
{
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, color);
	CPen *oldpen;
	oldpen = pMemDC->SelectObject(&pen);
	CBrush BlackBrush;
	BlackBrush.CreateSolidBrush(color);
	pMemDC->SelectObject(&BlackBrush);
	pMemDC->SelectObject(&pen);
	pMemDC->Ellipse(scale_X(x, w, xMin, xMax) - rad, scale_Y(y, w, yMax, yMin) - rad, scale_X(x, w, xMin, xMax) + rad, scale_Y(y, w, yMax, yMin) + rad);
}
void Draw::DrawGraphGridAxis(vector<double>x, vector<double>y1, vector<double>y2, double xMin, double xMax, int nWidth, COLORREF crColor1, COLORREF crColor2, CWnd* frameWnd, CDC* pMemDC, CRect w)
{
	double yMin, yMax, yMin1, yMax1, yMin2, yMax2;
	MaxMin(y1, yMax1, yMin1);
	MaxMin(y2, yMax2, yMin2);
	if (yMax1 > yMax2)yMax = yMax1;
	else yMax = yMax2;
	if (yMin1 < yMin2)yMin = yMin1;
	else yMin = yMin2;
	if (yMin > 0)yMin = 0;

	DrawTextAxis(x, xMin, xMax, yMax, yMin, pMemDC, w);				//значения на осях
	DrawGrid(x, xMin, xMax, yMax, yMin, pMemDC, w);					//прорисовка сетки
	DrawAxis(x, xMin, xMax, yMax, yMin, frameWnd, pMemDC, w);					//прорисовка осей
	DrawGraph(y1, x, L"I_a", xMin, xMax, yMax, yMin, nWidth, crColor1, pMemDC, w);				//прорисовка сигнала
	DrawGraph(y2, x,  L"I_g", xMin, xMax, yMax, yMin, nWidth, crColor2, pMemDC, w);				//прорисовка сигнала
}
void Draw::MaxMin(vector <double> &mas, double &Max_mas, double &Min_mas)
{
	int imin = 0; int imax = 0;
	for (int i = 0; i < mas.size(); i++)
	{
		if (mas[i] < mas[imin]) imin = i;
		if (mas[i] > mas[imax]) imax = i;
	}
	Max_mas = mas[imax];
	Min_mas = mas[imin];
}
void Draw::FilledWithAColorTriangle(vector<MyTriangle> tri, vector<Point>vertex, double xMin, double xMax, double yMin, double yMax, CDC* pMemDC, CRect w)
{
	POINT * polygon = new POINT[4];

	CPen pen = CPen(0, 1, RGB(0, 0, 0));
	pMemDC->SelectObject(pen);

	double min, max;
	int imin = 0; int imax = 0;
	for (int i = 0; i < vertex.size(); i++)
	{
		if (vertex[i].z < vertex[imin].z) imin = i;
		if (vertex[i].z > vertex[imax].z) imax = i;
	}
	max = vertex[imax].z;
	min = vertex[imin].z;

	for (int i = 0; i < tri.size(); i++)
	{
		polygon[0].x = scale_X(vertex[tri[i].A].x, w, xMin, xMax);
		polygon[0].y = scale_Y(vertex[tri[i].A].y, w, yMax, yMin);

		polygon[1].x = scale_X(vertex[tri[i].B].x, w, xMin, xMax);
		polygon[1].y = scale_Y(vertex[tri[i].B].y, w, yMax, yMin);

		polygon[2].x = scale_X(vertex[tri[i].C].x, w, xMin, xMax);
		polygon[2].y = scale_Y(vertex[tri[i].C].y, w, yMax, yMin);

		polygon[3].x = scale_X(vertex[tri[i].A].x, w, xMin, xMax);
		polygon[3].y = scale_Y(vertex[tri[i].A].y, w, yMax, yMin);

		double color = vertex[tri[i].A].z + vertex[tri[i].B].z + vertex[tri[i].C].z;
		color /= 3.;
		color -= min;
		color /= (max - min);

		CBrush brush(RGB(255 * color, 0, 255 * (1 - color)));
		pMemDC->SelectObject(brush);
		pMemDC->Polygon(polygon, 4);
	}
	delete[]polygon;
}