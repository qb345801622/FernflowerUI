
// FernflowerUI_MFC.h: FernflowerUI_MFC 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


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
	DECLARE_MESSAGE_MAP()
	afx_msg void OnEditCopy();
	afx_msg void OnEditSelectAll();
	afx_msg void OpenFile();

protected:
	//HANDLE mtx;

public:
	// 反编译操作
	void DoDecomplie(const CStringW & Source);
	//反编译标志
	enum class DecompFlags { DecompJar, DecompClass };
	enum class AppLanguage{Chinese,English} Language;
	CStringW PathToSave;
	CStringW JarFilePath;
	bool Initing;
	CDialogEx * RunningDialog;
	HANDLE EnableRecovery;
	CStringW Md5ofFile;
	CStringW FontFaceName;
	int FontSize;

	HANDLE SemInstanceCount;
	HANDLE MtxRmCache;
	HANDLE EvtIsToRmCache;

	bool IsJDKInstalled;

	bool IsQuickDecomp;
	afx_msg void OnFileSaveAs();
};

extern CFernflowerUIMFCApp theApp;

class connection_error :public std::exception
{
public:
	connection_error() :std::exception("connection_error\n") {};
	~connection_error() noexcept {};

};