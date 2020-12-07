// UVGrid.cpp: implementation of the CUVGrid class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "uvmaker.h"
#include "UVGrid.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//using namespace UVMAKER;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUVGrid::CUVGrid()
:m_nRow(30)
,m_nCol(30)
{
	BlockSize();

	m_arrColor.RemoveAll();
	m_arrColor.SetSize(m_nRow*m_nCol);
//	SetBlockColor(0,BLANKED_BLOCKS_UNSELCOLOR);
}

CUVGrid::~CUVGrid()
{
	Clear();
}

void CUVGrid::SetBlockColor(UINT nBlockIndex, COLORREF crBlock)
{
	ASSERT(nBlockIndex <= m_nCol*m_nRow);
	m_arrColor.SetAt(nBlockIndex, crBlock);
}

COLORREF CUVGrid::GetBlockColor(UINT nBlockIndex)
{
	ASSERT(nBlockIndex <= m_nCol*m_nRow);
	return m_arrColor.GetAt(nBlockIndex);
}

void CUVGrid::SetBlockWidth(double fBlockWidth)
{
	m_fBlockWidth = fBlockWidth;
}

double CUVGrid::GetBlockWidth()
{
	return m_fBlockWidth;
}

void CUVGrid::SetBlockHeight(double fBlockHeight)
{
	m_fBlockHeight = fBlockHeight;
}

double CUVGrid::GetBlockHeight()
{
	return m_fBlockHeight;
}

void CUVGrid::SetCol(UINT nCol)
{
	m_nCol = nCol;
}

UINT CUVGrid::GetCol()
{
	return m_nCol;
}

void CUVGrid::SetRow(UINT nRow)
{
	m_nRow = nRow;
}

UINT CUVGrid::GetRow()
{
	return m_nRow;
}

int CUVGrid::RectHit(CPoint ptPos)
{
//检查鼠标点在哪一个Block并返回其index，如果不在所有的Block里则返回-1
	UINT nY = (ptPos.y - m_ptOrg.y) / m_fBlockHeight;
	UINT nX = (ptPos.x - m_ptOrg.x) / m_fBlockWidth;

	TRACE("nY,nX,m_fBlockHeight,m_fBlockWidth = %d,%d,%f,%f\n",
		nY,nX,m_fBlockHeight,m_fBlockWidth);
	
//	UINT nIndex = ((m_nRows - 1) * m_nCols - nY*10)+nX;
	UINT nIndex = (nY*m_nRow)+nX;

	if(	nIndex < m_nRow*m_nCol && nX < m_nRow)
	{
		return nIndex;
	}
	else return -1;
}

void CUVGrid::SetGridBlockSize(UINT nRow, UINT nCol)
{
	if(nRow != 0 && nCol != 0)
	{
		m_nRow = nRow;
		m_nCol = nCol;
	}
	BlockSize();
	
	ResetGridColor();
}

void CUVGrid::BlockSize()
{
	m_fBlockHeight = static_cast<float>(m_szSize.cy)/m_nCol;
	m_fBlockWidth = static_cast<float>(m_szSize.cx)/m_nRow;
}

void CUVGrid::ResetGridColor()
{
	m_arrColor.RemoveAll();
	m_arrColor.SetSize(m_nRow*m_nCol);

	for(int x = 0;x< m_nRow;x++)
	{
		for(int y = 0;y<m_nCol;y++)
		{
//			SetBlockColor(x*m_nCol+y,BLANKED_BLOCKS_UNSELCOLOR);
		}
	}
}

void CUVGrid::Create()
{
//	BlockSize(); chiu deleted at 0619

	if(ShapeList.size())
	{
		Clear();
	}//Clear old list first

	CPCBShape * pCPCBShape = NULL;
	for(int i = 0; i<= m_nCol;i++)
	{//Draw rows
		CPoint ptStart, ptEnd;
		
		ptStart.x = 0;
		ptStart.y = 0+i*m_fBlockHeight;
		ptEnd.x = m_nRow*m_fBlockWidth;//0+m_szSize.cx;// chiu at 0619
		ptEnd.y = 0+i*m_fBlockHeight;
		
		pCPCBShape = new CPCBLine(ptStart,ptEnd);
		
		ShapeList.push_back(pCPCBShape);
	}

	for(int j = 0; j<= m_nRow;j++)
	{//Draw cols
		CPoint ptStart, ptEnd;
		
		ptStart.x = 0+j*m_fBlockWidth;
		ptStart.y = 0;
		ptEnd.x = 0+j*m_fBlockWidth;
		ptEnd.y = m_nCol*m_fBlockHeight;//0+m_szSize.cy;// chiu at 0619
		
		pCPCBShape = new CPCBLine(ptStart,ptEnd);
		
		ShapeList.push_back(pCPCBShape);
	}
	ResetGridColor();
}

//DEL void CUVGrid::Clear()
//DEL {
//DEL 
//DEL }

void CUVGrid::PaintBlock(UINT nRow, UINT nCol, CBrush &brBlock, CDC *pDC)
{
	CRect rect = GetRect(nRow, nCol);

//	pDC->PaintRgn((CRgn*)&rect);

	pDC->FillRect(rect, &brBlock);
}

CRect CUVGrid::GetRect(UINT nRow, UINT nCol)
{
	CRect rect;

	rect.top = (m_ptOrg.y+nCol * m_fBlockHeight)*m_fZoom;
	rect.bottom = (m_ptOrg.y+(nCol + 1) * m_fBlockHeight)*m_fZoom;
	rect.left = (m_ptOrg.x+nRow * m_fBlockWidth)*m_fZoom;
	rect.right = (m_ptOrg.x+(nRow + 1) * m_fBlockWidth)*m_fZoom;

	rect.NormalizeRect();
	rect.DeflateRect(4,0,2,6);
//	TRACE("rect(top,left,bottom.right = %d,%d,%d,%d\n",rect.top,rect.left,rect.bottom,rect.right);
	return rect;
}

void CUVGrid::Draw(CDC *pDC)
{
//	pDC->SetROP2(R2_MASKPEN);

	CPen pen(PS_DOT,1,RGB(0,0,0));
	CPen *pOldPen = pDC->SelectObject(&pen);

	CGraph::Draw(pDC);

	pDC->SelectObject(pOldPen);


	for(int v = 0;v<m_nCol;v++)
	{//Paint Block
		for(int u = 0;u< m_nRow;u++)
		{
			CBrush brush(m_arrColor.GetAt(v*m_nRow+u));
			PaintBlock(u,v,brush,pDC);
		}
	}
/**/
}

CPoint CUVGrid::GetArea(int nIndex)
{
	CPoint ptAreaPos;
	UINT nX = nIndex % m_nRow;
	UINT nY = nIndex / m_nRow;
	ptAreaPos.y = m_fBlockHeight * nY;
	ptAreaPos.x = m_fBlockWidth * nX;
	return ptAreaPos;
}
