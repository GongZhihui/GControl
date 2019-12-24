#pragma once
#include "stdafx.h"
#include "basic.h"

namespace GCtrl 
{

class Edit 
    : public CEdit
    , public Basic
{
public:
    Edit();
    ~Edit();

    // 设置边框颜色
    void setBorderColor(COLORREF color);
    // 设置圆角
    void setRoundPoint(CPoint point = {0,0});
    
private:
    DECLARE_MESSAGE_MAP()
    afx_msg void OnNcPaint();

private:
    COLORREF borderClr_{ RGB(195, 215, 220) };
    CPoint arcPoint_{ 0,0 };
};

}