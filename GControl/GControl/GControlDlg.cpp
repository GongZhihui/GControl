
// GControlDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "GControl.h"
#include "GControlDlg.h"
#include "afxdialogex.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGControlDlg 对话框



CGControlDlg::CGControlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GCONTROL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGControlDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_A, aCobo_);
    DDX_Control(pDX, IDC_EDIT_A, aEdit_);
}

BEGIN_MESSAGE_MAP(CGControlDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CGControlDlg 消息处理程序

BOOL CGControlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

    initComboBox();
    initEdit();

	return TRUE;  
}

void CGControlDlg::initComboBox()
{
    auto n = RGB(255,255,255);
    aCobo_.InsertString(0, "桔子");
    aCobo_.InsertString(1, "苹果");
    aCobo_.InsertString(2, "梨");
    aCobo_.InsertString(3, "梨");
    aCobo_.InsertString(4, "梨");
    aCobo_.InsertString(5, "梨");
    aCobo_.InsertString(6, "梨");
    aCobo_.InsertString(7, "梨");
    aCobo_.InsertString(8, "梨");
    aCobo_.setItemSelectedColor(RGB(255,0,0));
    CFont f;
    LOGFONT lf = { 0 };
    lf.lfHeight = 25;
    strcpy_s(lf.lfFaceName, "微软雅黑");
    f.CreateFontIndirectA(&lf);
    aCobo_.setFont(f);
    aCobo_.setItemHeight(30);
    aCobo_.setHeight(30);
    aCobo_.SetCurSel(0);
    //aCobo_.setItemColor(RGB(255,0,0));
}

void CGControlDlg::initEdit()
{
    aEdit_.SetWindowText("123456789");
    aEdit_.setBorderColor(RGB(255,0,0));
    aEdit_.setRoundPoint({ 10,10 });
    
    LOGFONT lf = { 0 };
    lf.lfHeight = 25;
    strcpy_s(lf.lfFaceName, "微软雅黑");
    f.CreateFontIndirectA(&lf);
    aEdit_.SetFont(&f);
    //aEdit_.SetReadOnly();
}


void CGControlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGControlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

