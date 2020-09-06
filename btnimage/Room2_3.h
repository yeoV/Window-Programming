#pragma once
#include "afxwin.h"


// CRoom2_3 대화 상자입니다.

class CRoom2_3 : public CDialog
{
	DECLARE_DYNAMIC(CRoom2_3)

public:
	CRoom2_3(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRoom2_3();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_room2_3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnOK();
	BOOL room2_3 = FALSE;
	CBitmapButton Accept_Button;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
