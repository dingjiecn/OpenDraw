// ODPolygon.cpp: implementation of the CODPolygon class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OD.h"
#include "ODPolygon.h"
#include <algorithm>
#include <math.h>
#include "compgeo.h"
using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CODPolygon::CODPolygon():CODShape(CRect(1E5, 1E5,-1E5,-1E5))
{
	
}

IMPLEMENT_SERIAL(CODPolygon, CODShape, 0)

void CODPolygon::Serialize(CArchive& ar)
{
	CODShape::Serialize(ar);
	if (ar.IsStoring())
	{
		WORD n = m_vertices.size();
		ar.WriteCount(n);
		ar.Write(&m_vertices[0], sizeof(CPoint)*n);
		ar.Write(&m_cmpPos[0], sizeof(ScalePos)*n);
	}
	else
	{
		WORD n = ar.ReadCount();
		m_vertices.resize(n);
		m_cmpPos.resize(n);
		ar.Read(&m_vertices[0], sizeof(CPoint)*n);
		ar.Read(&m_cmpPos[0], sizeof(ScalePos)*n);		
	}
}

struct _getBounds
{
	_getBounds():m_bounds(1E5, 1E5, -1E5, -1E5){}
	void operator () (const CPoint& vertex)
	{
		if (vertex.x < m_bounds.left)
			m_bounds.left = vertex.x ;

		if (vertex.x > m_bounds.right)
			m_bounds.right = vertex.x;


		if (vertex.y < m_bounds.top)
			m_bounds.top = vertex.y;

		if (vertex.y > m_bounds.bottom)
			m_bounds.bottom = vertex.y;
	}
	operator CRect ()
	{
		return m_bounds;
	}
	CRect m_bounds;
};

inline void resetBounds(CRect& bounds, const vector<CPoint>& vertices)
{
	bounds = std::for_each(vertices.begin(), vertices.end(), _getBounds());
}

inline void resetPos(vector<ScalePos>& pos, const vector<CPoint>& vertices, 
						const CRect& bounds)
{
	int nCount = vertices.size();
	pos.resize(nCount);
	for(int i = 0; i < nCount; i++)
	{
		pos[i].X = (float)(vertices[i].x-bounds.left)/(float)bounds.Width();
		pos[i].Y = (float)(vertices[i].y-bounds.top)/(float)bounds.Height();
	}
}

void CODPolygon::AddVertex(const CPoint& point)
{
	m_vertices.push_back(point);
}

void CODPolygon::EndAddVertex()
{
	resetBounds(m_bounds, m_vertices);
	resetPos(m_cmpPos, m_vertices, m_bounds);
	SetRotCenter();
}

CRect CODPolygon::GetInvalBounds()
{
	resetBounds(m_bounds, m_vertices);
	CRect invalBounds = CODShape::GetInvalBounds();
	invalBounds.InflateRect(50, 50);
	return invalBounds;
}

void CODPolygon::DrawShape(CDC* pDC)
{
	ASSERT_VALID(this);
	Graphics gp(pDC->m_hDC);
	SmoothingMode mode = gp.GetSmoothingMode();
	CRect bounds = m_bounds;
	bounds.NormalizeRect();
	gp.SetSmoothingMode(SmoothingModeAntiAlias);
	Pen pen(m_logPen.lopnColor, m_logPen.lopnWidth.x);
	GraphicsPath path;
	int n = m_vertices.size();
	if (n > 2)
		path.AddPolygon((Point*)&m_vertices[0], n);	
	else
		path.AddLines((Point*)&m_vertices[0], n);
	PointF center(m_rotCenter.x, m_rotCenter.y);
	Matrix matrix;
	matrix.RotateAt(m_rotAngle, center);
	path.Transform(&matrix);
	gp.DrawPath(&pen, &path);
	gp.SetSmoothingMode(mode);
	gp.ReleaseHDC(pDC->m_hDC);

/*
	CBrush brush;
	brush.CreateBrushIndirect(&m_logBrush))
	CPen pen;
	pen.CreatePenIndirect(&m_logPen))
	CBrush* pOldBrush;
	CPen* pOldPen;
	pOldBrush = pDC->SelectObject(&brush);
	pOldPen = pDC->SelectObject(&pen);
	pDC->Polygon(&m_vertices[0], m_vertices.size());
	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);	
*/
}

