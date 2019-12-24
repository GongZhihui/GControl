#include "stdafx.h"
#include "basic.h"

namespace GCtrl
{

CString GetCurrentDir()
{
    CString path;
    GetCurrentDirectory(300, path.GetBuffer(200));
    path.ReleaseBuffer();
    return path;
}

Basic::Basic()
{
}

Basic::~Basic()
{
}

void Basic::setFont(CFont & font)
{
    if (!font.GetSafeHandle())
        return;
    LOGFONT lf;
    font.GetLogFont(&lf);
    setFont(lf);
}

void Basic::setFont(LOGFONT & lf)
{
    font_.CreateFontIndirect(&lf);
}

CFont & Basic::getFont()
{
    return font_;
}

} // !GCtrl
