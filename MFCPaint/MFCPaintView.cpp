
// MFCPaintView.cpp: CMFCPaintView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCPaint.h"
#endif

#include "MFCPaintDoc.h"
#include "MFCPaintView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCPaintView

IMPLEMENT_DYNCREATE(CMFCPaintView, CView)

BEGIN_MESSAGE_MAP(CMFCPaintView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	ON_WM_CHAR()
	ON_WM_CLOSE()
	ON_COMMAND(ID_DRAW_LINE, &CMFCPaintView::OnDrawLine)
	ON_COMMAND(ID_DRAW_RECT, &CMFCPaintView::OnDrawRect)
	ON_COMMAND(ID_TEST_MENU, &CMFCPaintView::OnTest)
END_MESSAGE_MAP()

// CMFCPaintView 构造/析构

CMFCPaintView::CMFCPaintView() noexcept
{
	// TODO: 在此处添加构造代码
	m_bStatus = FALSE;
	m_start = { 0,0 };
	m_ptStop = { 0,0 };
	m_cur = { 0,0 };
}

CMFCPaintView::~CMFCPaintView()
{
}

BOOL CMFCPaintView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCPaintView 绘图

void CMFCPaintView::OnDraw(CDC* pDC)
{
	CMFCPaintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	CPen pen(PS_DASHDOT, 1, RGB(255, 0, 0));
	//当像素超过1的时候，线形会消失
	CPen* pOldPen = pDC->SelectObject(&pen);
	CBrush brush(RGB(255, 0, 0)), brush2(RGB(0, 255, 0));
	CBrush* pOldBrush = pDC->SelectObject(&brush);
	LOGPEN logpen;
	pOldPen->GetLogPen(&logpen);
	TRACE("style=%d color=%08X width=%d\r\n",
		logpen.lopnStyle, logpen.lopnColor, logpen.lopnWidth);
	//CPoint start = m_start, cur = m_cur;
	//start.y--; 
	if (m_bStatus) {
		pDC->FillRect(CRect(m_start, m_cur), NULL);
		/*cur.y--;
		pDC->MoveTo(m_start);
		pDC->LineTo(m_cur);

		pDC->MoveTo(start);
		pDC->LineTo(cur);*/
	}
	else {
		pDC->FillRect(CRect(m_start, m_ptStop), &brush2);
		//cur = m_stop;
		//cur.y--;
		//pDC->MoveTo(m_start);
		//pDC->LineTo(m_stop);

		//pDC->MoveTo(start);
		//pDC->LineTo(cur);
	}
	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
	CString sub = _T("");
	int y = 0;
	for (int i = 0; i < m_strText.GetLength(); i++)
	{
		if ((m_strText.GetAt(i) == '\n') || (m_strText.GetAt(i) == '\r')) {
			pDC->TextOut(0, y, sub);
			CSize sz = pDC->GetTextExtent(sub);
			sub.Empty();
			y += sz.cy + 2;
			continue;
		}
		sub += m_strText.GetAt(i);
	}
	if (sub.IsEmpty() == false)
		pDC->TextOut(0, y, sub);//TextOut只能显示单行文本
	//CPoint pt;
	CSize sz = pDC->GetTextExtent(sub);
	//pt.y = y;
	//pt.x = sz.cx + 2;
	//SetCaretPos(CPoint(sz.cx + 2, y));
	::SetCaretPos(sz.cx + 2, y);//设置光标位置
	//1 功能函数 2 仔细的去思考，如何使用
	//了解这些功能的限制和条件
}

void CMFCPaintView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCPaintView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCPaintView 诊断

#ifdef _DEBUG
void CMFCPaintView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCPaintView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCPaintDoc* CMFCPaintView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCPaintDoc)));
	return (CMFCPaintDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCPaintView 消息处理程序


void CMFCPaintView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_start = point;
	m_bStatus = TRUE;
	CView::OnLButtonDown(nFlags, point);
}


void CMFCPaintView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_ptStop = point;
	//CDC* pDC = GetDC();
	//1 什么是上下文
	//2 什么是设备上下文
	//pDC->MoveTo(m_start);
	//pDC->LineTo(m_stop);
	//ReleaseDC(pDC);
	InvalidateRect(NULL);//会触发OnDraw
	m_bStatus = FALSE;
	CView::OnLButtonUp(nFlags, point);
}


void CMFCPaintView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bStatus) {
		m_cur = point;
		InvalidateRect(NULL);//会触发OnDraw
		/*CDC* pDC = GetDC();
		pDC->MoveTo(m_start);
		pDC->LineTo(point);
		ReleaseDC(pDC);*/
	}
	CView::OnMouseMove(nFlags, point);
}


BOOL CMFCPaintView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类
	return CView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


int CMFCPaintView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	CClientDC dc(this);
	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);
	CreateSolidCaret(2, tm.tmHeight);
	ShowCaret();
	return 0;
}


void CMFCPaintView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	TRACE("%c\r\n", nChar);
	CClientDC dc(this);
	m_strText += (TCHAR)nChar;
	InvalidateRect(NULL);
	CView::OnChar(nChar, nRepCnt, nFlags);
}


void CMFCPaintView::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnClose();
}


void CMFCPaintView::OnDrawLine()
{
	TRACE("%s(%d):%s\r\n", __FILE__, __LINE__, __FUNCTION__);
}


void CMFCPaintView::OnDrawRect()
{
	// TODO: 在此添加命令处理程序代码
	TRACE("%s(%d):%s\r\n", __FILE__, __LINE__, __FUNCTION__);
}


void CMFCPaintView::OnTest()
{
	TRACE("%s(%d):%s\r\n", __FILE__, __LINE__, __FUNCTION__);
}
