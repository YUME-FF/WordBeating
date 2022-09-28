/*************************************************
 File name: CTabDlg2.h
 Author:����  Version:1.0.0  Date:2020.12.30
 Description: TabControl�ؼ��ĵڶ���ҳ�棬��Ҫʵ����
			1���������ݿ���ʾ�������ڵ��ʱ༭������ʾ
			ѡ��ĵ��ʣ��ڶ��༭����ʾ�������ݡ�
			2���ʿ����ӡ��޸ġ�ɾ������

 Function List:
 1.ConnectDatabase()
 ��Ҫ���ܣ��������ݿ�

 2. OnClickedButtonDbsearch()
 ��Ҫ���ܣ��������ݿ�����ȫ�����

 3.OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
 ��Ҫ���ܣ�������ɫ����

 4.OnBnClickedButtonAdd()
 ��Ҫ���ܣ��������

 5.OnBnClickedButtonDelete()
 ��Ҫ���ܣ�����ɾ��

 6.OnBnClickedButtonEdit()
 ��Ҫ���ܣ����ʱ༭
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
	MYSQL* mysql = new MYSQL; //mysql����
public:
	virtual BOOL OnInitDialog();
	//�������ݿ�
	virtual BOOL CTabDlg2::ConnectDatabase();
	//�б�
	CListCtrl m_list;
	//�б��еĵ���Ԫ��
	CEdit m_uiWord;
	//�б��еķ���Ԫ��
	CEdit m_uiMeaning;
	//����ͼƬ�ĳ�Ա����
	CBitmap m_Bmp;
	CBrush m_Brush;
	//�����ĳ�Ա����
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
