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
    BOOL createModal(CRect rect = {0, 0, 100, 100}, CWnd* parent = nullptr);
    BOOL create(CRect rect = { 0, 0, 100, 100}, CWnd* parent = nullptr);
    void setWindowRect(const CRect &rect);

private:
    BOOL OnInitDialog();
    afx_msg LRESULT OnNcHitTest(CPoint point);
    DECLARE_MESSAGE_MAP()
    
private:
    DialogTemplate dialogTemplate_;
    CRect windowRect_;
};

}