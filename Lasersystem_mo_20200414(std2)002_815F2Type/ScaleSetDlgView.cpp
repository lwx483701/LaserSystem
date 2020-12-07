// ScaleSetDlgView.cpp : implementation file
//

#include "stdafx.h"
#include "lasersystem.h"
#include "ScaleSetDlgView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScaleSetDlgView dialog


CScaleSetDlgView::CScaleSetDlgView(CWnd* pParent /*=NULL*/)
	: CDialog(CScaleSetDlgView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScaleSetDlgView)
	m_dbDownLimit = 1.0;
	m_dbUpLimit = 1.0;
	m_strChar = _T("A");
	m_ScaleSetSaved=true;
	//}}AFX_DATA_INIT
}


void CScaleSetDlgView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScaleSetDlgView)
	DDX_Text(pDX, IDC_EDT_DOWNLIMIT, m_dbDownLimit);
	DDX_Text(pDX, IDC_EDT_UPLIMIT, m_dbUpLimit);
	DDX_Text(pDX, IDC_EDT_CHAR, m_strChar);
	//}}AFX_DATA_MAP
	DDX_GridControl(pDX, IDC_SCALESETGRID, m_GridScaleSet);
}


BEGIN_MESSAGE_MAP(CScaleSetDlgView, CDialog)
	//{{AFX_MSG_MAP(CScaleSetDlgView)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BTN_ADD, OnScaleSetAdd)
	ON_BN_CLICKED(IDC_BTN_DELETE, OnScaleSetDelete)
	ON_BN_CLICKED(IDC_BTN_MODIFY, OnScaleSetModify)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnScaleSetSave)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScaleSetDlgView message handlers

int CScaleSetDlgView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
//	TODO: Add your specialized creation code here

	m_GridScaleSet.SetEditable(FALSE);
	m_GridScaleSet.SetListMode(TRUE);
	m_GridScaleSet.SetHeaderSort(FALSE);
	m_GridScaleSet.EnableDragAndDrop(TRUE);
	m_GridScaleSet.SetRowResize(FALSE);
	m_GridScaleSet.SetColumnResize(FALSE);

	TRY 
	{
		m_GridScaleSet.SetRowCount(GetDoc().GetSysScaleSetSize()+1);	//m_nRows
		m_GridScaleSet.SetColumnCount(4);								//m_nCols
		m_GridScaleSet.SetFixedRowCount(1);								//m_nFixRows;
		m_GridScaleSet.SetFixedColumnCount(1);							//m_nFixCols;
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

//	m_stCurUser.SubclassDlgItem(IDC_ST_CURUSER, this);
	return 0;
}

void CScaleSetDlgView::FillGridWithText()
{
    char buf[32];
//	DWORD dwTextStyle = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;
	DWORD dwTextStyle = DT_CENTER|DT_VCENTER|DT_SINGLELINE;
	char szRead[30]="";
	int colWidth[4]={40,130,130,40};

	for(int i=0; i<m_GridScaleSet.GetColumnCount();i++)
		m_GridScaleSet.SetColumnWidth(i, colWidth[i]);

	for (int row = 0; row < m_GridScaleSet.GetRowCount(); row++)
	{
		m_GridScaleSet.SetRowHeight(row, 20);

		for (int col = 0; col < m_GridScaleSet.GetColumnCount(); col++)
		{ 
			GV_ITEM Item;
			Item.mask = GVIF_TEXT|GVIF_FORMAT;
			Item.row = row;
			Item.col = col;

			if (row < 1)		//m_nFixRows
            {
				Item.nFormat = dwTextStyle;
				switch(col)
				{
				case 0:
//					strncpy(szRead,GetLang().GetWarningText(10079),30);
					Item.szText ="序号" ;
					break;
				case 1:
//					strncpy(szRead,GetLang().GetWarningText(10079),30);
					Item.szText ="下限值" ;
					break;
				case 2:
//					strncpy(szRead,GetLang().GetWarningText(10080),30);
					Item.szText = "上限值";
					break;
				case 3:
//					strncpy(szRead,GetLang().GetWarningText(10079),30);
					Item.szText ="字符" ;
					break;
				}
			}
            else if (col < 1)	//m_nFixCols
            {
			    sprintf(buf,"%d",row);
				Item.nFormat = dwTextStyle;
				Item.szText = buf;
			}
            else 
            {
				Item.nFormat = dwTextStyle;
				Item.szText = GetCurCellText(row,col);
			}

			m_GridScaleSet.SetItem(&Item);
			m_GridScaleSet.RedrawCell(row,col);
		}
	}
}

CString CScaleSetDlgView::GetCurCellText(UINT nRow, UINT nCol)
{
	CString str;
	std::vector<ScaleSet>::iterator ssv;
	ssv=GetDoc().GetSysScaleSet(nRow-1);	

//	ScaleSet ss = GetDoc().GetSysScaleSet(nRow-1);
	
	switch(nCol)
	{
	case 1:
		str.Format("%f",ssv->dbDownLimit);
		break;
	case 2:	
		str.Format("%f",ssv->dbUpLimit);
		break;
	case 3:	
		str=ssv->strChar;
		break;
	}

	return str;
}

