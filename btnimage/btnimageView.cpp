
// btnimageView.cpp : CbtnimageView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "btnimage.h"
#endif

#include "btnimageDoc.h"
#include "btnimageView.h"
#include "Room1_2.h"
#include "Room1_9.h"
#include "Room2_1.h"
#include "Room2_2.h"
#include "Room2_3.h"
#include "Room2_3to4.h"
#include "Room2_5.h"
#include "Room2_paper.h"
#include "NomalDialog.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CbtnimageView

IMPLEMENT_DYNCREATE(CbtnimageView, CFormView)

BEGIN_MESSAGE_MAP(CbtnimageView, CFormView)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_HINT, &CbtnimageView::OnBnClickedHint)
	ON_LBN_DBLCLK(IDC_LIST1, &CbtnimageView::OnLbnDblclkList1)
	ON_BN_CLICKED(IDC_START, &CbtnimageView::OnBnClickedStart)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CbtnimageView 생성/소멸

CbtnimageView::CbtnimageView()
	: CFormView(IDD_BTNIMAGE_FORM)
{
	// TODO: 여기에 생성 코드를 추가합니다.
room1 = FALSE;
 room1_clear = FALSE;
 room2 = FALSE;
 room2_clear = FALSE;
 room3 = FALSE;
 Caption1 = TRUE;
	 Caption2 = TRUE;
 bProgress = FALSE;
 bCover = TRUE;
 gameover = FALSE;
 bStart, bFinish, bCheck_Lbutton, bScene_Done = FALSE;
 iStart_SceneNumber = 1;
 iStart_SceneMax = 14;
}

CbtnimageView::~CbtnimageView()
{
}

void CbtnimageView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HINT, m_hint);
	DDX_Control(pDX, IDC_LIST1, m_item);
	DDX_Control(pDX, IDC_nHint, m_nHint);
	DDX_Control(pDX, IDC_START, Start_Button);
	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
}

BOOL CbtnimageView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.
	return CFormView::PreCreateWindow(cs);
}

void CbtnimageView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	//stime = GetCurrentTime();
	str.Format(_T("%d"), 3);
	m_nHint.SetWindowText(str);

	m_item.AddString(_T("light"));

	Start_Button.LoadBitmaps(IDB_STARTBUTTON, IDB_STARTBUTTON, NULL, NULL);
	Start_Button.SizeToContent();

	m_hint.LoadBitmaps(IDB_HINT, IDB_HINT, NULL, NULL);
	m_hint.SizeToContent();
}


// CbtnimageView 진단

#ifdef _DEBUG
void CbtnimageView::AssertValid() const
{
	CFormView::AssertValid();
}

void CbtnimageView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CbtnimageDoc* CbtnimageView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CbtnimageDoc)));
	return (CbtnimageDoc*)m_pDocument;
}
#endif //_DEBUG


// CbtnimageView 메시지 처리기

