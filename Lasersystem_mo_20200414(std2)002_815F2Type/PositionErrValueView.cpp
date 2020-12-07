// PositionErrValueView.cpp : implementation file
//

#include "stdafx.h"
#include "lasersystem.h"
#include "PositionErrValueView.h"
#include "operatecontrol.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPositionErrValueView
#define CELLWIDTH  58
#define CELLHEIDTH 32
IMPLEMENT_DYNCREATE(CPositionErrValueView, TVisualFormView)

CPositionErrValueView::CPositionErrValueView()
	: TVisualFormView(CPositionErrValueView::IDD)
{
	//{{AFX_DATA_INIT(CPositionErrValueView)
	m_mationdelay = 0;
	m_mationend = GetDoc().GetAxisXErrEnd();//-330000;//ly change 20110212      0->-330000 默认X轴
	m_mationstar = GetDoc().GetAxisXErrStart(); //330000;//ly change 20110212
	m_chooseXY = 0;//ly change 20110212 -1->0;
	m_MationTime = 1;
	m_mationpuls  = true;
	m_SysPosition = false;
	//}}AFX_DATA_INIT
}

CPositionErrValueView::~CPositionErrValueView()
{

}

void CPositionErrValueView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPositionErrValueView)
	DDX_Control(pDX, IDC_BETFACTOR, m_BetFactor);
	DDX_Control(pDX, IDC_BUTTONpause, m_mationpause);
	DDX_Control(pDX, IDC_BT_SET, m_btnSet);
	DDX_Control(pDX, IDC_BT_SAVE, m_btnSave);
	DDX_Control(pDX, IDC_BT_RESET, m_btnReset);
	DDX_Text(pDX, IDC_MationDelay, m_mationdelay);
	DDX_Text(pDX, IDC_MationEnd, m_mationend);
	DDX_Text(pDX, IDC_MationStar, m_mationstar);
	DDX_Radio(pDX, IDC_RADIOChooseX, m_chooseXY);
	DDX_Text(pDX, IDC_MationTime, m_MationTime);
	//}}AFX_DATA_MAP
	DDX_GridControl(pDX, IDC_GRIDPOSITIONERR, m_GridErr);
	DDX_GridControl(pDX, IDC_GRIDBETPOS,      m_GridBET);

}


BEGIN_MESSAGE_MAP(CPositionErrValueView, TVisualFormView)
	//{{AFX_MSG_MAP(CPositionErrValueView)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BT_SAVE, OnSave)
	ON_BN_CLICKED(IDC_BT_SET, OnSet)
	ON_BN_CLICKED(IDC_BT_RESET, OnReset)
	ON_BN_CLICKED(IDC_BUTTON1, OnMationRun)
	ON_BN_CLICKED(IDC_BUTTON9, OnMoveStar)
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_SPIN1, OnPusl)
	ON_BN_CLICKED(IDC_BUTTON2, OnButtonPusle)
	ON_BN_CLICKED(IDC_BUTTONpause, OnBUTTONpause)
	ON_BN_CLICKED(IDC_RADIOChooseX, OnRADIOChooseX)
	ON_BN_CLICKED(IDC_RADIOChooseY, OnRADIOChooseY)
//	ON_CBN_SELCHANGE(IDC_BETFACTOR, OnSelchangeBetfactor)
//	ON_BN_CLICKED(IDC_FITBET, OnFitBET)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPositionErrValueView diagnostics

#ifdef _DEBUG
void CPositionErrValueView::AssertValid() const
{
	CFormView::AssertValid();
}

