#pragma once
#include<Gdiplus.h>
#include<vector>
#include<algorithm>
using namespace std;
using namespace Gdiplus;

// PicStaticW

class PicStaticW : public CStatic
{
	DECLARE_DYNAMIC(PicStaticW)
	double Xmin;
	double Xmax;
	double Ymin;
	double Ymax;
	double Kx;
	double Ky;
	vector<PointF>Память;
	void Масштабирование(LPDRAWITEMSTRUCT lpDrawItemStruct);
	REAL KoordX(double X);
	REAL KoordY(double Y);
	void Прорисовка(Graphics &БитКарта);
public:
	PicStaticW();
	virtual ~PicStaticW();
protected:
	DECLARE_MESSAGE_MAP()
public:
	void Параметры(vector<double>Данные, double Rmax);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
};

