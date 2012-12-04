// ODView.cpp : implementation of the CODView class
//

#include "stdafx.h"
#include "OD.h"

#include "ODDoc.h"
#include "ODView.h"
#include "ODToolKit.h"
#include "ODLine.h"
#include "ODPolygon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CODView

IMPLEMENT_DYNCREATE(CODView, CScrollView)

BEGIN_MESSAGE_MAP(CODView, CScrollView)
//{{AFX_MSG_MAP(CODView)
ON_COMMAND(ID_DRAW_RECT, OnDrawRect)
ON_UPDATE_COMMAND_UI(ID_DRAW_RECT, OnUpdateDrawRect)
ON_COMMAND(ID_DRAW_ELLIPSE, OnDrawEllipse)
ON_UPDATE_COMMAND_UI(ID_DRAW_ELLIPSE, OnUpdateDrawEllipse)
ON_COMMAND(ID_DRAW_LINE, OnDrawLine)
ON_UPDATE_COMMAND_UI(ID_DRAW_LINE, OnUpdateDrawLine)
ON_COMMAND(ID_DRAW_POLYGON, OnDrawPolygon)
ON_UPDATE_COMMAND_UI(ID_DRAW_POLYGON, OnUpdateDrawPolygon)
ON_COMMAND(ID_DRAW_SELECT, OnDrawSelect)
ON_UPDATE_COMMAND_UI(ID_DRAW_SELECT, OnUpdateDrawSelect)
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_MOUSEMOVE()
ON_WM_LBUTTONDBLCLK()
//}}AFX_MSG_MAP
// Standard printing commands
ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CODView construction/destruction

CODView::CODView()
{
	m_bGrid = TRUE;
	m_gridColor = RGB(128, 128, 128);
}

CODView::~CODView()
{
	
}

void CODView::DrawGrid(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);
	COLORREF backColor = RGB(255, 255, 255);
	CBrush brush(backColor);
	pDC->FillRect(rect, &brush);
	
	CPen* pOldPen;
	CPen penDot;
	penDot.CreatePen(PS_DOT, 1, m_gridColor);
	pOldPen = pDC->SelectObject(&penDot);
	
	for (int x = 50; x < rect.right; x += 50)
	{
		pDC->MoveTo(x, rect.top);
		pDC->LineTo(x, rect.bottom);
	}
	
	for (int y = 50; y < rect.bottom; y += 50)
	{
		pDC->MoveTo(rect.left, y);
		pDC->LineTo(rect.right, y);
	}
	
	pDC->SelectObject(pOldPen);
}

BOOL CODView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	
	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CODView drawing

void CODView::OnDraw(CDC* pDC)
{
	CODDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap memBmp;
	CRect clipRect;
	GetClientRect(clipRect);
	memBmp.CreateCompatibleBitmap(pDC, clipRect.Width(), clipRect.Height());
	CBitmap* oldBmp;
	oldBmp = memDC.SelectObject(&memBmp);
	memDC.IntersectClipRect(clipRect);		
	
	DrawGrid(&memDC);
	pDoc->DrawShape(&memDC);
	
	pDC->BitBlt(0, 0, clipRect.Width(), clipRect.Height(), &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(oldBmp);
	
	// TODO: add draw code for native data here
}

void CODView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	
//	CODRect* shpRect = new CODRect(CRect(100, 100, 200, 200));
//	shpRect->SetRotaion(0);
//	GetDocument()->AddShape(shpRect);
//	GetDocument()->AddSelection(shpRect);
//
//	CODEllipse* shpEllipse = new CODEllipse(CRect(170, 170, 330, 230));
//	GetDocument()->AddShape(shpEllipse);
//	GetDocument()->AddSelection(shpEllipse);

//	CODLine* shpLine = new CODLine(CPoint(330, 130), CPoint(400, 200));
//	GetDocument()->AddShape(shpLine);

//	CODPolygon* shpPolygon = new CODPolygon();
//	shpPolygon->AddVertex(CPoint(330, 60));
//	shpPolygon->AddVertex(CPoint(400, 100));
//	shpPolygon->AddVertex(CPoint(430, 80));
//	shpPolygon->AddVertex(CPoint(420, 30));
//	shpPolygon->EndAddVertex();
//	GetDocument()->AddShape(shpPolygon);
//	GetDocument()->AddSelection(shpPolygon);
//	shpPolygon->SetRotaion(45);
	
	
	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CODView printing

BOOL CODView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CODView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CODView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CODView diagnostics

#ifdef _DEBUG
void CODView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CODView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CODDoc* CODView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CODDoc)));
	return (CODDoc*)m_pDocument;
}
#endif //_DEBUG

CODToolKit* CODView::GetToolKit()
{
	return CODToolKit::GetToolKit();
}

/////////////////////////////////////////////////////////////////////////////
// CODView message handlers
void CODView::OnDrawRect() 
{
	GetToolKit()->SetDrawMode(DM_RECT);
}

void CODView::OnUpdateDrawRect(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(GetToolKit()->GetDrawMode() == DM_RECT);		
}

void CODView::OnDrawEllipse() 
{
	GetToolKit()->SetDrawMode(DM_ELLIPSE);	
}

void CODView::OnUpdateDrawEllipse(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(GetToolKit()->GetDrawMode() == DM_ELLIPSE);		
}

void CODView::OnDrawLine() 
{
	GetToolKit()->SetDrawMode(DM_LINE);	
}

void CODView::OnUpdateDrawLine(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(GetToolKit()->GetDrawMode() == DM_LINE);			
}

void CODView::OnDrawPolygon() 
{
	GetToolKit()->SetDrawMode(DM_POLYGON);	
}

void CODView::OnUpdateDrawPolygon(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(GetToolKit()->GetDrawMode() == DM_POLYGON);	
}

void CODView::OnDrawSelect() 
{
	GetToolKit()->SetDrawMode(DM_SELECT);
}

void CODView::OnUpdateDrawSelect(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(GetToolKit()->GetDrawMode() == DM_SELECT);		
}

void CODView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	GetToolKit()->OnLButtonDown(this, nFlags, point);
}

void CODView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	GetToolKit()->OnLButtonUp(this, nFlags, point);
}

void CODView::OnMouseMove(UINT nFlags, CPoint point) 
{
	GetToolKit()->OnMouseMove(this, nFlags, point);
}

void CODView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	GetToolKit()->OnLButtonDblClk(this, nFlags, point);
}

