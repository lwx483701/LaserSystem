// ImesSettingDialog.cpp : implementation file
//
#include "stdafx.h"
#include "lasersystem.h"
#include "ImesSettingDialog.h"
#include "SysParameter.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define CELLWIDTH  160
#define CELLHEIDTH 30
/////////////////////////////////////////////////////////////////////////////
// CImesSettingDialog dialog
CImesSettingDialog::CImesSettingDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CImesSettingDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImesSettingDialog)
		// NOTE: the ClassWizard will add member initialization here
	m_strMachineNum=_T("");
	m_strImesURL=_T("");
	m_lTimeout=0;
	m_lIdtTime=0;
	m_bUserControlSwitch=FALSE;
	m_strHeartbeatContent=_T("");
	m_strHeartbeatFreq=_T("");
	m_beforLabel=_T("");
	//}}AFX_DATA_INIT
}

void CImesSettingDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImesSettingDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_EDIT_MACHINE, m_staMachineNum);
	DDX_Text(pDX, IDC_EDIT_MACHINE, m_strMachineNum);
	DDX_Control(pDX, IDC_EDIT_URL, m_staImesURL);
	DDX_Text(pDX, IDC_EDIT_URL, m_strImesURL);
	DDX_Control(pDX, IDC_EDIT_TIMEOUT, m_staTimeout);
	DDX_Text(pDX, IDC_EDIT_TIMEOUT, m_lTimeout);
	DDX_Control(pDX, IDC_EDIT_IDTTIME, m_staIdtTime);
	DDX_Text(pDX, IDC_EDIT_IDTTIME, m_lIdtTime);
	DDX_Control(pDX, IDC_CHECK_CONTROL, m_chkUserControlSwitch);
	DDX_Check(pDX, IDC_CHECK_CONTROL, m_bUserControlSwitch);
	DDX_Control(pDX, IDC_EDIT_CONTENT, m_staHeartbeatContent);
	DDX_Text(pDX, IDC_EDIT_CONTENT, m_strHeartbeatContent);
	DDX_Control(pDX, IDC_EDIT_FREQ, m_staHeartbeatFreq);
	DDX_Text(pDX, IDC_EDIT_FREQ, m_strHeartbeatFreq);

	//}}AFX_DATA_MAP
	DDX_GridControl(pDX, IDC_LABELTABLE, m_GridLabel);
}


BEGIN_MESSAGE_MAP(CImesSettingDialog, CDialog)
	//{{AFX_MSG_MAP(CImesSettingDialog)
	ON_WM_CREATE()
	ON_NOTIFY(GVN_BEGINLABELEDIT, IDC_LABELTABLE, SetEditDisabledBegin)
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_LABELTABLE, SetEditDisabledEnd)
	ON_BN_CLICKED(IDC_BUTTON9, OnOK)
	ON_BN_CLICKED(IDC_BUTTON1, OnCancel)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CImesSettingDialog message handlers

int CImesSettingDialog::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_GridLabel.SetEditable(TRUE);
	m_GridLabel.SetListMode(TRUE);
	m_GridLabel.SetHeaderSort(TRUE);
	m_GridLabel.EnableDragAndDrop(TRUE);
	m_GridLabel.SetTextBkColor(RGB(0xFF, 0xFF, 0xE0));

	m_GridLabel.SetEditRange(500000000,-500000000);
	TRY 
	{
		m_GridLabel.SetRowCount(GetDoc().GetSysIngredientExplainSetSize()+1);	//m_nRows
		m_GridLabel.SetColumnCount(3);								//m_nCols
		m_GridLabel.SetFixedRowCount(1);							//m_nFixRows;
		m_GridLabel.SetFixedColumnCount(1);							//m_nFixCols;
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
	m_GridLabel.SetRowResize(FALSE);
	m_GridLabel.SetColumnResize(FALSE);
	return 0;
}


CString CImesSettingDialog::GetCurCellText(UINT nRow, UINT nCol)
{
	CString str;
	std::vector<IngredientExplainSet>::iterator isv;
	isv=GetDoc().GetSysIngredientExplainSet(nRow-1);	
	switch(nCol)
	{
	case 1:
		str=isv->strLabel;
		break;
	case 2:	
		str=isv->strExplain;
		break;
	}

	return str;
}


