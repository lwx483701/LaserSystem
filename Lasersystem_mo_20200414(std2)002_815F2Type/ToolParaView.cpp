// ToolParaView.cpp : implementation file

#include <time.h>
#include <fstream>
#include "stdafx.h"
#include "lasersystem.h"

#include "ToolParaView.h"
#include "Excellon.h"
#include "OperateControl.h"
#include "checkerctrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolParaView

IMPLEMENT_DYNCREATE(CToolParaView, TVisualFormView)

CComboBox	CToolParaView::m_cmbToolMode;
CComboBox	CToolParaView::m_cmbToolIndex;
CComboBox	CToolParaView::m_cmbToolApt;
CComboBox	CToolParaView::m_cmbToolSubApt;
CTreeCtrlEx	CToolParaView::m_ToolParaTree;
BOOL CToolParaView::m_bDataModified;

CToolParaView::CToolParaView()	: TVisualFormView(CToolParaView::IDD)
{
	//{{AFX_DATA_INIT(CToolParaView)
	m_lLaserPeriod = 100;
	m_lLaserRelease = 5;
	m_dbToolDiameter = 0.0;
	m_strLaserWorkTime = _T("");
	m_strDataState = _T("");
	m_bTwoCycleMode = FALSE;
	m_checkPeriod = FALSE;
	m_bCircleProcMode = FALSE;
	m_lBeamDia = 150;
	m_lBeamStep = 80;
	m_sToolIndex = _T("");
	m_bDataModified=FALSE;
	m_dbStepScale = 1.2;
	//}}AFX_DATA_INIT
}

CToolParaView::~CToolParaView()
{
	
}

void CToolParaView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CToolParaView)
	DDX_Control(pDX, IDC_EDT_LASERRELEASE, m_edtLaserRelease);
	DDX_Control(pDX, IDC_EDT_LASERPERIOD, m_edtLaserPeriod);
	DDX_Text(pDX, IDC_EDT_LASERPERIOD, m_lLaserPeriod);
	DDX_Text(pDX, IDC_EDT_LASERRELEASE, m_lLaserRelease);
	DDX_Text(pDX, IDC_EDT_TOOLDIAMETER, m_dbToolDiameter);
	DDX_Control(pDX, IDC_BT_TOOLDEL, m_btnToolDel);
	DDX_Control(pDX, IDC_BT_TOOLADD, m_btnToolAdd);
	DDX_Control(pDX, IDC_BT_TOOLSAVE, m_btnToolSave);
	DDX_Control(pDX, IDC_BT_TOOLMODIFY, m_btnToolModi);
	DDX_Text(pDX, IDC_STA_LASERWORKT, m_strLaserWorkTime);
	DDX_Check(pDX, IDC_CHK_TWOCYCLEMODE, m_bTwoCycleMode);
	DDX_Check(pDX, IDC_CHECKPERIOD, m_checkPeriod);
	DDX_Check(pDX, IDC_CHK_CIRCLEPROCMODE, m_bCircleProcMode);
	DDX_Text(pDX, IDC_EDIT_BEAMDIA, m_lBeamDia);
	DDV_MinMaxLong(pDX, m_lBeamDia, 50, 250);
	DDX_Text(pDX, IDC_EDIT_BEAMSTEP, m_lBeamStep);
	DDV_MinMaxLong(pDX, m_lBeamStep, 25, 200);
	DDX_Text(pDX, IDC_EDT_TOOLINDEX, m_sToolIndex);
	DDX_Text(pDX, IDC_EDIT_STEPSCALE, m_dbStepScale);
	DDV_MinMaxDouble(pDX, m_dbStepScale, 1., 2.);
	DDX_Control(pDX, IDC_CMB_TOOLSUBAPT, m_cmbToolSubApt);
	DDX_Control(pDX, IDC_CMB_TOOLMODE, m_cmbToolMode);
	DDX_Control(pDX, IDC_CMB_TOOLINDEX, m_cmbToolIndex);
	DDX_Control(pDX, IDC_CMB_TOOLAPT, m_cmbToolApt);
	DDX_Control(pDX, IDC_TREE1, m_ToolParaTree);
	//}}AFX_DATA_MAP
	DDV_MinMaxUInt(pDX, m_lLaserRelease, 1, LASERMAXWIDTH);//ly add 20111216
}

BEGIN_MESSAGE_MAP(CToolParaView, TVisualFormView)
	//{{AFX_MSG_MAP(CToolParaView)
	ON_WM_CREATE()
	ON_MESSAGE(WM_TOOLPARASHOW,OnDisplayToolTree)
	ON_BN_CLICKED(IDC_BT_TOOLADD, OnToolParaAdd)
	ON_BN_CLICKED(IDC_BT_TOOLMODIFY, OnToolModify)
	ON_BN_CLICKED(IDC_BT_TOOLDEL, OnToolParaDel)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, OnSelChangedToolTree)
	ON_CBN_SELCHANGE(IDC_CMB_TOOLAPT, OnSelchangeCmbToolapt)
	ON_CBN_SELCHANGE(IDC_CMB_TOOLSUBAPT, OnSelchangeCmbToolSubapt)
	ON_BN_CLICKED(IDC_CHK_TWOCYCLEMODE, OnChkTwocyclemode)
	ON_BN_CLICKED(IDC_BNT_PARAMTEST, OnParamTest)
	ON_BN_CLICKED(IDC_BNT_PARAMTEST2, OnParamTest2)
	ON_BN_CLICKED(IDC_BNT_PARAMTEST3, OnParamTest3)
	ON_BN_CLICKED(IDC_BNT_PARAMTEST4, OnParamTest4)
	ON_BN_CLICKED(IDC_BUTTONLASERFOCUS, OnButtonLaserFocus)
	ON_BN_CLICKED(IDC_BUTTONAPERTURE, OnButtonAperture)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CHK_CIRCLEPROCMODE, OnChkCircleprocmode)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, On5mmTable)
	ON_BN_CLICKED(IDC_BT_TOOLSAVE, OnToolParaSave)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON3, OnTableAccuracy)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolParaView diagnostics

#ifdef _DEBUG
void CToolParaView::AssertValid() const
{
	CFormView::AssertValid();
}

void CToolParaView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

CToolParaView& GetToolView()
{
	static CToolParaView tpv;
	return tpv;
}

/////////////////////////////////////////////////////////////////////////////
// CToolParaView message handlers

int CToolParaView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

//  m_btnToolAdd.SubclassDlgItem(IDC_BT_TOOLADD,this);
//	m_btnToolDel.SubclassDlgItem(IDC_BT_TOOLDEL,this);
//	m_btnToolModi.SubclassDlgItem(IDC_BT_TOOLMODIFY,this);
//	m_btnToolSave.SubclassDlgItem(IDC_BT_TOOLSAVE,this);

	m_btnToolAdd.SetIcon(IDI_ADD,IDI_ADD);
    m_btnToolDel.SetIcon(IDI_DEL,IDI_DEL);
	m_btnToolModi.SetIcon(IDI_MODIFY,IDI_MODIFY);
    m_btnToolSave.SetIcon(IDI_SAVEP,IDI_SAVEP);

//	CRect rect;
//	this->GetWindowRect(rect);

	return 0;
}

