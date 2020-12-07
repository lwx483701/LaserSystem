// FilePointView.cpp : implementation file
//

#include "stdafx.h"
#include "lasersystem.h"
#include "FilePointView.h"
#include "PointcontrlView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFilePointView

const int MapMode = MM_LOMETRIC;				//映射方式,0.1mm/pixel
const CSize TableSize = CSize(650000,750000);	//50000+工作台大小(550000*650000)+50000，单位是um
const float ZoomRatio =1.5;						//缩放比率

IMPLEMENT_DYNCREATE(CFilePointView, CScrollView)

CFilePointView::CFilePointView():m_Zoom(NONE) ,m_Scal(24.0),m_xoff(0),m_yoff(0)
{

}

CFilePointView::~CFilePointView()
{

}

BEGIN_MESSAGE_MAP(CFilePointView, CScrollView)
//{{AFX_MSG_MAP(CFilePointView)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_REFLASHPOINT,OnReflashPoint)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFilePointView drawing

void CFilePointView::OnInitialUpdate()
{
	ZoomReset();

	isShowPathAndBE=FALSE;
	LButtomDown =FALSE;
	m_ScalDraw=(double)(GetDoc().GetSLBitPerMM()/1000.0);

	CScrollView::OnInitialUpdate();
}

void CFilePointView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	char ez[256]={""};
	float tempScal = (float)m_Scal/10000;

	m_ScalDraw=(double)(GetDoc().GetSLBitPerMM()/1000.0);		//20190829

	// TODO: add draw code here
	pDC->SetMapMode(MapMode);
	pDC->SetWindowOrg(0,TableSize.cy*tempScal);

	DrawDocFrame(pDC);								//台面边框

	if(!GetDoc().GetFileOpenState())
		return;
	else
	{
		CRD x,y;
		x=GetDoc().GetLBRefPoint().x;
		y=GetDoc().GetLBRefPoint().y;

		m_xoff = 22500-x;
		m_yoff = 22500-y;
	}

	if(!GetDoc().GetIsDoubleFileData())
	{
		DrawStringText(pDC);							//字符框和字符

		DrawFid(pDC);									//外靶点
		
		if(GetDoc().GetFileMode()==SystemDoc::NORMALPROC)				//“正常”工艺加工方式支持外层主标靶方式和内层主标靶方式
		{
			if(GetDoc().GetProcMode()==SystemDoc::INNERMARKPROC)
				DrawInnerFid(pDC);						//内靶点

			DrawPoint(pDC);								//分区框和点位
		}
		
		if(GetDoc().GetFileMode()==SystemDoc::INNERMARK)				//“6标靶”工艺加工方式仅支持外层主标靶方式
		{
			DrawInnerFid(pDC);							//内靶点
			DrawPoint(pDC);								//分区框和点位
		}
		
		if(GetDoc().GetFileMode()==SystemDoc::LOCALMARKM02)				//“M02内部标靶”工艺加工方式仅支持外层主标靶方式
		{
			for(int index=0;index<GetExcellonData().GetLocalMarkDataCount();index++)
			{
				DrawLocalMark(pDC,index);				//M02 LocalMark局部靶点?????
				DrawLocalMarkSubArea(pDC,index);		//局部区域分区框和点位?????		
			}

			DrawOtherSubArea(pDC);						//其他区域分区框和点位?????
		}
		
		if(GetDoc().GetFileMode()==SystemDoc::LOCALMARKSA)				//“分区内部标靶”工艺加工方式仅支持外层主标靶方式
		{
			for(int index=0;index<GetExcellonData().GetSALocalMarkDataCount();index++)
			{
				DrawSALocalMark(pDC,index);				//SA LocalMark局部靶点?????
			}

			DrawPoint(pDC);								//分区框和点位
		}
	}
	else//--------------------------------------------------------------20161109
	{
		int oldGlobalExcellonIndex=GetGlobalExcellonIndex();

		for(int i=0;i<2;i++)
		{
			SetGlobalExcellonIndex(i);
			
			DrawStringText(pDC);						//字符框和字符
			DrawFid(pDC);								//外靶点
			DrawPoint(pDC);								//分区框和点位
			DrawInnerFid(pDC);							//内靶点	
		}

		SetGlobalExcellonIndex(oldGlobalExcellonIndex);
	}
//-------------------------------------------------------------------------------
}

void CFilePointView::DrawDocFrame(CDC *pDC)
{
	float tempScal = (float)m_Scal/10000;
	int nWidth = 5;

	CPen pen(PS_SOLID, nWidth, ::GetSysColor(COLOR_WINDOWFRAME));
	CPen * pOldPen = pDC->SelectObject(&pen);
	pDC->SelectStockObject(HOLLOW_BRUSH);							//透明画刷

	CRect rect;
 	rect.top = 50000*tempScal;
	rect.left = 50000*tempScal;
	rect.right = (TableSize.cx-50000)*tempScal;
	rect.bottom =(TableSize.cy-50000)*tempScal;
//	rect.InflateRect(-nWidth,-nWidth,nWidth,nWidth);

	pDC->Rectangle(&rect);		//上下镜像?

	pen.DeleteObject();
	pDC->SelectObject(pOldPen);

	pen.CreatePen(PS_SOLID, 2*nWidth, ::GetSysColor(COLOR_BTNSHADOW));
	pDC->SelectObject(&pen);

//	rect.NormalizeRect();
	pDC->MoveTo(rect.right + 2*nWidth, rect.top - 2*nWidth);
	pDC->LineTo(rect.right + 2*nWidth, rect.bottom - 2*nWidth);
	pDC->MoveTo(rect.left  + 2*nWidth, rect.top - 2*nWidth);
	pDC->LineTo(rect.right + 2*nWidth, rect.top - 2*nWidth);

	pen.DeleteObject();
	pDC->SelectObject(pOldPen);
}

