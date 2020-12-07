// MarkMake.cpp : implementation file
//

#include "stdafx.h"
#include "lasersystem.h"
#include "MarkMake.h"

#include "SysParameter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMarkMake dialog


CMarkMake::CMarkMake(CWnd* pParent /*=NULL*/)
	: CDialog(CMarkMake::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMarkMake)
	m_iMarkType = 0;
	m_chkWhiteInBlack = FALSE;
	m_iMarkSize = 3150;
	//}}AFX_DATA_INIT

	pImageBMP=NULL;
	imageSize=0;
}

void CMarkMake::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMarkMake)
	DDX_Radio(pDX, IDC_RAD_MARKTYPE, m_iMarkType);
	DDX_Check(pDX, IDC_CHK_WHITEINBLACK, m_chkWhiteInBlack);
	DDX_Text(pDX, IDC_EDT_MARKSIZE, m_iMarkSize);
	DDV_MinMaxInt(pDX, m_iMarkSize, 0, 4500);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMarkMake, CDialog)
	//{{AFX_MSG_MAP(CMarkMake)
	ON_BN_CLICKED(IDOK, OnSave)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CHK_WHITEINBLACK, OnChkWhiteinblack)
	ON_EN_CHANGE(IDC_EDT_MARKSIZE, OnChangeEdtMarksize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CMarkMake& GetCMarkMake()
{
	static CMarkMake m_markMake;

	return m_markMake;
}
/////////////////////////////////////////////////////////////////////////////
// CMarkMake message handlers

void CMarkMake::OnSave()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);

	CString strMode;
	CString strName;
	char scrName[MaxPathLen];

	if(m_iMarkType==3)
	{
		if(GetDoc().GetTechnicType())
			strName=GetDoc().GetAppPath()+TESTPATTERNNAMELP;
		else
			strName=GetDoc().GetAppPath()+TESTPATTERNNAMESP;
		
		sprintf(scrName,"%s",strName);
	}
	else
	{
		if(!GetDoc().GetFileOpenState())
		{
			AfxMessageBox("请先打开要加工的文件！");
			return;
		}

		switch(m_iMarkType)
		{
		case 0:	
			strMode="Ext";
			break;
		case 1:	
			strMode="Inn";
			break;
		case 2:	
			strMode="Int";
			break;
		default:
			strMode="Ext";
		}

		strName=GetDoc().GetFileName();
		strName=strName.Left(strName.ReverseFind('.'));
		sprintf(scrName,"%s%s.bmp",strName,strMode);
	}

	GetImageBMP().BmpSave(scrName,pImageBMP,imageSize,imageSize);
}


void CMarkMake::OnSave2()
{
	pImageBMP=(unsigned char*) new BYTE[1100000];
	MakeBMP();

	CString strMode;
	CString strName;
	char scrName[MaxPathLen];
	
	
	if(!GetDoc().GetFileOpenState())
	{
		AfxMessageBox("请先打开要加工的文件！");
		return;
	}
	
	switch(m_iMarkType)
	{
	case 0:	
		strMode="Ext";
		break;
	case 1:	
		strMode="Inn";
		break;
	case 2:	
		strMode="Int";
		break;
	default:
		strMode="Ext";
	}
	
	strName=GetDoc().GetFileName();
	strName=strName.Left(strName.ReverseFind('.'));
	sprintf(scrName,"%s%s.bmp",strName,strMode);
	

	GetImageBMP().BmpSave(scrName,pImageBMP,imageSize,imageSize);
	if(pImageBMP)
	{
		delete pImageBMP;
		pImageBMP=NULL;
	}
}

BOOL CMarkMake::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	pImageBMP=(unsigned char*) new BYTE[1100000];

	MakeBMP();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMarkMake::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CRect rect;
	CSize size;		
	GetDlgItem(IDC_BMPDISPLAY)->GetClientRect(rect);
	size.cx=rect.Width();
	size.cy=rect.Height();

	CSize sizeImage;
	sizeImage.cx=imageSize;
	sizeImage.cy=imageSize;

	GetImageBMP().BmpDisplay(pImageBMP,sizeImage,::GetDlgItem(m_hWnd,IDC_BMPDISPLAY),size);

	// Do not call CDialog::OnPaint() for painting messages
}

void CMarkMake::MakeBMP()
{
	imageSize=(m_iMarkSize+200)/IMAGEPIXELX;
	imageSize=20*(imageSize/20+1);

	int circleSize=m_iMarkSize/2/IMAGEPIXELX;
//	int middleX=imageSize/2;
//	int middleY=imageSize/2;
	double middleX=(imageSize-1)/2.0;										//20200214
	double middleY=(imageSize-1)/2.0;
	long imageCount=imageSize*imageSize;

	int coordX=0;
	int coordY=0;

	for(long i=0;i<imageCount;i++)
	{
		coordX=i%imageSize;
		coordY=i/imageSize;

//		if(sqrt(pow((coordX-middleX),2)+pow((coordY-middleY),2))<=circleSize)
		if(sqrt(pow(((double)coordX-middleX),2)+pow(((double)coordY-middleY),2))<=circleSize)	//20200214
		{
			if(m_chkWhiteInBlack)
				pImageBMP[i]=255;
			else
				pImageBMP[i]=0;
		}		
		else
		{
			if(m_chkWhiteInBlack)
				pImageBMP[i]=0;
			else
				pImageBMP[i]=255;
		}
	}
}

void CMarkMake::OnChkWhiteinblack() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);

	MakeBMP();
	Invalidate();
}


void CMarkMake::OnChangeEdtMarksize() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(true);

	if(m_iMarkSize>4500)
		return;

	MakeBMP();
	Invalidate();	
}

void CMarkMake::OnCancel() 
{
	// TODO: Add extra cleanup here
	if(pImageBMP)
	{
		delete pImageBMP;
		pImageBMP=NULL;
	}

	CDialog::OnCancel();
}
