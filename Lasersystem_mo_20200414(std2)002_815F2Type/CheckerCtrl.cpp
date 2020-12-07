//Author:			Mehdi Mousavi
//Data of release:	8th of September, 2000
//Email:			Webmaster@modemmania.com

// CheckerCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "CheckerCtrl.h"
#include "Resource.h"
#include "warninginfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCheckerCtrl



CCheckerCtrl::CCheckerCtrl()
{
	//Sets the background brush of the client area
	m_backgroundBrush.CreateSolidBrush(GetSysColor(COLOR_BTNFACE));
//	m_backgroundBrush.CreateSolidBrush(CHECKERCTRLBACKGROUND);
	
	//Resets m_nyPos for scrolling purposes
	m_nyPos = 0;

	//Resets m_nBlockStartPos so that when the WM_PAINT message
	//is triggered, the control starts to show blocks
	//from m_nBlockStartPos position
	m_nBlockStartPos = 0;

	//Sets the starting index of blocks
	m_nStartIndex = 0;

	//Total number of blocks
	m_nNumberofBlocks = 0;

	//Offset for scrolling purposes
	m_nOffset = 0;

	m_nTotalVisibleBlocks = 0;

	m_nBlocksPerRow = 0;

    m_ulBlockWidth = 40;
    m_ulBlockHeight =m_ulBlockWidth-2;    

	m_lSelIndexv.clear();
	m_iSelectFlag.RemoveAll();
}

CCheckerCtrl::~CCheckerCtrl()
{
}

BOOL CCheckerCtrl::Create(DWORD dwStyle, const RECT &rect, CWnd *pParentWnd, UINT nID)
{
	//Postcondition:
	//	Creates a window after being registered, as well as
	//	setting all the required variables used hereinafter.
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

	m_nID = nID;
	m_pParentWnd = pParentWnd;
	
	SetCursor(LoadCursor(NULL, IDC_ARROW));
	m_rcScreen =rect;	
	return bRet;
}


BEGIN_MESSAGE_MAP(CCheckerCtrl, CWnd)
	//{{AFX_MSG_MAP(CCheckerCtrl)
	ON_WM_PAINT()
	ON_WM_VSCROLL()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCheckerCtrl message handlers

void CCheckerCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	//Fill the background color of the client area
	dc.FillRect(m_rcClient, &m_backgroundBrush);

	UINT nColumn = 0, nRow = 0;
	
	//Calculate the index of the last visible block	within the client area

	UINT nBlockEndPos = m_nBlockStartPos + m_nTotalVisibleBlocks + m_nBlocksPerRow;
	if(nBlockEndPos > m_nNumberofBlocks)
		nBlockEndPos = m_nNumberofBlocks;

	for(UINT i = m_nBlockStartPos; i < nBlockEndPos; i++)
	{
		CBrush brush(m_crColor.GetAt(i));
		SetBlock(nRow, nColumn, brush, dc);
		if((i + 1 - m_nBlockStartPos) % m_nBlocksPerRow == 0)
		{
			nRow++;
			nColumn = 0;
		}
		else
			nColumn++;
	}
}

void CCheckerCtrl::SetTotalBlocks(const UINT nRows, const UINT nCols, const UINT nStartIndex)
{
	
	m_nBlocksPerRow= nRows;
	m_nBlocksPerColumn = nCols;
	m_nNumberofBlocks = nRows * nCols;

	m_crColor.RemoveAll();
	m_crColor.SetSize(m_nNumberofBlocks);

	m_nTotalVisibleBlocks = m_nNumberofBlocks;

//	m_lSelIndexv.clear();
//	m_iSelectFlag.RemoveAll();
}

