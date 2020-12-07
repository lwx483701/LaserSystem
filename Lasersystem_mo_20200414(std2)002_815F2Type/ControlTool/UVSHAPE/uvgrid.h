// UVGrid.h: interface for the CUVGrid class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UVGRID_H__F8177E16_1377_42B8_994C_4CDA615984C5__INCLUDED_)
#define AFX_UVGRID_H__F8177E16_1377_42B8_994C_4CDA615984C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Graph.h"

class CUVGrid : public CGraph  
{
public:
	CPoint GetArea(int nIndex);
	void Draw(CDC * pDC);
	void Create();
	void SetGridBlockSize(UINT nRow, UINT nCol);
	int RectHit(CPoint ptPos);
	UINT GetRow();
	void SetRow(UINT nRow);
	UINT GetCol();
	void SetCol(UINT nCol);
	double GetBlockHeight();
	void SetBlockHeight(double fBlockHeight);
	double GetBlockWidth();
	void SetBlockWidth(double fBlockWidth);
	COLORREF GetBlockColor(UINT nBlockIndex);
	void SetBlockColor(UINT nBlockIndex, COLORREF crBlock);
	void ResetGridColor();
	CUVGrid();
	virtual ~CUVGrid();

private:
	CRect GetRect(UINT nRow, UINT nCol);
	void PaintBlock(UINT nRow, UINT nCol, CBrush &brBlock, CDC *pDC);
	void BlockSize();
	double m_fBlockHeight;
	double m_fBlockWidth;
	UINT m_nCol;
	UINT m_nRow;
	CArray	<COLORREF, COLORREF> m_arrColor;
	CArray	<COLORREF, COLORREF> m_arrBGColor;
};

#endif // !defined(AFX_UVGRID_H__F8177E16_1377_42B8_994C_4CDA615984C5__INCLUDED_)
