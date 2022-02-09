
// IMG_2.0Doc.cpp : implementation of the CIMG20Doc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "IMG_2.0.h"
#endif

#include "IMG_2.0Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define DIB_HEADER_MARKER ((WORD) ('M' << 8) | 'B')
// CIMG20Doc

IMPLEMENT_DYNCREATE(CIMG20Doc, CDocument)

BEGIN_MESSAGE_MAP(CIMG20Doc, CDocument)

END_MESSAGE_MAP()


// CIMG20Doc construction/destruction

CIMG20Doc::CIMG20Doc() noexcept
{
	// TODO: add one-time construction code here

}

CIMG20Doc::~CIMG20Doc()
{
}

BOOL CIMG20Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CIMG20Doc serialization

void CIMG20Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CIMG20Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CIMG20Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CIMG20Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CIMG20Doc diagnostics

#ifdef _DEBUG
void CIMG20Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CIMG20Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CIMG20Doc commands
/*
// 축소판 그림을 지원합니다.
void CIMG20Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

*/
BOOL CIMG20Doc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	CString strFilter;

	//A GUID is a 128 - bit value consisting of one group of 8 hexadecimal digits, followed by three groups of 4 hexadecimal digits each, followed by one group of 12 hexadecimal digits.
	CSimpleArray<GUID> aguidFileTypes;
	HRESULT hResult;


	hResult = m_Image_0.GetExporterFilterString(strFilter, aguidFileTypes, _T("All Image Files"));

	m_Image_0.Destroy();
	m_Image_1.Destroy();
	m_Image_2.Destroy();
	hResult = m_Image_0.Load(lpszPathName);

	m_ptrImage_0 = &m_Image_0;
	m_ptrImage_1 = m_ptrImage_0;
	m_ptrImage_2 = m_ptrImage_0;
	m_Image_1 = *m_ptrImage_0;
	m_Image_2 = *m_ptrImage_0;


	//HWND hWnd = AfxGetApp()->m_pMainWnd->m_hWnd;
	//int tab_num = TabCtrl_GetCurSel(hWnd);
	//CString str;
	//str.LoadString(AFX_IDS_APP_TITLE);
	//AfxGetMainWnd()->SetWindowText(str + " - " + dig.GetFileName());



	return TRUE;
}


BOOL CIMG20Doc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: Add your specialized code here and/or call the base class
	

	return CDocument::OnSaveDocument(lpszPathName);
}


void CIMG20Doc::OnBright()
{
	if (m_Image_2.IsNull()) {
		AfxMessageBox(_T("No Image to Edit"));
		return;
	}
	CInputDlgSlider dlgsldr;
	if (dlgsldr.DoModal() != IDOK)
		return;


	int factor = dlgsldr.m_sldr_int;

	//HWND hWnd = AfxGetApp()->m_pMainWnd->m_hWnd;
	//int tab_num = TabCtrl_GetCurSel(hWnd);

	//at this point, ptr1 is pointing to ptr2, which is output from last operation img1 is destroyed from onDraw

	int x;
	int y;
	int nRows = m_Image_1.GetHeight();
	int nCols = m_Image_1.GetWidth();
	int nBPP = m_Image_1.GetBPP();

	BYTE RR, GG, BB;

	//	if (!imageArr[tab_num - 1].Create(nCols, nRows, nBPP)) {
	//		return;
	//	}
	BYTE* ImageData_in = (BYTE*)m_Image_1.GetBits();
	BYTE* ImageData_out = (BYTE*)m_Image_2.GetBits();
	int nRowBytes = m_Image_1.GetPitch();



	for (y = 0; y < nRows; y++) {
		for (x = 0; x < nCols; x++) {

			BB = (ImageData_in[y * nRowBytes + x * 3 + 0]);
			GG = (ImageData_in[y * nRowBytes + x * 3 + 1]);
			RR = (ImageData_in[y * nRowBytes + x * 3 + 2]);
			
			if ((BB + factor) > 255)
				BB = 255;

			if ((GG + factor) > 255)
				GG = 255;

			if ((RR + factor) > 255)
				RR = 255;

			if ((BB + factor) < 0)
				BB = 0;

			if ((GG + factor) < 0)
				GG = 0;
				
			if ((RR + factor) < 0)
				RR = 0;


			ImageData_out[y * nRowBytes + x * 3 + 0] = BB;
			ImageData_out[y * nRowBytes + x * 3 + 1] = GG;
			ImageData_out[y * nRowBytes + x * 3 + 2] = RR;

		}
	}


	UpdateAllViews(NULL);

}