void CImesSettingDialog::FillGridWithText()
{
    DWORD dwTextStyle = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;
	for (int row = 0; row < m_GridLabel.GetRowCount(); row++)
	{
		m_GridLabel.SetRowHeight(row, CELLHEIDTH);
		char buf[30]={""};
		char szRead[30]={""};
		for (int col = 0; col < m_GridLabel.GetColumnCount(); col++)
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
					strncpy(szRead,GetLang().GetWarningText(10059),30);
					Item.szText = szRead;//"imes下发标签号"
					break;
				case 2:
					strncpy(szRead,GetLang().GetWarningText(10060),30);
					Item.szText = szRead;//"说明"
					break;
				}
			}
            else if (col < 1) //m_nFixCols
            {
			    sprintf(buf,"%d",row);
				Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE;
				Item.szText = buf;
				m_GridLabel.SetItemState(row,col, m_GridLabel.GetItemState(row,col) | GVIS_READONLY);
			}
            else 
            {
				Item.nFormat = dwTextStyle;
				Item.szText = GetCurCellText(row,col);
			}
			m_GridLabel.SetItem(&Item);
			if(col==0)
				m_GridLabel.SetColumnWidth(col,60);
			else
				m_GridLabel.SetColumnWidth(col,160);
			m_GridLabel.RedrawCell(row,col);
		}
	}
}

BOOL CImesSettingDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_strMachineNum  = GetDoc().GetSysMachineSn();
	m_strImesURL=GetDoc().GetSysImesURL();
	m_lTimeout=GetDoc().GetSysTimeout();
	m_lIdtTime = GetDoc().GetSysIdtTime();
	m_bUserControlSwitch=GetDoc().GetSysUserControlSwitch();
	m_strHeartbeatContent=GetDoc().GetSysHeartbeatContent();
	m_strHeartbeatFreq=GetDoc().GetSysHeartbeatFreq();

	COLORREF redColor = RGB(255,0,0);
	COLORREF greedColor = RGB(0,255,0);
	m_chkUserControlSwitch.SetLedColor(greedColor,redColor);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CImesSettingDialog::OnOK() 
{
	// TODO: Add your control notification handler code here
	if (!OnSetParam())
	{
		AfxMessageBox("心跳检测项不能为空,请重新输入!");
		return;
	}

	GetDoc().SaveMotionParam();
	GetDoc().SaveWebServiceParam();
	Delay(200);
	AfxMessageBox("参数已保存!");
	
#ifdef USELOG
	GetLog().Append_pro(10050,20023);//"保存","运动参数"
#endif 	
	
	CDialog::OnOK();
}


//必须要带NMHDR和LRESULT这两个参数，否则会报错
void CImesSettingDialog::SetEditDisabledBegin(NMHDR *pNotifyStruct, LRESULT* pResult) 
{
    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
    int row = (pItem->iRow);        
    int col = (pItem->iColumn);    
 
	//根据行号列号获取单元格内容
	m_beforLabel = m_GridLabel.GetItemText(row,col);
}


//必须要带NMHDR和LRESULT这两个参数，否则会报错
void CImesSettingDialog::SetEditDisabledEnd(NMHDR *pNotifyStruct, LRESULT* pResult) 
{
    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
    int row = (pItem->iRow);        
    int col = (pItem->iColumn);    
 
	//根据行号列号获取单元格内容
	CString  afterLabel = m_GridLabel.GetItemText(row,col);
	if (m_beforLabel != afterLabel)
	{
		if (GetDoc().GetCurUserLevel() != SystemDoc::ADMIN)//如果当前登陆用户非系统用户，则不可修改
		{
			AfxMessageBox("非管理员用户不可修改!");
			FillGridWithText();
			Invalidate();
		}
		else
		{
			//保存数据
			m_GridLabel.SetItemText(row,col,afterLabel);
		}
	}
}


BOOL CImesSettingDialog::OnSetParam() 
{
	UpdateData();
	if (m_strHeartbeatContent == "" || m_strHeartbeatFreq=="")
	{
		return FALSE;
	}

	//WebService
	GetDoc().SetSysMachineSn(m_strMachineNum);
	GetDoc().SetSysImesURL(m_strImesURL);
	GetDoc().SetSysTimeout(m_lTimeout);
	GetDoc().SetSysIdtTime(m_lIdtTime);
	GetDoc().SetSysUserControlSwitch(m_bUserControlSwitch);
	//GetDoc().SetSysHeartbeatContent(m_strHeartbeatContent);
	GetDoc().SetSysHeartbeatFreq(m_strHeartbeatFreq);

	//IngredientExplainSet
	std::vector<IngredientExplainSet>::iterator isv;
	for (int row = 1; row < m_GridLabel .GetRowCount(); row++)
	{
		isv=GetDoc().GetSysIngredientExplainSet(row-1);
		for (int col = 1; col < m_GridLabel.GetColumnCount(); col++)
		{ 
			CString str = m_GridLabel.GetItemText(row,col);
			switch(col)
				{
				case 1:
					isv->strLabel = str;
					break;
				case 2:
					isv->strExplain = str;
					break;
				}	
		}
	}
	
#ifdef USELOG
	GetLog().Append_pro(10049,20023);//"设定","运动参数"
#endif
	return TRUE;

}

void CImesSettingDialog::OnCancel() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

