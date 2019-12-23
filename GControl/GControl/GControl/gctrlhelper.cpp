#include "stdafx.h"
#include "gctrlhelper.h"
namespace GCtrl 
{

CtrlHelper::CtrlHelper()
{
}

CtrlHelper::~CtrlHelper()
{
}

void CtrlHelper::initFont(CFont & font, int size, const char * faceName)
{
    font.CreateFont(size, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0,
        ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, faceName);
}

void CtrlHelper::initBK(CWnd * wnd, CBitmap &bkbmp, int ctrlID, int imageID, bool main)
{
    bkbmp.LoadBitmapA(imageID);
    auto pStatic = static_cast<CStatic*>(wnd->GetDlgItem(ctrlID));
    pStatic->ModifyStyle(0xF, SS_BITMAP | SS_REALSIZECONTROL);
    pStatic->SetBitmap(bkbmp);

    if (main)
    {
        CRect rect;
        wnd->GetClientRect(rect);
        pStatic->MoveWindow(rect);
    }
}

//void CtrlHelper::initBtn(CButtonST & btn, int hoverBtnImageID, int btnImageID)
//{
//    btn.SetBitmaps(hoverBtnImageID, RGB(255, 0, 255), btnImageID, RGB(255, 0, 255));
//    btn.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
//    btn.SetAlign(CButtonST::ST_ALIGN_VERT);
//    btn.SetBtnCursor(IDC_CURSOR_HAND);
//}



} // namespace GCtrl