void CIMG20Doc::OnColourtoGray()
{
	if (m_Image_2.IsNull()) {
		AfxMessageBox(_T("No Image to Edit"));
		return;
	}
	//HWND hWnd = AfxGetApp()->m_pMainWnd->m_hWnd;
	//int tab_num = TabCtrl_GetCurSel(hWnd);


	//at this point, ptr1 is pointing to ptr2, which is output from last operation img1 is destroyed from onDraw


	int x;
	int y;
	int nRows = m_Image_1.GetHeight();
	int nCols = m_Image_1.GetWidth();
	int nBPP = m_Image_1.GetBPP();

	BYTE nRed, nGreen, nBlue, nGrey;


	//	if (!imageArr[tab_num - 1].Create(nCols, nRows, nBPP)) {
	//		return;

	BYTE* ImageData_in = (BYTE*)m_Image_1.GetBits();
	BYTE* ImageData_out = (BYTE*)m_Image_1.GetBits();
	int nRowBytes = m_Image_1.GetPitch();


	for (y = 0; y < nRows; y++)
		for (x = 0; x < nCols; x++) {
			nBlue = ImageData_in[y * nRowBytes + x * 3 + 0];
			nGreen = ImageData_in[y * nRowBytes + x * 3 + 1];
			nRed = ImageData_in[y * nRowBytes + x * 3 + 2];
			nGrey = (BYTE)(0.299 * nRed + 0.587 * nGreen + 0.114 * nBlue);  // (R+G+B)/3
			ImageData_out[y * nRowBytes + x * 3] = nGrey;
			ImageData_out[y * nRowBytes + x * 3 + 1] = nGrey;
			ImageData_out[y * nRowBytes + x * 3 + 2] = nGrey;
		}
	UpdateAllViews(NULL);
}

void CIMG20Doc::OnBW()
{

	if (m_Image_2.IsNull()) {
		AfxMessageBox(_T("No Image to Edit"));
		return;
	}

	CInputDlg dlg;

	if (dlg.DoModal() != IDOK)
		return;

	int factor = (int)dlg.m_input1;

	//at this point, ptr1 is pointing to ptr2, which is output from last operation img1 is destroyed from onDraw

	int x;
	int y;
	int nRows = m_Image_1.GetHeight();
	int nCols = m_Image_1.GetWidth();
	int nBPP = m_Image_1.GetBPP();

	BYTE RR, GG, BB, SUM;
	BYTE* ImageData_in = (BYTE*)m_Image_1.GetBits();
	BYTE* ImageData_out = (BYTE*)m_Image_2.GetBits();
	int nRowBytes = m_Image_1.GetPitch();

	for (y = 0; y < nRows; y++) {
		for (x = 0; x < nCols; x++) {

			BB = (ImageData_in[y * nRowBytes + x * 3 + 0]);
			GG = (ImageData_in[y * nRowBytes + x * 3 + 1]);
			RR = (ImageData_in[y * nRowBytes + x * 3 + 2]);

			if ((BB) > factor)
				BB = 255;
			if ((BB) <= factor)
				BB = 0;

			if ((GG) > factor)
				GG = 255;
			if ((GG) <= factor)
				GG = 0;

			if ((RR) > factor)
				RR = 255;
			if ((RR) <= factor)
				RR = 0;

			SUM = (RR + GG + BB) / 3;
			ImageData_out[y * nRowBytes + x * 3 + 0] = SUM;
			ImageData_out[y * nRowBytes + x * 3 + 1] = SUM;
			ImageData_out[y * nRowBytes + x * 3 + 2] = SUM;

		}
	}


	UpdateAllViews(NULL);
}


