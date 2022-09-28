/************************************************************
 FileName: CTabDlg1.cpp
 Author:范哲  Version :1.0.0  Date:2020.12.30
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
***********************************************************/

// CTabDlg1.cpp : implementation file
//

#include "pch.h"
#include "WordBeating.h"
#include "CTabDlg1.h"
#include "afxdialogex.h"
#define _CRT_SECURE_NO_WARNINGS


// CTabDlg1 dialog

//自定义消息:时钟更新
#define UM_UPDATE_CLOCK WM_USER+101

/***************************************
	定义时钟线程
	时间长度：1s
***************************************/
UINT clockThreadFun(LPVOID  Param)
{
	while (true)
	{
		Sleep(1000); //延时1秒

		::PostMessage((HWND)Param, UM_UPDATE_CLOCK, 0, 0);
	}

	return 1;
}

IMPLEMENT_DYNAMIC(CTabDlg1, CDialog)

CTabDlg1::CTabDlg1(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MAINDIALOG_TAB1, pParent)
{
	//加载资源中的位图
	m_Bmp.LoadBitmap(MAKEINTRESOURCE(IDB_BITMAP_BACKGROUND2));

	//创建位图画刷
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
	font3.CreatePointFont(150, "迷你简雪君");

	//改变静态控件字体格式
	GetDlgItem(IDC_STATIC1)->SetFont(&font3);
	GetDlgItem(IDC_STATIC2)->SetFont(&font3);

	//改变编辑框字体格式
	GetDlgItem(IDC_EDIT_WDSEARCH)->SetFont(&font2);
	GetDlgItem(IDC_EDIT_WDSHOW)->SetFont(&font1);
	GetDlgItem(IDC_EDIT_ANSSHOW)->SetFont(&font2);

	//启动新的线程，每隔1秒发送一个自定义消息（刷新屏幕）
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
Description: 根据系统当前的时间进行设置，实现广告的滚
动显示效果。
Input:    无    
Output:   无
*************************************************/
void CTabDlg1::ShowAD()
{
	//-------------------------------获取系统当前时间
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
Description: 单词查询，检测到按钮输入后，进行数据库内容
			查询。
Input:    无
Output:   无
*************************************************/
void CTabDlg1::OnBnClickedButtonWdsearch()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	ConnectDatabase();

	//查询语句
	char cQuery[150]; 

	//返回行的一个查询结果集
	MYSQL_RES* res; 

	//一个行数据的类型安全(type-safe)的表示，表示数据行的列
	MYSQL_ROW column; 

	//字段列数组
	MYSQL_FIELD* fd; 

	//存放查询结果
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
			//检测到用户输入的是英文
			flag = 0;

			sprintf_s(cQuery,
				"select Meaning from word where Vocabulary ='%s'",
				Word); //执行查询语句
		}
		else
		{
			//检测到用户输入的是中文
			flag = 1;

			sprintf_s(cQuery,
				"select Vocabulary from word where Meaning ='%s'",
				Word); //执行查询语句
		}
	}

	mysql_query(mysql, "set names gbk");

	//执行SQL语句
	mysql_query(mysql, cQuery);

	//获取结果集
	res = mysql_store_result(mysql); 
	if (res)
	{
		while (column = mysql_fetch_row(res))
		{
			CString varMeaning;
			varMeaning = column[0];
			m_SearchAns.SetWindowText(varMeaning);

		}
		mysql_free_result(res);//释放结果集
	}
	else
	{
		MessageBox("未查询到结果，请检查拼写或进入单词本界面进行单词添加");
	}

	UpdateData(false);
	mysql_close(mysql);
}

/*************************************************
Func Name: ConnectDatabase()
Description: 连接本机数据
Input:    无
Output:   无
*************************************************/
BOOL CTabDlg1::ConnectDatabase()
{
	//初始化mysql  
	mysql_init(mysql);
	
	if (mysql_real_connect(mysql,
		"localhost", "root", "animation717", "sys",
		0, NULL, 0))//中间分别是主机，用户名，密码，数据库名，端口号
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

/*************************************************
Func Name: OnBnClickedButtonAd()
Description: 通过动态链接库进行广告网页链接跳转。
Input:    无
Output:   无
*************************************************/
void CTabDlg1::OnBnClickedButtonAd()
{
	// TODO: Add your control notification handler code here
	HINSTANCE  DllHandler;
	typedef  void(*DLLTES)(char* pText);
	DLLTES DLLTest;

	//动态装载“OpenNet.dll”到内存,返回资源模块句柄给DllHandler
	DllHandler = ::LoadLibrary("OpenNet.dll");
	if (DllHandler != NULL)
	{
		//使用刚得到的资源模块句柄DllHandler并把该指针赋给DLLTest
		DLLTest = (DLLTES)::GetProcAddress(DllHandler, "OpenNet");

		//通过DLLTest间接调用OpenNet
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
Description: 跳转至有道词典官方网站。
Input:    无
Output:   无
*************************************************/
void CTabDlg1::OnBnClickedButtonUser()
{
	// TODO: Add your control notification handler code here
	ShellExecute(NULL, _T("open"), "http://www.youdao.com/", NULL, NULL, SW_SHOWNORMAL);
}