void CCheckerCtrl::SelectOthers()
{
	m_lSelIndexv.clear();
	m_iSelectFlag.RemoveAll();
	for(int nIndex=0;nIndex<m_nNumberofBlocks;nIndex++)
	{
		int kkk=m_crColor.GetSize();
		/*if( GetColor(nIndex) == BLANKED_BLOCKS_SELCOLOR || GetColor(nIndex) ==BLANKED_BLOCKS_COLOR)		
		SetBlock(nIndex,BLANKED_BLOCKS_UNSELCOLOR);
		else
		SetBlock(nIndex,BLANKED_BLOCKS_SELCOLOR);		
		Update(nIndex);
		*/
		
		if( GetColor(nIndex) == BLANKED_BLOCKS_SELCOLOR ) 
		{
			
			for(int i=0;i<m_iSelectFlag.GetSize();i++)
			{
				if(nIndex ==m_iSelectFlag.GetAt(i) )  
				{						
					m_lSelIndexv.erase(m_lSelIndexv.begin()+i);
					m_iSelectFlag.RemoveAt (m_iSelectFlag.GetSize()-1);						
				}
			}			
			//m_crColor.SetAt(nIndex,BLANKED_BLOCKS_UNSELCOLOR);
			SetBlock(nIndex,BLANKED_BLOCKS_UNSELCOLOR);
		}
		else if (GetColor(nIndex)!=BLANKED_BLOCKS_COLOR)
		{
			
			//UINT nY = nIndex / (m_nBlocksPerColumn-1);
			UINT nY = nIndex / m_nBlocksPerRow;
			UINT nX = nIndex % m_nBlocksPerRow;
			
			SetBlock(nIndex,BLANKED_BLOCKS_SELCOLOR);
			//	m_crColor.SetAt(nIndex,BLANKED_BLOCKS_SELCOLOR);
			
			m_lSelIndexv.push_back(BlockPos(nX,nY));
			m_iSelectFlag.Add(nIndex);
		}
		Update(nIndex);
	}
}
void CCheckerCtrl::SelectOthers2()
{
	m_lSelIndexv.clear();
	m_iSelectFlag.RemoveAll();
	//for(int nIndex=0;nIndex<m_nNumberofBlocks;nIndex++)GetSubAreaCnt

	for(int nIndex=0;nIndex<GetExcellonData().GetSubAreaCnt();nIndex++)
	{		
		for(int n=0; n<m_lSelIndexvCopy.size();++n)
		{
			CCheckerCtrl::BlockPos blkpos = m_lSelIndexvCopy[n];
			int selectIndex=blkpos.nRow*GetExcellonData().GetSubAreaRow()+blkpos.nCol;
            			
			UINT nY = nIndex/m_nBlocksPerRow;
			UINT nX = nIndex%m_nBlocksPerRow;
					
					/*
					m_nBlocksPerRow= nRows;
					m_nBlocksPerColumn = nCols;
					*/
					m_lSelIndexv.push_back(BlockPos(nX,nY));
					m_iSelectFlag.Add(nIndex);	

		
			if (selectIndex==nIndex)
			{
				for(int i=0;i<m_iSelectFlag.GetSize();i++)
				{
					if(nIndex ==m_iSelectFlag.GetAt(i) )  
					{						
						m_lSelIndexv.erase(m_lSelIndexv.begin()+i);
						m_iSelectFlag.RemoveAt (m_iSelectFlag.GetSize()-1);						
					}
				}
				
				m_crColor.SetAt(nIndex,BLANKED_BLOCKS_UNSELCOLOR);
			}
			else
			{
					m_crColor.SetAt(nIndex,BLANKED_BLOCKS_SELCOLOR);
					
					UINT nY = nIndex / (m_nBlocksPerColumn-1);
					UINT nX = nIndex % m_nBlocksPerRow;
					
					/*
					m_nBlocksPerRow= nRows;
					m_nBlocksPerColumn = nCols;
					*/
					m_lSelIndexv.push_back(BlockPos(nX,nY));
					m_iSelectFlag.Add(nIndex);				
			}
			Update(nIndex);
		}
	}
}

void CCheckerCtrl::SetTotalBlocks(const UINT nNumberofBlocks, const UINT nStartIndex)
{
	//Postcondition:
	//	Sets the member variable m_nNumberofBlocks to the specified
	//	number of blocks. Then creates an array of COLORREF, sized
	//	nNumberofBlocks, and initialize it with white color.
	//	Thereafter, it computes m_nOffset for scrolling purposes.
	m_nNumberofBlocks = nNumberofBlocks;

	m_crColor.SetSize(m_nNumberofBlocks);

	for(UINT i = 0; i < m_nNumberofBlocks; i++)
		m_crColor.SetAt(i, BLANKED_BLOCKS_COLOR);

	GetClientRect(m_rcClient);
	m_nBlocksPerRow = m_rcClient.Width() / m_ulBlockHeight;
	m_nBlocksPerColumn = m_rcClient.Height() / m_ulBlockWidth;
	
	m_nTotalVisibleBlocks = m_nBlocksPerRow * m_nBlocksPerColumn;
#if 1	
	//Calculate the vertical scroll bar's range
	if (m_nBlocksPerRow<=0)
		return ;
	int nOffset = (m_nNumberofBlocks / m_nBlocksPerRow);
	if(m_nNumberofBlocks % m_nBlocksPerRow != 0)
		nOffset++;
	
	m_nOffset = nOffset - m_nBlocksPerColumn;
	if(m_nOffset > 0)
		SetScrollRange(SB_VERT, 0, m_nOffset);
#endif
	//	Sets the starting index of blocks
	m_nStartIndex = nStartIndex;

//	m_lSelIndexv.clear(); 
}

