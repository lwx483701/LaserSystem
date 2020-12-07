// ColorProgressCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "ColorProgressCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorProgressCtrl
/*
��ɫ������ yutingxun 2006-8-24
*/
CColorProgressCtrl::CColorProgressCtrl()
{
	m_iLower = 0;
	m_iUpper = 120;
	m_iCurrentPosition=m_iUpper;

	m_clrStart=	COLORREF(RGB(0,0,255));
	m_clrEnd=	COLORREF(RGB(255,0,0));
	m_clrBkGround=::GetSysColor(COLOR_3DFACE);
	m_clrText=COLORREF(RGB(255,255,255));

}

CColorProgressCtrl::~CColorProgressCtrl()
{
}


BEGIN_MESSAGE_MAP(CColorProgressCtrl, CProgressCtrl)
	//{{AFX_MSG_MAP(CColorProgressCtrl)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorProgressCtrl message handlers

void CColorProgressCtrl::SetRange(long iLow,long iUpper)
{
	m_iLower=iLow;
	m_iUpper=iUpper;
	m_iCurrentPosition=iUpper;
	CProgressCtrl::SetRange(iLow,iUpper);
}

void CColorProgressCtrl::DrawGradient(CPaintDC *pDC, const RECT &rectClient, const int &nMaxWidth)
{
	RECT	rectFill;		//��ʾ����
	float	fStep;			//ÿһ���ķ���
	CBrush	brush;			//��ʾ����ɫ��ˢ
//	CMemDC	memDC(pDC);	

	int		r,g,b;
	float	rStep,gStep,bStep;
	//�õ���ͬ��ɫ�������������ɫ֮�������ֵ
	r=(GetRValue(m_clrEnd)-GetRValue(m_clrStart));
	g=(GetGValue(m_clrEnd)-GetGValue(m_clrStart));
	b=(GetBValue(m_clrEnd)-GetBValue(m_clrStart));
	//ʹ��������ʾ������ ����������ɫ��ֵ
	int		nSteps=max(abs(r),max(abs(g),abs(b)));
	//ȷ��ÿһ��ɫ�����ľ�������
	fStep=(float)rectClient.right/(float)nSteps;
	//����ÿһ��ɫ���Ĳ���
	rStep=r/(float)nSteps;
	gStep=g/(float)nSteps;
	bStep=b/(float)nSteps;

	r=GetRValue(m_clrStart);
	g=GetGValue(m_clrStart);
	b=GetBValue(m_clrStart);
	//������ɫ����Ľ�����
	for(int iOnBand=0;iOnBand<nSteps;iOnBand++)
	{
		::SetRect(&rectFill,
			//����Ϊ��������������Ͻ�x,y�����½�x,y
							(int)(iOnBand*fStep),
							0,
							(int)((iOnBand+1)*fStep),
							rectClient.bottom+1);
		
		VERIFY(brush.CreateSolidBrush(RGB(r+rStep*iOnBand,g+gStep*iOnBand,b+bStep*iOnBand)));
		pDC->FillRect(&rectFill,&brush);
		VERIFY(brush.DeleteObject());
		//�ڽ�������֮ǰ��ʹ�ñ���ɫ�����µĵĿͻ�����
		if(rectFill.right>nMaxWidth)
		{
			::SetRect(&rectFill,rectFill.right,0,rectClient.right,rectClient.bottom);
			VERIFY(brush.CreateSolidBrush(m_clrBkGround));
			pDC->FillRect(&rectFill,&brush);
			VERIFY(brush.DeleteObject());
			return;
		}
	}
}

void CColorProgressCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	if(m_iCurrentPosition<=m_iLower||m_iCurrentPosition>=m_iUpper)
	{
		CRect rect;
		GetClientRect(rect);
		CBrush brush;
		brush.CreateSolidBrush(::GetSysColor(COLOR_3DFACE));
		dc.FillRect(&rect,&brush);
		VERIFY(brush.DeleteObject());
		return;
	}
	CRect rectClient;
	GetClientRect(rectClient);
	float maxWidth((float)m_iCurrentPosition/(float)m_iUpper*(float)rectClient.right);
	//����
	DrawGradient(&dc,rectClient,(int)maxWidth);
	
	// Do not call CProgressCtrl::OnPaint() for painting messages
}
int CColorProgressCtrl::SetPos(long iPos)
{
	//Set the Position of the Progress
	m_iCurrentPosition=iPos;
	return (CProgressCtrl::SetPos(iPos));
}