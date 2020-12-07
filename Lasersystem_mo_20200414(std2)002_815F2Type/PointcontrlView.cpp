// PointcontrlView.cpp : implementation file
//

#include "stdafx.h"
#include "lasersystem.h"
#include "PointcontrlView.h"
#include "Excellon.h"
#include "FilePointView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPointcontrlView

IMPLEMENT_DYNCREATE(CPointcontrlView, TVisualFormView)

CSortListCtrl	CPointcontrlView::m_tInfor;
CDWordArray CPointcontrlView::ColorToolPoint;

COLORREF  CPointcontrlView::ColorToolFid;
COLORREF  CPointcontrlView::ColorToolTxt;
COLORREF  CPointcontrlView::ColorToolRect;

CPointcontrlView::CPointcontrlView()
	: TVisualFormView(CPointcontrlView::IDD)
{
	//{{AFX_DATA_INIT(CPointcontrlView)
	//}}AFX_DATA_INIT
}

CPointcontrlView::~CPointcontrlView()
{

}

CPointcontrlView& GetPointcontrlView()
{
	static CPointcontrlView PoContrl;
	return PoContrl;
}

void CPointcontrlView::DoDataExchange(CDataExchange* pDX)
{
	TVisualFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPointcontrlView)
	DDX_Control(pDX, IDC_BTN_TOOLCOLOR, m_btnToolColor);
	DDX_Control(pDX, IDC_BT_ZOOMFRAME, m_cBtZoomFrame);
	DDX_Control(pDX, IDC_BT_ZOOMRESET, m_cBtZoomReset);
	DDX_Control(pDX, IDC_BT_ZOOMOUT, m_cBtZoomOut);
	DDX_Control(pDX, IDC_BT_ZOOMIN, m_cBtZoomIn);
	DDX_Control(pDX, IDC_CB_COLORSEL, m_ColorSel);
	DDX_Control(pDX, IDC_LST_TOOL, m_tInfor);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPointcontrlView, CFormView)
	//{{AFX_MSG_MAP(CPointcontrlView)
	ON_BN_CLICKED(IDC_BT_ZOOMIN, OnBtZoomin)
	ON_BN_CLICKED(IDC_BT_ZOOMOUT, OnBtZoomout)
	ON_BN_CLICKED(IDC_BT_ZOOMRESET, OnBtZoomreset)
	ON_BN_CLICKED(IDC_BT_ZOOMFRAME, OnBtZoomframe)
	ON_BN_CLICKED(IDC_CHECK_PATHSHOW, OnBtPathShow)	//jpc add 20120429
	ON_WM_CHAR()
	ON_REGISTERED_MESSAGE(WM_XLISTCTRL_COMBO_SELECTION, OnComboSelection)
	ON_NOTIFY(NM_CLICK, IDC_LST_TOOL, OnClickLstTool)
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDC_BTN_TOOLCOLOR, OnBtnToolcolor)
	ON_BN_CLICKED(IDC_BTN_COLORSAVE, OnBtColorSave)
	//}}AFX_MSG_MAP
	END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPointcontrlView diagnostics

#ifdef _DEBUG
void CPointcontrlView::AssertValid() const
{
	TVisualFormView::AssertValid();
}

void CPointcontrlView::Dump(CDumpContext& dc) const
{
	TVisualFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPointcontrlView message handlers
void CPointcontrlView::SetUI()//ly add 20110318
{
	char szRead[20] = {""};
	GetLang().GetUIText("Pointcontrl","IDC_BT_ZOOMIN",szRead,20);
	SetDlgItemText(IDC_BT_ZOOMIN,szRead);
	GetLang().GetUIText("Pointcontrl","IDC_BT_ZOOMOUT",szRead,20);
	SetDlgItemText(IDC_BT_ZOOMOUT,szRead);
	GetLang().GetUIText("Pointcontrl","IDC_BT_ZOOMFRAME",szRead,20);
	SetDlgItemText(IDC_BT_ZOOMFRAME,szRead);
	GetLang().GetUIText("Pointcontrl","IDC_BT_ZOOMRESET",szRead,20);
	SetDlgItemText(IDC_BT_ZOOMRESET,szRead);
	GetLang().GetUIText("Pointcontrl","IDC_CHECK_PATHSHOW",szRead,20);//ly add 20120523
	SetDlgItemText(IDC_CHECK_PATHSHOW,szRead);
}

void CPointcontrlView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	if(GetLang().GetCurLanguage()==1)
		SetUI();

	m_cBtZoomFrame.SetIcon(IDI_ZOOMINM,IDI_ZOOMINM);

	m_cBtZoomReset.SetIcon(IDI_ZOOMNONE,IDI_ZOOMNONE);

	m_cBtZoomOut.SetIcon(IDI_ZOOMOUT,IDI_ZOOMOUT);

	m_cBtZoomIn.SetIcon(IDI_ZOOMIN,IDI_ZOOMIN);	
	m_ColorSel.InitBSColorCB();
	m_ColorSel.SetCurSel(0);

	m_tInfor.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	char szRead[50]={""};
	strncpy(szRead ,GetLang().GetWarningText(10041),50);
	m_tInfor.SetHeadings(szRead);//"刀号,60;刀径,60;颜色,60"
}

