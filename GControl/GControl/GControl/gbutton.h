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
#include "ggroupbox.h"
#include <functional>

namespace GCtrl 
{

/** Button 一个基类
    类型：
        PushButton 普通按钮
        Radio 单选框 必须配合GCtrl::GroupBbox, 不可使用GetCheck和SetCheck，得使用getCheck和setCheck
        CheckBox 复选框 不可使用GetCheck和SetCheck，得使用getCheck和setCheck
        ButtonEx 可使用CButton的全部函数，区别是自带背景透明
        
        以上几种子类未提供默认构造,都必须有parent

*/
class Button 
    : public CButton
    , public Basic
{
public:
    // 点击事件
    using ClickedEvent = std::function<void(bool)>;

    enum class BtnType
    {
        PushButton,
        Radio,
        CheckBox,
        // 就是系统按钮，背景透明
        ButtonEx
    };

    // 使用引用是为了保证父对象必须存在
    Button(CWnd &parent);
    Button(BtnType type, CWnd &parent);
    virtual ~Button();

    virtual BOOL create(int id, const IRect &rect, const char *text,
        int style = WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON);

    void setSize(const CRect &rect);
    void setSize(int width, int height);
    void setSize(const CSize &size);

    void setBitmap(int normalBmpID, int hoverBmpID = -1, int pressedBmpID = -1);
    CSize getBitmapSize();
    void setCheck(bool check = true);
    bool getCheck();
  
    void setGroup(GroupBox *group);

    void setClickedEvent(ClickedEvent &&clicked);

private:
    void DrawItem(LPDRAWITEMSTRUCT lps);
    void OnPaint();
    void PreSubclassWindow() override;
    HBRUSH CtlColor(CDC *dc, UINT col);
    afx_msg void OnMouseHover(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnMouseLeave();
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnBnClicked();
    DECLARE_MESSAGE_MAP()

protected:
    ClickedEvent clickedEvent_;
    BtnType btnType_{ BtnType::PushButton };
    CBitmap hoverbmp_;
    CBitmap normalbmp_;
    CBitmap pressedbmp_;

    CRect iconRect_;
    GroupBox *group_{ nullptr };

    COLORREF bkcolor_{ BadColor };
    CBrush bkbrush_;

    bool hover_{ false };
    bool press_{ false };
    bool check_{ false };
};

class PushButton : public Button 
{
public:
    PushButton(CWnd &parent);
    BOOL create(int id, const IRect &rect);
};

class RadioButton : public Button 
{
public:
    RadioButton(CWnd &parent);
    BOOL create(int id, const IRect &rect);

};

class CheckBox : public Button 
{
public:
    CheckBox(CWnd &parent);
    BOOL create(int id, const IRect &rect);
};

// 系统button，自动背景透明
class ButtonEx : public Button 
{
public:
    ButtonEx(CWnd &parent);
};


} // !namespace GCtrl