void CPositionErrValueView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPositionErrValueView message handlers
int CPositionErrValueView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (TVisualFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_btnReset.SubclassDlgItem(IDC_BT_RESET,this);
	m_btnReset.SetIcon(IDI_RESET,IDI_RESET);

	m_btnSet.SubclassDlgItem(IDC_BT_SET,this);
	m_btnSet.SetIcon(IDI_SET,IDI_SET);

	m_btnSave.SubclassDlgItem(IDC_BT_SAVE,this);
	m_btnSave.SetIcon(IDI_SAVEP,IDI_SAVEP);

	m_GridErr.SetEditable(TRUE);
	m_GridErr.SetListMode(TRUE);
	m_GridErr.SetHeaderSort(FALSE);
	m_GridErr.EnableDragAndDrop(TRUE);
	m_GridErr.SetTextBkColor(RGB(0xFF, 0xFF, 0xE0));

	m_GridErr.SetEditParseType( SES_NUMBERS | SES_SIGNED );
    m_GridErr.SetEditRange(TABLECOMPRANGE,-TABLECOMPRANGE);

	TRY 
	{
		m_GridErr.SetRowCount(3);			//m_nRows
		m_GridErr.SetColumnCount((GetDoc().GetAxisXErrCounter()>GetDoc().GetAxisYErrCounter()?
			GetDoc().GetAxisXErrCounter():GetDoc().GetAxisYErrCounter())+1);  //m_nCols
		m_GridErr.SetFixedRowCount(1);		//m_nFixRows;
		m_GridErr.SetFixedColumnCount(1);	//m_nFixCols;
	}
	CATCH (CMemoryException, e)
	{
		e->ReportError();
		e->Delete();
		return FALSE;
	}

	m_GridBET.SetEditable(TRUE);
	m_GridBET.SetListMode(TRUE);
	m_GridBET.SetHeaderSort(FALSE);
	m_GridBET.EnableDragAndDrop(TRUE);
	m_GridBET.SetTextBkColor(RGB(0xFF, 0xFF, 0xE0));

	m_GridBET.SetEditParseType( SES_NUMBERS | SES_SIGNED );
    m_GridBET.SetEditRange(350000,-15000);

	TRY 
	{
#ifdef DOUBLEBET
		m_GridBET.SetRowCount(5);			//m_nRows  双BET时候的
#else
		m_GridBET.SetRowCount(3);			//m_nRows//原来有的
#endif
		m_GridBET.SetColumnCount(19);		//m_nCols//ly change 20110122 13->19
		m_GridBET.SetFixedRowCount(1);		//m_nFixRows;
		m_GridBET.SetFixedColumnCount(1);	//m_nFixCols;

#ifdef DOUBLEBET							//20191126
		for(int number=2;number<19;number++)
		{
			m_GridBET.SetItemState(1,number,GVIS_READONLY);
			m_GridBET.SetItemState(3,number,GVIS_READONLY);
		}

		m_GridBET.SetItemBkColour(1,1,RGB(0xC0, 0xFF, 0xFF));
		m_GridBET.SetItemBkColour(3,1,RGB(0xC0, 0xFF, 0xFF));
#else
		for(int number=2;number<19;number++)
		{
			m_GridBET.SetItemState(1,number,GVIS_READONLY);
		}

		m_GridBET.SetItemBkColour(1,1,RGB(0xC0, 0xFF, 0xFF));
#endif
	}
	CATCH (CMemoryException, e)
	{
		e->ReportError();
		e->Delete();
		return FALSE;
	}

    DWORD dwTextStyle = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;
#ifndef _WIN32_WCE
    dwTextStyle |= DT_END_ELLIPSIS;
#endif

	FillGridWithText();						// fill rows/cols with text
	m_GridErr.SetRowResize(FALSE);
	m_GridErr.SetColumnResize(FALSE);	
	m_GridBET.SetRowResize(FALSE);
	m_GridBET.SetColumnResize(FALSE);	

	return 0;
}

void CPositionErrValueView::FillGridWithText()
{
    char buf[32];
	DWORD dwTextStyle = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;
 	
	for (int row = 0; row < m_GridErr.GetRowCount(); row++)
	{
		m_GridErr.SetRowHeight(row, CELLHEIDTH-5);
		
		for (int col = 0; col < m_GridErr.GetColumnCount(); col++)
		{ 
			GV_ITEM Item;
			Item.mask = GVIF_TEXT|GVIF_FORMAT;
			Item.row = row;
			Item.col = col;

			sprintf(buf,"%d",(col-m_GridErr.GetColumnCount()/2)*
				GetDoc().GetAxisXErrRange()/(GetDoc().GetAxisXErrCounter()-1)*2);
			if (row < 1)//m_nFixRows
            {
				if(col>0)
				{
				   Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE;
				   Item.szText = buf;
				}
			}
            else if (col < 1) //m_nFixCols
            {
				Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE;
				char szRead[30]={""};
				switch(row)
				{
				case 1:
					strncpy(szRead,GetLang().GetWarningText(10065),30);
					Item.szText =szRead;// "平台X轴"
					break;
				case 2:
					strncpy(szRead,GetLang().GetWarningText(10066),30);
					Item.szText = szRead;//"平台Y轴"
					break;
				}
			}
            else 
            {
				Item.nFormat = dwTextStyle;
				Item.szText = GetCurCellText(row,col);
			}

			m_GridErr.SetItem(&Item);
            m_GridErr.SetColumnWidth(col,CELLWIDTH+6);
			m_GridErr.RedrawCell(row,col);
		}
	}

	CString tempTest=GetLang().GetWarningText(10077);
	dwTextStyle = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;

	for ( row = 0; row < m_GridBET.GetRowCount(); row++)
	{
		m_GridBET.SetRowHeight(row, CELLHEIDTH-5);
		
		for (int col = 0; col < m_GridBET.GetColumnCount(); col++)
		{ 
			GV_ITEM Item;
			Item.mask = GVIF_TEXT|GVIF_FORMAT;
			Item.row = row;
			Item.col = col;

			char szRead[30]={""};
			strncpy(szRead,GetLang().GetWarningText(10076),30);
			sprintf(buf,szRead,col);//"光圈%d"
			if (row ==0)		//m_nFixRows
            {
				Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE;

				if(col==0)
					Item.szText = "";
				else
					Item.szText = buf;
			}
            else 
            {
				if (col==0)		//m_nFixCols
				{
					Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE;

					switch(row)
					{
					case 0:
						break;
					case 1:
						strncpy(szRead,GetLang().GetWarningText(10077),30);
						Item.szText = szRead;//"BET 偏移"
						break;
					case 2:
						strncpy(szRead,GetLang().GetWarningText(10078),30);
						Item.szText = szRead;//"实际光圈"
						break;
//#ifdef DOUBLEBET													//20191126
					case 3:
						//strncpy(szRead,GetLang().GetWarningText(10077),30);
						tempTest=GetLang().GetWarningText(10077);
						tempTest+=" 2";
						strncpy(szRead,tempTest,30);
						Item.szText = szRead;//"BET 偏移"
						break;
					case 4:
						//strncpy(szRead,GetLang().GetWarningText(10078),30);
						tempTest=GetLang().GetWarningText(10078);
						tempTest+=" 2";
						strncpy(szRead,tempTest,30);
						Item.szText = szRead;//"实际光圈"
						break;
//#endif
					}					
				}
				else
				{
					Item.nFormat = dwTextStyle;
					Item.szText = GetBETOffsetText(row,col);
				}
			}
 
			m_GridBET.SetItem(&Item);

			if(col==0)
			     m_GridBET.SetColumnWidth(col,CELLWIDTH+16);
			else
				m_GridBET.SetColumnWidth(col,CELLWIDTH-8);

			m_GridBET.RedrawCell(row,col);		
		}
	}
}

