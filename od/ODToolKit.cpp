// ODToolKit.cpp: implementation of the CODToolKit class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OD.h"
#include "ODToolKit.h"
#include "ODDrawTool.h"
#include "ODPolygonTool.h"
#include "ODSelectTool.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CODToolKit CODToolKit::s_pToolKit;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CODToolKit::CODToolKit():m_drawMode(DM_SELECT)
{
	InitTools();
}

void CODToolKit::InitTools()
{
	CODSelectTool* pSelTool = new CODSelectTool();
	m_toolList.push_back(pSelTool);
	CODLineTool* pLineTool = new CODLineTool();
	m_toolList.push_back(pLineTool);
	CODRectTool* pRectTool = new CODRectTool();
	m_toolList.push_back(pRectTool);
	CODEllipseTool* pEllipseTool = new CODEllipseTool();
	m_toolList.push_back(pEllipseTool);
	CODPolygonTool* pPolygonTool = new CODPolygonTool();
	m_toolList.push_back(pPolygonTool);
}

void CODToolKit::FreeTools()
{
	int n = m_toolList.size();
	for(int i = n-1; i >= 0; i--)
	{
		CODShapeTool* pTool = m_toolList[i];
		m_toolList.erase(m_toolList.begin()+i);
		delete pTool;
	}
}


CODToolKit::~CODToolKit()  //程序结束自动释放?
{
	FreeTools();
}

void CODToolKit::SetDrawMode(DrawMode mode)
{
	m_drawMode = mode;
}

DrawMode CODToolKit::GetDrawMode()
{
	return m_drawMode;
}

CODToolKit* CODToolKit::GetToolKit()
{
	return &s_pToolKit;
}

CODShapeTool* CODToolKit::GetShapeTool()
{
	return m_toolList[m_drawMode];
}

CODShapeTool* CODToolKit::GetShapeTool(DrawMode drawMode)
{
	return m_toolList[drawMode];
}

void CODToolKit::OnLButtonDown(CODView* pView, UINT nFlags, CPoint point)
{
	CODShapeTool* pTool = GetShapeTool();
	pTool->OnLButtonDown(pView, nFlags, point);
}

void CODToolKit::OnLButtonUp(CODView* pView, UINT nFlags, CPoint point)
{
	CODShapeTool* pTool = GetShapeTool();
	pTool->OnLButtonUp(pView, nFlags, point);
}

void CODToolKit::OnMouseMove(CODView* pView, UINT nFlags, CPoint point)
{
	CODShapeTool* pTool = GetShapeTool();
	pTool->OnMouseMove(pView, nFlags, point);
}

void CODToolKit::OnLButtonDblClk(CODView* pView, UINT nFlags, CPoint point)
{
	CODShapeTool* pTool = GetShapeTool();
	pTool->OnLButtonDblClk(pView, nFlags, point);
}