#pragma once
#include "GControl/gcontrol.h"

// CCtrlDlg 对话框

class CCtrlDlg 
    : public CDialogEx
    , public GCtrl::CtrlHelper
{
	DECLARE_DYNAMIC(CCtrlDlg)

public:
	CCtrlDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CCtrlDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CTRL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

    virtual BOOL OnInitDialog();
    void initBK();
    void initGroupBox();
    void initBtn();
private:
    CBitmap bkbmp_;
public:
    //CStatic zwflGpbox_;
    GCtrl::GroupBox zwflGpbox_;
    CButton cxyRiobtn_;
    CButton xmjlRiobtn_;
    CButton xsRiobtn_;
    GCtrl::Static tipStc_;
    GCtrl::PushButton testBtn_;
    GCtrl::RadioButton testRiobtn_;
    GCtrl::RadioButton testRiobtn2_;
    GCtrl::RadioButton testRiobtn3_;
    GCtrl::CheckBox testChkbox_;
    afx_msg void OnBnClickedButtonTest();
    afx_msg void OnBnClickedButton1();
};
