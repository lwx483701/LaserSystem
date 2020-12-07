// SignalOutView.cpp : implementation file
//

#include "stdafx.h"
#include "LaserSystem.h"
#include "SignalOutView.h"
#include "operatecontrol.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSignalOutView

IMPLEMENT_DYNCREATE(CSignalOutView, TVisualFormView)

CSignalOutView::CSignalOutView()
	: TVisualFormView(CSignalOutView::IDD)
{
	//{{AFX_DATA_INIT(CSignalOutView)
	//}}AFX_DATA_INIT
}

CSignalOutView::~CSignalOutView()
{

}

void CSignalOutView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSignalOutView)
	DDX_Control(pDX, IDC_CHK_OUT_50, m_chkOut50);
	DDX_Control(pDX, IDC_CHK_OUT_14, m_chkOut14);
	DDX_Control(pDX, IDC_CHK_OUT_13, m_chkOut13);
	DDX_Control(pDX, IDC_CHK_OUT_9, m_chkOut9);
	DDX_Control(pDX, IDC_CHK_OUT_8, m_chkOut8);
	DDX_Control(pDX, IDC_CHK_OUT_7, m_chkOut7);
	DDX_Control(pDX, IDC_CHK_OUT_6, m_chkOut6);
	DDX_Control(pDX, IDC_CHK_OUT_5, m_chkOut5);
	DDX_Control(pDX, IDC_CHK_OUT_4, m_chkOut4);
	DDX_Control(pDX, IDC_CHK_OUT_3, m_chkOut3);
	DDX_Control(pDX, IDC_CHK_OUT_2, m_chkOut2);
	DDX_Control(pDX, IDC_CHK_OUT_1, m_chkOut1);
	DDX_Control(pDX, IDC_CHK_OUT_12, m_chkOut12);
	DDX_Control(pDX, IDC_CHK_OUT_11, m_chkOut11);
	DDX_Control(pDX, IDC_CHK_OUT_10, m_chkOut10);
	DDX_Control(pDX, IDC_CHK_OUT_28, m_chkOut28);
	DDX_Control(pDX, IDC_CHK_OUT_27, m_chkOut27);
	DDX_Control(pDX, IDC_CHK_OUT_26, m_chkOut26);
	DDX_Control(pDX, IDC_CHK_OUT_25, m_chkOut25);
	DDX_Control(pDX, IDC_CHK_OUT_24, m_chkOut24);
	DDX_Control(pDX, IDC_CHK_OUT_23, m_chkOut23);
	DDX_Control(pDX, IDC_CHK_OUT_22, m_chkOut22);
	DDX_Control(pDX, IDC_CHK_OUT_21, m_chkOut21);
	DDX_Control(pDX, IDC_CHK_OUT_20, m_chkOut20);
	DDX_Control(pDX, IDC_CHK_OUT_49, m_chkOut49);
	DDX_Control(pDX, IDC_CHK_OUT_48, m_chkOut48);
	DDX_Control(pDX, IDC_CHK_OUT_47, m_chkOut47);
	DDX_Control(pDX, IDC_CHK_OUT_46, m_chkOut46);
	DDX_Control(pDX, IDC_CHK_OUT_45, m_chkOut45);
	DDX_Control(pDX, IDC_CHK_OUT_44, m_chkOut44);
	DDX_Control(pDX, IDC_CHK_OUT_43, m_chkOut43);
	DDX_Control(pDX, IDC_CHK_OUT_42, m_chkOut42);
	DDX_Control(pDX, IDC_CHK_OUT_41, m_chkOut41);
	DDX_Control(pDX, IDC_CHK_OUT_40, m_chkOut40);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSignalOutView, TVisualFormView)
	//{{AFX_MSG_MAP(CSignalOutView)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_CHK_OUT_1, OnOutput1Click)
	ON_BN_CLICKED(IDC_CHK_OUT_2, OnOutput2Click)
	ON_BN_CLICKED(IDC_CHK_OUT_3, OnOutput3Click)
	ON_BN_CLICKED(IDC_CHK_OUT_4, OnOutput4Click)
	ON_BN_CLICKED(IDC_CHK_OUT_5, OnOutput5Click)
	ON_BN_CLICKED(IDC_CHK_OUT_6, OnOutput6Click)
	ON_BN_CLICKED(IDC_CHK_OUT_7, OnOutput7Click)
	ON_BN_CLICKED(IDC_CHK_OUT_8, OnOutput8Click)
	ON_BN_CLICKED(IDC_CHK_OUT_9, OnOutput9Click)
	ON_BN_CLICKED(IDC_CHK_OUT_10, OnOutput10Click)
	ON_BN_CLICKED(IDC_CHK_OUT_11, OnOutput11Click)
	ON_BN_CLICKED(IDC_CHK_OUT_12, OnOutput12Click)
	ON_BN_CLICKED(IDC_CHK_OUT_20, OnOutput20Click)
	ON_BN_CLICKED(IDC_CHK_OUT_21, OnOutput21Click)
	ON_BN_CLICKED(IDC_CHK_OUT_24, OnOutput24Click)
	ON_BN_CLICKED(IDC_CHK_OUT_25, OnOutput25Click)
	ON_BN_CLICKED(IDC_CHK_OUT_26, OnOutput26Click)
	ON_BN_CLICKED(IDC_CHK_OUT_27, OnOutput27Click)
	ON_BN_CLICKED(IDC_CHK_OUT_28, OnOutput28Click)
	ON_BN_CLICKED(IDC_CHK_OUT_22, OnChkOut22Click)
	ON_BN_CLICKED(IDC_CHK_OUT_23, OnChkOut23Click)
	ON_BN_CLICKED(IDC_CHK_OUT_40, OnChkOut40Click)
	ON_BN_CLICKED(IDC_CHK_OUT_41, OnChkOut41Click)
	ON_BN_CLICKED(IDC_CHK_OUT_42, OnChkOut42Click)
	ON_BN_CLICKED(IDC_CHK_OUT_43, OnChkOut43Click)
	ON_BN_CLICKED(IDC_CHK_OUT_44, OnChkOut44Click)
	ON_BN_CLICKED(IDC_CHK_OUT_45, OnChkOut45Click)
	ON_BN_CLICKED(IDC_CHK_OUT_46, OnChkOut46Click)
	ON_BN_CLICKED(IDC_CHK_OUT_47, OnChkOut47Click)
	ON_BN_CLICKED(IDC_CHK_OUT_48, OnChkOut48Click)
	ON_BN_CLICKED(IDC_CHK_OUT_49, OnChkOut49Click)
	ON_BN_CLICKED(IDC_CHK_OUT_13, OnChkOut13Click)
	ON_BN_CLICKED(IDC_CHK_OUT_14, OnChkOut14Click)
	ON_BN_CLICKED(IDC_CHK_OUT_50, OnChkOut50)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSignalOutView diagnostics