void CFilePointView::DrawStringText(CDC *pDC)
{
	RECT rect;
	float tempScal = (float)m_Scal/10000;
	float pieR = 6+tempScal/0.02;
	Coord TxtPos,crdDest;
	
	CPen *pOldPen,PenText;
	CFont *def_font,font;

	PenText.CreatePen(PS_SOLID,1,CPointcontrlView::ColorToolTxt);
	pDC->SetTextColor(CPointcontrlView::ColorToolTxt);
	pDC->SetTextAlign(TA_BOTTOM); 
	
	VERIFY(font.CreatePointFont(m_Scal, "Arial", pDC));
	
	pOldPen = pDC->SelectObject(&PenText);
	def_font = pDC->SelectObject(&font);
	pDC->SelectStockObject(HOLLOW_BRUSH);
	
	if(GetExcellonData().GetDaySignCount()>0)
	{
		for(int n = 0; n<GetExcellonData().GetDaySignCount(); ++n)
		{
			TxtPos = GetExcellonData().GetDaySignPos(n);
			TxtPos.x += m_xoff;
			TxtPos.y += m_yoff;

			pDC->TextOut(TxtPos.x*tempScal,TxtPos.y*tempScal,"DATE",4);
			pDC->Ellipse(TxtPos.x*tempScal-pieR,
						TxtPos.y*tempScal-pieR,
						TxtPos.x*tempScal+pieR,
						TxtPos.y*tempScal+pieR);

			GetDrawTextRect(GetExcellonData().GetDaySignDir(n),GetExcellonData().GetDayTextPosition(n),TxtPos,rect,tempScal);
			pDC->Rectangle(&rect);
		}
	}
	
	if(GetExcellonData().GetTimeSignCount()>0)
	{
		for(int n = 0; n<GetExcellonData().GetTimeSignCount(); ++n)
		{
			TxtPos = GetExcellonData().GetTimeSignPos(n);
			TxtPos.x += m_xoff;
			TxtPos.y += m_yoff;

			pDC->TextOut(TxtPos.x*tempScal,TxtPos.y*tempScal,"TIME",4);
			pDC->Ellipse(TxtPos.x*tempScal-pieR,
						TxtPos.y*tempScal-pieR,
						TxtPos.x*tempScal+pieR,
						TxtPos.y*tempScal+pieR);

			GetDrawTextRect(GetExcellonData().GetTimeSignDir(n),GetExcellonData().GetTimeTextPosition(n),TxtPos,rect,tempScal);
			pDC->Rectangle(&rect);
		}
	}
	
	if(GetExcellonData().GetMachineSignCount()>0)
	{
		for(int n = 0; n<GetExcellonData().GetMachineSignCount(); ++n)
		{
			TxtPos = GetExcellonData().GetMachineSignPos(n);
			TxtPos.x += m_xoff;
			TxtPos.y += m_yoff;

			pDC->TextOut(TxtPos.x*tempScal,TxtPos.y*tempScal,"MACHINE");
			pDC->Ellipse(TxtPos.x*tempScal-pieR,
						TxtPos.y*tempScal-pieR,
						TxtPos.x*tempScal+pieR,
						TxtPos.y*tempScal+pieR);

			GetDrawTextRect(GetExcellonData().GetMachineSignDir(n),GetExcellonData().GetMachineTextPosition(n),TxtPos,rect,tempScal);
			pDC->Rectangle(&rect);
		}
	}
	
	if(GetExcellonData().GetLotIDSignCount()>0)
	{
		for(int n = 0; n<GetExcellonData().GetLotIDSignCount(); ++n)
		{
			TxtPos=GetExcellonData().GetLotIDSignPos(n);
			TxtPos.x += m_xoff;
			TxtPos.y += m_yoff;

			pDC->TextOut(TxtPos.x*tempScal,TxtPos.y*tempScal,"LOTID");
			pDC->Ellipse(TxtPos.x*tempScal-pieR,
						TxtPos.y*tempScal-pieR,
						TxtPos.x*tempScal+pieR,
						TxtPos.y*tempScal+pieR);

			GetDrawTextRect(GetExcellonData().GetLotIDSignDir(n),GetExcellonData().GetLotIDTextPosition(n),TxtPos,rect,tempScal);
			pDC->Rectangle(&rect);
		}
	}

	if(GetExcellonData().GetAxisNoSignCount()>0)
	{
		for(int n = 0; n<GetExcellonData().GetAxisNoSignCount(); ++n)
		{
			TxtPos=GetExcellonData().GetAxisNoSignPos(n);
			TxtPos.x += m_xoff;
			TxtPos.y += m_yoff;

			pDC->TextOut(TxtPos.x*tempScal,TxtPos.y*tempScal,"AxisNo");
			pDC->Ellipse(TxtPos.x*tempScal-pieR,
						TxtPos.y*tempScal-pieR,
						TxtPos.x*tempScal+pieR,
						TxtPos.y*tempScal+pieR);

			GetDrawTextRect(GetExcellonData().GetAxisNoSignDir(n),GetExcellonData().GetAxisNoTextPosition(n),TxtPos,rect,tempScal);
			pDC->Rectangle(&rect);
		}
	}
	
	if(GetExcellonData().GetScaleSignCount()>0)
	{
		for(int n = 0; n<GetExcellonData().GetScaleSignCount(); ++n)
		{
			TxtPos=GetExcellonData().GetScaleSignPos(n);
			TxtPos.x += m_xoff;
			TxtPos.y += m_yoff;

			pDC->TextOut(TxtPos.x*tempScal,TxtPos.y*tempScal,"Scale");
			pDC->Ellipse(TxtPos.x*tempScal-pieR,
						TxtPos.y*tempScal-pieR,
						TxtPos.x*tempScal+pieR,
						TxtPos.y*tempScal+pieR);

			GetDrawTextRect(GetExcellonData().GetScaleSignDir(n),GetExcellonData().GetScaleTextPosition(n),TxtPos,rect,tempScal);
			pDC->Rectangle(&rect);
		}
	}

	if(GetExcellonData().GetStrTextSignCount()>0)
	{
		for(int n = 0; n<GetExcellonData().GetStrTextSignCount(); ++n)
		{
			TxtPos=GetExcellonData().GetStrTextSignPos(n);
			TxtPos.x += m_xoff;
			TxtPos.y += m_yoff;

			pDC->TextOut(TxtPos.x*tempScal,TxtPos.y*tempScal,GetExcellonData().GetStrText(n));
			pDC->Ellipse(TxtPos.x*tempScal-pieR,
						TxtPos.y*tempScal-pieR,
						TxtPos.x*tempScal+pieR,
						TxtPos.y*tempScal+pieR);

			GetDrawTextRect(GetExcellonData().GetStrTextSignDir(n),GetExcellonData().GetStrTextPosition(n),TxtPos,rect,tempScal);
			pDC->Rectangle(&rect);
		}
	}
	
	CString InforStr;
	
	font.DeleteObject();
	pDC->SelectObject(def_font);
	
	VERIFY(font.CreatePointFont(m_Scal*2, "Arial", pDC));
	
	pDC->SelectObject(&font);
		
	if(GetDoc().GetFileMode()!=SystemDoc::LOCALMARKM02)
	{
		for(int curSubAreaNo=0;curSubAreaNo<GetExcellonData().GetSubAreaCnt();++curSubAreaNo)
		{		
			crdDest = GetExcellonData().GetSubAreaCenter(curSubAreaNo);
			crdDest.x += m_xoff;
			crdDest.y += m_yoff;

			InforStr.Format("SA%d",curSubAreaNo+1);
			pDC->TextOut((crdDest.x-10000)*tempScal,(crdDest.y-4000)*tempScal,InforStr);
		}
	}
	else
	{	
		for(int index=0;index<GetExcellonData().GetLocalMarkDataCount();index++)
		{
			for(int curSubAreaNo=0;curSubAreaNo<GetExcellonData().GetLocalMarkSubAreaCnt(index);++curSubAreaNo)
			{		
				crdDest = GetExcellonData().GetLocalMarkSubAreaCenter(index,curSubAreaNo);
				crdDest.x += m_xoff;
				crdDest.y += m_yoff;

				InforStr.Format("SA%d_%d",index+1,curSubAreaNo+1);
				pDC->TextOut((crdDest.x-10000)*tempScal,(crdDest.y-4000)*tempScal,InforStr);
			}
		}
		
		for(int curSubAreaNo=0;curSubAreaNo<GetExcellonData().GetOtherSubAreaCnt();++curSubAreaNo)
		{
			if(!GetExcellonData().GetOtherSubAreaIsEmpty(curSubAreaNo)) 
			{
				crdDest = GetExcellonData().GetOtherSubAreaCenter(curSubAreaNo);
				crdDest.x += m_xoff;
				crdDest.y += m_yoff;

				InforStr.Format("OSA%d",curSubAreaNo+1);
				pDC->TextOut((crdDest.x-10000)*tempScal,(crdDest.y-4000)*tempScal,InforStr);
			}
		}
	}
	
	font.DeleteObject();
	PenText.DeleteObject();

	pDC->SelectObject(def_font);
	pDC->SelectObject(pOldPen);
}

