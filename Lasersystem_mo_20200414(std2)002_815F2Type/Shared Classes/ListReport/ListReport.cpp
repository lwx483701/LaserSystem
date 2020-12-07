// ListReport.cpp : implementation file
//

#include "stdafx.h"
#include "ListReport.h"

#include "..\CSVLineParser\CSVLineparser.h"
#include "ListItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int intDefaultSpace = 15;


using namespace ListReportDefinition;
/////////////////////////////////////////////////////////////////////////////
// CListReport

CListReport::CListReport(int intStyle) : m_intStyle(intStyle)
{
}

CListReport::~CListReport()
{
}


BEGIN_MESSAGE_MAP(CListReport, CListCtrl)
	//{{AFX_MSG_MAP(CListReport)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListReport message handlers


void CListReport::PreSubclassWindow() 
{
	CListCtrl::PreSubclassWindow();

	return;
}

CListItem * CListReport::FindSelectedItem(CPoint point, int &intRow, int &intColumn)
{
	LVHITTESTINFO hitTestInfo;
	int intColumnCount, intSelectedColumn = -1, intItemType = ItemTypeText;
	CRect rcItem;
	CCSVLineParser csv;
	CListItem *pItem = NULL;

	intRow = -1, intColumn = -1;

	LV_COLUMN lvc;
	::ZeroMemory(&lvc, sizeof(lvc));
	lvc.mask = LVCF_WIDTH | LVCF_FMT;

	hitTestInfo.pt = point;
	if (HitTest(&hitTestInfo) >= 0 && hitTestInfo.iItem >= 0)
	{
		intRow = hitTestInfo.iItem;
		for (intColumnCount=0; GetColumn(intColumnCount, &lvc); intColumnCount++)
		{
			GetSubItemRect(hitTestInfo.iItem, intColumnCount,LVIR_BOUNDS, rcItem);
			if (intColumnCount == 0)
				rcItem.right = GetColumnWidth(0);

			if (rcItem.PtInRect(point))
			{
				intSelectedColumn = intColumnCount;
				break;
			}
		}
		if (intSelectedColumn >= 0
				&& m_vecProperty.size() >= hitTestInfo.iItem 
				&& m_vecProperty[hitTestInfo.iItem].size() >= intSelectedColumn)
		{
			intColumn = intSelectedColumn;

			csv.SetFullString(m_vecProperty[hitTestInfo.iItem][intSelectedColumn]);
			if (csv.size())
				intItemType = atoi(csv.GetAt(0).c_str());


			switch(intItemType)
			{
			case ItemTypeText:
				pItem = new CListItemText(csv.GetFullString());
				break;
			case ItemTypeCheckBox:
				pItem = new CListItemCheckBox(csv.GetFullString());
				break;
			default:
				pItem = NULL;
				break;
			}
		}
	}
	return pItem;
}

void CListReport::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	int intRow, intColumn;
	CWnd* pWnd;

	// record clicked point
	m_point = point;
	CListItem *pItem = FindSelectedItem(point, intRow, intColumn);

	if (pItem && intRow >= 0 && intColumn >= 0)
		pItem->DbClickItem(this, intRow, intColumn);
	delete pItem;
	CListCtrl::OnLButtonDblClk(nFlags, point);

	// notify parent with user messages
	if (pWnd = GetParent())
	pWnd->PostMessage(WM_LISTREPORT_LBUTTONDBLCLK);
}

void CListReport::OnLButtonDown(UINT nFlags, CPoint point) 
{
	int intRow, intColumn;
	CWnd* pWnd;

	// record clicked point
	m_point = point;
	CListItem *pItem = FindSelectedItem(point, intRow, intColumn);

	if (pItem && intRow >= 0 && intColumn >= 0)
		pItem->ClickItem(this, intRow, intColumn);
	delete pItem;
	CListCtrl::OnLButtonDown(nFlags, point);

	// notify parent with user messages
	if (pWnd = GetParent())
		pWnd->PostMessage(WM_LISTREPORT_LBUTTONDOWN);
}