void CbtnimageView::OnDraw(CDC* pDC)
{
	CClientDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	if ((gameover == TRUE )&& (bCover==FALSE)) {
		CClientDC dc(this);
		CRect rect;
		GetClientRect(&rect);
		dc.SelectStockObject(BLACK_BRUSH);
		dc.Rectangle(&rect);
		dc.SetTextColor(RGB(255, 255, 255));
		gameover = FALSE;
		
		(GetDlgItem(IDC_LIST1))->ShowWindow(FALSE);
		GetDlgItem(IDC_LIST1)->EnableWindow(FALSE);
		(GetDlgItem(IDC_HINT))->ShowWindow(FALSE);
		GetDlgItem(IDC_HINT)->EnableWindow(FALSE);
		(GetDlgItem(IDC_nHint))->ShowWindow(FALSE);
		GetDlgItem(IDC_nHint)->EnableWindow(FALSE);
		GetDlgItem(IDC_PROGRESS1)->ShowWindow(FALSE);
		GetDlgItem(IDC_PROGRESS1)->EnableWindow(FALSE);

		Print_Image(IDB_explorer, 50, 0);
		Call_Dialog(_T("자네 지금 무얼 하는 건가?"),170);
		Print_Image(IDB_GameOver, 0, 0);
		Wait(1500);
		bCover = TRUE;
		Caption1 = TRUE;
		Caption2 = TRUE;
		GetDlgItem(IDC_START)->ShowWindow(TRUE);
		GetDlgItem(IDC_START)->EnableWindow(TRUE);
		room1_stage = 1;
		room2_stage = 0;
		room3_stage = 0;
		
		int count = m_item.GetCount();
		m_item.SetCurSel(count - 1);
		for (int i = 1; i < count ; i++) {
			m_item.DeleteString(i);
		}
		
	}
	else if (bCover == TRUE)
	{
		Print_Image(IDB_COVER, 0, 0);
		bCover = FALSE;
	}
	else if (bStart == TRUE) {
		int iStr_length = 0, iMoveleft = 0;;
		CString tmpStory, Story;
		//바탕 검은색, 글자 흰색 배경 투명, 글자정렬
		//	GetClientRect(&rect);
		dc.SelectStockObject(BLACK_BRUSH);
		dc.Rectangle(&rect);
		dc.SetBkColor(TRANSPARENT);
		dc.SetTextColor(RGB(255, 255, 255));
		dc.SetTextAlign(TA_CENTER | TA_BOTTOM);

		//신 갯수는 13개임
		if (iStart_SceneNumber == 1)
		{
			Story = _T("[MFC 중간 성적 발표날..]");
			iStr_length = Story.GetLength();
			iMoveleft = 140;
		}
		else if (iStart_SceneNumber == 2)
		{
			Print_Image(IDB_Score, 250, 50);
			Story = _T("이번 성적 가볍게 1등이네.");
			iStr_length = Story.GetLength();
			iMoveleft = 160;
		}
		else if (iStart_SceneNumber == 3) {
			Story = _T("이번에도 장학금은 양보해줘야지..훗 나란녀석");
			iStr_length = Story.GetLength();
			iMoveleft = 200;
		}
		else if (iStart_SceneNumber == 4) {
			Story = _T("이정도면 교수님도 인생 재시작 권유하시는 부분~");
			iStr_length = Story.GetLength();
			iMoveleft = 200;
		}
		else if (iStart_SceneNumber == 5) {
			//			Print_Image(IDB_ME, 250, 50);
			Story = _T("헤헤 신난다 ㅎㅎㅎ");
			iStr_length = Story.GetLength();
			iMoveleft = 100;
		}
		else if (iStart_SceneNumber == 6) {
			Story = _T("<마포 대교>");
			iStr_length = Story.GetLength();
			iMoveleft = 90;
		}
		else if (iStart_SceneNumber == 7) {
			Print_Image(IDB_MAPO, 200, 50);
			Story = _T("한강물이라도 따뜻하면 좋겠다..ㅎㅎ ");
			iStr_length = Story.GetLength();
			iMoveleft = 180;
		}
		else if (iStart_SceneNumber == 8) {
			Print_Image(IDB_MAPO, 200, 50);
			Story = _T(" 잘있어라 학점아....사랑했다 MFC..");
			iStr_length = Story.GetLength();
			iMoveleft = 200;
		}
		else if (iStart_SceneNumber == 9) {
			bScene_Done = FALSE;
			Print_Image(IDB_EYE3, 200, 50);
			Wait(1000);
			Print_Image(IDB_EYE2, 200, 50);
			Wait(1000);
			Print_Image(IDB_EYE1, 200, 50);
			Wait(1200);
			Story = _T("그순간.....");
			dc.Rectangle(&rect);

			iStr_length = Story.GetLength();
			iMoveleft = 40;
		}
		else if (iStart_SceneNumber == 10) {
			bScene_Done = FALSE;
			for (int i = 0; i < 3;i++)
			{
				dc.SelectStockObject(WHITE_BRUSH);
				dc.Rectangle(&rect);
				Wait(50);
				dc.SelectStockObject(BLACK_BRUSH);
				dc.Rectangle(&rect);
				Wait(50);
			}
			Story = _T("대뇌 : mfc 기말고사 시험지를 훔치면 되잖아!");
			iStr_length = Story.GetLength();
			iMoveleft = 200;
		}
		else if (iStart_SceneNumber == 11) {
			Story = _T("히에엑?! 대뇌님 혹시 하버드?!");
			iStr_length = Story.GetLength();
			iMoveleft = 160;
		}
		else if (iStart_SceneNumber == 12) {
			Story = _T("좋아.. 고민보단 GO..");
			iStr_length = Story.GetLength();
			iMoveleft = 130;
		}
		else if (iStart_SceneNumber == 13) {
			Story = _T("낄낄낄.. 기말고사는 100점이라구!..");
			iStr_length = Story.GetLength();
			iMoveleft = 160;
		}
		//글자 한글자씩 출력부분
		if (iStart_SceneNumber < iStart_SceneMax) {
			int yPos = rect.bottom - 30;
			if (iStart_SceneNumber == 1 || iStart_SceneNumber == 6 || iStart_SceneNumber == 9)
				yPos = rect.bottom / 2;
			bCheck_Lbutton = FALSE;
			bScene_Done = FALSE;
			int xPos = 19;
			for (int i = 0; i < iStr_length; i++) {
				tmpStory = Story.GetAt(i);
				dc.TextOut(rect.right / 2 - iMoveleft + xPos * i, yPos, tmpStory);
				if (!bCheck_Lbutton)
					Wait(70);
			}
			dc.DrawText(_T("Click ▼"), &rect, DT_BOTTOM | DT_RIGHT | DT_SINGLELINE);
			bScene_Done = TRUE;
		}
		if (iStart_SceneNumber == iStart_SceneMax) {
			for (int i = 0; i < 256;) {
				CBrush brush = RGB(i, i, i);
				dc.SelectObject(&brush);
				dc.Rectangle(&rect);
				Wait(30);
				i += 5;
			}
			bStart = FALSE;
			Print_Image(IDB_pro_clear, 0, 0);
			Wait(2000);
			room1 = TRUE;
			Invalidate();
		}
	}
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	else if (room1 == TRUE) {
		GetDlgItem(IDC_LIST1)->ShowWindow(TRUE);
		GetDlgItem(IDC_LIST1)->EnableWindow(TRUE);
		GetDlgItem(IDC_HINT)->ShowWindow(TRUE);
		GetDlgItem(IDC_HINT)->EnableWindow(TRUE);
		GetDlgItem(IDC_nHint)->ShowWindow(TRUE);
		GetDlgItem(IDC_nHint)->EnableWindow(TRUE);
		GetDlgItem(IDC_PROGRESS1)->ShowWindow(TRUE);
		CFont font;
		font.CreatePointFont(200, _T("Arial"));
		GetDlgItem(IDC_nHint)->SetFont(&font);


		if (room1_stage == 1) {

			CClientDC dc(this);
			CBitmap bitmap;
			bitmap.LoadBitmap(IDB_room1_1);
			BITMAP bmpinfo;
			bitmap.GetBitmap(&bmpinfo);

			CDC dcmem;
			dcmem.CreateCompatibleDC(&dc);
			dcmem.SelectObject(&bitmap);

			dc.BitBlt(0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, &dcmem, 0, 0, SRCCOPY);
			if (Caption1 == TRUE)
			{
				Caption1 = FALSE;
				
					bProgress = TRUE;
					m_progress.SetRange(0, 100);
					m_progress.SetPos(100);
					m_progress.SetState(PBST_NORMAL);
					SetTimer(100, 1800, NULL);
				
				Call_Dialog(_T("여기가 교수님의 침실인가?"), 170);
				Call_Dialog(_T("여기에 시험지에 대한 단서가 있을지도 몰라."), 170);
				Call_Dialog(_T("교수님은 3분뒤에 오시니까"), 170);
				Call_Dialog(_T("그 안에 얼른 찾고 나가야겠어."), 170);
				
			}
				

		}
		else if (room1_stage == 2) {
			CClientDC dc(this);
			CBitmap bitmap;
			bitmap.LoadBitmap(IDB_room1_2);
			BITMAP bmpinfo;
			bitmap.GetBitmap(&bmpinfo);

			CDC dcmem;
			dcmem.CreateCompatibleDC(&dc);
			dcmem.SelectObject(&bitmap);

			dc.BitBlt(0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, &dcmem, 0, 0, SRCCOPY);
		}
		else if (room1_stage == 3) {
			CClientDC dc(this);
			CBitmap bitmap;
			bitmap.LoadBitmap(IDB_room1_3);
			BITMAP bmpinfo;
			bitmap.GetBitmap(&bmpinfo);

			CDC dcmem;
			dcmem.CreateCompatibleDC(&dc);
			dcmem.SelectObject(&bitmap);

			dc.BitBlt(0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, &dcmem, 0, 0, SRCCOPY);
		}
		else if (room1_stage == 4) {
			CClientDC dc(this);
			CBitmap bitmap;
			bitmap.LoadBitmap(IDB_room1_4);
			BITMAP bmpinfo;
			bitmap.GetBitmap(&bmpinfo);

			CDC dcmem;
			dcmem.CreateCompatibleDC(&dc);
			dcmem.SelectObject(&bitmap);

			dc.BitBlt(0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, &dcmem, 0, 0, SRCCOPY);
		}
		else if (room1_stage == 5 || room1_stage == 6) {
			CClientDC dc(this);
			CBitmap bitmap;
			bitmap.LoadBitmap(IDB_room1_5);
			BITMAP bmpinfo;
			bitmap.GetBitmap(&bmpinfo);

			CDC dcmem;
			dcmem.CreateCompatibleDC(&dc);
			dcmem.SelectObject(&bitmap);

			dc.BitBlt(0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, &dcmem, 0, 0, SRCCOPY);
		}
		else if (room1_stage == 7) {
			CClientDC dc(this);
			CBitmap bitmap;
			bitmap.LoadBitmap(IDB_room1_6);
			BITMAP bmpinfo;
			bitmap.GetBitmap(&bmpinfo);

			CDC dcmem;
			dcmem.CreateCompatibleDC(&dc);
			dcmem.SelectObject(&bitmap);

			dc.BitBlt(0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, &dcmem, 0, 0, SRCCOPY);
		}
		else if (room1_stage == 8) {
			CClientDC dc(this);
			CBitmap bitmap;
			bitmap.LoadBitmap(IDB_room1_7);
			BITMAP bmpinfo;
			bitmap.GetBitmap(&bmpinfo);

			CDC dcmem;
			dcmem.CreateCompatibleDC(&dc);
			dcmem.SelectObject(&bitmap);

			dc.BitBlt(0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, &dcmem, 0, 0, SRCCOPY);
		}
		else if (room1_stage == 9) {
			CClientDC dc(this);
			CBitmap bitmap;
			bitmap.LoadBitmap(IDB_room1_8);
			BITMAP bmpinfo;
			bitmap.GetBitmap(&bmpinfo);

			CDC dcmem;
			dcmem.CreateCompatibleDC(&dc);
			dcmem.SelectObject(&bitmap);

			dc.BitBlt(0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, &dcmem, 0, 0, SRCCOPY);
		}
		else if (room1_stage == 10) {
			CClientDC dc(this);
			CBitmap bitmap;
			bitmap.LoadBitmap(IDB_room1_9);
			BITMAP bmpinfo;
			bitmap.GetBitmap(&bmpinfo);

			CDC dcmem;
			dcmem.CreateCompatibleDC(&dc);
			dcmem.SelectObject(&bitmap);

			dc.BitBlt(0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, &dcmem, 0, 0, SRCCOPY);
		}
	}
	else if (room1_clear == TRUE) {
		(GetDlgItem(IDC_LIST1))->ShowWindow(FALSE);
		(GetDlgItem(IDC_HINT))->ShowWindow(FALSE);
		(GetDlgItem(IDC_nHint))->ShowWindow(FALSE);
		(GetDlgItem(IDC_PROGRESS1))->ShowWindow(FALSE);

		Print_Image(IDB_room1_clear, 0, 0);
		Wait(1200);
		room1_clear = FALSE;
		room2 = TRUE;
		Invalidate();
	}
	else if (room2 == TRUE) {
		CFont font;
		font.CreatePointFont(200, _T("Arial"));
		GetDlgItem(IDC_nHint)->SetFont(&font);

		str.Format(_T("%d"), 3 - nHint);
		m_nHint.SetWindowText(str);
		if (room2_stage == 0) {
			(GetDlgItem(IDC_LIST1))->ShowWindow(TRUE);
			(GetDlgItem(IDC_HINT))->ShowWindow(TRUE);
			(GetDlgItem(IDC_nHint))->ShowWindow(TRUE);
			(GetDlgItem(IDC_PROGRESS1))->ShowWindow(TRUE);
			CClientDC dc(this);
			CBitmap bitmap;
			bitmap.LoadBitmap(IDB_room2_dark);
			BITMAP bmpinfo;
			bitmap.GetBitmap(&bmpinfo);

			CDC dcmem;
			dcmem.CreateCompatibleDC(&dc);
			dcmem.SelectObject(&bitmap);

			dc.BitBlt(0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, &dcmem, 0, 0, SRCCOPY);
			if (Caption2 == TRUE)
			{
				Caption2 = FALSE;
				Call_Dialog(_T("교수님의 서재로 이어지는구나."), 170);
				Call_Dialog(_T("교수님이 쓰시는 물건들을 먼저 살펴볼까?"), 170);
				Call_Dialog(_T("아마 연관성이 있겠지."), 170);
			}
		}
		else if (room2_stage == 8) {
			CClientDC dc(this);
			CBitmap bitmap;
			bitmap.LoadBitmap(IDB_room2_to_room3);
			BITMAP bmpinfo;
			bitmap.GetBitmap(&bmpinfo);

			CDC dcmem;
			dcmem.CreateCompatibleDC(&dc);
			dcmem.SelectObject(&bitmap);

			dc.BitBlt(0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, &dcmem, 0, 0, SRCCOPY);
		}
		else if (room2_stage == 5) {
			CClientDC dc(this);
			CBitmap bitmap;
			bitmap.LoadBitmap(IDB_room2_desk);
			BITMAP bmpinfo;
			bitmap.GetBitmap(&bmpinfo);

			CDC dcmem;
			dcmem.CreateCompatibleDC(&dc);
			dcmem.SelectObject(&bitmap);

			dc.BitBlt(0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, &dcmem, 0, 0, SRCCOPY);
		}
		else if (room2_stage == 6 || room2_stage == 7) {
			CClientDC dc(this);
			CBitmap bitmap;
			bitmap.LoadBitmap(IDB_room2_nokey);
			BITMAP bmpinfo;
			bitmap.GetBitmap(&bmpinfo);

			CDC dcmem;
			dcmem.CreateCompatibleDC(&dc);
			dcmem.SelectObject(&bitmap);

			dc.BitBlt(0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, &dcmem, 0, 0, SRCCOPY);
		}
		else {
			CClientDC dc(this);
			CBitmap bitmap;
			bitmap.LoadBitmap(IDB_room2);
			BITMAP bmpinfo;
			bitmap.GetBitmap(&bmpinfo);

			CDC dcmem;
			dcmem.CreateCompatibleDC(&dc);
			dcmem.SelectObject(&bitmap);

			dc.BitBlt(0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, &dcmem, 0, 0, SRCCOPY);
		}
	}
	else if (room2_clear == TRUE) {
		(GetDlgItem(IDC_LIST1))->ShowWindow(FALSE);
		(GetDlgItem(IDC_HINT))->ShowWindow(FALSE);
		(GetDlgItem(IDC_nHint))->ShowWindow(FALSE);
		(GetDlgItem(IDC_PROGRESS1))->ShowWindow(FALSE);
		Print_Image(IDB_room2_clear, 0, 0);
		Wait(1200);
		room2_clear = FALSE;
		room3 = TRUE;
		Invalidate();
	}
	else if (room3 == TRUE) {
		(GetDlgItem(IDC_LIST1))->ShowWindow(TRUE);
		(GetDlgItem(IDC_HINT))->ShowWindow(TRUE);
		(GetDlgItem(IDC_nHint))->ShowWindow(TRUE);
		(GetDlgItem(IDC_PROGRESS1))->ShowWindow(TRUE);

		CFont font;
		font.CreatePointFont(200, _T("Arial"));
		GetDlgItem(IDC_nHint)->SetFont(&font);
		if (room3_stage == 0) {
			CClientDC dc(this);
			CBitmap bitmap;
			bitmap.LoadBitmap(IDB_room3_glassbook);
			BITMAP bmpinfo;
			bitmap.GetBitmap(&bmpinfo);

			CDC dcmem;
			dcmem.CreateCompatibleDC(&dc);
			dcmem.SelectObject(&bitmap);

			dc.BitBlt(0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, &dcmem, 0, 0, SRCCOPY);
		}
		else if (room3_stage == 1) {
			CClientDC dc(this);
			CBitmap bitmap;
			bitmap.LoadBitmap(IDB_room3_book);
			BITMAP bmpinfo;
			bitmap.GetBitmap(&bmpinfo);

			CDC dcmem;
			dcmem.CreateCompatibleDC(&dc);
			dcmem.SelectObject(&bitmap);

			dc.BitBlt(0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, &dcmem, 0, 0, SRCCOPY);
		}
	}
	else if (room3_clear == TRUE) {
		CClientDC dc(this);
		CBitmap bitmap;
		bitmap.LoadBitmap(IDB_room3_clear);
		BITMAP bmpinfo;
		bitmap.GetBitmap(&bmpinfo);

		CDC dcmem;
		dcmem.CreateCompatibleDC(&dc);
		dcmem.SelectObject(&bitmap);

		dc.BitBlt(0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, &dcmem, 0, 0, SRCCOPY);

	}
	
}


