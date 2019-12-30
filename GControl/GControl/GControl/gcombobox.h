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
#include "gedit.h"
#include "glistbox.h"
#include <functional>

namespace GCtrl
{

class ComboBox 
    : public CComboBox
    , public Basic
{
    DECLARE_DYNAMIC(ComboBox)

public:
    using SelChange = std::function<void(void)>;
    using DropDown = std::function<void(void)>;

    ComboBox(CWnd &parent);
    virtual ~ComboBox();

    BOOL create(int id, IRect rect, int style);
    BOOL createDropDown(int id, IRect rect);
    BOOL createDropList(int id, IRect rect);

    // 加载图片
    void loadDownPic(int bmpID);
    void loadDownPic(const CString & bmpPath);

    // 设置下拉列表窗口文字颜色
    void setTextColor(COLORREF color);
    // 设置listbox背景颜色，文字颜色
    void setItemColor(COLORREF bkColor = BadColor, COLORREF textColor = BadColor);
    // 设置listbox选中行的背景颜色，文字颜色
    void setItemSelectedColor(COLORREF bkColor = BadColor, COLORREF textColor = BadColor);
    // 设置edit的背景颜色
    void setInterColor(COLORREF color);
    // 设置edit的外边框颜色
    void setOuterColor(COLORREF color);
    
    // 设置edit的高度
    void setHeight(int height);
    // 设置listbox的item高度
    void setItemHeight(int height);
    // 设置字体，listbox和edit的字体一样
    void setFont(CFont &font);
    void setFont(LOGFONT &lf);
   
    void setSelChange(SelChange &&selChange);
    void setDropDown(DropDown &&dropDown);

private:
    void DrawItem(LPDRAWITEMSTRUCT lps);
    void MeasureItem(LPMEASUREITEMSTRUCT){}
    void DeleteItem(LPDELETEITEMSTRUCT){}
    int CompareItem(LPCOMPAREITEMSTRUCT){return 0;}

    void DrawShowText(CDC* pDC, CRect rect);
    void DrawPicture(CDC* pDC, CRect rect);

private:
    // 在这里子类化edit和listbox
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg void OnPaint();
    afx_msg void OnCbnSelchange();
    afx_msg void OnCbnDropdown();
    afx_msg void OnDestroy();
    // 失去焦点和获取焦点时必须调用次刷新，
    // 否则下拉列表又会显示为Dropdown
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    afx_msg void OnSetFocus(CWnd* pOldWnd);

    DECLARE_MESSAGE_MAP()

private:
    CBitmap downBmp_;
    bool defaultBmp_{ true };
    COLORREF textClr_{ RGB(0, 0, 0) };
    COLORREF interClr_{ RGB(240, 250, 255) };
    COLORREF outerClr_{ RGB(195, 215, 220) };
    COLORREF btnClr_{ RGB(127,127,127) };

    ListBox listBox_{ *this };
    Edit edit_{ *this };

    SelChange selChange_;
    DropDown dropDown_;
};

} // !GCtrl