#ifdef _DEBUG
void CSignalOutView::AssertValid() const
{
	CFormView::AssertValid();
}

void CSignalOutView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSignalOutView message handlers

int CSignalOutView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (TVisualFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_chkOut1.SubclassDlgItem(IDC_CHK_OUT_1,this);
	m_chkOut1.SetIcon(IDI_LEDON,IDI_LEDOFF);

	m_chkOut2.SubclassDlgItem(IDC_CHK_OUT_2,this);
	m_chkOut2.SetIcon(IDI_LEDON,IDI_LEDOFF);

	m_chkOut3.SubclassDlgItem(IDC_CHK_OUT_3,this);
	m_chkOut3.SetIcon(IDI_LEDON,IDI_LEDOFF);

	m_chkOut4.SubclassDlgItem(IDC_CHK_OUT_4,this);
	m_chkOut4.SetIcon(IDI_LEDON,IDI_LEDOFF);

	m_chkOut5.SubclassDlgItem(IDC_CHK_OUT_5,this);
	m_chkOut5.SetIcon(IDI_LEDON,IDI_LEDOFF);

	m_chkOut6.SubclassDlgItem(IDC_CHK_OUT_6,this);
	m_chkOut6.SetIcon(IDI_LEDON,IDI_LEDOFF);

	m_chkOut7.SubclassDlgItem(IDC_CHK_OUT_7,this);
	m_chkOut7.SetIcon(IDI_LEDON,IDI_LEDOFF);

	m_chkOut8.SubclassDlgItem(IDC_CHK_OUT_8,this);
	m_chkOut8.SetIcon(IDI_LEDON,IDI_LEDOFF);

	m_chkOut9.SubclassDlgItem(IDC_CHK_OUT_9,this);
	m_chkOut9.SetIcon(IDI_LEDON,IDI_LEDOFF);

	m_chkOut10.SubclassDlgItem(IDC_CHK_OUT_10,this);
	m_chkOut10.SetIcon(IDI_LEDON,IDI_LEDOFF);

	m_chkOut11.SubclassDlgItem(IDC_CHK_OUT_11,this);
	m_chkOut11.SetIcon(IDI_LEDON,IDI_LEDOFF);

	m_chkOut12.SubclassDlgItem(IDC_CHK_OUT_12,this);
	m_chkOut12.SetIcon(IDI_LEDON,IDI_LEDOFF);

	m_chkOut13.SubclassDlgItem(IDC_CHK_OUT_13,this);
	m_chkOut13.SetIcon(IDI_LEDON,IDI_LEDOFF);

	m_chkOut14.SubclassDlgItem(IDC_CHK_OUT_14,this);
	m_chkOut14.SetIcon(IDI_LEDON,IDI_LEDOFF);

//	m_chkOut15.SubclassDlgItem(IDC_CHK_OUT_15,this);
//	m_chkOut15.SetIcon(IDI_LEDON,IDI_LEDOFF);

//	m_chkOut16.SubclassDlgItem(IDC_CHK_OUT_16,this);
//	m_chkOut16.SetIcon(IDI_LEDON,IDI_LEDOFF);

//	m_chkOut17.SubclassDlgItem(IDC_CHK_OUT_17,this);
//	m_chkOut17.SetIcon(IDI_LEDON,IDI_LEDOFF);

//	m_chkOut18.SubclassDlgItem(IDC_CHK_OUT_18,this);
//	m_chkOut18.SetIcon(IDI_LEDON,IDI_LEDOFF);

//	m_chkOut19.SubclassDlgItem(IDC_CHK_OUT_19,this);
//	m_chkOut19.SetIcon(IDI_LEDON,IDI_LEDOFF);

	m_chkOut20.SubclassDlgItem(IDC_CHK_OUT_20,this);
	m_chkOut20.SetIcon(IDI_LEDON,IDI_LEDOFF);

	m_chkOut21.SubclassDlgItem(IDC_CHK_OUT_21,this);
	m_chkOut21.SetIcon(IDI_LEDON,IDI_LEDOFF);

	m_chkOut22.SubclassDlgItem(IDC_CHK_OUT_22,this);
	m_chkOut22.SetIcon(IDI_LEDON,IDI_LEDOFF);

	m_chkOut23.SubclassDlgItem(IDC_CHK_OUT_23,this);
	m_chkOut23.SetIcon(IDI_LEDON,IDI_LEDOFF);

	m_chkOut24.SubclassDlgItem(IDC_CHK_OUT_24,this);
	m_chkOut24.SetIcon(IDI_LEDON,IDI_LEDOFF);

	m_chkOut25.SubclassDlgItem(IDC_CHK_OUT_25,this);
	m_chkOut25.SetIcon(IDI_LEDON,IDI_LEDOFF);

	m_chkOut26.SubclassDlgItem(IDC_CHK_OUT_26,this);
	m_chkOut26.SetIcon(IDI_LEDON,IDI_LEDOFF);

	m_chkOut27.SubclassDlgItem(IDC_CHK_OUT_27,this);
	m_chkOut27.SetIcon(IDI_LEDON,IDI_LEDOFF);

	m_chkOut28.SubclassDlgItem(IDC_CHK_OUT_28,this);
	m_chkOut28.SetIcon(IDI_LEDON,IDI_LEDOFF);

//	m_chkOut29.SubclassDlgItem(IDC_CHK_OUT_29,this);
//	m_chkOut29.SetIcon(IDI_LEDON,IDI_LEDOFF);

//	m_chkOut30.SubclassDlgItem(IDC_CHK_OUT_30,this);
//	m_chkOut30.SetIcon(IDI_LEDON,IDI_LEDOFF);

//	m_chkOut31.SubclassDlgItem(IDC_CHK_OUT_31,this);
//	m_chkOut31.SetIcon(IDI_LEDON,IDI_LEDOFF);

//	m_chkOut32.SubclassDlgItem(IDC_CHK_OUT_32,this);
//	m_chkOut32.SetIcon(IDI_LEDON,IDI_LEDOFF);

//	m_chkOut33.SubclassDlgItem(IDC_CHK_OUT_33,this);
//	m_chkOut33.SetIcon(IDI_LEDON,IDI_LEDOFF);
    
//	m_chkOut34.SubclassDlgItem(IDC_CHK_OUT_34,this);
//	m_chkOut34.SetIcon(IDI_LEDON,IDI_LEDOFF);

//	m_chkOut35.SubclassDlgItem(IDC_CHK_OUT_35,this);
//	m_chkOut35.SetIcon(IDI_LEDON,IDI_LEDOFF);

//	m_chkOut36.SubclassDlgItem(IDC_CHK_OUT_36,this);
//	m_chkOut36.SetIcon(IDI_LEDON,IDI_LEDOFF);

//	m_chkOut37.SubclassDlgItem(IDC_CHK_OUT_37,this);
//	m_chkOut37.SetIcon(IDI_LEDON,IDI_LEDOFF);

//	m_chkOut38.SubclassDlgItem(IDC_CHK_OUT_38,this);
//	m_chkOut38.SetIcon(IDI_LEDON,IDI_LEDOFF);

//	m_chkOut39.SubclassDlgItem(IDC_CHK_OUT_39,this);
//	m_chkOut39.SetIcon(IDI_LEDON,IDI_LEDOFF);

	m_chkOut40.SubclassDlgItem(IDC_CHK_OUT_40,this);
	m_chkOut40.SetIcon(IDI_LEDON,IDI_LEDOFF);

	m_chkOut41.SubclassDlgItem(IDC_CHK_OUT_41,this);
	m_chkOut41.SetIcon(IDI_LEDON,IDI_LEDOFF);

	m_chkOut42.SubclassDlgItem(IDC_CHK_OUT_42,this);
	m_chkOut42.SetIcon(IDI_LEDON,IDI_LEDOFF);

	m_chkOut43.SubclassDlgItem(IDC_CHK_OUT_43,this);
	m_chkOut43.SetIcon(IDI_LEDON,IDI_LEDOFF);

	m_chkOut44.SubclassDlgItem(IDC_CHK_OUT_44,this);
	m_chkOut44.SetIcon(IDI_LEDON,IDI_LEDOFF);

	m_chkOut45.SubclassDlgItem(IDC_CHK_OUT_45,this);
	m_chkOut45.SetIcon(IDI_LEDON,IDI_LEDOFF);

	m_chkOut46.SubclassDlgItem(IDC_CHK_OUT_46,this);
	m_chkOut46.SetIcon(IDI_LEDON,IDI_LEDOFF);

	m_chkOut47.SubclassDlgItem(IDC_CHK_OUT_47,this);
	m_chkOut47.SetIcon(IDI_LEDON,IDI_LEDOFF);

	m_chkOut48.SubclassDlgItem(IDC_CHK_OUT_48,this);
	m_chkOut48.SetIcon(IDI_LEDON,IDI_LEDOFF);

	m_chkOut49.SubclassDlgItem(IDC_CHK_OUT_49,this);
	m_chkOut49.SetIcon(IDI_LEDON,IDI_LEDOFF);

	m_chkOut50.SubclassDlgItem(IDC_CHK_OUT_50,this);
	m_chkOut50.SetIcon(IDI_LEDON,IDI_LEDOFF);

	return 0;
}