void CFilePointView::GetDrawTextRect(TextDir td,TextPosition tp,Coord TxtPos,RECT &rect,float tempScal)
{
	if(HorizontalText==td)
	{
		switch(tp)
		{
		case 0:
			rect.left = (TxtPos.x)*tempScal;
			rect.top = (TxtPos.y+5000)*tempScal;			
			rect.right = (TxtPos.x+15000)*tempScal;
			rect.bottom = (TxtPos.y)*tempScal;
			break;
		case 1:
			rect.left = (TxtPos.x)*tempScal;
			rect.top = (TxtPos.y)*tempScal;			
			rect.right = (TxtPos.x+15000)*tempScal;
			rect.bottom = (TxtPos.y-5000)*tempScal;
			break;
		case 2:
			rect.left = (TxtPos.x-15000)*tempScal;
			rect.top = (TxtPos.y)*tempScal;			
			rect.right = (TxtPos.x)*tempScal;
			rect.bottom = (TxtPos.y-5000)*tempScal;
			break;
		case 3:
			rect.left = (TxtPos.x-15000)*tempScal;
			rect.top = (TxtPos.y+5000)*tempScal;			
			rect.right = (TxtPos.x)*tempScal;
			rect.bottom = (TxtPos.y)*tempScal;
			break;
		}
	}
	else if(VerticalText==td)
	{
		switch(tp)
		{
		case 0:
			rect.left = (TxtPos.x-5000)*tempScal;
			rect.top = (TxtPos.y+15000)*tempScal;			
			rect.right = (TxtPos.x)*tempScal;
			rect.bottom = (TxtPos.y)*tempScal;
			break;
		case 1:
			rect.left = (TxtPos.x)*tempScal;
			rect.top = (TxtPos.y+15000)*tempScal;			
			rect.right = (TxtPos.x+5000)*tempScal;
			rect.bottom = (TxtPos.y)*tempScal;
			break;
		case 2:
			rect.left = (TxtPos.x)*tempScal;
			rect.top = (TxtPos.y)*tempScal;			
			rect.right = (TxtPos.x+5000)*tempScal;
			rect.bottom = (TxtPos.y-15000)*tempScal;
			break;
		case 3:
			rect.left = (TxtPos.x-5000)*tempScal;
			rect.top = (TxtPos.y)*tempScal;			
			rect.right = (TxtPos.x)*tempScal;
			rect.bottom = (TxtPos.y-15000)*tempScal;
			break;
		}
	}
}

