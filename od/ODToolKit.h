// ODToolKit.h: interface for the CODToolKit class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ODTOOLKIT_H__C234ADE2_7E85_4C26_A9C3_94CA788450E3__INCLUDED_)
#define AFX_ODTOOLKIT_H__C234ADE2_7E85_4C26_A9C3_94CA788450E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ODShapeTool.h"

enum DrawMode
{
	DM_SELECT = 0,		//选择
	DM_LINE,			//直线
	DM_RECT,			//矩形
	DM_ELLIPSE,			//椭圆
	DM_POLYGON,			//多边形
};

class CODToolKit  //singleton
{
public:
	~CODToolKit();
	void SetDrawMode(DrawMode mode);
	DrawMode GetDrawMode();
	CODShapeTool* GetShapeTool();
	CODShapeTool* GetShapeTool(DrawMode drawMode);
	static CODToolKit* GetToolKit(); //get singleton instance
	void OnLButtonDown(CODView* pView, UINT nFlags, CPoint point);
	void OnLButtonUp(CODView* pView, UINT nFlags, CPoint point);
	void OnMouseMove(CODView* pView, UINT nFlags, CPoint point);
	void OnLButtonDblClk(CODView* pView, UINT nFlags, CPoint point);
private:
	CODToolKit();
	void InitTools();
	void FreeTools();
	static CODToolKit s_pToolKit;
	DrawMode m_drawMode;
	ShpToolList m_toolList;
};



#endif // !defined(AFX_ODToolKit_H__C234ADE2_7E85_4C26_A9C3_94CA788450E3__INCLUDED_)