CString CPositionErrValueView::GetCurCellText(UINT nRow, UINT nCol)
{
    ASSERT(nRow>0&&nCol>0);

	CString str;
	switch(nRow)
	{
	case 1:  //Axis X
		str.Format("%.0f",GetDoc().GetAxisXErr(nCol-1));
		break;
	case 2:	//Axis Y
		str.Format("%.0f",GetDoc().GetAxisYErr(nCol-1));
		break;
	}
	return str;

}

CString CPositionErrValueView::GetBETOffsetText(UINT nRow, UINT nCol)
{
   ASSERT(nRow>0&&nCol>0);

	CString str;
	switch(nRow)
	{
	case 1: 
		str.Format("%d",GetDoc().GetBETOffset(nCol-1));
		break;
	case 2: 
		str.Format("%d",GetDoc().GetFactualAperture(nCol));
		break;
//#ifdef DOUBLEBET								//20191126
	case 3: 
		str.Format("%d",GetDoc().GetBETOffset2(nCol-1));
		break;
	case 4: 
		str.Format("%d",GetDoc().GetFactualAperture2(nCol));
		break;
//#endif
	}

	return str;
}

void CPositionErrValueView::OnSave() 
{
//	if(!m_SysPosition)
//	{
//		m_SysPosition = true;

		OnSet();
//		GetDoc().ReleaseSysDoc();
		GetDoc().SaveMotionParam();
		Delay(200);
		AfxMessageBox("参数已设定并保存！");

#ifdef USELOG
		GetLog().Append_pro(10050,20050);//"保存","误差补偿参数"
#endif 
//		m_SysPosition = false;
//	}
}

void CPositionErrValueView::OnSet() 
{
	if(!m_SysPosition)
	{
		m_SysPosition = true;
		
		UpdateData();
		
		for (int col = 1; col < m_GridErr.GetColumnCount(); col++)
		{
			CString strCol = m_GridErr.GetItemText(0,col);
			long lPos  = atol(strCol);
			
			for (int row = 1; row < m_GridErr.GetRowCount(); row++)
			{ 
				CString strRow = m_GridErr.GetItemText(row,col);
				double dbErr = atol(strRow);

				switch(row)
				{
				case 1:
					GetDoc().SetAxisXErr(col-1,PosErr(lPos,dbErr));
					break;
				case 2:
					GetDoc().SetAxisYErr(col-1,PosErr(lPos,dbErr));
					break;
				}
			}
		}
		
		for ( col = 1; col < m_GridBET.GetColumnCount(); col++)
		{			
			for (int row = 1; row < m_GridBET.GetRowCount(); row++)
			{ 
				CString strRow = m_GridBET.GetItemText(row,col);
				long lValue  = atol(strRow);

				if((row==1)||(row==3))							//20191126 增加
				{
					strRow = m_GridBET.GetItemText(row,1);
					lValue  = atol(strRow);

					if(lValue!=atol(GetBETOffsetText(row,1)))
						GetDoc().SetAutoGalvoAdjustIsTimed(true);
				}

				if(lValue<0||lValue>GetDoc().GetBETMAX())
				{
					CString msg;
					msg.Format("BET offset:0-%d",GetDoc().GetBETMAX());
					AfxMessageBox(msg);
					m_SysPosition = false;
					return;
				}
				
				switch(row)
				{
				case 1:
					GetDoc().SetBETOffset(col-1,lValue);
					break;
				case 2:
					GetDoc().SetFactualAperture(col-1,lValue);
					break;
				case 3:
					GetDoc().SetBETOffset2(col-1,lValue);
					break;
				case 4:
					GetDoc().SetFactualAperture2(col-1,lValue);
					break;
				}
			}
		}

		FillGridWithText();										//20191126 增加
		
#ifdef USELOG
		GetLog().Append_pro(10049,20050);//"设定","误差补偿参数"
#endif
		m_SysPosition = false;
	}
}

