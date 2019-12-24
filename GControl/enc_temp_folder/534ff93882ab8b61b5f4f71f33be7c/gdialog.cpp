#include "stdafx.h"
#include "gdialog.h"

namespace GCtrl 
{

CRect Dialog::BadRect = { -1, -1, -1, -1 };
CRect Dialog::InitRect = { 0, 0, 100, 100};

BEGIN_MESSAGE_MAP(Dialog, CDialog)
    ON_WM_NCHITTEST()
END_MESSAGE_MAP()

DialogTemplate::DialogTemplate(int size)
{
    buffer_ = new WORD[size];
    if ((!buffer_) || (TemplateMaxSize > size))
    {
        ASSERT((!buffer_) || (TemplateMaxSize > size));
        exit(0);
    }
}

DialogTemplate::~DialogTemplate()
{
    if (buffer_)
    {
        delete buffer_;
        buffer_ = nullptr;
    }
}


DLGTEMPLATE* DialogTemplate::create(DWORD style, CRect& rect, DWORD styleEx)
{
    WORD* temp = buffer_;
    DLGTEMPLATE* dlgTemp = (DLGTEMPLATE*)temp;

    rect.left = rect.left * 2 / 3;
    rect.right = rect.right * 2 / 3;
    rect.top = rect.top * 2 / 3;
    rect.bottom = rect.bottom * 2 / 3;

    // 对话框模版
    dlgTemp->style = style;
    dlgTemp->dwExtendedStyle = styleEx;
    dlgTemp->cdit = 0;

    dlgTemp->cx = rect.Width();
    dlgTemp->cy = rect.Height();
    dlgTemp->x = (short)rect.left;
    dlgTemp->y = (short)rect.top;

    temp = (WORD*)(dlgTemp + 1);

    // 菜单
    *temp++ = 0;
    // class
    *temp++ = 0;
    // caption
    // font
    return dlgTemp;
}
BOOL Dialog::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    SetWindowText("dialog");
    return TRUE;
}
LRESULT Dialog::OnNcHitTest(CPoint point)
{
    CRect rect;
    GetClientRect(rect);
    ClientToScreen(rect);

    if (rect.PtInRect(point))
        return HTCAPTION;

    return CDialog::OnNcHitTest(point);
}

Dialog::Dialog()
{
}

Dialog::~Dialog()
{
}

BOOL Dialog::createModal(CRect rect, CWnd* parent)
{
    auto rc = rect == BadRect ? InitRect : rect;
    auto temp = dialogTemplate_.create(WS_VISIBLE | WS_POPUP | WS_SYSMENU | WS_CLIPSIBLINGS, rc);
    return CDialogEx::InitModalIndirect(temp, parent);;
}

BOOL Dialog::create(CRect rect, CWnd* parent)
{
    auto rc = rect == BadRect ? InitRect : rect;
    auto temp = dialogTemplate_.create(WS_VISIBLE | WS_POPUP | WS_SYSMENU | WS_CLIPSIBLINGS, rc);
    return CDialogEx::CreateIndirect(temp, parent);;
}

void Dialog::setWindowRect(const CRect & rect)
{
    windowRect_ = rect;
}


} //!namespace GCtrl