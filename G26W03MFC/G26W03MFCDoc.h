
// G26W03MFCDoc.h: CG26W03MFCDoc 클래스의 인터페이스
//

#include <vector>
#pragma once


class CG26W03MFCDoc : public CDocument
{
public:
	// 원의 중심 좌표 목록을 저장할 컨테이너
	std::vector<CPoint> m_points;

	// 데이터 초기화/삭제 함수
	void ClearPoints() {
		m_points.clear();
		SetModifiedFlag(TRUE); // 문서가 변경되었음을 표시
		UpdateAllViews(NULL);  // 연결된 모든 View에 화면 갱신 요청
	}

	// 원 좌표 추가 함수
	void AddPoint(CPoint pt) {
		m_points.push_back(pt);
		SetModifiedFlag(TRUE);
		UpdateAllViews(NULL);
	}
protected:
	CPoint Point = CPoint(-100, -100);
public:
	CPoint GetPoint() { return Point; }
	void SetPoint(CPoint p) { Point = p; }
protected: // serialization에서만 만들어집니다.
	CG26W03MFCDoc() noexcept;
	DECLARE_DYNCREATE(CG26W03MFCDoc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CG26W03MFCDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
