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

class ListBox 
    : public CListBox
    , public Basic
{
public:
    ListBox(CWnd &parent);
    ~ListBox();

    // 设置listbox背景颜色，文字颜色
    void setItemColor(COLORREF bkColor = BadColor, COLORREF textColor = BadColor);
    // 设置listbox选中行的背景颜色，文字颜色
    void setItemSelectedColor(COLORREF bkColor = BadColor, COLORREF textColor = BadColor);

private:
    DECLARE_MESSAGE_MAP()
    void DrawItem(LPDRAWITEMSTRUCT lps);

private:
    COLORREF itemBkClr_{ BadColor };
    COLORREF itemTextClr_{ BadColor };
    COLORREF itemSelectedBkClr_{ BadColor };
    COLORREF itemSelectedTextClr_{ BadColor };
};

} //! namespace GCtrl