/*--------------------------------------------------------
1	激光气体保护阀打开			2	镜头隔离气打开
3	左平台真空吸附				4	左平台真空释放
5	左测厚气缸上升				6	切换至长光路
7	激光预热阀打开				8	吸板风机上电
9	右平台真空吸附				10	右平台真空释放
11	右测厚气缸上升				12	探头清洁气打开
13	平台夹钳打开				14	切换至TOPHAT

20	红指示灯亮					21	绿指示灯亮
22	报警蜂鸣					23	X轴电机报警清除
24	Y轴电机报警清除				25	Z1轴电机报警清除
26	Z2轴电机报警清除			27	BET主动轴电机报警清除
28	BET从动轴电机报警清除

40	平台取料完成				41	下料准备
42	开始运行					43	左侧加工失败
44	右侧加工失败				45	可以上料
46	可以下料					47	上下料整体回零
48	结束运行					49	再次加板
---------------------------------------------------------*/

void CSignalOutView::OnOutput1Click() 
{
	UpdateData();
#ifndef IO_C//ly add 20110118
	GetControl().ChannelOutput(OLASERPROTECTGAS , m_chkOut1.GetCheck()==MIO_ON);//激光预热电磁阀
#endif
}
void CSignalOutView::OnOutput2Click() 
{
	UpdateData();
	GetControl().ChannelOutput(OTHETALENSPROTECT , m_chkOut2.GetCheck()==MIO_ON);    //激光快门电磁阀1
}
void CSignalOutView::OnOutput3Click() 
{
	UpdateData();
	GetControl().ChannelOutput(OTABLEVACUUMVALVE1 , m_chkOut3.GetCheck()==MIO_ON);    //激光快门电磁阀2
}
void CSignalOutView::OnOutput4Click() 
{
	UpdateData();
	GetControl().ChannelOutput(OTABLEVACUUMVALVERE1, m_chkOut4.GetCheck()==MIO_ON);    //激光隔离保护电磁阀1
}
void CSignalOutView::OnOutput5Click() 
{
	UpdateData();
	GetControl().ChannelOutput(OTESTTHICKNESSN1 , m_chkOut5.GetCheck()==MIO_ON);    //激光隔离保护电磁阀2	
}
void CSignalOutView::OnOutput6Click() 
{
	UpdateData();

	GetControl().ChannelOutput(OLASERSHUTTER1 , m_chkOut6.GetCheck()==MIO_ON);    ///测厚气缸
}
void CSignalOutView::OnOutput7Click() 
{
#ifndef IO_C
	UpdateData();
	GetControl().ChannelOutput(OLASERWARNUP  , m_chkOut7.GetCheck()==MIO_ON);    //激光功率测量清洁电磁阀	
#endif
}
void CSignalOutView::OnOutput8Click() 
{
	UpdateData();
	GetControl().ChannelOutput(OFANPOWERON, m_chkOut8.GetCheck()==MIO_ON);
}
void CSignalOutView::OnOutput9Click() 
{
	UpdateData();
	GetControl().ChannelOutput(OTABLEVACUUMVALVE2,m_chkOut9.GetCheck()==MIO_ON);   	
}
void CSignalOutView::OnOutput10Click() 
{
	UpdateData();
	GetControl().ChannelOutput(OTABLEVACUUMVALVERE2, m_chkOut10.GetCheck()==MIO_ON);
}
void CSignalOutView::OnOutput11Click() 
{
	UpdateData();
	GetControl().ChannelOutput(OTESTTHICKNESSN2 , m_chkOut11.GetCheck()==MIO_ON);  
}
void CSignalOutView::OnOutput12Click() 
{
	UpdateData();
	GetControl().ChannelOutput(OLASERPOWERCLEANER , m_chkOut12.GetCheck()==MIO_ON);    
}
/*
void CSignalOutView::OnOutput13Click() 
{
	UpdateData();
//	GetControl().ChannelOutput(OLOADSHACKE , m_chkOut13.GetCheck()==MIO_ON);    
	GetControl().ChannelOutput(OHOMEALL, m_chkOut13.GetCheck()==MIO_ON);

}
void CSignalOutView::OnOutput14Click() 
{
	UpdateData();
//	GetControl().ChannelOutput(OLOADVACUUMCHRIGHT , m_chkOut14.GetCheck()==MIO_ON);
	GetControl().ChannelOutput(OUNLOARDMOVETOTABLE, m_chkOut14.GetCheck()==MIO_ON);
}
void CSignalOutView::OnOutput15Click() 
{
	UpdateData();
	//GetControl().ChannelOutput(OLOADVACUUMCHLEFT , m_chkOut15.GetCheck()==MIO_ON);    
	GetControl().ChannelOutput(OLEFTERRO , m_chkOut15.GetCheck()==MIO_ON);
}

//第三块运动卡
void CSignalOutView::OnOutput16Click() 
{
	UpdateData();
	GetControl().ChannelOutput(OUNLOADVACUUMCHLEFT , m_chkOut16.GetCheck()==MIO_ON);    

}
void CSignalOutView::OnOutput17Click() 
{
	UpdateData();
	GetControl().ChannelOutput(OUNLOADVACUUMCHRIGHT , m_chkOut17.GetCheck()==MIO_ON);    

}
void CSignalOutView::OnOutput18Click() 
{
	UpdateData();
	GetControl().ChannelOutput(OUNLOADUPLEFT , m_chkOut18.GetCheck()==MIO_OFF);  
	GetControl().ChannelOutput(OUNLOADDOWNLEFT , m_chkOut18.GetCheck()==MIO_OFF); 


}
void CSignalOutView::OnOutput19Click() 
{
	UpdateData();
//	GetControl().ChannelOutput(OUNLOADDOWNRIGHT , m_chkOut19.GetCheck()==MIO_ON);    
	GetControl().ChannelOutput(RELOADBOARD , m_chkOut19.GetCheck()==MIO_ON);
}
*/