LONG CToolParaView::OnDisplayToolTree(UINT wParam, LONG lParam)		//显示“显示用”刀具参数
{
	HTREEITEM hSelect;

	if(GetDoc().GetFileOpenState())
	{
		char chSelectBuf[32];
		CString str;
		
		hSelect = m_ToolParaTree.GetSelectedItem();
		if(hSelect==NULL)
			hSelect = m_ToolParaTree.GetRootItem();
		
		str = m_ToolParaTree.GetItemText(hSelect);
		sprintf(chSelectBuf,"%s",(LPCTSTR)str);
		
		if(m_ToolParaTree.GetIndentLevel(hSelect)==1)
		{
			ShowEnergyInfo(chSelectBuf);
			str = m_ToolParaTree.GetItemText(m_ToolParaTree.GetParentItem(hSelect));
			sprintf(chSelectBuf,"%s",(LPCTSTR)str);
			ShowUToolInfo(chSelectBuf);
		}
		else if(m_ToolParaTree.GetIndentLevel(hSelect)==0)
			ShowUToolInfo(chSelectBuf);
	}
	else
	{
		hSelect = m_ToolParaTree.GetRootItem();				//?
		m_ToolParaTree.Expand(hSelect,TVE_EXPAND);			//展开根结点
		m_ToolParaTree.Select(hSelect,TVGN_FIRSTVISIBLE );	//?
	}

//	SetTimer(1,10000,NULL);
	return 0;
}

void CToolParaView::ToolParaClear()						//清除“显示用”刀具参数
{
	m_cmbToolIndex.ResetContent();
	m_ToolParaTree.DeleteAllItems();

	m_cmbToolIndex.SetCurSel(0);
	m_cmbToolMode.SetCurSel(0);
	m_cmbToolApt.SetCurSel(0);
	m_cmbToolSubApt.SetCurSel(0);

	GetDoc().SetToolCycleMode(false);
	GetDoc().SetSysCircleProcMode(false);
}

void CToolParaView::SetToolPara()						//设定“加工用”刀具参数 SystemDoc::m_tmToolsPara
{
	char ez[256]={""};

	char buf[64];
	long iRelease,iPeriod;
	long iToolNo,iAperture=0,iSubAperture=0;
	float fDiameter;
	int indent=0;

//清除“加工用”刀具参数
	GetDoc().ClearTools();	

//设定“加工用”刀具参数
	HTREEITEM hti = m_ToolParaTree.GetRootItem();
	while( hti )
	{
		indent = m_ToolParaTree.GetIndentLevel( hti );	
		if(indent==0)
		{

			GetToolInfo((LPCTSTR)m_ToolParaTree.GetItemText(hti),iToolNo,fDiameter,iAperture,iSubAperture);
			if(iSubAperture==0)
				GetDoc().SetToolCycleMode(false);
			else
				GetDoc().SetToolCycleMode(true);

			if(!m_ToolParaTree.ItemHasChildren(hti)||iAperture==0)
			{
				strncpy(ez,GetLang().GetWarningText(21087),256);
                sprintf(buf,ez,iToolNo);//"刀具T%d缺少加工参数设定,请确认!"
				
				AfxMessageBox(buf);
#ifdef USELOG
				GetLog().Append_pro(10113,"OnToolParaSave");//"缺少加工能量"
#endif				
			}			
			
			if(iAperture>0)
            {
//分析加工模式：Burst/Cycle/Multi			
				HTREEITEM hChildren = m_ToolParaTree.GetChildItem(hti);
				HTREEITEM hFirstChild = hChildren;
				HTREEITEM hLastChild  = hChildren;			
				do
				{
					hLastChild = hChildren;
				}while( (hChildren=m_ToolParaTree.GetNextSiblingItem(hChildren)) !=NULL);
						
				int nDrillModel;
				nDrillModel=GetDrillModel((LPCTSTR)m_ToolParaTree.GetItemText(hFirstChild),(LPCTSTR)m_ToolParaTree.GetItemText(hLastChild));

				if(m_ToolParaTree.ItemHasChildren(hti))
				{
					GetDoc().AddUserTool(iToolNo,fDiameter,iAperture,iSubAperture);
			
					int nToolNo=GetDoc().GetToolsCnt()-1;
					GetDoc().AddLayerToolPara(nToolNo,0,nDrillModel,0);	//iLayer=0,iOffset=0
				}
			}		
		}
		else if(indent==1)  
		{
			if(iAperture>0)
			{
				sscanf((LPCTSTR)m_ToolParaTree.GetItemText(hti),"%c_R:%d_P:%d",buf,&iRelease,&iPeriod);

				if(buf[0]=='B')
					GetDoc().AddEnergyPara(GetDoc().GetToolsCnt()-1,0,0,0,iRelease,iPeriod);	//iLayer=0,iEnergyNo=0
				else if( buf[0]=='C')
					GetDoc().AddEnergyPara(GetDoc().GetToolsCnt()-1,0,0,1,iRelease,iPeriod);
			}
		}

		hti = m_ToolParaTree.GetNextItem( hti );
	}	
}

void CToolParaView::LoadToolParaTree()
{	
	char chItemBuf[32];
	HTREEITEM hItem;
	TVITEM tvi;
	ToolInfo ti;

	memset (&tvi, '\0', sizeof (TVITEM));

//清除“显示用”刀具参数
	ToolParaClear();

//从刀具参数文件中加载“显示用”刀具参数并显示
	if(m_ToolParaTree.LoadToolFromFile( (LPCTSTR)GetDoc().GetToolFileName()))
	{				
		HTREEITEM hTool = m_ToolParaTree.GetRootItem();
		long iToolNo,iAperture,iSubAperture;
		float fDiameter;

		do
		{
			GetToolInfo((LPCTSTR)m_ToolParaTree.GetItemText(hTool),iToolNo,fDiameter,iAperture,iSubAperture);
			sprintf(chItemBuf,"T%d",iToolNo);
			m_cmbToolIndex.AddString(chItemBuf);
			
#ifndef APERTURE18
			char chToolBuf[64];
#ifdef APERTURE12
			if(iAperture>12)
			{
				iAperture=12;
				sprintf(chToolBuf,"%sC%f_Ap%d_SubAp%d",chItemBuf,fDiameter,iAperture,iSubAperture);
				m_ToolParaTree.SetItemText(hTool,chToolBuf);
			}

			if(iSubAperture>12)
			{
				if(iAperture==12)
					iSubAperture=11;
				else
					iSubAperture=12;

				sprintf(chToolBuf,"%sC%f_Ap%d_SubAp%d",chItemBuf,fDiameter,iAperture,iSubAperture);
				m_ToolParaTree.SetItemText(hTool,chToolBuf);
			}
#else
			if(iAperture>8)
			{
				iAperture=8;

				sprintf(chToolBuf,"%sC%f_Ap%d_SubAp%d",chItemBuf,fDiameter,iAperture,iSubAperture);
				m_ToolParaTree.SetItemText(hTool,chToolBuf);
			}

			if(iSubAperture>8)
			{
				if(iAperture==8)
					iSubAperture=7;
				else
					iSubAperture=8;

				sprintf(chToolBuf,"%sC%f_Ap%d_SubAp%d",chItemBuf,fDiameter,iAperture,iSubAperture);
				m_ToolParaTree.SetItemText(hTool,chToolBuf);
			}
#endif
#endif		
		}while( (hTool=m_ToolParaTree.GetNextSiblingItem(hTool))!=NULL);

#ifdef DINGYING 
		fDiameter *= 1000;
#endif
//设定“加工用”刀具参数
		SetToolPara();

		GetDoc().SetIsRecordPowerPara(TRUE);		//加工用参数已做记录
	}
	else
	{
		for(int i=0; i<GetExcellonData().GetToolsNum();++i)
		{
			ti = GetExcellonData().GetToolInfo(i);
			sprintf(chItemBuf,"T%dC%f_Ap0_SubAp0",ti.m_nToolIndex,ti.m_nToolX);

			HTREEITEM hTools = m_ToolParaTree.InsertItem(chItemBuf);

			sprintf(chItemBuf,"T%d",ti.m_nToolIndex);
			m_cmbToolIndex.AddString(chItemBuf);
		}
	}

	if( GetExcellonData().GetToolsNum()>0 )
		m_dbToolDiameter =(float)GetExcellonData().GetToolInfo(0).m_nToolX;		//显示第1把刀具的尺寸
}

