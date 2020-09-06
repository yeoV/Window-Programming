#pragma once
#include "afxwin.h"


// CRoom1_2 대화 상자입니다.

class CRoom1_2 : public CDialogEx
{
	DECLARE_DYNAMIC(CRoom1_2)

public:
	CRoom1_2(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRoom1_2();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_room1_2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnBnClickedOk();
	BOOL box = FALSE;
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	CBitmapButton Accept_Button;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
