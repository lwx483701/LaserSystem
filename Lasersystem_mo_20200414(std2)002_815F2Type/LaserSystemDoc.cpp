// LaserSystemDoc.cpp : implementation of the CLaserSystemDoc class
//

#include "stdafx.h"
#include "LaserSystem.h"

#include "LaserSystemDoc.h"
#include "TabWnd.h"
#include "MainFrm.h"

//#include "FrameworkProperties.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLaserSystemDoc

IMPLEMENT_DYNCREATE(CLaserSystemDoc, CDocument)

BEGIN_MESSAGE_MAP(CLaserSystemDoc, CDocument)
	//{{AFX_MSG_MAP(CLaserSystemDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLaserSystemDoc construction/destruction

CLaserSystemDoc::CLaserSystemDoc()
{
	// TODO: add one-time construction code here
}

CLaserSystemDoc::~CLaserSystemDoc()
{
}

BOOL CLaserSystemDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CLaserSystemDoc serialization

void CLaserSystemDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CLaserSystemDoc diagnostics

#ifdef _DEBUG
void CLaserSystemDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLaserSystemDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLaserSystemDoc commands

BOOL CLaserSystemDoc::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
  CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
  if (pFrame && pFrame->m_Framework.OnCmdMsg(nID,nCode,pExtra,pHandlerInfo))
    return TRUE;
  
  return CDocument::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}
