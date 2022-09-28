/*************************************************
 File name: CTabDlg1.h
 Author:范哲  Version:1.0.0  Date:2020.12.30
 Description: TabControl控件的第一个页面，主要实现了
			1、英文/中文字段的查询操作，在顶部编辑框中
			输入待查询内容，第二编辑框会再次输出待查询
			内容，第三编辑框输出翻译结果。
			2、广告栏位的滚动显示，点击广告可跳转至网
			页界面
			3、用户信息链接，点击右上角用户头像标识，可
			跳转至有道词典官方网站

 Function List:
 1.ConnectDatabase()
 主要功能：连接数据库

 2.OnBnClickedButtonWdsearch()
 主要功能：数据库字段查询

 3.OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
 主要功能：背景颜色美化

 4.OnBnClickedButtonAd()
 主要功能：广告网页跳转

 5.OnBnClickedButtonUser()
 主要功能：有道词典官网跳转
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

// CTabDlg1 dialog

class CTabDlg1 : public CDialog
{
	DECLARE_DYNAMIC(CTabDlg1)

public:
	CTabDlg1(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CTabDlg1();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAINDIALOG_TAB1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	//mysql连接
	MYSQL* mysql = new MYSQL; 
public:
	void ShowAD();
	virtual BOOL OnInitDialog();
	//连接数据库
	virtual BOOL CTabDlg1::ConnectDatabase();
	//输入需要查询的单词/中文
	CEdit m_SearchTarget;
	//展示查询的单词
	CEdit m_TargetShow;
	//展示需要查询的单词的中英翻译
	CEdit m_SearchAns;
	//广告栏位
	CBitmapButton m_ad;
	//查询按键
	CBitmapButton m_Search;
	//背景图片的成员变量
	CBitmap m_Bmp;
	CBrush m_Brush;
	//用户头像
	CBitmapButton m_UserPicture;
	afx_msg void OnBnClickedButtonWdsearch();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonAd();
	afx_msg LRESULT OnUpdateAD(WPARAM  wParam, LPARAM Param);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonUser();
};