void CPositionErrValueView::OnReset() 
{
	if(!m_SysPosition)
	{
		m_SysPosition = true;
		FillGridWithText();
		Invalidate();

#ifdef USELOG
		GetLog().Append_pro(10051,20050);//"恢复","误差补偿参数"
#endif 
		m_SysPosition = false;
	}
}

void CPositionErrValueView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
    if(bActivate)
	{
		int nLevel = GetDoc().GetCurUserLevel();
		if(nLevel==SystemDoc::PRIMARY)//初级
		{
			GetDlgItem(IDC_MationDelay)->EnableWindow(FALSE);
			GetDlgItem(IDC_MationTime)->EnableWindow(FALSE);
			GetDlgItem(IDC_RADIOChooseX)->EnableWindow(FALSE);
			GetDlgItem(IDC_RADIOChooseY)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON9)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTONpause)->EnableWindow(FALSE);
			
			m_GridErr.SetEditable(FALSE);
			m_GridErr.SetTextBkColor(RGB(214,211,206));	
			
			m_GridBET.SetEditable(FALSE);
			m_GridBET.SetTextBkColor(RGB(214,211,206));
			
			
			m_btnSet.EnableWindow(FALSE);
			m_btnSave.EnableWindow(FALSE);
			m_btnReset.EnableWindow(FALSE);
		}
		else if(nLevel==SystemDoc::SUPEROR)//高级
		{
			GetDlgItem(IDC_MationDelay)->EnableWindow(TRUE);
			GetDlgItem(IDC_MationTime)->EnableWindow(TRUE);
			GetDlgItem(IDC_RADIOChooseX)->EnableWindow(TRUE);
			GetDlgItem(IDC_RADIOChooseY)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON9)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTONpause)->EnableWindow(TRUE);
			
			m_GridErr.SetEditable(TRUE);
			m_GridErr.SetTextBkColor(RGB(255,255,255));
			
			m_GridBET.SetEditable(TRUE);
			m_GridBET.SetTextBkColor(RGB(255,255,255));	
			
			m_btnSet.EnableWindow(FALSE);
			m_btnSave.EnableWindow(FALSE);
			m_btnReset.EnableWindow(FALSE);
		}
	    else //系统
		{
			GetDlgItem(IDC_MationDelay)->EnableWindow(TRUE);
			GetDlgItem(IDC_MationTime)->EnableWindow(TRUE);
			GetDlgItem(IDC_RADIOChooseX)->EnableWindow(TRUE);
			GetDlgItem(IDC_RADIOChooseY)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON9)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTONpause)->EnableWindow(TRUE);
			
			m_GridErr.SetEditable(TRUE);
			m_GridErr.SetTextBkColor(RGB(255,255,255));	
			m_GridBET.SetEditable(TRUE);
			m_GridBET.SetTextBkColor(RGB(255,255,255));	
			
			m_btnSet.EnableWindow(TRUE);
			m_btnSave.EnableWindow(TRUE);
			m_btnReset.EnableWindow(TRUE);
		}
	}

	GetDlgItem(IDC_MationStar)->EnableWindow(FALSE);
	GetDlgItem(IDC_MationEnd)->EnableWindow(FALSE);
	FillGridWithText();

	UpdateData(FALSE);

	TVisualFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CPositionErrValueView::OnMationRun() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	char szRead[20] = {""};//ly add 20110323
	char ez[256]={""};
	strncpy(ez,GetLang().GetWarningText(31029),256);
	int nSel = AfxMessageBox(ez,MB_YESNO);//"干涉仪测试  开始操作  '是'\n取消操作 选择  '取消'\n"	
	if(nSel == IDYES)
	{
		if(!GetDoc().GetMotorState())
		{
			strncpy(ez,GetLang().GetWarningText(21001),256);
			AfxMessageBox(ez);//"机器未整体回零，不允许相关操作!"
			return;
		}
		long MatoinPos;
		BOOL Matoinfirst = true;
		MatoinPos = m_mationstar;
		for(int i=0;i<m_MationTime;i++)
		{
			if(m_chooseXY == 0)
			{
				if(Matoinfirst)
				{
					while(MatoinPos!=m_mationend)
					{
						if(!m_mationpuls)
						{
							strncpy(ez,GetLang().GetWarningText(31030),256);
							int nSel1 = AfxMessageBox(ez,MB_YESNO);//"暂停或停止  暂停  '是'\n停止  '取消'\n"	
							if(nSel1 == IDYES)
							{
								strncpy(ez,GetLang().GetWarningText(31031),256);
								AfxMessageBox(ez);//"暂停结束"
								m_mationpuls = true;
								strncpy(szRead ,GetLang().GetWarningText(10014),20);
								m_mationpause.SetWindowText(szRead);//"暂停"
							}
							else
							{
								return;
							}
						}
						GetControl().MoveTo(AXISTABX,MatoinPos);
						GetControl().WaitAxisStop(AXISTABX);
						if(m_mationstar<m_mationend)
						{	
							MatoinPos += GetDoc().GetAxisXErrnInterval();
						}
						else
						{
							MatoinPos -= GetDoc().GetAxisXErrnInterval();
						}
						Delay(m_mationdelay*1000);
					}
					if(!m_mationpuls)
					{
						strncpy(ez,GetLang().GetWarningText(31030),256);
						int nSel1 = AfxMessageBox(ez,MB_YESNO);//"暂停或停止  暂停  '是'\n停止  '取消'\n"	
						if(nSel1 == IDYES)
						{
							strncpy(ez,GetLang().GetWarningText(31031),256);
							AfxMessageBox(ez);//"暂停结束"
							m_mationpuls = true;
							strncpy(szRead ,GetLang().GetWarningText(10014),20);
							m_mationpause.SetWindowText(szRead);//"暂停"
						}
						else
						{
							return;
						}
					}
					GetControl().MoveTo(AXISTABX,MatoinPos);
					GetControl().WaitAxisStop(AXISTABX);
					Delay(m_mationdelay*1000);//走到终点位
					//ly add 20110310
					if(!m_mationpuls)
					{
						strncpy(ez,GetLang().GetWarningText(31030),256);
						int nSel1 = AfxMessageBox(ez,MB_YESNO);//"暂停或停止  暂停  '是'\n停止  '取消'\n"	
						if(nSel1 == IDYES)
						{
							strncpy(ez,GetLang().GetWarningText(31031),256);
							AfxMessageBox(ez);//"暂停结束"
							m_mationpuls = true;
							strncpy(szRead ,GetLang().GetWarningText(10014),20);
							m_mationpause.SetWindowText(szRead);//"暂停"
						}
						else
						{
							return;
						}
					}
					//越程===================
					//    *-----------*--^
					// ^--*-----------*--^//一个往返
					// ^--*-----------*--^
					//    *-----------*--^//两个往返，起点终点各采集4次
					//---ly add 20110310 现在要越程为5mm,去向永远有越程.
					if(m_mationstar<m_mationend)
					{	
						MatoinPos += 5000;
					}
					else
					{
						MatoinPos -= 5000;
					}
					GetControl().MoveTo(AXISTABX,MatoinPos);
					GetControl().WaitAxisStop(AXISTABX);
					Delay(m_mationdelay*1000);
					//---ly add 20110310 现在要越程为5mm返回到终点位置
					if(m_mationstar<m_mationend)
					{	
						MatoinPos -= 5000;
					}
					else
					{
						MatoinPos += 5000;
					}
					//----ly add 20110310
					Matoinfirst = false;
				}
				if(!Matoinfirst)//开始从越程处返程，当前在越程位
				{
					while(MatoinPos!=m_mationstar)
					{
						if(!m_mationpuls)
						{
							strncpy(ez,GetLang().GetWarningText(31030),256);
							int nSel1 = AfxMessageBox(ez,MB_YESNO);//"暂停或停止  暂停  '是'\n停止  '取消'\n"	
							if(nSel1 == IDYES)
							{
								strncpy(ez,GetLang().GetWarningText(31031),256);
								AfxMessageBox(ez);//"暂停结束"
								m_mationpuls = true;
								strncpy(szRead ,GetLang().GetWarningText(10014),20);
								m_mationpause.SetWindowText(szRead);//"暂停"
							}
							else
							{
								return;
							}
						}
						GetControl().MoveTo(AXISTABX,MatoinPos);//当前位置设为终点位
						GetControl().WaitAxisStop(AXISTABX);
						if(m_mationstar<m_mationend)
						{	
							MatoinPos -= GetDoc().GetAxisXErrnInterval();
						}
						else
						{
							MatoinPos += GetDoc().GetAxisXErrnInterval();
						}
						Delay(m_mationdelay*1000);
					}
					if(!m_mationpuls)
					{
						strncpy(ez,GetLang().GetWarningText(31030),256);
						int nSel1 = AfxMessageBox(ez,MB_YESNO);//"暂停或停止  暂停  '是'\n停止  '取消'\n"	
						if(nSel1 == IDYES)
						{
							strncpy(ez,GetLang().GetWarningText(31031),256);
							AfxMessageBox(ez);//"暂停结束"
							m_mationpuls = true;
							strncpy(szRead ,GetLang().GetWarningText(10014),20);
							m_mationpause.SetWindowText(szRead);//"暂停"
						}
						else
						{
							return;
						}
					}
					GetControl().MoveTo(AXISTABX,MatoinPos);//到起点位
					GetControl().WaitAxisStop(AXISTABX);
					Delay(m_mationdelay*1000);
					if(i<(m_MationTime-1))//如果不是最后一个返程则做越程动作,ly add 20110310
					{
						if(!m_mationpuls)
						{
							strncpy(ez,GetLang().GetWarningText(31030),256);
							int nSel1 = AfxMessageBox(ez,MB_YESNO);//"暂停或停止  暂停  '是'\n停止  '取消'\n"	
							if(nSel1 == IDYES)
							{
								strncpy(ez,GetLang().GetWarningText(31031),256);
								AfxMessageBox(ez);//"暂停结束"
								m_mationpuls = true;
								strncpy(szRead ,GetLang().GetWarningText(10014),20);
								m_mationpause.SetWindowText(szRead);//"暂停"
							}
							else
							{
								return;
							}
						}
						if(m_mationstar<m_mationend)
						{	
							MatoinPos -= 5000;
						}
						else
						{
							MatoinPos += 5000;
						}
						GetControl().MoveTo(AXISTABX,MatoinPos);//到越程位
						GetControl().WaitAxisStop(AXISTABX);
						Delay(m_mationdelay*1000);
						//---ly add 20110310 现在要越程为5mm返回到起点位置
						if(m_mationstar<m_mationend)
						{	
							MatoinPos += 5000;
						}
						else
						{
							MatoinPos -= 5000;
						}
					}
					Matoinfirst = true;					
				}
			}
			else if(m_chooseXY == 1)
			{
				if(Matoinfirst)
				{
					while(MatoinPos!=m_mationend)
					{
						if(!m_mationpuls)
						{
							strncpy(ez,GetLang().GetWarningText(31030),256);
							int nSel1 = AfxMessageBox(ez,MB_YESNO);//"暂停或停止  暂停  '是'\n停止  '取消'\n"	
							if(nSel1 == IDYES)
							{
								strncpy(ez,GetLang().GetWarningText(31031),256);
								AfxMessageBox(ez);//"暂停结束"
								m_mationpuls = true;
								strncpy(szRead ,GetLang().GetWarningText(10014),20);
								m_mationpause.SetWindowText(szRead);//"暂停"
							}
							else
							{
								return;
							}
						}
						GetControl().MoveTo(AXISTABY,MatoinPos);
						GetControl().WaitAxisStop(AXISTABY);
						if(m_mationstar<m_mationend)
						{	
							MatoinPos += GetDoc().GetAxisYErrnInterval();
						}
						else
						{
							MatoinPos -= GetDoc().GetAxisYErrnInterval();
						}
						Delay(m_mationdelay*1000);
					}
					if(!m_mationpuls)
					{
						strncpy(ez,GetLang().GetWarningText(31030),256);
						int nSel1 = AfxMessageBox(ez,MB_YESNO);//"暂停或停止  暂停  '是'\n停止  '取消'\n"	
						if(nSel1 == IDYES)
						{
							strncpy(ez,GetLang().GetWarningText(31031),256);
							AfxMessageBox(ez);//"暂停结束"
							m_mationpuls = true;
							strncpy(szRead ,GetLang().GetWarningText(10014),20);
							m_mationpause.SetWindowText(szRead);//"暂停"
						}
						else
						{
							return;
						}
					}
					GetControl().MoveTo(AXISTABY,MatoinPos);
					GetControl().WaitAxisStop(AXISTABY);
					Delay(m_mationdelay*1000);
					//ly add 20110310
					if(!m_mationpuls)
					{
						strncpy(ez,GetLang().GetWarningText(31030),256);
						int nSel1 = AfxMessageBox(ez,MB_YESNO);//"暂停或停止  暂停  '是'\n停止  '取消'\n"	
						if(nSel1 == IDYES)
						{
							strncpy(ez,GetLang().GetWarningText(31031),256);
							AfxMessageBox(ez);//"暂停结束"
							m_mationpuls = true;
							strncpy(szRead ,GetLang().GetWarningText(10014),20);
							m_mationpause.SetWindowText(szRead);//"暂停"
						}
						else
						{
							return;
						}
					}
					//越程===================
					//    *-----------*--^
					// ^--*-----------*--^//一个往返
					// ^--*-----------*--^
					//    *-----------*--^//两个往返，起点终点各采集4次
					//---ly add 20110310 现在要越程为5mm,去向永远有越程.
					if(m_mationstar<m_mationend)
					{	
						MatoinPos += 5000;
					}
					else
					{
						MatoinPos -= 5000;
					}

					GetControl().MoveTo(AXISTABY,MatoinPos);
					GetControl().WaitAxisStop(AXISTABY);
					Delay(m_mationdelay*1000);
					//---ly add 20110310 现在要越程为5mm返回到终点位置
					if(m_mationstar<m_mationend)
					{	
						MatoinPos -= 5000;
					}
					else
					{
						MatoinPos += 5000;
					}
					//----ly add 20110310
					Matoinfirst = false;
				}
				if(!Matoinfirst)//开始从越程处返程，当前在越程位
				{
					while(MatoinPos!=m_mationstar)
					{
						if(!m_mationpuls)
						{
							strncpy(ez,GetLang().GetWarningText(31030),256);
							int nSel1 = AfxMessageBox(ez,MB_YESNO);//"暂停或停止  暂停  '是'\n停止  '取消'\n"	
							if(nSel1 == IDYES)
							{
								strncpy(ez,GetLang().GetWarningText(31031),256);
								AfxMessageBox(ez);//"暂停结束"
								m_mationpuls = true;
								strncpy(szRead ,GetLang().GetWarningText(10014),20);
								m_mationpause.SetWindowText(szRead);//"暂停"
							}
							else
							{
								return;
							}
						}
						GetControl().MoveTo(AXISTABY,MatoinPos);
						GetControl().WaitAxisStop(AXISTABY);
						if(m_mationstar<m_mationend)
						{	
							MatoinPos -= GetDoc().GetAxisYErrnInterval();
						}
						else
						{
							MatoinPos += GetDoc().GetAxisYErrnInterval();
						}
						Delay(m_mationdelay*1000);
					}
					if(!m_mationpuls)
					{
						strncpy(ez,GetLang().GetWarningText(31030),256);
						int nSel1 = AfxMessageBox(ez,MB_YESNO);//"暂停或停止  暂停  '是'\n停止  '取消'\n"	
						if(nSel1 == IDYES)
						{
							strncpy(ez,GetLang().GetWarningText(31031),256);
							AfxMessageBox(ez);//"暂停结束"
							m_mationpuls = true;
							strncpy(szRead ,GetLang().GetWarningText(10014),20);
							m_mationpause.SetWindowText(szRead);//"暂停"
						}
						else
						{
							return;
						}
					}
					GetControl().MoveTo(AXISTABY,MatoinPos);
					GetControl().WaitAxisStop(AXISTABY);
					Delay(m_mationdelay*1000);
					//ly add 20110310
					if(i<(m_MationTime-1))//如果不是最后一个返程则做越程动作,ly add 20110310
					{
						if(!m_mationpuls)
						{
							strncpy(ez,GetLang().GetWarningText(31030),256);
							int nSel1 = AfxMessageBox(ez,MB_YESNO);//"暂停或停止  暂停  '是'\n停止  '取消'\n"	
							if(nSel1 == IDYES)
							{
								strncpy(ez,GetLang().GetWarningText(31031),256);
								AfxMessageBox(ez);//"暂停结束"
								m_mationpuls = true;
								strncpy(szRead ,GetLang().GetWarningText(10014),20);
								m_mationpause.SetWindowText(szRead);//"暂停"
							}
							else
							{
								return;
							}
						}
						if(m_mationstar<m_mationend)
						{	
							MatoinPos -= 5000;
						}
						else
						{
							MatoinPos += 5000;
						}
						GetControl().MoveTo(AXISTABY,MatoinPos);
						GetControl().WaitAxisStop(AXISTABY);
						Delay(m_mationdelay*1000);
						//---ly add 20110310 现在要越程为5mm返回到起点位置
						if(m_mationstar<m_mationend)
						{	
							MatoinPos += 5000;
						}
						else
						{
							MatoinPos -= 5000;
						}					
					}
					Matoinfirst = true;
				}
			}
		}
	}
}

