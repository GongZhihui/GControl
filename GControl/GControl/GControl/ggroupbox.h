﻿//------------------------------------------------------------------------------
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
#include "gstatic.h"
#include <vector>

namespace GCtrl
{

class GroupBox 
    : public Static
{
public:
    using RadioBtns = std::vector<CButton*>;

    GroupBox(CWnd &parent);

    void setBorderColor(COLORREF color);
    void setTopPos(int pos);
    void push_back(CButton *btn);
    RadioBtns &radioBtns();

    DECLARE_MESSAGE_MAP()
private:
    afx_msg void OnPaint();

private:
    RadioBtns radioBtns_;
    COLORREF borderClr_{ RGB(160,160,160) };
    int topPos_ = -1;
};

} // !namespace GCtrl