#pragma once

class InitializingTheDrawingWindow 
{
	private:
	public:
	CWnd* frameWnd;					// указатель  на окно картинки
	CDC* frameDc;						// указатель контекст устройства
	CRect r;							//  хранит размер окна

	CDC *mdc;
	CBitmap bmp;
	CBitmap *tmp;

	InitializingTheDrawingWindow();
	void setWindowIDC(CWnd* hDlg, int picID);
};