void CSignalOutView::OnOutput20Click() 
{
	UpdateData();
	GetControl().ChannelOutput(OLAMPREDON , m_chkOut20.GetCheck()==MIO_ON); 
	GetControl().ChannelOutput(OLAMPGREENON , IO_OFF);
}
void CSignalOutView::OnOutput21Click() 
{
	UpdateData();
	GetControl().ChannelOutput(OLAMPGREENON , m_chkOut21.GetCheck()==MIO_ON);    
}
void CSignalOutView::OnChkOut22Click() 
{
	UpdateData();
	GetControl().ChannelOutput(OCOMMONALARM , m_chkOut22.GetCheck()==MIO_ON); 	
}
void CSignalOutView::OnChkOut23Click() 
{
	UpdateData();
	GetControl().ChannelOutput(OSERVOALRAMCLEAR1 , m_chkOut23.GetCheck()==MIO_ON); 	
}
void CSignalOutView::OnOutput24Click() 
{
	UpdateData();
	GetControl().ChannelOutput(OSERVOALRAMCLEAR2 , m_chkOut24.GetCheck()==MIO_ON);    
}
void CSignalOutView::OnOutput25Click() 
{
	UpdateData();
	GetControl().ChannelOutput(OSERVOALRAMCLEAR3 , m_chkOut25.GetCheck()==MIO_ON);    
}
void CSignalOutView::OnOutput26Click() 
{
	UpdateData();
	GetControl().ChannelOutput(OSERVOALRAMCLEAR4 , m_chkOut26.GetCheck()==MIO_ON);    
}
void CSignalOutView::OnOutput27Click() //主动轴
{
	UpdateData();
	GetControl().ChannelOutput(OSERVOALRAMCLEAR6 , m_chkOut27.GetCheck()==MIO_ON);
}
void CSignalOutView::OnOutput28Click() //从动轴
{
	UpdateData();
	GetControl().ChannelOutput(OSERVOALRAMCLEAR5 , m_chkOut28.GetCheck()==MIO_ON);    
}
/*
void CSignalOutView::OnOutput32Click() 
{
		UpdateData();
	GetControl().ChannelOutput(OTABLEVACUUMVALVE1 , m_chkOut32.GetCheck() == MIO_ON);   
}

void CSignalOutView::OnOutput33Click() 
{
		UpdateData();
//	GetControl().ChannelOutput(OTABLEVACUUMVALVE2 , m_chkOut21.GetCheck()==0);    
}

void CSignalOutView::OnOutput34Click() 
{
 UpdateData();
	//	GetControl().ChannelOutput(OLOADDOLLYLOCK , m_chkOut34.GetCheck() == MIO_ON);  
	GetControl().ChannelOutput(OPROCEXIT , m_chkOut34.GetCheck() == MIO_ON); 		
}

void CSignalOutView::OnOutput35Click() 
{
	GetControl().ChannelOutput(OUNLOADDOLLYLOCK , m_chkOut35.GetCheck() == MIO_ON); 
}
*/

