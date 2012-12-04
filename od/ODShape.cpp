// ODShape.cpp: implementation of the CODShape class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OD.h"
#include "ODShape.h"
#include "ODView.h"
#include <math.h>
#include "compgeo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const int HANDLECOUNT = 9;
const int ROTATEHANDLE = 9;
					
#define ABGR(a,r,g,b)  ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16))|(((DWORD)((BYTE)(a))<<24)))
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CODShape::CODShape()
{	
}

CODShape::~CODShape()
{
}

CODShape::CODShape(const CRect& bounds):
m_bounds(bounds)
{
	m_logPen.lopnStyle = PS_INSIDEFRAME;
	m_logPen.lopnWidth.x = 1;
	m_logPen.lopnWidth.y = 1;
	m_logPen.lopnColor = ABGR(255, 0, 0, 0);

	m_logBrush.lbStyle = BS_NULL;
	m_logBrush.lbColor = ABGR(255, 227, 224, 184);
	m_logBrush.lbHatch = HS_DIAGCROSS;
	m_rotAngle = 0.0f;
	m_rotCenter = m_bounds.CenterPoint();
}

IMPLEMENT_SERIAL(CODShape, CObject, 0)

void CODShape::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << m_bounds;
		ar.Write(&m_logPen, sizeof(LOGPEN));
		ar.Write(&m_logBrush, sizeof(LOGBRUSH));
		ar << m_rotAngle;
		ar << m_rotCenter;
	}
	else
	{
		ar >> m_bounds;
		ar.Read(&m_logPen, sizeof(LOGPEN));
		ar.Read(&m_logBrush, sizeof(LOGBRUSH));
		ar >> m_rotAngle;
		ar >> m_rotCenter;
	}
}

CPoint CODShape::GetHandle(int nHandle)
{
	ASSERT_VALID(this);
	int x, y, xCenter, yCenter;

	xCenter = m_bounds.left + m_bounds.Width() / 2;
	yCenter = m_bounds.top + m_bounds.Height() / 2;

	switch (nHandle)
	{
	default:
		ASSERT(FALSE);
	case 1:
		x = m_bounds.left;
		y = m_bounds.top;
		break;
	case 2:
		x = xCenter;
		y = m_bounds.top;
		break;
	case 3:
		x = m_bounds.right;
		y = m_bounds.top;
		break;
	case 4:
		x = m_bounds.right;
		y = yCenter;
		break;
	case 5:
		x = m_bounds.right;
		y = m_bounds.bottom;
		break;

	case 6:
		x = xCenter;
		y = m_bounds.bottom;
		break;
	case 7:
		x = m_bounds.left;
		y = m_bounds.bottom;
		break;
	case 8:
		x = m_bounds.left;
		y = yCenter;
		break;
	case ROTATEHANDLE:
		x = xCenter;
		y = ((m_bounds.top<m_bounds.bottom)?m_bounds.top:m_bounds.bottom) - 20;
		break;
	}

	return GetRotPt(CPoint(x, y));
}

CRect CODShape::GetHandleRect(int nHandle)
{
	CPoint handle = CODShape::GetHandle(nHandle);
	return CRect(handle.x-3, handle.y-3, handle.x+3, handle.y+3);
}

int CODShape::GetHandleCount()
{
	return HANDLECOUNT;
}

int CODShape::HitTest(CPoint point, BOOL bSelected)
{
	ASSERT_VALID(this);
	if(bSelected)
	{
		int nHandleCnt = CODShape::GetHandleCount();
		for(int i = 1; i <= nHandleCnt; i++)
		{
			if (PtInRect(CODShape::GetHandleRect(i), point))
				return i;
		}
	}
	return 0;
}

void CODShape::DrawShape(CDC* pDC)
{

}

void CODShape::SetRotaion(float angle)
{
	m_rotAngle = angle;
}

void CODShape::DrawHandle(CDC* pDC)
{
	int nHandleCount = CODShape::GetHandleCount();
	CBrush* oldBrush = (CBrush*)pDC->SelectStockObject(WHITE_BRUSH);
	CPen* oldPen = (CPen*)pDC->SelectStockObject(BLACK_PEN);
	for (int nHandle = nHandleCount; nHandle >= 1; nHandle--)
	{
		CRect rect = CODShape::GetHandleRect(nHandle);
		if (nHandle==ROTATEHANDLE)
		{
			CPoint pt1 = CODShape::GetHandle(ROTATEHANDLE);
			CRect bounds = m_bounds;
			bounds.NormalizeRect();
			int topHandle = m_bounds.top<m_bounds.bottom?2:6;
			CPoint pt2 = CODShape::GetHandle(topHandle);
			pDC->MoveTo(pt1);
			pDC->LineTo(pt2);
			CBrush brush(RGB(0, 255, 0));
			CBrush* oldBrush = (CBrush*)pDC->SelectObject(&brush);
			pDC->Ellipse(&rect);
			pDC->SelectObject(oldBrush);
		}
		else
			pDC->Ellipse(&rect);
	}
	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
}

CRect CODShape::GetBounds()
{
	return m_bounds;
}

