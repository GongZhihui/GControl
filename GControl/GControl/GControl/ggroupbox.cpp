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
#include "ggroupbox.h"

namespace GCtrl 
{

BEGIN_MESSAGE_MAP(GroupBox, Static)
    ON_WM_PAINT()
END_MESSAGE_MAP()

GCtrl::GroupBox::GroupBox()
{
}

void GroupBox::setBorderColor(COLORREF color)
{
    borderClr_ = color;
}

void GroupBox::setTopPos(int pos)
{
    topPos_ = pos;
}

void GroupBox::push_back(CButton * btn)
{
    if(btn)
        radioBtns_.push_back(btn);
}

GroupBox::RadioBtns & GroupBox::radioBtns()
{
    return radioBtns_;
}

void GroupBox::OnPaint()
{
    CPaintDC dc(this); 
    CRect rccli;
    GetClientRect(&rccli);

    //创建画笔
    CPen pen;
    pen.CreatePen(PS_SOLID, 1, borderClr_);

    //选入画笔
    dc.SelectObject(pen);
    //只画一个矩形边框，不使用画刷擦除矩形内的图形
    dc.SelectStockObject(NULL_BRUSH);
    CFont *curFont = font_.GetSafeHandle() ? &font_ : GetFont();
    CFont *oldFont = dc.SelectObject(curFont);
    CString text;

    GetWindowText(text);
    //矩形的位置向下移动一些，给文本留一些位置
    rccli.top = topPos_ == -1 ? 7 : topPos_;
    dc.Rectangle(rccli);

    //显示文本
    auto parent = GetParent();
    if (parent)
    {
        //根据父窗口像素点的颜色来获取父窗口的背景颜色
        auto colorRef = parent->GetDC()->GetPixel(1, 1);
        //设置文本的背景颜色为父窗口的背景颜色    
        dc.SetBkColor(colorRef);
    }

    dc.TextOut(10, 0, text);
    dc.SelectObject(oldFont);
}

}
