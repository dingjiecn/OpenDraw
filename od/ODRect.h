// ODRect.h: interface for the CODRect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ODRECT_H__1538142C_EC54_4B19_8D82_6C2C7F51EA6D__INCLUDED_)
#define AFX_ODRECT_H__1538142C_EC54_4B19_8D82_6C2C7F51EA6D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ODShape.h"

class CODRect : public CODShape  
{
public:
	CODRect();
	DECLARE_SERIAL(CODRect);
	virtual void Serialize(CArchive& ar);
public:
	CODRect(const CRect& bounds);
	CODRect(const CPoint& point);
	virtual void DrawShape(CDC* pDC);
	virtual int HitTest(CPoint point, BOOL bSelected);
};

class CODEllipse : public CODShape  
{
public:
	CODEllipse();
	DECLARE_SERIAL(CODEllipse);
	virtual void Serialize(CArchive& ar);
public:
	CODEllipse(const CRect& bounds);
	CODEllipse(const CPoint& point);
	virtual void DrawShape(CDC* pDC);
	virtual int HitTest(CPoint point, BOOL bSelected);
};

#endif // !defined(AFX_ODRECT_H__1538142C_EC54_4B19_8D82_6C2C7F51EA6D__INCLUDED_)
