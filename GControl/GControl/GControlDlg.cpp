
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
    DDX_Control(pDX, IDC_LISTBOX_A, aListbox_);
    DDX_Control(pDX, IDC_STATIC_DXAN, dcanStc);
    DDX_Control(pDX, IDC_RADIO_A, dxanAStc_);
    DDX_Control(pDX, IDC_RADIO_B, dxanBStc_);
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

    initBK();
    initComboBox();
    initEdit();
    initListBox();
    initMessage();
    initDXAN();

	return TRUE;  
}

void CGControlDlg::initBK()
{
    bk_.LoadBitmapA(IDB_BITMAP_BK);
    
    
}

void CGControlDlg::initComboBox()
{
    auto n = RGB(255,255,255);
    //aCobo_.loadDownPic(IDB_BITMAP1);
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
    lf.lfHeight = 24;
    strcpy_s(lf.lfFaceName, "微软雅黑");
    f.CreateFontIndirectA(&lf);
    aCobo_.setFont(f);
    aCobo_.setItemHeight(20);
    aCobo_.setHeight(25);
    aCobo_.SetCurSel(0);
    aCobo_.setTextColor(RGB(255, 0, 0));
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

void CGControlDlg::initListBox()
{
    auto n = RGB(255, 255, 255);
    //aCobo_.loadDownPic(IDB_BITMAP1);
    aListbox_.InsertString(0, "桔子");
    aListbox_.InsertString(1, "苹果");
    aListbox_.InsertString(2, "梨");
    aListbox_.InsertString(3, "梨");
    aListbox_.InsertString(4, "梨");
    aListbox_.InsertString(5, "梨");
    aListbox_.InsertString(6, "梨");
    aListbox_.InsertString(7, "梨");
    aListbox_.InsertString(8, "梨");
    aListbox_.setItemSelectedColor(RGB(255, 0, 0));
    CFont f;
    LOGFONT lf = { 0 };
    lf.lfHeight = 24;
    strcpy_s(lf.lfFaceName, "微软雅黑");
    f.CreateFontIndirectA(&lf);
    aListbox_.setFont(f);
    aListbox_.SetCurSel(0);

}

void CGControlDlg::initMessage()
{
}

void CGControlDlg::initDXAN()
{
    /*dxanAStc_.SetParent(&dcanStc);
    dxanBStc_.SetParent(&dcanStc);

    nvStc_.SetParent(&xbStc_);
    nanStc_.SetParent(&xbStc_);*/
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



void CGControlDlg::OnBnClickedRadioNan()
{
    // TODO: 在此添加控件通知处理程序代码
}