void CbtnimageView::OnLButtonDown(UINT nFlags, CPoint point)
{
	bCheck_Lbutton = TRUE;
	//다음 신으로 넘기기
	if ((bScene_Done == TRUE) && (iStart_SceneNumber < iStart_SceneMax))
	{
		iStart_SceneNumber++;
		Invalidate();
	}
	if (room1 == TRUE) {
		CClientDC dc(this);
		CRgn rgn_picture, rgn_box, rgn_key, rgn_door, rgn_bed, rgn_pillow,
			rgn_light, rgn_paper, rgn_ground,rgn_other;

		rgn_picture.CreateRectRgn(166, 84, 307, 192);
		rgn_box.CreateRectRgn(204, 114, 283, 165);
		rgn_key.CreateRectRgn(230, 146, 260, 164);
		rgn_door.CreateRectRgn(591, 81, 659, 295);
		rgn_bed.CreateRectRgn(365, 325, 665, 350);
		rgn_pillow.CreateRectRgn(135, 259, 258, 297);
		rgn_light.CreateRectRgn(470, 175, 520, 200);
		rgn_paper.CreateRectRgn(492, 272, 521, 292);
		rgn_ground.CreateRectRgn(10, 406, 293, 459);
		rgn_other.CreateRectRgn(0,0,728,475);

		if (room1_stage == 1) {
			if (rgn_picture.PtInRegion(point)) {
				room1_stage = 2;
				Call_Dialog(_T("액자를 떼어내자, 금고같은것이 보여."), 170);
				Invalidate();
			}
			else if (rgn_door.PtInRegion(point))
				Call_Dialog(_T("잠겨있는것 같아."), 170);
			else if (rgn_bed.PtInRegion(point))
				Call_Dialog(_T("침대 매트리스 사이에 뭔가 있지 않을까?"), 170);
			else if (rgn_pillow.PtInRegion(point))
				Call_Dialog(_T("푹신푹신한 베개야."), 170);
			else if (rgn_light.PtInRegion(point))
				Call_Dialog(_T("밝은 백열등 전구야."), 170);
			else if (rgn_ground.PtInRegion(point))
				Call_Dialog(_T("소리가 조금 다른것같아. 아래 무언가 있으려나?"), 170);
			else if(rgn_other.PtInRegion(point))
				Call_Dialog(_T("여긴 아무것도 없는 것 같아. 다른곳을 찾아보자."), 170);
		}
		else if (room1_stage == 2) {
			CRoom1_2 dlg;
			if (rgn_box.PtInRegion(point)) {
				dlg.DoModal();
				if (dlg.box == TRUE) {
					room1_stage = 3;
					Invalidate();
				}
			}
			else if (rgn_door.PtInRegion(point))
				Call_Dialog(_T("잠겨있는것 같아."), 170);
			else if (rgn_bed.PtInRegion(point))
				Call_Dialog(_T("침대 매트리스 사이에 뭔가 있지 않을까?"), 170);
			else if (rgn_pillow.PtInRegion(point))
				Call_Dialog(_T("푹신푹신한 베개야."), 170);
			else if (rgn_light.PtInRegion(point))
				Call_Dialog(_T("밝은 백열등 전구야."), 170);
			else if (rgn_ground.PtInRegion(point))
				Call_Dialog(_T("소리가 조금 다른것같아. 아래 무언가 있으려나?"), 170);
			else if (rgn_other.PtInRegion(point))
				Call_Dialog(_T("여긴 아무것도 없는 것 같아. 다른곳을 찾아보자."), 170);
		}
		else if (room1_stage == 3) {
			if (rgn_key.PtInRegion(point)) {
				int count = m_item.GetCount();
				m_item.SetCurSel(count - 1);
				m_item.AddString(_T("열쇠"));
				Call_Dialog(_T("'열쇠'를 발견했어. 어디에 쓰이는거지?"), 170);
				room1_stage = 4;
				Invalidate();
			}
			else if (rgn_door.PtInRegion(point))
				Call_Dialog(_T("잠겨있는것 같아."), 170);
			else if (rgn_bed.PtInRegion(point))
				Call_Dialog(_T("침대 매트리스 사이에 뭔가 있지 않을까?"), 170);
			else if (rgn_pillow.PtInRegion(point))
				Call_Dialog(_T("푹신푹신한 베개야."), 170);
			else if (rgn_light.PtInRegion(point))
				Call_Dialog(_T("밝은 백열등 전구야."), 170);
			else if (rgn_ground.PtInRegion(point))
				Call_Dialog(_T("소리가 조금 다른것같아. 아래 무언가 있으려나?"), 170);
			else if (rgn_other.PtInRegion(point))
				Call_Dialog(_T("여긴 아무것도 없는 것 같아. 다른곳을 찾아보자."), 170);
		}
		else if (room1_stage == 4) {
			int nIndex = m_item.GetCurSel();
			m_item.GetText(nIndex, str);
			if (rgn_door.PtInRegion(point) && str == _T("열쇠")) {
				room1_stage = 5;
				Invalidate();
				Call_Dialog(_T("벽장안 문이 열렸어."), 170);
				int count = m_item.GetCount();
				m_item.SetCurSel(count - 1);
				m_item.AddString(_T("긴 막대기"));
				Call_Dialog(_T("긴 막대기를 발견했다. 어디에 쓰일 물건이지?"), 170);
			}
			else if (rgn_door.PtInRegion(point))
				Call_Dialog(_T("잠긴 것 같아. 무언가로 열 수 있지않을까?"), 170);
			else if (rgn_bed.PtInRegion(point))
				Call_Dialog(_T("침대 매트리스 사이에 뭔가 있지 않을까?"), 170);
			else if (rgn_pillow.PtInRegion(point))
				Call_Dialog(_T("푹신푹신한 베개야."), 170);
			else if (rgn_light.PtInRegion(point))
				Call_Dialog(_T("밝은 백열등 전구야."), 170);
			else if (rgn_ground.PtInRegion(point))
				Call_Dialog(_T("소리가 조금 다른것같아. 아래 무언가 있으려나?"), 170);
			else if (rgn_other.PtInRegion(point))
				Call_Dialog(_T("여긴 아무것도 없는 것 같아. 다른곳을 찾아보자."), 170);
		}
		else if (room1_stage == 5) {
			int nIndex = m_item.GetCurSel();
			m_item.GetText(nIndex, str);
			if (rgn_bed.PtInRegion(point) && str == _T("긴 막대기")) {
				int count = m_item.GetCount();
				m_item.SetCurSel(count - 1);
				m_item.AddString(_T("커터칼"));
				Call_Dialog(_T("매트리스 사이에서 '커터칼'을 주웠다."), 170);
				Call_Dialog(_T("이게 왜 여기에 있지...?"), 170);
				room1_stage = 6;
				Invalidate();
			}
			else if (rgn_bed.PtInRegion(point))
			{
				Call_Dialog(_T("깊숙히 뭔가 있는 것 같아."), 170);
				Call_Dialog(_T("꺼내고 싶은데 손이 닿지 않아..."), 170);

			}
			else if (rgn_pillow.PtInRegion(point))
				Call_Dialog(_T("푹신푹신한 베개야."), 170);
			else if (rgn_light.PtInRegion(point))
				Call_Dialog(_T("밝은 백열등 전구야."), 170);
			else if (rgn_ground.PtInRegion(point))
				Call_Dialog(_T("소리가 조금 다른것같아. 아래 무언가 있으려나?"), 170);
			else if (rgn_other.PtInRegion(point))
				Call_Dialog(_T("여긴 아무것도 없는 것 같아. 다른곳을 찾아보자."), 170);
		}
		else if (room1_stage == 6) {
			int nIndex = m_item.GetCurSel();
			m_item.GetText(nIndex, str);
			if (rgn_pillow.PtInRegion(point)) {
				if (str == _T("커터칼")) {
					int count = m_item.GetCount();
					m_item.SetCurSel(count - 1);
					m_item.AddString(_T("작은 망치"));
					Call_Dialog(_T("베개 안에서 '작은 망치'를 발견했다."), 170);
					Call_Dialog(_T("뭔가를 부시고 싶은걸."), 170);
					room1_stage = 7;
					Invalidate();
				}
				else
				{
					Call_Dialog(_T("푹신하다."), 170);
					Call_Dialog(_T("안에 뭔가가 들어있을까?"), 170);
				}
			}
			else if (rgn_ground.PtInRegion(point))
				Call_Dialog(_T("소리가 조금 다른것같아. 아래 무언가 있으려나?"), 170);
			else if (rgn_other.PtInRegion(point))
				Call_Dialog(_T("여긴 아무것도 없는 것 같아. 다른곳을 찾아보자."), 170);
		}
		else if (room1_stage == 7 && rgn_light.PtInRegion(point)) {
			int nIndex = m_item.GetCurSel();
			m_item.GetText(nIndex, str);
			if (rgn_light.PtInRegion(point)) {
				if (str == _T("작은 망치")) {
					room1_stage = 8;
					Invalidate();
					Call_Dialog(_T("전등을 부셨다. 어두워서 잘 보이지 않아."), 170);
				}
				else
					Call_Dialog(_T("너무 뜨거워서 손으로 만질 수 없어."), 170);
			}
			else if (rgn_ground.PtInRegion(point))
				Call_Dialog(_T("소리가 조금 다른것같아. 아래 무언가 있으려나?"), 170);
			else if (rgn_other.PtInRegion(point))
				Call_Dialog(_T("여긴 아무것도 없는 것 같다. 다른곳을 찾아보자."), 170);
		}
		else if (room1_stage == 8) {
			if (rgn_paper.PtInRegion(point)) {
				room1_stage = 9;
				int count = m_item.GetCount();
				m_item.SetCurSel(count - 1);
				m_item.AddString(_T("쪽지"));
				Call_Dialog(_T("'쪽지'를 주웠다. 어떤 내용이 들어있을까?"), 170);
				Invalidate();
			}
			else if (rgn_ground.PtInRegion(point))
				Call_Dialog(_T("소리가 조금 다른것같아. 아래 무언가 있으려나?"), 170);
			else if (rgn_other.PtInRegion(point))
				Call_Dialog(_T("여긴 아무것도 없는 것 같아. 다른곳을 찾아보자."), 170);
		}
		else if (room1_stage == 9 && rgn_ground.PtInRegion(point)) {
			CRoom1_9 dlg;
			dlg.DoModal();
			if (dlg.door == TRUE) {
				room1_stage = 10;
				Invalidate();
			}
		}
		else if (room1_stage == 10 && rgn_ground.PtInRegion(point)) {
			room1 = FALSE;
			room1_clear = TRUE;
			Invalidate();
			
		}
	}

	else if (room2 == TRUE) {
		CClientDC dc(this);
		CString str;
		int count;
		CRgn rgn_light, rgn_violin, rgn_pendulum, rgn_bookdoor,
			rgn_keyboard, rgn_desk, rgn_key, rgn_picture,rgn_other;

		//rgn_light.CreateEllipticRgn(458, 14, 520, 36);
		rgn_violin.CreateEllipticRgn(107, 258, 193, 281);
		rgn_pendulum.CreateEllipticRgn(683, 220, 705, 240);
		rgn_bookdoor.CreateEllipticRgn(207, 87, 283, 350);
		rgn_keyboard.CreateRectRgn(427, 248, 513, 290);
		rgn_desk.CreateRectRgn(566, 352, 578, 372);
		rgn_key.CreateEllipticRgn(505, 327, 533, 348);
		rgn_picture.CreateRectRgn(466, 189, 496, 209);
		rgn_other.CreateRectRgn(0, 0, 728, 475);


		if (room2_stage == 1) {
			if (rgn_violin.PtInRegion(point)) {
				CRoom2_1 dlg;
				dlg.DoModal();
				if (dlg.room2_1 == TRUE)
					room2_stage = 2;
			}
			else if (rgn_pendulum.PtInRegion(point))
				Call_Dialog(_T("시계추 밑에 무엇인가 있는 것 같아."), 170);
			else if (rgn_bookdoor.PtInRegion(point))
				Call_Dialog(_T("게임에선 이 책장같은곳 뒤에 공간이 있던데."), 170);
			else if (rgn_keyboard.PtInRegion(point))
				Call_Dialog(_T("오래된 타자기야. 한번 쳐보고 싶어."), 170);
			else if (rgn_desk.PtInRegion(point))
				Call_Dialog(_T("서랍은 잠겨있어."), 170);
			else if (rgn_picture.PtInRegion(point))
				Call_Dialog(_T("액자에 뭐라 적혀있는거 같은데.. 이따가 다시 보자"), 170);
			else if (rgn_other.PtInRegion(point))
				Call_Dialog(_T("여긴 아무것도 없는 것 같다. 다른곳을 찾아보자."), 170);
		}
		else if (room2_stage == 2) {
			if (rgn_pendulum.PtInRegion(point)) {
				Call_Dialog(_T("어릴때 많이 하던 틀린그림 찾기인가?"), 170);
				Call_Dialog(_T("귀찮으니까 3군데만 찾아야지."), 170);
				CRoom2_2 dlg;
				dlg.DoModal();
				if (dlg.room2_2 == TRUE) {
					int count = m_item.GetCount();
					m_item.SetCurSel(count - 1);
					m_item.AddString(_T("종이"));
					Call_Dialog(_T("시계추 밑에서 '종이'를 발견했다."), 170);
					room2_stage = 3;
				}
			}
			else if (rgn_keyboard.PtInRegion(point))
				Call_Dialog(_T("오래된 타자기야. 한번 쳐보고 싶어."), 170);
			else if (rgn_desk.PtInRegion(point))
				Call_Dialog(_T("서랍은 잠겨있어."), 170);
			else if (rgn_picture.PtInRegion(point))
				Call_Dialog(_T("액자에 뭐라 적혀있는거 같은데.. 이따가 다시 보자"), 170);
			else if (rgn_bookdoor.PtInRegion(point))
				Call_Dialog(_T("게임에선 이 책장같은곳 뒤에 공간이 있던데.."), 170);
			else if (rgn_other.PtInRegion(point))
				Call_Dialog(_T("여긴 아무것도 없는 것 같다. 다른곳을 찾아보자."), 170);
		}
		else if (room2_stage == 3) {
			if (rgn_keyboard.PtInRegion(point)) {
				int nIndex = m_item.GetCurSel();
				m_item.GetText(nIndex, str);
				if (str == _T("종이")) {
					CRoom2_3 dlg;
					dlg.DoModal();
					if (dlg.room2_3 == TRUE) {
						int count = m_item.GetCount();
						m_item.SetCurSel(count - 1);
						m_item.AddString(_T("뭔가 쓰여진종이"));
						Call_Dialog(_T("타자기 치는 느낌이 너무나 좋은걸."), 170);
						Call_Dialog(_T("'뭔가 쓰여진 종이'를 획득했다."), 170);
						room2_stage = 4;
					}
				}
				else {
					Call_Dialog(_T("시험지를 만드려면 뭐가 필요하지??"), 170);
				}
			}
			else if (rgn_desk.PtInRegion(point))
				Call_Dialog(_T("서랍은 잠겨있어."), 170);
			else if (rgn_picture.PtInRegion(point))
				Call_Dialog(_T("액자에 뭐라 적혀있는거 같은데.. 이따가 다시 보자"), 170);
			else if (rgn_bookdoor.PtInRegion(point))
				Call_Dialog(_T("게임에선 이 책장같은곳 뒤에 공간이 있던데.."), 170);
			else if (rgn_other.PtInRegion(point))
				Call_Dialog(_T("여긴 아무것도 없는 것 같다. 다른곳을 찾아보자."), 170);
		}
		else if (room2_stage == 4) {
			if (rgn_desk.PtInRegion(point)) {   //서랍 열기   
				CRoom2_3to4 dlg;
				dlg.DoModal();
				if (dlg.room2_3to4 == TRUE) {
					room2_stage = 5;
					Invalidate();
				}
			}
			else if (rgn_picture.PtInRegion(point))
				Call_Dialog(_T("액자에 뭐라 적혀있는거 같은데.. 이따가 다시 보자"), 170);
			else if (rgn_bookdoor.PtInRegion(point))
				Call_Dialog(_T("게임에선 이 책장같은곳 뒤에 공간이 있던데.."), 170);
			else if (rgn_other.PtInRegion(point))
				Call_Dialog(_T("여긴 아무것도 없는 것 같다. 다른곳을 찾아보자."), 170);

		}
		else if (room2_stage == 5) {
			if (rgn_key.PtInRegion(point)) {   //키발견
				count = m_item.GetCount();
				m_item.SetCurSel(count - 1);
				m_item.AddString(_T("masterkey"));
				Call_Dialog(_T("서랍에서 'masterkey'를 발견했다ㅡ"), 170);
				room2_stage = 6;
				Invalidate();
			}
			else if (rgn_picture.PtInRegion(point))
				Call_Dialog(_T("액자에 뭐라 적혀있는거 같은데.. 이따가 다시 보자"), 170);
			else if (rgn_bookdoor.PtInRegion(point))
				Call_Dialog(_T("게임에선 이 책장같은곳 뒤에 공간이 있던데.."), 170);
			else if (rgn_other.PtInRegion(point))
				Call_Dialog(_T("여긴 아무것도 없는 것 같다. 다른곳을 찾아보자."), 170);
		}
		else if (room2_stage == 6 ) {
			if (rgn_picture.PtInRegion(point)) {
				CRoom2_5 dlg;
				dlg.DoModal();
				if (dlg.room2_5 == TRUE)
					room2_stage = 7;
			}
			else if (rgn_bookdoor.PtInRegion(point))
				Call_Dialog(_T("게임에선 이 책장같은곳 뒤에 공간이 있던데.."), 170);
			else if (rgn_other.PtInRegion(point))
				Call_Dialog(_T("여긴 아무것도 없는 것 같다. 다른곳을 찾아보자."), 170);
		}
		else if (room2_stage == 7 ) {
			if (rgn_bookdoor.PtInRegion(point)) {
				room2_stage = 8;
				Invalidate();
				Call_Dialog(_T("어?? 새로운 공간으로 이어지는 문이야."), 170);
				Call_Dialog(_T("어쩌면 여기 있을지도 몰라"), 170);
			}
			else if (rgn_other.PtInRegion(point))
				Call_Dialog(_T("여긴 아무것도 없는 것 같다. 다른곳을 찾아보자."), 170);
		}
		else if (room2_stage == 8 && rgn_bookdoor.PtInRegion(point)) {
			room2 = FALSE;
			room2_clear = TRUE;
			Invalidate();
		}
	}
	else if (room3 == TRUE) {
		CClientDC dc(this);
		CRgn rgn_glassbook,rgn_book,rgn_other;

		rgn_glassbook.CreateRectRgn(276, 103, 385, 220);
		rgn_book.CreateRectRgn(301,140,361,219);
		rgn_other.CreateRectRgn(0, 0, 728, 475);

		if (room3_stage == 0  ) {
			if(rgn_glassbook.PtInRegion(point)){
				int nIndex = m_item.GetCurSel();
				m_item.GetText(nIndex, str);
				if (str == _T("masterkey")) {
					room3_stage = 1;
					Invalidate();
					Call_Dialog(_T("좋아. 유리를 열었어."), 170);
				}
				else {
					Call_Dialog(_T("열쇠가 필요한것 같은데?"), 170);
				}
			}
			else if (rgn_other.PtInRegion(point))
				Call_Dialog(_T("여긴 아무것도 없는 것 같다. 다른곳을 찾아보자."), 170);
		}
		else if (room3_stage == 1 ) {
			if (rgn_book.PtInRegion(point)) {
				room3 = FALSE;
				room3_clear = TRUE;
				Invalidate();
				(GetDlgItem(IDC_LIST1))->ShowWindow(FALSE);
				(GetDlgItem(IDC_HINT))->ShowWindow(FALSE);
				(GetDlgItem(IDC_nHint))->ShowWindow(FALSE);
				(GetDlgItem(IDC_PROGRESS1))->ShowWindow(FALSE);
				KillTimer(100);
				Call_Dialog(_T("드디어 시험지를 손에 넣었어."), 170);
				Call_Dialog(_T("이거면 기말고사 100점 맞을 수 있겠다.ㅎ"), 170);
				Call_Dialog(_T("어서 교수님의 집에서 빠져나가자."), 170);
				Call_Dialog(_T("그런데 웬 편지가 있네..?"), 170);
				CClientDC dc(this);
				CRect rect;
				GetClientRect(&rect);
				dc.SelectStockObject(BLACK_BRUSH);
				dc.SetBkColor(TRANSPARENT);
				dc.Rectangle(&rect);
				Call_Dialog(_T("..."), 170);
				Call_Dialog(_T("지금쯤 시험지를 손에 넣었을 제자에게.."), 170);
				Call_Dialog(_T("자네 왜 그러고 있는가?"), 170);
				Print_Image(IDB_Score, 250, 50);
				Call_Dialog(_T("혹시 중간고사를 잘 보지 못했나?"), 170);
				Print_Image(IDB_MAPO, 200, 50);
				Call_Dialog(_T("그래서 인생을 포기할 생각까지 했었나??"), 170);
				dc.Rectangle(&rect);
				Call_Dialog(_T("그러지 말게나."), 170);
				Call_Dialog(_T("자네 혹시 그거 아는가..?"), 170);
				Call_Dialog(_T("시험은 잘보는 사람이 있으려면 말이지,"), 170);
				Call_Dialog(_T("못보는 사람도 당연히 존재하는 법이라네.."), 170);
				Call_Dialog(_T("사람이 어떻게 살면서 매번 시험을 잘보겠나?"), 170);
				Call_Dialog(_T("이 한번의 작은 시험으로 길고 긴 인생을 쉽게 포기하지 말게나.."), 170);
				Call_Dialog(_T("그럼 기말고사 성적을 기대하겠네!"), 170);
				Call_Dialog(_T("'...'"), 170);
				Call_Dialog(_T("'그래 맞아...'"), 170);
				Call_Dialog(_T("'기말고사 한번 잘볼려고 교수님 집을 털다니.. 바보같긴..'"), 170);
				Call_Dialog(_T("'집가서 빨리 공부해야겠다.'"), 170);
				Call_Dialog(_T("'기말고사가 얼마 남지 않았어!'"), 170);
				Print_Image(IDB_ENDING, 0, 0);
			}
			else if (rgn_other.PtInRegion(point))
				Call_Dialog(_T("시간이 얼마없어. 시험지 가지고 나가자."), 170);
		}
	}

}


