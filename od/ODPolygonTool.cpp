// ODPolygonTool.cpp: implementation of the CODPolygonTool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OD.h"
#include "ODPolygonTool.h"
#include "ODPolygon.h"
#include "ODDoc.h"
#include "ODView.h"
#include "ODToolKit.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CODPolygonTool::CODPolygonTool():m_pPolygon(NULL)
{

}

CODPolygonTool::~CODPolygonTool()
{

}

void CODPolygonTool::OnLButtonDown(CODView* pView, UINT nFlags, CPoint point)
{
	CODShapeTool::OnLButtonDown(pView, nFlags, point);

	if (m_pPolygon == NULL)  //新建一个多边形
	{
		CODDoc* pDoc = pView->GetDocument();
		m_pPolygon = new CODPolygon();
		pDoc->AddShape(m_pPolygon);
		pDoc->ClearSelection();
		pView->Invalidate(FALSE);
		m_pPolygon->AddVertex(point);
	}	
	m_pPolygon->AddVertex(point);
}

void CODPolygonTool::OnLButtonUp(CODView* pView, UINT nFlags, CPoint point)
{
	//避免执行基类的ReleaseCapture
}

void CODPolygonTool::OnMouseMove(CODView* pView, UINT nFlags, CPoint point)
{
	if (m_pPolygon == NULL)
		return;
	int nLast = m_pPolygon->m_vertices.size() - 1;
	m_pPolygon->m_vertices[nLast] = point;
	m_pPolygon->Invalidate(pView);

	CODShapeTool::OnMouseMove(pView, nFlags, point);
}

void CODPolygonTool::OnLButtonDblClk(CODView* pView, UINT nFlags, CPoint point)
{
	::ReleaseCapture();
	m_pPolygon->m_vertices.pop_back();
	m_pPolygon->EndAddVertex();
	pView->GetDocument()->AddSelection(m_pPolygon);
	pView->Invalidate();
	m_pPolygon = NULL;
	CODToolKit::GetToolKit()->SetDrawMode(DM_SELECT);
}