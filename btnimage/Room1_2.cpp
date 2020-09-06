// Room1_2.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "btnimage.h"
#include "Room1_2.h"
#include "afxdialogex.h"

// CRoom1_2 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRoom1_2, CDialogEx)

CRoom1_2::CRoom1_2(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_room1_2, pParent)
{

}

CRoom1_2::~CRoom1_2()
{
}

void CRoom1_2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, Accept_Button);
}


BEGIN_MESSAGE_MAP(CRoom1_2, CDialogEx)
//	ON_BN_CLICKED(ID_OK, &CRoom1_2::OnBnClickedOk)
ON_WM_ERASEBKGND()
ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CRoom1_2 메시지 처리기입니다.







void CRoom1_2::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	int m_answer1,m_answer2,m_answer3;
	m_answer1 = GetDlgItemInt(IDC_ANSWER1);
	m_answer2 = GetDlgItemInt(IDC_ANSWER2);
	m_answer3 = GetDlgItemInt(IDC_ANSWER3);

	if (m_answer1 == 2 && m_answer2 == 2 && m_answer3 == 1) {
		box = TRUE;
		CDialogEx::OnOK();
	}
	else
		AfxMessageBox(_T("다시 풀어보자"));
	CDialog::OnOK();
}


BOOL CRoom1_2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

BOOL bResult = FALSE;

	LONG lResult = SetWindowLong(this->GetSafeHwnd()
		, GWL_EXSTYLE
		, GetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE) | WS_EX_LAYERED);
	bResult = SetLayeredWindowAttributes(0, 210, LWA_ALPHA);
	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	
		Accept_Button.LoadBitmaps(IDB_ADMIT, IDB_ADMIT, NULL, NULL);
		Accept_Button.SizeToContent();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL CRoom1_2::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(rect);
	pDC->FillSolidRect(rect, RGB(0, 0, 0));
	return TRUE;
}


void CRoom1_2::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialog::OnOK();
}
