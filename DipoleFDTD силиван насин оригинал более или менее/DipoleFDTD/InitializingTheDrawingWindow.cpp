#include "stdafx.h"
#include "InitializingTheDrawingWindow.h"

InitializingTheDrawingWindow::InitializingTheDrawingWindow()
{

}
// если что вызывается это так : setWindowIDC(this, IDC_DRAW_TRIANGLE)
void InitializingTheDrawingWindow::setWindowIDC(CWnd* hDlg, int picID)
{
	frameWnd = hDlg->GetDlgItem(picID);			// передали IDC картинки на которой изображен сигнал с шумом
	frameDc = frameWnd->GetDC();			// указатель контекст устройства
	frameWnd->GetClientRect(&r);

	mdc = new CDC();										//создание контекста
	mdc->CreateCompatibleDC(frameDc);		//связывание контекстов
	bmp.CreateCompatibleBitmap(frameDc, r.Width(), r.Height());
	tmp = mdc->SelectObject(&bmp);		//сделали объект текущим
}