// CtrlDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "GControl.h"
#include "CtrlDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "GControl/gcontrol.h"
#include <thread>

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
    DDX_Control(pDX, IDC_BUTTON_TSYX, tsyxBtn_);
    DDX_Control(pDX, IDC_TREE_TEST, testTree_);
}


BEGIN_MESSAGE_MAP(CCtrlDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_TEST, &CCtrlDlg::OnBnClickedButtonTest)
    ON_BN_CLICKED(IDC_BUTTON1, &CCtrlDlg::OnBnClickedButton1)
    ON_WM_CTLCOLOR()
    ON_WM_NCHITTEST()
    ON_BN_CLICKED(IDC_BUTTON_TSYX, &CCtrlDlg::OnBnClickedButtonTsyx)
    ON_NOTIFY(TVN_ITEMEXPANDED, IDC_TREE_TEST, &CCtrlDlg::OnTvnItemexpandedTreeTest)
    ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_TEST, &CCtrlDlg::OnTvnSelchangedTreeTest)
END_MESSAGE_MAP()


// CCtrlDlg 消息处理程序


BOOL CCtrlDlg::OnInitDialog()
{
    __super::OnInitDialog();
    initTreeCtrl();
    initBK();
    initGroupBox();
    initBtn();
    createCtrl();

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

    tsyxBtn_.setBitmap(IDB_PNG_TSYX);
    //tsyxBtn_.setBitmap(IDB_BITMAP_TSYX);

    testChkbox_.setCheck();
    testChkbox_.setParent(*this);

    tipStc_.setTextColor(RGB(255,0,0));
    /*testEdit_.setTextColor(RGB(0,0,0));
    testEdit_.setBKColor(RGB(255,0,0));
    testEdit_.setBorderColor(RGB(255,0,0));*/
    testEdit_.SetWindowTextA("这是一个编辑框");
}

void CCtrlDlg::createCtrl()
{
    createEdit.create(1, {20, 300, 150, 20});
    createStatic.create(2, {20, 340, 150, 20}, "这是一个create出来的");
    createGroupBox.create(3, { 20, 380, 150, 150 }, "手机品牌");
    createCombo.createDropDown(4, {200, 300, 150, 150});
    createCombo.InsertString(0, "oppo");
    createCombo.InsertString(1, "vivo");
    createCombo.InsertString(2, "meizu");
    createCombo.InsertString(2, "欧珀");
    createCombo.InsertString(2, "华为");
    createCombo.SetCurSel(0);
    createCombo.setItemSelectedColor(RGB(255, 0, 0));
    CFont f;
    LOGFONT lf = { 0 };
    lf.lfHeight = 24;
    strcpy_s(lf.lfFaceName, "微软雅黑");
    f.CreateFontIndirectA(&lf);
    createCombo.setFont(f);
    createCombo.setHeight(22);
    createCombo.setItemHeight(30);


}

void CCtrlDlg::initTreeCtrl()
{
    GCtrl::CtrlHelper::initFont(treeFont_);
    //插入根节点  
    auto zhongguo = testTree_.InsertItem("中国");
    auto shanxi = testTree_.InsertItem("山西", zhongguo);
    auto taiyuan = testTree_.InsertItem("太原", shanxi);
    auto yuncheng = testTree_.InsertItem("运城", shanxi);
    auto shandong = testTree_.InsertItem("山东", zhongguo);
    testTree_.Expand(zhongguo, TVE_EXPAND);//根部展开
    testTree_.SetFont(&treeFont_);
}


void CCtrlDlg::OnBnClickedButtonTest()
{
    GCtrl::ProgressDialog dlg(*this, "处理中",
        IDB_BITMAP_TB,
        IDB_BITMAP_MSG_CLOSE);
    std::thread([&]() {
        Sleep(20000);
        dlg.close();
        }).detach();
    dlg.show();
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


LRESULT CCtrlDlg::OnNcHitTest(CPoint point)
{
 
    dragdialog();

    return __super::OnNcHitTest(point);
}


void CCtrlDlg::OnBnClickedButtonTsyx()
{
    

}


void CCtrlDlg::OnNMClickTreeTest(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO: 在此添加控件通知处理程序代码
    *pResult = 0;
}


void CCtrlDlg::OnTvnSingleExpandTreeTest(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
    // TODO: 在此添加控件通知处理程序代码
    *pResult = 0;
}


void CCtrlDlg::OnTvnItemChangedTreeTest(NMHDR *pNMHDR, LRESULT *pResult)
{
    NMTVITEMCHANGE *pNMTVItemChange = reinterpret_cast<NMTVITEMCHANGE*>(pNMHDR);
    // TODO: 在此添加控件通知处理程序代码
    *pResult = 0;
}


void CCtrlDlg::OnTvnItemexpandedTreeTest(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
    // TODO: 在此添加控件通知处理程序代码
    *pResult = 0;
}


void CCtrlDlg::OnTvnSelchangedTreeTest(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
    // TODO: 在此添加控件通知处理程序代码
    *pResult = 0;
}


void CCtrlDlg::OnTvnSelchangingTreeTest(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
    // TODO: 在此添加控件通知处理程序代码
    *pResult = 0;
}