void CODPolygon::DrawHandle(CDC* pDC)
{
	int nCount = m_vertices.size();
	for(int i = 0; i < nCount; i++)
	{
		CPoint point = RotatePoint(m_vertices[i], m_rotCenter, m_rotAngle);
		pDC->PatBlt(point.x - 3, point.y - 3, 
			7, 7, BLACKNESS);
	}
	CODShape::DrawHandle(pDC);
}

int CODPolygon::GetHandleCount()
{
	return CODShape::GetHandleCount()+m_vertices.size();
}

CPoint CODPolygon::GetHandle(int nHandle)
{
	if(nHandle > CODShape::GetHandleCount())
	{
		int nIdx = nHandle - CODShape::GetHandleCount() - 1;
		return RotatePoint(m_vertices[nIdx], m_rotCenter, m_rotAngle);
	}
	else
		return CODShape::GetHandle(nHandle);
}

int CODPolygon::HitTest(CPoint point, BOOL bSelected)
{
	if(!bSelected)
	{
		int n = m_vertices.size();
		GraphicsPath path;
		path.AddPolygon((Point*)&m_vertices[0], n);
		PointF center(m_rotCenter.x, m_rotCenter.y);
		Matrix matrix;
		matrix.RotateAt(m_rotAngle, center);
		path.Transform(&matrix);
		Pen pen(m_logPen.lopnColor, m_logPen.lopnWidth.x+5);
		return path.IsOutlineVisible((Point&)point, &pen);
/*
		CRgn rgn;
		vector<CPoint> vertices;
		for(int i = 0; i < m_vertices.size(); i ++)
		{
			vertices.push_back(RotatePoint(m_vertices[i], m_rotCenter, m_rotAngle));
		}
		rgn.CreatePolygonRgn(&vertices[0], vertices.size(), ALTERNATE);
		if (rgn.PtInRegion(point))
			return 1;
		else
			return 0;
*/
	}
	
	int nHandle = GetHandleCount();
	for(int i = 1; i <= nHandle; i++)
	{
		CPoint pt = GetHandle(i);
		CRect rect(pt.x - 3, pt.y - 3, pt.x + 3, pt.y + 3);
		if (rect.PtInRect(point))
		{
			return i;
		}
	}
	return 0;
}

HCURSOR CODPolygon::GetHandleCursor(int nHandle)
{
	if(nHandle > CODShape::GetHandleCount())
	{
		return AfxGetApp()->LoadStandardCursor(IDC_CROSS);
	}
	else
		return CODShape::GetHandleCursor(nHandle);
}

//对每一个顶点位移
struct _moveVertices
{
	_moveVertices(const CPoint& delta):m_delta(delta)
	{}
	void operator () (CPoint& vertex)
	{
		vertex += m_delta;
	}
	CPoint m_delta;
};

void CODPolygon::MoveShape(const CPoint& delta)
{
	std::for_each(m_vertices.begin(), m_vertices.end(), _moveVertices(delta));
	CODShape::MoveShape(delta);
}

void CODPolygon::MoveHandleTo(int nHandle, const CPoint& point)
{
	if (nHandle > CODShape::GetHandleCount())
	{
		int nIdx = nHandle - CODShape::GetHandleCount() - 1;
		CPoint orgPoint = GetOrgPt(point);
		m_vertices[nIdx] = orgPoint;
		resetBounds(m_bounds, m_vertices);
		resetPos(m_cmpPos, m_vertices, m_bounds);
	}
	else
	{
		CODShape::MoveHandleTo(nHandle, point);	
		int nCount = m_vertices.size();
		CRect bounds = m_bounds;
		bounds.NormalizeRect();
		for (int i = 0; i < nCount; i++)
		{
			int x = bounds.Width() * m_cmpPos[i].X + bounds.left + 0.5f;
			int y = bounds.Height() * m_cmpPos[i].Y + bounds.top + 0.5f;
			m_vertices[i].x = x;
			m_vertices[i].y = y;
		}
	}
}

void CODPolygon::EndMoveHandle()
{
	m_bounds.NormalizeRect();
	CPoint point = m_bounds.CenterPoint();
	m_rotCenter = RotatePoint(point, m_rotCenter, m_rotAngle);
	CPoint delta = m_rotCenter - point;
	m_bounds += m_rotCenter - point;
	for_each(m_vertices.begin(), m_vertices.end(), _moveVertices(delta));
}