// FunctionTestView.cpp : implementation file
//

#include "stdafx.h"
#include "lasersystem.h"
#include "FunctionTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFunctionTestView

IMPLEMENT_DYNCREATE(CFunctionTestView, TVisualFormView)

CFunctionTestView::CFunctionTestView()
	: TVisualFormView(CFunctionTestView::IDD)
{
	//{{AFX_DATA_INIT(CFunctionTestView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CFunctionTestView::~CFunctionTestView()
{
}

void CFunctionTestView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFunctionTestView)
	DDX_Control(pDX, IDC_BT_DRILLMATRIX, m_btnDrillMatrix);
	DDX_Control(pDX, IDC_BT_LASER_POWERTEST, m_btnLaserPowerTest);
	DDX_Control(pDX, IDC_BT_LASER_WARMUP, m_btnLaserWarmUp);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFunctionTestView, TVisualFormView)
	//{{AFX_MSG_MAP(CFunctionTestView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFunctionTestView diagnostics

#ifdef _DEBUG
void CFunctionTestView::AssertValid() const
{
	CFormView::AssertValid();
}

void CFunctionTestView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFunctionTestView message handlers

int CFunctionTestView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (TVisualFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_btnLaserPowerTest.SubclassDlgItem(IDC_BT_LASER_POWERTEST,this);
	m_btnLaserPowerTest.SetIcon(IDI_LASER,IDI_LASER);

	m_btnLaserWarmUp.SubclassDlgItem(IDC_BT_LASER_WARMUP,this);
	m_btnLaserWarmUp.SetIcon(IDI_LASERWARMUP,IDI_LASERWARMUP);

	m_btnDrillMatrix.SubclassDlgItem(IDC_BT_DRILLMATRIX,this);
	m_btnDrillMatrix.SetIcon(IDI_MATRIX,IDI_MATRIX);

	return 0;
}
