// TreeCtrlEx.cpp : implementation file
//

#include "stdafx.h"
//#include "lasersystem.h"
#include "TreeCtrlEx.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlEx

CTreeCtrlEx::CTreeCtrlEx()
{
}

CTreeCtrlEx::~CTreeCtrlEx()
{
}


BEGIN_MESSAGE_MAP(CTreeCtrlEx, CTreeCtrl)
	//{{AFX_MSG_MAP(CTreeCtrlEx)
	ON_WM_PAINT()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnItemexpanding)
	ON_WM_PALETTECHANGED()
	ON_WM_QUERYNEWPALETTE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlEx message handlers

  // The pointer to my tree control.
CTreeCtrlEx* pmyTreeCtrl;
TVSORTCB tvs;



int CALLBACK CTreeCtrlEx::CompareNoCase(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
 
  CString    strItem1 = pmyTreeCtrl->GetItemText((HTREEITEM) lParam1);
  CString    strItem2 = pmyTreeCtrl->GetItemText((HTREEITEM) lParam2);
  
  HTREEITEM hParent = pmyTreeCtrl->GetParentItem((HTREEITEM) lParam1);
  hParent = pmyTreeCtrl->GetChildItem(hParent);
 
  CString strFirst = pmyTreeCtrl->GetItemText(hParent);

  int GT = strncmp(strItem2, strItem1,1);

  if(strncmp(strFirst,"B",sizeof(char)))
  {
	return GT;
  }
  else
  {
	return -GT;
  }


}


HTREEITEM CTreeCtrlEx::GetNextItem(HTREEITEM hItem)
{
	HTREEITEM hti;

	if(ItemHasChildren(hItem))
	{
		return GetChildItem(hItem);
	}
	else
	{
		while( (hti=GetNextSiblingItem(hItem)) == NULL) 
		{
			if( (hItem = GetParentItem(hItem) ) == NULL )
				return NULL;
		} 
	}
	return hti;
}

//Get Last item in the branch
HTREEITEM CTreeCtrlEx::GetLastItem(HTREEITEM hItem)
{
	HTREEITEM htiNext;

	if(hItem == NULL)
	{
		htiNext = GetRootItem();
		while(htiNext)
		{
			hItem = htiNext;
			htiNext = GetNextSiblingItem(htiNext);
		}
	}
	while( ItemHasChildren(hItem) )
	{
		htiNext = GetChildItem(hItem);
		while(htiNext)
		{
			hItem = htiNext;
			htiNext = GetNextSiblingItem(htiNext);
		}
	}
	return hItem;
}

HTREEITEM CTreeCtrlEx::GetPrevItem(HTREEITEM hItem)
{
	HTREEITEM hti;

	hti = GetPrevSiblingItem(hItem);

	if( hti = NULL)
		hti = GetParentItem(hItem);
	else
		hti = GetLastItem(hti);
	return hti;
}

HTREEITEM CTreeCtrlEx::FindItem(CString &str, 
								BOOL bCaseSensitive, 
								BOOL bDownDir, 
								BOOL bWholeWord, 
								HTREEITEM hItem)
{
	int lenSearchStr=str.GetLength();
	if( lenSearchStr==0 )return NULL;

	HTREEITEM htiSel=hItem ? hItem : GetSelectedItem();
	HTREEITEM htiCur=bDownDir ? GetNextItem( htiSel ) :
	    GetPrevItem( htiSel );
	CString sSearch = str;

	if( htiCur == NULL )
	{
		if( bDownDir ) htiCur=GetRootItem();
		else htiCur = GetLastItem( NULL );
	}

	if( !bCaseSensitive )
		sSearch.MakeLower();

	while( htiCur && htiCur !=htiSel )
	{
		CString sItemText = GetItemText( htiCur );
		if( !bCaseSensitive )
			sItemText.MakeLower();

		int n;
		while( (n=sItemText.Find( sSearch ) ) != -1 )
		{
			// search string found
			if( bWholeWord )
			{
				//Check preceding char
				if( n !=0 )
				{
					if( isalpha(sItemText[n-1]) ||
						sItemText[n-1] == '_' ){
						//Not whole word
                        sItemText = sItemText.Right(
                        sItemText.GetLength() - n -
						lenSearchStr );
					}
				}

				// Check succeeding char
				if( sItemText.GetLength() > n +
					lenSearchStr  && ( isalpha(sItemText
					[n+lenSearchStr]) ||
                    sItemText[n+lenSearchStr] == '_' ) )
				{
					//Not whole word
                    sItemText = sItemText.Right
						( sItemText.GetLength()
						- n - sSearch.GetLength() );
					continue;
				}
			}

			if( IsFindValid( htiCur ) )
				return htiCur;
			else break;
		}

		htiCur = bDownDir ? GetNextItem( htiCur ) :
		    GetPrevItem( htiCur );
			if( htiCur == NULL )
			{
				if( bDownDir ) htiCur = GetRootItem();
				else htiCur = GetLastItem( NULL );
			}
	}
	return NULL;
}

