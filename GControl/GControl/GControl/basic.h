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

constexpr auto ComboBoxDowmBmpPath = "\\GControl\\image\\combobox.bmp";
constexpr auto BadColor =  0xFFFFFFFF;
CString GetCurrentDir();


class Basic 
{
public:
    Basic();
    virtual ~Basic();

    // 这个font仅用作子类化时, 其他时候，请重新创建个font
    virtual void setFont(CFont &font);
    virtual void setFont(LOGFONT &lf);

    // 谨慎使用这个，最好只在子类化该控件时用这个
    // 其他时候，请重新创建个font
    CFont& getFont();

protected:
    CFont font_;
};

} //!GCtrl