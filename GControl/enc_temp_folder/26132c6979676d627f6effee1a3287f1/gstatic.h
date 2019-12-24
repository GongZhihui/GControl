#pragma once
#include "basic.h"

namespace GCtrl 
{

class Static 
    : public CStatic
    , public Basic
{
public:
    Static();
    DECLARE_MESSAGE_MAP()
    afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
};

} // !namespace GCtrl