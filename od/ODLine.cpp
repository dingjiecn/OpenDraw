// ODLine.cpp: implementation of the CODLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OD.h"
#include "ODLine.h"
#include "compgeo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

inline CRect GetPtRect(const CPoint& pt)
{
	return CRect(pt.x-3, pt.y-3, pt.x+3, pt.y+3);
}

CODLine::CODLine()
{

}

IMPLEMENT_SERIAL(CODLine, CODShape, 0)

void CODLine::Serialize(CArchive& ar)
{
	CODShape::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << m_ptStart;
		ar << m_ptEnd;
		ar << m_rcStart;
		ar << m_rcEnd;
	}
	else
	{
		ar >> m_ptStart;
		ar >> m_ptEnd;
		ar >> m_rcStart;
		ar >> m_rcEnd;
	}
}

CODLine::CODLine(const CPoint& ptStart, const CPoint& ptEnd):
CODShape(CRect(ptStart, ptEnd)),m_ptStart(ptStart), m_ptEnd(ptEnd)
{
	m_rcStart = GetPtRect(m_ptStart);
	m_rcEnd = GetPtRect(m_ptEnd);
}

CODLine::CODLine(const CPoint& point):CODShape(CRect(point, point)),
m_ptStart(point), m_ptEnd(point)
{
	m_rcStart = GetPtRect(m_ptStart);
	m_rcEnd = GetPtRect(m_ptEnd);
}

void CODLine::DrawShape(CDC* pDC)
{
	Graphics gp(pDC->m_hDC);
	SmoothingMode mode = gp.GetSmoothingMode();
	gp.SetSmoothingMode(SmoothingModeAntiAlias);
	Pen pen(m_logPen.lopnColor, m_logPen.lopnWidth.x);
	Point ptStart(m_ptStart.x, m_ptStart.y);
	Point ptEnd(m_ptEnd.x, m_ptEnd.y);
	gp.DrawLine(&pen, ptStart, ptEnd);
	gp.SetSmoothingMode(mode);
	gp.ReleaseHDC(pDC->m_hDC);

/*
	CPen pen;
	pen.CreatePenIndirect(&m_logPen);
	CPen* oldPen = pDC->SelectObject(&pen);
	pDC->MoveTo(m_ptStart);
	pDC->LineTo(m_ptEnd);
	pDC->SelectObject(oldPen);
*/
}
int CODLine::HitTest(CPoint point, BOOL bSelected)
{
	if (!bSelected)
	{
		POINT points[4];
		GetLineRect(points, m_ptStart, m_ptEnd, m_logPen.lopnWidth, 5);
		CRgn rgn;
		rgn.CreatePolygonRgn(points, 4, ALTERNATE);
		if (rgn.PtInRegion(point))		
			return 1;
	}
	else
	{
		if (PtInRect(m_rcStart, point))			
		{
			return 1;
		}
		else if (PtInRect(m_rcEnd, point))
		{
			return 2;
		}
	}
	return 0;
}

void CODLine::DrawHandle(CDC* pDC)
{
	CBrush* oldBrush = (CBrush*)pDC->SelectStockObject(WHITE_BRUSH);
	CPen* oldPen = (CPen*)pDC->SelectStockObject(BLACK_PEN);
	pDC->Ellipse(&m_rcStart);
	pDC->Ellipse(&m_rcEnd);
	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
}

HCURSOR CODLine::GetHandleCursor(int nHandle)
{
	ASSERT(nHandle==1||nHandle==2);
	return AfxGetApp()->LoadStandardCursor(IDC_CROSS);
}

void CODLine::MoveHandleTo(int nHandle, const CPoint& point)
{
	ASSERT(nHandle==1||nHandle==2);
	if (nHandle == 1)
	{
		m_ptStart = point;
		m_rcStart = GetPtRect(m_ptStart);
	}
	else //if (nHandle ==2)
	{
		m_ptEnd = point;
		m_rcEnd= GetPtRect(m_ptEnd);
	}
	m_bounds.SetRect(m_ptStart, m_ptEnd);
}

void CODLine::MoveShape(const CPoint& delta)
{
	m_ptStart += delta;
	m_ptEnd += delta;
	m_rcStart = GetPtRect(m_ptStart);
	m_rcEnd = GetPtRect(m_ptEnd);
	m_bounds += delta;
}