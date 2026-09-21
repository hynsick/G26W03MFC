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

	int radius = 20; // 원의 반지름 설정

	// Document에 저장된 모든 좌표를 순회하며 원 그리기
	for (const auto& pt : pDoc->m_points)
	{
		pDC->Ellipse(pt.x - radius, pt.y - radius, pt.x + radius, pt.y + radius);
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
	CG26W03MFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->AddPoint(point); // Document에 새로운 좌표 추가

	CView::OnLButtonDown(nFlags, point);
}

// 마우스 오른쪽 버튼 클릭: 전체 삭제
void CG26W03MFCView::OnRButtonDown(UINT nFlags, CPoint point)
{
	CG26W03MFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->ClearPoints(); // Document에 저장된 원 좌표 전체 삭제

	CView::OnRButtonDown(nFlags, point);
}