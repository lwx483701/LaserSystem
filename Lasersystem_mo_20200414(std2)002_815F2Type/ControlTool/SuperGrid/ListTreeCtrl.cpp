// ListTreeCtrl.cpp : implementation file
//

#include "stdafx.h"
//#include "..\..\uvmaker.h"
//#include "testgrid.h"
#include "ListTreeCtrl.h"
#include "ComboInListView.h"
#include "..\\..\\warninginfo.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListTreeCtrl

CListTreeCtrl::CListTreeCtrl()
{
}

CListTreeCtrl::~CListTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(CListTreeCtrl, CSuperGridCtrl)
	//{{AFX_MSG_MAP(CListTreeCtrl)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListTreeCtrl message handlers

int CListTreeCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CSuperGridCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	if(!m_image.Create(IDB_FOLDERS,16,1,RGB(0, 255, 255)))
		return -1;

	SetImageList(&m_image, LVSIL_SMALL);
	CImageList *pImageList = GetImageList(LVSIL_SMALL);
	if(pImageList)
		ImageList_GetIconSize(pImageList->m_hImageList, &m_cxImage, &m_cyImage);
	else
		return -1;
	
	return 0;
}

bool CListTreeCtrl::InitializeGrid()
{
	SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES);

	//LPTSTR lpszCols[] = {_T("工具号"),_T("加工方式"),_T("脉冲宽度"),_T("脉冲频率"),_T("光圈"),_T("加工次数"),_T("焦距偏移"),_T("刻线延时"),_T("加工速度"),0};
	
	char ez1[256]={""};//ly 20110405
	char ez2[256]={""};//ly 20110405
	char ez3[256]={""};//ly 20110405
	char ez4[256]={""};//ly 20110405
	char ez5[256]={""};//ly 20110405
	char ez6[256]={""};//ly 20110405
	char ez7[256]={""};//ly 20110405
	char ez8[256]={""};//ly 20110405
	char ez9[256]={""};//ly 20110405

	strncpy(ez1 ,GetLang().GetWarningText(10180),256);
	strncpy(ez2 ,GetLang().GetWarningText(10181),256);
	strncpy(ez3 ,GetLang().GetWarningText(10182),256);
	strncpy(ez4 ,GetLang().GetWarningText(10183),256);
	strncpy(ez5 ,GetLang().GetWarningText(10184),256);
	strncpy(ez6 ,GetLang().GetWarningText(10185),256);
	strncpy(ez7 ,GetLang().GetWarningText(10186),256);
	strncpy(ez8 ,GetLang().GetWarningText(10187),256);
	strncpy(ez9 ,GetLang().GetWarningText(10188),256);

	LPTSTR lpszCols[] = {_T(ez1),//"工具号""Tool number"
		_T(ez2),//"加工方式""Mode"
		_T(ez3),//"脉冲宽度""Pulse width"
		_T(ez4),//"脉冲频率""Pulse frequency"
		_T(ez5),//"光圈""Aperture"
		_T(ez6),//"加工次数""Process times"
		_T(ez7),//"焦距偏移""Focus offset"
		_T(ez8),//"刻线延时""Reticle delay"
		_T(ez9),0};//"加工速度""Peocess speed"
	
	LV_COLUMN   lvColumn;
	//initialize the columns
	lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvColumn.fmt = LVCFMT_LEFT;
	lvColumn.cx = 150;
	for(int x = 0; lpszCols[x]!=NULL; x++)
    {
		//make the secondary columns smaller
		if(x)
		  lvColumn.cx = 100;

		lvColumn.pszText = lpszCols[x];
		InsertColumn(x,&lvColumn);
    }

	CItemInfo* lp = new CItemInfo();
	lp->SetCheck(1);
	lp->SetImage(4);
	//add item text
	lp->SetItemText(_T("T1"));
	
	//initalized list for the combobox
	
	CStringList Aperlist;
	if(GetLang().GetCurLanguage()==0)
	{
		Aperlist.AddTail("光圈1");
		Aperlist.AddTail("光圈2");
		Aperlist.AddTail("光圈3");
		Aperlist.AddTail("光圈4");
		Aperlist.AddTail("光圈5");
		Aperlist.AddTail("光圈6");
	}
	else if(GetLang().GetCurLanguage()==1)
	{
		Aperlist.AddTail("Aperture1");
		Aperlist.AddTail("Aperture2");
		Aperlist.AddTail("Aperture3");
		Aperlist.AddTail("Aperture4");
		Aperlist.AddTail("Aperture5");
		Aperlist.AddTail("Aperture6");
	}
    lp->SetListData(3, &Aperlist);

	CStringList ProcTypelist;
	ProcTypelist.AddTail("C");
	ProcTypelist.AddTail("B");
	ProcTypelist.AddTail("M");
    lp->SetListData(3, &ProcTypelist);

	
	//Create root item
	CTreeItem * pRoot = InsertRootItem(lp);//previous on N.Y.P.D we call it CreateTreeCtrl(lp)
	if( pRoot == NULL )
		return  FALSE;

	//insert items	
	int nCol = GetNumCol();
	for(int i=0; i < nCol; i++)
	{
		CItemInfo* lpItemInfo = new CItemInfo();
		CString strItem;
		strItem.Format(_T("Item %d"),i);
		//add items text
		lpItemInfo->SetItemText(strItem);
		//add subitem text
		for(int y=0;y < nCol-1; y++) 
		{
			CString str;
			str.Format(_T("subItem %d of %s"),y,lpItemInfo->GetItemText());
			lpItemInfo->AddSubItemText(str);
			lpItemInfo->SetCheck(1);
			
			lpItemInfo->SetControlType(lp->CONTROLTYPE::combobox, 3/*col # 3 from subitems...really col #4 in view, live with it*/);
			lpItemInfo->SetListData(y, &Aperlist);
			lpItemInfo->SetControlType(lp->CONTROLTYPE::combobox, 0/*col # 3 from subitems...really col #4 in view, live with it*/);
			lpItemInfo->SetListData(y, &ProcTypelist);
			
		}
		//insert the iteminfo with ParentPtr
		CTreeItem* pParent = InsertItem(pRoot, lpItemInfo);
		//other nodes
		if(i%nCol)
		{
			CTreeItem* pParent1=NULL;
			CTreeItem* pParent2=NULL;

		}
		
	}
	
	//could now expand one level
	Expand(pRoot, 0 /*listview index 0*/); 
	UINT uflag = LVIS_SELECTED | LVIS_FOCUSED;
	SetItemState(0, uflag, uflag);

	//Create another rootitem	
	//block 
	{
		CItemInfo* lp = new CItemInfo();
		lp->SetImage(4);
		//add item text
		lp->SetItemText(_T("Z2"));
		CTreeItem * pRoot = InsertRootItem(lp);

		CItemInfo* lpAgent = new CItemInfo();
		lpAgent->SetItemText(_T("Bugs: well it's possible"));
		lpAgent->SetImage(2);
		CTreeItem *pParent2 = InsertItem(pRoot,lpAgent);
	}

 return TRUE;
}
#define IDC_COMBOBOXINLISTVIEW 0x1235
void CListTreeCtrl::OnControlLButtonDown(UINT nFlags, CPoint point, LVHITTESTINFO& ht)
{
	//now I am sure I added a combobox some where, so check for this control
	CTreeItem*pSelItem = GetTreeItem(ht.iItem);
	if(pSelItem!=NULL)
	{	
		CItemInfo* pInfo = GetData(pSelItem);
		CItemInfo::CONTROLTYPE ctrlType;
		if(pInfo->GetControlType(ht.iSubItem-1, ctrlType))
		{	
			if(ctrlType==pInfo->CONTROLTYPE::combobox) 
			{
					CStringList* list=NULL;
					pInfo->GetListData(ht.iSubItem-1, list);
					CComboBox * pList = ShowList(ht.iItem, ht.iSubItem, list);
			}
		}								
		/*
		else //activate default edit control
			CSuperGridCtrl::OnControlLButtonDown(nFlags, point, ht);
		*/
	}
}

