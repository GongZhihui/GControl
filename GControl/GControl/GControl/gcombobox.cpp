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
#include "gcombobox.h"
#include "Basic.h"
#include "resource.h"
#include <GdiPlus.h>

namespace GCtrl
{

IMPLEMENT_DYNAMIC(ComboBox, CComboBox)

BEGIN_MESSAGE_MAP(ComboBox, CComboBox)
    ON_WM_PAINT()
    ON_CONTROL_REFLECT(CBN_SELCHANGE, &ComboBox::OnCbnSelchange)
    ON_CONTROL_REFLECT(CBN_DROPDOWN, &ComboBox::OnCbnDropdown)
    ON_WM_CTLCOLOR()
    ON_WM_DESTROY()
    ON_WM_KILLFOCUS()
    ON_WM_SETFOCUS()
END_MESSAGE_MAP()

ComboBox::ComboBox(CWnd &parent)
    : Basic{parent}
{
}

ComboBox::~ComboBox()
{
}

void ComboBox::loadDownPic(int bmpID)
{
    downBmp_.LoadBitmap(bmpID);
    defaultBmp_ = false;
}

void ComboBox::loadDownPic(const CString & bmpPath)
{
    downBmp_.LoadBitmap(bmpPath);
    defaultBmp_ = false;
}

void ComboBox::setTextColor(COLORREF color)
{
    textClr_ = color;
}

void ComboBox::setItemColor(COLORREF bkColor, COLORREF textColor)
{
    listBox_.setItemColor(bkColor, textColor);
}

void ComboBox::setItemSelectedColor(COLORREF bkColor, COLORREF textColor)
{
    listBox_.setItemSelectedColor(bkColor, textColor);
}

void ComboBox::setInterColor(COLORREF color)
{
    interClr_ = color;
}

void ComboBox::setOuterColor(COLORREF color)
{
    outerClr_ = color;
}

void ComboBox::setHeight(int height)
{
    SendMessage(CB_SETITEMHEIGHT, -1, height);
}

void ComboBox::setItemHeight(int height)
{
    SendMessage(CB_SETITEMHEIGHT, 0, height);
}

void ComboBox::setFont(CFont & font)
{
    if (!font.GetSafeHandle())
        return;
    LOGFONT lf = {0};
    font.GetLogFont(&lf);
    setFont(lf);
}

void ComboBox::setFont(LOGFONT & lf)
{
    font_.CreateFontIndirect(&lf);
    listBox_.setFont(lf);
    edit_.setFont(lf);
}

void ComboBox::setSelChange(SelChange && selChange)
{
    selChange_ = std::move(selChange);
}

void ComboBox::setDropDown(DropDown && dropDown)
{
    dropDown_ = std::move(dropDown);
}

void ComboBox::OnPaint()
{
    CPaintDC dc(this);
    CRect rectCombo;
    CBrush brushInser, brushOuter;
    COMBOBOXINFO comboInfo;
    CString strShow;

    GetWindowText(strShow);
    comboInfo.cbSize = sizeof(COMBOBOXINFO);
    GetComboBoxInfo(&comboInfo);
    GetClientRect(rectCombo);

    brushInser.CreateSolidBrush(interClr_);
    brushOuter.CreateSolidBrush(outerClr_);

    dc.FillRect(rectCombo, &brushInser);
    dc.FrameRect(rectCombo, &brushOuter);
    DrawPicture(&dc, comboInfo.rcButton);
    DrawShowText(&dc, rectCombo);
}   

void ComboBox::DrawItem(LPDRAWITEMSTRUCT lps)
{
}

void ComboBox::DrawPicture(CDC* pDC, CRect rect)
{
    if (defaultBmp_)
    {
        int centerx = rect.left + rect.Width() / 2;
        int centery = rect.top + rect.Height() / 2;
        int leftx = centerx - 5;
        int lefty = centery - 2;
        int rightx = centerx + 5;
        int righty = centery - 2;
        int bottomx = centerx;
        int bottomy = centery + 3;

        Gdiplus::Graphics gh(pDC->m_hDC);
        Gdiplus::Pen pen({130, 135, 144}, 1.55);
        gh.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
        gh.DrawLine(&pen, leftx, lefty, bottomx, bottomy);
        gh.DrawLine(&pen, bottomx, bottomy, rightx, righty);
    }
    else
    {
        rect.left = rect.right - rect.Height();
        CBitmap* oldBmp;
        auto memDc = new CDC;

        memDc->CreateCompatibleDC(pDC);
        oldBmp = memDc->SelectObject(&downBmp_);
        BITMAP bmp = { 0 };
        downBmp_.GetObject(sizeof(bmp), &bmp);
        pDC->StretchBlt(rect.left, rect.top, rect.Width(), rect.Height(), memDc, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
        memDc->SelectObject(oldBmp);

        ReleaseDC(memDc);
        delete memDc;
        memDc = nullptr;
    }
}

void ComboBox::DrawShowText(CDC* pDC, CRect rect)
{
    CRect rc = rect;
    rc.left += 3;
    CString text;
    GetWindowText(text);

    auto curFont = font_.GetSafeHandle() ? &font_ : GetFont();
    auto oldFont = pDC->SelectObject(curFont);
    int bkMode = pDC->SetBkMode(TRANSPARENT);
    pDC->SetTextColor(textClr_);
    pDC->DrawText(text, rc, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
    pDC->SelectObject(oldFont);
    pDC->SetBkMode(bkMode);
}

void ComboBox::OnCbnSelchange()
{
    Invalidate();
    if (selChange_) 
    {
        selChange_();
    }
    else 
    {
        parent_->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), CBN_SELCHANGE));
    }
}

void ComboBox::OnCbnDropdown()
{
    if (dropDown_) 
    {
        dropDown_();
    }
    else 
    {
        parent_->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), CBN_DROPDOWN));
    }
}



HBRUSH ComboBox::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CComboBox::OnCtlColor(pDC, pWnd, nCtlColor);

    if (nCtlColor == CTLCOLOR_LISTBOX) 
    {
        if (!listBox_.GetSafeHwnd()) 
        {
            listBox_.SubclassWindow(pWnd->GetSafeHwnd());
        }
    }
    else if (nCtlColor == CTLCOLOR_EDIT)
    {
        if (!edit_.GetSafeHwnd()) 
        {
            edit_.SubclassWindow(pWnd->GetSafeHwnd());
            edit_.SetFont(&edit_.getFont());
        }
    }
    return hbr;
}



void ComboBox::OnDestroy()
{
    if (edit_.GetSafeHwnd())
        edit_.UnsubclassWindow();
    if (listBox_.GetSafeHwnd())
        listBox_.UnsubclassWindow();
    CComboBox::OnDestroy();
}

void ComboBox::OnKillFocus(CWnd* pNewWnd)
{
    CComboBox::OnKillFocus(pNewWnd);
    Invalidate();
}


void ComboBox::OnSetFocus(CWnd* pOldWnd)
{
    CComboBox::OnSetFocus(pOldWnd);
    Invalidate();
}

} // !GCtrl