void CSignalOutView::OnChkOut40Click() 
{
	UpdateData();
	GetControl().ChannelOutput(OSORBOK , m_chkOut40.GetCheck()==MIO_ON);  	
}

void CSignalOutView::OnChkOut41Click() 
{
	UpdateData();
	GetControl().ChannelOutput(OUNLOARDMOVETOTABLE , m_chkOut41.GetCheck()==MIO_ON);  	
}

void CSignalOutView::OnChkOut42Click() 
{
	UpdateData();
	GetControl().ChannelOutput(OAOTUBIGN , m_chkOut42.GetCheck()==MIO_ON);  	
}

void CSignalOutView::OnChkOut43Click() 
{
	UpdateData();
	GetControl().ChannelOutput(OLEFTERRO , m_chkOut43.GetCheck()==MIO_ON);  	
}

void CSignalOutView::OnChkOut44Click() 
{
	UpdateData();
	GetControl().ChannelOutput(ORIGHTERRO , m_chkOut44.GetCheck()==MIO_ON);  	
}

void CSignalOutView::OnChkOut45Click() 
{
	UpdateData();
	GetControl().ChannelOutput(OLOARDBORD , m_chkOut45.GetCheck()==MIO_ON);  	
}

void CSignalOutView::OnChkOut46Click() 
{
	UpdateData();
	GetControl().ChannelOutput(OUNLAORDBORD , m_chkOut46.GetCheck()==MIO_ON);  	
}

