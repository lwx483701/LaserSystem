// ProgressCheckCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "ProgressCheckCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgressCheckCtrl
#define  TUNERADIO  2000

CProgressCheckCtrl::CProgressCheckCtrl()
{
m_backgroundBrush.CreateSolidBrush(GetSysColor(COLOR_BTNFACE));
m_CenterPos = CPoint(2500,2500);
m_BlockHigh = 0;
m_BlockWidth = 0;
m_lSelIndexv.RemoveAll();
}

CProgressCheckCtrl::~CProgressCheckCtrl()
{
}


BEGIN_MESSAGE_MAP(CProgressCheckCtrl, CWnd)
	//{{AFX_MSG_MAP(CProgressCheckCtrl)
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CProgressCheckCtrl message handlers

BOOL CProgressCheckCtrl::Create(DWORD dwStyle, const RECT &rect, CWnd *pParentWnd, UINT nID) 
{
//	
	Block pl(Coord(25000,25000),50000,50000);
	Block p2(Coord(25000,50000),20000,20000);
	Block p3(Coord(25000,75000),20000,20000);
	Block p4(Coord(25000,100000),20000,20000);
	
	Block p5(Coord(50000,25000),20000,20000);
	Block p6(Coord(50000,50000),20000,20000);
	Block p7(Coord(50000,75000),20000,20000);
	Block p8(Coord(50000,100000),20000,20000);

	


	
	
	
	static CString className = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW);
	BOOL bRet = CWnd::CreateEx(WS_EX_CLIENTEDGE, 
								className,
								NULL,
								dwStyle,
								rect.left,
								rect.top,
								rect.right - rect.left,
								rect.bottom - rect.top,
								pParentWnd->GetSafeHwnd(),
								(HMENU) nID);
	
	//	m_nID = nID;
	//	m_pParentWnd = pParentWnd;
	
	SetCursor(LoadCursor(NULL, IDC_ARROW));
		m_rcScreen =rect;	
	return bRet;


}
void CProgressCheckCtrl::SetBlockColor(int nIndex, COLORREF crColor)
{
 this->m_crColor.SetAt(nIndex,crColor);	
}
void CProgressCheckCtrl::RemoveAllData()
{
	this->m_Array.RemoveAll();
}

void CProgressCheckCtrl::SetBlock(int nIndex,const Coord iPoint,const long lWidth,const long lHigh,const COLORREF crColor)
{
 //this->m_crColor.SetAt(nIndex,crColor);
	Block OpBloack;
	OpBloack.point= iPoint;
	OpBloack.high = lHigh;
	OpBloack.width = lWidth;
	OpBloack.ColorBlock = crColor;
	m_Array.Add(OpBloack);
}

void CProgressCheckCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	for(int iBlocknum=0;iBlocknum<m_Array.GetSize();iBlocknum++)
	{
			CBrush bru(m_Array.GetAt(iBlocknum).ColorBlock);
			Coord  crd(m_Array.GetAt(iBlocknum).point);
			long   Wid(m_Array.GetAt(iBlocknum).width);
			long   Hig(m_Array.GetAt(iBlocknum).high);
			DrawBlock(iBlocknum,crd,Wid,Hig,bru,dc);

	}
	
}

void CProgressCheckCtrl::DrawBlock(int iBlocknum,const Coord crd,const long lWidth,const long lHigh ,CBrush &brush, CDC &dc)
{
	GetClientRect(m_rcClient);
	CRect rect(((crd.x-lWidth/2)/TUNERADIO),(crd.y-lHigh/2)/TUNERADIO,(crd.x+lWidth/2)/TUNERADIO,(crd.y+lHigh/2)/TUNERADIO);//= m_RectArray.GetAt(iBlocknum);
	
	rect.bottom = -rect.bottom + m_rcClient.bottom;
	rect.top = -rect.top + m_rcClient.bottom;
	dc.Rectangle(&rect);
	
	rect.left++;
	rect.top--;
	rect.bottom++;
	rect.right--;
	
	dc.FillRect(rect, &brush);
	
}



void CProgressCheckCtrl::Refresh()
{
Invalidate();
}

void CProgressCheckCtrl::Update(CPoint ptCenter, long width, long high)
{
	CClientDC dc(this);
	CRect rect;
	rect.top = (ptCenter.y-high)/1000;
	rect.bottom = (ptCenter.y+high)/1000;
	rect.left = (ptCenter.x-width)/1000;
	rect.right = (ptCenter.x+width)/1000;
	
	dc.Rectangle(&rect);
	rect.left++;
	rect.top++;
	rect.bottom--;
	rect.right--;
	
	CBrush brush;
	brush.CreateSolidBrush(RGB(255,255,255));
	dc.FillRect(rect, &brush);
}

void CProgressCheckCtrl::Update(CRect lrect,const COLORREF crColor)
{
	CClientDC dc(this);

	
	dc.Rectangle(&lrect);
	lrect.left++;
	lrect.top++;
	lrect.bottom--;
	lrect.right--;
	
	CBrush brush;
	brush.CreateSolidBrush(crColor);
	dc.FillRect(lrect, &brush);
}
void CProgressCheckCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CClientDC dc(this);
	dc.DPtoLP(&point);
	for(int nBlock =0 ;nBlock<m_Array.GetSize();nBlock++)
	{
		 CRect rect;//(m_Array.GetAt(nBlock).point.x);// = m_Array.GetAt(nBlock).;
		 rect.top = -((m_Array.GetAt(nBlock).point.y-m_Array.GetAt(nBlock).high/2)/TUNERADIO)+ m_rcClient.bottom;
		 rect.bottom = -((m_Array.GetAt(nBlock).point.y+m_Array.GetAt(nBlock).high/2)/TUNERADIO)+ m_rcClient.bottom;
		// rect.top = rect.top; //+ m_rcClient.bottom;
		 long temp;
		 temp = rect.bottom;
		 rect.bottom= rect.top;
		 rect.top=temp ;
		 rect.left = (m_Array.GetAt(nBlock).point.x-m_Array.GetAt(nBlock).width/2)/TUNERADIO;
		 rect.right = (m_Array.GetAt(nBlock).point.x+m_Array.GetAt(nBlock).width/2)/TUNERADIO;
		 
		 if(rect.PtInRect(point))
		 {
			 COLORREF	CurColor =  BLANKED_BLOCKS_SELCOLOR;
			 Update(rect,CurColor);
			
				m_lSelIndexv.Add(nBlock);
			 break;
		 }
	}
	CWnd::OnLButtonUp(nFlags, point);
}

void CProgressCheckCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{

	
	CWnd::OnMouseMove(nFlags, point);
}

void CProgressCheckCtrl::SetBlockWidth(UINT nWidth,UINT nR,UINT nC)
{
	m_ulBlockWidth = 25/50.0*nWidth;
	m_ulBlockHeight = m_ulBlockWidth;
	CRect rect;
	rect = m_rcScreen;
	long lHeight = m_ulBlockHeight* nR;
	long lWidth  = m_ulBlockWidth * nC;
	CPoint pt = m_rcScreen.CenterPoint(); 
	rect.left = (pt.x - lWidth/2); 
	rect.top  = (pt.y - lHeight/2);
	rect.bottom =(lHeight + rect.top+5);
	rect.right  =  lWidth + rect.left+5;
	MoveWindow(&rect,TRUE);

}
