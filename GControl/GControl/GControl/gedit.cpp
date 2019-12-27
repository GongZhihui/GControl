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

#include "stdafx.h"
#include "gedit.h"

namespace GCtrl 
{

BEGIN_MESSAGE_MAP(Edit, CEdit)
    ON_WM_NCPAINT()
    ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()

Edit::Edit()
{
    textcolor_ = { RGB(0,0,0) };
    bkcolor_ = { RGB(255,255,255) };
}
Edit::~Edit()
{
}
void Edit::setBorderColor(COLORREF color)
{
    borderClr_ = color;
}

void Edit::setRoundPoint(CPoint point)
{
    arcPoint_ = point;
}

void Edit::OnNcPaint()
{
    CWindowDC dc(this);
    CRect rect;
    GetWindowRect(rect);
    rect = CRect(0, 0, rect.right - rect.left, rect.bottom - rect.top);
    rect.InflateRect(-1, -1);
    rect.left -= 1;
    rect.right += 1;
    rect.top -= 1;
    rect.bottom += 1;
    CPen pen;
    pen.CreatePen(PS_SOLID, 1, borderClr_);
    dc.SelectObject(pen);
    dc.RoundRect(rect, arcPoint_);
}

HBRUSH Edit::CtlColor(CDC * dc, UINT color)
{
    if (!bkbrush_.m_hObject)
        bkbrush_.CreateSolidBrush(bkcolor_);
    dc->SetTextColor(textcolor_);
    dc->SetBkMode(TRANSPARENT);
    return bkbrush_;
}

} // !namespace GCtrl
