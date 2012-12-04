// ODRect.cpp: implementation of the CODRect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OD.h"
#include "ODRect.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CODRect::CODRect()
{}

IMPLEMENT_SERIAL(CODRect, CODShape, 0)

void CODRect::Serialize(CArchive& ar)
{
	CODShape::Serialize(ar);
}

CODRect::CODRect(const CRect& bounds):CODShape(bounds)
{}

CODRect::CODRect(const CPoint& point):CODShape(CRect(point, point))
{}

void CODRect::DrawShape(CDC* pDC)
{
	ASSERT_VALID(this);
	Graphics gp(pDC->m_hDC);
	SmoothingMode mode = gp.GetSmoothingMode();
	CRect bounds = m_bounds;
	bounds.NormalizeRect();
	gp.SetSmoothingMode(SmoothingModeAntiAlias);
	GraphicsPath path;
	Rect rect(bounds.left, bounds.top, bounds.Width(), bounds.Height());
	path.AddRectangle(rect);
	Pen pen(m_logPen.lopnColor, m_logPen.lopnWidth.x);
	PointF center(m_rotCenter.x, m_rotCenter.y);
	Matrix matrix;
	matrix.RotateAt(m_rotAngle, center);
	path.Transform(&matrix);
	SolidBrush brush(m_logBrush.lbColor);
	gp.FillPath(&brush, &path);
	gp.DrawPath(&pen, &path);
	gp.SetSmoothingMode(mode);
	gp.ReleaseHDC(pDC->m_hDC);

/*
	CPen pen;
	pen.CreatePenIndirect(&m_logPen);
	CBrush brush;
	brush.CreateBrushIndirect(&m_logBrush);
	CPen* oldPen = pDC->SelectObject(&pen);
	CBrush* oldBrush = (CBrush*)pDC->SelectObject(&brush);
	pDC->Rectangle(m_bounds);
	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
*/
}

int CODRect::HitTest(CPoint point, BOOL bSelected)
{
	if(!bSelected)
	{
		GraphicsPath path;
		Rect rect(m_bounds.left, m_bounds.top, m_bounds.Width(), m_bounds.Height());
		path.AddRectangle(rect);
		Matrix matrix;
		PointF center(m_rotCenter.x, m_rotCenter.y);
		matrix.RotateAt(m_rotAngle, center);
		path.Transform(&matrix);
		Region rgn(&path);
		Rect ptRect(point.x - 1, point.y - 1, 3, 3);
		return rgn.IsVisible(ptRect);
/*
		if (PtInRect(m_bounds, point))
			return 1;
*/
	}
	return CODShape::HitTest(point, bSelected);
}

CODEllipse::CODEllipse()
{}

IMPLEMENT_SERIAL(CODEllipse, CODShape, 0)

void CODEllipse::Serialize(CArchive& ar)
{
	CODShape::Serialize(ar);
}

CODEllipse::CODEllipse(const CRect& bounds):CODShape(bounds)
{}

CODEllipse::CODEllipse(const CPoint& point):CODShape(CRect(point, point))
{}

void CODEllipse::DrawShape(CDC* pDC)
{
	Graphics gp(pDC->m_hDC);
	SmoothingMode mode = gp.GetSmoothingMode();
	CRect bounds = m_bounds;
	bounds.NormalizeRect();
	gp.SetSmoothingMode(SmoothingModeAntiAlias);
	GraphicsPath path;
	Rect rect(bounds.left, bounds.top, bounds.Width(), bounds.Height());
	path.AddEllipse(rect);
	Pen pen(m_logPen.lopnColor, m_logPen.lopnWidth.x);
	PointF center(m_rotCenter.x, m_rotCenter.y);
	Matrix matrix;
	matrix.RotateAt(m_rotAngle, center);
	path.Transform(&matrix);
	SolidBrush brush(m_logBrush.lbColor);
	gp.FillPath(&brush, &path);
	gp.DrawPath(&pen, &path);
	gp.SetSmoothingMode(mode);
	gp.ReleaseHDC(pDC->m_hDC);
	

/*	GDI
	CPen pen;
	pen.CreatePenIndirect(&m_logPen);
	CBrush brush;
	brush.CreateBrushIndirect(&m_logBrush);
	CPen* oldPen = pDC->SelectObject(&pen);
	CBrush* oldBrush = (CBrush*)pDC->SelectObject(&brush);
	pDC->Ellipse(m_bounds);
	pDC->
	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
*/
}

int CODEllipse::HitTest(CPoint point, BOOL bSelected)
{
	if (!bSelected)
	{
		GraphicsPath path;
		Rect rect(m_bounds.left, m_bounds.top, m_bounds.Width(), m_bounds.Height());
		path.AddEllipse(rect);
		Matrix matrix;
		PointF center(m_rotCenter.x, m_rotCenter.y);
		matrix.RotateAt(m_rotAngle, center);
		path.Transform(&matrix);
		Region rgn(&path);
		Rect ptRect(point.x - 1, point.y - 1, 3, 3);
		return rgn.IsVisible(ptRect);
/*
		CRgn rgn;
		rgn.CreateEllipticRgnIndirect(m_bounds);
		if (rgn.PtInRegion(point))
			return 1;
*/
	}
	return CODShape::HitTest(point, bSelected);
}