void CIMG20Doc::OnInvert()
{
	if (m_Image_2.IsNull()) {
		AfxMessageBox(_T("No Image to Edit"));
		return;
	}

	//at this point, ptr1 is pointing to ptr2, which is output from last operation img1 is destroyed from onDraw

	int x;
	int y;
	int nRows = m_Image_1.GetHeight();
	int nCols = m_Image_1.GetWidth();
	int nBPP = m_Image_1.GetBPP();

	BYTE RR, GG, BB, SUM;
	BYTE* ImageData_in = (BYTE*)m_Image_1.GetBits();
	BYTE* ImageData_out = (BYTE*)m_Image_2.GetBits();
	int nRowBytes = m_Image_1.GetPitch();

	for (y = 0; y < nRows; y++) {
		for (x = 0; x < nCols; x++) {

			BB = 255 - (ImageData_in[y * nRowBytes + x * 3 + 0]);
			GG = 255 - (ImageData_in[y * nRowBytes + x * 3 + 1]);
			RR = 255 - (ImageData_in[y * nRowBytes + x * 3 + 2]);

			ImageData_out[y * nRowBytes + x * 3 + 0] = BB;
			ImageData_out[y * nRowBytes + x * 3 + 1] = GG;
			ImageData_out[y * nRowBytes + x * 3 + 2] = RR;

		}
	}


	UpdateAllViews(NULL);
}


void CIMG20Doc::OnLevel()
{
	if (m_Image_2.IsNull()) {
		AfxMessageBox(_T("No Image to Edit"));
		return;
	}

	//at this point, ptr1 is pointing to ptr2, which is output from last operation img1 is destroyed from onDraw

	int x;
	int y;
	int nRows = m_Image_1.GetHeight();
	int nCols = m_Image_1.GetWidth();
	int nBPP = m_Image_1.GetBPP();

	BYTE RR, GG, BB, SUM;
	BYTE* ImageData_in = (BYTE*)m_Image_1.GetBits();
	BYTE* ImageData_out = (BYTE*)m_Image_2.GetBits();
	int nRowBytes = m_Image_1.GetPitch();

	for (y = 0; y < nRows; y++) {
		for (x = 0; x < nCols; x++) {

			BB = ImageData_in[y * nRowBytes + x * 3 + 0];
			GG = ImageData_in[y * nRowBytes + x * 3 + 1];
			RR = ImageData_in[y * nRowBytes + x * 3 + 2];

			if (BB > 0 && BB <= 100)
				BB = 0;
			if (GG > 100 && GG <= 200)
				GG = 0;
			if (RR > 200 && RR <= 255)
				RR = 0;

			ImageData_out[y * nRowBytes + x * 3 + 0] = BB;
			ImageData_out[y * nRowBytes + x * 3 + 1] = GG;
			ImageData_out[y * nRowBytes + x * 3 + 2] = RR;

		}
	}

	UpdateAllViews(NULL);
}


void CIMG20Doc::OnRotate()
{

}
//original width = 720
//original height = 960

void CIMG20Doc::OnRotate90()
{

	if (m_Image_2.IsNull()) {
		AfxMessageBox(_T("No Image to Edit"));
		return;
	}


	int x;
	int y;
	int nRows = m_Image_1.GetHeight();
	int nCols = m_Image_1.GetWidth();
	int nBPP = m_Image_1.GetBPP();

	BYTE RR, GG, BB, SUM;
	BYTE* ImageData_in = (BYTE*)m_Image_1.GetBits();
	BYTE* ImageData_out = (BYTE*)m_Image_2.GetBits();
	int nRowBytes = m_Image_1.GetPitch();


	//m_Image_2.Destroy();
	//m_Image_2.Create(nRows, nCols, nBPP);


	for (y = 0; y < nRows; y++) {
		for (x = 0; x < nCols; x++) {

			//BB = ImageData_in[abs(nCols-1 - x) * nRowBytes + y * 3 + 0];
			//GG = ImageData_in[abs(nCols-1 - x) * nRowBytes + y * 3 + 1];
			//RR = ImageData_in[abs(nCols-1 - x) * nRowBytes + y * 3 + 2];

			//BB = ImageData_in[abs(nCols - 1 - x) * nRowBytes + y * 3 + 0];
			//GG = ImageData_in[abs(nCols - 1 - x) * nRowBytes + y * 3 + 1];
			//RR = ImageData_in[abs(nCols - 1 - x) * nRowBytes + y * 3 + 2];


			//ImageData_out[y * nRowBytes + x * 3 + 0] = BB;
			//ImageData_out[y * nRowBytes + x * 3 + 1] = GG;
			//ImageData_out[y * nRowBytes + x * 3 + 2] = RR;

		}
	}

 
	UpdateAllViews(NULL);

}

wqss

void CIMG20Doc::OnFlipH()
{
	// TODO: Add your implementation code here.
}


void CIMG20Doc::OnFlipV()
{
	// TODO: Add your implementation code here.
}


int CIMG20Doc::OnZoom()
{
	// TODO: Add your implementation code here.
	return 0;
}