void CToolParaView::OnToolParaAdd() 
{
	char ez[256]={""};

	UpdateData();

	HTREEITEM hSelect = m_ToolParaTree.GetSelectedItem();
	if(hSelect == NULL)
    {
		strncpy(ez,GetLang().GetWarningText(21076),256);
        AfxMessageBox(ez);//"请先选择加工数据!"
#ifdef USELOG
		GetLog().Append_pro(10109,"OnToolParaAdd");//"请先选择加工数据"
#endif
		return ;
    }

	char buf[64];
	HTREEITEM hItem;
	int nLevel = m_ToolParaTree.GetIndentLevel(hSelect);

	sprintf(buf,"%s_R:%d_P:%d",m_cmbToolMode.GetCurSel()?"C":"C",m_lLaserRelease,m_lLaserPeriod);

#ifdef USELOG
	GetLog().Append_pro(10110,"OnToolParaAdd",buf);//"增加参数"
#endif

	if(nLevel==0)
		hItem = m_ToolParaTree.InsertItem(buf,hSelect,TVI_FIRST);
    else if(nLevel==1)
		hItem = m_ToolParaTree.InsertItem(buf,m_ToolParaTree.GetParentItem(hSelect),hSelect);

 	m_ToolParaTree.SetItemData(hItem,(DWORD)(hItem));
	m_ToolParaTree.SelectItem(hItem);
	m_ToolParaTree.Sort(hItem);

	m_bDataModified=TRUE;

	UpdateData(FALSE);
}

void CToolParaView::OnToolModify() 
{
	char ez[256]={""};

	UpdateData();

	HTREEITEM hSelect = m_ToolParaTree.GetSelectedItem();
	if(hSelect == NULL)
    {
		strncpy(ez,GetLang().GetWarningText(21076),256);
        AfxMessageBox(ez);//"请先选择加工数据!"
#ifdef USELOG
		GetLog().Append_pro(10109,"OnToolParaAdd");//"请先选择加工数据"
#endif
		return ;
    }

    if(m_ToolParaTree.GetIndentLevel(hSelect) == 1)
    {
		char buf[64];
		sprintf(buf,"%s_R:%d_P:%d",m_cmbToolMode.GetCurSel()?"C":"C",m_lLaserRelease,m_lLaserPeriod);

		m_ToolParaTree.SetItemText(hSelect,buf);
		
#ifdef USELOG
		GetLog().Append_pro(10111,20166,buf);//"修改参数","刀具参数"
#endif
		m_ToolParaTree.SetItemData(hSelect,(DWORD)(hSelect));
		m_ToolParaTree.SelectItem(hSelect);
		m_ToolParaTree.Sort(hSelect);
	}

	m_bDataModified=TRUE;

	UpdateData(FALSE);
}

void CToolParaView::OnToolParaDel() 
{
	char ez[256]={""};

	UpdateData();

	HTREEITEM hSelect = m_ToolParaTree.GetSelectedItem();
	if(hSelect == NULL)
    {
		strncpy(ez,GetLang().GetWarningText(21076),256);
        AfxMessageBox(ez);//"请先选择加工数据!"
#ifdef USELOG
		GetLog().Append_pro(10109,"OnToolParaAdd");//"请先选择加工数据"
#endif
		return ;
    }

    if(m_ToolParaTree.GetParentItem(hSelect)!=NULL)
    {
        m_ToolParaTree.DeleteItem(hSelect);

#ifdef USELOG
		GetLog().Append_pro(10112,20166);//"删除参数","刀具参数"
#endif
    }

	m_bDataModified=TRUE;

	UpdateData(FALSE);
}

void CToolParaView::OnToolParaSave() 
{
	char ez[256]={""};

	if(!m_bDataModified)
		return;

	if(!GetDoc().GetFileOpenState())
	{
		strncpy(ez,GetLang().GetWarningText(11021),256);
        AfxMessageBox(ez);//"请先打开加工文件!"
		return ;
	}

	m_bDataModified=FALSE;

//保存“显示用”刀具参数到刀具参数文件中
	m_ToolParaTree.SaveToolToFile((LPCTSTR)GetDoc().GetToolFileName());

//设定“加工用”刀具参数
	SetToolPara();

	GetDoc().SetIsRecordPowerPara(TRUE);		//加工用参数已做记录
	
//刀具参数备份	
    int i;
	LayerToolPara ltp;
	
	for(i=0;i<GetDoc().GetToolsCnt();++i)
	{
		ltp = GetDoc().GetToolPara(i);
		GetInfo().SaveToFile("toolpara.txt","_DrillModel%d,Offset%d\n",ltp.GetDrillMode(),ltp.GetFocusOffset());
		int iPeriod;
		int n =0;
		if(ltp.GetDrillMode()%2==0)
		{
			for(n=0;n<ltp.GetBurstNum();++n)
			{
				iPeriod = ltp.GetBstEnergy(n).m_iPeriod;

				GetInfo().SaveToFile("toolpara.txt","__B release%d Period%d\n",
				ltp.GetBstEnergy(n).m_iRelease,
				ltp.GetBstEnergy(n).m_iPeriod);
			}
			
			for(n=0;n<ltp.GetCycleNum();++n)
			{
				iPeriod = ltp.GetCycEnergy(n).m_iPeriod;

				GetInfo().SaveToFile("toolpara.txt","__C release%d Period%d\n",
				ltp.GetCycEnergy(n).m_iRelease,
				ltp.GetCycEnergy(n).m_iPeriod);
			}
		}
		else
		{
			for(n=0;n<ltp.GetCycleNum();++n)
			{
				iPeriod = ltp.GetCycEnergy(n).m_iPeriod;

				GetInfo().SaveToFile("toolpara.txt","__C release%d Period%d\n",
				ltp.GetCycEnergy(n).m_iRelease,
				ltp.GetCycEnergy(n).m_iPeriod);
			}

			for(n=0;n<ltp.GetBurstNum();++n)
			{
				iPeriod = ltp.GetBstEnergy(n).m_iPeriod;

				GetInfo().SaveToFile("toolpara.txt","__B release%d Period%d\n",
				ltp.GetBstEnergy(n).m_iRelease,
				ltp.GetBstEnergy(n).m_iPeriod);
			}
		}
	}

	Delay(200);
	AfxMessageBox("刀具参数已设定并保存！");

	if(GetDoc().GetSysCircleProcMode())			//20160809
	{
		int nHoleDiameter=50;

		for(int nn=0;nn<GetDoc().GetToolsCnt();++nn)
		{
			GetDoc().arrayBigHoleCPoint[nn].RemoveAll();

			nHoleDiameter=GetDoc().GetToolDiameter(nn);
			if(nHoleDiameter==0)
			{
				char buf[64];
                sprintf(buf,"刀具T%d缺少有效的孔径参数，无法进行环绕加工方式，请确认!",GetDoc().GetToolNo(nn));			
				AfxMessageBox(buf);

//				for(int mm=0;mm<nn;++mm)
//					GetDoc().arrayBigHoleCPoint[mm].RemoveAll();

//				return;
			}

			if (nHoleDiameter<=300)
				continue;

//			SetBigHole(nHoleDiameter,m_lBeamDia,m_lBeamStep,nn);
//			SetBigHoleNew(nHoleDiameter,m_lBeamDia,m_lBeamStep,nn);							//20160831
//			SetBigHoleNew(nHoleDiameter,m_dbStepScale*m_lBeamDia,m_lBeamStep,nn);			//20180823
			SetBigHoleNewNew(nHoleDiameter,m_lBeamDia,m_lBeamStep,m_dbStepScale,nn);		//20180823
		}
	}
}
/*
void CToolParaView::GetToolInfo(const char *buf, long &iToolNo, float &dbDiameter, long &iAperture)
{
	 if(!strchr(buf,'A'))
     {
        sscanf(buf,"T%d:D%f",&iToolNo,&dbDiameter);
        iAperture = 0;
     }
     else
     {
        sscanf(buf,"T%d:D%f_Ap%d",&iToolNo,&dbDiameter,&iAperture);
     }
}
*/
void CToolParaView::GetToolInfo(const char *buf, long &iToolNo, float &dbDiameter, long &iAperture,long &iSubAperture)
{
	 if(!strchr(buf,'A'))
     {
        sscanf(buf,"T%dC%f",&iToolNo,&dbDiameter);
        iAperture = 0;
		iSubAperture=0;
     }
     else
	 {
		sscanf(buf,"T%dC%f_Ap%d_SubAp%d",&iToolNo,&dbDiameter,&iAperture,&iSubAperture);
		//dbDiameter *= 1000;
	 }     
}

