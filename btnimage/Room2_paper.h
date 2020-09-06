#pragma once


// CRoom2_paper 대화 상자입니다.

class CRoom2_paper : public CDialog
{
	DECLARE_DYNAMIC(CRoom2_paper)

public:
	CRoom2_paper(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRoom2_paper();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_room2_paper };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
