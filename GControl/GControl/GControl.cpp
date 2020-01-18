
// GControl.cpp: 定义应用程序的类行为。
//

#include "stdafx.h"
#include "GControl.h"
#include "GControlDlg.h"
#include "GControl/gcontrol.h"
#include "resource.h"
#include "CtrlDlg.h"
#include <GdiPlus.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGControlApp

BEGIN_MESSAGE_MAP(CGControlApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CGControlApp 构造

CGControlApp::CGControlApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CGControlApp 对象

CGControlApp theApp;


// CGControlApp 初始化

BOOL CGControlApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
	CWinApp::InitInstance();
	AfxEnableControlContainer();
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    auto nnn = static_cast<int>(3.78);
    auto nnnn = std::round(3.78);
    

    GCtrl::IRect rett1;
    GCtrl::DRect ret{1.1,2.6,3.7,5.5};
    auto n = ret.right();
    auto rect1 = ret.crect();
    auto rett = [](RECT ret) 
    {
        return ret.bottom;
    };
    n = rett(ret);

    GCtrl::MsgBox::init(IDB_BITMAP_MSG_BK, IDB_BITMAP_MSG_OK, IDB_BITMAP_MSG_CLOSE);
    GCtrl::MsgBox::info_time("开具成功!", 2000,"啥东西哇发票已经开具成功");
    GCtrl::MsgBox::info("发票已经开具成功, 无法重新开票, 但数据上传异常, 请联系服务单位进行处理！");
    CCtrlDlg cdlg;
    cdlg.DoModal();

    /*GCtrl::Dialog dlg1;
    CString result;
    dlg1.createModal(CRect(0, 0, 100, 100));
    if (IDOK == dlg1.DoModal())
    {

    }*/

    /*GCtrl::Dialog dlg1;
    CString result;
    if (dlg1.create(CRect(0, 0, 100, 100)))
    {
        dlg1.ShowWindow(SW_SHOW);
    }*/
    CRect rect = { 0,0,100,100 };
   

	CGControlDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}



int CGControlApp::ExitInstance()
{
    Gdiplus::GdiplusShutdown(gdiplusToken);
    return CWinApp::ExitInstance();
}
