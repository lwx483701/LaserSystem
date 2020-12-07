// OperateRefCoord.cpp : implementation file
//

#include "stdafx.h"
#include "lasersystem.h"
#include "OperateRefCoord.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COperateRefCoord

IMPLEMENT_DYNCREATE(COperateRefCoord, TVisualFormView)

COperateRefCoord::COperateRefCoord()
	: TVisualFormView(COperateRefCoord::IDD)
{
	//{{AFX_DATA_INIT(COperateRefCoord)
	m_lLaserPowerZ = 0;
	m_lLaserPowerY = 0;
	m_lLaserPowerX = 0;
	m_lTabLoadX = 0;
	m_lTabLoadY = 0;
	m_lTabUnloadX = 0;
	m_lTabUnloadY = 0;
	m_lTestThickness = 0;
	m_lLaserCleanX = 0;
	m_lLaserCleanY = 0;
	m_lAptOffset = 0;
	m_lBETOffset = 0;
	m_lCCDDistancePosX = 0;
	m_lCCDDistancePosY = 0;
	m_lCCDBoardThick = 0;
	m_lGalvoBoardThick = 0;
	m_lThicknessX = 0;
	m_lThicknessY = 0;
	m_lBETPriOffset = 0;
	m_lGlvAdjPosX = 0;
	m_lGlvAdjPosY = 0;
	m_SysOperate = false;
	//}}AFX_DATA_INIT
}

COperateRefCoord::~COperateRefCoord()
{
}

