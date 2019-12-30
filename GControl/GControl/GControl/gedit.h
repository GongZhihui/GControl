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
#include "basic.h"

namespace GCtrl 
{

class Edit 
    : public CEdit
    , public Basic
{
public:
    Edit(CWnd &parent);
    ~Edit();

    // 设置边框颜色
    void setBorderColor(COLORREF color);
    // 设置圆角
    void setRoundPoint(CPoint point = {0,0});
    
private:
    DECLARE_MESSAGE_MAP()
    afx_msg void OnNcPaint();
    HBRUSH CtlColor(CDC *dc, UINT color);

private:
    COLORREF borderClr_{ RGB(195, 215, 220) };
    CPoint arcPoint_{ 0,0 };
    CBrush bkbrush_;
};

}