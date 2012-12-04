l// ODShapeTool.cpp: implementation of the CODShapeTool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OD.h"
#include "ODShape.h"
#include "ODDoc.h"
#include "ODView.h"
#include "ODToolKit.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CPoint CODShapeTool::s_downPoint(0, 0);
CPoint CODShapeTool::s_lastPoint(0, 0);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
void CODShapeTool::OnLButtonDown(CODView* pView, UINT nFlags, CPoint point)
{
	pView->SetCapture();
	s_downPoint = point;
	s_lastPoint = point;
}

void CODShapeTool::OnLButtonUp(CODView* pView, UINT nFlags, CPoint point)
{
	ReleaseCapture();	
	CODToolKit::GetToolKit()->SetDrawMode(DM_SELECT);
}

void CODShapeTool::OnMouseMove(CODView* pView, UINT nFlags, CPoint point)
{
	s_lastPoint = point;	
//	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
}

void CODShapeTool::OnLButtonDblClk(CODView* pView, UINT nFlags, CPoint point)
{

}
