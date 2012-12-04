// ODDoc.h : interface of the CODDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ODDOC_H__52F2B96B_ED0A_4295_BDD3_31179BC737D2__INCLUDED_)
#define AFX_ODDOC_H__52F2B96B_ED0A_4295_BDD3_31179BC737D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ODShape.h"
#include "ODRect.h"

class CODView;
class CODDoc : public CDocument
{
protected: // create from serialization only
	CODDoc();
	DECLARE_DYNCREATE(CODDoc)

public:
	CODShape* AddShape(CODShape* pShape);
	BOOL RemoveShape(CODShape* pShape);
	CODShape* AddSelection(CODShape* pShape);
	CODShape* GetShapeAt(const CPoint& point);
	const ODShapeList& GetSelection();
	void ClearSelection();
	void DrawShape(CDC* pDC);
	void RectSelect(CRect rect);
	BOOL IsSelected(CODShape* pShape);
private:


public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CODDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CODDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	ODShapeList m_shapeList;
	ODShapeList m_selection;
	int m_nMapMode;
	CSize m_paperSize;

// Generated message map functions
protected:
	//{{AFX_MSG(CODDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ODDOC_H__52F2B96B_ED0A_4295_BDD3_31179BC737D2__INCLUDED_)
