#if !defined(AFX_OPERATEREFCOORD_H__DB3CBFF2_7219_42A3_8116_8AB3C829214D__INCLUDED_)
#define AFX_OPERATEREFCOORD_H__DB3CBFF2_7219_42A3_8116_8AB3C829214D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OperateRefCoord.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COperateRefCoord form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include "stdafx.h"
class COperateRefCoord : public TVisualFormView
{
protected:
	void SetUI();//ly add 20110318
	COperateRefCoord();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(COperateRefCoord)

// Form Data
public:
	//{{AFX_DATA(COperateRefCoord)
	enum { IDD = IDD_OPERREFCOORDVIEW };
	CButton	m_ButtonSelectOverBorad;
	CSmartEdit	m_edtCCDBoardThick;
	CSmartEdit	m_edtGalvoBoardThick;
	CSmartEdit	m_edtCCDDistancePosY;
	CSmartEdit	m_edtCCDDistancePosX;
	CSmartEdit	m_edtGlvAdjPosY;
	CSmartEdit	m_edtGlvAdjPosX;
	CSmartEdit	m_edtBETPriOffset;
	CSmartEdit	m_edtThicknessY;
	CSmartEdit	m_edtThicknessX;
	CSmartEdit	m_edtBETOffset;
	CSmartEdit	m_edtAptOffset;
	CTransParentButton	m_btnReset;
	CTransParentButton	m_btnSet;
	CTransParentButton	m_btnSave;
	CSmartEdit	m_edtLaserCleanX;
	CSmartEdit	m_edtLaserCleanY;
	CSmartEdit	m_edtThickness;
	CSmartEdit	m_edtTabUnloadY;
	CSmartEdit	m_edtTabUnloadX;
	CSmartEdit	m_edtTabLoadY;
	CSmartEdit	m_edtTabLoadX;
	CComboBox	m_cmbScanHead;
	CSmartEdit	m_edtLaserPowerX;
	CSmartEdit	m_edtLaserPowerY;
	CSmartEdit	m_edtLaserPowerZ;
	long	m_lLaserPowerZ;
	long	m_lLaserPowerY;
	long	m_lLaserPowerX;
	long	m_lTabLoadX;
	long	m_lTabLoadY;
	long	m_lTabUnloadX;
	long	m_lTabUnloadY;
	long	m_lTestThickness;
	long	m_lLaserCleanX;
	long	m_lLaserCleanY;
	long	m_lAptOffset;
	long	m_lBETOffset;
	long	m_lCCDDistancePosX;
	long	m_lCCDDistancePosY;
	long	m_lCCDBoardThick;
	long	m_lGalvoBoardThick;
	long	m_lThicknessX;
	long	m_lThicknessY;
	long	m_lBETPriOffset;
	long	m_lGlvAdjPosX;
	long	m_lGlvAdjPosY;
	BOOL    m_SysOperate;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COperateRefCoord)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~COperateRefCoord();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(COperateRefCoord)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnResetTestPara();
	afx_msg void OnSetTestPara();
	afx_msg void OnDestroy();
	afx_msg void OnSelchangeCmbScanhead();
	afx_msg void OnDropdownCmbScanhead();
	afx_msg void OnSave();
	afx_msg void OnCheckOverbselect();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPERATEREFCOORD_H__DB3CBFF2_7219_42A3_8116_8AB3C829214D__INCLUDED_)
