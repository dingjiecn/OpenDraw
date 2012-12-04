// ODSelectTool.cpp: implementation of the CODSelectTool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OD.h"
#include "ODSelectTool.h"
#include "ODDoc.h"
#include "ODView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CODSelectTool::CODSelectTool():m_selectMode(SM_NONE),m_nMoveHandle(0)
{}

void CODSelectTool::OnLButtonDown(CODView* pView, UINT nFlags, CPoint point)
{
	CODDoc* pDoc = pView->GetDocument();
	ASSERT_VALID(pDoc);
	const ODShapeList& selection = pDoc->GetSelection();
	CODShape* pShape = pDoc->GetShapeAt(point);
	if (selection.size()==1)				//已经选中目标，点击测试判断状态是否应为Resize
	{
		CODShape* pSelShp = *selection.begin();
		int nHandle = pSelShp->HitTest(point, TRUE);
		if (nHandle > 0)
		{
			m_selectMode = nHandle==9?SM_ROTATE:SM_SIZE;
			m_nMoveHandle = nHandle;
			if (nHandle==9)
				::SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR_ROTATE));
			else
				::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
			CODShapeTool::OnLButtonDown(pView, nFlags, point);
			return;
		}
	}	

	if (pShape!=NULL)				
	{
		if(selection.size()>0&&pDoc->IsSelected(pShape))
		{

		}
		else		//重新选择目标，状态为moving
		{
			pDoc->ClearSelection();
			pDoc->AddSelection(pShape);
			pView->Invalidate(FALSE);
		}
		m_selectMode = SM_MOVE;
	}
	else
	{
		pDoc->ClearSelection();
		pView->Invalidate(FALSE);
		CClientDC dc(pView);
		CRect rect(point.x, point.y, point.x, point.y);
		rect.NormalizeRect();
		dc.DrawFocusRect(rect);
		m_selectMode = SM_RECTSEL;
	}
	CODShapeTool::OnLButtonDown(pView, nFlags, point);	
}

void CODSelectTool::OnLButtonUp(CODView* pView, UINT nFlags, CPoint point)
{
	CODDoc* pDoc = pView->GetDocument();
	ASSERT_VALID(pDoc);
	const ODShapeList& selection = pDoc->GetSelection();
	if (m_selectMode==SM_SIZE&&selection.size()==1)
		(*selection.begin())->EndMoveHandle();
	if(m_selectMode==SM_RECTSEL)
	{
		CClientDC dc(pView);
		CRect rect(s_downPoint.x, s_downPoint.y, s_lastPoint.x, s_lastPoint.y);
		rect.NormalizeRect();
		dc.DrawFocusRect(rect);
		pDoc->RectSelect(rect);	
		pView->Invalidate(FALSE);
	}
	m_selectMode = SM_NONE;
	CODShapeTool::OnLButtonUp(pView, nFlags, point);
}

void CODSelectTool::OnMouseMove(CODView* pView, UINT nFlags, CPoint point)
{
	CODDoc* pDoc = pView->GetDocument();
	ASSERT_VALID(pDoc);
	const ODShapeList& selection = pDoc->GetSelection();
	CODShape* pShape = NULL;
	if (selection.size()>0)
		pShape = *selection.begin();
	if (pShape==NULL)
	{
		if(m_selectMode==SM_RECTSEL)
		{
			CClientDC dc(pView);
			CRect rect(s_downPoint.x, s_downPoint.y, s_lastPoint.x, s_lastPoint.y);
			rect.NormalizeRect();
			dc.DrawFocusRect(rect);//擦去上一次的框框
			rect.SetRect(s_downPoint.x, s_downPoint.y, point.x, point.y);
			rect.NormalizeRect();
			dc.DrawFocusRect(rect);
			CODShapeTool::OnMouseMove(pView, nFlags, point);
		}
		return;
	}
	CPoint delta = point - s_lastPoint;
	if (m_selectMode == SM_MOVE)
	{
		CShpIt it = selection.begin();
		for(; it != selection.end(); it++)
		{
			(*it)->Invalidate(pView);
			(*it)->MoveShape(delta);
			(*it)->Invalidate(pView);
		}
	}		
	else if (m_selectMode==SM_SIZE||m_selectMode==SM_ROTATE)
	{
		pShape->Invalidate(pView);
		pShape->MoveHandleTo(m_nMoveHandle, point);
		pShape->Invalidate(pView);
		return;
	}
	else //if (m_selectMode==SM_NONE) //做鼠标形状的测试
	{
		if (selection.size()>1)
			return;
		CRect bounds = pShape->GetInvalBounds();
		if (!PtInRect(bounds, point))			//优化
			return;

		int nHandle = pShape->HitTest(point, TRUE);
		if (nHandle > 0)
		{
			::SetCursor(pShape->GetHandleCursor(nHandle));
			return;
		}
	}
	CODShapeTool::OnMouseMove(pView, nFlags, point);	
}
