// Room1_9.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "btnimage.h"
#include "Room1_9.h"
#include "afxdialogex.h"


// CRoom1_9 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRoom1_9, CDialog)

CRoom1_9::CRoom1_9(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_room1_9, pParent)
{

	
}

CRoom1_9::~CRoom1_9()
{
}

void CRoom1_9::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, Accept_Button);
}


BEGIN_MESSAGE_MAP(CRoom1_9, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CRoom1_9 메시지 처리기입니다.





void CRoom1_9::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	int answer1, answer2, answer3, answer4;
	answer1 = GetDlgItemInt(IDC_ANSWER1);
	answer2 = GetDlgItemInt(IDC_ANSWER2);
	answer3 = GetDlgItemInt(IDC_ANSWER3);
	answer4 = GetDlgItemInt(IDC_ANSWER4);

	if (answer1 == 1 && answer2 == 0 && answer3 == 2 && answer4 == 4) {
		door = TRUE;
		CDialog::OnOK();
	}
	else
		AfxMessageBox(_T("다시 풀어보자."));
}


BOOL CRoom1_9::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(rect);
	pDC->FillSolidRect(rect, RGB(0, 0, 0));
	return TRUE;
}


BOOL CRoom1_9::OnInitDialog()
{
	CDialog::OnInitDialog();

	BOOL bResult = FALSE;

	LONG lResult = SetWindowLong(this->GetSafeHwnd()
		, GWL_EXSTYLE
		, GetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE) | WS_EX_LAYERED);
	bResult = SetLayeredWindowAttributes(0, 210, LWA_ALPHA);
	Accept_Button.LoadBitmaps(IDB_ADMIT, IDB_ADMIT, NULL, NULL);
	Accept_Button.SizeToContent();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CRoom1_9::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialog::OnOK();
}
