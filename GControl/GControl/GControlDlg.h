
// GControlDlg.h: 头文件
//

#pragma once
#include "GControl/gcombobox.h"
#include "GControl/gedit.h"

// CGControlDlg 对话框
class CGControlDlg : public CDialogEx
{
// 构造
public:
	CGControlDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GCONTROL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();

    void initBK();
    void initComboBox();
    void initEdit();
    void initListBox();
    void initMessage();
    void initDXAN();

	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
    CBitmap bk_;
    GCtrl::ComboBox aCobo_;
    GCtrl::Edit aEdit_;
    CFont f;
    GCtrl::ListBox aListbox_;
public:
    CStatic dcanStc;
    CStatic xbStc_;
    CButton dxanAStc_;
    CButton dxanBStc_;
    CButton nanStc_;
    CButton nvStc_;
    afx_msg void OnBnClickedRadioNan();
};
