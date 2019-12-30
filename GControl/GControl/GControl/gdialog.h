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
#include "gbutton.h"

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

class Dialog : public CDialog
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

class MsgBox : public Dialog 
{
public:
    MsgBox();

public:
    static void init(int bkbmp, int okbmp, int closebmp, const CRect &rect = initRect);
    static int info(const CString text, const CString title = "提示");
    static int info(CWnd *parent, const CString text, const CString title = "提示");
    static int info(HWND parent, const CString text, const CString title = "提示");

private:
    virtual BOOL OnInitDialog();
    void setData(const CString text, const CString title);
    void setBmp(int bk, int close, int ok);
    void initFont();
    void initBK();
    void initData();
    void initCtrl();

private:
    static int okID_;
    static int closeID_;
    static int bkID_;
    static CRect initRect;

    PushButton okBtn_{ *this };
    PushButton closeBtn_{ *this };

    CDateTimeCtrl timeCtrl_;
    CEdit edit_;

    Static titleStc_{ *this };
    Static textStc_{ *this };
    Static bkStc_{ *this };

    CBitmap bkbmp_;

    CFont titleFont_;
    CFont textFont_;
    CFont textFont_small;

    CString title_;
    CString text_;
};

}