void CCheckerCtrl::SetBlock(int nRow, int nColumn, CBrush &brush, CDC &dc)
{
	//Postcondition:
	//	Places a block on nRow, nColumn ordered pair, 
	//	and paints it with brush color
	CRect rect = GetRect(nRow, nColumn);

	dc.Rectangle(&rect);
	
//	char buf[64];
//	sprintf(buf," nRow=%d,nCol=%d\n left=%d,right=%d, top=%d,bottom=%d",
//		nRow,nColumn,rect.left,rect.right,rect.top,rect.bottom);
//	AfxMessageBox(buf);

	rect.left++;
	rect.top++;
	rect.bottom--;
	rect.right--;

	dc.FillRect(rect, &brush);
	dc.SetBkMode(TRANSPARENT);//ly add 20120711

	int num=0;
	if((nRow%2)==0)
	{
		num = m_nBlocksPerRow*(nRow)+nColumn+1;
	}
	else
	{
		num = m_nBlocksPerRow*(nRow)+(m_nBlocksPerRow-nColumn);
	}
	CString str;
	str.Format("%d",num);
	dc.DrawText(str,rect,DT_CENTER);//ly add 20120711
}

void CCheckerCtrl::SetBlock(const UINT nBlockNumber, const COLORREF crColor)
{
	//Postcondition:
	//	Sets the color of a specified block number to crColor
	ASSERT(nBlockNumber - m_nStartIndex < m_nNumberofBlocks);
	m_crColor.SetAt(nBlockNumber - m_nStartIndex, crColor);
}
#if 1
void CCheckerCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{

	int nyOffset;
	switch(nSBCode)
	{
	case SB_PAGEDOWN:
		if(m_nyPos < m_nOffset)
		{
			if(m_nyPos + 2 < m_nOffset)
				nyOffset = 2;
			else
				nyOffset = m_nOffset - m_nyPos;

			m_nyPos += nyOffset;
			m_nBlockStartPos += m_nBlocksPerRow * nyOffset;

			SetScrollPos(SB_VERT, m_nyPos);
			ScrollWindow(0, -nyOffset * m_ulBlockWidth);
		}
		break;

	case SB_PAGEUP:
		if(m_nyPos > 0)
		{
			if(m_nyPos - 2 > 0)
				nyOffset = 2;
			else
				nyOffset = m_nyPos;

			m_nBlockStartPos -= m_nBlocksPerRow * nyOffset;

			m_nyPos -= nyOffset;
			SetScrollPos(SB_VERT, m_nyPos);
			ScrollWindow(0, nyOffset * m_ulBlockWidth);
		}
		break;

	case SB_LINEUP:
		if(m_nyPos > 0)
		{
			m_nBlockStartPos -= m_nBlocksPerRow;

			m_nyPos--;
			SetScrollPos(SB_VERT, m_nyPos);
			ScrollWindow(0, m_ulBlockWidth);
		}
		break;

	case SB_LINEDOWN:
		if(m_nyPos < m_nOffset)
		{
			m_nBlockStartPos += m_nBlocksPerRow;

			m_nyPos++;
			SetScrollPos(SB_VERT, m_nyPos);
			ScrollWindow(0, -m_ulBlockWidth);
		}
		break;
	}

	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}
#endif

void CCheckerCtrl::Refresh()
{
	//Postcondition:
	Invalidate();
}

COLORREF CCheckerCtrl::GetBlock(const UINT nBlockNumber) const
{
	//Precondition:
	ASSERT(nBlockNumber >= m_nStartIndex && nBlockNumber - m_nStartIndex <= m_nNumberofBlocks);
	return m_crColor.GetAt(nBlockNumber - m_nStartIndex);
}

void CCheckerCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	SetFocus();
	
	DWORD dwPos = GetMessagePos();
	CPoint clickedPoint((int)(short)LOWORD(dwPos), (int)(short)HIWORD(dwPos));
	ScreenToClient(&clickedPoint);
	
	if(clickedPoint.x % m_ulBlockHeight == 0 || clickedPoint.y % m_ulBlockWidth == 0)
		m_bShouldUpdated = FALSE;
	else
	{
		UINT nY = clickedPoint.y / m_ulBlockWidth;
		UINT nX = clickedPoint.x / m_ulBlockHeight;
		
		UINT nIndex = (m_nBlocksPerColumn-1-nY) * m_nBlocksPerRow + nX + m_nyPos * m_nBlocksPerRow;
		
//		if(nIndex < m_nNumberofBlocks && nX < m_nBlocksPerRow)					//20190402
		if((nIndex < m_nNumberofBlocks) && (nX < m_nBlocksPerRow) && (GetColor(nIndex) != BLANKED_BLOCKS_COLOR))
		{
			SetCapture();

			m_bShouldUpdated = TRUE;

			CString strNumber;
			strNumber.Format("%d", nIndex + m_nStartIndex);			
					
			tooltipRect.left--;
			tooltipRect.top--;
			tooltipRect.bottom++;
			tooltipRect.right++;
			
			if( GetColor(nIndex) == BLANKED_BLOCKS_SELCOLOR)
			{
				for(int i=0;i<m_iSelectFlag.GetSize();i++)
				{
					if(nIndex ==m_iSelectFlag.GetAt(i) )  
					{						
						m_lSelIndexv.erase(m_lSelIndexv.begin()+i);
						m_iSelectFlag.RemoveAt (m_iSelectFlag.GetSize()-1);						
					}
				}
				
				SetBlock(nIndex,BLANKED_BLOCKS_UNSELCOLOR);
			}
			else
			{
				SetBlock(nIndex,BLANKED_BLOCKS_SELCOLOR);
				m_lSelIndexv.push_back(BlockPos(nX,m_nBlocksPerColumn-1-nY));
				m_iSelectFlag.Add(nIndex);
			}

			Update(nIndex);
		}
		else											//20190402
			m_bShouldUpdated = FALSE;
	}
/*	
	for(int j=0;j<m_lSelIndexv.size();j++)
	{
	TRACE("tttttttttttttt  %d%d\n", m_lSelIndexv[j].nRow,m_lSelIndexv[j].nCol);
	}
*/
	CWnd::OnLButtonDown(nFlags, point);
}

void CCheckerCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if(m_bShouldUpdated)
	{
		CClientDC dc(this);
		InvalidateRect(&tooltipRect, FALSE);
		ReleaseCapture();
		m_bShouldUpdated = FALSE;
	}

	CWnd::OnLButtonUp(nFlags, point);
}

void CCheckerCtrl::CreateSafeTooltipRect(int iIndex, LPCTSTR lpszText)
{
//	tooltipRect = 
}

void CCheckerCtrl::CreateSafeTooltipRect(int x, int y, LPCTSTR lpszText)
{
	int nTextLength = strlen(lpszText);
	int nTextWidth = 25;//nTextLength;
	if(nTextWidth < 5)
		nTextWidth = 5;
	
	if(x + m_ulBlockWidth * nTextWidth <= m_rcClient.right)
		tooltipRect.right = x + nTextLength * nTextWidth;
	else
		tooltipRect.right = x - nTextLength * nTextWidth;

	if(y + m_ulBlockWidth <= m_rcClient.bottom)
		tooltipRect.bottom = y + m_ulBlockWidth;
	else
		tooltipRect.bottom = y - m_ulBlockWidth;

	tooltipRect.left = x;
	tooltipRect.top = y;

	if(tooltipRect.left > tooltipRect.right)
	{
		int nTemp = tooltipRect.left;
		tooltipRect.left = tooltipRect.right;
		tooltipRect.right = nTemp;
	}
	if(tooltipRect.top > tooltipRect.bottom)
	{
		int nTemp = tooltipRect.bottom;
		tooltipRect.bottom = tooltipRect.top;
		tooltipRect.top = nTemp;
	}
}

void CCheckerCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
//	SetCursor(LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_SELECTBLOCK)));
	SetCursor(LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_SELCUR)));
	CWnd::OnMouseMove(nFlags, point);
}

void CCheckerCtrl::Reset()
{
	for(UINT i = 0; i < m_nNumberofBlocks; i++)
		m_crColor.SetAt(i, BLANKED_BLOCKS_COLOR);

	m_lSelIndexv.clear();
	m_iSelectFlag.RemoveAll();
}

