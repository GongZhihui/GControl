#pragma once
#include "stdafx.h"

namespace GCtrl 
{

class Edit : public CEdit 
{
public:
    Edit();
    ~Edit();

    // 设置边框颜色
    void setBorderColor(COLORREF color);
    // 设置圆角
    void setRoundPoint(CPoint point = {0,0});
    // 这个font仅用作子类化时, 其他时候，请重新创建个font
    void setFont(CFont &font);
    void setFont(const LOGFONT &lf);
    
    // 谨慎使用这个，最好只在子类化该控件时用这个
    // 其他时候，请重新创建个font
    CFont& getFont();

private:
    DECLARE_MESSAGE_MAP()
    afx_msg void OnNcPaint();

private:
    COLORREF borderClr_{ RGB(195, 215, 220) };
    CPoint arcPoint_{ 0,0 };
    CFont font_;
};

}