void CFilePointView::DrawFid(CDC *pDC)
{
	Coord FidPos;
	float tempScal = (float)m_Scal/10000;
	float pieR = 6+tempScal/0.02;

	CPen *pOldPen,PenFid;
	PenFid.CreatePen(PS_SOLID,6,CPointcontrlView::ColorToolFid);
	pOldPen = pDC->SelectObject(&PenFid);

	for(int FidIdex=0;FidIdex<GetExcellonData().GetFiducialNum();FidIdex++)
	{
		FidPos = GetExcellonData().GetFiducialPos(FidIdex);
		FidPos.x += m_xoff;
		FidPos.y += m_yoff;

		pDC->MoveTo(FidPos.x*tempScal-pieR,FidPos.y*tempScal);
		pDC->LineTo(FidPos.x*tempScal+pieR,FidPos.y*tempScal);
		pDC->MoveTo(FidPos.x*tempScal,FidPos.y*tempScal-pieR);
		pDC->LineTo(FidPos.x*tempScal,FidPos.y*tempScal+pieR);
		
		pDC->Ellipse(FidPos.x*tempScal-pieR,
					FidPos.y*tempScal-pieR,
					FidPos.x*tempScal+pieR,
					FidPos.y*tempScal+pieR);	
	}

	PenFid.DeleteObject();	
	pDC->SelectObject(pOldPen);
}

void CFilePointView::DrawInnerFid(CDC *pDC)
{
	Coord FidPos;
	float tempScal = (float)m_Scal/10000;
	float pieR = 6+tempScal/0.02;

	CPen *pOldPen,PenFid;
	PenFid.CreatePen(PS_SOLID,6,CPointcontrlView::ColorToolTxt);
	pOldPen = pDC->SelectObject(&PenFid);

	for(int FidIdex=0;FidIdex<GetExcellonData().GetInnerFiducialNum();FidIdex++)
	{
		FidPos = GetExcellonData().GetInnerFiducialPos(FidIdex);
		FidPos.x += m_xoff;
		FidPos.y += m_yoff;

		pDC->MoveTo(FidPos.x*tempScal-pieR,FidPos.y*tempScal);
		pDC->LineTo(FidPos.x*tempScal+pieR,FidPos.y*tempScal);
		pDC->MoveTo(FidPos.x*tempScal,FidPos.y*tempScal-pieR);
		pDC->LineTo(FidPos.x*tempScal,FidPos.y*tempScal+pieR);
		
		pDC->Ellipse(FidPos.x*tempScal-pieR,
					FidPos.y*tempScal-pieR,
					FidPos.x*tempScal+pieR,
					FidPos.y*tempScal+pieR);		
	}

	PenFid.DeleteObject();	
	pDC->SelectObject(pOldPen);
}

void CFilePointView::DrawLocalMark(CDC *pDC,int index)
{ 
	Coord LocalMarkPos;
	float tempScal = (float)m_Scal/10000;
	float pieR = 6+tempScal/0.02;

	CPen *pOldPen,PenFid;
	PenFid.CreatePen(PS_SOLID,6,CPointcontrlView::ColorToolFid);
	pOldPen = pDC->SelectObject(&PenFid);

	for(int n=0;n<GetExcellonData().GetLocalMark(index).size();n++)
	{
		LocalMarkPos = GetExcellonData().GetLocalMarkDataPos(index,n);
		LocalMarkPos.x += m_xoff;
		LocalMarkPos.y += m_yoff;

		pDC->MoveTo(LocalMarkPos.x*tempScal-pieR,LocalMarkPos.y*tempScal);
		pDC->LineTo(LocalMarkPos.x*tempScal+pieR,LocalMarkPos.y*tempScal);
		pDC->MoveTo(LocalMarkPos.x*tempScal,LocalMarkPos.y*tempScal-pieR);
		pDC->LineTo(LocalMarkPos.x*tempScal,LocalMarkPos.y*tempScal+pieR);
		
		pDC->Ellipse(LocalMarkPos.x*tempScal-pieR,
					LocalMarkPos.y*tempScal+pieR,
					LocalMarkPos.x*tempScal+pieR,
					LocalMarkPos.y*tempScal-pieR);
	}	
			
	PenFid.DeleteObject();	
	pDC->SelectObject(pOldPen);
}