void CPositionErrValueView::OnMoveStar() 
{
	UpdateData();
	char ez[256]={""};//ly 20110404
	strncpy(ez,GetLang().GetWarningText(21064),256);
	int nSel = AfxMessageBox(ez,MB_YESNO);	//"运动到起点位置  开始操作  '是'\n取消操作 选择  '取消'\n"
	if(nSel == IDYES)
	{
		if(!GetDoc().GetMotorState())
		{
			strncpy(ez,GetLang().GetWarningText(21001),256);
			AfxMessageBox(ez);//"机器未整体回零，不允许相关操作!"
			return;
		}
		if(m_chooseXY == 0)
		{
			GetControl().MoveTo(AXISTABX,m_mationstar);
			GetControl().WaitAxisStop(AXISTABX);

		}
		else if(m_chooseXY == 1)
		{
			GetControl().MoveTo(AXISTABY,m_mationstar);
			GetControl().WaitAxisStop(AXISTABY);
		}	
	}
}

void CPositionErrValueView::OnPusl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
}

void CPositionErrValueView::OnButtonPusle() 
{
	char szRead[20] = {""};
	if(m_mationpuls)
	{
		m_mationpuls = false;
		strncpy(szRead ,GetLang().GetWarningText(10013),20);
		m_mationpause.SetWindowText(szRead);//"继续"
	}
	else
	{
		m_mationpuls = true;
		strncpy(szRead ,GetLang().GetWarningText(10014),20);
		m_mationpause.SetWindowText(szRead);//"暂停"
	}
}

