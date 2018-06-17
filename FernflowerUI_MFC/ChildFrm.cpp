
// ChildFrm.cpp: CChildFrame 类的实现
//

#include "stdafx.h"
#include "FernflowerUI_MFC.h"
#include "FernflowerUI_MFCView.h"
#include "CommonWrapper.h"
#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
	ON_WM_CREATE()
	ON_WM_MDIACTIVATE()
	ON_UPDATE_COMMAND_UI(ID_ENABLE_RECOVERY, &CChildFrame::OnUpdateEnableRecovery)
	ON_COMMAND(ID_ENABLE_RECOVERY, &CChildFrame::OnEnableRecovery)
	ON_WM_DESTROY()
	ON_COMMAND(ID_SELECT_FONT, &CChildFrame::OnSelectFont)
	ON_COMMAND(ID_QUICK_DECOMP, &CChildFrame::OnQuickDecomp)
	ON_UPDATE_COMMAND_UI(ID_QUICK_DECOMP, &CChildFrame::OnUpdateQuickDecomp)
	ON_COMMAND(ID_CLEAR_CACHE, &CChildFrame::OnClearCache)
	ON_UPDATE_COMMAND_UI(ID_CLEAR_CACHE, &CChildFrame::OnUpdateClearCache)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()

// CChildFrame 构造/析构

CChildFrame::CChildFrame()
{
	EnableActiveAccessibility();
	// TODO: 在此添加成员初始化代码
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	return CMDIChildWndEx::OnCreateClient(lpcs, pContext);
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或样式
	if (!CMDIChildWndEx::PreCreateWindow(cs))
		return FALSE;

	return TRUE;
}

// CChildFrame 诊断

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame 消息处理程序


void CChildFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
	// TODO: 在此添加专用代码和/或调用基类

	SetWindowText(m_strTitle);
	CommonWrapper::GetMainFrame()->SetWindowText(theApp.JarFilePath + L" => " + m_strTitle + _T(" - FernFlowerUI"));
	//Calling base class' method is useless.
	//CMDIChildWndEx::OnUpdateFrameTitle(bAddToTitle);
}


int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	return 0;
}


void CChildFrame::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd)
{
	CMDIChildWndEx::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);

	// TODO: 在此处添加消息处理程序代码
}


void CChildFrame::OnUpdateEnableRecovery(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(WaitForSingleObject(theApp.EnableRecovery,0)!=WAIT_TIMEOUT);
}


void CChildFrame::OnEnableRecovery()
{
	// TODO: 在此添加命令处理程序代码
	if (WaitForSingleObject(theApp.EnableRecovery, 0) != WAIT_TIMEOUT)
	{
		ResetEvent(theApp.EnableRecovery);
	}
	else
	{
		SetEvent(theApp.EnableRecovery);
	}
}


void CChildFrame::OnDestroy()
{
	for (auto it = CommonWrapper::GetMainFrame()->m_MDIChildWndMap.begin(); it != CommonWrapper::GetMainFrame()->m_MDIChildWndMap.end(); it++)
	{
		if (it->second==this)
		{
			CommonWrapper::GetMainFrame()->m_MDIChildWndMap.erase(it);
			break;
		}
	}
	CMDIChildWndEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}


