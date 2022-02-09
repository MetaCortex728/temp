
// IMG_2.0Doc.h : interface of the CIMG20Doc class
//


#pragma once
#include "CInputDlgSlider.h"
#include "CInputDlg.h"
class CIMG20Doc : public CDocument
{
protected: // create from serialization only
	CIMG20Doc() noexcept;
	DECLARE_DYNCREATE(CIMG20Doc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CIMG20Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);

	CImage* m_ptrImage_0;
	CImage* m_ptrImage_1;
	CImage* m_ptrImage_2;

	CImage m_Image_0;	//ORIGINAL
	CImage m_Image_1;	//CURRENT (WITHIN FUNCTION)
	CImage m_Image_2;	//OUTPUT (TO BE DISPLAYED)
	void OnBright();
	void OnColourtoGray();
	void OnBW();
	void OnInvert();
	void OnLevel();


	void OnRotate();
	void OnRotate90();
	void OnFlipH();
	void OnFlipV();
	int OnZoom();
};
