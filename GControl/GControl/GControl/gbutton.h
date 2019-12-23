#pragma once
#include "stdafx.h"

namespace GCtrl 
{

class Button : public CButton
{
public:
    enum class BtnType
    {
        PushButton,
        Radio,
        CheckBox
    };

    Button();
    Button(BtnType type);
    virtual ~Button();

    void setSize(const CRect &rect);
    void setSize(int width, int height);
    void setBitmap(int normalBmpID, int hoverBmpID = -1, int pressedBmpID = -1);
    void setCheck(bool check = true);
    bool getCheck();

private:
    void DrawItem(LPDRAWITEMSTRUCT lps);
    void PreSubclassWindow() override;
    afx_msg void OnMouseHover(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnMouseLeave();
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
    DECLARE_MESSAGE_MAP()

protected:
    BtnType btnType_{ BtnType::PushButton };
    CBitmap hoverbmp_;
    CBitmap normalbmp_;
    CBitmap pressedbmp_;

    bool hover_{ false };
    bool press_{ false };
    bool check_{ false };
};

class PushButton : public Button 
{
public:
    PushButton();
};

class RadioButton : public Button 
{
public:
    RadioButton();
};

class CheckBox : public Button 
{
public:
    CheckBox();
};





} // !namespace GCtrl