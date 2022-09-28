/*************************************************
 File name: WordBeatingDlg.h
 Author:范哲  Version:1.0.0  Date:2020.12.30
 Description: 主对话框界面，主要实现了
			1、TabControl控件之间页面的跳转

 Function List:
 1. OnTcnSelchangeTabMain(NMHDR* pNMHDR, LRESULT* pResult)
 主要功能：Tab标签页面跳转
*************************************************/
// WordBeatingDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "WordBeating.h"
#include "WordBeatingDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWordBeatingDlg dialog



CWordBeatingDlg::CWordBeatingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WORDBEATING_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON);
	hIcon_Tab1 = AfxGetApp()->LoadIcon(IDI_ICON1);
	hIcon_Tab2 = AfxGetApp()->LoadIcon(IDI_ICON2);
}

void CWordBeatingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	//变量m_tab用来与对话框中的Tab Control控件交互
	DDX_Control(pDX, IDC_TAB_MAIN, m_tab);
}

BEGIN_MESSAGE_MAP(CWordBeatingDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &CWordBeatingDlg::OnTcnSelchangeTabMain)
END_MESSAGE_MAP()


// CWordBeatingDlg message handlers

BOOL CWordBeatingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	imagelist.Create(16, 16, ILC_COLOR32, 2, 2);

	imagelist.Add(hIcon_Tab1);
	imagelist.Add(hIcon_Tab2);
	m_tab.SetImageList(&imagelist);

	//为Tab Control增加两个页面
	m_tab.InsertItem(0, _T("查询"), 0);
	m_tab.InsertItem(1, _T("单词本"), 1);

	//创建两个对话框
	m_page1.Create(IDD_MAINDIALOG_TAB1, &m_tab);
	m_page2.Create(IDD_MAINDIALOG_TAB2, &m_tab);

	//设定在Tab内显示的范围
	CRect rc;
	m_tab.GetClientRect(rc);
	rc.top += 20;
	rc.bottom -= 0;
	rc.left += 0;
	rc.right -= 0;
	m_page1.MoveWindow(&rc);
	m_page2.MoveWindow(&rc);

	//把对话框对象指针保存起来
	pDialog[0] = &m_page1;
	pDialog[1] = &m_page2;

	//显示初始页面
	pDialog[0]->ShowWindow(SW_SHOW);
	pDialog[1]->ShowWindow(SW_HIDE);

	//保存当前选择
	m_CurSelTab = 0;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWordBeatingDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWordBeatingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/*************************************************
Func Name: OnTcnSelchangeTabMain()
Description: 进行Tab控件的页面转换。
Input:    无
Output:   无
*************************************************/
void CWordBeatingDlg::OnTcnSelchangeTabMain(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	//把当前的页面隐藏起来
	pDialog[m_CurSelTab]->ShowWindow(SW_HIDE);

	//得到新的页面索引
	m_CurSelTab = m_tab.GetCurSel();

	//把新的页面显示出来
	pDialog[m_CurSelTab]->ShowWindow(SW_SHOW);

	*pResult = 0;
}
