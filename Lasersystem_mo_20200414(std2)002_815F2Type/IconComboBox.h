// IconComboBox.h : header file
//

#ifndef _ICONCOMBOBOX_H_
#define _ICONCOMBOBOX_H_

//////////////////////////////////////////////////////
//                                                  //
//                   CIconComboBox                  //
//                                                  //
// Copyright (c) Joel Wahlberg ENATOR Networks 1997 //
//               joel.wahlberg@enator.se            //
//                                                  //
//////////////////////////////////////////////////////

class CIconComboBox : public CComboBox
{
// Contruction/Destruction
public:
	CIconComboBox();
	virtual ~CIconComboBox();

// Attributes
public:
	CSize m_sizeIcon;

// Operations
public:
	virtual int AddIcon(LPCTSTR lpszIconFile);
	virtual int InsertIcon(int nIndex, LPCTSTR lpszIconFile);
	virtual int SelectIcon(LPCTSTR lpszIconFile);
	virtual int SelectIcon(int nIndex);
	virtual int DeleteIcon(LPCTSTR lpszIconFile);
	virtual int DeleteIcon(int nIndex);

// Implementation
protected:
	virtual void OnOutputIcon(LPDRAWITEMSTRUCT lpDIS, BOOL bSelected);

// Overrides
	virtual int AddString(LPCTSTR lpszString);
	virtual int InsertString(int nIndex, LPCTSTR lpszString);
	virtual int DeleteString(int nIndex);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMIS);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
};

#endif // _ICONCOMBOBOX_H_
