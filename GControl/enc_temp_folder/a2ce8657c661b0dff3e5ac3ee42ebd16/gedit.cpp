#include "stdafx.h"
#include "gedit.h"

namespace GCtrl 
{

BEGIN_MESSAGE_MAP(Edit, CEdit)
    ON_WM_NCPAINT()
END_MESSAGE_MAP()

Edit::Edit()
{
}
Edit::~Edit()
{
}
void Edit::setBorderColor(COLORREF color)
{
    borderClr_ = color;
}

void Edit::setRoundPoint(CPoint point)
{
    arcPoint_ = point;
}

void Edit::OnNcPaint()
{
    CWindowDC dc(this);
    CRect rect;
    GetWindowRect(rect);
    rect = CRect(0, 0, rect.right - rect.left, rect.bottom - rect.top);
    rect.InflateRect(-1, -1);
    rect.left -= 1;
    rect.right += 1;
    rect.top -= 1;
    rect.bottom += 1;
    CPen pen;
    pen.CreatePen(PS_SOLID, 1, borderClr_);
    dc.SelectObject(pen);
    dc.RoundRect(rect, arcPoint_);
}


}
