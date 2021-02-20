#pragma once


// CStoneSimulator 대화 상자

class CStoneSimulator : public CDialogEx
{
	DECLARE_DYNAMIC(CStoneSimulator)

public:
	CStoneSimulator(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CStoneSimulator();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STONE_SIMULATOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
