// ListItem.cpp: implementation of the CListItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include <sstream>

#include "ListItem.h"
#include "..\CSVLineParser\CSVLineparser.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// begin class CListItemText
//////////////////////////////////////////////////////////////////////
CListItemText::CListItemText(string sProperty)
	: CListItem(sProperty)
	, m_bBold(false)
	, m_colorText(::GetSysColor(COLOR_WINDOWTEXT))

{
	CCSVLineParser csv(sProperty);

	if ((int)csv.size() == 3)
	{
		m_bBold = (csv.GetAt(1) != "0");
		m_colorText = atoi(csv.GetAt(2).c_str());
	}
}

string CListItemText::GenerateProperty(bool bBold, COLORREF color)
{
	CCSVLineParser csv;
	stringstream ss;

	ss << ItemTypeText;
	csv.SetAt(0, ss.str()); // item type first
	csv.SetAt(1, bBold ? string("1") : string("0"));
	ss.str("");
	ss << color;
	csv.SetAt(2, ss.str());

	return csv.GetFullString();
}

void CListItemText::DrawRect(CDC &dc, CRect rcItem, string sText, bool bSelected)
{
	COLORREF rgbBkgnd = ::GetSysColor(bSelected ? COLOR_HIGHLIGHT : COLOR_WINDOW)
		, rgbText = m_colorText; 
	CFont *pOldFont = NULL;
	CFont fontObj;
	if (m_bBold)
	{
		fontObj.CreateFont(
			rcItem.bottom-rcItem.top,  // nHeight
			0,                         // nWidth
			0,                         // nEscapement
			0,                         // nOrientation
			FW_BOLD,		           // nWeight
			FALSE,                     // bItalic
			FALSE,                     // bUnderline
			0,                         // cStrikeOut
			ANSI_CHARSET,              // nCharSet
			OUT_DEFAULT_PRECIS,        // nOutPrecision
			CLIP_DEFAULT_PRECIS,       // nClipPrecision
			DEFAULT_QUALITY,           // nQuality
			DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
			"Arial");
		pOldFont = dc.SelectObject(&fontObj);
	}

	dc.SetBkColor(rgbBkgnd);
	dc.SetTextColor(rgbText);
	LPCSTR pszText = CListReport::MakeShortString(&dc, sText.c_str(), rcItem.right-rcItem.left, 2*intBorder);
	dc.TextOut(rcItem.left + intBorder, rcItem.top + intBorder, pszText);

	if (m_bBold)
	{
		dc.SelectObject(pOldFont);
		fontObj.DeleteObject();
	}
}

//////////////////////////////////////////////////////////////////////
// end of class CListItemText
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// begin class CListItemCheckBox
//////////////////////////////////////////////////////////////////////
CListItemCheckBox::CListItemCheckBox(string sProperty)
	: CListItem(sProperty)
{
}

string CListItemCheckBox::GenerateProperty()
{
	CCSVLineParser csv;
	stringstream ss;

	ss << ItemTypeCheckBox;
	csv.SetAt(0, ss.str()); // item type first
	return csv.GetFullString();
}

void CListItemCheckBox::DrawRect(CDC &dc, CRect rcItem, string sText, bool bSelected)
{
CRect chkboxrect;
	chkboxrect = rcItem;
	chkboxrect.bottom -= 1;
	chkboxrect.left += 9;		// line up checkbox with header checkbox
	chkboxrect.right = chkboxrect.left + chkboxrect.Height();	// width = height

	// center the checkbox
	chkboxrect.left = rcItem.left + rcItem.Width()/2 - chkboxrect.Height()/2 - 1;
	chkboxrect.right = chkboxrect.left + chkboxrect.Height();

	// draw border
	dc.Ellipse(&chkboxrect);
	//dc.DrawEdge(&chkboxrect, EDGE_SUNKEN, BDR_RAISEDINNER  );

	
	
		//draw the check mark
		/*int x = chkboxrect.left + 9;
		ASSERT(x < chkboxrect.right);
		int y = chkboxrect.top + 3;
		int i;
		for (i = 0; i < 4; i++)
		{
			dc.MoveTo(x, y);
			dc.LineTo(x, y+3);
			x--;
			y++;
		}
		for (i = 0; i < 3; i++)
		{
			dc.MoveTo(x, y);
			dc.LineTo(x, y+3);
			x--;
			y--;
		}
		*/
	chkboxrect.bottom-=2;
	chkboxrect.top+=2;
	chkboxrect.left+=2;
	chkboxrect.right-=2;

	CBrush brushDot;
	CBrush*	pOldbrush;
		if (atoi(sText.c_str()))
		{
		brushDot.CreateSolidBrush(RGB(255,32,0));

		}
		else
		{
	brushDot.CreateSolidBrush(RGB(0,32,0));

		}
	
		pOldbrush = dc.SelectObject(&brushDot);
		dc.Ellipse(&chkboxrect);
		
		dc.SelectObject(pOldbrush);
		brushDot.DeleteObject();
		//	dc.f(&chkboxrect,RGB(255,0,0));
		
	

	
}

void CListItemCheckBox::ClickItem(CListReport *pParent, int intRow, int intColumn)
{
	ASSERT(pParent);
	if (intRow < 0 && intColumn < 0)
		return;

	bool bCheck = pParent->GetItemText(intRow, intColumn) == "1";
	pParent->SetItemText(intRow, intColumn, bCheck ? "0":"1");
}
//////////////////////////////////////////////////////////////////////
// end of class CListItemCheckBox
//////////////////////////////////////////////////////////////////////
