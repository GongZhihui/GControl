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
#include "gbutton.h"
#include <GdiPlus.h>

namespace GCtrl
{

BEGIN_MESSAGE_MAP(Button, CButton)
    ON_WM_CTLCOLOR_REFLECT()
    ON_WM_MOUSEHOVER()
    ON_WM_MOUSEMOVE()
    ON_WM_MOUSELEAVE()
    ON_WM_SETCURSOR()
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_CONTROL_REFLECT(BN_CLICKED, &Button::OnBnClicked)
END_MESSAGE_MAP()

Button::Button(CWnd &parent)
    : parent_{ &parent}
{
}

HBRUSH Button::CtlColor(CDC *dc, UINT col)
{
    CRect rc, cli;
    CClientDC pdc(parent_);
    GetWindowRect(rc);
    cli = rc;
    parent_->ScreenToClient(&rc);
    auto color = pdc.GetPixel(rc.left + rc.Width() / 2, rc.top + rc.Height() / 2);
    bkcolor_ = bkcolor_ == BadColor ? color : bkcolor_;
    ScreenToClient(&cli);
    dc->FillSolidRect(cli, bkcolor_);
    return (HBRUSH)::GetStockObject(NULL_BRUSH);
}

Button::Button(BtnType type, CWnd &parent)
    : btnType_{type}
    , parent_{&parent}
{
}

Button::~Button()
{
}

void Button::OnMouseHover(UINT nFlags, CPoint point)
{
    CButton::OnMouseHover(nFlags, point);
    hover_ = true;
    InvalidateRect(iconRect_);
}

void Button::OnMouseMove(UINT nFlags, CPoint point)
{
    CButton::OnMouseMove(nFlags, point);
    TRACKMOUSEEVENT  tme = { 0 };
    tme.cbSize = sizeof(TRACKMOUSEEVENT);
    tme.dwFlags = TME_HOVER | TME_LEAVE;
    tme.dwHoverTime = 50;
    tme.hwndTrack = this->m_hWnd;
    if (TrackMouseEvent(&tme)) {}
    hover_ = true;
}

void Button::OnMouseLeave()
{
    CButton::OnMouseLeave();
    hover_ = false;
    Invalidate();
}

void GCtrl::Button::OnBnClicked()
{
    if (clickedEvent_)
        clickedEvent_(check_);
}

void Button::DrawItem(LPDRAWITEMSTRUCT lps)
{
    auto dc = CDC::FromHandle(lps->hDC);
    CRect rect = lps->rcItem;
    CRect winRect;
    GetWindowRect(winRect);

    auto drawBtn = [&]()
    {
        Gdiplus::Color color;
        if (hover_)
            color = { 0,120,215 };
        else
            color = { 56, 56, 56 };
        Gdiplus::Graphics gh(lps->hDC);
        // 以高为边的正方形
        Gdiplus::Rect rc = { rect.left, rect.top, rect.Height() - 4, rect.Height() - 4 };
        iconRect_ = { rect.left, rect.top, rect.Height(), rect.Height()};
        rc.X += 1;
        rc.Y += 1;
        Gdiplus::Pen pen(color);
        
        if (btnType_ == BtnType::Radio)
        {
            gh.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
            gh.FillEllipse(&Gdiplus::SolidBrush({ 255,255,255 }), rc);
            gh.DrawEllipse(&pen, rc);
            if (check_) 
            {
                rc.X += 3;
                rc.Y += 3;
                rc.Width = rc.Width - 6;
                rc.Height = rc.Width;
                gh.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
                gh.FillEllipse(&Gdiplus::SolidBrush(color), rc);
            }
        }
        else if(btnType_ == BtnType::CheckBox)
        {
            gh.FillRectangle(&Gdiplus::SolidBrush({ 255,255,255 }), rc);
            gh.DrawRectangle(&pen, rc);
            if (check_) 
            {
                // √的位置(0, 1/2),(1/3, 1/4),(1, 3/4) 单位长度为1下的坐标
                Gdiplus::Point left = { rc.X + 1, rc.Y + rc.Height / 2 - 1 };
                Gdiplus::Point right = { rc.X + rc.Width - 1, rc.Y + rc.Height / 4 };
                Gdiplus::Point bottom = { rc.X + rc.Width / 3, rc.Y + rc.Height * 3 / 4 };
                Gdiplus::Pen pen(color, 1.52);
                gh.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
                gh.DrawLine(&pen, left, bottom);
                gh.DrawLine(&pen, bottom, right);
            }
        }
    };
    auto drawText = [&]()
    {
        CDC memDC;
        memDC.CreateCompatibleDC(dc);
        CRect rc = rect;
        rc.left += rc.Height() - 4;
        CString text;
        GetWindowText(text);
        dc->SetBkMode(TRANSPARENT);
        dc->DrawText(text, rc, DT_VCENTER | DT_CENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
    };

    if (btnType_ == BtnType::PushButton) 
    {
        BITMAP bitmap;
        CDC memDc;
        memDc.CreateCompatibleDC(dc);

        if (hover_)
        {
            if (press_)
            {
                pressedbmp_.GetBitmap(&bitmap);
                memDc.SelectObject(pressedbmp_);
            }
            else
            {
                hoverbmp_.GetBitmap(&bitmap);
                memDc.SelectObject(hoverbmp_);
            }
        }
        else 
        {
            if (press_)
            {
                pressedbmp_.GetBitmap(&bitmap);
                memDc.SelectObject(pressedbmp_);
            }
            else
            {
                hoverbmp_.GetBitmap(&bitmap);
                memDc.SelectObject(hoverbmp_);
            }
        }
        dc->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &memDc, 0, 0, SRCCOPY);
    }
    else if (btnType_ == BtnType::Radio)
    {
        drawBtn();
        drawText();
    }
    else if(btnType_ == BtnType::CheckBox)
    {
        drawBtn();
        drawText();
    }

}

void Button::OnPaint()
{
    CPaintDC dc(this);
    CRect rcClient, rcClip, rcHeader;
    GetClientRect(&rcClient);

    dc.GetClipBox(&rcClip);

    CDC MemDC;
    CBitmap MemBitmap, *pOldBitmap;

    MemDC.CreateCompatibleDC(&dc);
    int nMode = MemDC.SetMapMode(dc.GetMapMode());

    MemBitmap.CreateCompatibleBitmap(&dc, rcClient.Width(), rcClient.Height());
    pOldBitmap = MemDC.SelectObject(&MemBitmap);
    MemDC.FillSolidRect(&rcClient, GetBkColor(dc.m_hDC));

    CRgn rgn;
    rgn.CreateRectRgn(rcClip.left, rcClip.top, rcClip.right, rcClip.bottom);
    MemDC.SelectClipRgn(&rgn);
    DefWindowProc(WM_PAINT, (WPARAM)MemDC.m_hDC, (LPARAM)0);
    MemDC.SelectClipRgn(NULL);

    if (rcClip.top < rcHeader.Height())
        rcClip.top = rcHeader.Height();

    dc.BitBlt(rcClip.left, rcClip.top, rcClip.Width(), rcClip.Height(), &MemDC, rcClip.left, rcClip.top, SRCCOPY);

    MemDC.SetMapMode(nMode);
    MemDC.SelectObject(pOldBitmap);
    MemDC.DeleteDC();
    MemBitmap.DeleteObject();
    rgn.DeleteObject();
    
}

void Button::OnLButtonDown(UINT nFlags, CPoint point)
{
    press_ = true;
    CButton::OnLButtonDown(nFlags, point);
}


void Button::OnLButtonUp(UINT nFlags, CPoint point)
{
    press_ = false;
    if (btnType_ == BtnType::Radio) 
    {
        if (group_) 
        {
            for (const auto & it : group_->radioBtns()) 
            {
                if (this == it) 
                {
                    check_ = true;
                }
                else 
                {
                    static_cast<RadioButton*>(it)->setCheck(false);
                    it->Invalidate();
                }
            }
        }
    }
    else
    {
        check_ = check_ ? false : true;
    }

    CButton::OnLButtonUp(nFlags, point);
}

BOOL Button::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
    if(hover_)
        ::SetCursor(::LoadCursor(NULL, IDC_HAND));
    else 
        ::SetCursor(::LoadCursor(NULL, IDC_ARROW));

