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
    afx_msg void OnBnClickedButtonTest();
    afx_msg void OnBnClickedButton1();

    virtual BOOL OnInitDialog();
    void initBK();
    void initGroupBox();
    void initBtn();
    void createCtrl();
private:
    CBitmap bkbmp_;
public:
    //CStatic zwflGpbox_;
    GCtrl::GroupBox zwflGpbox_{ *this };
    GCtrl::ButtonEx cxyRiobtn_{*this};
    GCtrl::ButtonEx xmjlRiobtn_{*this};
    GCtrl::ButtonEx xsRiobtn_{*this};
    GCtrl::Static tipStc_{ *this };
    GCtrl::PushButton testBtn_{*this};
    GCtrl::RadioButton testRiobtn_{ *this };
    GCtrl::RadioButton testRiobtn2_{ *this };
    GCtrl::RadioButton testRiobtn3_{ *this };
    GCtrl::CheckBox testChkbox_{ *this };
    CDateTimeCtrl dtc_;
    GCtrl::ButtonEx testCheckBox_{ *this };
    GCtrl::Edit testEdit_{ *this };
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

    GCtrl::Edit createEdit{ *this };
    GCtrl::GroupBox createGroupBox{ *this };
    GCtrl::ListBox create{ *this };
    GCtrl::Static createStatic{ *this };
    GCtrl::ComboBox createCombo{ *this };
};
