// FileView.cpp: 实现文件
//

#include "stdafx.h"
#include "FernflowerUI_MFC.h"
#include "FileView.h"
#include "CommonWrapper.h"


// CFileView

IMPLEMENT_DYNAMIC(CFileView, CDockablePane)

CFileView::CFileView()
{

}

CFileView::~CFileView()
{
}


BEGIN_MESSAGE_MAP(CFileView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()



// CFileView 消息处理程序



int CFileView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	/*CSubThread * SubThread = DYNAMIC_DOWNCAST(CSubThread, AfxBeginThread(RUNTIME_CLASS(CSubThread), 0, 0, CREATE_SUSPENDED));
	SubThread->pParentView = this;
	SubThread->m_bAutoDelete = true;
	SubThread->ResumeThread();
	auto WaitFor = [&]() {return SubThread->Created; };
	CommonWrapper::CWaitDlg Wait(AfxGetMainWnd(), WaitFor, 1, IsInChinese() ? L"正在初始化" : L"Initing", 20, IDD_WAITLAUNCH, true);
	Wait.DoModal();*/
	const DWORD dwTreeStyle = WS_CHILD | WS_VISIBLE | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS | TVS_FULLROWSELECT | TVS_TRACKSELECT;
	CRect rectDummy(0, 0, 0, 0);
	m_ShellTreeView.Create(dwTreeStyle, rectDummy, this, ID_SHELLTREE);
	m_ShellTreeView.SetExtendedStyle(0, TVS_EX_DOUBLEBUFFER);
	SetWindowTheme(m_ShellTreeView.m_hWnd, _T("Explorer"), nullptr);
	m_ShellTreeView.SetFlags(m_ShellTreeView.GetFlags() | SHCONTF_NONFOLDERS | SHCONTF_FASTITEMS);
	m_ShellTreeView.EnableShellContextMenu();
//	auto Running = [this]() {m_ShellTreeView.RunModalLoop(); };
//	std::thread Run(Running);
//	Run.detach();
	/*bool Created = false;
	auto WaitFor = [&]() {return Created; };
	auto SubThreadProc=[&,this]()->void {
		const DWORD dwTreeStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS;
		CRect rectDummy(0, 0, 0, 0);
		m_ShellTreeView.Create(dwTreeStyle, rectDummy, this, ID_SHELLTREE);
		Created = true;
		m_ShellTreeView.SetFlags(m_ShellTreeView.GetFlags() | SHCONTF_NONFOLDERS);
		m_ShellTreeView.EnableShellContextMenu();

		MSG msg;
		while (::GetMessage(&msg, m_ShellTreeView.GetSafeHwnd(), 0, 0))
		{
			if (msg.message == WM_NOTIFY)
			{
				LRESULT Result;
				m_ShellTreeView.OnWndMsg(msg.message, msg.wParam, msg.lParam, &Result);
			}
			else
			{
				::DispatchMessage(&msg);
			}
		}};
	std::thread SubThread=std::thread(SubThreadProc);
	SubThread.detach();
	CommonWrapper::CWaitDlg Wait(AfxGetMainWnd(), WaitFor, 1, L"正在创建文件视图");
	Wait.DoModal();*/

	return 0;
}


void CFileView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDockablePane::OnPaint()
	CRect rectTree;
	if (!::IsWindow(m_ShellTreeView.GetSafeHwnd()))
		return;
	m_ShellTreeView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}


void CFileView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	AdjustLayout();
}


void CFileView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	// TODO: 在此处添加消息处理程序代码
	m_ShellTreeView.SetFocus();
}


