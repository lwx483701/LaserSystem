
#include "Stdafx.h"
#include "SmartEdit.h"
#include "math.h"
#include "..\\..\\warninginfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//AfxApi CSmartEdit * GetSmartEdit( CWnd *pcwnd, int id )
//{
//	return (CSmartEdit *)pcwnd->GetDlgItem( id );
//}

#define BLANK_ENTRY		0//-1
///////////////////////////////////////////////////////////
// CSmartEdit implementation

BEGIN_MESSAGE_MAP(CSmartEdit, CEdit)
	//{{AFX_MSG_MAP(CSmartEdit)
	ON_WM_CHAR()
	ON_CONTROL_REFLECT(EN_UPDATE, OnUpdate)
	ON_WM_KILLFOCUS()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CSmartEdit::CSmartEdit()
{
	m_wParseType = SES_ALL;
//	m_pSlider = NULL;
	m_iValue = INT_MIN;
	m_pFormat = NULL;
	m_bUseFp = FALSE;
	m_myMax  = pow(2,30);		    //	Maximum number the edit control will accept
	m_myMin  = -pow(2,30);		    //	Minimum number the edit control will accept
    
	m_iMax   = m_myMax;
    m_iMin   = m_myMin;
	m_bConfirm = TRUE;
}

CSmartEdit::~CSmartEdit()
{
	if( m_pFormat )
		free( m_pFormat );
}

int CSmartEdit::SetParseType( WORD type )
{
	m_wParseType = type;
	return type;
}
// Aliasing on top of an existing Edit control
BOOL CSmartEdit::SubclassEdit( UINT nID, CWnd* pParent, WORD wParseStyle )
{
	SetParseType( wParseStyle );
	return SubclassDlgItem( nID, pParent );
}
// Input character filter
void CSmartEdit::OnChar( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	WORD type = SES_OTHERCHARS;		// default
	int	alpha = IsCharAlpha( (TCHAR)nChar );
	int	number = IsCharAlphaNumeric( (TCHAR)nChar ) && ! alpha;

	RemoveLeadingZeros ( );

	if( nChar < 0x20 )
		type = SES_ALL;				// always allow control chars ???
	else if( number )
		type = SES_NUMBERS | SES_SIGNED | SES_FLOATINGPT;
	else if( alpha )
		{
		type = SES_LETTERS;
		if( toupper( (TCHAR)nChar ) == 'E' )
			type |= SES_FLOATINGPT;
		}
	else if( (TCHAR)nChar == '-' )		// dash
		type = SES_SIGNED | SES_FLOATINGPT;
	else if( (TCHAR)nChar == '.' )		// dot
		type = SES_FLOATINGPT;
	else if( (TCHAR)nChar == '_' )		// underscore
		type = SES_UNDERSCORE | SES_OTHERCHARS;

	if( m_wParseType & type )
	{
//        CString strold;
//		GetWindowText(strold);
		CEdit::OnChar(nChar, nRepCnt, nFlags);  // permitted
/*		if(m_wParseType & SES_NUMBERS)
		{
			if(!CheckData())
			{
				m_bConfirm = FALSE;
				AfxMessageBox("Error",MB_OK);
			}
		}
*/	}
	else
		{
		// illegal character - inform parent
		OnBadInput();
		}

 
}

void CSmartEdit::OnBadInput()
{
	MessageBeep((UINT)-1);
}

int	CSmartEdit::UpdateEdit( int position )
{
	TCHAR buffer[512];
    RemoveLeadingZeros();
	if( position == m_iValue )
		return FALSE;		// been here already

	m_iValue = position;
	if( m_bUseFp )
		{
		// scale to double value
		m_dValue = m_dMin + (double)m_iValue * m_dRange / 1000.0;
		sprintf( buffer, m_pFormat, m_dValue );
		}
	else
		sprintf( buffer, "%d", m_iValue );

	SetWindowText( buffer );
	return TRUE;
}

