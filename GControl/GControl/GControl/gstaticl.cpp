#include "stdafx.h"
#include "gstatic.h"

namespace GCtrl 
{

Static::Static()
{
}

BEGIN_MESSAGE_MAP(Static, CStatic)
    ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()


HBRUSH Static::CtlColor(CDC* pDC, UINT nCtlColor)
{
    pDC->SetBkMode(TRANSPARENT);
    return (HBRUSH)::GetStockObject(NULL_BRUSH);
}

} // !namespace GCtrl
