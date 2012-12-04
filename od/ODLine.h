// ODLine.h: interface for the CODLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ODLINE_H__DE7440CD_6BE1_4086_AFCB_899CC264EB7B__INCLUDED_)
#define AFX_ODLINE_H__DE7440CD_6BE1_4086_AFCB_899CC264EB7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ODShape.h"

class CODLine : public CODShape  
{
public:
	CODLine();
	DECLARE_SERIAL(CODLine);
	virtual void Serialize(CArchive& ar);
public:
	CODLine(const CPoint& ptStart, const CPoint& ptEnd);
	CODLine(const CPoint& point);
	virtual void DrawShape(CDC* pDC);
	virtual int HitTest(CPoint point, BOOL bSelected);
	virtual void DrawHandle(CDC* pDC);
	virtual void MoveHandleTo(int nHandle, const CPoint& point);
	virtual HCURSOR GetHandleCursor(int nHandle);
	virtual void MoveShape(const CPoint& delta);
private:
	CPoint m_ptStart;
	CPoint m_ptEnd;
	CRect m_rcStart;
	CRect m_rcEnd;
};

#endif // !defined(AFX_ODLINE_H__DE7440CD_6BE1_4086_AFCB_899CC264EB7B__INCLUDED_)