void CChildFrame::OnSelectFont()
{
	// TODO: 在此添加命令处理程序代码
	CHARFORMAT2 Format;
	static_cast<CFernflowerUIMFCView*>(GetActiveView())->m_wndEdit.GetDefaultCharFormat(Format);
	CFontDialog FontSelect(Format);
	if (FontSelect.DoModal() == IDOK)
	{
		lstrcpy(Format.szFaceName, theApp.FontFaceName = FontSelect.GetFaceName());
		theApp.FontSize = (Format.yHeight = FontSelect.GetSize() * 2) / 20;
		static_cast<CFernflowerUIMFCView*>(GetActiveView())->m_wndEdit.SetSel(0, -1);
		static_cast<CFernflowerUIMFCView*>(GetActiveView())->m_wndEdit.SetDefaultCharFormat(Format);
		static_cast<CFernflowerUIMFCView*>(GetActiveView())->m_wndEdit.SetSelectionCharFormat(Format);
		static_cast<CFernflowerUIMFCView*>(GetActiveView())->m_wndEdit.m_wndLineBox.GetDefaultCharFormat(Format);
		lstrcpy(Format.szFaceName, theApp.FontFaceName = FontSelect.GetFaceName());
		theApp.FontSize = (Format.yHeight = FontSelect.GetSize() * 2) / 20;
		static_cast<CFernflowerUIMFCView*>(GetActiveView())->m_wndEdit.m_wndLineBox.SetSel(0, -1);
		static_cast<CFernflowerUIMFCView*>(GetActiveView())->m_wndEdit.m_wndLineBox.SetDefaultCharFormat(Format);
		CFernflowerUIMFCView * pView = static_cast<CFernflowerUIMFCView*>(GetActiveView());
		pView->FinishHighLight = false;
		AfxGetMainWnd()->BeginWaitCursor();
		CStringW Contact;
		static_cast<CFernflowerUIMFCView*>(GetActiveView())->m_wndEdit.GetWindowTextW(Contact);
		std::future<void> SetHighLight = std::async([&](const CStringW & Str, CWnd * MainWnd) {
			pView->SetViewText(Str);
		}, Contact, AfxGetMainWnd());
		CommonWrapper::CProgressBar Progress(AfxGetMainWnd(),
			[&]()->int {AfxGetMainWnd()->RestoreWaitCursor(); return pView->FinishHighLight; },
			5, IsInChinese()?L"正在设置字体":L"Setting the new font", 0, 77);
		Progress.DoModal();
		pView->FinishHighLight = false;
		AfxGetMainWnd()->EndWaitCursor();
	}
}


void CChildFrame::OnQuickDecomp()
{
	// TODO: 在此添加命令处理程序代码
	theApp.IsQuickDecomp = !theApp.IsQuickDecomp;
}


void CChildFrame::OnUpdateQuickDecomp(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(theApp.IsQuickDecomp);
}


void CChildFrame::OnClearCache()
{
	// TODO: 在此添加命令处理程序代码
	if (WaitForSingleObject(theApp.EvtIsToRmCache, 0) != WAIT_TIMEOUT)
	{
		ResetEvent(theApp.EvtIsToRmCache);
	}
	else
	{
		SetEvent(theApp.EvtIsToRmCache);
	}
	CommonWrapper::GetMainFrame()->OnViewCaptionBar();
}


void CChildFrame::OnUpdateClearCache(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(WaitForSingleObject(theApp.EvtIsToRmCache, 0) != WAIT_TIMEOUT);
}


void CChildFrame::OnDropFiles(HDROP DropFile)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int DropCount = DragQueryFile(DropFile, -1, NULL, 0);//取得被拖动文件的数目  
	if (DropCount == 1)
	{
		WCHAR wcStr[MAX_PATH];
		DragQueryFile(DropFile, 0, wcStr, MAX_PATH);//获得拖曳的第i个文件的文件名 
		theApp.DoDecomplie(wcStr);
	}
	else
	{
		WCHAR ThisPath[MAX_PATH];
		GetModuleFileName(nullptr, ThisPath, MAX_PATH);
		for (int i = 1; i < DropCount; i++)
		{
			WCHAR wcStr[MAX_PATH];
			DragQueryFile(DropFile, i, wcStr, MAX_PATH);//获得拖曳的第i个文件的文件名  
			ShellExecute(nullptr, L"open", ThisPath, wcStr, nullptr, SW_SHOW);
		}
		WCHAR wcStr[MAX_PATH];
		DragQueryFile(DropFile, 0, wcStr, MAX_PATH);//获得拖曳的第i个文件的文件名  
		theApp.DoDecomplie(wcStr);
	}
	DragFinish(DropFile);
}