// IsFindValid    - Virtual function used by FindItem to allow this
//             function to filter the result of FindItem
//Returns    - True if item matches the criteria
//Arg             - Handle of the item

BOOL CTreeCtrlEx::IsFindValid(HTREEITEM)
{
return TRUE;
}


HTREEITEM CTreeCtrlEx::FindItemData(DWORD lparam, BOOL bDownDir, 
									HTREEITEM hItem)
{
	HTREEITEM htiSel = hItem?hItem : GetSelectedItem();
    HTREEITEM htiCur = bDownDir ? GetNextItem( htiSel ):GetPrevItem(htiSel);
	if( htiCur == NULL )
	{
		if( bDownDir )
			htiCur = GetRootItem();
		else
			htiCur = GetLastItem( NULL );
	}
	while( htiCur && htiCur !=htiSel )
	{
		DWORD sItemData = GetItemData( htiCur );
		if (sItemData == lparam )
			return htiCur;
		htiCur = bDownDir ? GetNextItem( htiCur ):
		  GetPrevItem( htiCur );
		if( htiCur == NULL )
		{
			if( bDownDir )
				htiCur = GetRootItem();
			else
                htiCur = GetLastItem( NULL );
		}
	}
	return NULL;

}

HTREEITEM CTreeCtrlEx::FindData(HTREEITEM hti, DWORD dwData)
{
	if(hti == NULL) return NULL;

	if(GetItemData( hti ) ==dwData)
	{
		Select( hti,TVGN_CARET);
		EnsureVisible( hti );
		return hti;
	}

	hti = GetChildItem( hti );
	do
	{
		HTREEITEM hti_res;
		if((hti_res = FindData( hti,dwData)) !=NULL )
			return hti_res;
	}while( (hti = GetNextSiblingItem( hti )) !=NULL );
	return NULL;
	
}

void CTreeCtrlEx::Serialize(CArchive &ar)
{
	if (ar.IsStoring())
	{
		//storing code
		HTREEITEM hti = GetRootItem();
		while( hti )
		{
			int indent = GetIndentLevel( hti );
			while( indent-- )
				ar.WriteString( "\t" );
			ar.WriteString( GetItemText( hti ) + "\r\n");
			hti = GetNextItem( hti );

		}
	}
	else
	{
		//loading code
		CString sLine;
		if( !ar.ReadString( sLine ) )
			return;

		HTREEITEM hti = NULL;
		int indent=0,baseindent =0;

		while( sLine[baseindent] == '\t')
			baseindent ++;

		do
		{
			if(sLine.GetLength() == 0)
				continue;

			for(indent=0; sLine[indent] == '\t'; ++indent)
				;                       // 
			sLine = sLine.Right(sLine.GetLength()-indent);

			indent -= baseindent;

			HTREEITEM hParent;
			int previndent = GetIndentLevel( hti );
	
			if( indent == previndent )
			{	
				hParent = GetParentItem(hti); 
			}
			else if ( indent > previndent)
			{	
				hParent = hti;
			}
			else
			{
				int nLevelsUp = previndent - indent;
				hParent = GetParentItem ( hti);
				while( nLevelsUp-- )
				{
					hParent = GetParentItem(hParent);
				}	
			}

			hti = InsertItem(sLine,hParent?hParent:TVI_ROOT,TVI_LAST);
			
		}while( ar.ReadString(sLine) );

	}

}

