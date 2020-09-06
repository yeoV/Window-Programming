// Room2_paper.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "btnimage.h"
#include "Room2_paper.h"
#include "afxdialogex.h"


// CRoom2_paper 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRoom2_paper, CDialog)

CRoom2_paper::CRoom2_paper(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_room2_paper, pParent)
{

}

CRoom2_paper::~CRoom2_paper()
{
}

void CRoom2_paper::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRoom2_paper, CDialog)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CRoom2_paper 메시지 처리기입니다.


void CRoom2_paper::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialog::OnOK();
}
