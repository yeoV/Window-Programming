#pragma once


// CRoom2_3to4 대화 상자입니다.

class CRoom2_3to4 : public CDialog
{
	DECLARE_DYNAMIC(CRoom2_3to4)

public:
	CRoom2_3to4(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRoom2_3to4();
	BOOL room2_3to4 = FALSE;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_room2_3to4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
