// ShowNum.cpp : implementation file
//

#include "stdafx.h"
#include "gh0st.h"
#include "ShowNum.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CShowNum* g_pNumDlg;
/////////////////////////////////////////////////////////////////////////////
// CShowNum

IMPLEMENT_DYNCREATE(CShowNum, CFormView)

CShowNum::CShowNum()
	: CFormView(CShowNum::IDD)
{
	//{{AFX_DATA_INIT(CShowNum)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	g_pNumDlg = this;
// 	NT = 0;
// 	XP = 0;
// 	Vista = 0;
// 	Win7 = 0;
// 	Win2000 = 0;
// 	Win2003 = 0;
// 	Win2008 = 0;
}

CShowNum::~CShowNum()
{
}

void CShowNum::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShowNum)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShowNum, CFormView)
	//{{AFX_MSG_MAP(CShowNum)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON9, OnButton9)
	ON_WM_CREATE()

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowNum diagnostics

#ifdef _DEBUG
void CShowNum::AssertValid() const
{
	CFormView::AssertValid();
}

void CShowNum::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CShowNum message handlers

void CShowNum::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	m_MyCpuCtrl.SetRefreshInterval(1000);
	m_MyMemCtrl.SetRefreshInterval(1000);
	UpdateData(FALSE);
	
	CFormView::OnInitialUpdate();
	// TODO: Add your specialized code here and/or call the base class
}

UINT CShowNum::GetNum( int nID )
{	
	UpdateData(TRUE);
	return	GetDlgItemInt( nID, NULL, FALSE );
}

void CShowNum::SetNum( int uID, UINT nValue )
{	
	UpdateData(TRUE);
	SetDlgItemInt( uID, nValue );
}

void CShowNum::OnButton1() 
{
	// TODO: Add your control notification handler code here
		ShellExecute(NULL,"open","notepad.exe",NULL,NULL,SW_SHOW);
}

void CShowNum::OnButton6() 
{
	// TODO: Add your control notification handler code here
	ShellExecute(NULL,"open","gpedit.msc",NULL,NULL,SW_SHOW);	
}

void CShowNum::OnButton2() 
{
	// TODO: Add your control notification handler code here
	  ShellExecute(NULL,"open","mspaint.exe",NULL,NULL,SW_SHOW);
}

void CShowNum::OnButton3() 
{
	// TODO: Add your control notification handler code here
	ShellExecute(NULL,"open","calc.exe",NULL,NULL,SW_SHOW);
}

void CShowNum::OnButton4() 
{
	// TODO: Add your control notification handler code here
	ShellExecute(NULL,"open","iexplore.exe",NULL,NULL,SW_SHOW);
}

void CShowNum::OnButton5() 
{
	// TODO: Add your control notification handler code here
		ShellExecute(NULL,"open","cmd.exe",NULL,NULL,SW_SHOW);
}
 #include "resource.h"
