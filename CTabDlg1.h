/*************************************************
 File name: CTabDlg1.h
 Author:����  Version:1.0.0  Date:2020.12.30
 Description: TabControl�ؼ��ĵ�һ��ҳ�棬��Ҫʵ����
			1��Ӣ��/�����ֶεĲ�ѯ�������ڶ����༭����
			�������ѯ���ݣ��ڶ��༭����ٴ��������ѯ
			���ݣ������༭�������������
			2�������λ�Ĺ�����ʾ�����������ת����
			ҳ����
			3���û���Ϣ���ӣ�������Ͻ��û�ͷ���ʶ����
			��ת���е��ʵ�ٷ���վ

 Function List:
 1.ConnectDatabase()
 ��Ҫ���ܣ��������ݿ�

 2.OnBnClickedButtonWdsearch()
 ��Ҫ���ܣ����ݿ��ֶβ�ѯ

 3.OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
 ��Ҫ���ܣ�������ɫ����

 4.OnBnClickedButtonAd()
 ��Ҫ���ܣ������ҳ��ת

 5.OnBnClickedButtonUser()
 ��Ҫ���ܣ��е��ʵ������ת
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
	//mysql����
	MYSQL* mysql = new MYSQL; 
public:
	void ShowAD();
	virtual BOOL OnInitDialog();
	//�������ݿ�
	virtual BOOL CTabDlg1::ConnectDatabase();
	//������Ҫ��ѯ�ĵ���/����
	CEdit m_SearchTarget;
	//չʾ��ѯ�ĵ���
	CEdit m_TargetShow;
	//չʾ��Ҫ��ѯ�ĵ��ʵ���Ӣ����
	CEdit m_SearchAns;
	//�����λ
	CBitmapButton m_ad;
	//��ѯ����
	CBitmapButton m_Search;
	//����ͼƬ�ĳ�Ա����
	CBitmap m_Bmp;
	CBrush m_Brush;
	//�û�ͷ��
	CBitmapButton m_UserPicture;
	afx_msg void OnBnClickedButtonWdsearch();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonAd();
	afx_msg LRESULT OnUpdateAD(WPARAM  wParam, LPARAM Param);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonUser();
};
