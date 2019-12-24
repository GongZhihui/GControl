#pragma once
#include "stdafx.h"

namespace GCtrl 
{

constexpr auto TemplateMaxSize = 1024;

class DialogTemplate
{
public:
    DialogTemplate(int size = TemplateMaxSize);
    ~DialogTemplate();

    DLGTEMPLATE* create(DWORD style, CRect& rect, DWORD styleEx = 0);

private:
    WORD* buffer_;
};


class Dialog : public CDialogEx
{
public:
    Dialog();
    ~Dialog();

public:
    BOOL createModal(CRect rect = InitRect, CWnd* parent = nullptr);
    BOOL create(CRect rect = InitRect, CWnd* parent = nullptr);
    void setWindowRect(const CRect &rect);

    BOOL OnInitDialog();
    afx_msg LRESULT OnNcHitTest(CPoint point);
    DECLARE_MESSAGE_MAP()
    
private:
    DialogTemplate dialogTemplate_;

protected:
    static CRect BadRect;
    static CRect InitRect;
    CRect windowRect_;
};

}