void CSmartEdit::SetFormatString( ccp fmtstring )
{
	if( m_pFormat )
		free( m_pFormat );

	// this method is used so we can track allocations

	int len = strlen( fmtstring );
	m_pFormat = (TCHAR *)calloc( sizeof( TCHAR ), 1 + len );
	strcpy( m_pFormat, fmtstring );
}

int CSmartEdit::SetParams( cint imin, cint imax, cint ticbands )
{
	m_bUseFp = FALSE;
	m_iBands = ticbands;
	m_iMin = imin;
	m_iMax = imax;
	InitSlider();
	SetFormatString( "%d" );
	WORD type = SES_NUMBERS;
	if( imin < 0 )
		type |= SES_SIGNED;
	SetParseType( type );
	return TRUE;
}


int CSmartEdit::SetParams( cdbl dmin, cdbl dmax,
						cint ticbands, ccp fmtstring )
{
	m_bUseFp = TRUE;
	m_iBands = ticbands;
	m_dRange = dmax - dmin;
	m_dMin = dmin;
	m_dMax = dmax;
	m_iMin = 0;
	m_iMax = 1000;

	InitSlider();
	SetFormatString( fmtstring );
	SetParseType( SES_FLOATINGPT );
	return TRUE;
}

int CSmartEdit::SetValue( cint ivalue )
{
	if( m_bUseFp )
		return FALSE;

	if( ( ivalue < m_iMin ) || ( ivalue > m_iMax ) )
		return FALSE;

	TCHAR buf[512];
	sprintf( buf, m_pFormat, ivalue );
	SetWindowText( buf );
	return TRUE;
}


int CSmartEdit::SetValue( cdbl dvalue )
{
	if( ! m_bUseFp )
		return FALSE;

	if( ( dvalue < m_dMin ) || ( dvalue > m_dMax ) )
		return FALSE;

	TCHAR buf[512];
	sprintf( buf, m_pFormat, dvalue );
	SetWindowText( buf );
	return TRUE;
}


void CSmartEdit::OnUpdate() 
{	
#if 0
	CString strWindowText;
	LONG ValidationNumber;
	//	Initialize Variables
	strWindowText.Empty ( );
	ValidationNumber = 0;
	//	Remove the leading zeros from the edit control
	RemoveLeadingZeros ( );
	//	Copy the contents of the edit control to a string
	GetWindowText ( strWindowText );
	//	Check if the edit control is blank

	if ( strWindowText.IsEmpty ( ) )
	{
		m_myLastValidValue = BLANK_ENTRY;
	}
	else
	{
		ValidationNumber = atol ( strWindowText );

		if ( ( ValidationNumber < m_myMin ) || ( ValidationNumber > m_myMax ) )
		{
			if ( m_myLastValidValue >= 0 )
			{
				strWindowText.Format ( "%d", m_myLastValidValue );
			}
			else
			{
				strWindowText.Empty ( );
			}
			SetWindowText ( strWindowText );
			SetSel ( strWindowText.GetLength ( ), strWindowText.GetLength ( ) );
			
			MessageBeep ( 0xFFFFFFFF );
		}
		else
		{
			m_myLastValidValue = ValidationNumber;
		}
	}
#endif
}

void CSmartEdit::RemoveLeadingZeros()
{
	//	Local Variables
	//
	CString strWindowText;
	SHORT index;

	strWindowText.Empty ( );
	index = 0;
	
	GetWindowText ( strWindowText );

	if ( strWindowText.GetLength ( ) > 1 )
	{
		if(!(m_wParseType&SES_LETTERS))//Chiu 0507 如果同时允许字母的时候，不去除起始的0字符
		{
			if(m_wParseType&SES_SIGNED)
			{
				index = strWindowText.FindOneOf ( "-123456789" );
			}
			else
			{
				index = strWindowText.FindOneOf ( "123456789" );
			}

			if ( index > 0 )
			{
				strWindowText = strWindowText.Mid ( index );
			}
			else  if ( index == -1 )
			{
				strWindowText = "0";
			}
			if ( index != 0 )
			{
				SetWindowText ( strWindowText );
				SetSel ( 0, 0 );
			}
		}
#if 0
		else
		{
		    if(m_wParseType&SES_NUMBERS)
			   strWindowText.Format("%d",atol(strWindowText));
		    else if(m_wParseType&SES_FLOATINGPT)
			   strWindowText.Format("%f",atof(strWindowText));
               

			SetWindowText ( strWindowText );
		}
#endif
	}
}

