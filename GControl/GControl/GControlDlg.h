
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

    void initComboBox();
    void initEdit();

	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
    GCtrl::ComboBox aCobo_;
public:
    GCtrl::GEdit aEdit_;
    CFont f;
};
