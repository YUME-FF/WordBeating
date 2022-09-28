/************************************************************
 FileName: CTabDlg1.cpp
 Author:����  Version :1.0.0  Date:2020.12.30
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
***********************************************************/

// CTabDlg1.cpp : implementation file
//

#include "pch.h"
#include "WordBeating.h"
#include "CTabDlg1.h"
#include "afxdialogex.h"
#define _CRT_SECURE_NO_WARNINGS


// CTabDlg1 dialog

//�Զ�����Ϣ:ʱ�Ӹ���
#define UM_UPDATE_CLOCK WM_USER+101

/***************************************
	����ʱ���߳�
	ʱ�䳤�ȣ�1s
***************************************/
UINT clockThreadFun(LPVOID  Param)
{
	while (true)
	{
		Sleep(1000); //��ʱ1��

		::PostMessage((HWND)Param, UM_UPDATE_CLOCK, 0, 0);
	}

	return 1;
}

IMPLEMENT_DYNAMIC(CTabDlg1, CDialog)

CTabDlg1::CTabDlg1(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MAINDIALOG_TAB1, pParent)
{
	//������Դ�е�λͼ
	m_Bmp.LoadBitmap(MAKEINTRESOURCE(IDB_BITMAP_BACKGROUND2));

	//����λͼ��ˢ
	m_Brush.CreatePatternBrush(&m_Bmp);
}

CTabDlg1::~CTabDlg1()
{
}

void CTabDlg1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_WDSEARCH, m_SearchTarget);
	DDX_Control(pDX, IDC_EDIT_WDSHOW, m_TargetShow);
	DDX_Control(pDX, IDC_EDIT_ANSSHOW, m_SearchAns);
	DDX_Control(pDX, IDC_BUTTON_AD, m_ad);
	DDX_Control(pDX, IDC_BUTTON_WDSEARCH, m_Search);
	DDX_Control(pDX, IDC_BUTTON_USER, m_UserPicture);
}


BEGIN_MESSAGE_MAP(CTabDlg1, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_WDSEARCH, &CTabDlg1::OnBnClickedButtonWdsearch)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_AD, &CTabDlg1::OnBnClickedButtonAd)
	ON_WM_PAINT()
	ON_MESSAGE(UM_UPDATE_CLOCK, &CTabDlg1::OnUpdateAD)
	ON_BN_CLICKED(IDC_BUTTON_USER, &CTabDlg1::OnBnClickedButtonUser)
END_MESSAGE_MAP()


// CTabDlg1 message handlers

BOOL CTabDlg1::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	static  CFont  font1, font2, font3;
	font1.CreatePointFont(300, "MS Shell Dlg(8)");
	font2.CreatePointFont(150, "MS Shell Dlg(8)");
	font3.CreatePointFont(150, "�����ѩ��");

	//�ı侲̬�ؼ������ʽ
	GetDlgItem(IDC_STATIC1)->SetFont(&font3);
	GetDlgItem(IDC_STATIC2)->SetFont(&font3);

	//�ı�༭�������ʽ
	GetDlgItem(IDC_EDIT_WDSEARCH)->SetFont(&font2);
	GetDlgItem(IDC_EDIT_WDSHOW)->SetFont(&font1);
	GetDlgItem(IDC_EDIT_ANSSHOW)->SetFont(&font2);

	//�����µ��̣߳�ÿ��1�뷢��һ���Զ�����Ϣ��ˢ����Ļ��
	AfxBeginThread(clockThreadFun, (LPVOID)GetSafeHwnd());
	
	m_Search.LoadBitmaps(IDB_BITMAP_SEARCH);
	m_Search.SizeToContent();
	m_UserPicture.LoadBitmaps(IDB_BITMAP_USER);
	m_UserPicture.SizeToContent();


	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

/*************************************************   
Func Name: ShowAD()   
Description: ����ϵͳ��ǰ��ʱ��������ã�ʵ�ֹ��Ĺ�
����ʾЧ����
Input:    ��    
Output:   ��
*************************************************/
void CTabDlg1::ShowAD()
{
	//-------------------------------��ȡϵͳ��ǰʱ��
	CTime m_time = CTime::GetCurrentTime();
	int second = m_time.GetSecond();
	if (second % 10 < 5)
	{
		m_ad.LoadBitmaps(IDB_BITMAP_AD00);
		m_ad.SizeToContent();
	}
	else
	{
		m_ad.LoadBitmaps(IDB_BITMAP_AD01);
		m_ad.SizeToContent();
	}
}

LRESULT CTabDlg1::OnUpdateAD(WPARAM wParam, LPARAM Param)
{
	Invalidate();
	return true;
}

