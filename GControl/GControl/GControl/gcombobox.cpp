// CComboBoxLx.cpp: 实现文件
//
#include "stdafx.h"
#include "gcombobox.h"
#include "Basic.h"
#include "resource.h"


namespace GCtrl
{

CoboListBox::CoboListBox()
{
}

CoboListBox::~CoboListBox()
{
}

void CoboListBox::PreSubclassWindow()
{
    CListBox::PreSubclassWindow();
}

void CoboListBox::DrawItem(LPDRAWITEMSTRUCT lps)
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

            if (itemSelectedBkClr != BadColor)
                clrBackground = itemSelectedBkClr;
            if (itemSelectedTextClr != BadColor)
                clrText = itemSelectedTextClr;
        }
        else
        {
            clrBackground = ::GetSysColor(COLOR_WINDOW);
            clrText = ::GetSysColor(COLOR_WINDOWTEXT);

            if (itemBkClr != BadColor)
                clrBackground = itemBkClr;
            if (itemTextClr != BadColor)
                clrText = itemTextClr;
        }

        CFont *curFont = font.GetSafeHandle() ? &font : GetFont();
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

//----------------------------------------------------------------
// CComboBoxLx

IMPLEMENT_DYNAMIC(ComboBox, CComboBox)

ComboBox::ComboBox()
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

void ComboBox::setItemColor(COLORREF bkColor, COLORREF textColor)
{
    listBox_.itemBkClr = bkColor;
    listBox_.itemTextClr = textColor;
}

void ComboBox::setItemSelectedColor(COLORREF bkColor, COLORREF textColor)
{
    listBox_.itemSelectedBkClr = bkColor;
    listBox_.itemSelectedTextClr = textColor;
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
    font_.CreateFontIndirect(&lf);
    listBox_.font.CreateFontIndirect(&lf);
    edit_.font.CreateFontIndirect(&lf);
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

void ComboBox::MeasureItem(LPMEASUREITEMSTRUCT lps)
{
}

int ComboBox::CompareItem(LPCOMPAREITEMSTRUCT lps)
{
    return 0;
}


BEGIN_MESSAGE_MAP(ComboBox, CComboBox)
    ON_WM_PAINT()
    //ON_WM_NCPAINT()
    //ON_MESSAGE(WM_MOUSEHOVER, &ComboBox::OnMouseHover)
    //ON_MESSAGE(WM_MOUSELEAVE, &ComboBox::OnMouseLeave)
    ON_CONTROL_REFLECT(CBN_SELCHANGE, &ComboBox::OnCbnSelchange)
    //ON_CONTROL_REFLECT(CBN_DROPDOWN, &ComboBox::OnCbnDropdown)
    ON_WM_CTLCOLOR()
    ON_WM_DESTROY()
    ON_WM_KILLFOCUS()
    ON_WM_SETFOCUS()
END_MESSAGE_MAP()

BOOL ComboBox::PreCreateWindow(CREATESTRUCT& cs)
{
    return CComboBox::PreCreateWindow(cs);
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

        CPen pen, *oldPen;
        pen.CreatePen(PS_SOLID, 2, btnClr_);
        oldPen = pDC->SelectObject(&pen);
        pDC->MoveTo(leftx, lefty);
        pDC->LineTo(bottomx, bottomy);
        pDC->MoveTo(bottomx, bottomy);
        pDC->LineTo(rightx, righty);
        pDC->SelectObject(oldPen);
    }
    else
    {
        rect.left = rect.right - rect.Height();
        CBitmap* oldBmp;
        CDC* memDc = new CDC;

        memDc->CreateCompatibleDC(pDC);
        oldBmp = memDc->SelectObject(&downBmp_);
        BITMAP bmp = { 0 };
        downBmp_.GetObject(sizeof(bmp), &bmp);
        pDC->StretchBlt(rect.left, rect.top, rect.Width(), rect.Height(), memDc, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
        //pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), memDc, 0, 0, SRCCOPY);
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

    CFont *curFont = font_.GetSafeHandle() ? &font_ : GetFont();
    CFont* oldFont = pDC->SelectObject(curFont);
    int bkMode = pDC->SetBkMode(TRANSPARENT);
    pDC->DrawText(text, rc, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
    pDC->SelectObject(oldFont);
    pDC->SetBkMode(bkMode);
}


void ComboBox::OnMouseMove(UINT nFlags, CPoint point)
{
    TRACKMOUSEEVENT tme;

    tme.cbSize = sizeof(tme);
    tme.hwndTrack = m_hWnd;
    tme.dwHoverTime = 1;
    tme.dwFlags = TME_LEAVE | TME_HOVER;

    _TrackMouseEvent(&tme);

    CComboBox::OnMouseMove(nFlags, point);
}

LRESULT ComboBox::OnMouseHover(WPARAM wParam, LPARAM lParam)
{
    COMBOBOXINFO comboInfo;
    CRect rectBtn;
    CPoint point;

    comboInfo.cbSize = sizeof(COMBOBOXINFO);
    GetComboBoxInfo(&comboInfo);
    rectBtn = comboInfo.rcButton;
    ClientToScreen(rectBtn);
    GetCursorPos(&point);
    Invalidate(FALSE);

    return 1;
}

LRESULT ComboBox::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
    Invalidate();
    return 1;
}

void ComboBox::OnCbnSelchange()
{
    Invalidate();
}


void ComboBox::PreSubclassWindow()
{
    CComboBox::PreSubclassWindow();
}

void ComboBox::OnNcPaint()
{
}


void ComboBox::OnCbnDropdown()
{
    COMBOBOXINFO comboInfo;
    comboInfo.cbSize = sizeof(COMBOBOXINFO);
    GetComboBoxInfo(&comboInfo);
    CWindowDC dc(this);
    CRect rect;
    CBrush brush;
    brush.CreateSolidBrush(outerClr_);
    ::GetWindowRect(comboInfo.hwndList, rect);
    dc.FrameRect(rect, &brush);
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
            edit_.SetFont(&edit_.font);
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

