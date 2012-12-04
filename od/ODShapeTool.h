// ODShapeTool.h: interface for the CODShapeTool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ODSHAPETOOL_H__C9DE1A66_229C_4987_939D_05B190AD2B12__INCLUDED_)
#define AFX_ODSHAPETOOL_H__C9DE1A66_229C_4987_939D_05B190AD2B12__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>

class CODView;
class CODRect;
class CODLine;

class CODShapeTool  
{
public:
	virtual void OnLButtonDown(CODView* pView, UINT nFlags, CPoint point);
	virtual void OnLButtonUp(CODView* pView, UINT nFlags, CPoint point);
	virtual void OnMouseMove(CODView* pView, UINT nFlags, CPoint point);
	virtual void OnLButtonDblClk(CODView* pView, UINT nFlags, CPoint point);
protected:
	static CPoint s_downPoint;
	static CPoint s_lastPoint;
};

typedef std::vector<CODShapeTool*> ShpToolList;

#endif // !defined(AFX_ODSHAPETOOL_H__C9DE1A66_229C_4987_939D_05B190AD2B12__INCLUDED_)
