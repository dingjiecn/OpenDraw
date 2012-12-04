// ODPolygon.h: interface for the CODPolygon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ODPOLYGON_H__E9A8ED83_0850_49BB_8215_F5D4E82EDA28__INCLUDED_)
#define AFX_ODPOLYGON_H__E9A8ED83_0850_49BB_8215_F5D4E82EDA28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ODShape.h"
#include <vector>

struct ScalePos
{
	float X;
	float Y;
};
class CODPolygon : public CODShape  
{
	friend class CODPolygonTool;
public:
	CODPolygon();
	DECLARE_SERIAL(CODPolygon);
	virtual void Serialize(CArchive& ar);
	virtual void DrawShape(CDC* pDC);
	virtual int HitTest(CPoint point, BOOL bSelected);
	virtual void MoveShape(const CPoint& delta);
	virtual void MoveHandleTo(int nHandle, const CPoint& point);
	virtual void DrawHandle(CDC* pDC);
	virtual int GetHandleCount();
	virtual CPoint GetHandle(int nHandle);
	virtual HCURSOR GetHandleCursor(int nHandle);
	virtual void EndMoveHandle();
	virtual CRect GetInvalBounds();
	void AddVertex(const CPoint& point);
	void EndAddVertex();
private:
	std::vector<CPoint> m_vertices;
	std::vector<ScalePos> m_cmpPos; //顶点的相对位置,缩放用
};

#endif // !defined(AFX_ODPOLYGON_H__E9A8ED83_0850_49BB_8215_F5D4E82EDA28__INCLUDED_)
