#pragma once

#include "stdafx.h"

namespace GCtrl 
{

constexpr auto ComboBoxDowmBmpPath = "\\GControl\\image\\combobox.bmp";
constexpr auto BadColor =  0xFFFFFFFF;
CString GetCurrentDir();


class Basic 
{
public:
    Basic();
    virtual ~Basic();

    // 这个font仅用作子类化时, 其他时候，请重新创建个font
    virtual void setFont(CFont &font);
    virtual void setFont(LOGFONT &lf);

    // 谨慎使用这个，最好只在子类化该控件时用这个
    // 其他时候，请重新创建个font
    CFont& getFont();

protected:
    CFont font_;
};

} //!GCtrl