void CFilePointView::DrawSALocalMark(CDC *pDC,int index)
{ 
	Coord LocalMarkPos;
	float tempScal = (float)m_Scal/10000;
	float pieR = 6+tempScal/0.02;

	CPen *pOldPen,PenFid;
	PenFid.CreatePen(PS_SOLID,6,CPointcontrlView::ColorToolFid);
	pOldPen = pDC->SelectObject(&PenFid);

	for(int n=0;n<GetExcellonData().GetSALocalMark(index).size();n++)
	{
		LocalMarkPos = GetExcellonData().GetSALocalMarkDataPos(index,n);
		LocalMarkPos.x += m_xoff;
		LocalMarkPos.y += m_yoff;

		pDC->MoveTo(LocalMarkPos.x*tempScal-pieR,LocalMarkPos.y*tempScal);
		pDC->LineTo(LocalMarkPos.x*tempScal+pieR,LocalMarkPos.y*tempScal);
		pDC->MoveTo(LocalMarkPos.x*tempScal,LocalMarkPos.y*tempScal-pieR);
		pDC->LineTo(LocalMarkPos.x*tempScal,LocalMarkPos.y*tempScal+pieR);
		
		pDC->Ellipse(LocalMarkPos.x*tempScal-pieR,
					LocalMarkPos.y*tempScal+pieR,
					LocalMarkPos.x*tempScal+pieR,
					LocalMarkPos.y*tempScal-pieR);
	}
			
	PenFid.DeleteObject();	
	pDC->SelectObject(pOldPen);
}

void CFilePointView::DrawPoint(CDC *pDC)
{
	RECT rect;
	Coord crdDest;
	int nCommandCnt=0;
	float tempScal = (float)(m_Scal/10000);
	float pieR =3+tempScal/0.02;

	CPen  PenDot;
	PenDot.CreatePen(PS_SOLID, 1,RGB(0,0,0));
	CBrush brushDot(RGB(0,0,0));
	
	CPen* pOldPen;
	CBrush*	pOldbrush;
	pOldPen=(CPen*)pDC->SelectObject(&PenDot);
	pOldbrush=pDC->SelectObject(&brushDot);

	PenDot.DeleteObject();
	brushDot.DeleteObject();

	pDC->SelectObject(pOldbrush);
	pDC->SelectObject(pOldPen);

	for(int curSubAreaNo=0;curSubAreaNo<GetExcellonData().GetSubAreaCnt();++curSubAreaNo)
	{
		unsigned long colorRect=CPointcontrlView::ColorToolRect;
		PenDot.CreatePen(PS_SOLID,1,colorRect);		

		crdDest = GetExcellonData().GetSubAreaCenter(curSubAreaNo);
		crdDest.x += m_xoff;
		crdDest.y += m_yoff;
	
		rect.left = (crdDest.x-GetDoc().GetScanSize()*500)*tempScal;
		rect.top = (crdDest.y-GetDoc().GetScanSize()*500)*tempScal;			
		rect.right = (crdDest.x+GetDoc().GetScanSize()*500)*tempScal;
		rect.bottom = (crdDest.y+GetDoc().GetScanSize()*500)*tempScal;

		pDC->SelectObject(&PenDot);
		pDC->Rectangle(&rect);

		PenDot.DeleteObject();
		pDC->SelectObject(pOldPen);

		SubArea& subarea = GetExcellonData().GetSubAreaData(curSubAreaNo);
		
//处理文件头没有刀具信息，而有点的问题???

		CPoint linetoPiontBegin(0,0);
		CPoint linetoPiontEnd(0,0);
		
		for(int it=0;it<GetExcellonData().GetToolsNum();++it)
		{   
			ToolInfo nToolNo = GetExcellonData().GetToolInfo(it);
			int nSubToolIndex = subarea.GetSameToolIndex(nToolNo.m_nToolIndex);
			if(nSubToolIndex==-1)
				continue;

			unsigned long colorPoint=CPointcontrlView::ColorToolPoint.GetAt(it);
			PenDot.CreatePen(PS_SOLID,1,colorPoint);
			brushDot.CreateSolidBrush(colorPoint);

			pDC->SelectObject(&PenDot);
			pDC->SelectObject(&brushDot); 
			
			int holecnt = subarea.hcvHoleData[nSubToolIndex].hcvHolePos.size();
			if (holecnt<=0) 
				continue ;

			std::vector<HoleClass>::iterator hcv;
			hcv = const_cast<HoleClass*>(subarea.hcvHoleData.begin()+nSubToolIndex);
			std::vector<Coord>::iterator Holecrd,Holecrd1,Holecrd2;
			Coord crd;
			CRD crdX,crdY;

			nCommandCnt = 0;

			while(nCommandCnt<holecnt)
			{
				Holecrd = (hcv->hcvHolePos.begin()+nCommandCnt);
				crd.x=Holecrd->x;
				crd.y=Holecrd->y;
				crd.x/=m_ScalDraw;
				crd.y/=m_ScalDraw;
				crdX=(crd.y+crdDest.x)*tempScal;
				crdY=((-crd.x)+crdDest.y)*tempScal;

				if (isShowPathAndBE)
				{
					if (nCommandCnt==0)
					{
						pDC->Ellipse(int(crdX-pieR)-10,int(crdY-pieR)-10,int(crdX+pieR)+10,int(crdY+pieR)+10);
						
						linetoPiontBegin.x=crdX;
						linetoPiontBegin.y=crdY;
						pDC->MoveTo(linetoPiontBegin);
						pDC->TextOut(linetoPiontBegin.x,linetoPiontBegin.y,"B");

					}
					else if (nCommandCnt==holecnt-1)
					{
						pDC->Ellipse(int(crdX-pieR)-10,int(crdY-pieR)-10,int(crdX+pieR)+10,int(crdY+pieR)+10);

						linetoPiontEnd.x=crdX;
						linetoPiontEnd.y=crdY;
						pDC->TextOut(linetoPiontEnd.x,linetoPiontEnd.y,"E");
					}
					else
					{
						pDC->Ellipse(int(crdX-pieR),int(crdY-pieR),int(crdX+pieR),int(crdY+pieR));

						linetoPiontEnd.x=crdX;
						linetoPiontEnd.y=crdY;
					}

					if (nCommandCnt>0)
						pDC->LineTo(linetoPiontEnd);							
				}
				else
					pDC->Ellipse(int(crdX-pieR),int(crdY+pieR),int(crdX+pieR),int(crdY-pieR));					
				
				nCommandCnt++;
			}

			PenDot.DeleteObject();
			brushDot.DeleteObject();

			pDC->SelectObject(pOldbrush);
			pDC->SelectObject(pOldPen);
		}
	}
}

