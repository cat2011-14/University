#pragma once

class InitializingTheDrawingWindow 
{
	private:
	public:
	CWnd* frameWnd;					// ���������  �� ���� ��������
	CDC* frameDc;						// ��������� �������� ����������
	CRect r;							//  ������ ������ ����

	CDC *mdc;
	CBitmap bmp;
	CBitmap *tmp;

	InitializingTheDrawingWindow();
	void setWindowIDC(CWnd* hDlg, int picID);
};