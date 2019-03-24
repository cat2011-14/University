#pragma once 
#include "Point.h"
#include "InitializingTheDrawingWindow.h"
//#include "Draw.h"
#include <vector>
#include <set>
using namespace std;
struct Circle
{
	double x;
	double y;
	double r;
};

struct MyTriangle
{
	int A;
	int B;
	int C;
};
#include "Draw.h"
class Triangulation
{
	//Draw draw;
	/*
	������� ������������ � ����������� �������� �� �������� � � �
	xMin - ����������� ������� �� ��������� �
	xMax - ������������ ������� �� ��������� �
 	yMin - ����������� ������� �� ��������� �
	yMax - ������������ ������� �� ��������� �
	*/
	void MinMax(vector<Point>vertex, double &xMin, double &xMax, double &yMin, double &yMax);

	/*
	��������� �� ������� ������ 
	false - ����� ����� � ����������
	true - ����� ����� ��� ����������
	*/
	bool Check(Point A, Circle circle);

	/*
	��������� ����������� �� ������������
	true - ����������� ���������� (��� ����� ����� �� �� ����� ������)
	false - ����������� �� ���������� (��� ��� ����� ����� �� ����� ������) 
	*/
	bool Correctness(Point A, Point B, Point C);

	/*
	�������� �������������, ������� ����� � �������� ����� ������� ���� �� ����� A, B, C, D
	tri - ������ �������������
	A- ���������� ������
	*/
	void DeleteTriangle(vector<MyTriangle> &tri, Point A, vector<Point>vertex);
public:
	/*
	������ ����� � ������ ��������� ���������� ������������
	�,�,� - ������� ������������
	circle - ��������� ����������
	*/
	void FindCircle(Point A, Point B, Point C, Circle &circle);

	/*
	��������� ������� (x, y) ���� � ����� ������������ ������ � � ������ �
	� - ������ ��������� �
	� - ������ ��������� �
	vertex - ������� 
	*/
	void VertexOfATriangle(vector<double>x, vector<double>y, vector<Point> &vertex);

	/*
	������������ ������� �������� ��������
	vertex - ��������� �����
	tri - ��������� �������������
	*/
	void TriangulationIterate(vector<Point>vertex, vector<MyTriangle> &tri);
	/*
	������������ ������� �������� ��������
	vertex - ��������� �����
	tri - ��������� �������������
	*/
	void TriangulationIterateForRec(vector<Point>vertex, vector<int>index, vector<MyTriangle> &tri);

	/*
	����������� ������������ 
	vertex - ��������� �����
	tri - ��������� �������������
	*/
	void TriangulationRecurrent(InitializingTheDrawingWindow* win, /*Draw draw, */bool anim, vector<Point>vertex, vector<MyTriangle> &tri, vector<Point>superstructure);
};