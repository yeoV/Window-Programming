// Room2_3to4.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "btnimage.h"
#include "Room2_3to4.h"
#include "afxdialogex.h"


// CRoom2_3to4 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRoom2_3to4, CDialog)

CRoom2_3to4::CRoom2_3to4(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_room2_3to4, pParent)
{

}

CRoom2_3to4::~CRoom2_3to4()
{
}

void CRoom2_3to4::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRoom2_3to4, CDialog)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CRoom2_3to4 메시지 처리기입니다.


void CRoom2_3to4::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CClientDC dc(this);
	CRgn rgn_position;
	rgn_position.CreateRectRgn(222, 13, 310, 92);
	CBrush brush;
	

	if (rgn_position.PtInRegion(point)) {
		brush.CreateSolidBrush(RGB(0, 0, 255));
		room2_3to4 = TRUE;
		dc.FillRgn(&rgn_position,&brush);
		AfxMessageBox(_T("좋아 암호를 해독했어."));
		CDialog::OnOK();
	}
	else {
		AfxMessageBox(_T("이러다 걸리겠어..서두르자"));
		CDialog::OnOK();
	}
}
