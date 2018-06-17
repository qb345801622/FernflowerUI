
// ChildFrm.h: CChildFrame 类的接口
//

#pragma once

class CChildFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// 特性
protected:
	CSplitterWndEx m_wndSplitter;
	CStringW       m_strTitle;
public:
	friend class CMainFrame;
	friend class CFernflowerUIMFCApp;
// 操作
public:

// 重写
	public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
	virtual void OnUpdateFrameTitle(BOOL bAddToTitle);
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);
	afx_msg void OnUpdateEnableRecovery(CCmdUI *pCmdUI);
	afx_msg void OnEnableRecovery();
	afx_msg void OnDestroy();
	afx_msg void OnSelectFont();
	afx_msg void OnQuickDecomp();
	afx_msg void OnUpdateQuickDecomp(CCmdUI *pCmdUI);
	afx_msg void OnClearCache();
	afx_msg void OnUpdateClearCache(CCmdUI *pCmdUI);
	afx_msg void OnDropFiles(HDROP hDropInfo);
};
