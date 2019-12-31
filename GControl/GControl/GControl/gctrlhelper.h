//------------------------------------------------------------------------------
/*
    This file is part of gcontrol: https://github.com/gongzhihui/gcontrol
    Copyright (c) 2019 龚志慧.
    Permission to use, copy, modify, and/or distribute this software for any
    purpose  with  or without fee is hereby granted, provided that the above
    copyright notice and this permission notice appear in all copies.
    THE  SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
    WITH  REGARD  TO  THIS  SOFTWARE  INCLUDING  ALL  IMPLIED  WARRANTIES  OF
    MERCHANTABILITY  AND  FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
    ANY  SPECIAL ,  DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
    WHATSOEVER  RESULTING  FROM  LOSS  OF USE, DATA OR PROFITS, WHETHER IN AN
    ACTION  OF  CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
//==============================================================================

#pragma once
#include "stdafx.h"

namespace GCtrl 
{

#define super __super

#define dragdialog()                       \
    CRect rect;                            \
    GetClientRect(rect);                   \
    ClientToScreen(rect);                  \
    if (rect.PtInRect(point))              \
        return HTCAPTION                   \

class CtrlHelper 
{
public:
    CtrlHelper();
    ~CtrlHelper();
    
    static void initFont(CFont & font, int size = 22, const char * faceName = "微软雅黑");
    static void initBK(CWnd * wnd, CBitmap &bkbmp, int ctrlID, int imageID, bool main = true);
    static void refreshControl(CWnd *self, CWnd *ctrl);
    //void initBtn(CButtonST & btn, int hoverBtnImageID, int btnImageID);
};



} //!namespace GCtrl