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
// CTabDlg2.cpp : implementation file
//

#include "pch.h"
#include "WordBeating.h"
#include "CTabDlg2.h"
#include "afxdialogex.h"
#define _CRT_SECURE_NO_WARNINGS

IMPLEMENT_DYNAMIC(CTabDlg2, CDialog)

CTabDlg2::CTabDlg2(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MAINDIALOG_TAB2, pParent)
{
	//������Դ�е�λͼ
	m_Bmp.LoadBitmap(MAKEINTRESOURCE(IDB_BITMAP_BACKGROUND));

	//����λͼ��ˢ
	m_Brush.CreatePatternBrush(&m_Bmp);
}

CTabDlg2::~CTabDlg2()
{
}

void CTabDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DBSHOW, m_list);
	DDX_Control(pDX, IDC_EDIT_WORD, m_uiWord);
	DDX_Control(pDX, IDC_EDIT_MEANING, m_uiMeaning);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_AddWord);
	DDX_Control(pDX, IDC_BUTTON_EDIT, m_EditWord);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_DeleteWord);
	DDX_Control(pDX, IDC_BUTTON_DBSEARCH, m_SearchAll);
}


BEGIN_MESSAGE_MAP(CTabDlg2, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_DBSEARCH, &CTabDlg2::OnClickedButtonDbsearch)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CTabDlg2::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CTabDlg2::OnBnClickedButtonDelete)
	ON_NOTIFY(NM_CLICK, IDC_LIST_DBSHOW, &CTabDlg2::OnNMClickListDbshow)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, &CTabDlg2::OnBnClickedButtonEdit)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CTabDlg2 message handlers
BOOL CTabDlg2::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	//�趨�����ʽ
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	//��Listctrl�ؼ�������У������ݿ�table��Ӧ��
	/*
	��һ��������ʾ��Ҫ���õ���
	�ڶ���������ʾҪ����������ֵ
	������������ʾ������ʾ���
	���ĸ�������ʾ�����з���Ŀ��
	*/
	m_list.InsertColumn(0, _T("����"), LVCFMT_CENTER, 180);
	m_list.InsertColumn(1, _T("��Ӣ����"), LVCFMT_LEFT, 1500);

	LOGFONT   logfont;
	CFont* pfont = m_list.GetFont();
	pfont->GetLogFont(&logfont);

	//�޸�����ı���
	logfont.lfHeight = logfont.lfHeight * 1.5;   
	logfont.lfWidth = logfont.lfWidth * 1.5;

	static  CFont  font;
	font.CreateFontIndirect(&logfont);
	m_list.SetFont(&font);
	font.Detach();

	font.CreatePointFont(150, "MS Shell Dlg(8)");

	GetDlgItem(IDC_EDIT_WORD)->SetFont(&font);
	GetDlgItem(IDC_EDIT_MEANING)->SetFont(&font);

	m_AddWord.LoadBitmaps(IDB_BITMAP_ADD);
	m_AddWord.SizeToContent();
	m_EditWord.LoadBitmaps(IDB_BITMAP_EDIT);
	m_EditWord.SizeToContent();
	m_DeleteWord.LoadBitmaps(IDB_BITMAP_DELETE);
	m_DeleteWord.SizeToContent();
	m_SearchAll.LoadBitmaps(IDB_BITMAP_SEARCHALL);
	m_SearchAll.SizeToContent();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

/*************************************************
Func Name: OnClickedButtonDbsearch()
Description: ��⵽��ť����󣬽������ݿ�����
			�����
Input:    ��
Output:   ��
*************************************************/
void CTabDlg2::OnClickedButtonDbsearch()
{
	// TODO: Add your control notification handler code here
	m_list.DeleteAllItems();
	ConnectDatabase();

	//�洢��ѯ���
	char cQuery[150]; 

	//����ṹ�������е�һ����ѯ�����
	MYSQL_RES* res;

	//һ�������ݵ����Ͱ�ȫ(type-safe)�ı�ʾ����ʾ�����е���
	MYSQL_ROW column; 

	sprintf_s(cQuery, "select * from word"); 
	mysql_query(mysql, "set names gbk"); 
	mysql_query(mysql, cQuery);

	//��ȡ�����
	res = mysql_store_result(mysql);

	int count = 0;
	while (column = mysql_fetch_row(res))
	{
		/*Ҫ��ListContrl��������ݿ�����ݣ���Ҫ�ȸ��ؼ�����һ�У�
		������һ�������ÿ��������ݣ��ȿ�����*/
		m_list.InsertItem(count, _T(""));
		CString varVocabulary;
		varVocabulary = column[0];
		m_list.SetItemText(count, 0, varVocabulary);
		CString varMeaning;
		varMeaning = column[1];
		m_list.SetItemText(count, 1, varMeaning);
		count++;
	}
}

/*************************************************
Func Name: ConnectDatabase()
Description: ���ӱ�������
Input:    ��
Output:   ��
*************************************************/
BOOL CTabDlg2::ConnectDatabase()
{
	//��ʼ��mysql  
	mysql_init(mysql);

	if (mysql_real_connect(mysql,
		"localhost", "root", "animation717", "sys",
		0, NULL, 0)) //�м�ֱ����������û��������룬���ݿ������˿ں�
	{
		return true;
	}	
}