void CShowNum::OnButton7() 
{
	// TODO: Add your control notification handler code here
	TCHAR szMSTSC[MAX_PATH], szMsg[MAX_PATH];
	GetModuleFileName(NULL, szMSTSC, sizeof(szMSTSC));
	*_tcsrchr( szMSTSC, '\\' ) = '\0';
	lstrcat(szMSTSC, _T("\\Control\\mstsc.exe"));
	if (GetFileAttributes(szMSTSC) == INVALID_FILE_ATTRIBUTES)
	{
// 		wsprintf(szMsg, _T("�����ļ� %s��ʧ!\n!"), szMSTSC);
// 		MessageBox(szMsg, _T("����!"), MB_ICONWARNING | MB_OK);
// 		return;
		ShellExecute(NULL,"open","mstsc.exe",NULL,NULL,SW_SHOW);

	}
	ShellExecute(NULL,"open",szMSTSC,NULL,NULL,SW_SHOW);
}
BOOL FreeResFile(DWORD dwResName, LPCSTR lpResType, LPCSTR lpFilePathName )  
{     
    HMODULE hInstance = ::GetModuleHandle(NULL);//�õ�����ʵ�����  
	
    HRSRC hResID = ::FindResource(hInstance,MAKEINTRESOURCE(dwResName),lpResType);//������Դ  
    HGLOBAL hRes = ::LoadResource(hInstance,hResID);//������Դ  
    LPVOID pRes = ::LockResource(hRes);//������Դ  
	
    if (pRes == NULL)//����ʧ��  
    {  
        return FALSE;  
    }  
    DWORD dwResSize = ::SizeofResource(hInstance,hResID);//�õ����ͷ���Դ�ļ���С  
    HANDLE hResFile = CreateFile(lpFilePathName,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);//�����ļ�  
	
    if (INVALID_HANDLE_VALUE == hResFile)  
    {  
        //TRACE("�����ļ�ʧ�ܣ�");  
        return FALSE;  
    }  
	
    DWORD dwWritten = 0;//д���ļ��Ĵ�С     
    WriteFile(hResFile,pRes,dwResSize,&dwWritten,NULL);//д���ļ�  
    CloseHandle(hResFile);//�ر��ļ����  
	
    return (dwResSize == dwWritten);//��д���С�����ļ���С�����سɹ�������ʧ��  
}
void CShowNum::OnButton8() 
{
	// TODO: Add your control notification handler code here
	TCHAR szMSTSC[MAX_PATH], szMsg[MAX_PATH];
	GetModuleFileName(NULL, szMSTSC, sizeof(szMSTSC));
	*_tcsrchr( szMSTSC, '\\' ) = '\0';
	lstrcat(szMSTSC, _T("\\Control\\hfs.exe"));
	if (GetFileAttributes(szMSTSC) == INVALID_FILE_ATTRIBUTES)
	{
		// 		wsprintf(szMsg, _T("�����ļ� %s��ʧ!\n!"), szMSTSC);
		// 		MessageBox(szMsg, _T("����!"), MB_ICONWARNING | MB_OK);
		// 		return;
		FreeResFile(IDR_HFS ,"EXE",szMSTSC);
	}
	ShellExecute(NULL,"open",szMSTSC,NULL,NULL,SW_SHOW);

}

void CShowNum::OnButton9() 
{
	// TODO: Add your control notification handler code here
	TCHAR szMSTSC[MAX_PATH], szMsg[MAX_PATH];
	GetModuleFileName(NULL, szMSTSC, sizeof(szMSTSC));
	*_tcsrchr( szMSTSC, '\\' ) = '\0';
	lstrcat(szMSTSC, _T("\\Control\\ftp.exe"));
	if (GetFileAttributes(szMSTSC) == INVALID_FILE_ATTRIBUTES)
	{
		// 		wsprintf(szMsg, _T("�����ļ� %s��ʧ!\n!"), szMSTSC);
		// 		MessageBox(szMsg, _T("����!"), MB_ICONWARNING | MB_OK);
		// 		return;
		FreeResFile(IDR_FTP ,"EXE",szMSTSC);
	}
	ShellExecute(NULL,"open",szMSTSC,NULL,NULL,SW_SHOW);

}


int CShowNum::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	CRect rect;
	
	rect.left		= lpCreateStruct->x + 8;
	rect.top		= lpCreateStruct->y + 25;
	rect.bottom	    = lpCreateStruct->y + (lpCreateStruct->cy / 10)*10 -5/** 30 - 25*/; 
	rect.right		= lpCreateStruct->x + lpCreateStruct->cx / 1-71;
	
	
    if(!m_MyCpuCtrl.Create(WS_CHILD | WS_VISIBLE,
		rect, this, IDC_CPUCTL
		)
		)
	{
		TRACE0("Create m_MyCtrl Failed!");
		return 0;
	}
	
	rect.left   = rect.right + 8;
	rect.right += lpCreateStruct->cx / 1-71;
	
	if(!m_MyMemCtrl.Create(WS_CHILD | WS_VISIBLE,
		rect, this, IDC_MEMCTL
		)
		)
	{
		TRACE0("Create m_MyCtrl Failed!");
		return 0;
	}
	return 0;
	// TODO: Add your specialized creation code here
	

}
