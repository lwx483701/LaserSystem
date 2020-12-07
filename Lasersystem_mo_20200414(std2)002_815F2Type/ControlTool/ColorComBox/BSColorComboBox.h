
#if !defined(_BS_BSCOLORCB)
#define _BS_BSCOLORCB
extern UINT  WM_XLISTCTRL_COMBO_SELECTION;
//!!!为使用模板CArray/CList之类的数据类型所必须的头文件!!!
#include <afxtempl.h>

//系统常用颜色的自定义名称
const static char* strColorName[] = 
{
	"黑色", "红色","蓝色","栗色","绿色",  "深蓝色", "橄榄色", 
		
		"紫色",  "紫红","青色", "银灰", "灰色" ,"黄色", "浅绿", 
		
		"浅蓝", "白色"
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
	//初始化组合框(第一个被调用的函数)
	void InitBSColorCB(void);
	//得到当前的颜色值或R/G/B值
	COLORREF GetColor();
	void GetRGBValue(int* R, int* G, int* B);
public:
	//{{AFX_VIRTUAL(CBSColorComboBox)
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_VIRTUAL
	
protected:
	bool m_bOverControl;	//鼠标的状态(是否处于按钮上)	
	int iIconX, iIconY;		//SMALL ICON的大小尺寸
	COLORREF m_crColor;		//当前选中的颜色
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