void CPointcontrlView::LoadToolColorFormFile()
{
	FILE* fp;
	char buf[32];
	CString	pathname=GetDoc().GetAppPath()+"param\\toolColor.txt";

	if( (fp=fopen(pathname,"r+"))==NULL)
		return ;

	fscanf(fp,"%s",buf);
	COLORREF curcorlor = atol(buf);

	ColorToolPoint.RemoveAll();
	while(!feof(fp))
	{
		fscanf(fp,"%s",buf);
		ColorToolPoint.Add(curcorlor);
		curcorlor = atol(buf);
	}

	fclose( fp );
}

void CPointcontrlView::SaveAssisCrInfo()
{
	CIniFile IniFile;
	CString str,path;

	path=AfxGetApp()->m_pszHelpFilePath;
	str=AfxGetApp()->m_pszExeName;
	path=path.Left(path.ReverseFind('.')-str.GetLength());
	IniFile.SetName("param\\TAssisColo");
	IniFile.SetPath(path);

	BOOL bExist=IniFile.OpenIniFileForWrite();
	if(bExist)
	{
		IniFile.WriteSection("TassistantColor");
		IniFile.WriteItemInt("ColorToolFid",ColorToolFid);
		IniFile.WriteItemInt("ColorToolRect",ColorToolRect);
		IniFile.WriteItemInt("ColorToolTxt",ColorToolTxt);

		IniFile.CloseIniFile();
	}
	else
	{
		char ez[256]={""};
		strncpy(ez,GetLang().GetWarningText(21062),256);
		MessageBox(ez);//"存储刀具辅助信息颜色出错！"
	}
}

void CPointcontrlView::LoadAssisCrInfo()
{
	CIniFile IniFile;
	CString str,path;

	path=AfxGetApp()->m_pszHelpFilePath;
	str=AfxGetApp()->m_pszExeName;
	path=path.Left(path.ReverseFind('.')-str.GetLength());
	IniFile.SetName("param\\TAssisColo");
	IniFile.SetPath(path);

	BOOL bExist=IniFile.OpenIniFileForRead();
	if(bExist)
	{
		long TempCr;
		
		if(!IniFile.GetItemInt("TassistantColor","ColorToolFid", TempCr))
			ColorToolFid = 255;
		else
			ColorToolFid = TempCr;
		
		if(!IniFile.GetItemInt("TassistantColor","ColorToolTxt",TempCr))
			ColorToolTxt = 255;	
		else
			ColorToolTxt = TempCr;
		
		if(!IniFile.GetItemInt("TassistantColor","ColorToolRect", TempCr))
			ColorToolRect = 255;
		else
			ColorToolRect= TempCr;
		
		IniFile.CloseIniFile();			
	}	
}

void CPointcontrlView::SaveToolColorToFile()
{
	FILE* fp;
	char buf[32];
	COLORREF  tc;
	CString	pathname=GetDoc().GetAppPath()+"param\\toolColor.txt";

	if( (fp=fopen(pathname,"w+"))==NULL)
		return ;
	
	for(int i = 0;i<ColorToolPoint.GetSize();i++)
	{
		tc = ColorToolPoint.GetAt(i);
		fprintf(fp,"%d\n",tc);
	}
	
	fclose( fp );
}

void CPointcontrlView::LoadToolInfor()
{
	CRect rect;
	char ToolIndex[8],ToolXBuf[16];
	ToolInfo ti;
	int i = 0;
	int ToolsNum = GetExcellonData().GetToolsNum();

	m_tInfor.DeleteAllItems();
	LoadAssisCrInfo();
	LoadToolColorFormFile();
	ColorToolPoint.SetSize(ToolsNum);

	for(i; i<ToolsNum;++i)
	{
		ti = GetExcellonData().GetToolInfo(i);
		sprintf(ToolIndex,"T0%d",ti.m_nToolIndex);
		sprintf(ToolXBuf,"D%4.1f",ti.m_nToolX);
		m_tInfor.AddItem(ToolIndex,ToolXBuf,_T(" "));
		m_tInfor.SetItemColor(i,2,ColorToolPoint.GetAt(i),ColorToolPoint.GetAt(i));
	}

	if(GetLang().GetCurLanguage()==0)
	{
		m_tInfor.AddItem("标靶颜色",_T(" "),_T(" "));
		m_tInfor.SetItemColor(i,2,ColorToolFid,ColorToolFid);
		++i;
		m_tInfor.AddItem("框格颜色",_T(" "),_T(" "));
		m_tInfor.SetItemColor(i,2,ColorToolRect,ColorToolRect);
		++i;
		m_tInfor.AddItem("字符颜色",_T(" "),_T(" "));
		m_tInfor.SetItemColor(i,2,ColorToolTxt,ColorToolTxt);
	}
	else if(GetLang().GetCurLanguage()==1)
	{
		m_tInfor.AddItem("Target Color",_T(" "),_T(" "));
		m_tInfor.SetItemColor(i,2,ColorToolFid,ColorToolFid);
		++i;
		m_tInfor.AddItem("Grid Color",_T(" "),_T(" "));
		m_tInfor.SetItemColor(i,2,ColorToolRect,ColorToolRect);
		++i;
		m_tInfor.AddItem("Text Color",_T(" "),_T(" "));
		m_tInfor.SetItemColor(i,2,ColorToolTxt,ColorToolTxt);
	}
}

