
// DipoleFDTDDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "DipoleFDTD.h"
#include "DipoleFDTDDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// диалоговое окно CDipoleFDTDDlg



CDipoleFDTDDlg::CDipoleFDTDDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDipoleFDTDDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDipoleFDTDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDipoleFDTDDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SOLVE, &CDipoleFDTDDlg::OnBnClickedSolve)
END_MESSAGE_MAP()


// обработчики сообщений CDipoleFDTDDlg

BOOL CDipoleFDTDDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	win.setWindowIDC(this, IDC_DRAW);
	srand(time(0));

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CDipoleFDTDDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		win.frameDc->BitBlt(0, 0, win.r.Width(), win.r.Height(), win.mdc, 0, 0, SRCCOPY);
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CDipoleFDTDDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDipoleFDTDDlg::Solve()
{
	vector<vector<double>> ga(IE, vector<double>(JE, 0));
	vector<vector<double>> dz(IE, vector<double>(JE, 0));
	vector<vector<double>> ez(IE, vector<double>(JE, 0));
	vector<vector<double>> hx(IE, vector<double>(JE, 0));
	vector<vector<double>> hy(IE, vector<double>(JE, 0));

	int  n, i, j, nsteps, npml; // jc, ic, l,
	double ddx, dt, T, pi;//sigma, epsz,  eaf, epsilon
	double xn, xxn, xnum, xd, curl_e;
	double pulse; //spread,  t0,

	vector<double> gi2(IE);
	vector<double> gi3(IE);
	vector<double> gj2(IE);
	vector<double> gj3(IE);
	vector<double> fi1(IE);
	vector<double> fi2(IE);
	vector<double> fi3(IE);
	vector<double> fj1(IE);
	vector<double> fj2(IE);
	vector<double> fj3(IE);
	vector<vector<double>> ihx(IE, vector<double>(JE, 0));
	vector<vector<double>> ihy(IE, vector<double>(JE, 0));

	//ic = IE / 2 - 5;
	//jc = JE / 2 - 5;
	ddx = 0.01;
	dt = ddx / 6e8;
	pi = 3.14159;

	for (j = 0; j < JE; j++)
	{
		for (i = 0; i < IE; i++)
		{
			dz[i][j] = 0.;
			hx[i][j] = 0.;
			hy[i][j] = 0.;
			ihx[i][j] = 0.;
			ihy[i][j] = 0.;
			ga[i][j] = 1.0;
			ez[i][j] = 0.0;
		}
	}

	for (i = 0; i < IE; i++){
		gi2[i] = 1.0;
		gi3[i] = 1.0;
		fi1[i] = 0.0;
		fi2[i] = 1.0;
		fi3[i] = 1.0;
	}

	for (j = 0; j < JE; j++){
		gj2[j] = 1.0;
		gj3[j] = 1.0;
		fj1[j] = 0.0;
		fj2[j] = 1.0;
		fj3[j] = 1.0;
	}
	npml = 8;		//колличество клеток
	for (i = 0; i <= npml; i++)
	{
		xnum = npml - i;
		xd = npml;
		xxn = xnum / xd;
		xn = 0.25*pow(xxn, 3.0);
		gi2[i] = 1.0 / (1.0 + xn);
		gi2[IE - 1 - i] = 1.0 / (1.0 + xn);
		gi3[i] = (1.0 - xn) / (1.0 + xn);
		gi3[IE - i - 1] = (1.0 - xn) / (1.0 + xn);
		xxn = (xnum - 0.5) / xd;
		xn = 0.25*pow(xxn, 3.0);
		fi1[i] = xn;
		fi1[IE - 2 - i] = xn;
		fi2[i] = 1.0 / (1.0 + xn);
		fi2[IE - 2 - i] = 1.0 / (1.0 + xn);
		fi3[i] = (1.0 - xn) / (1.0 + xn);
		fi3[IE - 2 - i] = (1.0 - xn) / (1.0 + xn);
	}

	for (j = 0; j <= npml; j++){
		xnum = npml - j;
		xd = npml;
		xxn = xnum / xd;
		xn = 0.25*pow(xxn, 3.0);

		gj2[j] = 1.0 / (1.0 + xn);
		gj2[JE - 1 - j] = 1.0 / (1.0 + xn);
		gj3[j] = (1.0 - xn) / (1.0 + xn);
		gj3[JE - j - 1] = (1.0 - xn) / (1.0 + xn);
		xxn = (xnum - 0.5) / xd;
		xn = 0.25*pow(xxn, 3.0);
		fj1[j] = xn;
		fj1[JE - 2 - j] = xn;
		fj2[j] = 1.0 / (1.0 + xn);
		fj2[JE - 2 - j] = 1.0 / (1.0 + xn);
		fj3[j] = (1.0 - xn) / (1 + xn);
		fj3[JE - 2 - j] = (1.0 - xn) / (1 + xn);
	}

	double t0 = 20.0;
	double spread = 6.0;
	T = 0;
	nsteps = 800;

	for (n = 1; n <= nsteps; n++){
		T = T + 1;
		for (j = 1; j < JE; j++){
			for (i = 1; i < IE; i++){
				dz[i][j] = gi3[i] * gj3[j] * dz[i][j] +
					gi2[i] * gj2[j] * 0.5*(hy[i][j] - hy[i - 1][j] -
					hx[i][j] + hx[i][j - 1]);

			}
		}


		//pulse = sin(2 * pi * 1e+19 * dt * T);
		pulse = sin(2 * pi * 10 * dt * T);
		//dz[49][51] = pulse;
		//dz[51][49] = -pulse;


		dz[48][52] = pulse;
		dz[52][48] = -pulse;

		/*dz[50][38] = cos(2 * pi * 10 * dt * T + pi/3);
		dz[50][62] = cos(2 * pi * 10 * dt * T - pi/3);
		*/
		for (j = 1; j < JE - 1; j++){
			for (i = 1; i < IE - 1; i++){
				ez[i][j] = ga[i][j] * dz[i][j];
			}
		}
		//--------------
		for (j = 0; j < JE - 1; j++){
			ez[0][j] = 0.0;
			ez[IE - 1][j] = 0.0;
		}
		for (i = 0; i < IE - 1; i++){
			ez[i][0] = 0.0;
			ez[i][JE - 1] = 0.0;
		}
		//---------------
		for (j = 0; j < JE - 1; j++){
			for (i = 0; i < IE; i++){
				curl_e = ez[i][j] - ez[i][j + 1];
				ihx[i][j] = ihx[i][j] + fi1[i] * curl_e;
				hx[i][j] = fj3[j] * hx[i][j] +
					fj2[j] * 0.5*(curl_e + ihx[i][j]);
			}
		}

		for (j = 0; j < JE; j++){
			for (i = 0; i < IE - 1; i++){
				curl_e = ez[i + 1][j] - ez[i][j];
				ihy[i][j] = ihy[i][j] + fj1[j] * curl_e;
				hy[i][j] = fi3[i] * hy[i][j] +
					fi2[i] * 0.5*(curl_e + ihy[i][j]);
			}
		}
		FindRadiattionPattern(hx, hy, ez);
	}
	Beep(500, 500);
}