CComboBox* CListTreeCtrl::ShowList(int nItem, int nCol, CStringList *lstItems)
{
	
	CString strFind = GetItemText(nItem, nCol);

	//basic code start
	CRect rect;
	int offset = 0;
	// Make sure that the item is visible
	if( !EnsureVisible(nItem, TRUE)) return NULL;
	GetSubItemRect(nItem, nCol, LVIR_BOUNDS, rect);
	// Now scroll if we need to expose the column
	CRect rcClient;
	GetClientRect(rcClient);
	if( offset + rect.left < 0 || offset + rect.left > rcClient.right )
	{
		CSize size;
		size.cx = offset + rect.left;
		size.cy = 0;
		Scroll(size);
		rect.left -= size.cx;
	}
	
	rect.left += offset;	
	rect.right = rect.left + GetColumnWidth(nCol);
	if(rect.right > rcClient.right) 
	   rect.right = rcClient.right;
	//basic code end

	rect.bottom += 10 * rect.Height();//dropdown area
	
	DWORD dwStyle =  WS_CHILD | WS_VISIBLE|CBS_DROPDOWNLIST | CBS_DISABLENOSCROLL;
	CComboBox *pList = new CComboInListView(nItem, nCol, lstItems);
	pList->Create(dwStyle, rect, this, IDC_COMBOBOXINLISTVIEW);
	pList->ModifyStyleEx(0,WS_EX_CLIENTEDGE);//can we tell at all
	pList->SetHorizontalExtent(CalcHorzExtent(pList, lstItems));
	pList->ShowDropDown();
	pList->SelectString(-1, strFind.GetBuffer(1));
	// The returned pointer should not be saved
	
	
	return pList;
}
int CListTreeCtrl::CalcHorzExtent(CWnd* pWnd, CStringList *pList)
{
	int nExtent=0;
	if(pWnd!=NULL)
	{
		CDC* pDC = pWnd->GetDC();
		HFONT hFont = (HFONT)pWnd->SendMessage(WM_GETFONT); //why not pWnd->GetFont();..I like the send thing alot and
		CFont *pFont = CFont::FromHandle(hFont);			//this way I get to use this function..cool :)
		if(pFont!=NULL)										//ya what ever makes me happy,.right :}
		{
			CFont* pOldFont = pDC->SelectObject(pFont);
			CSize newExtent;
			POSITION pos = pList->GetHeadPosition();
			while(pos != NULL)
			{
				CString str(pList->GetNext(pos));
				newExtent = pDC->GetTextExtent(str);
				newExtent.cx += 6;
				if (newExtent.cx > nExtent)
				{
					nExtent = newExtent.cx;
				}
			}
			pDC->SelectObject(pOldFont);
		}
		pWnd->ReleaseDC(pDC);
	}
	return nExtent;
}