#pragma once
#include "afxdialogex.h"


// CInputDlgSlider dialog

class CInputDlgSlider : public CDialog
{
	DECLARE_DYNAMIC(CInputDlgSlider)

public:
	CInputDlgSlider(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CInputDlgSlider();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INPUT_SLIDER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_sldr;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CEdit m_sldr_val;
	afx_msg void OnEnChangeSldrVal();
	virtual BOOL OnInitDialog();
	int m_sldr_int = 0;
	afx_msg void OnBrightness();
};
