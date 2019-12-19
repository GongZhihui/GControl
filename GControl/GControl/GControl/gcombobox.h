#pragma once
#include "stdafx.h"
#include "basic.h"
#include "gedit.h"

namespace GCtrl
{

class CoboListBox : public CListBox
{
public:
    CoboListBox();
    ~CoboListBox();

    COLORREF itemBkClr{ BadColor };
    COLORREF itemTextClr{ BadColor };
    COLORREF itemSelectedBkClr{ BadColor };
    COLORREF itemSelectedTextClr{ BadColor };
    CFont font;
private:
    void DrawItem(LPDRAWITEMSTRUCT lps);
    virtual void PreSubclassWindow();
};

class ComboBox : public CComboBox
{
    DECLARE_DYNAMIC(ComboBox)

public:
    ComboBox();
    virtual ~ComboBox();

    void loadDownPic(int bmpID);
    void loadDownPic(const CString & bmpPath);

    void setItemColor(COLORREF bkColor = BadColor, COLORREF textColor = BadColor);
    void setItemSelectedColor(COLORREF bkColor = BadColor, COLORREF textColor = BadColor);
    void setInterColor(COLORREF color);
    void setOuterColor(COLORREF color);
    
    void setHeight(int height);
    void setItemHeight(int height);

    void setFont(CFont &font);
private:
   
private:
    void DrawItem(LPDRAWITEMSTRUCT lps);
    void MeasureItem(LPMEASUREITEMSTRUCT lps);
    int CompareItem(LPCOMPAREITEMSTRUCT lps);
    void DrawShowText(CDC* pDC, CRect rect);
    void DrawPicture(CDC* pDC, CRect rect);
 
    virtual void PreSubclassWindow();
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

private:
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg void OnCbnSelchange();
    afx_msg void OnPaint();
    afx_msg void OnNcPaint();
    afx_msg void OnCbnDropdown();
    afx_msg void OnDestroy();

    DECLARE_MESSAGE_MAP()

private:
    CBitmap downBmp_;
    bool defaultBmp_{ false };
    COLORREF interClr_{ RGB(240, 250, 255) };
    COLORREF outerClr_{ RGB(195, 215, 220) };
    
    COLORREF itemBkClr_{ BadColor };
    COLORREF itemTextClr_{ BadColor };
    COLORREF itemSelectedBkClr_{ BadColor };
    COLORREF itemSelectedTextClr_{ BadColor };

    CFont font_;
    CoboListBox listBox_;
    GEdit edit_;
public:
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    afx_msg void OnSetFocus(CWnd* pOldWnd);
};

} // !GCtrl