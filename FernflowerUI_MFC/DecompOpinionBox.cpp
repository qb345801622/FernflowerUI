// DecompOpinionBox.cpp: 实现文件
//

#include "stdafx.h"
#include "FernflowerUI_MFC.h"
#include "DecompOpinionBox.h"
#include "afxdialogex.h"
#include "CommonWrapper.h"


// DecompOpinionBox 对话框

IMPLEMENT_DYNAMIC(CDecompOpinionBox, CDialogEx)

CDecompOpinionBox::CDecompOpinionBox(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OPINIONBOX, pParent)
{

}

CDecompOpinionBox::~CDecompOpinionBox()
{
}

void CDecompOpinionBox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDecompOpinionBox, CDialogEx)
	ON_MESSAGE(WM_INITDIALOG, &CDecompOpinionBox::OnInitDialog)
END_MESSAGE_MAP()


// DecompOpinionBox 消息处理程序


afx_msg LRESULT CDecompOpinionBox::OnInitDialog(WPARAM wParam, LPARAM lParam)
{
	LRESULT bRet = HandleInitDialog(wParam, lParam);
	m_pTreeCtrl = static_cast<CTreeCtrl*>(GetDlgItem(IDC_TREEOPINIONS));
	m_pTreeCtrl->ModifyStyle(TVS_CHECKBOXES|TVS_HASBUTTONS, 0);
	m_pTreeCtrl->ModifyStyle(0, TVS_CHECKBOXES| TVS_HASBUTTONS);
	SetWindowTheme(m_pTreeCtrl->GetSafeHwnd(), _T("Explorer"), nullptr);
	if (m_Font.CreatePointFont(120, L"Microsoft YaHei"))
	{
		m_pTreeCtrl->SetFont(&m_Font);
	}
	for (auto it = theApp.m_DecompOpinion.OpinionMap.begin(); it != theApp.m_DecompOpinion.OpinionMap.end(); it++)
	{
		HTREEITEM hItem = m_pTreeCtrl->InsertItem(it->first);
		if (it->first==L"log")
		{
			m_pTreeCtrl->SetItemState(hItem, INDEXTOSTATEIMAGEMASK(0), TVIS_STATEIMAGEMASK);
			m_pTreeCtrl->SetItemState(hItem, TVIS_EXPANDPARTIAL, TVIS_EXPANDPARTIAL);
			/*TV_ITEM tvItem;
			ZeroMemory(&tvItem, sizeof(tvItem));
			tvItem.hItem = hItem;
			tvItem.mask = TVIF_CHILDREN;
			tvItem.cChildren = I_CHILDRENCALLBACK;
			m_pTreeCtrl->SetItem(&tvItem);*/
			m_pTreeCtrl->InsertItem(L"ERROR", hItem);
			m_pTreeCtrl->InsertItem(L"WARN", hItem);
			m_pTreeCtrl->InsertItem(L"INFO", hItem);
			m_pTreeCtrl->InsertItem(L"TRACE", hItem);
		}
	}
	return bRet;
}
