#pragma once
#include "stdafx.h"
#include "gdialog.h"

namespace GCtrl 
{

class messagebox : public Dialog 
{
public:
    messagebox();
    ~messagebox();

    static int info(const CString &title, const CString &caption);
};

}