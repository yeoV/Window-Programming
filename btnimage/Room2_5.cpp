// Room2_5.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "btnimage.h"
#include "Room2_5.h"
#include "afxdialogex.h"


// CRoom2_5 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRoom2_5, CDialog)

CRoom2_5::CRoom2_5(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_room2_5, pParent)
{

}

CRoom2_5::~CRoom2_5()
{
}

void CRoom2_5::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, Accept_Button);
}


BEGIN_MESSAGE_MAP(CRoom2_5, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CRoom2_5 메시지 처리기입니다.


void CRoom2_5::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CString edit1;
	GetDlgItemText(IDC_EDIT1, edit1);

	if (edit1 == _T("door") || edit1 == _T("DOOR")) {
		room2_5 = TRUE;
		AfxMessageBox(_T("좋아. 거의 다 푼것같은데."));
		CDialog::OnOK();
	}
	else {
		AfxMessageBox(_T("다시한번 해보자."));
	}
}


BOOL CRoom2_5::OnInitDialog()
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


BOOL CRoom2_5::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(rect);
	pDC->FillSolidRect(rect, RGB(0, 0, 0));
	return TRUE;
}


HBRUSH CRoom2_5::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);


	UINT nID = pWnd->GetDlgCtrlID();

	if (nID == IDC_Caption1)
	{
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 255));
		hbr = ::CreateSolidBrush(RGB(0, 0, 0));
	}
	if (nID == IDC_Caption2)
	{
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 255));
		hbr = ::CreateSolidBrush(RGB(0, 0, 0));
	}
	return hbr;
}


void CRoom2_5::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialog::OnOK();
}