void CFileView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	if (!::IsWindow(m_ShellTreeView.GetSafeHwnd()))
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);
	
	::SetWindowPos(m_ShellTreeView.GetSafeHwnd(), 0, rectClient.left + 1, rectClient.top + 1, rectClient.Width() - 2, rectClient.Height() - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

void CFileView::ShowPane(BOOL bShow, BOOL bDelay, BOOL bActivate)
{
	if (bShow)
	{
		//m_ShellTreeView.ShowWindow(SW_SHOW);
		//m_ShellTreeView.m_ShellTreeView.ShowWindow(SW_SHOW);
	}
	else
	{
		//m_ShellTreeView.ShowWindow(SW_HIDE);
		//m_ShellTreeView.m_ShellTreeView.ShowWindow(SW_HIDE);
	}
	CDockablePane::ShowPane(bShow, bDelay, bActivate);
}

IMPLEMENT_DYNCREATE(CSubThread, CWinThread)

CSubThread::CSubThread() :CWinThread(), Created(false)
{
}



CSubThread::~CSubThread()
{
}

CSubThread::CSubThread(AFX_THREADPROC pfnThreadProc, LPVOID pParam) :CWinThread(pfnThreadProc, pParam)
{
}


BOOL CSubThread::InitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类
	CWinThread::InitInstance();

	//HookWindowCreate();
//	ASSERT(AttachThreadInput(m_nThreadID, theApp.m_nThreadID, TRUE));
	const DWORD dwTreeStyle = WS_CHILD | WS_VISIBLE | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS | TVS_FULLROWSELECT | TVS_TRACKSELECT;
	CRect rectDummy(0, 0, 0, 0);
	//pParentView->m_ShellTreeView.Create(dwTreeStyle, rectDummy, CWnd::FromHandle(pParentView->GetSafeHwnd()), ID_SHELLTREE);
	//pParentView->m_ShellTreeView.SetFlags(pParentView->m_ShellTreeView.GetFlags() | SHCONTF_NONFOLDERS);
	//pParentView->m_ShellTreeView.EnableShellContextMenu();
	//pParentView->m_ShellTreeView.CreateEx(WS_EX_NOPARENTNOTIFY | WS_EX_TOOLWINDOW, nullptr, nullptr, WS_POPUP|MFS_4THICKFRAME, rectDummy, CWnd::FromHandle(pParentView->GetSafeHwnd()));
	pParentView->m_ShellTreeView.ModifyStyle(WS_CAPTION | WS_BORDER, 0);
	pParentView->m_ShellTreeView.ModifyStyleEx(WS_EX_CLIENTEDGE, 0);
	pParentView->m_ShellTreeView.EnableWindow();
	//pParentView->m_ShellTreeView.m_ShellTreeView.EnableWindow();
	//pParentView->m_ShellTreeView.SetOwner(pParentView);
	//UnHookWindowCreate();
	Created = true;

	return TRUE;
}

void CSubThread::HookWindowCreate()
{
	//m_CreationHook = ::SetWindowsHookEx(WH_CBT, _AfxCbtFilterHook, nullptr, ::GetCurrentThreadId());
	if (m_CreationHook==nullptr)
	{
		AfxThrowMemoryException();
	}
}

bool CSubThread::UnHookWindowCreate()
{
	return UnhookWindowsHookEx(m_CreationHook);
}


BEGIN_MESSAGE_MAP(CShellTreeFrame, CMiniFrameWnd)
	ON_WM_CREATE()
	ON_REGISTERED_MESSAGE(WM_SHELLTREE_SELPATH, &CShellTreeFrame::OnShelltreeSelpath)
	ON_WM_SIZE()
END_MESSAGE_MAP()


int CShellTreeFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMiniFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	const DWORD dwTreeStyle = WS_CHILD | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS | TVS_FULLROWSELECT | TVS_TRACKSELECT;
	CRect rectDummy(0, 0, 0, 0);
	VERIFY(m_ShellTreeView.Create(dwTreeStyle, rectDummy, this, ID_SHELLTREE));
	m_ShellTreeView.SetFlags(m_ShellTreeView.GetFlags() | SHCONTF_NONFOLDERS);
	m_ShellTreeView.EnableShellContextMenu();
	SetWindowTheme(m_ShellTreeView.m_hWnd, _T("Explorer"), nullptr);
	
	return 0;
}


afx_msg LRESULT CShellTreeFrame::OnShelltreeSelpath(WPARAM wParam, LPARAM lParam)
{
	return m_ShellTreeView.SelectPath(strPathToSelect);
}


void CShellTreeFrame::OnSize(UINT nType, int cx, int cy)
{
	CMiniFrameWnd::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CRect rect;
	GetClientRect(rect);
	m_ShellTreeView.SetWindowPos(nullptr, 0, 0, cx, cy, SWP_NOACTIVATE);
}


void CFileView::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDockablePane::OnShowWindow(bShow, nStatus);

	// TODO: 在此处添加消息处理程序代码
	if (bShow)
	{
		//m_ShellTreeView.ShowWindow(SW_SHOW);
		//m_ShellTreeView.m_ShellTreeView.ShowWindow(SW_SHOW);
	}
	else
	{
		//m_ShellTreeView.ShowWindow(SW_HIDE);
		//m_ShellTreeView.m_ShellTreeView.ShowWindow(SW_HIDE);
	}
}
