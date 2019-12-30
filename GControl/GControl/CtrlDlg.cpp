// CtrlDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "GControl.h"
#include "CtrlDlg.h"
#include "afxdialogex.h"
#include "resource.h"


// CCtrlDlg 对话框

IMPLEMENT_DYNAMIC(CCtrlDlg, CDialogEx)

CCtrlDlg::CCtrlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CTRL, pParent)
{

}

CCtrlDlg::~CCtrlDlg()
{
}

void CCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_STATIC_CTRL_ZWFL, zwflGpbox_);
    DDX_Control(pDX, IDC_RADIO_CTRL_CXY, cxyRiobtn_);
    DDX_Control(pDX, IDC_RADIO_CTRL_XMJL, xmjlRiobtn_);
    DDX_Control(pDX, IDC_RADIO_CTRL_XS, xsRiobtn_);
    DDX_Control(pDX, IDC_STATIC_CTRL_TIP, tipStc_);
    DDX_Control(pDX, IDC_BUTTON_TEST, testBtn_);
    DDX_Control(pDX, IDC_RADIO_TEST, testRiobtn_);
    DDX_Control(pDX, IDC_CHECK_TEST, testChkbox_);
    DDX_Control(pDX, IDC_RADIO_TEST2, testRiobtn2_);
    DDX_Control(pDX, IDC_RADIO_TEST3, testRiobtn3_);
    DDX_Control(pDX, IDC_DATETIMEPICKER, dtc_);
    DDX_Control(pDX, IDC_CHECK_TEST2, testCheckBox_);
    DDX_Control(pDX, IDC_EDIT_TEST_T, testEdit_);
}


BEGIN_MESSAGE_MAP(CCtrlDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_TEST, &CCtrlDlg::OnBnClickedButtonTest)
    ON_BN_CLICKED(IDC_BUTTON1, &CCtrlDlg::OnBnClickedButton1)
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CCtrlDlg 消息处理程序


BOOL CCtrlDlg::OnInitDialog()
{
    __super::OnInitDialog();
    initBK();
    initGroupBox();
    initBtn();

    return TRUE;  
}

void CCtrlDlg::initBK()
{
    super::initBK(this, bkbmp_, IDC_STATIC_CTRL_BK, IDB_BITMAP_BK);
}

void CCtrlDlg::initGroupBox()
{
    LOGFONT lf = { 0 };
    lf.lfHeight = 30;
    strcpy_s(lf.lfFaceName, "微软雅黑");

    zwflGpbox_.setFont(lf);
    zwflGpbox_.setTopPos(14);
    zwflGpbox_.setBorderColor(RGB(255, 0, 0));
}

void CCtrlDlg::initBtn()
{
    testBtn_.setBitmap(IDB_BITMAP_SPSZ, IDB_BITMAP_SPSZ_HOVER, IDB_BITMAP_SPSZ_PRESS);
    testBtn_.setSize({0,0,80,26});
    testBtn_.setParent(*this);
    testRiobtn_.setCheck();
    testRiobtn_.setParent(*this);
    testRiobtn_.setGroup(&zwflGpbox_);
    testRiobtn2_.setParent(*this);
    testRiobtn2_.setGroup(&zwflGpbox_);
    testRiobtn3_.setParent(*this);
    testRiobtn3_.setGroup(&zwflGpbox_);

    testChkbox_.setCheck();
    testChkbox_.setParent(*this);

    tipStc_.setTextColor(RGB(255,0,0));
    /*testEdit_.setTextColor(RGB(0,0,0));
    testEdit_.setBKColor(RGB(255,0,0));
    testEdit_.setBorderColor(RGB(255,0,0));*/
    testEdit_.SetWindowTextA("这是一个编辑框");
}


void CCtrlDlg::OnBnClickedButtonTest()
{
    CString log;
    log.Format("%d %d %d %d -%d == %d %d %d", testRiobtn_.getCheck(), 
        testRiobtn2_.getCheck(), testRiobtn3_.getCheck(),
        testChkbox_.getCheck(), testCheckBox_.GetCheck() == BST_CHECKED,
        cxyRiobtn_.GetCheck(), xmjlRiobtn_.GetCheck(), xsRiobtn_.GetCheck());
    AfxMessageBox(log);
}


void CCtrlDlg::OnBnClickedButton1()
{
    OnOK();
}


HBRUSH CCtrlDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = __super::OnCtlColor(pDC, pWnd, nCtlColor);

    /*if (pWnd->GetDlgCtrlID() == IDC_EDIT_TEST_T && (nCtlColor == CTLCOLOR_EDIT))
    {
        static CBrush brush;
        if(!brush.m_hObject)
            brush.CreateSolidBrush(RGB(255,0,0));
        pDC->SetTextColor(RGB(0, 0, 0));
        pDC->SetBkMode(TRANSPARENT);

        return brush;
    }*/
    return hbr;
}
