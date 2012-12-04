// ODDoc.cpp : implementation of the CODDoc class
//

#include "stdafx.h"
#include "OD.h"

#include "ODDoc.h"
#include "ODView.h"
#include <algorithm>
#include "odline.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CODDoc

IMPLEMENT_DYNCREATE(CODDoc, CDocument)

BEGIN_MESSAGE_MAP(CODDoc, CDocument)
	//{{AFX_MSG_MAP(CODDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CODDoc construction/destruction

CODDoc::CODDoc():m_paperSize(850, 1100), m_nMapMode(MM_ISOTROPIC)
{
}

CODDoc::~CODDoc()
{
	CODShape* pShp;
	ShpIt it = m_shapeList.begin();
	for(; it != m_shapeList.end(); it++)
	{
		pShp = *it;
		delete pShp;
	}
}

BOOL CODDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CODDoc serialization

void CODDoc::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		WORD n = m_shapeList.size();
		ar.WriteCount(n);
		ShpIt it = m_shapeList.begin();
		for(; it != m_shapeList.end(); it++)
		{
			ar << *it;
		}
	}
	else
	{
		WORD n = ar.ReadCount();
		CODShape* pShape;
		while(n--)
		{
			ar >> pShape;
			m_shapeList.push_back(pShape);
		}
	}
}

CODShape* CODDoc::AddShape(CODShape* pShape)
{
	m_shapeList.push_back(pShape);
	return pShape;
}

BOOL CODDoc::RemoveShape(CODShape* pShape)
{
	ShpIt it = std::find(m_shapeList.begin(), m_shapeList.end(), pShape);
	if (it != m_shapeList.end())
	{
		m_shapeList.erase(it);
		delete pShape;
		return TRUE;
	}
	return FALSE;
}

CODShape* CODDoc::AddSelection(CODShape* pShape)
{
	m_selection.push_back(pShape);
	return pShape;
}

void CODDoc::RectSelect(CRect rect)
{
	ShpIt it = m_shapeList.begin();
	for(; it != m_shapeList.end(); it++)
	{
		CRect shpRect = (*it)->GetShapeRect();
		if (rect.PtInRect(shpRect.TopLeft())
			&&rect.PtInRect(shpRect.BottomRight()))
			AddSelection(*it);		
	}
}

void CODDoc::ClearSelection()
{
	m_selection.clear();
}

const ODShapeList& CODDoc::GetSelection()
{
	return m_selection;
}

CODShape* CODDoc::GetShapeAt(const CPoint& point)
{
	ShpIt it = m_shapeList.begin();
	for(; it != m_shapeList.end(); it++)
	{
		if ((*it)->HitTest(point, FALSE))
			return *it;
	}
	return NULL;
}

BOOL CODDoc::IsSelected(CODShape* pShape)
{
	ShpIt it = m_selection.begin();
	for(; it != m_selection.end(); it++)
	{
		if (pShape == *it)
			return TRUE;
	}
	return FALSE;
}

void CODDoc::DrawShape(CDC* pDC)
{
	ShpIt it = m_shapeList.begin();
	for(; it != m_shapeList.end(); it++)
	{
		(*it)->DrawShape(pDC);
	}
	it = m_selection.begin();
	for(; it != m_selection.end(); it++)
	{
		(*it)->DrawHandle(pDC);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CODDoc diagnostics

#ifdef _DEBUG
void CODDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CODDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CODDoc commands