long CToolParaView::GetDrillModel(const char *pchFirst, const char *pchLast) const
{
	if(pchFirst[0]=='B')
    {
        if(pchLast[0]=='C')
            return  LayerToolPara::BCModel;
        else
            return  LayerToolPara::BModel;
    }
    else
    {
        if(pchLast[0] =='C')
            return LayerToolPara::CModel;
        else
            return LayerToolPara::CBModel;
    }
}
/*
void CToolParaView::ShowUToolInfo(const char *buf) 
{
	long nToolNo=0,nAperture=-1;
	char pbuf[16];

	GetToolInfo(buf,nToolNo,m_dbToolDiameter,nAperture);
	sprintf(pbuf,"T%d",nToolNo);

//	m_cmbToolApt.SetCurSel(nAperture-1);
	m_cmbToolApt.SetCurSel(nAperture);
	m_cmbToolIndex.SetCurSel( m_cmbToolIndex.FindString(-1,pbuf) );

	UpdateData(FALSE);
}
*/
void CToolParaView::ShowUToolInfo(const char *buf) 
{
	long nToolNo=0,nAperture=0,nSubAperture=0;
	char pbuf[16];

	GetToolInfo(buf,nToolNo,m_dbToolDiameter,nAperture,nSubAperture);
	m_dbToolDiameter *= 1000;
	sprintf(pbuf,"T%d",nToolNo);

//	m_sToolIndex.Format("T%d",nToolNo);		//20160809
//	m_cmbToolApt.SetCurSel(nAperture-1);

	m_cmbToolApt.SetCurSel(nAperture);
	m_cmbToolSubApt.SetCurSel(nSubAperture);
	m_cmbToolIndex.SetCurSel( m_cmbToolIndex.FindString(-1,pbuf) );

	UpdateData(FALSE);
}

void CToolParaView::ShowEnergyInfo(const char *buf)
{
   char bufModel[4];	
   memset(bufModel,'\0',sizeof(bufModel) );

   sscanf(buf,"%c_R:%d_P:%d",bufModel,&m_lLaserRelease,&m_lLaserPeriod);
  
   if(bufModel[0] =='B')
        m_cmbToolMode.SetCurSel(0);
   else
        m_cmbToolMode.SetCurSel(0);

   UpdateData(FALSE);
}

void CToolParaView::OnSelChangedToolTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cmbToolMode.SetCurSel(0);

	UpdateData();

	char chSelectBuf[32];
	CString str;
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	HTREEITEM hSelect = m_ToolParaTree.GetSelectedItem();

	str = m_ToolParaTree.GetItemText(hSelect);
	sprintf(chSelectBuf,"%s",(LPCTSTR)str);

	if(m_ToolParaTree.GetIndentLevel(hSelect)==1)
	{	
		ShowEnergyInfo(chSelectBuf);

		str = m_ToolParaTree.GetItemText(m_ToolParaTree.GetParentItem(hSelect));
		sprintf(chSelectBuf,"%s",(LPCTSTR)str);
		ShowUToolInfo(chSelectBuf);
	}
	else if(m_ToolParaTree.GetIndentLevel(hSelect)==0)
		ShowUToolInfo(chSelectBuf);

	*pResult = 0;
}

void CToolParaView::OnSelchangeCmbToolapt() 
{
    char chToolBuf[64],ToolNumBuf[4];
	char ez[256]={""};
 
	UpdateData();

	if(!GetDoc().GetFileOpenState())
	{
		strncpy(ez,GetLang().GetWarningText(11021),256);
        AfxMessageBox(ez);//"请先打开加工文件!"
		return ;
	}
	
	HTREEITEM hSelect = m_ToolParaTree.GetSelectedItem();	
	if(hSelect == NULL)
    {
		strncpy(ez,GetLang().GetWarningText(21077),256);
        AfxMessageBox(ez);//"请先选择刀具号"
#ifdef USELOG
		GetLog().Append_pro(10114,"OnSelchangeCmbToolapt");//"请先选择刀具号"
#endif
		return ;
    }

#ifndef APERTURE18
#ifndef APERTURE12//ly change 20110122 8光圈
	if(m_cmbToolApt.GetCurSel()>8)
	{
		strncpy(ez,GetLang().GetWarningText(21058),256);
		AfxMessageBox(ez);//"光圈设定值不允许大于8#光圈!"
		return ;
	}
#else//ly change 20110122 12
	if(m_cmbToolApt.GetCurSel()>12)
	{
		strncpy(ez,GetLang().GetWarningText(21059),256);
		AfxMessageBox(ez);//"光圈设定值不允许大于12#光圈!"
		return ;
	}
#endif
#endif
	
	if(m_cmbToolApt.GetCurSel()==0)
	{
		strncpy(ez,GetLang().GetWarningText(21078),256);
		int nSel = AfxMessageBox(ez,MB_YESNO);//"请确认是否要取消该刀具的加工?"

		if(nSel == IDNO )
		{
			RestorePara();
			return;
		}
	}

	m_bDataModified=TRUE;

	m_cmbToolIndex.GetLBText(m_cmbToolIndex.GetCurSel(),ToolNumBuf);

	//	sprintf(chToolBuf,"%s:D%.1f_Ap%d",ToolNumBuf,m_dbToolDiameter,m_cmbToolApt.GetCurSel()+1);
#ifdef DINGYING
	if (m_dbToolDiameter!=0)
	{
		m_dbToolDiameter = m_dbToolDiameter/1000;
	}
#endif
    sprintf(chToolBuf,"%sC%.4f_Ap%d_SubAp%d",ToolNumBuf,m_dbToolDiameter,m_cmbToolApt.GetCurSel(),m_cmbToolSubApt.GetCurSel());

    switch( m_ToolParaTree.GetIndentLevel(hSelect) )
    {
        case 0:
            m_ToolParaTree.SetItemText(hSelect,chToolBuf);
            break;
        case 1:
            m_ToolParaTree.SetItemText(m_ToolParaTree.GetParentItem(hSelect),chToolBuf);
            break;
        default:
            break;
    }
}