    return TRUE;
}

void Button::PreSubclassWindow()
{
    if(btnType_ != BtnType::ButtonEx)
        ModifyStyle(0, BS_OWNERDRAW, SWP_FRAMECHANGED);
    CButton::PreSubclassWindow();
}

void Button::setSize(const CRect & rect)
{
    setSize(rect.Width(), rect.Height());
}

void Button::setSize(const CSize & size)
{
    setSize(size.cx, size.cy);
}

void Button::setSize(int width, int height)
{
    CRect rc;
    GetWindowRect(rc);
    int left = rc.left + rc.Width() / 2 - width / 2;
    int top = rc.top + rc.Height() / 2 - height / 2;
    MoveWindow(left, top, width, height);

}

void Button::setBitmap(int normalBmpID, int hoverBmpID, int pressedBmpID)
{
    normalbmp_.LoadBitmap(normalBmpID);
    if (hoverBmpID != -1) 
    {
        hoverbmp_.LoadBitmap(hoverBmpID);
        if (pressedBmpID != -1) 
            pressedbmp_.LoadBitmap(pressedBmpID);
        else 
            pressedbmp_.LoadBitmap(hoverBmpID);
    }
    else 
    {
        hoverbmp_.LoadBitmap(normalBmpID);
        pressedbmp_.LoadBitmap(normalBmpID);
    }

    setSize(getBitmapSize());
}

CSize Button::getBitmapSize()
{
    CSize size;
    if (normalbmp_.m_hObject) 
    {
        BITMAP bmp;
        normalbmp_.GetBitmap(&bmp);
        size.cx = bmp.bmWidth;
        size.cy = bmp.bmHeight;
    }

    return size;
}

void Button::setCheck(bool check)
{
    check_ = check;
}

bool Button::getCheck()
{
    return check_;
}

void Button::setParent(CWnd * parent)
{
    parent_ = parent;
}

void Button::setGroup(GroupBox * group)
{
    group_ = group;
    group_->push_back(this);
}

void Button::setClickedEvent(ClickedEvent &&clicked)
{
    clickedEvent_ = std::move(clicked);
}

PushButton::PushButton(CWnd &parent)
    : Button{ BtnType::PushButton, parent}
{
}

RadioButton::RadioButton(CWnd &parent)
    : Button{BtnType::Radio, parent}
{
}

CheckBox::CheckBox(CWnd &parent)
    : Button{BtnType::CheckBox, parent}
{
}

ButtonEx::ButtonEx(CWnd & parent)
    : Button{ BtnType::ButtonEx, parent }
{
}

} // !namespace GCtrl
