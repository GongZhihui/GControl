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
#include "glistbox.h"

namespace GCtrl
{

BEGIN_MESSAGE_MAP(ListBox, CListBox)
   
END_MESSAGE_MAP()

ListBox::ListBox(CWnd &parent)
    : Basic{parent}
{
}

ListBox::~ListBox()
{
}

void ListBox::setItemColor(COLORREF bkColor, COLORREF textColor)
{
    itemBkClr_ = bkColor;
    itemTextClr_ = textColor;
}

void ListBox::setItemSelectedColor(COLORREF bkColor, COLORREF textColor)
{
    itemSelectedBkClr_ = bkColor;
    itemSelectedTextClr_ = textColor;
}

void ListBox::DrawItem(LPDRAWITEMSTRUCT lps)
{
    auto dc = CDC::FromHandle(lps->hDC);
    int item = lps->itemID;
    CRect rcItem = lps->rcItem;
    HICON hIcon = (HICON)lps->itemData;

    if (item != CB_ERR)
    {
        COLORREF clrBackground;
        COLORREF clrText;
        CRect rcText = rcItem;

        if (lps->itemState & ODS_SELECTED)  //如果当前项被选中
        {
            clrBackground = ::GetSysColor(COLOR_HIGHLIGHT);
            clrText = ~::GetSysColor(COLOR_WINDOWTEXT) & 0x00FFFFFF;

            if (itemSelectedBkClr_ != BadColor)
                clrBackground = itemSelectedBkClr_;
            if (itemSelectedTextClr_ != BadColor)
                clrText = itemSelectedTextClr_;
        }
        else
        {
            clrBackground = ::GetSysColor(COLOR_WINDOW);
            clrText = ::GetSysColor(COLOR_WINDOWTEXT);

            if (itemBkClr_ != BadColor)
                clrBackground = itemBkClr_;
            if (itemTextClr_ != BadColor)
                clrText = itemTextClr_;
        }

        auto curFont = font_.GetSafeHandle() ? &font_ : GetFont();
        auto oldFont = dc->SelectObject(curFont);
        dc->SetTextColor(clrText);
        dc->SetBkColor(clrBackground);
        dc->ExtTextOut(0, 0, ETO_OPAQUE, rcText, NULL, 0, NULL);
        CString text;
        GetText(item, text);
        rcText.left += 3;
        dc->DrawText(text, text.GetLength(), rcText, DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_WORD_ELLIPSIS);
        dc->SelectObject(oldFont);
    }
}

} //!namespace GCtrl