void CScaleSetDlgView::OnScaleSetAdd() 
{
	// TODO: Add your control notification handler code here
    UpdateData();

	char buf[10]="";

	if(m_dbUpLimit<=m_dbDownLimit)
	{
		AfxMessageBox("输入的上下限值有误，请确认!");
		return;
	}

	std::vector<ScaleSet>::iterator ssv;
	for(int i=0;i<GetDoc().GetSysScaleSetSize();i++)
	{
		ssv=GetDoc().GetSysScaleSet(i);
		if((m_dbDownLimit<ssv->dbUpLimit)||(m_strChar==ssv->strChar))
		{
			AfxMessageBox("新增数据与已有数据有冲突，请确认!");
			return;
		}
	}

	ScaleSet ss;
	ss.dbDownLimit=m_dbDownLimit;
	ss.dbUpLimit=m_dbUpLimit;
	m_strChar.MakeUpper();
	ss.strChar=m_strChar;
	
	GetDoc().AddSysScaleSet(ss);
	m_GridScaleSet.InsertRow(buf);
    FillGridWithText();
	m_GridScaleSet.SetSelectedRange(m_GridScaleSet.GetRowCount()-1,0,
	m_GridScaleSet.GetRowCount()-1,m_GridScaleSet.GetColumnCount()-1);

	m_ScaleSetSaved=false;
	UpdateData(false);
}

void CScaleSetDlgView::OnScaleSetDelete() 
{
	// TODO: Add your control notification handler code here
	int row = m_GridScaleSet.GetFocusCell().row;
	if(row<0)
	{
		AfxMessageBox("请先选择有效行!");
		return;
	}

	GetDoc().DeleteSysScaleSet(row-1);
	
	m_GridScaleSet.DeleteRow(row);
	m_GridScaleSet.SetSelectedRange(row,0,row,m_GridScaleSet.GetColumnCount()-1);
	
	FillGridWithText();
	m_GridScaleSet.RedrawWindow();
	m_ScaleSetSaved=false;
}

void CScaleSetDlgView::OnScaleSetModify() 
{
	// TODO: Add your control notification handler code here
    UpdateData();
	int row = m_GridScaleSet.GetFocusCell().row;
	if(row<0)
	{
		AfxMessageBox("请先选择有效行!");
		return;
	}

	if(m_dbUpLimit<=m_dbDownLimit)
	{
		AfxMessageBox("输入的上下限值有误，请确认!");
		return;
	}

	std::vector<ScaleSet>::iterator ssv;
	for(int i=0;i<GetDoc().GetSysScaleSetSize();i++)
	{
		if((row-1)==i)
			continue;

		ssv=GetDoc().GetSysScaleSet(i);
		if((m_dbDownLimit<ssv->dbUpLimit)||(m_strChar==ssv->strChar))
		{
			AfxMessageBox("修改数据与原有数据有冲突，请确认!");
			return;
		}
	}

	ssv=GetDoc().GetSysScaleSet(row-1);

	ssv->dbDownLimit=m_dbDownLimit;
	ssv->dbUpLimit=m_dbUpLimit;
	ssv->strChar=m_strChar;

//	GetDoc().GetSysScaleSet(row-1).dbDownLimit=m_dbDownLimit;
//	GetDoc().GetSysScaleSet(row-1).dbUpLimit=m_dbUpLimit;
//	GetDoc().GetSysScaleSet(row-1).strChar=m_strChar;

	FillGridWithText();
	m_GridScaleSet.RedrawWindow();
	m_ScaleSetSaved=false;
}

void CScaleSetDlgView::OnScaleSetSave() 
{
	// TODO: Add your control notification handler code here
	if(!m_ScaleSetSaved)
	{
		GetDoc().SaveProcessParam();

#ifdef USELOG
		GetLog().Append_pro(10050,20051);//"系统参数保存","系统参数测试"
#endif
		m_ScaleSetSaved = true;
	}	
}

void CScaleSetDlgView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
    static int oldrow =-1;
	int row = m_GridScaleSet.GetFocusCell().row;

	if((oldrow!=row)&&(row>0))
	{
	    if(row<m_GridScaleSet.GetRowCount())
		{
			std::vector<ScaleSet>::iterator ssv;
			ssv=GetDoc().GetSysScaleSet(row-1);
			
			m_dbDownLimit=ssv->dbDownLimit;
			m_dbUpLimit=ssv->dbUpLimit;
			m_strChar=ssv->strChar;		
		}

		oldrow = row;
		UpdateData(FALSE);
//		Invalidate();
	}
	
	CDialog::OnTimer(nIDEvent);
}
