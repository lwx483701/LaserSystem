// MotionParameterView.cpp : implementation file
//

#include "stdafx.h"
#include "lasersystem.h"
#include "MotionParameterView.h"
#include "SysParameter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMotionParameterView

#define CELLWIDTH  100
#define CELLHEIDTH 36
IMPLEMENT_DYNCREATE(CMotionParameterView, TVisualFormView)

CMotionParameterView::CMotionParameterView()
	: TVisualFormView(CMotionParameterView::IDD)
{
	//{{AFX_DATA_INIT(CMotionParameterView)
		// NOTE: the ClassWizard will add member initialization here
	m_SysMotion = false;
	//}}AFX_DATA_INIT
}

CMotionParameterView::~CMotionParameterView()
{

}

void CMotionParameterView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMotionParameterView)
	DDX_Control(pDX, IDC_BT_SET, m_btnSet);
	DDX_Control(pDX, IDC_BT_SAVE, m_btnSave);
	DDX_Control(pDX, IDC_BT_RESET, m_btnReset);
	//}}AFX_DATA_MAP
	DDX_GridControl(pDX, IDC_GRIDMOTIONPARAM, m_Grid);

}

BEGIN_MESSAGE_MAP(CMotionParameterView, TVisualFormView)
	//{{AFX_MSG_MAP(CMotionParameterView)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BT_SET, OnSetParam)
	ON_BN_CLICKED(IDC_BT_RESET, OnResetParam)
	ON_BN_CLICKED(IDC_BT_SAVE, OnSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMotionParameterView diagnostics

#ifdef _DEBUG
void CMotionParameterView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMotionParameterView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMotionParameterView message handlers
int CMotionParameterView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (TVisualFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_btnReset.SubclassDlgItem(IDC_BT_RESET,this);
	m_btnReset.SetIcon(IDI_RESET,IDI_RESET);

	m_btnSet.SubclassDlgItem(IDC_BT_SET,this);
	m_btnSet.SetIcon(IDI_SET,IDI_SET);

	m_btnSave.SubclassDlgItem(IDC_BT_SAVE,this);
	m_btnSave.SetIcon(IDI_SAVEP,IDI_SAVEP);

	m_Grid.SetEditable(TRUE);
	m_Grid.SetListMode(TRUE);
	m_Grid.SetHeaderSort(FALSE);
	m_Grid.EnableDragAndDrop(TRUE);
	m_Grid.SetTextBkColor(RGB(0xFF, 0xFF, 0xE0));

	m_Grid.SetEditRange(500000000,-500000000);
	TRY {
		m_Grid.SetRowCount(12);   //m_nRows
//		m_Grid.SetColumnCount(5);  //m_nCols
		m_Grid.SetColumnCount(4);  //m_nCols			//20160907
		m_Grid.SetFixedRowCount(1);//m_nFixRows;
		m_Grid.SetFixedColumnCount(1);//m_nFixCols;
	}
	CATCH (CMemoryException, e)
	{
		e->ReportError();
		e->Delete();
		return FALSE;
	}
    END_CATCH

    DWORD dwTextStyle = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;
#ifndef _WIN32_WCE
    dwTextStyle |= DT_END_ELLIPSIS;
#endif

	FillGridWithText();
	m_Grid.SetRowResize(FALSE);
	m_Grid.SetColumnResize(FALSE);

	return 0;
}

CString CMotionParameterView::GetCurCellText(UINT nRow, UINT nCol)
{
      
	CString str;
	switch(nCol)
	{
	case 1:
		str.Format("%d",GetDoc().GetMoveAcc(GetAxisEncode(nRow-1)));
		break;
	case 2:	
		str.Format("%d",GetDoc().GetMoveMaxSpeed(GetAxisEncode(nRow-1)));
		break;
	case 3:	
		str.Format("%d",GetDoc().GetMoveDec(GetAxisEncode(nRow-1)));
		break;
	case 4:	
		break;
	}
	return str;
}

UINT CMotionParameterView::GetAxisEncode(int nIndex) const
{
     UINT ulRtn;
	 switch(nIndex)
	 {
	 case 0:
	     ulRtn = AXISTABX;
		 break;
	 case 1:
	     ulRtn = AXISTABY;
		 break;
	 case 2:
		 ulRtn = AXISTAB;
		 break;
	 case 3:
	     ulRtn = AXISBETPRI;
		 break;
	 case 4:
	     ulRtn = AXISAPT;
		 break;
	 case 5:
	     ulRtn = AXISLOADX;
		 break;
	 case 6:
	     ulRtn = AXISLOADY;
		 break;
	 case 7:
	     ulRtn = AXISLEFTZ;
		 break;
	 case 8:
		 ulRtn = AXISRIGHTZ;
		 break;
	 case 9:
		 ulRtn = AXISUNLOADX;
		 break;
	 case 10:
		 ulRtn = AXISUNLOADY;
		 break;
	 }
	return ulRtn;
}

void CMotionParameterView::FillGridWithText()
{
    DWORD dwTextStyle = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;
	for (int row = 0; row < m_Grid.GetRowCount(); row++)
	{
		m_Grid.SetRowHeight(row, CELLHEIDTH-6);
		char szRead[30]={""};
		for (int col = 0; col < m_Grid.GetColumnCount(); col++)
		{ 
			GV_ITEM Item;
			Item.mask = GVIF_TEXT|GVIF_FORMAT;
			Item.row = row;
			Item.col = col;
			if (row < 1)
            {
				Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE;

				switch(col)
				{
				case 1:
					strncpy(szRead,GetLang().GetWarningText(10061),30);
					Item.szText =szRead;//"加速度"
					break;
				case 2:
					strncpy(szRead,GetLang().GetWarningText(10062),30);
					Item.szText = szRead;//"最大速度"
					break;
				case 3:
					strncpy(szRead,GetLang().GetWarningText(10063),30);
					Item.szText = szRead;//"减速度"
					break;
				case 4:
					strncpy(szRead,GetLang().GetWarningText(10064),30);
					Item.szText = szRead;//"-"
					break;
				}
			}
            else if (col < 1) //m_nFixCols
            {
				Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE;
				switch(row)
				{
				case 1:
					strncpy(szRead,GetLang().GetWarningText(10065),30);
					Item.szText =szRead ;//"平台X轴"
					break;
				case 2:
					strncpy(szRead,GetLang().GetWarningText(10066),30);
					Item.szText =szRead ;//"平台Y轴"
					break;
				case 3:
					strncpy(szRead,GetLang().GetWarningText(10067),30);
					Item.szText =szRead ;//"平台XY"
					break;
				case 4:
					strncpy(szRead,GetLang().GetWarningText(10068),30);
					Item.szText = szRead;//"光束调节"
					break;
				case 5:
					strncpy(szRead,GetLang().GetWarningText(10069),30);
					Item.szText =szRead ;//"光圈调整"
					break;
				case 6:
					strncpy(szRead,GetLang().GetWarningText(10070),30);
					Item.szText = szRead;//"上料升降"
					break;
				case 7:
					strncpy(szRead,GetLang().GetWarningText(10071),30);
					Item.szText =szRead ;//"上料平移"
					break;
				case 8:
					strncpy(szRead,GetLang().GetWarningText(10072),30);
					Item.szText = szRead;//"左侧Z轴"
					break;
				case 9:
					strncpy(szRead,GetLang().GetWarningText(10073),30);
					Item.szText = szRead;//"右侧Z轴"
					break;
				case 10:
					strncpy(szRead,GetLang().GetWarningText(10074),30);
					Item.szText = szRead;//"下料升降"
					break;
				case 11:
					strncpy(szRead,GetLang().GetWarningText(10075),30);
					Item.szText = szRead;//"下料平移"
					break;
				}
			}
            else 
            {
				Item.nFormat = dwTextStyle;
				Item.szText = GetCurCellText(row,col);
			}
			m_Grid.SetItem(&Item);
			if(col==0)
				m_Grid.SetColumnWidth(col,CELLWIDTH+32);
			else
				m_Grid.SetColumnWidth(col,CELLWIDTH+22);
			m_Grid.RedrawCell(row,col);
		}
	}
}

void CMotionParameterView::OnSetParam() 
{
	if(!m_SysMotion)
	{
		m_SysMotion = true;

		for (int row = 1; row < m_Grid.GetRowCount(); row++)
		{
			for (int col = 1; col < m_Grid.GetColumnCount(); col++)
			{ 
				CString str = m_Grid.GetItemText(row,col);
				long lva = atol(str);
				
				switch(col)
				{
				case 1:
					GetDoc().SetMoveAcc(GetAxisEncode(row-1),lva);
					break;
				case 2:
					GetDoc().SetMoveMaxSpeed(GetAxisEncode(row-1),lva);
					break;
				case 3:
					GetDoc().SetMoveDec(GetAxisEncode(row-1),lva);
					break;
				}
			}
		}
		
#ifdef USELOG
		GetLog().Append_pro(10049,20023);//"设定","运动参数"
#endif

		m_SysMotion = false;
	}
}

void CMotionParameterView::OnSave() 
{
//	if(!m_SysMotion)
//	{
//		m_SysMotion = true;

		OnSetParam() ;
//		GetDoc().ReleaseSysDoc();
		GetDoc().SaveMotionParam();
		Delay(200);
		AfxMessageBox("参数已设定并保存！");
		
#ifdef USELOG
		GetLog().Append_pro(10050,20023);//"保存","运动参数"
#endif 

//		m_SysMotion = false;
//	}
}

void CMotionParameterView::OnResetParam() 
{
	if(!m_SysMotion)
	{
		m_SysMotion = true;

		FillGridWithText();
		Invalidate();
		
#ifdef USELOG
		GetLog().Append_pro(10051,20023);//"恢复","运动参数"
#endif 

		m_SysMotion = false;
	}
}

void CMotionParameterView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	static int n;
	if(bActivate)
	{
		int nLevel = GetDoc().GetCurUserLevel();
		if(nLevel==SystemDoc::ADMIN)//系统
		{
			 m_Grid.SetEditable(TRUE);
			 m_Grid.SetTextBkColor(RGB(255,255,255));			 

			 m_btnSet.EnableWindow(TRUE);
			 m_btnSave.EnableWindow(TRUE);
			 m_btnReset.EnableWindow(TRUE);
		}
		else
		{
			 m_Grid.SetEditable(FALSE);
			 m_Grid.SetTextBkColor(RGB(214,211,206));	
			 m_btnSet.EnableWindow(FALSE);
			 m_btnSave.EnableWindow(FALSE);
			 m_btnReset.EnableWindow(FALSE);
		}
	}
	TVisualFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CMotionParameterView::SetUI()//ly add 20110318
{
	char szRead[20] = {""};
	GetLang().GetUIText("MotionParameter","IDC_BT_RESET",szRead,20);
	SetDlgItemText(IDC_BT_RESET,szRead);
	GetLang().GetUIText("MotionParameter","IDC_BT_SET",szRead,20);
	SetDlgItemText(IDC_BT_SET,szRead);
	GetLang().GetUIText("MotionParameter","IDC_BT_SAVE",szRead,20);
	SetDlgItemText(IDC_BT_SAVE,szRead);
}

void CMotionParameterView::OnInitialUpdate() 
{
	TVisualFormView::OnInitialUpdate();
	if(GetLang().GetCurLanguage()==1)
		SetUI();

	// TODO: Add your specialized code here and/or call the base class
}