HCURSOR CODShape::GetHandleCursor(int nHandle)
{
	ASSERT_VALID(this);

	if (ROTATEHANDLE==nHandle)
		return AfxGetApp()->LoadCursor(IDC_CURSOR_ROTATE);

	float theta = m_rotAngle;	//保证鼠标形状是合理的
	if (m_rotAngle < 0)
		theta += 360;
	nHandle += (theta+22.5f)/45.0f;
	nHandle %= 8;
	if (nHandle==0)
		nHandle = 8;
	
	LPCTSTR id;
	switch (nHandle)
	{
	default:
		ASSERT(FALSE);
	case 1:
	case 5:
		id = IDC_SIZENWSE;
		break;
	case 2:
	case 6:
		id = IDC_SIZENS;
		break;
	case 3:
	case 7:
		id = IDC_SIZENESW;
		break;
	case 4:
	case 8:
		id = IDC_SIZEWE;
		break;
	}
	return AfxGetApp()->LoadStandardCursor(id);
}

void CODShape::MoveShape(const CPoint& delta)
{
	m_bounds += delta;
	m_rotCenter = m_bounds.CenterPoint();
}

inline CRect getPtsBounds(CPoint* pts, int n)
{
	ASSERT(pts);
	ASSERT(n>0);
	CRect maxBounds(pts[0], pts[0]);
	for (int i = 1; i < n; i++)
	{
		if(pts[i].x>maxBounds.right)
			maxBounds.right = pts[i].x;
		if(pts[i].y>maxBounds.bottom)
			maxBounds.bottom = pts[i].y;
		if(pts[i].x<maxBounds.left)
			maxBounds.left = pts[i].x;
		if(pts[i].y<maxBounds.top)
			maxBounds.top = pts[i].y;
	}
	return maxBounds;
}

CRect CODShape::GetInvalBounds()
{
	CPoint pts[5];
	pts[0] = GetHandle(1);
	pts[1] = GetHandle(3);
	pts[2] = GetHandle(5);
	pts[3] = GetHandle(7);
	pts[4] = GetHandle(ROTATEHANDLE);
	CRect maxBounds = getPtsBounds(pts, 5);
	maxBounds.InflateRect(5, 5);
	return maxBounds;
}

CRect CODShape::GetShapeRect()
{
	CPoint pts[5];
	pts[0] = GetHandle(1);
	pts[1] = GetHandle(3);
	pts[2] = GetHandle(5);
	pts[3] = GetHandle(7);
	CRect rect(pts[0], pts[0]);
	rect = getPtsBounds(pts, 4);
	return rect;
}

void CODShape::Invalidate(CODView* pView)
{
	pView->InvalidateRect(GetInvalBounds(), FALSE);
	//pView->Invalidate(FALSE);
}

//一些后续处理工作，规格化边界，重设旋转中心等等
void CODShape::EndMoveHandle()
{
	m_bounds.NormalizeRect();
	SetRotCenter();
}

void CODShape::MoveHandleTo(int nHandle, const CPoint& point)
{
	ASSERT_VALID(this);
	if (nHandle == 9)
	{
		RotateTo(point);
		return;
	}

	CPoint orgPoint = GetOrgPt(point);
	switch (nHandle)
	{
	default:
		return;
		ASSERT(FALSE);
	case 1:
		m_bounds.left = orgPoint.x;
		m_bounds.top = orgPoint.y;
		break;

	case 2:
		m_bounds.top = orgPoint.y;
		break;

	case 3:
		m_bounds.right = orgPoint.x;
		m_bounds.top = orgPoint.y;
		break;

	case 4:
		m_bounds.right = orgPoint.x;
		break;

	case 5:
		m_bounds.right = orgPoint.x;
		m_bounds.bottom = orgPoint.y;
		break;

	case 6:
		m_bounds.bottom = orgPoint.y;
		break;

	case 7:
		m_bounds.left = orgPoint.x;
		m_bounds.bottom = orgPoint.y;
		break;

	case 8:
		m_bounds.left = orgPoint.x;
		break;
	}	
}

void CODShape::RotateTo(const CPoint& point)
{
//	CPoint point = GetHandle(ROTATEHANDLE) + delta;
	CRect bounds = GetBounds();
	CPoint center = bounds.CenterPoint();
	CPoint handle(center.x, center.y-10);
	float theta = GetAngle(center, handle, point)/PI*180;
	if (point.x < center.x)
		theta = -theta;
	SetRotaion(theta);	
}

CPoint CODShape::GetRotPt(const CPoint& point)
{
	return RotatePoint(point, m_rotCenter, m_rotAngle);
}

CPoint CODShape::GetOrgPt(const CPoint& point)
{
	return RotatePoint(point, m_rotCenter, -m_rotAngle);
}

CPoint CODShape::GetRotCenter()
{
	return m_rotCenter;
}

void CODShape::SetRotCenter()
{
	CPoint point = m_bounds.CenterPoint();
	m_rotCenter = RotatePoint(point, m_rotCenter, m_rotAngle);
	m_bounds += m_rotCenter - point;
}
