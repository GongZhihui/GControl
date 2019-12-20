#include "stdafx.h"
#include "glistbox.h"

namespace GCtrl
{

ListBox::ListBox()
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

void ListBox::setFont(CFont & font)
{
    if (!font.GetSafeHandle())
        return;
    LOGFONT lf;
    font.GetLogFont(&lf);
    setFont(lf);
}

void ListBox::setFont(const LOGFONT & lf)
{
    font_.CreateFontIndirect(&lf);
}

void ListBox::DrawItem(LPDRAWITEMSTRUCT lps)
{
    CDC *dc = CDC::FromHandle(lps->hDC);
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

        CFont *curFont = font_.GetSafeHandle() ? &font_ : GetFont();
        CFont *oldFont = dc->SelectObject(curFont);
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