void CToolParaView::OnSelchangeCmbToolSubapt() 
{
	HTREEITEM hTool = m_ToolParaTree.GetRootItem();
	long iToolNo,iAperture,iSubAperture;
	float fDiameter;
    char chToolBuf[64],ToolNumBuf[4];
	char ez[256]={""};//ly 20110404
 
	UpdateData();

	if(!GetDoc().GetFileOpenState())
	{
		strncpy(ez,GetLang().GetWarningText(11021),256);
        AfxMessageBox(ez);//"请先打开加工文件!"
		return ;
	}
	
	HTREEITEM hSelect = m_ToolParaTree.GetSelectedItem();	
	if(hSelect == NULL)
    {
		strncpy(ez,GetLang().GetWarningText(21077),256);
        AfxMessageBox(ez);//"请先选择刀具号"
#ifdef USELOG
		GetLog().Append_pro(10114,"OnSelchangeCmbToolSubapt");//"请先选择刀具号"
#endif
		return ;
    }

#ifndef APERTURE18
#ifndef APERTURE12//ly change 20110122 8光圈
	if(m_cmbToolSubApt.GetCurSel()>8)
	{
		strncpy(ez,GetLang().GetWarningText(21058),256);
		AfxMessageBox(ez);//"光圈设定值不允许大于8#光圈!"
		return ;
	}
#else//ly change 20110122 12光圈
	if(m_cmbToolSubApt.GetCurSel()>12)
	{
		strncpy(ez,GetLang().GetWarningText(21059),256);
		AfxMessageBox(ez);//"光圈设定值不允许大于12#光圈!"
		return ;
	}
#endif
#endif

	if(GetDoc().GetToolCycleMode())
	{
		if(m_cmbToolSubApt.GetCurSel()==0)
		{
			strncpy(ez,GetLang().GetWarningText(21079),256);
			AfxMessageBox(ez);//"副刀具号置零，取消该刀具的主副循环加工方式!"
		}
		else
		{
			if(m_cmbToolApt.GetCurSel()==m_cmbToolSubApt.GetCurSel())
			{
				strncpy(ez,GetLang().GetWarningText(21080),256);
				AfxMessageBox(ez);//"主副刀具号选择相同，取消该刀具的主副循环加工方式!"	
				m_cmbToolSubApt.SetCurSel(0);
			}
		}
	}

	m_bDataModified=TRUE;

	m_cmbToolIndex.GetLBText(m_cmbToolIndex.GetCurSel(),ToolNumBuf);

//	sprintf(chToolBuf,"%s:D%.1f_Ap%d",ToolNumBuf,m_dbToolDiameter,m_cmbToolApt.GetCurSel()+1);
    sprintf(chToolBuf,"%sC%f_Ap%d_SubAp%d",ToolNumBuf,m_dbToolDiameter,m_cmbToolApt.GetCurSel(),m_cmbToolSubApt.GetCurSel());

    switch( m_ToolParaTree.GetIndentLevel(hSelect) )
    {
        case 0:
            m_ToolParaTree.SetItemText(hSelect,chToolBuf);
            break;
        case 1:
            m_ToolParaTree.SetItemText(m_ToolParaTree.GetParentItem(hSelect),chToolBuf);
            break;
        default:
            break;
    }
}

void CToolParaView::SetUI()//ly add 20110318
{
	char szRead[40] = {""};
	GetLang().GetUIText("ToolPara","IDC_STATIC8",szRead,40);
	SetDlgItemText(IDC_STATIC8,szRead);
	GetLang().GetUIText("ToolPara","IDC_STATIC1",szRead,40);
	SetDlgItemText(IDC_STATIC1,szRead);
	GetLang().GetUIText("ToolPara","IDC_STATIC2",szRead,40);
	SetDlgItemText(IDC_STATIC2,szRead);
	GetLang().GetUIText("ToolPara","IDC_STATIC3",szRead,40);
	SetDlgItemText(IDC_STATIC3,szRead);
	GetLang().GetUIText("ToolPara","IDC_STATIC_SUBAPT",szRead,40);
	SetDlgItemText(IDC_STATIC_SUBAPT,szRead);
	GetLang().GetUIText("ToolPara","IDC_STATIC4",szRead,40);
	SetDlgItemText(IDC_STATIC4,szRead);
	GetLang().GetUIText("ToolPara","IDC_CMB_TOOLMODE",szRead,40);
	m_cmbToolMode.ResetContent();//IDC_CMB_TOOLMODE
	m_cmbToolMode.AddString(szRead);
	GetLang().GetUIText("ToolPara","IDC_STATIC5",szRead,40);
	SetDlgItemText(IDC_STATIC5,szRead);
	GetLang().GetUIText("ToolPara","IDC_STATIC6",szRead,40);
	SetDlgItemText(IDC_STATIC6,szRead);
	GetLang().GetUIText("ToolPara","IDC_CHK_TWOCYCLEMODE",szRead,40);
	SetDlgItemText(IDC_CHK_TWOCYCLEMODE,szRead);
	GetLang().GetUIText("ToolPara","IDC_CHECKPERIOD",szRead,40);
	SetDlgItemText(IDC_CHECKPERIOD,szRead);
	GetLang().GetUIText("ToolPara","IDC_BT_TOOLADD",szRead,40);
	SetDlgItemText(IDC_BT_TOOLADD,szRead);
	GetLang().GetUIText("ToolPara","IDC_BT_TOOLMODIFY",szRead,40);
	SetDlgItemText(IDC_BT_TOOLMODIFY,szRead);
	GetLang().GetUIText("ToolPara","IDC_BT_TOOLMODIFY",szRead,40);
	SetDlgItemText(IDC_BT_TOOLMODIFY,szRead);
	GetLang().GetUIText("ToolPara","IDC_BT_TOOLDEL",szRead,40);
	SetDlgItemText(IDC_BT_TOOLDEL,szRead);
	GetLang().GetUIText("ToolPara","IDC_BT_TOOLSAVE",szRead,40);
	SetDlgItemText(IDC_BT_TOOLSAVE,szRead);
	GetLang().GetUIText("ToolPara","IDC_BNT_PARAMTEST",szRead,40);
	SetDlgItemText(IDC_BNT_PARAMTEST,szRead);
	GetLang().GetUIText("ToolPara","IDC_BNT_DRILLONEHOLE",szRead,40);
	SetDlgItemText(IDC_BNT_DRILLONEHOLE,szRead);
	GetLang().GetUIText("ToolPara","IDC_BUTTONLASERFOCUS",szRead,40);//ly add 20120210
	SetDlgItemText(IDC_BUTTONLASERFOCUS,szRead);
	GetLang().GetUIText("ToolPara","IDC_BUTTONAPERTURE",szRead,40);//ly add 20120210
	SetDlgItemText(IDC_BUTTONAPERTURE,szRead);
	GetLang().GetUIText("ToolPara","IDC_STATIC7",szRead,40);//ly add 20130422
	SetDlgItemText(IDC_STATIC7,szRead);		
}

void CToolParaView::OnInitialUpdate() 
{	
	TVisualFormView::OnInitialUpdate();
	if(GetLang().GetCurLanguage()==1)
		SetUI();

	m_edtLaserPeriod.SetParseType  (SES_NUMBERS); 
	m_edtLaserRelease.SetParseType (SES_NUMBERS); 
	m_edtLaserRelease.SetRange(0,LASERMAXWIDTH);

//	m_checkPeriod  =GetDoc().GetCheckPeriod();
	m_cmbToolIndex.SetCurSel(0);
	m_cmbToolMode.SetCurSel(0);
	m_cmbToolApt.SetCurSel(0);
	m_cmbToolSubApt.SetCurSel(0);

	m_lBeamDia = GetDoc().GetSysBeamDia();			//20160809
	m_lBeamStep = GetDoc().GetSysBeamStep();

/*
	if (GetDoc().GetBunchMode())
	{
		m_cmbToolMode.ResetContent();
		m_cmbToolMode.AddString("脉冲串(B)");
		m_cmbToolMode.SetCurSel(0);
	}
*/
}

