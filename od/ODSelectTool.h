// ODSelectTool.h: interface for the CODSelectTool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ODSELECTTOOL_H__644BF1DB_F548_4A75_B713_2B9C54564F7C__INCLUDED_)
#define AFX_ODSELECTTOOL_H__644BF1DB_F548_4A75_B713_2B9C54564F7C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ODShapeTool.h"

enum SelectMode
{
	SM_NONE = 0,
	SM_MOVE, 
	SM_SIZE,
	SM_ROTATE,
	SM_RECTSEL
};

class CODSelectTool: public CODShapeTool
{
public:
	CODSelectTool();
	virtual void OnLButtonDown(CODView* pView, UINT nFlags, CPoint point);
	virtual void OnLButtonUp(CODView* pView, UINT nFlags, CPoint point);
	virtual void OnMouseMove(CODView* pView, UINT nFlags, CPoint point);
private:
	SelectMode m_selectMode;
	int m_nMoveHandle;
};

#endif // !defined(AFX_ODSELECTTOOL_H__644BF1DB_F548_4A75_B713_2B9C54564F7C__INCLUDED_)
