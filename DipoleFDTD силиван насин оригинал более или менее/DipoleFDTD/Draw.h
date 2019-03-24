#pragma once
#include <vector>
#include "Triangulation.h"
using namespace std;

class Draw
{
	double scale_X(double x, CRect w,double xMin, double xMax);						//��������������� �� ��� x � ����� ������ ���������
	double scale_Y(double y, CRect w, double yMax, double yMin);		//��������������� �� ��� y � ����� ������ ���������
	int NumberVertical=10;		//����� ������������ �����
	int NumberHorizontal=5;		//����� �������������� �����
	void MaxMin(vector <double> &mas, double &Max_mas, double &Min_mas);
	CFont Font;
	void SetFont(int size, int angle, CWnd* frameWnd);
public:

	//���������� ������� �������
	void DrawGraph(vector <double> mas, vector <double> step, CString str, double xMin, double xMax, double yMax, double yMin, int rad, COLORREF color, CDC* pMemDC, CRect w);
	//���������� �����
	void DrawGrid(vector <double> &mas, double xMin, double xMax, double yMax, double yMin, CDC* pMemDC, CRect w);
	//���������� ���� OX � OY 
	void DrawAxis(vector <double> &mas, double xMin, double xMax, double yMax, double yMin, CWnd* frameWnd, CDC* pMemDC, CRect w);
	//������ �������� �� ����
	void DrawTextAxis(vector <double> &mas, double xMin, double xMax, double yMax, double yMin, CDC* pMemDC, CRect w);
	//������ �����
	void DrawLine(double x1, double y1, double x2, double y2, double xMin, double xMax, double yMin, double yMax, int rad, COLORREF color, CDC* pMemDC, CRect w);
	//������ ����
	void DrawCircle(double xc, double yc, double xMin, double xMax, double yMin, double yMax, double rc, CPen &pen, CDC* pMemDC, CRect w);
	//��������� ���
	void DrawAll(CDC* pMemDC, CRect w);
	//������ �����������
	void DrawTriangle(double x1, double y1, double x2, double y2, double x3, double y3, double xMin, double xMax, double yMin, double yMax, CPen &pen, CDC* pMemDC, CRect w);
	void DrawPoints(double x, double y, int rad, double xMin, double xMax, double yMin, double yMax, COLORREF color, CDC* pMemDC, CRect w);
	void DrawGraphGridAxis(vector<double>x, vector<double>y1, vector<double>y2, double xMin, double xMax, int nWidth, COLORREF crColor1, COLORREF crColor2, CWnd* frameWnd, CDC* pMemDC, CRect w);
	void FilledWithAColorTriangle(vector<MyTriangle> tri, vector<Point>vertex, double xMin, double xMax, double yMin, double yMax, CDC* pMemDC, CRect w);
};