void CListReport::DrawItem(LPDRAWITEMSTRUCT lpDIS) 
{
	CDC dc;
	CRect rcItem, rcCell;
	COLORREF rgbBkgnd;
	bool bSelected;

	int intColumnCount, intItemType = ItemTypeText;
	CCSVLineParser csv;
	CListItem *pItem;

	dc.Attach(lpDIS->hDC);

	TCHAR  lpBuffer[256];
	LV_ITEM lvi;
	lvi.mask = LVIF_TEXT | LVIF_PARAM ;
	lvi.iItem = lpDIS->itemID ; 	
	lvi.iSubItem = 0;
	lvi.pszText = lpBuffer ;
	lvi.cchTextMax = sizeof(lpBuffer);

	LV_COLUMN lvc;
	::ZeroMemory(&lvc, sizeof(lvc));
	lvc.mask = LVCF_WIDTH | LVCF_FMT;


	for (intColumnCount=0; GetColumn(intColumnCount, &lvc); intColumnCount++)
	{
		GetSubItemRect(lpDIS->itemID, intColumnCount,LVIR_BOUNDS, rcCell);
		if (intColumnCount == 0)
		{
			rcItem = rcCell;
			rcCell.right = GetColumnWidth(0);
		}

		if (m_intStyle & intCellSelect)
			bSelected = (rcCell.PtInRect(m_point) == TRUE);
		else
			bSelected = (rcItem.PtInRect(m_point) == TRUE);

		if (bSelected)
			rgbBkgnd = ::GetSysColor(COLOR_HIGHLIGHTTEXT);
		else
			rgbBkgnd = ::GetSysColor(COLOR_WINDOW);

		CBrush br(rgbBkgnd);
		dc.FillRect(rcCell, &br);

		if( lpDIS->itemID < 0)
			break;

		if (m_vecProperty.size() < lpDIS->itemID 
				|| m_vecProperty[lpDIS->itemID].size() < intColumnCount)
			break;

		csv.SetFullString(m_vecProperty[lpDIS->itemID][intColumnCount]);
		if (csv.size())
			intItemType = atoi(csv.GetAt(0).c_str());

		switch(intItemType)
		{
		case ItemTypeText:
			pItem = new CListItemText();
			break;
		case ItemTypeCheckBox:
			pItem = new CListItemCheckBox(csv.GetFullString());
			break;
		default:
			pItem = NULL;
			break;
		}

		if (pItem)
		{
			lvi.iSubItem = intColumnCount;
			VERIFY(GetItem(&lvi));
			pItem->DrawRect(dc, rcCell, lpBuffer, bSelected);
		}
		delete pItem;
	}
	dc.Detach();
}

// operations
BOOL CListReport::AddColumn(LPCTSTR strItem,int nItem, int intColumnWidth, int nSubItem, int nMask,int nFmt)
{
	LV_COLUMN lvc;
	lvc.mask = nMask;
	lvc.fmt = nFmt;
	lvc.pszText = (LPTSTR) strItem;
	
	if (intColumnWidth > 0)
		lvc.cx = intColumnWidth;
	else
		lvc.cx = GetStringWidth(lvc.pszText) + intDefaultSpace;
	
	if(nMask & LVCF_SUBITEM)
	{
		if(nSubItem != -1)
			lvc.iSubItem = nSubItem;
		else
			lvc.iSubItem = nItem;
	}
	return InsertColumn(nItem,&lvc);
}

BOOL CListReport::AddItem(int nItem, int nSubItem, LPCTSTR strItem, string sProperty)
{
	LV_ITEM lvItem;
	lvItem.mask = (LVIF_TEXT | LVIF_PARAM);
	lvItem.iItem = nItem;
	lvItem.iSubItem = nSubItem;
	lvItem.pszText = (LPTSTR) strItem;
	lvItem.lParam = 0;

	// record property of the sub item.
	if (nItem > m_vecProperty.size() || (nSubItem && nSubItem > m_vecProperty[nItem].size()) )
		return false;
	else if (nItem == m_vecProperty.size())
	{
		vecPropertyItem prop;
		prop.push_back(sProperty);
		m_vecProperty.push_back(prop);
	}
	else if (nSubItem == m_vecProperty[nItem].size())
		m_vecProperty[nItem].push_back(sProperty);
	else
		m_vecProperty[nItem][nSubItem] = sProperty;


	if(nSubItem == 0)
	{
		return InsertItem(&lvItem);
	}
	else
	{
		lvItem.mask &= ~(LVIF_PARAM);
		return SetItem(&lvItem);
	}
}

// helper function, get displayed actual text
LPCTSTR CListReport::MakeShortString(CDC* pDC, LPCTSTR lpszLong, int nColumnLen, int nOffset)
{
	static const _TCHAR szThreeDots[] = _T("...");

	int nStringLen = lstrlen(lpszLong);

	if(nStringLen == 0 ||
		(pDC->GetTextExtent(lpszLong, nStringLen).cx + nOffset) <= nColumnLen)
	{
		return(lpszLong);
	}

	static _TCHAR szShort[MAX_PATH];

	lstrcpy(szShort,lpszLong);
	int nAddLen = pDC->GetTextExtent(szThreeDots,sizeof(szThreeDots)).cx;

	for(int i = nStringLen-1; i > 0; i--)
	{
		szShort[i] = 0;
		if((pDC->GetTextExtent(szShort, i).cx + nOffset + nAddLen)
			<= nColumnLen)
		{
			break;
		}
	}

	lstrcat(szShort, szThreeDots);
	return(szShort);
}

BOOL CListReport::DeleteItem( int nItem )
{
	int intItemCount;

	if (!CListCtrl::DeleteItem(nItem))
		return FALSE;

	if (nItem < 0 || nItem >= (int)m_vecProperty.size())
		return TRUE;

	for (intItemCount = nItem; intItemCount < (int)m_vecProperty.size()-1; intItemCount++)
		swap(m_vecProperty[intItemCount], m_vecProperty[intItemCount+1]);

	m_vecProperty.pop_back();
	return TRUE;
}

BOOL CListReport::DeleteAllItems()
{
	if (!CListCtrl::DeleteAllItems())
		return FALSE;
	m_vecProperty.clear();
	return TRUE;
}
