#include "stdafx.h"
#include "ggroupbox.h"

namespace GCtrl 
{

BEGIN_MESSAGE_MAP(GroupBox, Static)
    ON_WM_PAINT()
END_MESSAGE_MAP()

GCtrl::GroupBox::GroupBox()
{
}

void GroupBox::setBorderColor(COLORREF color)
{
    borderClr_ = color;
}

void GroupBox::setTopPos(int pos)
{
    topPos_ = pos;
}

void GroupBox::OnPaint()
{
    CPaintDC dc(this); 
    CRect rccli;
    GetClientRect(&rccli);

    //创建画笔
    CPen pen;
    pen.CreatePen(PS_SOLID, 1, borderClr_);

    //选入画笔
    dc.SelectObject(pen);
    //只画一个矩形边框，不使用画刷擦除矩形内的图形
    dc.SelectStockObject(NULL_BRUSH);
    CFont *curFont = font_.GetSafeHandle() ? &font_ : GetFont();
    CFont *oldFont = dc.SelectObject(curFont);
    CString text;

    GetWindowText(text);
    //矩形的位置向下移动一些，给文本留一些位置
    rccli.top = topPos_ == -1 ? 7 : topPos_;
    dc.Rectangle(rccli);

    //显示文本
    CWnd *parent = GetParent();
    if (NULL != parent)
    {
        //根据父窗口像素点的颜色来获取父窗口的背景颜色
        COLORREF colorRef = parent->GetDC()->GetPixel(1, 1);
        //设置文本的背景颜色为父窗口的背景颜色    
        dc.SetBkColor(colorRef);
    }

    dc.TextOut(10, 0, text);
    dc.SelectObject(oldFont);
}

}
