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
	//加载资源中的位图
	m_Bmp.LoadBitmap(MAKEINTRESOURCE(IDB_BITMAP_BACKGROUND));

	//创建位图画刷
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

	//设定风格样式
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	//在Listctrl控件上添加列，与数据库table对应。
	/*
	第一个参数表示需要设置的列
	第二个参数表示要给该列填充的值
	第三个参数表示填充的显示风格
	第四个参数表示给该列分配的宽度
	*/
	m_list.InsertColumn(0, _T("单词"), LVCFMT_CENTER, 180);
	m_list.InsertColumn(1, _T("中英翻译"), LVCFMT_LEFT, 1500);

	LOGFONT   logfont;
	CFont* pfont = m_list.GetFont();
	pfont->GetLogFont(&logfont);

	//修改字体的比例
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
Description: 检测到按钮输入后，进行数据库内容
			输出。
Input:    无
Output:   无
*************************************************/
void CTabDlg2::OnClickedButtonDbsearch()
{
	// TODO: Add your control notification handler code here
	m_list.DeleteAllItems();
	ConnectDatabase();

	//存储查询语句
	char cQuery[150]; 

	//这个结构代表返回行的一个查询结果集
	MYSQL_RES* res;

	//一个行数据的类型安全(type-safe)的表示，表示数据行的列
	MYSQL_ROW column; 

	sprintf_s(cQuery, "select * from word"); 
	mysql_query(mysql, "set names gbk"); 
	mysql_query(mysql, cQuery);

	//获取结果集
	res = mysql_store_result(mysql);

	int count = 0;
	while (column = mysql_fetch_row(res))
	{
		/*要往ListContrl中填充数据库的数据，就要先给控件开辟一行，
		在向这一行里面的每列填充数据，先开辟行*/
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
Description: 连接本机数据
Input:    无
Output:   无
*************************************************/
BOOL CTabDlg2::ConnectDatabase()
{
	//初始化mysql  
	mysql_init(mysql);

	if (mysql_real_connect(mysql,
		"localhost", "root", "animation717", "sys",
		0, NULL, 0)) //中间分别是主机，用户名，密码，数据库名，端口号
	{
		return true;
	}	
}

/*************************************************
Func Name: OnBnClickedButtonAdd()
Description: 检测到按钮输入后，对编辑框内的单词以及释义
		进行数据库内容存储。
Input:    无
Output:   无
*************************************************/
void CTabDlg2::OnBnClickedButtonAdd()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	ConnectDatabase();

	//设置数据库字符格式，解决中文乱码问题
	mysql_query(mysql, "set names 'gb2312'");

	CString word, meaning;
	m_uiWord.GetWindowText(word);
	m_uiMeaning.GetWindowText(meaning);

	char insert[1000];
	sprintf_s(insert, 
		"insert into word(Vocabulary, Meaning) values (\'%s\', \'%s\')", 
		word, meaning);

	// 执行 sql 语句。    
	if (mysql_query(mysql, insert) == 0)
	{
		AfxMessageBox(_T("添加单词成功!"));
	}
	else 
	{
		AfxMessageBox(_T("添加单词失败!"));
	}
	UpdateData(false);
	mysql_close(mysql);//关闭Mysql连接
}

/*************************************************
Func Name: OnBnClickedButtonDelete()
Description: 检测到按钮输入后，对编辑框内的单词以及释义
		进行数据库内容删除。
Input:    无
Output:   无
*************************************************/
void CTabDlg2::OnBnClickedButtonDelete()
{
	// TODO: Add your control notification handler code here
	ConnectDatabase();

	//设置数据库字符格式，解决中文乱码问题
	mysql_query(mysql, "set names 'gb2312'");

	CString word, meaning;
	int nIndex;

	//获取当前鼠标在ListContrl中的位置
	nIndex = m_list.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if (nIndex != -1)
	{
		//获取鼠标点击的内容
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

	// 执行 sql 语句。    
	if (mysql_query(mysql, delet) == 0)
	{
		AfxMessageBox(_T("删除单词成功!"));
	}
	else
	{
		AfxMessageBox(_T("删除单词失败!"));
	}
	UpdateData(false);
	mysql_close(mysql);//关闭Mysql连接
}

/*************************************************
Func Name: OnNMClickListDbshow()
Description: 检测到鼠标点击后，将列表中对应的单词及释义
			显示至编辑框内。
Input:    鼠标点击处
Output:   无
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
	//获取鼠标当前选中的行
	nIndex = m_list.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);

	//将该行的信息显示到编辑框中
	m_uiWord.SetWindowText(m_list.GetItemText(nIndex, 0));
	m_uiMeaning.SetWindowText(m_list.GetItemText(nIndex, 1));

	*pResult = 0;
}

/*************************************************
Func Name: OnBnClickedButtonEdit()
Description: 检测到按钮输入后，对编辑框内的单词以及释义
		进行数据库内容修改。
Input:    无
Output:   无
*************************************************/
void CTabDlg2::OnBnClickedButtonEdit()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	ConnectDatabase();

	//设置数据库字符格式，解决中文乱码问题
	mysql_query(mysql, "set names 'gb2312'");

	CString EditWord, EditMeaning, OrinWord, OrinMeaning;
	int nIndex;

	//获取当前鼠标在ListContrl中的位置
	nIndex = m_list.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if (nIndex != -1)
	{
		//获取鼠标点击的内容
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
	
	// 执行 sql 语句。    
	if (mysql_query(mysql, edit) == 0)
	{
		AfxMessageBox(_T("修改单词成功!"));
	}
	else
	{
		AfxMessageBox(_T("修改单词失败!"));
	}
	UpdateData(false);
	mysql_close(mysql);//关闭Mysql连接
}

HBRUSH CTabDlg2::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	if (nCtlColor == CTLCOLOR_EDIT)
	{
		pDC->SetBkColor(RGB(250, 250, 250));  //字体背景色
	}
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(RGB(0, 50, 150)); //字体颜色

		pDC->SetBkMode(TRANSPARENT); //设置字体背景为透明
	}

	// TODO:  Return a different brush if the default is not desired
	return m_Brush;
}
