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
#include "basic.h"

namespace GCtrl
{

Basic::Basic(CWnd &parent)
    : parent_{&parent}
{
}

Basic::~Basic()
{
}

void Basic::setFont(CFont & font)
{
    if (!font.GetSafeHandle())
        return;
    LOGFONT lf;
    font.GetLogFont(&lf);
    setFont(lf);
}

void Basic::setFont(LOGFONT & lf)
{
    font_.CreateFontIndirect(&lf);
}

void Basic::setBKColor(COLORREF color)
{
    bkcolor_ = color;
}

void Basic::setTextColor(COLORREF color)
{
    textcolor_ = color;
}

void Basic::setParent(CWnd & parent)
{
    parent_ = &parent;
}

CWnd & Basic::getParent()
{
    return *parent_;
}

CFont & Basic::getFont()
{
    return font_;
}

} // !GCtrl