void CSmartEdit::SetRange(LONG lMin, LONG lMax)
{
	ASSERT(lMin<=lMax);
	m_myMin = lMin;
	m_myMax = lMax;
	m_myLastValidValue = lMin;
	if(!(m_wParseType & SES_NUMBERS))
		return;
	else
		Validate();
}
CSmartEdit::CSmartEdit(CWnd* pParent, CRect& rect, DWORD dwStyle,WORD wType, UINT nID,
                 int nRow, int nColumn, CString sInitText, UINT nFirstChar)
{

}

BOOL CSmartEdit::CheckData() 
{
	CString strWindowText;
	double ValidationNumber;
	//	Initialize Variables
	strWindowText.Empty ( );
	ValidationNumber = 0;

	//	Remove the leading zeros from the edit control
	RemoveLeadingZeros ( );
	//	Copy the contents of the edit control to a string
	GetWindowText ( strWindowText );
	//	Check if the edit control is blank

//	if(strlen(strWindowText)>strlen((CString)(m_myMin)))
//	{
/*	CString strMin,strMax;
	strMin.Format("%d",m_myMin);
	strMax.Format("%d",m_myMax);
	if(strlen(strWindowText)>strlen(strMin)&&strlen(strWindowText)>strlen(strMax))
		//Chiu 0625
		//当输入字符长度超过最大
	*/	
	if (!(m_wParseType & SES_NUMBERS) && strWindowText.IsEmpty ( ) )
	{
		m_myLastValidValue = BLANK_ENTRY;
	}
	else
	{
		ValidationNumber = atof ( strWindowText );
		if ( ( ValidationNumber < m_myMin ) || ( ValidationNumber > m_myMax ) )
		{

			char errbuf[32];
			long lMax = m_myMax;
			long lMin = m_myMin;
			MessageBeep ( 0xFFFFFFFF );
			Sleep(100);
			MessageBeep ( 0xFFF);
			Sleep(50);

			if(ValidationNumber < m_myMin)
			{
			    m_myLastValidValue = m_myLastValidValue;
				ValidationNumber = m_myLastValidValue;
				SetWindowText(ltoa(m_myLastValidValue,errbuf,10));	
			
			}
			else if(ValidationNumber>m_myMax)
			{
				m_myLastValidValue = m_myLastValidValue;
				ValidationNumber = m_myLastValidValue;
				SetWindowText(ltoa(m_myLastValidValue,errbuf,10));	
			
			}
            return FALSE;
		}
		else
		{
			m_myLastValidValue = ValidationNumber;
		}
	}
	return TRUE;
}

void CSmartEdit::SetSlideLink(CFormView *pParent, int sliderid)
{
	m_pSlider = (CLinkSlider *)pParent->GetDlgItem( sliderid );
	ASSERT( m_pSlider );
	m_pSlider->SetEditLink( this );
}
void CSmartEdit::SetSlideLink(CDialog *pParent, int sliderid)
{
	m_pSlider = (CLinkSlider *)pParent->GetDlgItem( sliderid );
	ASSERT( m_pSlider );
	m_pSlider->SetEditLink( this );
}

AfxApi CLinkSlider * GetLinkSlider( CWnd *pcwnd, int id )
{
	return (CLinkSlider *)pcwnd->GetDlgItem( id );
}


///////////////////////////////////////////////////////////


BEGIN_MESSAGE_MAP(CLinkSlider, CSliderCtrl)
	//{{AFX_MSG_MAP(CLinkSlider)
	ON_WM_HSCROLL_REFLECT()
	ON_WM_VSCROLL_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CLinkSlider::CLinkSlider() : CSliderCtrl()
{
	m_pEdit = NULL;
	m_iPosition = INT_MAX;
	m_bVertical = FALSE;
}