void CFilePointView::DrawLocalMarkSubArea(CDC *pDC,int index)
{
	RECT rect;
	Coord crdDest;
	int nCommandCnt=0;
	float tempScal = (float)(m_Scal/10000);
	float pieR =3+tempScal/0.02;

	CPen  PenDot;
	PenDot.CreatePen(PS_SOLID, 1,RGB(0,0,0));
	CBrush brushDot(RGB(0,0,0));
	
	CPen* pOldPen;
	CBrush*	pOldbrush;
	pOldPen=(CPen*)pDC->SelectObject(&PenDot);
	pOldbrush=pDC->SelectObject(&brushDot);

	PenDot.DeleteObject();
	brushDot.DeleteObject();

	pDC->SelectObject(pOldbrush);
	pDC->SelectObject(pOldPen);
	
	for(int curSubAreaNo=0;curSubAreaNo<GetExcellonData().GetLocalMarkSubAreaCnt(index);++curSubAreaNo)
	{	
		unsigned long colorRect=CPointcontrlView::ColorToolRect;
		PenDot.CreatePen(PS_SOLID,1,colorRect);

		crdDest = GetExcellonData().GetLocalMarkSubAreaCenter(index,curSubAreaNo);
		crdDest.x += m_xoff;
		crdDest.y += m_yoff;
	
		rect.left = (crdDest.x-GetDoc().GetScanSize()*500)*tempScal;
		rect.top = (crdDest.y-GetDoc().GetScanSize()*500)*tempScal;			
		rect.right = (crdDest.x+GetDoc().GetScanSize()*500)*tempScal;
		rect.bottom = (crdDest.y+GetDoc().GetScanSize()*500)*tempScal;

		pDC->SelectObject(&PenDot);
		pDC->Rectangle(&rect);

		PenDot.DeleteObject();
		pDC->SelectObject(pOldPen);

		SubArea& subarea = GetExcellonData().GetLocalMarkSubAreaData(index,curSubAreaNo);

//处理文件头没有刀具信息，而有点的问题???

		CPoint linetoPiontBegin(0,0);
		CPoint linetoPiontEnd(0,0);
		
		for(int it=0;it<GetExcellonData().GetToolsNum();++it)
		{   
			ToolInfo nToolNo = GetExcellonData().GetToolInfo(it);
			int nSubToolIndex = subarea.GetSameToolIndex(nToolNo.m_nToolIndex);
			if(nSubToolIndex==-1)
				continue;

			unsigned long colorPoint=CPointcontrlView::ColorToolPoint.GetAt(nToolNo.m_nToolIndex-1);
			PenDot.CreatePen(PS_SOLID,1,colorPoint);
			brushDot.CreateSolidBrush(colorPoint);

			pDC->SelectObject(&PenDot);
			pDC->SelectObject(&brushDot); 
			
			int holecnt = subarea.hcvHoleData[nSubToolIndex].hcvHolePos.size();
			if (holecnt<=0) 
				continue ;

			std::vector<HoleClass>::iterator hcv;
			hcv = const_cast<HoleClass*>(subarea.hcvHoleData.begin()+nSubToolIndex);
			std::vector<Coord>::iterator Holecrd,Holecrd1,Holecrd2;
			Coord crd;
			CRD crdX,crdY;

			nCommandCnt = 0;

			while(nCommandCnt<holecnt)
			{
				Holecrd = (hcv->hcvHolePos.begin()+nCommandCnt);
				crd.x=Holecrd->x;
				crd.y=Holecrd->y;
				crd.x/=m_ScalDraw;
				crd.y/=m_ScalDraw;
				crdX=(crd.y+crdDest.x)*tempScal;
				crdY=((-crd.x)+crdDest.y)*tempScal;

				if (isShowPathAndBE)
				{
					if (nCommandCnt==0)
					{
						pDC->Ellipse(int(crdX-pieR)-10,int(crdY-pieR)-10,int(crdX+pieR)+10,int(crdY+pieR)+10);
						
						linetoPiontBegin.x=crdX;
						linetoPiontBegin.y=crdY;
						pDC->MoveTo(linetoPiontBegin);
						pDC->TextOut(linetoPiontBegin.x,linetoPiontBegin.y,"B");

					}
					else if (nCommandCnt==holecnt-1)
					{
						pDC->Ellipse(int(crdX-pieR)-10,int(crdY-pieR)-10,int(crdX+pieR)+10,int(crdY+pieR)+10);

						linetoPiontEnd.x=crdX;
						linetoPiontEnd.y=crdY;
						pDC->TextOut(linetoPiontEnd.x,linetoPiontEnd.y,"E");
					}
					else
					{
						pDC->Ellipse(int(crdX-pieR),int(crdY-pieR),int(crdX+pieR),int(crdY+pieR));

						linetoPiontEnd.x=crdX;
						linetoPiontEnd.y=crdY;
					}

					if (nCommandCnt>0)
						pDC->LineTo(linetoPiontEnd);							
				}
				else
					pDC->Ellipse(int(crdX-pieR),int(crdY+pieR),int(crdX+pieR),int(crdY-pieR));					
				
				nCommandCnt++;
			}

			PenDot.DeleteObject();
			brushDot.DeleteObject();

			pDC->SelectObject(pOldbrush);
			pDC->SelectObject(pOldPen);
		}
	}
}