void CToolParaView::OnChkTwocyclemode() 
{
	// TODO: Add your control notification handler code here
	char ez[256]={""};
	
	if(!GetDoc().GetFileOpenState())
	{
		strncpy(ez,GetLang().GetWarningText(11021),256);
        AfxMessageBox(ez);//"请先打开加工文件!"

		m_bTwoCycleMode=false;
		UpdateData(false);
		return ;
	}

	UpdateData();

	if(!GetDoc().GetToolCycleMode())
	{
		if(m_bTwoCycleMode)
		{
			int nSel = AfxMessageBox("请确定是否要进入主副循环加工方式? ",MB_YESNO);		
			if(nSel == IDYES )
			{
//				GetDlgItem(IDC_STATIC_SUBAPT)->EnableWindow(TRUE);
				GetDlgItem(IDC_CMB_TOOLSUBAPT)->EnableWindow(TRUE);		
				GetDoc().SetToolCycleMode(true);
			}
			else
				m_bTwoCycleMode=false;
		}
	}
	else
	{
		if(!m_bTwoCycleMode)
		{
			int nSel = AfxMessageBox("请确定是否要退出主副循环加工方式? ",MB_YESNO);		
			if(nSel == IDYES )
			{
				HTREEITEM hTool = m_ToolParaTree.GetRootItem();
				long iToolNo,iAperture,iSubAperture;
				float fDiameter;
				char chToolBuf[64],ToolNumBuf[4];
				
				do
				{
					GetToolInfo((LPCTSTR)m_ToolParaTree.GetItemText(hTool),iToolNo,fDiameter,iAperture,iSubAperture);
					sprintf(ToolNumBuf,"T%d",iToolNo);
					iSubAperture=0;
					sprintf(chToolBuf,"%sC%f_Ap%d_SubAp%d",ToolNumBuf,fDiameter,iAperture,iSubAperture);
					m_ToolParaTree.SetItemText(hTool,chToolBuf);	
				}while( (hTool=m_ToolParaTree.GetNextSiblingItem(hTool))!=NULL );
				
				m_cmbToolSubApt.SetCurSel(0);
				
//				GetDlgItem(IDC_STATIC_SUBAPT)->EnableWindow(FALSE);
				GetDlgItem(IDC_CMB_TOOLSUBAPT)->EnableWindow(FALSE);		
				GetDoc().SetToolCycleMode(false);
			}
			else
				m_bTwoCycleMode=true;
		}
	}

	UpdateData(false);
}

void CToolParaView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	// TODO: Add your specialized code here and/or call the base class
	char ez[256]={""};

	if(bActivate)
	{
//		SetTimer(888,500,NULL);
/*				
		if(!GetDoc().GetFileOpenState())
		{
			m_dbToolDiameter=0;
			m_lLaserPeriod = 100;
			m_lLaserRelease = 5;
		}
*/
		GetDlgItem(IDC_CMB_TOOLSUBAPT)->EnableWindow(FALSE);			//暂时取消主副循环加工方式 20180626
		GetDlgItem(IDC_STATIC_SUBAPT)->EnableWindow(FALSE);

		GetDlgItem(IDC_STATIC4)->EnableWindow(FALSE);
		GetDlgItem(IDC_CMB_TOOLMODE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDT_LASERPERIOD)->EnableWindow(FALSE);

		if(GetControl().GetRunState()!=CControl::END)
		{
			GetDlgItem(IDC_BNT_PARAMTEST2)->EnableWindow(FALSE);
			GetDlgItem(IDC_BNT_PARAMTEST3)->EnableWindow(FALSE);
			GetDlgItem(IDC_BNT_PARAMTEST4)->EnableWindow(FALSE);
			GetDlgItem(IDC_BNT_PARAMTEST)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTONLASERFOCUS)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTONAPERTURE)->EnableWindow(FALSE);	
			
			GetDlgItem(IDC_CMB_TOOLINDEX)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDT_TOOLDIAMETER)->EnableWindow(FALSE);
			GetDlgItem(IDC_CMB_TOOLAPT)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDT_LASERRELEASE)->EnableWindow(FALSE);
			
			GetDlgItem(IDC_BT_TOOLADD)->EnableWindow(FALSE);
			GetDlgItem(IDC_BT_TOOLMODIFY)->EnableWindow(FALSE);
			GetDlgItem(IDC_BT_TOOLDEL)->EnableWindow(FALSE);
			GetDlgItem(IDC_BT_TOOLSAVE)->EnableWindow(FALSE);
			
			GetDlgItem(IDC_CHK_CIRCLEPROCMODE)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_BEAMSTEP)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_BEAMDIA)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
		}
		else
		{
			GetDlgItem(IDC_BNT_PARAMTEST2)->EnableWindow(TRUE);
			GetDlgItem(IDC_BNT_PARAMTEST3)->EnableWindow(TRUE);
			GetDlgItem(IDC_BNT_PARAMTEST4)->EnableWindow(TRUE);	
			GetDlgItem(IDC_BNT_PARAMTEST)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTONLASERFOCUS)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTONAPERTURE)->EnableWindow(TRUE);
			
			GetDlgItem(IDC_CMB_TOOLINDEX)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDT_TOOLDIAMETER)->EnableWindow(TRUE);
			GetDlgItem(IDC_CMB_TOOLAPT)->EnableWindow(TRUE);	
			GetDlgItem(IDC_EDT_LASERRELEASE)->EnableWindow(TRUE);
			
			GetDlgItem(IDC_BT_TOOLADD)->EnableWindow(TRUE);
			GetDlgItem(IDC_BT_TOOLMODIFY)->EnableWindow(TRUE);
			GetDlgItem(IDC_BT_TOOLDEL)->EnableWindow(TRUE);
			GetDlgItem(IDC_BT_TOOLSAVE)->EnableWindow(TRUE);
			
			GetDlgItem(IDC_CHK_CIRCLEPROCMODE)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_BEAMSTEP)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_BEAMDIA)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
		}
	}
	else
	{
//		KillTimer(888);

		if(m_bDataModified&&GetDoc().GetFileOpenState())
		{
			strncpy(ez,GetLang().GetWarningText(21081),256);
			int nSel = AfxMessageBox(ez,MB_YESNO);//"加工参数已经改变，请问是否保存?"

			if(nSel == IDYES )
				OnToolParaSave();
			else
				RestorePara();

			m_bDataModified=FALSE;
		}
	}

	TVisualFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CToolParaView::RestorePara()
{
	LoadToolParaTree();

	UpdateData(false);
}