LRESULT CPointcontrlView::OnComboSelection(WPARAM cr, LPARAM lParam)
{
	if((m_TempiIten >m_tInfor.GetItemCount())||(m_TempiIten<0))
	{	
		char ez[256]={""};
		strncpy(ez,GetLang().GetWarningText(21063),256);
		MessageBox(ez);//"设置颜色失败，请注意选择刀具"
		return 0;
	}

//	int a= m_tInfor.GetItemCount();

	if(m_TempiIten == m_tInfor.GetItemCount()-1)
		ColorToolTxt=cr;
	
	if(m_TempiIten == m_tInfor.GetItemCount()-2)
		ColorToolRect=cr;
	
	if(m_TempiIten == m_tInfor.GetItemCount()-3)
		ColorToolFid=cr;
		
	if(m_TempiIten < m_tInfor.GetItemCount()-3)
		ColorToolPoint.SetAt(m_TempiIten,cr);
	
	m_tInfor.SetItemColor(m_TempiIten,2,cr,cr);
	
	POSITION pos = GetDocument()->GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetDocument()->GetNextView(pos);
		ASSERT(pView != NULL);
		
		if(pView->IsKindOf(RUNTIME_CLASS(CFilePointView)))
		{
			pView->PostMessage(WM_REFLASHPOINT,0,0);
			return 0;
		}
	}
	
	return 0;
}

void CPointcontrlView::OnClickLstTool(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;	 
	if(m_TempiIten != pNMListView->iItem)
	{
		m_TempiIten = pNMListView->iItem;
	}

	*pResult = 0;
}


void CPointcontrlView::OnBtZoomin() 
{
	// TODO: Add your control notification handler code here
	POSITION pos = GetDocument()->GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetDocument()->GetNextView(pos);
		ASSERT(pView != NULL);
		
		if(pView->IsKindOf(RUNTIME_CLASS(CFilePointView)))
		{
			pView->PostMessage(WM_REFLASHPOINT,1,0);
			return ;
		}
	}   
		
	return ;
}

void CPointcontrlView::OnBtZoomout() 
{
	// TODO: Add your control notification handler code here
	POSITION pos = GetDocument()->GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetDocument()->GetNextView(pos);
		ASSERT(pView != NULL);
		
		if(pView->IsKindOf(RUNTIME_CLASS(CFilePointView)))
		{
			pView->PostMessage(WM_REFLASHPOINT,2,0);
			return ;
		}
	}   
		
	return ;
}

void CPointcontrlView::OnBtZoomreset() 
{
	POSITION pos = GetDocument()->GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetDocument()->GetNextView(pos);
		ASSERT(pView != NULL);
		
		if(pView->IsKindOf(RUNTIME_CLASS(CFilePointView)))
		{
			pView->PostMessage(WM_REFLASHPOINT,3,0);

			return ;
		}
	}   
		
	return ;
}

void CPointcontrlView::OnBtZoomframe() 
{
    POSITION pos = GetDocument()->GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetDocument()->GetNextView(pos);
		ASSERT(pView != NULL);
		
		if(pView->IsKindOf(RUNTIME_CLASS(CFilePointView)))
		{
			pView->PostMessage(WM_REFLASHPOINT,4,0);
			return ;
		}
	}   
	return ;
}

void CPointcontrlView::OnBtPathShow() //jpc add 20120429------------
{
    UpdateData();
	int check=((CButton*)(GetDlgItem(IDC_CHECK_PATHSHOW)))->GetCheck();
	POSITION pos = GetDocument()->GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetDocument()->GetNextView(pos);
		ASSERT(pView != NULL);
		
		if(pView->IsKindOf(RUNTIME_CLASS(CFilePointView)))
		{
			if (check)
			{
				pView->PostMessage(WM_REFLASHPOINT,5,1);
			}
			else
			{
				pView->PostMessage(WM_REFLASHPOINT,5,0);
			}
			
			return ;
		}
	}   
	return ;
}

void CPointcontrlView::OnBtnToolcolor() 
{
	// TODO: Add your control notification handler code here
	AfxMessageBox(" ");
}

void CPointcontrlView::ToolInforClear()
{
	m_tInfor.DeleteAllItems();
}

void CPointcontrlView::OnBtColorSave() 
{
	// TODO: Add your control notification handler code here
	SaveToolColorToFile();
	SaveAssisCrInfo();
	Delay(200);
	AfxMessageBox("参数已设定并保存！");
}
