#include "stdafx.h"
#include "InitializingTheDrawingWindow.h"

InitializingTheDrawingWindow::InitializingTheDrawingWindow()
{

}
// ���� ��� ���������� ��� ��� : setWindowIDC(this, IDC_DRAW_TRIANGLE)
void InitializingTheDrawingWindow::setWindowIDC(CWnd* hDlg, int picID)
{
	frameWnd = hDlg->GetDlgItem(picID);			// �������� IDC �������� �� ������� ��������� ������ � �����
	frameDc = frameWnd->GetDC();			// ��������� �������� ����������
	frameWnd->GetClientRect(&r);

	mdc = new CDC();										//�������� ���������
	mdc->CreateCompatibleDC(frameDc);		//���������� ����������
	bmp.CreateCompatibleBitmap(frameDc, r.Width(), r.Height());
	tmp = mdc->SelectObject(&bmp);		//������� ������ �������
}