void CSignalOutView::OnChkOut47Click() 
{
	UpdateData();
	GetControl().ChannelOutput(OHOMEALL , m_chkOut47.GetCheck()==MIO_ON);  	
}

void CSignalOutView::OnChkOut48Click() 
{
	UpdateData();
	GetControl().ChannelOutput(OPROCEXIT , m_chkOut48.GetCheck()==MIO_ON);  	
}

void CSignalOutView::OnChkOut49Click() 
{
	UpdateData();
	GetControl().ChannelOutput(RELOADBOARD , m_chkOut49.GetCheck()==MIO_ON);  	
}

void CSignalOutView::SetUI()//ly add 20110318
{
	char szRead[40] = {""};
	GetLang().GetUIText("SignalOut","IDC_STATIC1",szRead,40);
	SetDlgItemText(IDC_STATIC1,szRead);
	GetLang().GetUIText("SignalOut","IDC_CHK_OUT_1",szRead,40);
	SetDlgItemText(IDC_CHK_OUT_1,szRead);
	GetLang().GetUIText("SignalOut","IDC_CHK_OUT_7",szRead,40);
	SetDlgItemText(IDC_CHK_OUT_7,szRead);
	GetLang().GetUIText("SignalOut","IDC_CHK_OUT_2",szRead,40);
	SetDlgItemText(IDC_CHK_OUT_2,szRead);
	GetLang().GetUIText("SignalOut","IDC_CHK_OUT_8",szRead,40);
	SetDlgItemText(IDC_CHK_OUT_8,szRead);
	GetLang().GetUIText("SignalOut","IDC_CHK_OUT_3",szRead,40);
	SetDlgItemText(IDC_CHK_OUT_3,szRead);
	GetLang().GetUIText("SignalOut","IDC_CHK_OUT_9",szRead,40);
	SetDlgItemText(IDC_CHK_OUT_9,szRead);
	GetLang().GetUIText("SignalOut","IDC_CHK_OUT_4",szRead,40);
	SetDlgItemText(IDC_CHK_OUT_4,szRead);
	GetLang().GetUIText("SignalOut","IDC_CHK_OUT_10",szRead,40);
	SetDlgItemText(IDC_CHK_OUT_10,szRead);
	GetLang().GetUIText("SignalOut","IDC_CHK_OUT_5",szRead,40);
	SetDlgItemText(IDC_CHK_OUT_5,szRead);
	GetLang().GetUIText("SignalOut","IDC_CHK_OUT_11",szRead,40);
	SetDlgItemText(IDC_CHK_OUT_11,szRead);
	GetLang().GetUIText("SignalOut","IDC_CHK_OUT_6",szRead,40);
	SetDlgItemText(IDC_CHK_OUT_6,szRead);
	GetLang().GetUIText("SignalOut","IDC_CHK_OUT_12",szRead,40);
	SetDlgItemText(IDC_CHK_OUT_12,szRead);
	GetLang().GetUIText("SignalOut","IDC_CHK_OUT_13",szRead,40);
	SetDlgItemText(IDC_CHK_OUT_13,szRead);
	GetLang().GetUIText("SignalOut","IDC_CHK_OUT_14",szRead,40);
	SetDlgItemText(IDC_CHK_OUT_14,szRead);
	GetLang().GetUIText("SignalOut","IDC_STATIC2",szRead,40);
	SetDlgItemText(IDC_STATIC2,szRead);
	GetLang().GetUIText("SignalOut","IDC_CHK_OUT_20",szRead,40);
	SetDlgItemText(IDC_CHK_OUT_20,szRead);
	GetLang().GetUIText("SignalOut","IDC_CHK_OUT_21",szRead,40);
	SetDlgItemText(IDC_CHK_OUT_21,szRead);
	GetLang().GetUIText("SignalOut","IDC_CHK_OUT_22",szRead,40);
	SetDlgItemText(IDC_CHK_OUT_22,szRead);
	GetLang().GetUIText("SignalOut","IDC_CHK_OUT_23",szRead,40);
	SetDlgItemText(IDC_CHK_OUT_23,szRead);
	GetLang().GetUIText("SignalOut","IDC_CHK_OUT_24",szRead,40);
	SetDlgItemText(IDC_CHK_OUT_24,szRead);
	GetLang().GetUIText("SignalOut","IDC_CHK_OUT_25",szRead,40);
	SetDlgItemText(IDC_CHK_OUT_25,szRead);
	GetLang().GetUIText("SignalOut","IDC_CHK_OUT_26",szRead,40);
	SetDlgItemText(IDC_CHK_OUT_26,szRead);
	GetLang().GetUIText("SignalOut","IDC_CHK_OUT_27",szRead,40);
	SetDlgItemText(IDC_CHK_OUT_27,szRead);
	GetLang().GetUIText("SignalOut","IDC_CHK_OUT_28",szRead,40);
	SetDlgItemText(IDC_CHK_OUT_28,szRead);
	GetLang().GetUIText("SignalOut","IDC_STATIC3",szRead,40);
	SetDlgItemText(IDC_STATIC3,szRead);
	GetLang().GetUIText("SignalOut","IDC_CHK_OUT_40",szRead,40);
	SetDlgItemText(IDC_CHK_OUT_40,szRead);
	GetLang().GetUIText("SignalOut","IDC_CHK_OUT_41",szRead,40);
	SetDlgItemText(IDC_CHK_OUT_41,szRead);
	GetLang().GetUIText("SignalOut","IDC_CHK_OUT_42",szRead,40);
	SetDlgItemText(IDC_CHK_OUT_42,szRead);
	GetLang().GetUIText("SignalOut","IDC_CHK_OUT_43",szRead,40);
	SetDlgItemText(IDC_CHK_OUT_43,szRead);
	GetLang().GetUIText("SignalOut","IDC_CHK_OUT_44",szRead,40);
	SetDlgItemText(IDC_CHK_OUT_44,szRead);
	GetLang().GetUIText("SignalOut","IDC_CHK_OUT_45",szRead,40);
	SetDlgItemText(IDC_CHK_OUT_45,szRead);
	GetLang().GetUIText("SignalOut","IDC_CHK_OUT_46",szRead,40);
	SetDlgItemText(IDC_CHK_OUT_46,szRead);
	GetLang().GetUIText("SignalOut","IDC_CHK_OUT_47",szRead,40);
	SetDlgItemText(IDC_CHK_OUT_47,szRead);
	GetLang().GetUIText("SignalOut","IDC_CHK_OUT_48",szRead,40);
	SetDlgItemText(IDC_CHK_OUT_48,szRead);
	GetLang().GetUIText("SignalOut","IDC_CHK_OUT_49",szRead,40);
	SetDlgItemText(IDC_CHK_OUT_49,szRead);
}

