//------------------------------------------------------------------------------
/*
    This file is part of gcontrol: https://github.com/gongzhihui/gcontrol
    Copyright (c) 2019 龚志慧.
    Permission to use, copy, modify, and/or distribute this software for any
    purpose  with  or without fee is hereby granted, provided that the above
    copyright notice and this permission notice appear in all copies.
    THE  SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
    WITH  REGARD  TO  THIS  SOFTWARE  INCLUDING  ALL  IMPLIED  WARRANTIES  OF
    MERCHANTABILITY  AND  FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
    ANY  SPECIAL ,  DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
    WHATSOEVER  RESULTING  FROM  LOSS  OF USE, DATA OR PROFITS, WHETHER IN AN
    ACTION  OF  CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
//==============================================================================

#include "stdafx.h"
#include "gprogressdialog.h"
#include "gctrlhelper.h"
#include <thread>

namespace GCtrl
{

namespace 
{
int BK_ID = 0;
int CLOSE_ID = 1;
int PROGRESS_ID = 2;
int TIP_ID = 3;
int WM_PROGRESS_UPDATA = WM_USER + 0xFFF;

CRect INIT_RECT = { 0,0,500,200 };

}

BEGIN_MESSAGE_MAP(ProgressDialog, Dialog)
    ON_MESSAGE(WM_PROGRESS_UPDATA, OnUpdateProgressMessage)
END_MESSAGE_MAP()

ProgressDialog::ProgressDialog(CWnd & parent,
    const CString &tip,
    int bkBmpID, 
    int closeBmpID)
    : parent_(&parent)
    , bkBmpID_(bkBmpID)
    , closeBmpID_(closeBmpID)
    , tip_(tip)
    , execEvent_(false, false, "ExecSuccess", NULL)
    , showEvent_(false, false, "ShowSuccess", NULL)
{
}

int ProgressDialog::show()
{
    createModal(INIT_RECT, parent_);
    return DoModal();
}

void ProgressDialog::close()
{
    execEvent_.SetEvent();
    WaitForSingleObject(showEvent_.m_hObject, INFINITE);
}

BOOL ProgressDialog::OnInitDialog()
{
    createCtrl();
    initBK();
    initFont();
    initCtrl();
    std::thread([&]() {updatePosThread(); }).detach();
    return FALSE;
}

void ProgressDialog::createCtrl()
{
    bkStc_.create(BK_ID, { 0,0, 0, 0 }, "", WS_CHILD | WS_VISIBLE | SS_CENTER | SS_BITMAP);
    tipStc_.create(TIP_ID, { 70, 76, 350, 26 }, "");
    closeBtn_.create(CLOSE_ID, { 472, 6, 12, 15 });
    CRect rect;
    tipStc_.GetWindowRect(rect);
    ScreenToClient(rect);
    rect.OffsetRect(0, 25);
    rect.bottom -= 5;
    progress_.Create(WS_CHILD | WS_VISIBLE, rect, this, PROGRESS_ID);
}

void ProgressDialog::initBK()
{
    bkbmp_.LoadBitmapA(bkBmpID_);
    bkStc_.ModifyStyle(0xF, SS_BITMAP | SS_REALSIZECONTROL);

    bkStc_.SetBitmap(bkbmp_);
    CRect rect;
    GetClientRect(rect);
    bkStc_.MoveWindow(rect);
}

void ProgressDialog::initFont()
{
}

void ProgressDialog::initCtrl()
{
    tipStc_.SetWindowTextA(tip_);

    closeBtn_.setBitmap(closeBmpID_);
 
    progress_.SetRange(0, 100);
    progress_.SetStep(1);
    progress_.SetPos(1);
}

void ProgressDialog::setProgressData(int pos)
{
    UpdateData(false);
    int lower = 0;
    int upper = 0;
    progress_.GetRange(lower, upper);
    progress_.SetPos(pos);

    UpdateData(false);

    if (upper == progress_.GetPos())
    {
        OnOK();
    }
}

void ProgressDialog::updatePosThread()
{
    int progressVal = 1;
    int waitTime = 10;
  
    while (true)
    {
        if (WaitForSingleObject(execEvent_.m_hObject, waitTime) != WAIT_OBJECT_0)
        {
            progressVal++;
            if (progressVal < 95)
            {
                if (progressVal > 60)
                {
                    waitTime += 100;
                }
                PostMessage(WM_PROGRESS_UPDATA, (WPARAM)progressVal, 0);
            }
        }
        else
        {
            progressVal = 100;
            PostMessage(WM_PROGRESS_UPDATA, (WPARAM)progressVal, 0);
            showEvent_.SetEvent();
            return;
        }
    }

    while (progressVal < 100)
    {
        Sleep(150);
        progressVal++;
        PostMessage(WM_PROGRESS_UPDATA, (WPARAM)progressVal, 0);
    }

    progressVal = 100;
    PostMessage(WM_PROGRESS_UPDATA, (WPARAM)progressVal, 0);
    showEvent_.SetEvent();
    return;
}

LRESULT ProgressDialog::OnUpdateProgressMessage(WPARAM wParam, LPARAM lParam)
{
    int progressVal = (int)wParam;
    setProgressData(progressVal);
    return 0;
}



}
