// ODShape.h: interface for the CODShape class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ODShape_H__125A1B30_9A77_4C4D_9B48_894687D03BEC__INCLUDED_)
#define AFX_ODShape_H__125A1B30_9A77_4C4D_9B48_894687D03BEC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <list>

class CODView;

class CODShape : public CObject  
{
public:
	CODShape();
	virtual ~CODShape();
	DECLARE_SERIAL(CODShape);
	virtual void Serialize(CArchive& ar);
public:
	CODShape(const CRect& position);
	virtual void DrawShape(CDC* pDC);
	virtual void DrawHandle(CDC* pDC);
	virtual int HitTest(CPoint point, BOOL bSelected);
	virtual int GetHandleCount();
	virtual CRect GetBounds();		//未经旋转过的
	virtual HCURSOR GetHandleCursor(int nHandle);
	virtual void MoveHandleTo(int nHandle, const CPoint& point);
	virtual void MoveShape(const CPoint& delta);
	virtual void Invalidate(CODView* pView);
	virtual void EndMoveHandle();
	virtual CPoint GetHandle(int nHandle);
	virtual CRect GetHandleRect(int nHandle);
	virtual CRect GetInvalBounds();
	virtual void RotateTo(const CPoint& point);
	virtual CRect GetShapeRect();	//旋转后图形Rect,框选用
public:
	void SetRotaion(float angle);
	CPoint GetRotPt(const CPoint& point);
	CPoint GetOrgPt(const CPoint& point);
	CPoint GetRotCenter();
	void SetRotCenter();
protected:
	CRect m_bounds;
	LOGPEN m_logPen;
	LOGBRUSH m_logBrush;
	float m_rotAngle;
	CPoint m_rotCenter;		//旋转中心
};

typedef std::list<CODShape*> ODShapeList;
typedef ODShapeList::iterator ShpIt;
typedef ODShapeList::const_iterator CShpIt;

#endif // !defined(AFX_ODShape_H__125A1B30_9A77_4C4D_9B48_894687D03BEC__INCLUDED_)
