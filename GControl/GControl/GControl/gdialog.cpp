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
#include "gdialog.h"
#include "Resource.h"

namespace GCtrl 
{

CRect Dialog::BadRect = { -1, -1, -1, -1 };
CRect Dialog::InitRect = { 0, 0, 100, 100};

BEGIN_MESSAGE_MAP(Dialog, CDialog)
    ON_WM_NCHITTEST()
END_MESSAGE_MAP()

DialogTemplate::DialogTemplate(int size)
{
    buffer_ = new WORD[size];
    if ((!buffer_) || (TemplateMaxSize > size))
    {
        ASSERT((!buffer_) || (TemplateMaxSize > size));
        exit(0);
    }
}

DialogTemplate::~DialogTemplate()
{
    if (buffer_)
    {
        delete buffer_;
        buffer_ = nullptr;
    }
}


DLGTEMPLATE* DialogTemplate::create(DWORD style, CRect& rect, DWORD styleEx)
{
    WORD* temp = buffer_;
    DLGTEMPLATE* dlgTemp = (DLGTEMPLATE*)temp;

    rect.left = rect.left * 2 / 3;
    rect.right = rect.right * 2 / 3;
    rect.top = rect.top * 2 / 3;
    rect.bottom = rect.bottom * 2 / 3;

    // 对话框模版
    dlgTemp->style = style;
    dlgTemp->dwExtendedStyle = styleEx;
    dlgTemp->cdit = 0;

    dlgTemp->cx = rect.Width();
    dlgTemp->cy = rect.Height();
    dlgTemp->x = (short)rect.left;
    dlgTemp->y = (short)rect.top;

    temp = (WORD*)(dlgTemp + 1);

    // 菜单
    *temp++ = 0;
    // class
    *temp++ = 0;
    // caption
    // font
    return dlgTemp;
}
BOOL Dialog::OnInitDialog()
{
    CDialog::OnInitDialog();
    SetWindowText("dialog");
    return TRUE;
}
LRESULT Dialog::OnNcHitTest(CPoint point)
{
    CRect rect;
    GetClientRect(rect);
    ClientToScreen(rect);

    if (rect.PtInRect(point))
        return HTCAPTION;

    return CDialog::OnNcHitTest(point);
}

Dialog::Dialog()
{
}

Dialog::~Dialog()
{
}

BOOL Dialog::createModal(CRect rect, CWnd* parent)
{
    auto rc = rect == BadRect ? InitRect : rect;
    auto temp = dialogTemplate_.create(WS_VISIBLE | WS_POPUP, rc);
    return CDialog::InitModalIndirect(temp, parent);
}

BOOL Dialog::create(CRect rect, CWnd* parent)
{
    auto rc = rect == BadRect ? InitRect : rect;
    auto temp = dialogTemplate_.create(WS_VISIBLE | WS_POPUP | WS_SYSMENU | WS_CLIPSIBLINGS, rc);
    return CDialog::CreateIndirect(temp, parent);;
}

void Dialog::setWindowRect(const CRect & rect)
{
    windowRect_ = rect;
}

//------------------------------------------------------

int MsgBox::okID_ = -1;
int MsgBox::closeID_ = -1;
int MsgBox::bkID_ = -1;
CRect MsgBox::initRect = { 0,0,330,192 };

MsgBox::MsgBox()
{
}

void MsgBox::init(int bkbmp, int okbmp, int closebmp, const CRect &rect)
{
    okID_ = okbmp;
    closeID_ = closebmp;
    bkID_ = bkbmp;
    initRect = rect;
}

int MsgBox::info(CWnd *parent, const CString text, const CString title)
{
    MsgBox dlg;
    if(parent && parent->m_hWnd)
        dlg.SetParent(parent);
    dlg.setData(text, title);
    dlg.createModal(initRect);
    return dlg.DoModal();
}

int MsgBox::info(HWND parent, const CString text, const CString title)
{
    return info(CWnd::FromHandle(parent), text, title);
}

int MsgBox::info(const CString text, const CString title)
{
    return info(CWnd{}, text, title);
}

void MsgBox::setData(const CString text, const CString title)
{
    title_ = title;
    text_ = text;
    auto size = text.GetLength();
    if (size <= 32)
        textStc_.setTextAlign(GCtrl::Static::TextAlign::Center);
}

void MsgBox::setBmp(int bk, int close, int ok)
{
    okID_ = ok;
    closeID_ = close;
    bkID_ = bk;
}

BOOL MsgBox::OnInitDialog()
{
    Dialog::OnInitDialog();

    bkStc_.create(0, { 0,0, 0, 0 }, "", WS_CHILD | WS_VISIBLE | SS_CENTER | SS_BITMAP);
    okBtn_.create(1, { 135, 143, 62, 27 });
    closeBtn_.create(2, { 309, 6, 12, 15 });
    titleStc_.create(3, { 9, 4, 105, 24 }, "");
    textStc_.create(4, { 31, 69, 270,  59 }, "");
    
    initFont();
    initBK();
    initCtrl();
    initData();

    return TRUE;
}

void MsgBox::initFont()
{
    titleFont_.CreateFont(22, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0,
        ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "微软雅黑");

    textFont_.CreateFont(22, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0,
        ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "微软雅黑");
    
    textFont_small.CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0,
        ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "微软雅黑");
}

void MsgBox::initBK()
{
    bkbmp_.LoadBitmapA(bkID_);
    bkStc_.ModifyStyle(0xF, SS_BITMAP | SS_REALSIZECONTROL);

    bkStc_.SetBitmap(bkbmp_);
    CRect rect;
    GetClientRect(rect);
    bkStc_.MoveWindow(rect);
}

void MsgBox::initData()
{
    titleStc_.SetWindowTextA(title_);
    titleStc_.SetFont(&titleFont_);
    titleStc_.setTextColor(RGB(255, 255, 255));
    textStc_.SetWindowTextA(text_);
    if (text_.GetLength() >= 64)
        textStc_.SetFont(&textFont_small);
    else
        textStc_.SetFont(&textFont_);
}

void MsgBox::initCtrl()
{
    okBtn_.setBitmap(okID_);
    okBtn_.setClickedEvent([&](bool) {OnOK(); });
    closeBtn_.setBitmap(closeID_);
    closeBtn_.setClickedEvent([&](bool) {OnCancel(); });
}
} //!namespace GCtrl