void CbtnimageView::OnBnClickedHint()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	static int lastHint = 0;
	if (room1 == TRUE) {
		if (nHint < 3 || (nHint == 3 && lastHint == room1_stage)) {
			if (lastHint != room1_stage && nHint != 3)
				nHint++;
			CFont font;
			font.CreatePointFont(200, _T("Arial"));
			GetDlgItem(IDC_nHint)->SetFont(&font);
			str.Format(_T("%d"), 3-nHint);
			m_nHint.SetWindowText(str);
			if (room1_stage == 1)
				Call_Dialog(_T("벽에 걸린건 뭐지?"), 170);
			else if (room1_stage == 2)
				Call_Dialog(_T("저건 금고인가?"), 170);
			else if (room1_stage == 3)
				Call_Dialog(_T("열쇠가 있는것 같아."), 170);
			else if (room1_stage == 4)
				Call_Dialog(_T("열쇠를 써보자."), 170);
			else if (room1_stage == 5)
				Call_Dialog(_T("긴 막대기로 깊숙히 있는 뭔가를 꺼낼 수 있지 않을까?"), 170);
			else if (room1_stage == 6)
				Call_Dialog(_T("커터칼로 찢어볼까?"), 170);
			else if (room1_stage == 7)
				Call_Dialog(_T("작은 망치로 뭘 깰 수 있지?"), 170);
			else if (room1_stage == 8)
				Call_Dialog(_T("쪽지가 떨어졌어."), 170);
			else if (room1_stage == 9)
				Call_Dialog(_T("쪽지 문제를 풀어야 할텐데.."), 170);
			lastHint = room1_stage;
		}
		else
			Call_Dialog(_T("힌트는 더이상 없다."), 170);
	}

	else if (room2 == TRUE) {
		if (nHint < 3 || (nHint == 3 && lastHint == room2_stage)) {
			if (lastHint != room2_stage && nHint != 3)
				nHint++;
			CFont font;
			font.CreatePointFont(200, _T("Arial"));
			GetDlgItem(IDC_nHint)->SetFont(&font);
			str.Format(_T("%d"), 3 - nHint);
			m_nHint.SetWindowText(str);
			if (room2_stage == 0)	//전등 힌트
				Call_Dialog(_T("너무 어둡다..아이템을 쓸까?"), 170);
			else if (room2_stage == 1)	//바이올린 힌트
				Call_Dialog(_T("아! 교수님 취미가 바이올린이랬는데.."), 170);
			else if (room2_stage == 2)	//시계추
				Call_Dialog(_T("바로 전 문제가 뭐에 관한 문제였지?"), 170);
			else if (room2_stage == 3)	//타자기
				Call_Dialog(_T("시험문제를 뭘로 내셨을까? 종이는 있는데.."), 170);
			else if (room2_stage == 4)	//책상
				Call_Dialog(_T("종이에 뭐가 써져있는지 볼까??"), 170);
			else if (room2_stage == 5)	//키
				Call_Dialog(_T("키가 있잖아? 일단 아이템에 넣어볼까?"), 170);
			else if (room2_stage == 6)	//액자
				Call_Dialog(_T("액자가 많은게 수상해..혹시 단서인가?"), 170);
			else if (room2_stage == 7)	//책장
				Call_Dialog(_T("힌트는 전단계에서 주어졌다."), 170);
			lastHint = room2_stage;
		}
		else
			Call_Dialog(_T("힌트는 더이상 없다."), 170);
	}
	else if (room3 == TRUE) {
		if (nHint < 3 || (nHint == 3 && lastHint == room2_stage)) {
			if (lastHint != room2_stage && nHint != 3)
				nHint++;
			CFont font;
			font.CreatePointFont(200, _T("Arial"));
			GetDlgItem(IDC_nHint)->SetFont(&font);
			str.Format(_T("%d"), 3 - nHint);
			m_nHint.SetWindowText(str);
			if (room3_stage == 0)	//전등 힌트
				Call_Dialog(_T("유리속에 갇혀있는데..뭐로 열어야 하지?!"),170);
			lastHint = room3_stage;
		}
		else
			Call_Dialog(_T("힌트는 더이상 없다."), 170);
	}
}


