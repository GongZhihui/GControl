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

constexpr auto TemplateMaxSize = 1024;

class DialogTemplate
{
public:
    DialogTemplate(int size = TemplateMaxSize);
    ~DialogTemplate();

    DLGTEMPLATE* create(DWORD style, CRect& rect, DWORD styleEx = 0);

private:
    WORD* buffer_;
};


class Dialog : public CDialogEx
{
public:
    Dialog();
    ~Dialog();

public:
    BOOL createModal(CRect rect = InitRect, CWnd* parent = nullptr);
    BOOL create(CRect rect = InitRect, CWnd* parent = nullptr);
    void setWindowRect(const CRect &rect);

    BOOL OnInitDialog();
    afx_msg LRESULT OnNcHitTest(CPoint point);
    DECLARE_MESSAGE_MAP()
    
private:
    DialogTemplate dialogTemplate_;

protected:
    static CRect BadRect;
    static CRect InitRect;
    CRect windowRect_;
};

}