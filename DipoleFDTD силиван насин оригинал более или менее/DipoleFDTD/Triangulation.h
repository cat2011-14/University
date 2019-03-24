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
	находит максимальные и минимальные элементы из векторов х и у
	xMin - минимальный элемент из множества х
	xMax - максимальный элемент из множества х
 	yMin - минимальный элемент из множества у
	yMax - максимальный элемент из множества у
	*/
	void MinMax(vector<Point>vertex, double &xMin, double &xMax, double &yMin, double &yMax);

	/*
	провер€ет на правило ƒелоне 
	false - точка лежит в окружности
	true - точка лежит вне окружности
	*/
	bool Check(Point A, Circle circle);

	/*
	провер€ем треугольник на корректность
	true - треугольник существует (три точки лежат не на одной пр€мой)
	false - треугольник не существует (все три точки лежат на одной пр€мой) 
	*/
	bool Correctness(Point A, Point B, Point C);

	/*
	удаление треугольников, которые имеют в качестве своей вершины одну из точек A, B, C, D
	tri - массив треугольников
	A- координаты вершин
	*/
	void DeleteTriangle(vector<MyTriangle> &tri, Point A, vector<Point>vertex);
public:
	/*
	найдем центр и радиус описанной окружности треугольника
	ј,¬,— - вершины треугольника
	circle - параметры окружности
	*/
	void FindCircle(Point A, Point B, Point C, Circle &circle);

	/*
	формирует вершины (x, y) име€ в своем распор€жении вектор х и вектор у
	х - вектор координат х
	у - вектор координат у
	vertex - вершины 
	*/
	void VertexOfATriangle(vector<double>x, vector<double>y, vector<Point> &vertex);

	/*
	триангул€ци€ методом простого перебора
	vertex - множество точек
	tri - множество треугольников
	*/
	void TriangulationIterate(vector<Point>vertex, vector<MyTriangle> &tri);
	/*
	триангул€ци€ методом простого перебора
	vertex - множество точек
	tri - множество треугольников
	*/
	void TriangulationIterateForRec(vector<Point>vertex, vector<int>index, vector<MyTriangle> &tri);

	/*
	рекурентна€ триангул€ци€ 
	vertex - множество точек
	tri - множество треугольников
	*/
	void TriangulationRecurrent(InitializingTheDrawingWindow* win, /*Draw draw, */bool anim, vector<Point>vertex, vector<MyTriangle> &tri, vector<Point>superstructure);
};