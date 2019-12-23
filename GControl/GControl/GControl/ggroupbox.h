#pragma once
#include "stdafx.h"
#include "gstatic.h"

namespace GCtrl
{

class GroupBox : public Static
{
public:
    GroupBox();
    void setBorderColor(COLORREF color);
    void setTopPos(int pos);

    DECLARE_MESSAGE_MAP()
private:
    afx_msg void OnPaint();

private:
    COLORREF borderClr_{ RGB(160,160,160) };
    int topPos_ = -1;
};

} // !namespace GCtrl