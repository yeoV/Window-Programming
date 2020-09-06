#pragma once
#include "afxwin.h"


// CRoom1_9 대화 상자입니다.

class CRoom1_9 : public CDialog
{
	DECLARE_DYNAMIC(CRoom1_9)

public:
	CRoom1_9(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRoom1_9();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_room1_9 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnOK();
	BOOL door = FALSE;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();
	CBitmapButton Accept_Button;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
