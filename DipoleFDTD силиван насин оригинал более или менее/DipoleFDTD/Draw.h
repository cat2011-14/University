#pragma once
#include <vector>
#include "Triangulation.h"
using namespace std;

class Draw
{
	double scale_X(double x, CRect w,double xMin, double xMax);						//масштабирование по оси x и сдвиг центра координат
	double scale_Y(double y, CRect w, double yMax, double yMin);		//масштабирование по оси y и сдвиг центра координат
	int NumberVertical=10;		//число вертикальных линий
	int NumberHorizontal=5;		//число горизонтальных линий
	void MaxMin(vector <double> &mas, double &Max_mas, double &Min_mas);
	CFont Font;
	void SetFont(int size, int angle, CWnd* frameWnd);
public:

	//прорисовка графика сигнала
	void DrawGraph(vector <double> mas, vector <double> step, CString str, double xMin, double xMax, double yMax, double yMin, int rad, COLORREF color, CDC* pMemDC, CRect w);
	//прорисовка сетки
	void DrawGrid(vector <double> &mas, double xMin, double xMax, double yMax, double yMin, CDC* pMemDC, CRect w);
	//прорисовка осей OX и OY 
	void DrawAxis(vector <double> &mas, double xMin, double xMax, double yMax, double yMin, CWnd* frameWnd, CDC* pMemDC, CRect w);
	//ставим значения на осях
	void DrawTextAxis(vector <double> &mas, double xMin, double xMax, double yMax, double yMin, CDC* pMemDC, CRect w);
	//рисуем линию
	void DrawLine(double x1, double y1, double x2, double y2, double xMin, double xMax, double yMin, double yMax, int rad, COLORREF color, CDC* pMemDC, CRect w);
	//рисуем круг
	void DrawCircle(double xc, double yc, double xMin, double xMax, double yMin, double yMax, double rc, CPen &pen, CDC* pMemDC, CRect w);
	//закрасить все
	void DrawAll(CDC* pMemDC, CRect w);
	//рисуем треугольник
	void DrawTriangle(double x1, double y1, double x2, double y2, double x3, double y3, double xMin, double xMax, double yMin, double yMax, CPen &pen, CDC* pMemDC, CRect w);
	void DrawPoints(double x, double y, int rad, double xMin, double xMax, double yMin, double yMax, COLORREF color, CDC* pMemDC, CRect w);
	void DrawGraphGridAxis(vector<double>x, vector<double>y1, vector<double>y2, double xMin, double xMax, int nWidth, COLORREF crColor1, COLORREF crColor2, CWnd* frameWnd, CDC* pMemDC, CRect w);
	void FilledWithAColorTriangle(vector<MyTriangle> tri, vector<Point>vertex, double xMin, double xMax, double yMin, double yMax, CDC* pMemDC, CRect w);
};