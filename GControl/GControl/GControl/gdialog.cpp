#include "stdafx.h"
#include "gdialog.h"

namespace GCtrl 
{

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
    auto temp = dialogTemplate_.create(WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_POPUP | DS_MODALFRAME, rect);
    return CDialogEx::InitModalIndirect(temp, parent);;
}

BOOL Dialog::create(CRect rect, CWnd* parent)
{
    auto temp = dialogTemplate_.create(WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_POPUP, rect);
    return CDialogEx::CreateIndirect(temp, parent);;
}

void Dialog::setWindowRect(const CRect & rect)
{
    windowRect_ = rect;
}


} //!namespace GCtrl