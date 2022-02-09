// CInputDlgSlider.cpp : implementation file
//

#include "pch.h"
#include "IMG_2.0.h"
#include "afxdialogex.h"
#include "CInputDlgSlider.h"


// CInputDlgSlider dialog

IMPLEMENT_DYNAMIC(CInputDlgSlider, CDialog)

CInputDlgSlider::CInputDlgSlider(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_INPUT_SLIDER, pParent)
{

}

CInputDlgSlider::~CInputDlgSlider()
{
}

void CInputDlgSlider::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_SLIDER1, m_sldr);
    DDX_Control(pDX, IDC_SLDR_VAL, m_sldr_val);
}

void CInputDlgSlider::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    int val;
    CString temp_str;
    int nSPos = 0;
    if (pScrollBar)
    {
        if (pScrollBar == (CScrollBar*)&m_sldr)
        {
            nSPos = m_sldr.GetPos();
            temp_str.Format(_T("%d"), nSPos);
            m_sldr_val.SetWindowTextW(temp_str);
        }

        CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
    }

}

void CInputDlgSlider::OnEnChangeSldrVal()
{
    CString temp_str;

    //read edit box value
    m_sldr_val.GetWindowTextW(temp_str);
    int nSPos = _ttoi(temp_str);

    //pass to slider

    m_sldr.SetPos(nSPos);

    UpdateData(TRUE);
    m_sldr_int = nSPos;
}

BEGIN_MESSAGE_MAP(CInputDlgSlider, CDialog)
    ON_WM_HSCROLL()
    ON_EN_CHANGE(IDC_SLDR_VAL, &CInputDlgSlider::OnEnChangeSldrVal)
END_MESSAGE_MAP()


// CInputDlgSlider message handlers


BOOL CInputDlgSlider::OnInitDialog()
{
    CDialog::OnInitDialog();
    // TODO: Add your specialized code here and/or call the base class
    m_sldr.SetRange(-255.0, 255.0); //최소, 최대 값
   // m_sldr.SetPos(1.0); // 현재 위치
    m_sldr.SetLineSize(0.1); // 방향키고 움직일 때 사이즈
    m_sldr.SetPageSize(0.1); //PgUp, PgDn 으로 움직일 때 사이즈
    return TRUE;
}
