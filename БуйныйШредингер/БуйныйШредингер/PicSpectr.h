#pragma once
#include<Gdiplus.h>
#include<vector>
#include<algorithm>
using namespace std;
using namespace Gdiplus;

// PicSpectr

class PicSpectr : public CStatic
{
	DECLARE_DYNAMIC(PicSpectr)
	double Xmin;
	double Xmax;
	double Ymin;
	double Ymax;
	double Kx;
	double Ky;
	vector<PointF>������;
	void ���������������(LPDRAWITEMSTRUCT lpDrawItemStruct);
	REAL KoordX(double X);
	REAL KoordY(double Y);
	void ����������(Graphics &��������);
public:
	PicSpectr();
	virtual ~PicSpectr();

protected:
	DECLARE_MESSAGE_MAP()
public:
	void ���������(vector<double>������, double Rmax);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
};

