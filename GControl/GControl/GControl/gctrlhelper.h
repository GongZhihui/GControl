#pragma once
#include "stdafx.h"

namespace GCtrl 
{

#define super __super

class CtrlHelper 
{
public:
    CtrlHelper();
    ~CtrlHelper();
    
    void initFont(CFont & font, int size = 22, const char * faceName = "微软雅黑");
    void initBK(CWnd * wnd, CBitmap &bkbmp, int ctrlID, int imageID, bool main = true);
    //void initBtn(CButtonST & btn, int hoverBtnImageID, int btnImageID);
};



} //!namespace GCtrl