void CbtnimageView::OnLbnDblclkList1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nIndex = m_item.GetCurSel();
	m_item.GetText(nIndex, str);
	if (room2 == TRUE && nIndex != LB_ERR && room2_stage == 0 && str == _T("light")) {
		room2_stage = 1;
		Invalidate();
		Call_Dialog(_T("이제야 방이 잘 보이는군."), 170);
	}
	else if (str == _T("쪽지")) {
		AfxMessageBox(_T("'I n D I T \\n I U D I I' -> 0 0 0 0 "));
		Invalidate();
	}
	else if (str == _T("뭔가 쓰여진종이")) {
		CRoom2_paper dlg;
		dlg.DoModal();
	}
}


void CbtnimageView::Wait(DWORD dwMillisecond)
{
	MSG msg;
	DWORD dwStart;
	dwStart = GetTickCount();

	while (GetTickCount() - dwStart < dwMillisecond)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}



int CbtnimageView::Call_Dialog(CString str_Caption, int height)
{
	
	CRect rect;
	GetClientRect(&rect);
	ClientToScreen(&rect);
	NomalDialog pDlg = new NomalDialog();
	pDlg.str_Caption = str_Caption;
	pDlg.view = this;
	pDlg.x_Pos = rect.left;
	pDlg.y_Pos = rect.bottom - height;
	pDlg.width = rect.Width();
	pDlg.height = height;
	int result = pDlg.DoModal();

	return result;
}