void COperateRefCoord::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COperateRefCoord)
	DDX_Control(pDX, IDC_CHECK_OVERBSELECT, m_ButtonSelectOverBorad);
	DDX_Control(pDX, IDC_CCDBOARDTHICK, m_edtCCDBoardThick);
	DDX_Control(pDX, IDC_GALVOBOARDTHICK, m_edtGalvoBoardThick);
	DDX_Control(pDX, IDC_CCDDISTANCEPOSY, m_edtCCDDistancePosY);
	DDX_Control(pDX, IDC_CCDDISTANCEPOSX, m_edtCCDDistancePosX);
	DDX_Control(pDX, IDC_EDT_GLVADJPOSY, m_edtGlvAdjPosY);
	DDX_Control(pDX, IDC_EDT_GLVADJPOSX, m_edtGlvAdjPosX);
	DDX_Control(pDX, IDC_EDT_BETPRIOFFSET, m_edtBETPriOffset);
	DDX_Control(pDX, IDC_EDT_THICKNESSY, m_edtThicknessY);
	DDX_Control(pDX, IDC_EDT_THICKNESSX, m_edtThicknessX);
	DDX_Control(pDX, IDC_EDT_BETOFFSET, m_edtBETOffset);
	DDX_Control(pDX, IDC_EDT_APTOFFSET, m_edtAptOffset);
	DDX_Control(pDX, IDC_BT_RESETTESTP, m_btnReset);
	DDX_Control(pDX, IDC_BT_SETTESTP, m_btnSet);
	DDX_Control(pDX, IDC_BT_SAVE, m_btnSave);
	DDX_Control(pDX, IDC_EDT_LASERCLEANX, m_edtLaserCleanX);
	DDX_Control(pDX, IDC_EDT_LASERCLEANY, m_edtLaserCleanY);
	DDX_Control(pDX, IDC_EDT_THICKNESS, m_edtThickness);
	DDX_Control(pDX, IDC_EDT_TABUNLOADY, m_edtTabUnloadY);
	DDX_Control(pDX, IDC_EDT_TABUNLOADX, m_edtTabUnloadX);
	DDX_Control(pDX, IDC_EDT_TABLOADY, m_edtTabLoadY);
	DDX_Control(pDX, IDC_EDT_TABLOADX, m_edtTabLoadX);
	DDX_Control(pDX, IDC_CMB_SCANHEAD, m_cmbScanHead);
	DDX_Control(pDX, IDC_EDT_LASERPOWERX, m_edtLaserPowerX);
	DDX_Control(pDX, IDC_EDT_LASERPOWERY, m_edtLaserPowerY);
	DDX_Control(pDX, IDC_EDT_LASERPOWERZ, m_edtLaserPowerZ);
	DDX_Text(pDX, IDC_EDT_LASERPOWERZ, m_lLaserPowerZ);
	DDX_Text(pDX, IDC_EDT_LASERPOWERY, m_lLaserPowerY);
	DDX_Text(pDX, IDC_EDT_LASERPOWERX, m_lLaserPowerX);
	DDX_Text(pDX, IDC_EDT_TABLOADX, m_lTabLoadX);
	DDX_Text(pDX, IDC_EDT_TABLOADY, m_lTabLoadY);
	DDX_Text(pDX, IDC_EDT_TABUNLOADX, m_lTabUnloadX);
	DDX_Text(pDX, IDC_EDT_TABUNLOADY, m_lTabUnloadY);
	DDX_Text(pDX, IDC_EDT_THICKNESS, m_lTestThickness);
	DDX_Text(pDX, IDC_EDT_LASERCLEANX, m_lLaserCleanX);
	DDX_Text(pDX, IDC_EDT_LASERCLEANY, m_lLaserCleanY);
	DDX_Text(pDX, IDC_EDT_APTOFFSET, m_lAptOffset);
	DDX_Text(pDX, IDC_EDT_BETOFFSET, m_lBETOffset);
	DDX_Text(pDX, IDC_CCDDISTANCEPOSX, m_lCCDDistancePosX);
	DDX_Text(pDX, IDC_CCDDISTANCEPOSY, m_lCCDDistancePosY);
	DDX_Text(pDX, IDC_CCDBOARDTHICK, m_lCCDBoardThick);
	DDX_Text(pDX, IDC_GALVOBOARDTHICK, m_lGalvoBoardThick);
	DDX_Text(pDX, IDC_EDT_THICKNESSX, m_lThicknessX);
	DDX_Text(pDX, IDC_EDT_THICKNESSY, m_lThicknessY);
	DDX_Text(pDX, IDC_EDT_BETPRIOFFSET, m_lBETPriOffset);
	DDX_Text(pDX, IDC_EDT_GLVADJPOSX, m_lGlvAdjPosX);
	DDX_Text(pDX, IDC_EDT_GLVADJPOSY, m_lGlvAdjPosY);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COperateRefCoord, TVisualFormView)
	//{{AFX_MSG_MAP(COperateRefCoord)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BT_RESETTESTP, OnResetTestPara)
	ON_BN_CLICKED(IDC_BT_SETTESTP, OnSetTestPara)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_CMB_SCANHEAD, OnSelchangeCmbScanhead)
	ON_CBN_DROPDOWN(IDC_CMB_SCANHEAD, OnDropdownCmbScanhead)
	ON_BN_CLICKED(IDC_BT_SAVE, OnSave)
	ON_BN_CLICKED(IDC_CHECK_OVERBSELECT, OnCheckOverbselect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COperateRefCoord diagnostics

#ifdef _DEBUG
void COperateRefCoord::AssertValid() const
{
	CFormView::AssertValid();
}

void COperateRefCoord::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COperateRefCoord message handlers

int COperateRefCoord::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (TVisualFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
//	m_btnReset.SubclassDlgItem(IDC_BT_RESETTESTP,this);
	m_btnReset.SetIcon(IDI_RESET,IDI_RESET);

//	m_btnSet.SubclassDlgItem(IDC_BT_SETTESTP,this);
	m_btnSet.SetIcon(IDI_SET,IDI_SET);


//	m_btnSave.SubclassDlgItem(IDC_BT_SAVE,this);
	m_btnSave.SetIcon(IDI_SAVEP,IDI_SAVEP);


//	m_edtLoadBenchMark.SetParseType  (SES_NUMBERS|SES_SIGNED);
//	m_edtLoadPitchPos.SetParseType   (SES_NUMBERS|SES_SIGNED); 
//	m_edtUnloadPitchPos.SetParseType (SES_NUMBERS|SES_SIGNED); 
//	m_edtUnloadBenchMark.SetParseType(SES_NUMBERS|SES_SIGNED);
//	m_edtLoadLiftBM.SetParseType     (SES_NUMBERS|SES_SIGNED);
//	m_edtUnloadLiftBM.SetParseType   (SES_NUMBERS|SES_SIGNED);
//	m_edtLoadTransPos.SetParseType   (SES_NUMBERS);
//	m_edtUnloadTransPos.SetParseType (SES_NUMBERS);

//	m_lLoadPitchPos    = GetDoc().GetLoadPitchPos();   
//	m_lLoadBenchmark   = GetDoc().GetLoadBenchMarkPos();
//	m_lUnloadPitchPos  = GetDoc().GetUnloadPitchPos();
//	m_lUnloadBenchmark = GetDoc().GetUnloadBenchMarkPos();
//	m_lLoadLiftBM	   = GetDoc().GetLoadLiftBMPos();	
//	m_lUnloadLiftBM	   = GetDoc().GetUnloadLiftBMPos();
//    m_ulLoadTransPos   = GetDoc().GetLoadTransPos();
//    m_ulUnloadTransPos = GetDoc().GetUnloadTransPos();
//	m_ulLoadTunePos = GetDoc().GetLoadTunePos();
//	m_ulUnLoadTunePos = GetDoc().GetUnLoadTunePos();

//	m_edtCCDToGlvOffX.SetParseType (SES_NUMBERS | SES_SIGNED);
//	m_edtCCDToGlvOffY.SetParseType (SES_NUMBERS | SES_SIGNED);
//	m_edtCCDToGlvOffZ.SetParseType (SES_NUMBERS | SES_SIGNED);  
//    m_edtCCDToGlvOffLongZ.SetParseType (SES_NUMBERS | SES_SIGNED);
	m_edtLaserPowerX.SetParseType  (SES_NUMBERS | SES_SIGNED);
	m_edtLaserPowerY.SetParseType  (SES_NUMBERS | SES_SIGNED);
	m_edtLaserPowerY.SetParseType  (SES_NUMBERS | SES_SIGNED);
 

	m_lCCDDistancePosX = GetDoc().GetCCDToCCDTestOffset(0).x;
	m_lCCDDistancePosY = GetDoc().GetCCDToCCDTestOffset(0).y;
//	m_lCCDToGlvOffX = GetDoc().GetCCDToGlvTestOffset(0).x;
//	m_lCCDToGlvOffY = GetDoc().GetCCDToGlvTestOffset(0).y;
//	m_lCCDToGlvOffZ = GetDoc().GetCCDToGlvTestOffset(0).z;
//	m_lCCDToGlvOffLongZ = GetDoc().GetLongPathCCDToGlvTestOffset(0).z;
	m_lLaserPowerX = GetDoc().GetLaserPowerTestCrd(0).x;
	m_lLaserPowerY = GetDoc().GetLaserPowerTestCrd(0).y;
	m_lLaserPowerZ = GetDoc().GetLaserPowerTestCrd(0).z;
	
	//平台
	m_edtTabLoadX.SetParseType   (SES_NUMBERS | SES_SIGNED);
	m_edtTabLoadY.SetParseType   (SES_NUMBERS | SES_SIGNED);
	m_edtTabUnloadX.SetParseType (SES_NUMBERS | SES_SIGNED);
	m_edtTabUnloadY.SetParseType (SES_NUMBERS | SES_SIGNED);
//	m_edtTabBenchmarkX.SetParseType (SES_NUMBERS | SES_SIGNED);
//	m_edtTabBenchmarkY.SetParseType (SES_NUMBERS | SES_SIGNED);
//    m_edtTabPitchDisX.SetParseType (SES_NUMBERS | SES_SIGNED);
//    m_edtTabPitchDisY.SetParseType (SES_NUMBERS | SES_SIGNED);
    m_edtThickness.SetParseType (SES_NUMBERS | SES_SIGNED);

	m_lTabLoadX = GetDoc().GetTabLoadPos().x;
	m_lTabLoadY = GetDoc().GetTabLoadPos().y;
	m_lTabUnloadX = GetDoc().GetTabUnloadPos().x;
	m_lTabUnloadY = GetDoc().GetTabUnloadPos().y;
//	m_lTabBenchmarkX = GetDoc().GetTabBenchmark().x;
//	m_lTabBenchmarkY = GetDoc().GetTabBenchmark().y;
//    m_lTabPitchDisX  = GetDoc().GetTabPitchDistanceXY().x;
//    m_lTabPitchDisY  = GetDoc().GetTabPitchDistanceXY().y;

//	m_ulPcbThickness = GetDoc().GetPCBThickness(); 
	m_lAptOffset = GetDoc().GetAptBenchmark();
	m_lBETPriOffset=GetDoc().GetBETPriOffset();
	m_lBETOffset = GetDoc().GetBETBenchmark();

	m_lTestThickness = GetDoc().GetTestThicknessPos();
	m_lLaserCleanX = GetDoc().GetLaserTestCleanRefPos().x;
	m_lLaserCleanY = GetDoc().GetLaserTestCleanRefPos().y;

	m_lCCDBoardThick = GetDoc().GetCCDBoardThick();
	m_lGalvoBoardThick = GetDoc().GetGalvoBoardThick();

	m_edtThicknessX.SetParseType   (SES_NUMBERS | SES_SIGNED);
	m_edtThicknessY.SetParseType   (SES_NUMBERS | SES_SIGNED);

	m_lThicknessX=GetDoc().GetThicknessX();
	m_lThicknessY=GetDoc().GetThicknessY();


	m_lGlvAdjPosX = GetDoc().GetGlvAdjPosX();
	m_lGlvAdjPosY = GetDoc().GetGlvAdjPosY();

	return 0;
}

void COperateRefCoord::OnDestroy() 
{
	TVisualFormView::OnDestroy();
	UpdateData();

//	GetDoc().SetLoadPitchPos(m_lLoadPitchPos);
//	GetDoc().SetUnLoadPitchPos(m_lUnloadPitchPos);
//	GetDoc().SetLoadBenchMarkPos(m_lLoadBenchmark);
//	GetDoc().SetUnLoadBenchMarkPos(m_lUnloadBenchmark);
//	GetDoc().SetLoadLiftBMPos(m_lLoadLiftBM);
//	GetDoc().SetUnloadLiftBMPos(m_lUnloadLiftBM);
   
//	GetDoc().SetLoadTransPos( m_ulLoadTransPos);
//	GetDoc().SetUnloadTransPos(m_ulUnloadTransPos);

//	GetDoc().SetTestAperture( m_cmbApt.GetCurSel()+1 );


	int nHead = m_cmbScanHead.GetCurSel();	
	Coord3D crd3d;
	Coord	crd;

//	crd3d.x = m_lCCDToGlvOffX;
//	crd3d.y = m_lCCDToGlvOffY;
//	crd3d.z = m_lCCDToGlvOffZ;
//	GetDoc().SetCCDToGlvTestOffset(crd3d,nHead);

//	crd3d.x = m_lCCDDistancePosX;
//	crd3d.y = m_lCCDDistancePosY;
//	crd3d.z = m_lCCDToGlvOffZ;
//	GetDoc().SetCCDToCCDTestOffset(crd3d,nHead);
//	crd3d.x = m_lCCDToGlvOffX;
//	crd3d.y = m_lCCDToGlvOffY;
//	crd3d.z = m_lCCDToGlvOffLongZ;
//	GetDoc().SetLongPathCCDToGlvTestOffset(crd3d,nHead);
	crd3d.x = m_lLaserPowerX;
	crd3d.y = m_lLaserPowerY;
	crd3d.z = m_lLaserPowerZ;
	GetDoc().SetLaserPowerTestCrd(crd3d,nHead);

	crd.x = m_lTabLoadX;
	crd.y = m_lTabLoadY;
	GetDoc().SetTabLoadPos(crd);

	crd.x = m_lTabUnloadX;
	crd.y = m_lTabUnloadY;
	GetDoc().SetTabUnloadPos(crd);

//	crd.x = m_lTabBenchmarkX;
//	crd.y = m_lTabBenchmarkY;
//	GetDoc().SetTabBenchmark(crd);

//	crd.x = m_lTabPitchDisX;
//	crd.y = m_lTabPitchDisY;
//	GetDoc().SetTabPitchDistanceXY(crd);
	GetDoc().SetTestThicknessPos(m_lTestThickness);

	/*
    GetDoc().SetAptBenchmark(m_lAptOffset);
	GetDoc().SetBETPriOffset(m_lBETPriOffset);
	GetDoc().SetBETBenchmark(m_lBETOffset);
	*/
#ifdef DOUBLEBET
//	int nHead = m_cmbScanHead.GetCurSel();
	if (nHead==1)
	{
		GetDoc().SetAptBenchmark2(m_lAptOffset);
		GetDoc().SetBETPriOffset2(m_lBETPriOffset);
		GetDoc().SetBETSubOffset2(m_lBETOffset);
	}
	else
	{
		GetDoc().SetAptBenchmark(m_lAptOffset);
		GetDoc().SetBETPriOffset(m_lBETPriOffset);
		GetDoc().SetBETBenchmark(m_lBETOffset);
	}
#else
	GetDoc().SetAptBenchmark(m_lAptOffset);
	GetDoc().SetBETPriOffset(m_lBETPriOffset);
	GetDoc().SetBETBenchmark(m_lBETOffset);
#endif

//    GetDoc().SetPCBThickness(m_ulPcbThickness);
	GetDoc().SetLaserTestCleanRefPos(Coord(m_lLaserCleanX,m_lLaserCleanY));
}

void COperateRefCoord::SetUI()//ly add 20110318
{
	char szRead[40] = {""};
	GetLang().GetUIText("OperateRefCoord","IDC_STATIC1",szRead,40);
	SetDlgItemText(IDC_STATIC1,szRead);
	GetLang().GetUIText("OperateRefCoord","IDC_STATIC2",szRead,40);
	SetDlgItemText(IDC_STATIC2,szRead);
	GetLang().GetUIText("OperateRefCoord","IDC_STATIC3",szRead,40);
	SetDlgItemText(IDC_STATIC3,szRead);
	GetLang().GetUIText("OperateRefCoord","IDC_STATIC4",szRead,40);
	SetDlgItemText(IDC_STATIC4,szRead);
	GetLang().GetUIText("OperateRefCoord","IDC_STATIC5",szRead,40);
	SetDlgItemText(IDC_STATIC5,szRead);
	GetLang().GetUIText("OperateRefCoord","IDC_STATIC6",szRead,40);
	SetDlgItemText(IDC_STATIC6,szRead);
	GetLang().GetUIText("OperateRefCoord","IDC_STATIC7",szRead,40);
	SetDlgItemText(IDC_STATIC7,szRead);
	GetLang().GetUIText("OperateRefCoord","IDC_STATIC8",szRead,40);
	SetDlgItemText(IDC_STATIC8,szRead);
	GetLang().GetUIText("OperateRefCoord","IDC_STATIC9",szRead,40);
	SetDlgItemText(IDC_STATIC9,szRead);
	GetLang().GetUIText("OperateRefCoord","IDC_STATIC10",szRead,40);
	SetDlgItemText(IDC_STATIC10,szRead);
	GetLang().GetUIText("OperateRefCoord","IDC_STATIC11",szRead,40);
	SetDlgItemText(IDC_STATIC11,szRead);
	GetLang().GetUIText("OperateRefCoord","IDC_STATIC12",szRead,40);
	SetDlgItemText(IDC_STATIC12,szRead);
	GetLang().GetUIText("OperateRefCoord","IDC_STATIC13",szRead,40);
	SetDlgItemText(IDC_STATIC13,szRead);
	GetLang().GetUIText("OperateRefCoord","IDC_STATIC14",szRead,40);
	SetDlgItemText(IDC_STATIC14,szRead);
	GetLang().GetUIText("OperateRefCoord","IDC_STATIC15",szRead,40);
	SetDlgItemText(IDC_STATIC15,szRead);
	GetLang().GetUIText("OperateRefCoord","IDC_STATIC16",szRead,40);
	SetDlgItemText(IDC_STATIC16,szRead);
	GetLang().GetUIText("OperateRefCoord","IDC_STATIC17",szRead,40);
	SetDlgItemText(IDC_STATIC17,szRead);
	GetLang().GetUIText("OperateRefCoord","IDC_STATIC18",szRead,40);
	SetDlgItemText(IDC_STATIC18,szRead);
	GetLang().GetUIText("OperateRefCoord","IDC_STATIC19",szRead,40);
	SetDlgItemText(IDC_STATIC19,szRead);
	GetLang().GetUIText("OperateRefCoord","IDC_STATIC20",szRead,40);
	SetDlgItemText(IDC_STATIC20,szRead);
	GetLang().GetUIText("OperateRefCoord","IDC_STATIC21",szRead,40);
	SetDlgItemText(IDC_STATIC21,szRead);
	GetLang().GetUIText("OperateRefCoord","IDC_STATIC22",szRead,40);
	SetDlgItemText(IDC_STATIC22,szRead);
	GetLang().GetUIText("OperateRefCoord","IDC_STATIC23",szRead,40);
	SetDlgItemText(IDC_STATIC23,szRead);
	GetLang().GetUIText("OperateRefCoord","IDC_BT_RESETTESTP",szRead,40);
	SetDlgItemText(IDC_BT_RESETTESTP,szRead);
	GetLang().GetUIText("OperateRefCoord","IDC_BT_SETTESTP",szRead,40);
	SetDlgItemText(IDC_BT_SETTESTP,szRead);
	GetLang().GetUIText("OperateRefCoord","IDC_BT_SAVE",szRead,40);
	SetDlgItemText(IDC_BT_SAVE,szRead);
}

void COperateRefCoord::OnInitialUpdate() 
{
	TVisualFormView::OnInitialUpdate();
	if(GetLang().GetCurLanguage()==1)
		SetUI();

//	m_cmbApt.SetCurSel(GetDoc().GetTestAperture()-1);
	char szRead[20]={""};
	m_cmbScanHead.ResetContent();
	strncpy(szRead,GetLang().GetWarningText(10052),20);
	m_cmbScanHead.AddString(szRead);
	strncpy(szRead,GetLang().GetWarningText(10053),20);
	m_cmbScanHead.AddString(szRead);
	m_cmbScanHead.SetCurSel(0);	

	m_edtThickness.SetParseType(SES_NUMBERS);
	m_edtAptOffset.SetParseType(SES_NUMBERS);
	m_edtBETOffset.SetParseType(SES_NUMBERS);
	m_edtBETPriOffset.SetParseType(SES_NUMBERS);

//	m_edtBETOffset.SetRange(-15000,15000);
   
	//功率测试位 与 清理位 相对位置
	m_edtLaserCleanX.SetParseType(SES_NUMBERS|SES_SIGNED);
	m_edtLaserCleanY.SetParseType(SES_NUMBERS|SES_SIGNED);
}

void COperateRefCoord::OnSelchangeCmbScanhead() 
{
	UpdateData();	
	int nHead = m_cmbScanHead.GetCurSel();
	Coord3D crd; 
//	Coord3D crd = GetDoc().GetCCDToGlvTestOffset(nHead);
//	m_lCCDToGlvOffX =crd.x;
//	m_lCCDToGlvOffY =crd.y;
//	m_lCCDToGlvOffZ =crd.z;
//  crd = GetDoc().GetCCDToCCDTestOffset(nHead);
//	m_lCCDDistancePosX =crd.x;
//	m_lCCDDistancePosY =crd.y;
//m_lCCDToGlvOffLongZ = GetDoc().GetLongPathCCDToGlvTestOffset(nHead).z; 
		
	crd = GetDoc().GetLaserPowerTestCrd(nHead);  
	m_lLaserPowerX =crd.x;
	m_lLaserPowerY =crd.y;
	m_lLaserPowerZ =crd.z;

#ifdef DOUBLEBET
	if (nHead==1)
	{
		m_lAptOffset= GetDoc().GetAptBenchmark2();
		m_lBETPriOffset=GetDoc().GetBETPriOffset2();
		m_lBETOffset= GetDoc().GetBETSubOffset2();	
	}
	else
	{
		m_lAptOffset= GetDoc().GetAptBenchmark();
		m_lBETPriOffset=GetDoc().GetBETPriOffset();
		m_lBETOffset= GetDoc().GetBETBenchmark();	
	}
#endif

	UpdateData(FALSE);	
}

/*
void COperateRefCoord::OnSelchangeCmbApt() 
{
	UpdateData();
//	GetDoc().SetTestAperture( m_cmbApt.GetCurSel()+1 );
}
*/

void COperateRefCoord::OnDropdownCmbScanhead() 
{
	UpdateData();	
	int nHead = m_cmbScanHead.GetCurSel();	
	Coord3D crd;

//	crd.x = m_lCCDToGlvOffX;
//	crd.y = m_lCCDToGlvOffY;
//	crd.z = m_lCCDToGlvOffZ;
//	GetDoc().SetCCDToGlvTestOffset(crd,nHead);

//	crd.z = this->m_lCCDToGlvOffLongZ;
//	GetDoc().SetLongPathCCDToGlvTestOffset(crd,nHead);
//	crd.x = m_lCCDDistancePosX;
//	crd.y = m_lCCDDistancePosY;
//	crd.z = m_lCCDToGlvOffZ;
//	GetDoc().SetCCDToCCDTestOffset(crd,nHead);

	crd.x = m_lLaserPowerX;
	crd.y = m_lLaserPowerY;
	crd.z = m_lLaserPowerZ;
	GetDoc().SetLaserPowerTestCrd(crd,nHead);
}


void COperateRefCoord::OnResetTestPara() 
{
	if(!m_SysOperate)
	{
		m_SysOperate = true;
		GetDoc().InitializeSysDoc();
		
		int nHead = m_cmbScanHead.GetCurSel();	
		
		m_lCCDDistancePosX = GetDoc().GetCCDToCCDTestOffset(0).x;
		m_lCCDDistancePosY = GetDoc().GetCCDToCCDTestOffset(0).y;

		m_lLaserPowerX =  GetDoc().GetLaserPowerTestCrd(nHead).x;
		m_lLaserPowerY =  GetDoc().GetLaserPowerTestCrd(nHead).y;
		m_lLaserPowerZ =  GetDoc().GetLaserPowerTestCrd(nHead).z;
		
		m_lTabLoadX = GetDoc().GetTabLoadPos().x;
		m_lTabLoadY = GetDoc().GetTabLoadPos().y;
		m_lTabUnloadX = GetDoc().GetTabUnloadPos().x;
		m_lTabUnloadY = GetDoc().GetTabUnloadPos().y;	
		
#ifdef DOUBLEBET
//		int nHead = m_cmbScanHead.GetCurSel();
		if (nHead==1)
		{			
			m_lAptOffset= GetDoc().GetAptBenchmark2();
			m_lBETPriOffset=GetDoc().GetBETPriOffset2();
			m_lBETOffset= GetDoc().GetBETSubOffset2();	
		}
		else
		{
			m_lAptOffset= GetDoc().GetAptBenchmark();
			m_lBETPriOffset=GetDoc().GetBETPriOffset();
			m_lBETOffset= GetDoc().GetBETBenchmark();	
		}
#else
		m_lAptOffset= GetDoc().GetAptBenchmark();
		m_lBETPriOffset=GetDoc().GetBETPriOffset();
		m_lBETOffset= GetDoc().GetBETBenchmark();	
#endif

		
		//功率测试位 与 清理位 相对位置
		m_lLaserCleanX = GetDoc().GetLaserTestCleanRefPos().x;
		m_lLaserCleanY = GetDoc().GetLaserTestCleanRefPos().y;
		
		m_lCCDBoardThick = GetDoc().GetCCDBoardThick();
		m_lGalvoBoardThick = GetDoc().GetGalvoBoardThick();
		
		m_lTestThickness = GetDoc().GetTestThicknessPos();
		m_lThicknessX=GetDoc().GetThicknessX();
		m_lThicknessY=GetDoc().GetThicknessY();
		
		m_lGlvAdjPosX = GetDoc().GetGlvAdjPosX();
		m_lGlvAdjPosY = GetDoc().GetGlvAdjPosY();
		
		UpdateData(FALSE);
		//yutingxun 6-1
#ifdef USELOG
		GetLog().Append_pro(10051,20042);//"恢复","操作坐标参数"
#endif 
		m_SysOperate = false;
	}
}

void COperateRefCoord::OnSetTestPara() 
{
	if(!m_SysOperate)
	{
		m_SysOperate = true;
		UpdateData();
		
		int nHead = m_cmbScanHead.GetCurSel();	
		Coord3D crd3d;

		crd3d.x = m_lCCDDistancePosX;
		crd3d.y = m_lCCDDistancePosY;
		crd3d.z = 0;
		GetDoc().SetCCDToCCDTestOffset(crd3d,0);

		crd3d.x = m_lLaserPowerX;
		crd3d.y = m_lLaserPowerY;
		crd3d.z = m_lLaserPowerZ;
		GetDoc().SetLaserPowerTestCrd(crd3d,nHead);
		
		Coord crd;
		
		if (m_ButtonSelectOverBorad.GetCheck())
		{//为翻板位置显示
			crd.x = m_lTabLoadX;
			crd.y = m_lTabLoadY;
			GetDoc().SetOverTabLoadPos(crd);
			
			crd.x = m_lTabUnloadX;
			crd.y = m_lTabUnloadY;
			GetDoc().SetOverTabUnloadPos(crd);
			
		}
		else
		{//非翻板位置，正常流程
			crd.x = m_lTabLoadX;
			crd.y = m_lTabLoadY;
			GetDoc().SetTabLoadPos(crd);
			
			crd.x = m_lTabUnloadX;
			crd.y = m_lTabUnloadY;
			GetDoc().SetTabUnloadPos(crd);			
		}		
			
		GetDoc().SetTestThicknessPos(m_lTestThickness);

#ifdef DOUBLEBET
//		int nHead = m_cmbScanHead.GetCurSel();
		if (nHead==1)
		{
			GetDoc().SetAptBenchmark2(m_lAptOffset);
			GetDoc().SetBETPriOffset2(m_lBETPriOffset);
	    	GetDoc().SetBETSubOffset2(m_lBETOffset);
		}
		else
		{
			GetDoc().SetAptBenchmark(m_lAptOffset);
			GetDoc().SetBETPriOffset(m_lBETPriOffset);
		    GetDoc().SetBETBenchmark(m_lBETOffset);
		}
#else
		GetDoc().SetAptBenchmark(m_lAptOffset);
		GetDoc().SetBETPriOffset(m_lBETPriOffset);
		GetDoc().SetBETBenchmark(m_lBETOffset);
#endif	
		GetDoc().SetLaserTestCleanRefPos(Coord(m_lLaserCleanX,m_lLaserCleanY));

		GetDoc().SetCCDBoardThick(m_lCCDBoardThick);
		GetDoc().SetGalvoBoardThick(m_lGalvoBoardThick);
		
		GetDoc().SetThicknessX(m_lThicknessX);
		GetDoc().SetThicknessY(m_lThicknessY);
		
		GetDoc().SetGlvAdjPosX(m_lGlvAdjPosX);
		GetDoc().SetGlvAdjPosY(m_lGlvAdjPosY);
		
#ifdef USELOG
		GetLog().Append_pro(10049,20042);//"设置","操作坐标参数"
#endif 
		m_SysOperate = false;
	}
}

void COperateRefCoord::OnSave() 
{
//	if(!m_SysOperate)
//	{
//		m_SysOperate = true;

		OnSetTestPara();
//		GetDoc().ReleaseSysDoc();
		GetDoc().SaveProcessParam();
		Delay(200);
		AfxMessageBox("参数已设定并保存！");

//		m_SysOperate = false;
//	}
}

void COperateRefCoord::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
    if(bActivate)
	{	
		if (1==GetDoc().GetFunctionOverBorad())
           GetDlgItem(IDC_CHECK_OVERBSELECT)->ShowWindow(TRUE);
		else
			GetDlgItem(IDC_CHECK_OVERBSELECT)->ShowWindow(FALSE);

		int nLevel = GetDoc().GetCurUserLevel();
		if(nLevel==SystemDoc::PRIMARY)//初级
		{
			m_edtGlvAdjPosX.EnableWindow(FALSE);//振镜校正时平台位置
			m_edtGlvAdjPosY.EnableWindow(FALSE);
			
			m_edtCCDDistancePosX.EnableWindow(FALSE);//CCD校正时平台位置
			m_edtCCDDistancePosY.EnableWindow(FALSE);
			
			if(1==GetDoc().GetFZInnerMark())////20160321 为满足方正校正版厚度不一样	
			{
				m_edtGalvoBoardThick.EnableWindow(TRUE);//校正板厚设置
				m_btnReset.EnableWindow(TRUE);
				m_btnSet.EnableWindow(TRUE);
				m_btnSave.EnableWindow(TRUE);
			}
			else
			{
				m_edtGalvoBoardThick.EnableWindow(FALSE);//校正板厚设置
				m_btnReset.EnableWindow(FALSE);
				m_btnSet.EnableWindow(FALSE);
				m_btnSave.EnableWindow(FALSE);
			}

			m_edtCCDBoardThick.EnableWindow(FALSE);
			
			m_edtLaserCleanX.EnableWindow(FALSE);//探头清洁位置
			m_edtLaserCleanY.EnableWindow(FALSE);
			
			m_cmbScanHead.EnableWindow(FALSE);//探头功率测试位置
			m_edtLaserPowerX.EnableWindow(FALSE);
			m_edtLaserPowerY.EnableWindow(FALSE);
			m_edtLaserPowerZ.EnableWindow(FALSE);
				
			m_edtAptOffset.EnableWindow(FALSE);//光束校准系统轴偏置
			m_edtBETPriOffset.EnableWindow(FALSE);
			m_edtBETOffset.EnableWindow(FALSE);
	
			m_edtThickness.EnableWindow(FALSE);//自动测厚时XYZ轴位置
			m_edtThicknessX.EnableWindow(FALSE);
			m_edtThicknessY.EnableWindow(FALSE);			

			m_edtTabUnloadX.EnableWindow(FALSE);//上下料时XY平台位置
			m_edtTabUnloadY.EnableWindow(FALSE);	    
			m_edtTabLoadX.EnableWindow(FALSE);
			m_edtTabLoadY.EnableWindow(FALSE);
		}
		else if(nLevel==SystemDoc::SUPEROR)//高级
		{
//#ifdef CHONGDA
			if(GetDoc().GetCustomerSpecial()==1)
			{
				m_edtGlvAdjPosX.EnableWindow(FALSE);//振镜校正时平台位置
				m_edtGlvAdjPosY.EnableWindow(FALSE);
				
				m_edtCCDDistancePosX.EnableWindow(FALSE);//CCD校正时平台位置
				m_edtCCDDistancePosY.EnableWindow(FALSE);
				
				m_edtGalvoBoardThick.EnableWindow(FALSE);//校正板厚设置
				m_edtCCDBoardThick.EnableWindow(FALSE);
				
				m_edtLaserCleanX.EnableWindow(FALSE);//探头清洁位置
				m_edtLaserCleanY.EnableWindow(FALSE);
				
				m_cmbScanHead.EnableWindow(FALSE);//探头功率测试位置
				m_edtLaserPowerX.EnableWindow(FALSE);
				m_edtLaserPowerY.EnableWindow(FALSE);
				m_edtLaserPowerZ.EnableWindow(FALSE);
				
				m_edtAptOffset.EnableWindow(FALSE);//光束校准系统轴偏置
				m_edtBETPriOffset.EnableWindow(FALSE);
				m_edtBETOffset.EnableWindow(FALSE);
				
				m_edtThickness.EnableWindow(FALSE);//自动测厚时XYZ轴位置
				m_edtThicknessX.EnableWindow(FALSE);
				m_edtThicknessY.EnableWindow(FALSE);
			}
//#else
			else
			{
				m_edtGlvAdjPosX.EnableWindow(TRUE);//振镜校正时平台位置
				m_edtGlvAdjPosY.EnableWindow(TRUE);
				
				m_edtCCDDistancePosX.EnableWindow(TRUE);//CCD校正时平台位置
				m_edtCCDDistancePosY.EnableWindow(TRUE);
				
				m_edtGalvoBoardThick.EnableWindow(TRUE);//校正板厚设置
				m_edtCCDBoardThick.EnableWindow(TRUE);
				
				m_edtLaserCleanX.EnableWindow(TRUE);//探头清洁位置
				m_edtLaserCleanY.EnableWindow(TRUE);
				
				m_cmbScanHead.EnableWindow(TRUE);//探头功率测试位置
				m_edtLaserPowerX.EnableWindow(TRUE);
				m_edtLaserPowerY.EnableWindow(TRUE);
				m_edtLaserPowerZ.EnableWindow(TRUE);
				
				m_edtAptOffset.EnableWindow(TRUE);//光束校准系统轴偏置
				m_edtBETPriOffset.EnableWindow(TRUE);
				m_edtBETOffset.EnableWindow(TRUE);
				
				m_edtThickness.EnableWindow(TRUE);//自动测厚时XYZ轴位置
				m_edtThicknessX.EnableWindow(TRUE);
				m_edtThicknessY.EnableWindow(TRUE);
			}
//#endif
			m_edtTabUnloadX.EnableWindow(TRUE);//上下料时XY平台位置
			m_edtTabUnloadY.EnableWindow(TRUE);	    
			m_edtTabLoadX.EnableWindow(TRUE);
			m_edtTabLoadY.EnableWindow(TRUE);
					
			m_btnReset.EnableWindow(TRUE);
			m_btnSet.EnableWindow(TRUE);
			m_btnSave.EnableWindow(TRUE);
		}
		else if(nLevel==SystemDoc::ADMIN)//系统
		{
			m_edtGlvAdjPosX.EnableWindow(TRUE);//振镜校正时平台位置
			m_edtGlvAdjPosY.EnableWindow(TRUE);
			
			m_edtCCDDistancePosX.EnableWindow(TRUE);//CCD校正时平台位置
			m_edtCCDDistancePosY.EnableWindow(TRUE);
			
			m_edtGalvoBoardThick.EnableWindow(TRUE);//校正板厚设置
			m_edtCCDBoardThick.EnableWindow(TRUE);
			
			m_edtLaserCleanX.EnableWindow(TRUE);//探头清洁位置
			m_edtLaserCleanY.EnableWindow(TRUE);
			
			m_cmbScanHead.EnableWindow(TRUE);//探头功率测试位置
			m_edtLaserPowerX.EnableWindow(TRUE);
			m_edtLaserPowerY.EnableWindow(TRUE);
			m_edtLaserPowerZ.EnableWindow(TRUE);
			
			m_edtAptOffset.EnableWindow(TRUE);//光束校准系统轴偏置
			m_edtBETPriOffset.EnableWindow(TRUE);
			m_edtBETOffset.EnableWindow(TRUE);

			m_edtThickness.EnableWindow(TRUE);//自动测厚时XYZ轴位置
			m_edtThicknessX.EnableWindow(TRUE);
			m_edtThicknessY.EnableWindow(TRUE);			

			m_edtTabUnloadX.EnableWindow(TRUE);//上下料时XY平台位置
			m_edtTabUnloadY.EnableWindow(TRUE);	    
			m_edtTabLoadX.EnableWindow(TRUE);
			m_edtTabLoadY.EnableWindow(TRUE);
					
			m_btnReset.EnableWindow(TRUE);
			m_btnSet.EnableWindow(TRUE);
			m_btnSave.EnableWindow(TRUE);
		} 		
	}
	UpdateData(FALSE);
	
	TVisualFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void COperateRefCoord::OnCheckOverbselect() 
{
	UpdateData();
	if (m_ButtonSelectOverBorad.GetCheck())
	{//为翻板位置显示
		
		m_lTabLoadX=GetDoc().GetOverTabLoadPos().x;;
		m_lTabLoadY=GetDoc().GetOverTabLoadPos().y;
		m_lTabUnloadX=GetDoc().GetOverTabUnloadPos().x;;
		m_lTabUnloadY=GetDoc().GetOverTabUnloadPos().y;
		
	}
	else
	{//非翻板位置，正常流程
		m_lTabLoadX=GetDoc().GetTabLoadPos().x;;
		m_lTabLoadY=GetDoc().GetTabLoadPos().y;
		m_lTabUnloadX=GetDoc().GetTabUnloadPos().x;;
		m_lTabUnloadY=GetDoc().GetTabUnloadPos().y;
	}
	UpdateData(FALSE);
}
