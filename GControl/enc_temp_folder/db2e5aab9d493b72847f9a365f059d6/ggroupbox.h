#pragma once
#include "stdafx.h"
#include "gstatic.h"
#include <vector>

namespace GCtrl
{

class GroupBox : public Static
{
public:
    using RadioBtns = std::vector<CButton*>;

    GroupBox();
    void setBorderColor(COLORREF color);
    void setTopPos(int pos);
    void push_back(CButton *btn);
    RadioBtns &radioBtns();

    DECLARE_MESSAGE_MAP()
private:
    afx_msg void OnPaint();

private:
    RadioBtns radioBtns_;
    COLORREF borderClr_{ RGB(160,160,160) };
    int topPos_ = -1;
};

} // !namespace GCtrl