void CToolParaView::ParamTest(int testType)
{
	char ez[256]={""};

	if(!GetDoc().GetMotorState())
	{
		strncpy(ez,GetLang().GetWarningText(21001),256);
		AfxMessageBox(ez);//"机器未整体回零，不允许相关操作!"
		return;
	}

    char buf[64],ToolNumBuf[4];
	long ToolNo,iToolNo,iAperture=0,iSubAperture=0,nToolIndex=-1;
	float fDiameter;
	int nToolno=-1;

	UpdateData();

	if(m_ToolParaTree.GetRootItem()==NULL)
	{
		strncpy(ez,GetLang().GetWarningText(21082),256);
        AfxMessageBox(ez);//"请先打开文件并设定刀具参数!"
		return;
	}
	
	if(m_bDataModified)
	{		
		strncpy(ez,GetLang().GetWarningText(21083),256);
        AfxMessageBox(ez);//"加工参数已经改变，请先保存参数!"
		return;
	}

	m_cmbToolIndex.GetLBText(m_cmbToolIndex.GetCurSel(),ToolNumBuf);
    sscanf(ToolNumBuf,"T%d",&ToolNo);
	
	HTREEITEM hti = m_ToolParaTree.GetRootItem();
	while( hti )
	{
		GetToolInfo((LPCTSTR)m_ToolParaTree.GetItemText(hti),iToolNo,fDiameter,iAperture,iSubAperture);
		
		if(ToolNo==iToolNo)
		{
			if(!m_ToolParaTree.ItemHasChildren(hti)||iAperture==0)
			{
				strncpy(ez,GetLang().GetWarningText(21087),256);
                sprintf(buf,ez,iToolNo);		//"刀具T%d缺少加工参数设定,请确认!"	
				AfxMessageBox(buf);
				return;
			}
			else
			{
				for(int it=0;it<GetDoc().GetToolsCnt();++it)
				{
					if(ToolNo == GetDoc().GetToolNo(it))
					{
						nToolno=it;
						break;
					}
				}
				
				if(nToolno==-1)
				{
					strncpy(ez,GetLang().GetWarningText(21084),256);
					AfxMessageBox(ez);//"刀具参数信息错误!"
					return;
				}
			}
		}	

		hti = m_ToolParaTree.GetNextSiblingItem( hti );
	}

	int nSel=AfxMessageBox("请确认是否继续操作，继续请选“是”，取消请选“否”！",MB_YESNO);	//20191015
	if(nSel==IDNO)
		return;
	
	int nHead=2;
	if(GetDoc().GetProcAxisMode()==1)
		nHead=0;
	if(GetDoc().GetProcAxisMode()==2)
		nHead=1;
/*
	strncpy(ez,GetLang().GetWarningText(31038),256);
	int nSel = AfxMessageBox(ez,MB_YESNOCANCEL);//"单轴测试参数  选择  '是'\n双轴测试参数  选择  '否'\n取   消  操   作  选择  '取消'\n"

	if(nSel==IDYES)
	{
		strncpy(ez,GetLang().GetWarningText(31039),256);
		nSel = AfxMessageBox(ez,MB_YESNOCANCEL);//"左轴测试  选择  '是'\n右轴测试  选择  '否'\n取消操作  选择  '取消'\n"

		if(nSel==IDYES)
			nHead=0; 
		else if(nSel==IDNO) 
			nHead=1;
		else
			return;

	}
	else if(nSel==IDNO)
		nHead=2;
	else
		return;	
*/
//平台真空吸附并判断
	GetControl().ChannelOutput(OFANPOWERON,IO_ON); 
	Delay(500);

	if(!GetControl().TableAdsorbInProc(nHead))
	{
		GetControl().ResetTableStatus();
		return;
	}

	GetControl().SetRunState(CControl::OPERATE);
	OnActivateView(true,this,this);

	switch(testType)
	{
	case 1:
		 GetControl().DrillParamTest(nHead,nToolno);
		break;
	case 2:
		 GetControl().DrillParamTest(nHead,nToolno,1);
		break;
	case 3:
		 GetControl().DrillParamTest(nHead,nToolno,0.5);
		break;
	case 4:
		 GetControl().DrillParamTest(nHead,nToolno,0.25);
		break;
	case 5:
		 GetControl().DrillParamFocusTest(nHead,nToolno,1);
		break;
	case 6:
		 GetControl().DrillParamApertureTest(nHead,nToolno,1);
		break;
	case 7:
		 GetControl().DrillTableTest(nHead,nToolno);
		break;
	case 8:
		 GetControl().DrillTableAccuracy(nHead,nToolno);
		break;
	}

	nSel = AfxMessageBox("请选择是否保持平台吸附，保持请选“是”，取消请选“否”!",MB_YESNO);	//20190626
	if(nSel==IDNO)
	{
		GetControl().TableClampOperate(true,GetDoc().GetTableClamp());
		GetControl().ChannelOutput(OFANPOWERON,IO_OFF); 
		GetControl().ChannelOutput(OTABLEVACUUMVALVE1,IO_OFF);
		GetControl().ChannelOutput(OTABLEVACUUMVALVERE1,IO_OFF);
		GetControl().ChannelOutput(OTABLEVACUUMVALVE2,IO_OFF);
		GetControl().ChannelOutput(OTABLEVACUUMVALVERE2,IO_OFF);
	}

	GetControl().SetRunState(CControl::END);
	OnActivateView(true,this,this);
}

void CToolParaView::OnParamTest() 
{
	ParamTest(1);
}

void CToolParaView::OnParamTest2()
{
	ParamTest(2);
}

void CToolParaView::OnParamTest3() 
{
	ParamTest(3);
}

void CToolParaView::OnParamTest4() 
{
	ParamTest(4);
}

void CToolParaView::OnButtonLaserFocus()
{
	ParamTest(5);
}

void CToolParaView::OnButtonAperture()
{
	ParamTest(6);
}

void CToolParaView::OnTimer(UINT nIDEvent)
{
	if (nIDEvent == 1)
	{

	}

    if (nIDEvent == 888)
	{
/*
        GetDlgItem(IDC_CMB_TOOLINDEX)->EnableWindow(FALSE);					//?
		
		if(GetControl().GetRunState()==CControl::RUN)
		{
			GetDlgItem(IDC_CMB_TOOLAPT)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDT_LASERRELEASE)->EnableWindow(FALSE);
		}
		else
		{
			int nLevel = GetDoc().GetCurUserLevel();

			if(nLevel==SystemDoc::PRIMARY)//初级				
			{
				GetDlgItem(IDC_CMB_TOOLAPT)->EnableWindow(FALSE);
				GetDlgItem(IDC_EDT_LASERRELEASE)->EnableWindow(FALSE);
			}
			else
			{
				GetDlgItem(IDC_CMB_TOOLAPT)->EnableWindow(TRUE);
				GetDlgItem(IDC_EDT_LASERRELEASE)->EnableWindow(TRUE);
			}
		}
*/
	}

	TVisualFormView::OnTimer(nIDEvent);
}

void CToolParaView::OnDestroy() 
{
	TVisualFormView::OnDestroy();
	
	// TODO: Add your message handler code here

//	KillTimer(1);//ly add 20130114
}
//////////////////////////////////////////////////////////////////////////////////////////////////
void CToolParaView::OnChkCircleprocmode()				//20160809
{
	// TODO: Add your control notification handler code here
	char ez[256]={""};
	
	if(!GetDoc().GetFileOpenState())
	{
		strncpy(ez,GetLang().GetWarningText(11021),256);
        AfxMessageBox(ez);//"请先打开加工文件!"

		m_bCircleProcMode=false;
		UpdateData(false);
		return ;
	}

	UpdateData();
	char* buf;

	if(!GetDoc().GetSysCircleProcMode())
	{
		if(m_bCircleProcMode)
		{
			int nSel = AfxMessageBox("请确定是否要进入大孔环绕加工方式? ",MB_YESNO);		
			if(nSel == IDYES )
			{
				buf="10mm间距";
				SetDlgItemText(IDC_BNT_PARAMTEST2,buf);
				buf="5mm间距";
				SetDlgItemText(IDC_BNT_PARAMTEST3,buf);
				buf="2.5mm间距";
				SetDlgItemText(IDC_BNT_PARAMTEST4,buf);

				GetDoc().SetSysCircleProcMode(true);
			}
			else
				m_bCircleProcMode=false;
		}
	}
	else
	{
		if(!m_bCircleProcMode)
		{
			int nSel = AfxMessageBox("请确定是否要退出大孔环绕加工方式? ",MB_YESNO);		
			if(nSel == IDYES )
			{
				buf="1mm间距";
				SetDlgItemText(IDC_BNT_PARAMTEST2,buf);
				buf="0.5mm间距";
				SetDlgItemText(IDC_BNT_PARAMTEST3,buf);
				buf="0.25mm间距";
				SetDlgItemText(IDC_BNT_PARAMTEST4,buf);

				GetDoc().SetSysCircleProcMode(false);
			}
			else
				m_bCircleProcMode=true;
		}
	}

	UpdateData(false);
}

