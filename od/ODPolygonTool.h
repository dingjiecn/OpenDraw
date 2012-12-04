// ODPolygonTool.h: interface for the CODPolygonTool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ODPOLYGONTOOL_H__07B50119_0DF8_4C18_B32F_B0B831E92106__INCLUDED_)
#define AFX_ODPOLYGONTOOL_H__07B50119_0DF8_4C18_B32F_B0B831E92106__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ODShapeTool.h"
class CODPolygon;

class CODPolygonTool : public CODShapeTool  
{
public:
	CODPolygonTool();
	virtual ~CODPolygonTool();
	virtual void OnLButtonDown(CODView* pView, UINT nFlags, CPoint point);
	virtual void OnLButtonUp(CODView* pView, UINT nFlags, CPoint point);
	virtual void OnMouseMove(CODView* pView, UINT nFlags, CPoint point);
	virtual void OnLButtonDblClk(CODView* pView, UINT nFlags, CPoint point);
private:
	CODPolygon* m_pPolygon;
};

#endif // !defined(AFX_ODPOLYGONTOOL_H__07B50119_0DF8_4C18_B32F_B0B831E92106__INCLUDED_)
