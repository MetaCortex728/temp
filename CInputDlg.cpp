// CInputDlg.cpp : implementation file
//

#include "pch.h"
#include "IMG_2.0.h"
#include "afxdialogex.h"
#include "CInputDlg.h"


// CInputDlg dialog

IMPLEMENT_DYNAMIC(CInputDlg, CDialogEx)

CInputDlg::CInputDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INPUT_1VAL, pParent)
	, m_input1(0)
{

}

CInputDlg::~CInputDlg()
{
}

void CInputDlg::DoDataExchange(CDataExchange* pDX)
{
	DDX_Text(pDX, IDC_EDIT1, m_input1);
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CInputDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &CInputDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CInputDlg message handlers


void CInputDlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
