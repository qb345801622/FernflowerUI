
// FernflowerUI_MFC.h: FernflowerUI_MFC 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号

#include "ChildFrm.h"
#include "FernflowerUI_MFCData.h"


// CFernflowerUIMFCApp:
// 有关此类的实现，请参阅 FernflowerUI_MFC.cpp
//

class CFernflowerUIMFCApp : public CWinAppEx
{
public:
	CFernflowerUIMFCApp();


	// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	// 实现
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	afx_msg void OnReportBugs();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnEditCopy();
	afx_msg void OnEditSelectAll();
public:
	afx_msg void OnStartupFileOpen();
	afx_msg void OpenFile();
	afx_msg bool OpenInnerFile(CString FilePath);

	inline CMultiDocTemplate* GetTheDocTemplate()
	{
		POSITION Pos = m_pDocManager->GetFirstDocTemplatePosition();
		CDocTemplate* pDocT = m_pDocManager->GetNextDocTemplate(Pos);
		return static_cast<CMultiDocTemplate*>(pDocT);
	}

protected:
	//HANDLE mtx;

public:
	// 反编译操作
	void DoDecomplie(const CStringW & Source);
	//反编译标志
	enum class DecompFlags { DecompJar, DecompClass } Flag;
	enum class OpenFlags { OpenJar, OpenClass } OpenFlag;
	enum class AppLanguage{Chinese,English} Language;

	CFindDialog::SearchArea m_PreferredArea;

	CStringW PathToSave;
	CStringW JarFilePath;
	CStringW JREInfo;
	bool Initing;
	bool bDecompInsideJar;
	bool bMultiSelection;
	CDialogEx * RunningDialog;
	CMultiDocTemplate * pStartupPageDocT;
	CRecentFileList * pMRUList;
	HANDLE EnableRecovery;
	CStringW Md5ofFile;
	CStringW m_Uuid;
	CStringW FontFaceName;
	CStringW LatestFileFolder;
	int FontSize;

	HANDLE SemInstanceCount;
	HANDLE MtxRmCache;
	HANDLE EvtIsToRmCache;

	bool IsJDKInstalled;

	bool IsQuickDecomp;
	bool EnableAutoSave;
	bool EnableIgnoreCache;
	bool EnableDesktopAlert;
	bool EnableMDIReload;

	DecomplieOptions m_DecompOption;

	afx_msg void OnFileSaveAs();
	virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
	afx_msg void OnFileSave();
	afx_msg void OnUpdateFileSave(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFileSaveAs(CCmdUI *pCmdUI);
	afx_msg void OnFileClose();
	afx_msg void OnUpdateFileClose(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRecentFileMenu(CCmdUI *pCmdUI);
	afx_msg void OnFileNew();
};

extern CFernflowerUIMFCApp theApp;

class connection_error :public std::exception
{
public:
	connection_error() :std::exception("connection_error\n") {};
	~connection_error() noexcept {};

};

class CCmdLineArgInfo :public CCommandLineInfo
{
public:
	bool m_bOpenNewFile;
	bool m_bOpenInnerFile;
	virtual void ParseParam(const TCHAR* pszParam, BOOL bFlag, BOOL bLast) override;
	CCmdLineArgInfo() :CCommandLineInfo(), m_bOpenNewFile(false), m_bOpenInnerFile(false) {};
};

class CDecompAlertWnd :public CMFCDesktopAlertWnd
{
protected:
	virtual BOOL OnClickLinkButton(UINT);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
};