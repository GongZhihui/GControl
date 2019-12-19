#include "stdafx.h"
#include "gedit.h"

namespace GCtrl 
{
GEdit::GEdit()
{
}
GEdit::~GEdit()
{
}
void GEdit::setBorderColor(COLORREF color)
{
    borderClr_ = color;
}

void GEdit::setRoundPoint(CPoint point)
{
    arcPoint_ = point;
}


BEGIN_MESSAGE_MAP(GEdit, CEdit)
    ON_WM_NCPAINT()
    ON_WM_PAINT()
END_MESSAGE_MAP()


void GEdit::OnNcPaint()
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
    CPen *oldPen;
    dc.SelectObject(pen);
    dc.RoundRect(rect, arcPoint_);
}


}