long CTreeCtrlEx::GetIndentLevel(HTREEITEM hItem) const
{

	long lIndent = 0;

	while( (hItem = GetParentItem(hItem) )!=NULL )
		lIndent ++;

	return lIndent;
}


BOOL CTreeCtrlEx::LoadToolFromFile(const char *filename)
{
	FILE* fp;
	char buf[MaxPathLen];

	if( (fp=fopen(filename,"r"))==NULL)							//r+	//20180118
		return FALSE;
	
	HTREEITEM hti = NULL;
	int indent=0,baseindent =0;
	
	fscanf(fp,"%s",buf);
	while( buf[baseindent] == '-')
		baseindent++;
	
	do
	{
		if( strlen(buf) == 0)
			continue;
		
		for(indent=0; buf[indent] == '-'; ++indent)
			;                       

		strcpy(buf,buf+indent);
		indent -= baseindent;
		
		HTREEITEM hParent;
		int previndent = GetIndentLevel( hti );
		
		if( indent == previndent )	
			hParent = GetParentItem(hti); 
		else if ( indent > previndent)	
			hParent = hti;
		else
		{
			int nLevelsUp = previndent - indent;
			hParent = GetParentItem ( hti);

			while( nLevelsUp-- )
			{
				hParent = GetParentItem(hParent);
			}	
		}
		
		hti = InsertItem(buf,hParent?hParent:TVI_ROOT,TVI_LAST);
		
		SetItemData(hti,(DWORD)(hti));
		
		fscanf(fp,"%s",buf);
		
	}while(!feof(fp));

	fclose(fp);
	
	return TRUE;
}

void CTreeCtrlEx::SaveToolToFile(const char *filename)
{
	FILE* fp;

	if(strlen(filename)==0)
		return ;

	if( (fp=fopen(filename,"w+"))==NULL)
		return ;

	HTREEITEM hti = GetRootItem();
	while( hti )
	{
		int indent = GetIndentLevel( hti );
		while( indent-- )
			fprintf(fp,"-");
		
		fprintf(fp,"%s\r\n", GetItemText(hti));

//		CString dfd =	GetItemText(hti);
		hti = GetNextItem( hti );
	}

	fclose(fp);
}

BOOL CTreeCtrlEx::Sort(HTREEITEM hItem, BOOL bSortA)
{

  pmyTreeCtrl = this;

  tvs.hParent =   GetParentItem(hItem);
  tvs.lpfnCompare = CompareNoCase;
  tvs.lParam = (LPARAM) bSortA;

  SortChildrenCB(&tvs);
  return 0;
}

BOOL CTreeCtrlEx::SetBkImage(UINT nIDResource)
{
	return SetBkImage( (LPCTSTR)nIDResource );
}

BOOL CTreeCtrlEx::SetBkImage(LPCTSTR lpszResourceName)
{
	if( m_bitmap.m_hObject != NULL )
		m_bitmap.DeleteObject();
	if( m_pal.m_hObject != NULL )
		m_pal.DeleteObject();


	HBITMAP hBmp = (HBITMAP)::LoadImage( AfxGetInstanceHandle(),
			lpszResourceName, IMAGE_BITMAP, 0,0, LR_CREATEDIBSECTION );

	if( hBmp == NULL )
		return FALSE;

	m_bitmap.Attach( hBmp );
	BITMAP bm;
	m_bitmap.GetBitmap( &bm );
	m_cxBitmap = bm.bmWidth;
	m_cyBitmap = bm.bmHeight;


	// Create a logical palette for the bitmap
	DIBSECTION ds;
	BITMAPINFOHEADER &bmInfo = ds.dsBmih;
	m_bitmap.GetObject( sizeof(ds), &ds );

	int nColors = bmInfo.biClrUsed ? bmInfo.biClrUsed : 1 << bmInfo.biBitCount;

	// Create a halftone palette if colors > 256. 
	CClientDC dc(NULL);			// Desktop DC
	if( nColors > 256 )
		m_pal.CreateHalftonePalette( &dc );
	else
	{
		// Create the palette

		RGBQUAD *pRGB = new RGBQUAD[nColors];
		CDC memDC;
		memDC.CreateCompatibleDC(&dc);

		memDC.SelectObject( &m_bitmap );
		::GetDIBColorTable( memDC, 0, nColors, pRGB );

		UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * nColors);
		LOGPALETTE *pLP = (LOGPALETTE *) new BYTE[nSize];

		pLP->palVersion = 0x300;
		pLP->palNumEntries = nColors;

		for( int i=0; i < nColors; i++)
		{
			pLP->palPalEntry[i].peRed = pRGB[i].rgbRed;
			pLP->palPalEntry[i].peGreen = pRGB[i].rgbGreen;
			pLP->palPalEntry[i].peBlue = pRGB[i].rgbBlue;
			pLP->palPalEntry[i].peFlags = 0;
		}

		m_pal.CreatePalette( pLP );

		delete[] pLP;
		delete[] pRGB;
	}
	Invalidate();

	return TRUE;

}