void CToolParaView::SetBigHole(int nHoleDia,int nBeamDia,int nStepLength,int nIndex)
{
	double faculaRadius=nBeamDia/2.0;				//光斑半径		
	double stepLength=nStepLength;					//光斑间距
	double holeRadius=(nHoleDia-nBeamDia)/2.0;		//最外圆轨迹半径
	
	int  circleNumbers=holeRadius/stepLength;
	if ((holeRadius-stepLength*circleNumbers)>(stepLength/2.0))	
		circleNumbers+=1;
	
	stepLength=holeRadius/(double)circleNumbers;

	double dbSLScale=GetDoc().GetSLBitPerMM()/1000.0;
	double dLoops=0.0;
	int iLoops=0;
	double angle=0.0;
	Coord temp(0,0);
	
	for (int i=1;i<=circleNumbers;i++)		//由内向外
	{
		dLoops=(double)i*2.0*PI;			
		iLoops=i*2*PI;					
		if (abs(10*dLoops-10*iLoops)>4)
			iLoops=iLoops+1;
		
		angle=2.0*PI/(double)iLoops;	
		
		for (int f=0;f<iLoops;f++)
		{
			temp.x=i*stepLength*cos(f*angle)*dbSLScale;
			temp.y=i*stepLength*sin(f*angle)*dbSLScale;
			GetDoc().arrayBigHoleCPoint[nIndex].Add(temp);
		}	
	}
/*
	for (int i=circleNumbers;i>0;i--)		//由外向内
	{
		dLoops=(double)i*2.0*PI;			
		iLoops=i*2*PI;					
		if (abs(10*dLoops-10*iLoops)>4)
			iLoops=iLoops+1;
		
		angle=2.0*PI/(double)iLoops;	
		
		for (int f=0;f<iLoops;f++)
		{
			temp.x=i*stepLength*cos(f*angle)*dbSLScale;
			temp.y=i*stepLength*sin(f*angle)*dbSLScale;
			GetDoc().arrayBigHoleCPoint[nIndex].Add(temp);
		}	
	}
*/
}

void CToolParaView::OnButton1() 
{
	// TODO: Add your control notification handler code here
	if(!GetDoc().GetSysCircleProcMode())
		return;

	UpdateData();

	GetDoc().SetSysBeamDia(m_lBeamDia);
	GetDoc().SetSysBeamStep(m_lBeamStep);
	GetDoc().SaveProcessParam();
	Delay(200);
	AfxMessageBox("光斑参数已设定并保存！");

//	m_bDataModified=TRUE;
}
//////////////////////////////////////////////////////////////////////////////////
void CToolParaView::SetBigHoleNew(int nHoleDia,int nBeamDia,int nStepLength,int nIndex)		//20180823 控制圆间点距，固定圆上点距
{
	double circleStepLength=nBeamDia;
	int  circleNumbers=nHoleDia/2/circleStepLength+1;

	double dbSLScale=GetDoc().GetSLBitPerMM()/1000.0;
	double dLoops=0.0;
	int iLoops=0;
	double angle=0.0;
	Coord temp(0,0);

	for (int i=0;i<circleNumbers;i++)							//由外向内	
	{
		dLoops=(double)2.0*PI*(nHoleDia/2-i*circleStepLength)/nStepLength;			
		iLoops=2*PI*(nHoleDia/2-i*circleStepLength)/nStepLength;
		if (abs(10*dLoops-10*iLoops)>4)
			iLoops=iLoops+1;
		
		angle=2.0*PI/(double)iLoops;	
		
		for (int f=0;f<iLoops;f++)
		{
			temp.x=(nHoleDia/2-i*circleStepLength)*cos(f*angle)*dbSLScale;
			temp.y=(nHoleDia/2-i*circleStepLength)*sin(f*angle)*dbSLScale;

			GetDoc().arrayBigHoleCPoint[nIndex].Add(temp);
		}	
	}
}

void CToolParaView::SetBigHoleNewNew(int nHoleDia,int nBeamDia,int nStepLength,double dbStepScale,int nIndex)	//20180824 控制圆间点距，变化圆上点距
{
	double circleStepLength=nBeamDia*dbStepScale;
	int  circleNumbers=nHoleDia/2/circleStepLength+1;

	double dbSLScale=GetDoc().GetSLBitPerMM()/1000.0;
	double dLoops=0.0;
	int iLoops=0;
	double angle=0.0;
	double angleOffset=0.0;
	Coord temp(0,0);
	double dbStepLength=nStepLength;
	double dbRadius=nHoleDia/2;
/*
	for (int i=0;i<circleNumbers;i++)							//由外向内	
	{
		dbStepLength=((dbStepScale-1.0)*i+1)*nStepLength;		//变化圆上点距
		dbRadius=nHoleDia/2-i*circleStepLength;	

		dLoops=(double)2.0*PI*dbRadius/dbStepLength;			
		iLoops=2*PI*dbRadius/dbStepLength;
		if (abs(10*dLoops-10*iLoops)>4)
			iLoops=iLoops+1;
		
		angle=2.0*PI/(double)iLoops;	
		
		for (int f=0;f<iLoops;f++)
		{
			temp.x=dbRadius*cos(f*angle)*dbSLScale;
			temp.y=dbRadius*sin(f*angle)*dbSLScale;

			GetDoc().arrayBigHoleCPoint[nIndex].Add(temp);
		}	
	}
*/
/*
	for (int i=circleNumbers-1;i>=0;i--)						//由内向外	
	{
		dbStepLength=((dbStepScale-1.0)*i+1)*nStepLength;		//变化圆上点距
		dbRadius=nHoleDia/2-i*circleStepLength;	

		dLoops=(double)2.0*PI*dbRadius/dbStepLength;			
		iLoops=2*PI*dbRadius/dbStepLength;
		if (abs(10*dLoops-10*iLoops)>4)
			iLoops=iLoops+1;
		
		angle=2.0*PI/(double)iLoops;	

		for (int f=0;f<iLoops;f++)		
//		for (int f=0;f<iLoops-1;f++)
		{
			temp.x=dbRadius*cos(f*angle)*dbSLScale;
			temp.y=dbRadius*sin(f*angle)*dbSLScale;

			GetDoc().arrayBigHoleCPoint[nIndex].Add(temp);
		}	
	}
*/

	angleOffset=2.0*PI/(double)circleNumbers;					//变化圆上起始点

	for (int i=circleNumbers-1;i>=0;i--)						//由内向外	
	{
		dbStepLength=((dbStepScale-1.0)*i+1)*nStepLength;		//变化圆上点距
		dbRadius=nHoleDia/2-i*circleStepLength;	

		dLoops=(double)2.0*PI*dbRadius/dbStepLength;			
		iLoops=2*PI*dbRadius/dbStepLength;
		if (abs(10*dLoops-10*iLoops)>4)
			iLoops=iLoops+1;
		
		angle=2.0*PI/(double)iLoops;	
		
		for (int f=0;f<iLoops;f++)
//		for (int f=0;f<iLoops-1;f++)
		{
			temp.x=dbRadius*cos(f*angle+i*angleOffset)*dbSLScale;
			temp.y=dbRadius*sin(f*angle+i*angleOffset)*dbSLScale;

			GetDoc().arrayBigHoleCPoint[nIndex].Add(temp);
		}

		if(i==0)
		{
			for (int f=0;f<iLoops;f++)
//			for (int f=0;f<iLoops-1;f++)
			{
				temp.x=dbRadius*cos(f*angle+i*angleOffset+angle/3)*dbSLScale;
				temp.y=dbRadius*sin(f*angle+i*angleOffset+angle/3)*dbSLScale;
				
				GetDoc().arrayBigHoleCPoint[nIndex].Add(temp);
			}

			for (int g=0;g<iLoops;g++)
//			for (int g=0;g<iLoops-1;g++)
			{
				temp.x=dbRadius*cos(g*angle+i*angleOffset+angle*2/3)*dbSLScale;
				temp.y=dbRadius*sin(g*angle+i*angleOffset+angle*2/3)*dbSLScale;
				
				GetDoc().arrayBigHoleCPoint[nIndex].Add(temp);
			}
		}
	}

}

void CToolParaView::On5mmTable() 
{
	// TODO: Add your control notification handler code here
	ParamTest(7);
}

void CToolParaView::OnTableAccuracy() 
{
	// TODO: Add your control notification handler code here
	ParamTest(8);	
}
