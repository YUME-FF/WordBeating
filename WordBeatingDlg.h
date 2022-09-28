/*************************************************
 File name: WordBeatingDlg.h
 Author:����  Version:1.0.0  Date:2020.12.30
 Description: ���Ի�����棬��Ҫʵ����
			1��TabControl�ؼ�֮��ҳ�����ת

 Function List:
 1. OnTcnSelchangeTabMain(NMHDR* pNMHDR, LRESULT* pResult)
 ��Ҫ���ܣ�Tab��ǩҳ����ת
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
	//Ӧ��ͼ��
	HICON m_hIcon;
	//Tab�ؼ���ǩͼ��
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
	//��������Ի������ָ��
	CDialog* pDialog[2];  
	afx_msg void OnTcnSelchangeTabMain(NMHDR* pNMHDR, LRESULT* pResult);
};