void CLinkSlider::SetEditLink( CSmartEdit *pedit )
{
	m_pEdit = pedit;
	DWORD style = GetStyle();
	if( style & TBS_VERT )
		m_bVertical = TRUE;
}


void CLinkSlider::SetSlidePos( const int pos )
{
	if( m_bVertical )
		m_iPosition = m_iMax - ( pos - m_iMin );
	else
		m_iPosition = pos;

	SetPos( m_iPosition );
}


void CLinkSlider::SetSlideRange( const int imin, const int imax )
{
	m_iMin = imin;
	m_iMax = imax;
	SetRange( m_iMin, m_iMax );
}


void CLinkSlider::HScroll( UINT ncode, UINT pos )
{
	CSliderCtrl::OnHScroll( ncode, pos, NULL );
	if( ! m_pEdit )
		return;
	m_iPosition = GetPos();
	m_pEdit->UpdateEdit( m_iPosition );

	switch( ncode )
		{
		case TB_PAGEUP :
		case TB_PAGEDOWN :
			m_iPosition = GetPos();
			m_pEdit->UpdateEdit( m_iPosition );
			break;
	
		case TB_THUMBTRACK :
			m_iPosition = pos;
			m_pEdit->UpdateEdit( pos );
			break;
		}
}


void CLinkSlider::VScroll( UINT ncode, UINT pos )
{
	CSliderCtrl::OnVScroll( ncode, pos, NULL );
	if( ! m_pEdit )
		return;
  
	m_iPosition = m_iMax - ( GetPos() - m_iMin );
	m_pEdit->UpdateEdit( m_iPosition );

	switch( ncode )
		{
		// we have to play some games with vertical sliders -
		// max position is on the bottom and min is on the top

		case TB_PAGEUP :
		case TB_PAGEDOWN :
			m_iPosition = m_iMax - ( GetPos() - m_iMin );
			m_pEdit->UpdateEdit( m_iPosition );
			break;

		case TB_THUMBTRACK :
			m_iPosition = m_iMax - ( pos - m_iMin );
			m_pEdit->UpdateEdit( m_iPosition );
		}
}

int CSmartEdit::InitSlider()
{
	if( ! m_pSlider )
		return FALSE;
	m_pSlider->SetEditLink( this );
	m_iRange = m_iMax - m_iMin;
	m_pSlider->SetSlideRange( m_iMin, m_iMax );
	int freq = m_iRange / m_iBands;
	m_pSlider->SetTicFreq( freq );
	return TRUE;

}

void CSmartEdit::OnKillFocus(CWnd* pNewWnd) 
{
	CEdit::OnKillFocus(pNewWnd);
	char ez[256]={""};//ly 20110404
	// TODO: Add your message handler code here
		if(!CheckData())
		{
		 char	LastData[64];
			m_bConfirm = FALSE;
			CString strErr;
			strncpy(ez,GetLang().GetWarningText(21101),256);
			strErr.Format(ez,m_myMin,m_myMax);//"请输入范围%d和%d之内的数字"
			AfxMessageBox(strErr,MB_OK);
			SetWindowText(ltoa(int((m_myMax+m_myMin)/2),LastData,10));	
			return;
		}
}

BOOL CSmartEdit::GetConfirm()
{	
	return m_bConfirm;
}

void CSmartEdit::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CEdit::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	
}

//DEL int CSmartEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) 
//DEL {
//DEL 	if (CEdit::OnCreate(lpCreateStruct) == -1)
//DEL 		return -1;
//DEL 	
//DEL 	// TODO: Add your specialized creation code here
//DEL 	
//DEL 	return 0;
//DEL }

BOOL CSmartEdit::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	CWnd* pWnd = this;
	return pWnd->Create(_T("EDIT"), NULL, dwStyle, rect, pParentWnd, nID);
}

BOOL CSmartEdit::Validate()
{	
	CString strText;
	strText.Empty ( );
	GetWindowText(strText);
	LONG validateNum = 0;
	validateNum = atol(strText);
	validateNum = max(m_myMin,validateNum);
	validateNum = min(m_myMax,validateNum);
	strText.Format("%d",validateNum);
	SetWindowText(strText);
	return TRUE;
}
