
// IMG_2.0View.h : interface of the CIMG20View class
//

#pragma once
#include "CInputDlgSlider.h"
#include "CInputDlg.h"
class CIMG20View : public CView
{
protected: // create from serialization only
	CIMG20View() noexcept;
	DECLARE_DYNCREATE(CIMG20View)

// Attributes
public:
	CIMG20Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CIMG20View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBrightness();
	afx_msg void OnClrtogray();
	afx_msg void OnBW();
	afx_msg void OnInvert();
	afx_msg void OnLevel();
	afx_msg void OnRotate();
	afx_msg void OnRotate90();
	afx_msg void OnFlipH();
	afx_msg void OnFlipV();
	afx_msg void OnZoom();
};

#ifndef _DEBUG  // debug version in IMG_2.0View.cpp
inline CIMG20Doc* CIMG20View::GetDocument() const
   { return reinterpret_cast<CIMG20Doc*>(m_pDocument); }
#endif