void CTreeCtrlEx::OnPaint() 
{
	CPaintDC dc(this); 
	
	CRect rcClip, rcClient;
	dc.GetClipBox( &rcClip );
	GetClientRect(&rcClient);

	// Create a compatible memory DC 
	CDC memDC;
	memDC.CreateCompatibleDC( &dc );

	// Select a compatible bitmap into the memory DC
	CBitmap bitmap, bmpImage;
	bitmap.CreateCompatibleBitmap( &dc, rcClient.Width(), rcClient.Height() );
	memDC.SelectObject( &bitmap );

	CRgn rgn;
	rgn.CreateRectRgnIndirect( &rcClip );
	memDC.SelectClipRgn(&rgn);
	rgn.DeleteObject();

	// First let the control do its default drawing.
	CWnd::DefWindowProc( WM_PAINT, (WPARAM)memDC.m_hDC, 0 );

	// Draw bitmap in the background if one has been set
	if( m_bitmap.m_hObject != NULL )
	{
		// Now create a mask
		CDC maskDC;
		maskDC.CreateCompatibleDC(&dc);
		CBitmap maskBitmap;

		// Create monochrome bitmap for the mask
		maskBitmap.CreateBitmap( rcClient.Width(), rcClient.Height(),
						1, 1, NULL );
		maskDC.SelectObject( &maskBitmap );
		memDC.SetBkColor( ::GetSysColor( COLOR_WINDOW ) );

		// Create the mask from the memory DC
		maskDC.BitBlt( 0, 0, rcClient.Width(), rcClient.Height(), &memDC,
					rcClient.left, rcClient.top, SRCCOPY );


		CDC tempDC;
		tempDC.CreateCompatibleDC(&dc);
		tempDC.SelectObject( &m_bitmap );

		CDC imageDC;
		CBitmap bmpImage;
		imageDC.CreateCompatibleDC( &dc );
		bmpImage.CreateCompatibleBitmap( &dc, rcClient.Width(),
						rcClient.Height() );
		imageDC.SelectObject( &bmpImage );

		if( dc.GetDeviceCaps(RASTERCAPS) & RC_PALETTE && m_pal.m_hObject != NULL )
		{
			dc.SelectPalette( &m_pal, FALSE );
			dc.RealizePalette();

			imageDC.SelectPalette( &m_pal, FALSE );
		}

		// Get x and y offset
		CRect rcRoot;
		GetItemRect( GetRootItem(), rcRoot, FALSE );
		rcRoot.left = -GetScrollPos( SB_HORZ );

		// Draw bitmap in tiled manner to imageDC
		for( int i = rcRoot.left; i < rcClient.right; i += m_cxBitmap )
			for( int j = rcRoot.top; j < rcClient.bottom; j += m_cyBitmap )
				imageDC.BitBlt( i, j, m_cxBitmap, m_cyBitmap, &tempDC,
							0, 0, SRCCOPY );

		// Set the background in memDC to black. Using SRCPAINT with black and any other
		// color results in the other color, thus making black the transparent color
		memDC.SetBkColor(RGB(0,0,0));
		memDC.SetTextColor(RGB(255,255,255));
		memDC.BitBlt(rcClip.left, rcClip.top, rcClip.Width(), rcClip.Height(), &maskDC,
				rcClip.left, rcClip.top, SRCAND);

		// Set the foreground to black. See comment above.
		imageDC.SetBkColor(RGB(255,255,255));
		imageDC.SetTextColor(RGB(0,0,0));
		imageDC.BitBlt(rcClip.left, rcClip.top, rcClip.Width(), rcClip.Height(), &maskDC,
				rcClip.left, rcClip.top, SRCAND);

		// Combine the foreground with the background
		imageDC.BitBlt(rcClip.left, rcClip.top, rcClip.Width(), rcClip.Height(),
					&memDC, rcClip.left, rcClip.top,SRCPAINT);

		// Draw the final image to the screen		
		dc.BitBlt( rcClip.left, rcClip.top, rcClip.Width(), rcClip.Height(),
					&imageDC, rcClip.left, rcClip.top, SRCCOPY );
	}
	else //background color
	{
#if 0
		// Now create a mask
		CDC maskDC;
		maskDC.CreateCompatibleDC(&dc);
		CBitmap maskBitmap;

		// Create monochrome bitmap for the mask
		maskBitmap.CreateBitmap( rcClip.Width(), rcClip.Height(), 1, 1, NULL );
		maskDC.SelectObject( &maskBitmap );
		memDC.SetBkColor( ::GetSysColor( COLOR_WINDOW ) );

		// Create the mask from the memory DC
		maskDC.BitBlt( 0, 0, rcClip.Width(), rcClip.Height(), &memDC,
					rcClip.left, rcClip.top, SRCCOPY );

		dc.FillRect(rcClip, &CBrush(RGB(255,255,192)) );

		memDC.SetBkColor(RGB(0,0,0));
		memDC.SetTextColor(RGB(255,255,255));
		memDC.BitBlt(rcClip.left, rcClip.top, rcClip.Width(), rcClip.Height(), &maskDC, rcClip.left, rcClip.top, SRCAND);

		// Set the foreground to black. See comment above.
		dc.SetBkColor(RGB(255,255,255));
		dc.SetTextColor(RGB(0,0,0));
		dc.BitBlt(rcClip.left, rcClip.top, rcClip.Width(), rcClip.Height(), &maskDC, rcClip.left, rcClip.top, SRCAND);

		// Combine the foreground with the background
		dc.BitBlt(rcClip.left, rcClip.top, rcClip.Width(),
			            rcClip.Height(), &memDC,
						rcClip.left, rcClip.top,SRCPAINT);
#else
		dc.BitBlt( rcClip.left, rcClip.top, rcClip.Width(),
				rcClip.Height(), &memDC,
				rcClip.left, rcClip.top, SRCCOPY );
#endif

	}
}

void CTreeCtrlEx::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if( m_bitmap.m_hObject != NULL )
		InvalidateRect(NULL);

	CTreeCtrl::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CTreeCtrlEx::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if( m_bitmap.m_hObject != NULL )
		InvalidateRect(NULL);

	CTreeCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CTreeCtrlEx::OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	if( m_bitmap.m_hObject != NULL )
		InvalidateRect(NULL);
	
	*pResult = 0;
}

void CTreeCtrlEx::OnPaletteChanged(CWnd* pFocusWnd) 
{
	CTreeCtrl::OnPaletteChanged(pFocusWnd);

	if( pFocusWnd == this )
		return;
	OnQueryNewPalette();
	
}

BOOL CTreeCtrlEx::OnQueryNewPalette() 
{
	CClientDC dc(this);
	if( dc.GetDeviceCaps(RASTERCAPS) & RC_PALETTE && m_pal.m_hObject != NULL )
	{
		dc.SelectPalette( &m_pal, FALSE );
		BOOL result = dc.RealizePalette();
		if( result )
			Invalidate();
		return result;
	}

	return CTreeCtrl::OnQueryNewPalette();
}
