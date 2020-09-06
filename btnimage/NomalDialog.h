#pragma once


// NomalDialog 대화 상자입니다.
class  CbtnimageView;
class NomalDialog : public CDialog
{
	DECLARE_DYNAMIC(NomalDialog)

public:
	NomalDialog(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~NomalDialog();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NOMAL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	int x_Pos, y_Pos;
	int width, height;
	CbtnimageView *view;
	CString  str_Caption;
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

