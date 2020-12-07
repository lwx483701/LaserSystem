// LaserSystemView.cpp : implementation of the CLaserSystemView class
//

#include "stdafx.h"
#include "LaserSystem.h"

#include "LaserSystemDoc.h"
#include "LaserSystemView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLaserSystemView

IMPLEMENT_DYNCREATE(CLaserSystemView, CView)

BEGIN_MESSAGE_MAP(CLaserSystemView, CView)
	//{{AFX_MSG_MAP(CLaserSystemView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLaserSystemView construction/destruction

CLaserSystemView::CLaserSystemView()
{
	// TODO: add construction code here

}

CLaserSystemView::~CLaserSystemView()
{
}

BOOL CLaserSystemView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLaserSystemView drawing

void CLaserSystemView::OnDraw(CDC* pDC)
{
	CLaserSystemDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CLaserSystemView printing

BOOL CLaserSystemView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLaserSystemView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLaserSystemView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CLaserSystemView diagnostics

#ifdef _DEBUG
void CLaserSystemView::AssertValid() const
{
	CView::AssertValid();
}

void CLaserSystemView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLaserSystemDoc* CLaserSystemView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLaserSystemDoc)));
	return (CLaserSystemDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLaserSystemView message handlers
