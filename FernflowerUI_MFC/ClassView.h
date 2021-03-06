
#pragma once

#include "ViewTree.h"
#include "stdafx.h"

class CClassToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*)GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CClassView : public CDockablePane
{
public:
	CClassView();
	virtual ~CClassView();

	void AdjustLayout();
	void OnChangeVisualStyle();
	void SearchClass(CStringW Path,HTREEITEM hParent);
	void ShowClassView(const CStringW & Path);
	void ClearAll()
	{
		m_wndClassView.DeleteAllItems();
		m_mapItemRange.clear();
	}
	CViewTree * GetTreeView()
	{
		return &m_wndClassView;
	}

	std::map<HTREEITEM, CHARRANGE> m_mapItemRange;
//	std::map<HTREEITEM,std::map<CString, CHARRANGE>> m_mapScopeRange;
	std::map<HTREEITEM, std::pair<CString, CHARRANGE>> m_mapScopeRange;
	std::vector<CString> lstjavaFileName;
	std::map<CString, HTREEITEM> m_mapClassFile;

protected:
	CClassToolBar m_wndToolBar;
	CViewTree m_wndClassView;
	CStatic   m_wndStaticText;
	CFont     m_TextFont;
	std::map<int, int> m_mapSysImageId;
	int m_nCurrImageCount;
	CImageList m_ClassViewImages;
	UINT m_nCurrSort;

	void FillClassView();
	void ParseClasses(CString FilePath, HTREEITEM hParentItem);
	void ParseInnerClass(CString Content, HTREEITEM hParentItem, int nOffset,CString NameSpace);
	bool isspace(_In_ TCHAR Ch)
	{
		return (Ch == _T(' ')) || (Ch == _T('\r')) || (Ch == _T('\n')) || (Ch == _T('\t'));
	}

	//std::vector<CString> m_vecTypeName = { L"boolean" ,L"byte" ,L"char",L"double",L"int",L"long",L"short",L"void" };

	CStringW GetShortName(const CStringW & Str)
	{
		CStringW Result;
		for (int i = Str.GetLength(); i >= 0&&Str[i]!=L'\\'; i--)
		{
			CStringW Tmp(Str[i]);
			Result += Tmp;
		}
		Result.MakeReverse();
		return Result;
	}

	// ��д
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void ShowPane(BOOL bShow, BOOL bDelay, BOOL bActivate/* = TRUE*/);

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnClassAddMemberFunction();
	afx_msg void OnClassAddMemberVariable();
	afx_msg void OnClassDefinition();
	afx_msg void OnClassProperties();
	afx_msg void OnNewFolder();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg LRESULT OnChangeActiveTab(WPARAM, LPARAM);
	afx_msg void OnSort(UINT id);
	afx_msg void OnUpdateSort(CCmdUI* pCmdUI);

	DECLARE_MESSAGE_MAP()
};