/*************************************************
Func Name: OnBnClickedButtonWdsearch()
Description: ���ʲ�ѯ����⵽��ť����󣬽������ݿ�����
			��ѯ��
Input:    ��
Output:   ��
*************************************************/
void CTabDlg1::OnBnClickedButtonWdsearch()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	ConnectDatabase();

	//��ѯ���
	char cQuery[150]; 

	//�����е�һ����ѯ�����
	MYSQL_RES* res; 

	//һ�������ݵ����Ͱ�ȫ(type-safe)�ı�ʾ����ʾ�����е���
	MYSQL_ROW column; 

	//�ֶ�������
	MYSQL_FIELD* fd; 

	//��Ų�ѯ���
	char str[100][100]; 

	CString Word;
	m_SearchTarget.GetWindowText(Word);
	m_TargetShow.SetWindowText(Word);

	char cIsChinese;
	int flag=0;
	for (int i = 0; i < Word.GetLength(); i++)
	{
		cIsChinese = Word.GetAt(i);
		if (cIsChinese >= 'a' && cIsChinese <= 'z'
			|| cIsChinese >= 'A' && cIsChinese <= 'Z')
		{
			//��⵽�û��������Ӣ��
			flag = 0;

			sprintf_s(cQuery,
				"select Meaning from word where Vocabulary ='%s'",
				Word); //ִ�в�ѯ���
		}
		else
		{
			//��⵽�û������������
			flag = 1;

			sprintf_s(cQuery,
				"select Vocabulary from word where Meaning ='%s'",
				Word); //ִ�в�ѯ���
		}
	}

	mysql_query(mysql, "set names gbk");

	//ִ��SQL���
	mysql_query(mysql, cQuery);

	//��ȡ�����
	res = mysql_store_result(mysql); 
	if (res)
	{
		while (column = mysql_fetch_row(res))
		{
			CString varMeaning;
			varMeaning = column[0];
			m_SearchAns.SetWindowText(varMeaning);

		}
		mysql_free_result(res);//�ͷŽ����
	}
	else
	{
		MessageBox("δ��ѯ�����������ƴд����뵥�ʱ�������е������");
	}

	UpdateData(false);
	mysql_close(mysql);
}

/*************************************************
Func Name: ConnectDatabase()
Description: ���ӱ�������
Input:    ��
Output:   ��
*************************************************/
BOOL CTabDlg1::ConnectDatabase()
{
	//��ʼ��mysql  
	mysql_init(mysql);
	
	if (mysql_real_connect(mysql,
		"localhost", "root", "animation717", "sys",
		0, NULL, 0))//�м�ֱ����������û��������룬���ݿ������˿ں�
	{
		return true;
	}
		
}

HBRUSH CTabDlg1::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	if (nCtlColor == CTLCOLOR_EDIT)
	{
		pDC->SetBkColor(RGB(250, 250, 250));  //���屳��ɫ
	}
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(RGB(0, 50, 150)); //������ɫ

		pDC->SetBkMode(TRANSPARENT); //�������屳��Ϊ͸��
	}
	// TODO:  Return a different brush if the default is not desired
	return m_Brush;
}

/*************************************************
Func Name: OnBnClickedButtonAd()
Description: ͨ����̬���ӿ���й����ҳ������ת��
Input:    ��
Output:   ��
*************************************************/
void CTabDlg1::OnBnClickedButtonAd()
{
	// TODO: Add your control notification handler code here
	HINSTANCE  DllHandler;
	typedef  void(*DLLTES)(char* pText);
	DLLTES DLLTest;

	//��̬װ�ء�OpenNet.dll�����ڴ�,������Դģ������DllHandler
	DllHandler = ::LoadLibrary("OpenNet.dll");
	if (DllHandler != NULL)
	{
		//ʹ�øյõ�����Դģ����DllHandler���Ѹ�ָ�븳��DLLTest
		DLLTest = (DLLTES)::GetProcAddress(DllHandler, "OpenNet");

		//ͨ��DLLTest��ӵ���OpenNet
		DLLTest("1");
		FreeLibrary(DllHandler);
	}
	else
	{
		ShellExecute(NULL, _T("open"), "http://www.bilibili.com", NULL, NULL, SW_SHOWNORMAL);
	}	
}

void CTabDlg1::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
	ShowAD();
					   // Do not call CDialog::OnPaint() for painting messages
}

/*************************************************
Func Name: OnBnClickedButtonUser()
Description: ��ת���е��ʵ�ٷ���վ��
Input:    ��
Output:   ��
*************************************************/
void CTabDlg1::OnBnClickedButtonUser()
{
	// TODO: Add your control notification handler code here
	ShellExecute(NULL, _T("open"), "http://www.youdao.com/", NULL, NULL, SW_SHOWNORMAL);
}

