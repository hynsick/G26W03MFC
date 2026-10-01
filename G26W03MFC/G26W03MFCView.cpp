// G26W03MFCView.cpp: CG26W03MFCView 클래스의 구현
//

#include "pch.h"
#include "framework.h"

#ifndef SHARED_HANDLERS
#include "G26W03MFC.h"
#endif

#include "G26W03MFCDoc.h"
#include "G26W03MFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CG26W03MFCView

IMPLEMENT_DYNCREATE(CG26W03MFCView, CView)

// 메시지 맵은 하나로 통합합니다.
BEGIN_MESSAGE_MAP(CG26W03MFCView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	// 마우스 메시지 핸들러 등록
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

// CG26W03MFCView 생성/소멸
CG26W03MFCView::CG26W03MFCView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
}

CG26W03MFCView::~CG26W03MFCView()
{
}

BOOL CG26W03MFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

// CG26W03MFCView 그리기
void CG26W03MFCView::OnDraw(CDC* pDC)
{
	CG26W03MFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	//CPoint p = pDoc->GetPoint();
	//pDC->Ellipse(p.x - 30, p.y - 30, p.x + 30, p.y + 30);

	for (int i = 0; i < pDoc->GetPointsCount(); i++) {
		CPoint p = pDoc->GetPoint(i);
		// 고정값 30 대신 m_nRadius 사용
		pDC->Ellipse(p.x - m_nRadius, p.y - m_nRadius, p.x + m_nRadius, p.y + m_nRadius);
	}
}

// CG26W03MFCView 인쇄
BOOL CG26W03MFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CG26W03MFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CG26W03MFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

// CG26W03MFCView 진단
#ifdef _DEBUG
void CG26W03MFCView::AssertValid() const
{
	CView::AssertValid();
}

void CG26W03MFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CG26W03MFCDoc* CG26W03MFCView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CG26W03MFCDoc)));
	return (CG26W03MFCDoc*)m_pDocument;
}
#endif //_DEBUG

// CG26W03MFCView 메시지 처리기

// 마우스 왼쪽 버튼 클릭: 좌표 추가 및 화면 갱신
void CG26W03MFCView::OnLButtonDown(UINT nFlags, CPoint point)
{
	GetDocument()->AddPoint(point);
	Invalidate();

	CView::OnLButtonDown(nFlags, point);
}

// 마우스 오른쪽 버튼 클릭: 전체 삭제
void CG26W03MFCView::OnRButtonDown(UINT nFlags, CPoint point)
{
	GetDocument()->RemoveLast();
	Invalidate();

}
void CG26W03MFCView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (nFlags & MK_LBUTTON) {
		// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
		GetDocument()->AddPoint(point);
		Invalidate();
	}
	CView::OnMouseMove(nFlags, point);
}
// 휠 굴릴 때 크기 조절 함수
BOOL CG26W03MFCView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (zDelta > 0) {
		m_nRadius += 5; // 휠을 위로 굴리면 커짐
	}
	else {
		m_nRadius -= 5; // 휠을 아래로 굴리면 작아짐
	}

	// 최소 크기 제한
	if (m_nRadius < 5) m_nRadius = 5;

	Invalidate(); // 화면 갱신
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}