void CFilePointView::DrawOtherSubArea(CDC *pDC)
{
	RECT rect;
	Coord crdDest;
	int nCommandCnt=0;
	float tempScal = (float)(m_Scal/10000);
	float pieR =3+tempScal/0.02;

	CPen  PenDot;
	PenDot.CreatePen(PS_SOLID, 1,RGB(0,0,0));
	CBrush brushDot(RGB(0,0,0));
	
	CPen* pOldPen;
	CBrush*	pOldbrush;
	pOldPen=(CPen*)pDC->SelectObject(&PenDot);
	pOldbrush=pDC->SelectObject(&brushDot);

	PenDot.DeleteObject();
	brushDot.DeleteObject();

	pDC->SelectObject(pOldbrush);
	pDC->SelectObject(pOldPen);
	
	for(int curSubAreaNo=0;curSubAreaNo<GetExcellonData().GetOtherSubAreaCnt();++curSubAreaNo)
	{
		unsigned long colorRect=CPointcontrlView::ColorToolRect;
		PenDot.CreatePen(PS_SOLID,1,colorRect);		

		crdDest = GetExcellonData().GetOtherSubAreaCenter(curSubAreaNo);
		crdDest.x += m_xoff;
		crdDest.y += m_yoff;
	
		rect.left = (crdDest.x-GetDoc().GetScanSize()*500)*tempScal;
		rect.top = (crdDest.y-GetDoc().GetScanSize()*500)*tempScal;			
		rect.right = (crdDest.x+GetDoc().GetScanSize()*500)*tempScal;
		rect.bottom = (crdDest.y+GetDoc().GetScanSize()*500)*tempScal;

		pDC->SelectObject(&PenDot);
		pDC->Rectangle(&rect);

		PenDot.DeleteObject();
		pDC->SelectObject(pOldPen);

		SubArea& subarea = GetExcellonData().GetOtherSubAreaData(curSubAreaNo);

//处理文件头没有刀具信息，而有点的问题???

		CPoint linetoPiontBegin(0,0);
		CPoint linetoPiontEnd(0,0);
		
		for(int it=0;it<GetExcellonData().GetToolsNum();++it)
		{   
			ToolInfo nToolNo = GetExcellonData().GetToolInfo(it);
			int nSubToolIndex = subarea.GetSameToolIndex(nToolNo.m_nToolIndex);
			if(nSubToolIndex==-1)
				continue;

			unsigned long colorPoint=CPointcontrlView::ColorToolPoint.GetAt(nToolNo.m_nToolIndex-1);
			PenDot.CreatePen(PS_SOLID,1,colorPoint);
			brushDot.CreateSolidBrush(colorPoint);

			pDC->SelectObject(&PenDot);
			pDC->SelectObject(&brushDot); 
			
			int holecnt = subarea.hcvHoleData[nSubToolIndex].hcvHolePos.size();
			if (holecnt<=0) 
				continue ;

			std::vector<HoleClass>::iterator hcv;
			hcv = const_cast<HoleClass*>(subarea.hcvHoleData.begin()+nSubToolIndex);
			std::vector<Coord>::iterator Holecrd,Holecrd1,Holecrd2;
			Coord crd;
			CRD crdX,crdY;

			nCommandCnt = 0;

			while(nCommandCnt<holecnt)
			{
				Holecrd = (hcv->hcvHolePos.begin()+nCommandCnt);
				crd.x=Holecrd->x;
				crd.y=Holecrd->y;
				crd.x/=m_ScalDraw;
				crd.y/=m_ScalDraw;
				crdX=(crd.y+crdDest.x)*tempScal;
				crdY=((-crd.x)+crdDest.y)*tempScal;

				if (isShowPathAndBE)
				{
					if (nCommandCnt==0)
					{
						pDC->Ellipse(int(crdX-pieR)-10,int(crdY-pieR)-10,int(crdX+pieR)+10,int(crdY+pieR)+10);
						
						linetoPiontBegin.x=crdX;
						linetoPiontBegin.y=crdY;
						pDC->MoveTo(linetoPiontBegin);
						pDC->TextOut(linetoPiontBegin.x,linetoPiontBegin.y,"B");

					}
					else if (nCommandCnt==holecnt-1)
					{
						pDC->Ellipse(int(crdX-pieR)-10,int(crdY-pieR)-10,int(crdX+pieR)+10,int(crdY+pieR)+10);

						linetoPiontEnd.x=crdX;
						linetoPiontEnd.y=crdY;
						pDC->TextOut(linetoPiontEnd.x,linetoPiontEnd.y,"E");
					}
					else
					{
						pDC->Ellipse(int(crdX-pieR),int(crdY-pieR),int(crdX+pieR),int(crdY+pieR));

						linetoPiontEnd.x=crdX;
						linetoPiontEnd.y=crdY;
					}

					if (nCommandCnt>0)
						pDC->LineTo(linetoPiontEnd);							
				}
				else
					pDC->Ellipse(int(crdX-pieR),int(crdY+pieR),int(crdX+pieR),int(crdY-pieR));					
				
				nCommandCnt++;
			}

			PenDot.DeleteObject();
			brushDot.DeleteObject();

			pDC->SelectObject(pOldbrush);
			pDC->SelectObject(pOldPen);
		}	
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFilePointView diagnostics

#ifdef _DEBUG
void CFilePointView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CFilePointView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFilePointView message handlers

LRESULT CFilePointView::OnReflashPoint(WPARAM wParam,LPARAM lParam)
{
	if(wParam == 1)
	{
		if(m_Scal>25*256) return 0;
		m_Zoom = NONE;
		ZoomIn();
	}
	if(wParam == 2)
	{
		if(m_Scal<=24) return 0;
		m_Zoom = NONE;
		ZoomOut();
	}
	if(wParam == 3)
	{
		m_Zoom = NONE;
		ZoomReset();
	}
	if(wParam == 4)
	{
		m_Zoom = RECTZOOMIN;
		return 0;
	}
	if(wParam == 5)
	{
		int m_nID = (int)lParam;
		if (m_nID==0)
			isShowPathAndBE=FALSE;
		else
			isShowPathAndBE=TRUE;
	}

	Invalidate();
	return 0;
}

void CFilePointView::ZoomIn()
{//放大
	m_Scal= m_Scal*ZoomRatio;

	CPoint pt =GetScrollPosition();
	pt.x *=ZoomRatio;
	pt.y *=ZoomRatio;

	CSize size;
	float tempScal = (float)m_Scal/10000;
	size.cx = TableSize.cx*tempScal;
	size.cy = TableSize.cy*tempScal;

	SetScrollSizes(MapMode, size);			//重置滚动条
	ScrollToPosition(pt);					//设定新位置
}

void CFilePointView::ZoomOut()
{//缩小
	m_Scal= m_Scal/ZoomRatio;

	CPoint pt =GetScrollPosition();
	pt.x /=ZoomRatio;
	pt.y /=ZoomRatio;

	CSize size;
	float tempScal = (float)m_Scal/10000;
	size.cx = TableSize.cx*tempScal;
	size.cy = TableSize.cy*tempScal;

	SetScrollSizes(MapMode, size);			//重置滚动条
	if(m_Scal>48.0)
		ScrollToPosition(pt);				//设定新位置
}

void CFilePointView::ZoomReset()
{//全显m_ScalDraw;
	m_Scal= 24.0;

	CPoint pt;
	pt.x = 0;
	pt.y = 0;

	CSize size;
	float tempScal = (float)m_Scal/10000;
	size.cx = TableSize.cx*tempScal;
	size.cy = TableSize.cy*tempScal;

	SetScrollSizes(MapMode, size);			//重置滚动条
	ScrollToPosition(pt);					//设定新位置
}

void CFilePointView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_Zoom == RECTZOOMIN)
	{
		m_ptdownInView = point;
		m_ptlastInView = point;

		m_ptZoomInFirst = point;	//保存矩形区域的左上角坐标
		SetCapture();				//设置输入焦点

		LButtomDown = true;
	}
	
	CScrollView::OnLButtonDown(nFlags, point);
}