/*************************************************
Func Name: OnBnClickedButtonAdd()
Description: ��⵽��ť����󣬶Ա༭���ڵĵ����Լ�����
		�������ݿ����ݴ洢��
Input:    ��
Output:   ��
*************************************************/
void CTabDlg2::OnBnClickedButtonAdd()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	ConnectDatabase();

	//�������ݿ��ַ���ʽ�����������������
	mysql_query(mysql, "set names 'gb2312'");

	CString word, meaning;
	m_uiWord.GetWindowText(word);
	m_uiMeaning.GetWindowText(meaning);

	char insert[1000];
	sprintf_s(insert, 
		"insert into word(Vocabulary, Meaning) values (\'%s\', \'%s\')", 
		word, meaning);

	// ִ�� sql ��䡣    
	if (mysql_query(mysql, insert) == 0)
	{
		AfxMessageBox(_T("��ӵ��ʳɹ�!"));
	}
	else 
	{
		AfxMessageBox(_T("��ӵ���ʧ��!"));
	}
	UpdateData(false);
	mysql_close(mysql);//�ر�Mysql����
}

/*************************************************
Func Name: OnBnClickedButtonDelete()
Description: ��⵽��ť����󣬶Ա༭���ڵĵ����Լ�����
		�������ݿ�����ɾ����
Input:    ��
Output:   ��
*************************************************/
void CTabDlg2::OnBnClickedButtonDelete()
{
	// TODO: Add your control notification handler code here
	ConnectDatabase();

	//�������ݿ��ַ���ʽ�����������������
	mysql_query(mysql, "set names 'gb2312'");

	CString word, meaning;
	int nIndex;

	//��ȡ��ǰ�����ListContrl�е�λ��
	nIndex = m_list.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if (nIndex != -1)
	{
		//��ȡ�����������
		word = m_list.GetItemText(nIndex, 0);
		meaning = m_list.GetItemText(nIndex, 1);
	}
	else
	{
		m_uiWord.GetWindowText(word);
		m_uiMeaning.GetWindowText(meaning);
	}

	char delet[1000];
	sprintf_s(delet, 
		"delete from word where Vocabulary='%s' and Meaning='%s'",
		word, meaning);

	// ִ�� sql ��䡣    
	if (mysql_query(mysql, delet) == 0)
	{
		AfxMessageBox(_T("ɾ�����ʳɹ�!"));
	}
	else
	{
		AfxMessageBox(_T("ɾ������ʧ��!"));
	}
	UpdateData(false);
	mysql_close(mysql);//�ر�Mysql����
}

/*************************************************
Func Name: OnNMClickListDbshow()
Description: ��⵽������󣬽��б��ж�Ӧ�ĵ��ʼ�����
			��ʾ���༭���ڡ�
Input:    �������
Output:   ��
*************************************************/
void CTabDlg2::OnNMClickListDbshow(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	int nIndex = 0;
	if (nIndex == -1)
	{
		nIndex = 0;
	}
	//��ȡ��굱ǰѡ�е���
	nIndex = m_list.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);

	//�����е���Ϣ��ʾ���༭����
	m_uiWord.SetWindowText(m_list.GetItemText(nIndex, 0));
	m_uiMeaning.SetWindowText(m_list.GetItemText(nIndex, 1));

	*pResult = 0;
}

/*************************************************
Func Name: OnBnClickedButtonEdit()
Description: ��⵽��ť����󣬶Ա༭���ڵĵ����Լ�����
		�������ݿ������޸ġ�
Input:    ��
Output:   ��
*************************************************/
void CTabDlg2::OnBnClickedButtonEdit()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	ConnectDatabase();

	//�������ݿ��ַ���ʽ�����������������
	mysql_query(mysql, "set names 'gb2312'");

	CString EditWord, EditMeaning, OrinWord, OrinMeaning;
	int nIndex;

	//��ȡ��ǰ�����ListContrl�е�λ��
	nIndex = m_list.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if (nIndex != -1)
	{
		//��ȡ�����������
		OrinWord = m_list.GetItemText(nIndex, 0);
		OrinMeaning = m_list.GetItemText(nIndex, 1);
	}
	m_uiWord.GetWindowText(EditWord);
	m_uiMeaning.GetWindowText(EditMeaning);

	char edit[1000];
	if (EditWord != OrinWord)
	{
		sprintf_s(edit,
			"update word set Vocabulary='%s' where Meaning='%s'",
			EditWord, OrinMeaning);
	}
	else
	{
		sprintf_s(edit,
			"update word set Meaning='%s' where Vocabulary='%s'",
			EditMeaning, OrinWord);
	}
	
	// ִ�� sql ��䡣    
	if (mysql_query(mysql, edit) == 0)
	{
		AfxMessageBox(_T("�޸ĵ��ʳɹ�!"));
	}
	else
	{
		AfxMessageBox(_T("�޸ĵ���ʧ��!"));
	}
	UpdateData(false);
	mysql_close(mysql);//�ر�Mysql����
}

HBRUSH CTabDlg2::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
