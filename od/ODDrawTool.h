#ifndef  __ODDrawTool_H__
#define __ODDrawTool_H__

#include "ODLine.h"
#include "ODDoc.h"
#include "ODView.h"

//适用于只用一次鼠标点击拖动可以创建的图形，在本例中除polygon外都可以用此模板
template<class T>
class CODDrawTool: public CODShapeTool 
{
public:
	CODDrawTool();
	virtual void OnLButtonDown(CODView* pView, UINT nFlags, CPoint point);
	virtual void OnLButtonUp(CODView* pView, UINT nFlags, CPoint point);
	virtual void OnMouseMove(CODView* pView, UINT nFlags, CPoint point);
private:
	T* m_pNewShp;
};

template<class T>
CODDrawTool<T>::CODDrawTool():m_pNewShp(NULL)
{}

template<class T>
void CODDrawTool<T>::OnLButtonDown(CODView* pView, UINT nFlags, CPoint point)
{
	CODShapeTool::OnLButtonDown(pView, nFlags, point);
	CODDoc* pDoc = pView->GetDocument();
	m_pNewShp = new T(point);
	pDoc->AddShape(m_pNewShp);
	pDoc->ClearSelection();
	pDoc->AddSelection(m_pNewShp);
	//m_pNewShp->Invalidate(pView);
	pView->Invalidate(FALSE);

	CODToolKit::GetToolKit()->GetShapeTool(DM_SELECT)->OnLButtonDown(pView, nFlags, point);
}

template<class T>
void CODDrawTool<T>::OnLButtonUp(CODView* pView, UINT nFlags, CPoint point)
{
	CODShapeTool::OnLButtonUp(pView, nFlags, point);
	if (s_lastPoint == s_downPoint)
	{
		CODDoc* pDoc = pView->GetDocument();
		CRect rect = m_pNewShp->GetBounds();
		rect.InflateRect(5, 5);
		pDoc->RemoveShape(m_pNewShp);
		pDoc->ClearSelection();
		pView->InvalidateRect(rect);
		m_pNewShp = NULL;
		return;
	}
	m_pNewShp = NULL;
	CODToolKit::GetToolKit()->GetShapeTool(DM_SELECT)->OnLButtonUp(pView, nFlags, point);
}

template<class T>
void CODDrawTool<T>::OnMouseMove(CODView* pView, UINT nFlags, CPoint point)
{
	if (m_pNewShp==NULL)
		return;
	CODShapeTool::OnMouseMove(pView, nFlags, point);
	CODToolKit::GetToolKit()->GetShapeTool(DM_SELECT)->OnMouseMove(pView, nFlags, point);
}

typedef CODDrawTool<CODRect> CODRectTool;
typedef CODDrawTool<CODLine> CODLineTool;
typedef CODDrawTool<CODEllipse> CODEllipseTool;

#endif// __ODDrawTool_H__