void CbtnimageView::OnBnClickedStart()
{
	bStart = TRUE;
	GetDlgItem(IDC_START)->ShowWindow(FALSE);
	GetDlgItem(IDC_START)->EnableWindow(FALSE);
}

void CbtnimageView::Print_Image(int Image_ID, int x_Pos, int y_Pos)
{
	CBitmap Myimage;
	CClientDC dc(this);
	Myimage.LoadBitmap(Image_ID);
	BITMAP bmpinfo;
	Myimage.GetBitmap(&bmpinfo);

	CDC dcmem;
	dcmem.CreateCompatibleDC(&dc);
	dcmem.SelectObject(&Myimage);
	dc.StretchBlt(x_Pos, y_Pos, bmpinfo.bmWidth, bmpinfo.bmHeight - 50, &dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY | DT_CENTER);

	dcmem.DeleteDC();
}

BOOL CbtnimageView::OnEraseBkgnd(CDC* pDC)
{
	if (room1 == TRUE)
	{
		CRect rect;
		GetClientRect(rect);
		pDC->FillSolidRect(rect, RGB(0,0, 0));

		return TRUE;
	}
}


HBRUSH CbtnimageView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	UINT nID = pWnd->GetDlgCtrlID();

	if (nID == IDC_nHint)
	{
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 255));
		hbr = ::CreateSolidBrush(RGB(0, 0, 0));
	}
	if (nID == IDC_LIST1)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SelectStockObject(NULL_BRUSH);
		pDC->SetBkColor(RGB(213, 213, 213));
		pDC->SetTextColor(RGB(0, 0, 0));
		hbr = ::CreateSolidBrush(RGB(213, 213, 213));


	}
	return hbr;
}


