/*************************************************
 File name: CTabDlg2.h
 Author:范哲  Version:1.0.0  Date:2020.12.30
 Description: TabControl控件的第而个页面，主要实现了
			1、单词数据库显示操作，在单词编辑框中显示
			选择的单词，第二编辑框显示翻译内容。
			2、词库的添加、修改、删除功能

 Function List:
 1.ConnectDatabase()
 主要功能：连接数据库

 2. OnClickedButtonDbsearch()
 主要功能：单词数据库内容全部输出

 3.OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
 主要功能：背景颜色美化

 4.OnBnClickedButtonAdd()
 主要功能：单词添加

 5.OnBnClickedButtonDelete()
 主要功能：单词删除

 6.OnBnClickedButtonEdit()
 主要功能：单词编辑
*************************************************/
#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<Windows.h>
#include<WinSock.h>
#include<mysql.h>

#include "afxcmn.h"
#include "afxdb.h"
#include "afxwin.h"
#include<iostream>

#pragma comment(lib,"libmysql.lib")
#pragma comment(lib,"wsock32.lib")
// CTabDlg2 dialog

class CTabDlg2 : public CDialog
{
	DECLARE_DYNAMIC(CTabDlg2)

public:
	CTabDlg2(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CTabDlg2();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAINDIALOG_TAB2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
private: 
	MYSQL* mysql = new MYSQL; //mysql连接
public:
	virtual BOOL OnInitDialog();
	//连接数据库
	virtual BOOL CTabDlg2::ConnectDatabase();
	//列表
	CListCtrl m_list;
	//列表中的单词元素
	CEdit m_uiWord;
	//列表中的翻译元素
	CEdit m_uiMeaning;
	//背景图片的成员变量
	CBitmap m_Bmp;
	CBrush m_Brush;
	//按键的成员变量
	CBitmapButton m_AddWord;
	CBitmapButton m_EditWord;
	CBitmapButton m_DeleteWord;
	CBitmapButton m_SearchAll;
	afx_msg void OnClickedButtonDbsearch();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnNMClickListDbshow(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonEdit();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
