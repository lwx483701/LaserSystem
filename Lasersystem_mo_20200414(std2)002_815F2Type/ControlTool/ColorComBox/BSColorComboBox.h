
#if !defined(_BS_BSCOLORCB)
#define _BS_BSCOLORCB
extern UINT  WM_XLISTCTRL_COMBO_SELECTION;
//!!!Ϊʹ��ģ��CArray/CList֮������������������ͷ�ļ�!!!
#include <afxtempl.h>

//ϵͳ������ɫ���Զ�������
const static char* strColorName[] = 
{
	"��ɫ", "��ɫ","��ɫ","��ɫ","��ɫ",  "����ɫ", "���ɫ", 
		
		"��ɫ",  "�Ϻ�","��ɫ", "����", "��ɫ" ,"��ɫ", "ǳ��", 
		
		"ǳ��", "��ɫ"
};

const static char* strColorName_En[] = 
{
	"black", "red","blue","dark red","dark green",  "dark blue", "dark yellow", 
		
		"dark magenta", "purple" ,"cyan", "silver gray", "gray" ,"yellow", "green", 
		
		"litht blue", "white"
};

const static COLORREF RGBValue[] = 
{
	
		RGB(0,0,0),//black
		RGB(255,0,0),//red
		RGB(0,0,255),//blue
		RGB(128,0,0),// dark red
		RGB(0,128,0),//dark green
		RGB(0,0,120),///dark blue
		RGB(128,128,0),//dark yellow
		RGB(128,0,128),//dark magenta
		RGB(255,0,255),//magenta
		RGB(0,128,128),//dark cyan
		RGB(192,192,192),//litht gray
		RGB(128,128,128),//dark gray
		RGB(255,255,0),//yellow
		RGB(0,255,0),//green
		RGB(0,255,255),//cyan
		RGB(255,255,255),//white
		
		
};
typedef struct BSCBITEM
{
	int			iIndex;
	COLORREF	crColor;
	LPCTSTR		lpCaption;
}BSCBITEM, *LPBSCBITEM;

class CBSColorComboBox : public CComboBox
{
	DECLARE_DYNCREATE(CBSColorComboBox)		
public:
	CBSColorComboBox();
	virtual ~CBSColorComboBox();

	BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	//��ʼ����Ͽ�(��һ�������õĺ���)
	void InitBSColorCB(void);
	//�õ���ǰ����ɫֵ��R/G/Bֵ
	COLORREF GetColor();
	void GetRGBValue(int* R, int* G, int* B);
public:
	//{{AFX_VIRTUAL(CBSColorComboBox)
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_VIRTUAL
	
protected:
	bool m_bOverControl;	//����״̬(�Ƿ��ڰ�ť��)	
	int iIconX, iIconY;		//SMALL ICON�Ĵ�С�ߴ�
	COLORREF m_crColor;		//��ǰѡ�е���ɫ
	CList<LPBSCBITEM, LPBSCBITEM> m_crItem;
	
	void OnCBPaint(CDC* pDC);
	LPBSCBITEM GetItem(int iIndex = 0);
	
protected:
	
	COLORREF			m_nComboItem;
	int				m_nComboSubItem;
	//{{AFX_MSG(CBSColorComboBox)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSelchange();
	afx_msg void OnSelendok();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
};
#endif // !defined(_BS_BSCOLORCB)