void CSignalOutView::OnInitialUpdate() 
{
	TVisualFormView::OnInitialUpdate();
	if(GetLang().GetCurLanguage()==1)
		SetUI();
	
//	m_chkOut25.SetCheck(TRUE);
//	m_chkOut24.SetCheck(TRUE);	

//	m_chkOut27.SetCheck(TRUE);
//	m_chkOut26.SetCheck(TRUE);
//
//	m_chkOut32.SetCheck(TRUE);
//	m_chkOut33.SetCheck(TRUE);

}

void CSignalOutView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	time_t start_time, end_time;
	char ez[256]={""};//ly 20110405
	if(!bActivate)
	{
#ifdef USEIOCARD
#ifdef USECOM
		GetControl().ChannelOutput(OTESTTHICKNESSN1,MIO_OFF);
		
		start_time = time( NULL );
		while(GetControl().QueryIOBit(ITHICKNESS1N))
		{	
			end_time = time( NULL );
			if( difftime(end_time, start_time)>6 )
			{
#ifndef LESSWARN
				strncpy(ez,GetLang().GetWarningText(41041),256);
				AfxMessageBox(ez);//"左侧测厚气缸上升未到位，请检查!"
#endif
				break;
			}
		}
		
		GetControl().ChannelOutput(OTESTTHICKNESSN2,MIO_OFF);
		
		start_time = time( NULL );
		while(GetControl().QueryIOBit(ITHICKNESS2N))
		{	
			end_time = time( NULL );
			if( difftime(end_time, start_time)>6 )
			{
#ifndef LESSWARN
				strncpy(ez,GetLang().GetWarningText(41042),256);
				AfxMessageBox(ez);//"右侧测厚气缸上升未到位，请检查!"
#endif
				break;
			}
		}
		
		if(GetDoc().GetTechnicType())
		{
			GetControl().ChannelOutput(OLASERSHUTTER1,MIO_ON);
			
			start_time = time( NULL );
			while(LSPATH_CHECKING &&( GetControl().QueryIOBit(ILASERSHUTTERLTP)||GetControl().QueryIOBit(ILASERSHUTTERRTP)))
			{	
				end_time = time( NULL );
				if( difftime(end_time, start_time)>5 )
				{
#ifndef LESSWARN
					strncpy(ez,GetLang().GetWarningText(41002),256);
					AfxMessageBox(ez);//"未能切换到长光路，请检查!"
#endif
#ifdef USELOG
					GetLog().Append_pro(10007,20008);//"未能切换到长光路!","光路切换"
#endif
					break;
				}
			}	
		}
		else
		{	
			GetControl().ChannelOutput(OLASERSHUTTER1,MIO_OFF);
			
			start_time = time( NULL );
			while(LSPATH_CHECKING &&( GetControl().QueryIOBit(ILASERSHUTTERLTN)||GetControl().QueryIOBit(ILASERSHUTTERRTN)))
			{	
				end_time = time( NULL );
				if( difftime(end_time, start_time)>5 )
				{
#ifndef LESSWARN
					strncpy(ez,GetLang().GetWarningText(41001),256);
					AfxMessageBox(ez);//"未能切换到短光路，请检查!"
#endif
#ifdef USELOG
					GetLog().Append_pro(10006,20008);//"未能切换到短光路!","光路切换"
#endif
					break;
				}
			}
		}
#endif
#endif	
		if(GetDoc().GetLaserPowerState())
		{
#ifndef IO_C//ly add 20110118
			GetControl().ChannelOutput(OLASERPROTECTGAS,MIO_ON);
			GetControl().ChannelOutput(OLASERWARNUP,MIO_ON); 
			
			start_time = time( NULL );
			while(GetControl().QueryIOBit(ILASERWARMUPN))
			{	
				end_time = time( NULL );
				if( difftime(end_time, start_time)>5 )
				{
#ifndef LESSWARN
					strncpy(ez,GetLang().GetWarningText(41015),256);
					AfxMessageBox(ez);//"激光预热快门未能打开，请检查!"
#endif
					break;
				}
			}
#endif
		}
		else
		{
#ifndef IO_C//ly add 20110118
			GetControl().ChannelOutput(OLASERPROTECTGAS,MIO_OFF);
			GetControl().ChannelOutput(OLASERWARNUP,MIO_OFF);

			start_time = time( NULL );
			while(GetControl().QueryIOBit(ILASERWARMUPP))
			{	
				end_time = time( NULL );
				if( difftime(end_time, start_time)>5 )
				{
#ifndef LESSWARN
					strncpy(ez,GetLang().GetWarningText(41016),256);
					AfxMessageBox(ez);//"激光预热快门未能关闭，请检查!"
#endif
					break;
				}
			}
#endif
		}		
	}
	else
	{
		int nLevel = GetDoc().GetCurUserLevel();
		if(nLevel==SystemDoc::PRIMARY)//初级
		{
			GetDlgItem(IDC_CHK_OUT_1)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHK_OUT_2)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHK_OUT_3)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHK_OUT_4)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHK_OUT_5)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHK_OUT_6)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHK_OUT_7)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHK_OUT_8)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHK_OUT_9)->EnableWindow(FALSE);				
			GetDlgItem(IDC_CHK_OUT_10)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHK_OUT_11)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHK_OUT_12)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHK_OUT_13)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHK_OUT_14)->EnableWindow(FALSE);

			GetDlgItem(IDC_CHK_OUT_20)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHK_OUT_21)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHK_OUT_22)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHK_OUT_23)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHK_OUT_24)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHK_OUT_25)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHK_OUT_26)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHK_OUT_27)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHK_OUT_28)->EnableWindow(FALSE);

			GetDlgItem(IDC_CHK_OUT_40)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHK_OUT_41)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHK_OUT_42)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHK_OUT_43)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHK_OUT_44)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHK_OUT_45)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHK_OUT_46)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHK_OUT_47)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHK_OUT_48)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHK_OUT_49)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHK_OUT_50)->EnableWindow(FALSE);
		}
		else if(nLevel==SystemDoc::SUPEROR)//高级
		{
			GetDlgItem(IDC_CHK_OUT_1)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_2)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_3)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_4)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_5)->EnableWindow(TRUE);			
			if(LSPATH_CHECKING==0)
			{
				GetDlgItem(IDC_CHK_OUT_6)->EnableWindow(FALSE);
			}
			else
			{
				GetDlgItem(IDC_CHK_OUT_6)->EnableWindow(TRUE);
			}
			GetDlgItem(IDC_CHK_OUT_7)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_8)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_9)->EnableWindow(TRUE);				
			GetDlgItem(IDC_CHK_OUT_10)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_11)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_12)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_13)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_14)->EnableWindow(TRUE);

			GetDlgItem(IDC_CHK_OUT_20)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_21)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_22)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_23)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_24)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_25)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_26)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_27)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_28)->EnableWindow(TRUE);

			GetDlgItem(IDC_CHK_OUT_40)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_41)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_42)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_43)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_44)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_45)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_46)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_47)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_48)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_49)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_50)->EnableWindow(TRUE);
		}
	    else //系统
		{
			GetDlgItem(IDC_CHK_OUT_1)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_2)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_3)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_4)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_5)->EnableWindow(TRUE);			
			if(LSPATH_CHECKING==0)
			{
				GetDlgItem(IDC_CHK_OUT_6)->EnableWindow(FALSE);
			}
			else
			{
				GetDlgItem(IDC_CHK_OUT_6)->EnableWindow(TRUE);
			}
			GetDlgItem(IDC_CHK_OUT_7)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_8)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_9)->EnableWindow(TRUE);				
			GetDlgItem(IDC_CHK_OUT_10)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_11)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_12)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_13)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_14)->EnableWindow(TRUE);

			GetDlgItem(IDC_CHK_OUT_20)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_21)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_22)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_23)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_24)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_25)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_26)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_27)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_28)->EnableWindow(TRUE);

			GetDlgItem(IDC_CHK_OUT_40)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_41)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_42)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_43)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_44)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_45)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_46)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_47)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_48)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_49)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHK_OUT_50)->EnableWindow(TRUE);
		}
		
	}
	TVisualFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CSignalOutView::OnChkOut13Click() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
#ifdef IO_C
	GetControl().ChannelOutput(OTABLECLAMP , m_chkOut13.GetCheck()==IO_ON);
#else
	GetControl().ChannelOutput(OTABLECLAMP , m_chkOut13.GetCheck()==IO_OFF);
#endif
}

void CSignalOutView::OnChkOut14Click() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	GetControl().ChannelOutput(OLASERSHUTTER2 , m_chkOut14.GetCheck()==IO_ON);	
}

void CSignalOutView::OnChkOut50() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	GetControl().ChannelOutput(STOPMOVE , m_chkOut50.GetCheck()==MIO_ON);  	
}