void CFilePointView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default	
	if (LButtomDown&&(m_Zoom == RECTZOOMIN))
	{
		CClientDC dc(this);
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENWSE));

		CRect rect1(m_ptdownInView.x, m_ptdownInView.y, m_ptlastInView.x, m_ptlastInView.y);
		rect1.NormalizeRect();
		dc.DrawFocusRect(rect1);
		rect1.SetRect(m_ptdownInView.x, m_ptdownInView.y, point.x, point.y);
		rect1.NormalizeRect();
		dc.DrawFocusRect(rect1);

		m_ptlastInView = point;	
	}
	
	CScrollView::OnMouseMove(nFlags, point);
}

void CFilePointView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default	
	if (m_Zoom == RECTZOOMIN)
	{
		CClientDC dc(this);

		ReleaseCapture();
		
		LButtomDown= false;
		m_ptZoomInLast = point;

		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW)); 

		if ((m_ptZoomInLast.x != m_ptZoomInFirst.x) && (m_ptZoomInLast.y != m_ptZoomInFirst.y))
		{
			CRect rect;
			GetClientRect(&rect);
			
			float Xini = (float)(rect.right - rect.left)/abs(m_ptZoomInLast.x - m_ptZoomInFirst.x);
			float Yini = (float)(rect.bottom - rect.top)/abs(m_ptZoomInLast.y - m_ptZoomInFirst.y);

			if (m_Scal>25*256||Xini > 25 || Yini > 25 || Xini < 0.2 || Yini < 0.2)
			{
				Invalidate();
				CScrollView::OnLButtonUp(nFlags, point);
				return; 
			}
			
			Xini=(Xini+Yini)/2;
			m_Scal *= Xini;

			dc.SetMapMode(MapMode);
			CPoint pt =GetScrollPosition();
			dc.LPtoDP(&pt);
			pt.x =(pt.x+m_ptZoomInFirst.x)*Xini;
			pt.y =(pt.y+m_ptZoomInFirst.y)*Xini;
			dc.DPtoLP(&pt);	
			
			CSize size;
			float tempScal = (float)m_Scal/10000;
			size.cx = TableSize.cx*tempScal;
			size.cy = TableSize.cy*tempScal;

			SetScrollSizes(MapMode, size);			//重置滚动条
			ScrollToPosition(pt);					//设定新位置

			Invalidate();
		}	
	}
	
	CScrollView::OnLButtonUp(nFlags, point);
}
