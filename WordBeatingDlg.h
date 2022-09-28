/*************************************************
 File name: WordBeatingDlg.h
 Author:范哲  Version:1.0.0  Date:2020.12.30
 Description: 主对话框界面，主要实现了
			1、TabControl控件之间页面的跳转

 Function List:
 1. OnTcnSelchangeTabMain(NMHDR* pNMHDR, LRESULT* pResult)
 主要功能：Tab标签页面跳转
*************************************************/
// WordBeatingDlg.h : header file
//

#pragma once
#include "CTabDlg1.h"
#include "CTabDlg2.h"

// CWordBeatingDlg dialog
class CWordBeatingDlg : public CDialogEx
{
// Construction
public:
	CWordBeatingDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WORDBEATING_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	//应用图标
	HICON m_hIcon;
	//Tab控件标签图标
	HICON hIcon_Tab1;
	HICON hIcon_Tab2;
	
	CTabCtrl m_tab;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int m_CurSelTab;
	CImageList imagelist;
	CTabDlg1 m_page1;
	CTabDlg2 m_page2;
	//用来保存对话框对象指针
	CDialog* pDialog[2];  
	afx_msg void OnTcnSelchangeTabMain(NMHDR* pNMHDR, LRESULT* pResult);
};
