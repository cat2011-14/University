#include "stdafx.h"
#include  "Triangulation.h"

void Triangulation::MinMax(vector<Point>vertex, double &xMin, double &xMax, double &yMin, double &yMax)
{
	int Ximin = 0; int Ximax = 0;
	int Yimin = 0; int Yimax = 0;
	for (int i = 0; i < vertex.size(); i++)
	{
		if (vertex[i].x < vertex[Ximin].x) Ximin = i;
		if (vertex[i].x > vertex[Ximax].x) Ximax = i;

		if (vertex[i].y < vertex[Yimin].y) Yimin = i;
		if (vertex[i].y > vertex[Yimax].y) Yimax = i;
	}
	xMax = vertex[Ximax].x;
	xMin = vertex[Ximin].x;

	yMax = vertex[Yimax].y;
	yMin = vertex[Yimin].y;
}
bool Triangulation::Check(Point A, Circle circle)
{
	double a = sqrt((A.x - circle.x)*(A.x - circle.x) + (A.y - circle.y)*(A.y - circle.y));
	if (a < circle.r)//лежит внутри окружности
	{
		return false;
	}
	return true;
}
void Triangulation::FindCircle(Point A, Point B, Point C, Circle &circle)
{
	circle.x = 1 / 2.* ((B.x * B.x - A.x * A.x + B.y * B.y - A.y * A.y)*(C.y - A.y) - (C.x * C.x - A.x * A.x + C.y * C.y - A.y * A.y)*(B.y - A.y)) /
		((B.x - A.x)*(C.y - A.y) - (C.x - A.x)*(B.y - A.y));
	circle.y = 1 / 2.*((C.x * C.x - A.x * A.x + C.y * C.y - A.y * A.y)*(B.x - A.x) - (B.x * B.x - A.x * A.x + B.y * B.y - A.y * A.y)*(C.x - A.x)) /
		((B.x - A.x)*(C.y - A.y) - (C.x - A.x)*(B.y - A.y));
	circle.r = sqrt((circle.x - A.x)*(circle.x - A.x) + (circle.y - A.y)*(circle.y - A.y));
}
bool Triangulation::Correctness(Point A, Point B, Point C)
{
	double check = abs((B.x - A.x)*(C.y - A.y) - (C.x - A.x)*(B.y - A.y));
	if (abs(check) < 1e-16)
	{
		return false;
	}
	return true;
}
void Triangulation::DeleteTriangle(vector<MyTriangle> &tri, Point A, vector<Point>vertex)
{
	vector<MyTriangle> buf_tri;
	for (int i = 0; i < tri.size(); i++)
	{
		if ((vertex[tri[i].A] != A) && (vertex[tri[i].B] != A) && (vertex[tri[i].C] != A))
		{
			buf_tri.push_back(tri[i]);
		}
	}
	tri = buf_tri;
	buf_tri.clear();
}
void Triangulation::TriangulationIterate(vector<Point>vertex, vector<MyTriangle> &tri)
{
	Point A;
	Point B;
	Point C;
	Circle circle;
	vector<MyTriangle> tri_buf;
	bool exist;
	for (int i = 0; i < vertex.size() - 2; i++)
	{
		for (int j = i + 1; j < vertex.size() - 1; j++)
		{
			for (int k = j + 1; k < vertex.size(); k++)
			{
				A = vertex[i];
				B = vertex[j];
				C = vertex[k];

				bool check1 = Correctness(A, B, C);
				if (check1 == true)
				{
					FindCircle(A, B, C, circle);
					exist = true;
					for (int l = 0; l < vertex.size(); l++)
					{
						//проверяем, принадлежит ли точка данному треугольнику
						if ((A == vertex[l]) || (B == vertex[l]) || (C == vertex[l]))
						{
							continue;
						}
						//проверяем, лежит ли точка внутри описанной окружности
						bool check = Check(vertex[l], circle);
						if (check == false)
						{
							exist = false;
							break;
						}
					}
					if (exist == true)
					{
						MyTriangle buf1;
						buf1.A = i;
						buf1.B = j;
						buf1.C = k;
						tri_buf.push_back(buf1);
					}
				}
			}
		}
	}
	tri = tri_buf;
}
void Triangulation::TriangulationIterateForRec(vector<Point>vertex, vector<int> index, vector<MyTriangle> &tri)
{
	Point A;
	Point B;
	Point C;
	Circle circle;
	vector<MyTriangle> tri_buf;
	bool exist;
	for (int i = 0; i < index.size() - 2; i++)
	{
		for (int j = i + 1; j < index.size() - 1; j++)
		{
			for (int k = j + 1; k < index.size(); k++)
			{
				A = vertex[index[i]];
				B = vertex[index[j]];
				C = vertex[index[k]];

				bool check1 = Correctness(A, B, C);
				if (check1 == true)
				{
					FindCircle(A, B, C, circle);
					exist = true;
					for (int l = 0; l < index.size(); l++)
					{
						//проверяем, принадлежит ли точка данному треугольнику
						if ((A == vertex[index[l]]) || (B == vertex[index[l]]) || (C == vertex[index[l]]))
						{
							continue;
						}
						//проверяем, лежит ли точка внутри описанной окружности
						bool check = Check(vertex[index[l]], circle);
						if (check == false)
						{
							exist = false;
							break;
						}
					}
					if (exist == true)
					{
						MyTriangle buf1;
						buf1.A = index[i];
						buf1.B = index[j];
						buf1.C = index[k];
						tri_buf.push_back(buf1);
					}
				}
			}
		}
	}
	tri = tri_buf;
}
void Triangulation::VertexOfATriangle(vector<double>x, vector<double>y, vector<Point> &vertex)
{
	vertex.resize(x.size());
	for (int i = 0; i < x.size(); i++)
	{
		vertex[i].x = x[i];
		vertex[i].y = y[i];
	}
}
void Triangulation::TriangulationRecurrent(InitializingTheDrawingWindow* win, /*Draw draw,*/ bool anim, vector<Point>vertex, vector<MyTriangle> &tri, vector<Point>superstructure)
{
	CPen penYellow;
	penYellow.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));

	double xMin, xMax, yMin, yMax;
	MinMax(superstructure, xMin, xMax, yMin, yMax);

	vector<MyTriangle> buf_tri;

	set<int>buf_point;
	vector<Point> point;
	vector<int> index;

	Circle circle;
	bool check;

	vector<Point>NewVertex;
	NewVertex.resize(superstructure.size() + vertex.size());
	index.resize(superstructure.size());
	for (int i = 0; i < NewVertex.size(); i++)
	{
		if (i < superstructure.size())
		{
			NewVertex[i] = superstructure[i];
			index[i] = i;
		}
		else NewVertex[i] = vertex[i - superstructure.size()];
	}	
	//vertex = NewVertex;
	
	for (int i = superstructure.size(); i < NewVertex.size(); i++)
	{
		buf_tri.clear();
		if (index.size()>2)
		{
			TriangulationIterateForRec(NewVertex, index, buf_tri);
		}
		else
		{
			index.push_back(i);
			i++;
			TriangulationIterateForRec(NewVertex, index, buf_tri);
		}
	
		for (int j = 0; j < buf_tri.size(); j++)
		{
			if (i != superstructure.size())
			{
				if ((buf_tri[j].A == i - 1) || (buf_tri[j].B == i - 1 ) || (buf_tri[j].C == i - 1 ))
				{
					tri.push_back(buf_tri[j]);
				}
			}
			else
			{
				tri.push_back(buf_tri[j]);
			}
		}
		//----------------------------------------
		if (anim)
		{
			Draw draw;
			draw.DrawAll(win->mdc, win->r);
			for (int k = 0; k < vertex.size(); k++)
			{
				draw.DrawPoints(vertex[k].x, vertex[k].y, 3, xMin, xMax, yMax, yMin, RGB(0, 0, 255), win->mdc, win->r);
			}	
			for (int k = 0; k < superstructure.size(); k++)
			{
				draw.DrawPoints(superstructure[k].x, superstructure[k].y, 3, xMin, xMax, yMax, yMin, RGB(226, 185, 230), win->mdc, win->r);
			}
			for (int k = 0; k < tri.size(); k++)
			{
				draw.DrawTriangle(NewVertex[tri[k].A].x, NewVertex[tri[k].A].y, NewVertex[tri[k].B].x, NewVertex[tri[k].B].y, NewVertex[tri[k].C].x, NewVertex[tri[k].C].y, xMin, xMax, yMin, yMax, penYellow, win->mdc, win->r);
			}
			win->frameDc->BitBlt(0, 0, win->r.Width(), win->r.Height(), win->mdc, 0, 0, SRCCOPY);
			Sleep(100);
		}
		//--------------------------------------------
		buf_tri.clear();
		point.clear();
		for (int j = 0; j < tri.size(); j++)
		{
			//нашли центр и радиус описанной окружности
			FindCircle(NewVertex[tri[j].A], NewVertex[tri[j].B], NewVertex[tri[j].C], circle);
			check = Check(NewVertex[i], circle);
			if (check == false)
			{
				buf_point.emplace(tri[j].A);
				buf_point.emplace(tri[j].B);
				buf_point.emplace(tri[j].C);
				buf_point.emplace(i);
			}
			else
			{
				buf_tri.push_back(tri[j]);
			}
		}

		tri.clear();
		tri = buf_tri;
		index.clear();
		for (auto iter = buf_point.begin(); iter != buf_point.end(); iter++)
		{
			int buf;
			buf = *iter;
			index.push_back(buf);
		}
		buf_point.clear();
	}
	TriangulationIterateForRec(NewVertex, index, buf_tri);
	for (int j = 0; j < buf_tri.size(); j++)
	{
		if ((NewVertex[buf_tri[j].A] == NewVertex[NewVertex.size() - 1]) || (NewVertex[buf_tri[j].B] == NewVertex[NewVertex.size() - 1]) || (NewVertex[buf_tri[j].C] == NewVertex[NewVertex.size() - 1]))
		{
			tri.push_back(buf_tri[j]);
		}
	}
	//удаляем точки сверхструктруы
	for (int i = 0; i < superstructure.size(); i++)
	{
		DeleteTriangle(tri, superstructure[i], NewVertex);
	}

	for (int i = 0; i < tri.size(); i++)
	{
		tri[i].A = tri[i].A - superstructure.size();
		tri[i].B = tri[i].B- superstructure.size();
		tri[i].C = tri[i].C - superstructure.size();
	}

	Draw draw;
	draw.DrawAll(win->mdc, win->r);

	for (int i = 0; i < tri.size(); i++)
	{
		draw.DrawTriangle(vertex[tri[i].A].x, vertex[tri[i].A].y, vertex[tri[i].B].x, vertex[tri[i].B].y, vertex[tri[i].C].x, vertex[tri[i].C].y, xMin - 4, xMax + 4, yMin - 4, yMax + 4, penYellow, win->mdc, win->r);
	}
	for (int i = 0; i < vertex.size(); i++)
	{
		draw.DrawPoints(vertex[i].x, vertex[i].y, 3, xMin - 4, xMax + 4, yMax + 4, yMin - 4, RGB(0, 0, 255), win->mdc, win->r);
	}
	win->frameDc->BitBlt(0, 0, win->r.Width(), win->r.Height(), win->mdc, 0, 0, SRCCOPY);
}