void CCheckerCtrl::Update(const UINT nBlockNumber)
{
	//Precondition:
	//	nBlockNumber must be in the range of the defined blocks
	//Postcondition:
	//	Updates the color of a specified index on CRT, if and only
	//	if it's already visible
	ASSERT(nBlockNumber >= m_nStartIndex && nBlockNumber - m_nStartIndex <= m_nNumberofBlocks);

	if(IsVisible(nBlockNumber))
	{
		UINT nRow = (nBlockNumber - m_nStartIndex) / m_nBlocksPerRow - m_nyPos;
		UINT nColumn = (nBlockNumber - m_nStartIndex) % m_nBlocksPerRow;
		
		CClientDC dc(this);
		CRect rect = GetRect(nRow, nColumn);
		
		rect.left++;
		rect.top++;
		rect.bottom--;
		rect.right--;
		
		CBrush brush;
		brush.CreateSolidBrush(m_crColor.GetAt(nBlockNumber - m_nStartIndex));
		dc.FillRect(rect, &brush);

		dc.SetBkMode(TRANSPARENT);//ly add 20120711

		int num=0;
		if((nRow%2)==0)
		{
			num = m_nBlocksPerRow*(nRow)+nColumn+1;
		}
		else
		{
			num = m_nBlocksPerRow*(nRow)+(m_nBlocksPerRow-nColumn);
		}
		CString str;
		str.Format("%d",num);

		dc.DrawText(str,rect,DT_CENTER);//ly add 20120711
	}
}

CRect CCheckerCtrl::GetRect(const UINT nRow, const UINT nColumn)
{
	//Postcondition:
	CRect PanRect;
	CRect rect;

	rect.left    = nColumn * m_ulBlockHeight   + 1;
	rect.right   = rect.left + m_ulBlockHeight -1;

	rect.top     = (m_nBlocksPerColumn-1-nRow) * m_ulBlockWidth + 1;
	rect.bottom  = rect.top + m_ulBlockWidth  -1;

	return rect;
}

BOOL CCheckerCtrl::IsVisible(const UINT nBlockNumber)
{
	//Calculate the index of the last visible block
	//within the client area
	UINT nBlockEndPos = m_nBlockStartPos + m_nTotalVisibleBlocks + m_nBlocksPerRow;
	if(nBlockEndPos > m_nNumberofBlocks)
		nBlockEndPos = m_nNumberofBlocks;

	if(nBlockNumber >= m_nBlockStartPos && nBlockNumber <= nBlockEndPos)
		return TRUE;
	else
		return FALSE;
}

void CCheckerCtrl::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	SetFocus();
	if(!(point.x % m_ulBlockHeight == 0 || point.y % m_ulBlockWidth == 0))
	{
		UINT nY = point.y / m_ulBlockWidth;
		UINT nX = point.x / m_ulBlockHeight;

		UINT nIndex = nY * m_nBlocksPerRow + nX + m_nyPos * m_nBlocksPerRow;
		if(nIndex < m_nNumberofBlocks && nX < m_nBlocksPerRow)
			m_pParentWnd->PostMessage(WM_CHECKERCTRL_RBUTTONDOWN, m_nID, nIndex + m_nStartIndex);
	}

	CWnd::OnRButtonDown(nFlags, point);
}

COLORREF CCheckerCtrl::GetColor(int nIndex) const
{
    return m_crColor.GetAt(nIndex);
}

int CCheckerCtrl::GetSelectBlockNum()const
{
   return m_lSelIndexv.size();
}

CCheckerCtrl::BlockPos CCheckerCtrl::GetSelectBlockPos(unsigned int unIndex)
{
    ASSERT(unIndex<m_lSelIndexv.size());
	char ez[256]={""};//ly 20110404
    if(unIndex>=m_lSelIndexv.size())
	{
		strncpy(ez,GetLang().GetWarningText(11001),256);
	   AfxMessageBox(ez);//"读取选取区域 超出范围"
	   return BlockPos(0,0);
	}
	return m_lSelIndexv[unIndex];
}

void CCheckerCtrl::SetBlockWidth(UINT nWidth,UINT nR,UINT nC)
{
//	m_ulBlockWidth = 25/50.0*nWidth;
	m_ulBlockWidth = 0.45*nWidth;												//20161109
	
	m_ulBlockHeight = m_ulBlockWidth;

	CRect rect;
	rect = m_rcScreen;

	long lHeight = m_ulBlockHeight* nR;
	long lWidth  = m_ulBlockWidth * nC;

	CPoint pt = m_rcScreen.CenterPoint(); 

	rect.left = pt.x - lWidth/2; 
	rect.top  = pt.y - lHeight/2;  

	rect.bottom =  lHeight + rect.top+5;
	rect.right  =  lWidth + rect.left+5;

	MoveWindow(&rect,TRUE);

}