void CDipoleFDTDDlg::OnBnClickedSolve()
{
	Solve();
}
void CDipoleFDTDDlg::FindRadiattionPattern(vector<vector <double>>massHx, vector<vector <double>>massHy, vector<vector <double>>massEz)
{
	Point point;
	struct RadiationPattern
	{
		double elevation;
		double azimuth;
		double I;
		double other;
	};

	double rad = IE / 2 - 10;
	double count = 360;
	vector<RadiationPattern> dipole;

	for (int i = 0; i < count; i++)
	{
		point.x = rad*cos(2. * M_PI / count*i) + IE / 2;
		point.y = rad*sin(2. * M_PI / count*i) + IE / 2;

		RadiationPattern bufdipole;
		bufdipole.azimuth = 0;
		bufdipole.elevation = (2. * M_PI / count*i)*(180. / M_PI);//в градусах

	/*	bufdipole.I = sqrt(massHx[(int)point.x][(int)point.y] * massHx[(int)point.x][(int)point.y]
			 + massHy[(int)point.x][(int)point.y] * massHy[(int)point.x][(int)point.y]);*/
		//bufdipole.I = abs(massHy[(int)point.x][(int)point.y] * massHy[(int)point.x][(int)point.y]);
		bufdipole.I = abs(massHx[(int)point.x][(int)point.y] * massHx[(int)point.x][(int)point.y]);
		bufdipole.other = abs(massEz[(int)point.x][(int)point.y]);
		dipole.push_back(bufdipole);
	}

	int imin = 0; int imax = 0;
	for (int i = 0; i < dipole.size(); i++)
	{
		if (dipole[i].I < dipole[imin].I) imin = i;
		if (dipole[i].I > dipole[imax].I) imax = i;
	}
	double Max_mas = dipole[imax].I;
	double Min_mas = dipole[imin].I;

	for (int i = 0; i < dipole.size(); i++)
	{
		dipole[i].I /= Max_mas;
	}



	imin = 0;  imax = 0;
	for (int i = 0; i < dipole.size(); i++)
	{
		if (dipole[i].other < dipole[imin].other) imin = i;
		if (dipole[i].other > dipole[imax].other) imax = i;
	}
	Max_mas = dipole[imax].other;
	Min_mas = dipole[imin].other;

	for (int i = 0; i < dipole.size(); i++)
	{
		dipole[i].other /= Max_mas;
	}

	draw.DrawAll(win.mdc, win.r);
	//draw.DrawTextAxis(vector<double>(), -1, 1, 1, -1, win.mdc, win.r);				//значения на осях
	draw.DrawGrid(vector<double>(), -1, 1, 1, -1, win.mdc, win.r);					//прорисовка сетки
	//draw.DrawAxis(vector<double>(), -1, 1, 1, -1, win.frameWnd, win.mdc, win.r);					//прорисовка осей
	//draw.DrawTextAxis(vector<double>(), 0, 360, Max_mas, Min_mas, win.mdc, win.r);				//значения на осях
	//draw.DrawGrid(vector<double>(), 0, 360, Max_mas, Min_mas, win.mdc, win.r);					//прорисовка сетки
	//draw.DrawAxis(vector<double>(), 0, 360, Max_mas, Min_mas, win.frameWnd, win.mdc, win.r);					//прорисовка осей
	/*for (int i = 0; i < dipole.size(); i++)
	{
	draw.DrawPoints(dipole[i].I*cos(dipole[i].elevation * M_PI / 180.), dipole[i].I*sin(dipole[i].elevation * M_PI / 180.), 2, -1, 1, 1, -1, RGB(0, 0, 255), win.mdc, win.r);
	}*/

	for (int i = 0; i < dipole.size() - 1; i++)
	{
		draw.DrawLine(dipole[i].I*cos(dipole[i].elevation * M_PI / 180.), dipole[i].I*sin(dipole[i].elevation * M_PI / 180.),
			dipole[i + 1].I*cos(dipole[i + 1].elevation * M_PI / 180.), dipole[i + 1].I*sin(dipole[i + 1].elevation * M_PI / 180.),
			-1, 1, 1, -1, 1, RGB(0, 125, 255), win.mdc, win.r);
		draw.DrawLine(dipole[i].other*cos(dipole[i].elevation * M_PI / 180.), dipole[i].other*sin(dipole[i].elevation * M_PI / 180.),
			dipole[i + 1].other*cos(dipole[i + 1].elevation * M_PI / 180.), dipole[i + 1].other*sin(dipole[i + 1].elevation * M_PI / 180.),
			-1, 1, 1, -1, 1, RGB(255, 125, 0), win.mdc, win.r);
	}
	win.frameDc->BitBlt(0, 0, win.r.Width(), win.r.Height(), win.mdc, 0, 0, SRCCOPY);
}
bool CDipoleFDTDDlg::InsideTheTriangle(Point p1, Point p2, Point p3, Point p)
{
	double sign1 = (p2.x - p1.x)*(p.y - p1.y) - (p2.y - p1.y)*(p.x - p1.x);
	double sign2 = (p3.x - p2.x)*(p.y - p2.y) - (p3.y - p2.y)*(p.x - p2.x);
	double sign3 = (p1.x - p3.x)*(p.y - p3.y) - (p1.y - p3.y)*(p.x - p3.x);
	if ((sign1 >= 0) && (sign2 >= 0) && (sign3 >= 0))return true;
	if ((sign1 <= 0) && (sign2 <= 0) && (sign3 <= 0))return true;
	return false;
}