void CPositionErrValueView::OnBUTTONpause() 
{
	char szRead[20] = {""};
	if(m_mationpuls)
	{
		m_mationpuls = false;
		strncpy(szRead ,GetLang().GetWarningText(10013),20);
		m_mationpause.SetWindowText(szRead);//"继续"
		
		double xxx,xx;
		xxx = m_GridErr.GetColumnCount();
		
		xxx =	GetDoc().GetAxisYErrnInterval();
		xx =	GetDoc().GetAxisXErrnInterval();
		//		GetWindowText(
	}
	else
	{
		m_mationpuls = true;
		strncpy(szRead ,GetLang().GetWarningText(10014),20);
		m_mationpause.SetWindowText(szRead);//"暂停"
	}
}

void CPositionErrValueView::OnRADIOChooseX() 
{
	m_chooseXY = 0;
	m_mationend = GetDoc().GetAxisXErrEnd();//-330000;//ly change 20110212      0->-330000 默认X轴
	m_mationstar = GetDoc().GetAxisXErrStart();// 330000;//ly change 20110212
	UpdateData(FALSE);
}

void CPositionErrValueView::OnRADIOChooseY() 
{
	m_chooseXY = 1;
	m_mationend = GetDoc().GetAxisYErrEnd();// -480000;//ly change 20110212      0->-330000 默认X轴
	m_mationstar = GetDoc().GetAxisYErrStart();//450000;//ly change 20110212
	UpdateData(FALSE);

}

