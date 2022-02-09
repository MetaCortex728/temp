
// IMG_2.0View.cpp : implementation of the CIMG20View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "IMG_2.0.h"
#endif

#include "IMG_2.0Doc.h"
#include "IMG_2.0View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIMG20View

IMPLEMENT_DYNCREATE(CIMG20View, CView)

BEGIN_MESSAGE_MAP(CIMG20View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CIMG20View::OnFilePrintPreview)

	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(IDM_BRIGHTNESS, &CIMG20View::OnBrightness)
	ON_COMMAND(IDM_CLRTOGRAY, &CIMG20View::OnClrtogray)
	ON_COMMAND(IDM_BW, &CIMG20View::OnBW)
	ON_COMMAND(IDM_INVERT, &CIMG20View::OnInvert)
	ON_COMMAND(IDM_LEVEL, &CIMG20View::OnLevel)
	ON_COMMAND(IDM_ROTATE, &CIMG20View::OnRotate)
	ON_COMMAND(IDM_ROTATE90, &CIMG20View::OnRotate90)
	ON_COMMAND(IDM_FLIPH, &CIMG20View::OnFlipH)
	ON_COMMAND(IDM_FLIPV, &CIMG20View::OnFlipV)
	ON_COMMAND(IDM_ZOOM, &CIMG20View::OnZoom)
END_MESSAGE_MAP()

// CIMG20View construction/destruction

CIMG20View::CIMG20View() noexcept
{
	// TODO: add construction code here

}

CIMG20View::~CIMG20View()
{
}

BOOL CIMG20View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// cimg20view drawing
//bool makecellframeimage(lpctstr insourceimagefilename, lpctstr indestimagefilename,
//	const crect& intagetrect, refguid inimageformattomake)
//{
//	cimage    tempsourceimage;
//	cimage    tempdestimage;
//
//	crect    temptargetrect = intagetrect;
//	//-------------------------------------------------
//	// 1. 원본 이미지를 tempsourceimage에 로딩
//	//-------------------------------------------------
//	tempsourceimage.load(insourceimagefilename);
//	cdc* psourcedc = cdc::fromhandle(tempsourceimage.getdc());    // 원본 이미지의 dc를 얻는다
//
//	//-------------------------------------------------
//	// 2. 파일로 만들 이미지 객체 tempdestimage 생성
//	//-------------------------------------------------
//	int bitperpixel = psourcedc->getdevicecaps(bitspixel);
//	tempdestimage.create(temptargetrect.width(), temptargetrect.height(), bitperpixel);
//	cdc* pdestdc = cdc::fromhandle(tempdestimage.getdc());
//
//	if (!psourcedc || !pdestdc)
//	{
//		return false;
//	}
//	//---------------------------------------------------------------------
//	 // 3. 타겟 dc( 만들 이미지의 dc )에 원본 이미지 dc 의 내용을 를 쓴다
//	 //--------------------------------------------------------------------
//	pdestdc->bitblt(0, 0, temptargetrect.width(), temptargetrect.height(),
//		psourcedc, temptargetrect.left, temptargetrect.top, srccopy);
//
//	tempdestimage.releasedc();
//	tempsourceimage.releasedc();
//	//--------------------------------------------------------
//	// 4. 이미지 파일로 저장
//	//-------------------------------------------------------
//	tempdestimage.save(indestimagefilename, inimageformattomake);
//
//	return true;
//}


void CIMG20View::OnDraw(CDC* pDC)
{

	CIMG20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//HWND hWnd = AfxGetApp()->m_pMainWnd->m_hWnd;
	//int tab_num = TabCtrl_GetCurSel(hWnd);
	CRect Rect;
	GetClientRect(&Rect);


	if ((pDoc->m_Image_0).IsNull())						//if first init, do nothing and return
		return;

	//if ((pDoc->m_Image_1).IsNull()) {
	//	ReleaseDC(pDC);
	//	(pDoc->m_Image_1).Destroy();
	//	return;
	//}

	float width = Rect.right - Rect.left;
	float height = Rect.bottom - Rect.top;
	float rect_rate = width / height;
	float img_rate = (float)((pDoc->m_Image_1).GetWidth()) / (float)((pDoc->m_Image_1).GetHeight());
	float wndsize = Rect.Size().cx * Rect.Size().cy;
	float imgsize = (float)((pDoc->m_Image_1).GetWidth()) * (float)((pDoc->m_Image_1).GetHeight());
	bool isImgBigger = 0;
	if (imgsize > wndsize)
		bool isImgBigger = true;

	/*
	//if img is bigger than rect and height is greater than width OR img is smaller than rect and width is greater than height, priority_range is 1
	//int priority_range = ((img_rate > rect_rate && img_rate < 1) || (img_rate < rect_rate&& img_rate >= 1)) ? 1 : 0;

	//if (img_rate < 1) priority_range = 1 - priority_range;
	//if (priority_range) width = height * img_rate;
	//else height = width / img_rate;

	//Rect.left = 0; 
	//Rect.right = (int)width;
	//Rect.top = 0; 
	//Rect.bottom = (int)height;
	//int interval_x = (Rect.right - (int)width) / 2;
	//int interval_y = (Rect.bottom - (int)height) / 2;
	//Rect.left = interval_x; 
	//Rect.right = (int)width + interval_x; 
	//Rect.top = interval_y; 
	//Rect.bottom = (int)height + interval_y;
	*/

	if (isImgBigger)		//if img is bigger than rect(window)
		(pDoc->m_Image_1).Draw(pDC->m_hDC, Rect);

	if (!isImgBigger)		//if not
		(pDoc->m_Image_1).Draw(pDC->m_hDC, 0, 0);


	//pDoc->m_Image_2.Destroy();			//		hBitmap = Detach(); ::DeleteObject(hBitmap);
	pDoc->m_ptrImage_2 = pDoc->m_ptrImage_1;
	pDoc->m_Image_2 = *(pDoc->m_ptrImage_1);	//just overwrite it

	ReleaseDC(pDC);

}


// CIMG20View printing


void CIMG20View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CIMG20View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CIMG20View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CIMG20View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CIMG20View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CIMG20View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CIMG20View diagnostics

#ifdef _DEBUG
void CIMG20View::AssertValid() const
{
	CView::AssertValid();
}

void CIMG20View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CIMG20Doc* CIMG20View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIMG20Doc)));
	return (CIMG20Doc*)m_pDocument;
}
#endif //_DEBUG


// CIMG20View message handlers


void CIMG20View::OnBrightness()
{
	CIMG20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnBright();
	Invalidate(TRUE);
}


void CIMG20View::OnClrtogray()
{
	CIMG20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnColourtoGray();
	Invalidate(TRUE);
}


void CIMG20View::OnBW()
{
	CIMG20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnBW();
	Invalidate(TRUE);
}


void CIMG20View::OnInvert()
{
	CIMG20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnInvert();
	Invalidate(TRUE);
}


void CIMG20View::OnLevel()
{
	CIMG20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnLevel();
	Invalidate(TRUE);
}


void CIMG20View::OnRotate()
{
	CIMG20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnRotate();
	Invalidate(TRUE);
}


void CIMG20View::OnRotate90()
{
	CIMG20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnRotate90();
	Invalidate(TRUE);
}


void CIMG20View::OnFlipH()
{
	CIMG20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnFlipH();
	Invalidate(TRUE);
}


void CIMG20View::OnFlipV()
{
	CIMG20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnFlipV();
	Invalidate(TRUE);
}


void CIMG20View::OnZoom()
{
	CIMG20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnZoom();
	Invalidate(TRUE);
}
