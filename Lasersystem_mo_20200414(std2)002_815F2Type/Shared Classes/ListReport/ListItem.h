// ListItem.h: interface for the CListItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISTITEM_H__628A9CFB_6C8A_4D1E_85BE_A6F71878E625__INCLUDED_)
#define AFX_LISTITEM_H__628A9CFB_6C8A_4D1E_85BE_A6F71878E625__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include "ListReport.h"

using namespace std;
using namespace ListReportDefinition;

class CListItem  
{
public:
	CListItem(string sProperty="") : m_sProperty(sProperty) {};
	virtual ~CListItem() {};
	virtual void DrawRect(CDC &dc, CRect rcItem, string sText, bool bSelected) = 0;
	virtual void ClickItem(CListReport *pParent, int intRow, int intColumn) = 0;
	virtual void DbClickItem(CListReport *pParent, int intRow, int intColumn) = 0;
protected:
	string m_sProperty;
};

class CListItemText : public CListItem
{
public:
	CListItemText(string sProperty="");
	virtual ~CListItemText() {};
	static string GenerateProperty(bool bBold, COLORREF color);
	virtual void DrawRect(CDC &dc, CRect rcItem, string sText, bool bSelected);
	virtual void ClickItem(CListReport *pParent, int intRow, int intColumn){}
	virtual void DbClickItem(CListReport *pParent, int intRow, int intColumn){}
private:
	bool m_bBold;
	COLORREF m_colorText;
};

class CListItemCheckBox : public CListItem
{
public:
	CListItemCheckBox(string sProperty="");
	virtual ~CListItemCheckBox() {};
	static string GenerateProperty();
	virtual void DrawRect(CDC &dc, CRect rcItem, string sText, bool bSelected);
	virtual void ClickItem(CListReport *pParent, int intRow, int intColumn);
	virtual void DbClickItem(CListReport *pParent, int intRow, int intColumn){ClickItem(pParent, intRow, intColumn);}
};
#endif // !defined(AFX_LISTITEM_H__628A9CFB_6C8A_4D1E_85BE_A6F71878E625__INCLUDED_)