void CPositionErrValueView::SetUI()//ly add 20110318
{
	char szRead[20] = {""};
	GetLang().GetUIText("PositionErrValue","IDC_STATIC1",szRead,20);
	SetDlgItemText(IDC_STATIC1,szRead);
	GetLang().GetUIText("PositionErrValue","IDC_STATIC2",szRead,20);
	SetDlgItemText(IDC_STATIC2,szRead);
	GetLang().GetUIText("PositionErrValue","IDC_STATIC3",szRead,20);
	SetDlgItemText(IDC_STATIC3,szRead);
	GetLang().GetUIText("PositionErrValue","IDC_STATIC4",szRead,20);
	SetDlgItemText(IDC_STATIC4,szRead);
	GetLang().GetUIText("PositionErrValue","IDC_STATIC5",szRead,20);
	SetDlgItemText(IDC_STATIC5,szRead);
	GetLang().GetUIText("PositionErrValue","IDC_STATIC6",szRead,20);
	SetDlgItemText(IDC_STATIC6,szRead);
	GetLang().GetUIText("PositionErrValue","IDC_STATIC7",szRead,20);//ly add 20110420 光束倍率
	SetDlgItemText(IDC_STATIC7,szRead);
	GetLang().GetUIText("PositionErrValue","IDC_RADIOChooseX",szRead,20);
	SetDlgItemText(IDC_RADIOChooseX,szRead);
	GetLang().GetUIText("PositionErrValue","IDC_RADIOChooseY",szRead,20);
	SetDlgItemText(IDC_RADIOChooseY,szRead);
	GetLang().GetUIText("PositionErrValue","IDC_BUTTON9",szRead,20);
	SetDlgItemText(IDC_BUTTON9,szRead);
	GetLang().GetUIText("PositionErrValue","IDC_BUTTON1",szRead,20);
	SetDlgItemText(IDC_BUTTON1,szRead);
	GetLang().GetUIText("PositionErrValue","IDC_BUTTONpause",szRead,20);
	SetDlgItemText(IDC_BUTTONpause,szRead);
	GetLang().GetUIText("PositionErrValue","IDC_BT_RESET",szRead,20);
	SetDlgItemText(IDC_BT_RESET,szRead);
	GetLang().GetUIText("PositionErrValue","IDC_BT_SET",szRead,20);
	SetDlgItemText(IDC_BT_SET,szRead);
	GetLang().GetUIText("PositionErrValue","IDC_BT_SAVE",szRead,20);
	SetDlgItemText(IDC_BT_SAVE,szRead);
}

void CPositionErrValueView::OnInitialUpdate() 
{
	TVisualFormView::OnInitialUpdate();

	if(GetLang().GetCurLanguage()==1)
		SetUI();

	// TODO: Add your specialized code here and/or call the base class	
}

