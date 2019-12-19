#pragma once
#include "stdafx.h"

namespace GCtrl 
{

class GEdit : public CEdit 
{
public:
    GEdit();
    ~GEdit();

    CFont font;

    void setBorderColor(COLORREF color);
    void setRoundPoint(CPoint point = {0,0});
private:
    DECLARE_MESSAGE_MAP()
    afx_msg void OnNcPaint();

private:
    COLORREF borderClr_{ RGB(195, 215, 220) };
    CPoint arcPoint_{ 0,0 };
};

}