void CbtnimageView::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 100)
	{
		if (room1_clear != TRUE || room2_clear != TRUE){
			if (m_progress.GetPos() > 0)
			{
				if (m_progress.GetPos() > 20 && m_progress.GetPos() <= 50)
				{
					m_progress.SetState(PBST_PAUSED);
				}
				if (m_progress.GetPos() <= 20)
				{
					m_progress.SetState(PBST_ERROR);
				}
				m_progress.OffsetPos(-1);
			}
			else if(m_progress.GetPos()==0){

				KillTimer(nIDEvent);
				bProgress = FALSE;
				gameover = TRUE;
				CClientDC dc(this);
				CRect rect;
				GetClientRect(&rect);
				dc.SelectStockObject(BLACK_BRUSH);
				dc.Rectangle(&rect);
				dc.SetTextColor(RGB(255, 255, 255));

				room1 = FALSE;
				room1_clear = FALSE;
				room2 = FALSE;
				room2_clear = FALSE;
				room3 = FALSE;
				bStart, bFinish, bCheck_Lbutton, bScene_Done = FALSE;
				
				//OnClose();
				Invalidate();

			}
		}
	}
}


void CbtnimageView::Restart()
{
	bCover = TRUE;
	GetDlgItem(IDC_START)->ShowWindow(TRUE);
	GetDlgItem(IDC_START)->EnableWindow(TRUE);
	room1 = FALSE;
	room1_clear = FALSE;
	room2 = FALSE;
	room2_clear = FALSE;
	room3 = FALSE;
	Caption1 = TRUE;
	Caption2 = TRUE;
	bProgress = FALSE;
	gameover = FALSE;
	bStart, bFinish, bCheck_Lbutton, bScene_Done = FALSE;
	Invalidate();
	
}

