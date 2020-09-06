// NomalDialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "btnimage.h"
#include "NomalDialog.h"
#include "afxdialogex.h"


// NomalDialog 대화 상자입니다.

IMPLEMENT_DYNAMIC(NomalDialog, CDialog)

NomalDialog::NomalDialog(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_NOMAL, pParent)
{

}

NomalDialog::~NomalDialog()
{
}

void NomalDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(NomalDialog, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// NomalDialog 메시지 처리기입니다.


BOOL NomalDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	BOOL bResult = FALSE;

	LONG lResult = SetWindowLong(this->GetSafeHwnd()
		, GWL_EXSTYLE
		, GetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE) | WS_EX_LAYERED);
	bResult = SetLayeredWindowAttributes(0, 170 ,LWA_ALPHA);
	MoveWindow(x_Pos, y_Pos, width, height);

	//폰트
	CFont font1, font2;
	font1.CreatePointFont(30, _T("굴림"));
	font2.CreatePointFont(20, _T("굴림"));
	GetDlgItem(IDC_EXPLAIN)->SetFont(&font1);
	GetDlgItem(IDC_ENTER)->SetFont(&font2);
	GetDlgItem(IDC_EXPLAIN)->SetWindowText(str_Caption);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL NomalDialog::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(rect);
	pDC->FillSolidRect(rect, RGB(0, 0, 0));
	return TRUE;
}


HBRUSH NomalDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	UINT nID = pWnd->GetDlgCtrlID();

	if (nID == IDC_EXPLAIN)
	{
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 255));
		hbr = ::CreateSolidBrush(RGB(0, 0, 0));
	}
	if (nID == IDC_ENTER)
	{
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 255));
		hbr = ::CreateSolidBrush(RGB(0, 0, 0));
	}
	return hbr;
}


void NomalDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialog::OnOK();
}
