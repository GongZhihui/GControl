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
    ListBox();
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