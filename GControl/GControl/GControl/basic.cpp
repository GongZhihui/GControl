#include "Basic.h"
#include "stdafx.h"

namespace GCtrl
{

CString GetCurrentDir()
{
    CString path;
    GetCurrentDirectory(300, path.GetBuffer(200));
    path.ReleaseBuffer();
    return path;
}

} // !GCtrl
