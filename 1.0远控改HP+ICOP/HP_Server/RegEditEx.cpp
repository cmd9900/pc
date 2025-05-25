//#include <windows.h>
#include "StdAfx.h"

char* DelSpace(char *szData)
{
	int i=0 ;
	while(1)
	{
		if(strnicmp(szData+i," ",1))
			break;
		i++;			
	}
	return (szData+i);
}
//����ע������ȡ��Ȩ��(KEY_READ||KEY_WRITE||KEY_ALL_ACCESS)
int SetKeySecurityEx(HKEY MainKey,LPCTSTR SubKey,DWORD security)
{

	HKEY  hKey;
	SID_IDENTIFIER_AUTHORITY sia = SECURITY_NT_AUTHORITY;
	PSID pSystemSid              = NULL;
	PSID pUserSid                = NULL;
	SECURITY_DESCRIPTOR sd;
	PACL    pDacl                = NULL;
	DWORD   dwAclSize;
	int     iResult              = 0;
	
	__try
	{
		if(RegOpenKeyExA(MainKey, SubKey, 0, WRITE_DAC, &hKey) != ERROR_SUCCESS)
			__leave;
		if(!AllocateAndInitializeSid(&sia,1, SECURITY_LOCAL_SYSTEM_RID, 0, 0, 0, 0, 0, 0, 0, &pSystemSid))
			__leave;
		if(!AllocateAndInitializeSid(&sia, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &pUserSid))
			__leave;
		dwAclSize = sizeof(ACL) + 2 * (sizeof(ACCESS_ALLOWED_ACE) - sizeof(DWORD)) + GetLengthSid(pSystemSid) + GetLengthSid(pUserSid);
		pDacl = (PACL)HeapAlloc(GetProcessHeap(), 0, dwAclSize);
		if(pDacl == NULL)
			__leave;
		if(!InitializeAcl(pDacl, dwAclSize, ACL_REVISION))
			__leave;
		if(!AddAccessAllowedAce(pDacl, ACL_REVISION, KEY_ALL_ACCESS, pSystemSid))
			__leave;
		if(!AddAccessAllowedAce(pDacl, ACL_REVISION, (unsigned long)security, pUserSid))
			__leave;
		if(!InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION))
			__leave;
		if(!SetSecurityDescriptorDacl(&sd, TRUE, pDacl, FALSE))
			__leave;
		if(RegSetKeySecurity(hKey, (SECURITY_INFORMATION)DACL_SECURITY_INFORMATION, &sd) != ERROR_SUCCESS)
			__leave;
		iResult =1;
	}
	__finally
	{
		RegCloseKey(MainKey);
		RegCloseKey(hKey);
		
		if(pDacl != NULL)
			HeapFree(GetProcessHeap(), 0, pDacl);
		if(pSystemSid !=NULL)
			FreeSid(pSystemSid);
		if(pUserSid != NULL)
			FreeSid(pUserSid);
	}
	
	return iResult;
}

//��ȡע����ָ����������(Mode:0-����ֵ���� 1-�����Ӽ� 2-����ָ������ 3-�жϸü��Ƿ����)
int ReadRegEx(HKEY MainKey,LPCTSTR SubKey,LPCTSTR Vname,DWORD Type,char *szData,LPBYTE szBytes,DWORD lbSize,int Mode)
{
    //////////////////////////////////////////////////////////
	//���ַ���"%-24s %-15s %s \r\n"�����������ַ������ӷ���
	char *njOFO1="%-24s %-15", *yryCx2="s %s \r\n",*ddueK3=NULL;
	ddueK3=new char[strlen(njOFO1)+strlen(yryCx2)+1];
	strcpy(ddueK3,njOFO1);//��njOFO1��ָ��NULL�������ַ������Ƶ�ddueK3��ָ��������
	strcat(ddueK3,yryCx2);//��yryCx2��ָ�ַ�����ӵ�ddueK3��β��(����dest��β����'\0')�����'\0'
	//������ʵ����ddueK3=njOFO1+yryCx2,��njOFO1��yryCx2����������
	//////////////////////////////////////////////////////////
	
	//////////////////////////////////////////////////////////
	//���ַ���"%-24s %-15s \r\n"�����������ַ������ӷ���
	char *SAFTd1="%-24s %-", *TZwjC2="15s \r\n",*nNdzb3=NULL;
	nNdzb3=new char[strlen(SAFTd1)+strlen(TZwjC2)+1];
	strcpy(nNdzb3,SAFTd1);//��SAFTd1��ָ��NULL�������ַ������Ƶ�nNdzb3��ָ��������
	strcat(nNdzb3,TZwjC2);//��TZwjC2��ָ�ַ�����ӵ�nNdzb3��β��(����dest��β����'\0')�����'\0'
	//������ʵ����nNdzb3=SAFTd1+TZwjC2,��SAFTd1��TZwjC2����������
	//////////////////////////////////////////////////////////
	
	HKEY   hKey;
	int    ValueDWORD,iResult=0;
	char*  PointStr;
	char   KeyName[32],ValueSz[MAX_PATH],ValueTemp[MAX_PATH];
	DWORD  szSize,KnSize,dwIndex=0;
	
	memset(KeyName,0,sizeof(KeyName));
	memset(ValueSz,0,sizeof(ValueSz));
	memset(ValueTemp,0,sizeof(ValueTemp));
	
	__try
	{
		//SetKeySecurityEx(MainKey,SubKey,KEY_ALL_ACCESS);
		if(RegOpenKeyEx(MainKey,SubKey,0,KEY_READ,&hKey) != ERROR_SUCCESS)
		{
			iResult = -1;
			__leave;
		}
		switch(Mode)
		{
		case 0:
			switch(Type)
			{
			case REG_SZ:
			case REG_EXPAND_SZ:
				szSize = sizeof(ValueSz);
				if(RegQueryValueEx(hKey,Vname,NULL,&Type,(LPBYTE)ValueSz,&szSize) == ERROR_SUCCESS)
				{
					strcpy(szData,DelSpace(ValueSz));
					iResult =1;
				}
				break;
			case REG_MULTI_SZ:
				szSize = sizeof(ValueSz);
				if(RegQueryValueEx(hKey,Vname,NULL,&Type,(LPBYTE)ValueSz,&szSize) == ERROR_SUCCESS)
				{
					for(PointStr = ValueSz; *PointStr; PointStr = strchr(PointStr,0)+1)
					{
						strncat(ValueTemp,PointStr,sizeof(ValueTemp));
						strncat(ValueTemp," ",sizeof(ValueTemp));
					}
					strcpy(szData,ValueTemp);
					iResult =1;
				}
				break;
			case REG_DWORD:
				szSize = sizeof(DWORD);
				if(RegQueryValueEx(hKey,Vname,NULL,&Type,(LPBYTE)&ValueDWORD,&szSize ) == ERROR_SUCCESS)
				{
					wsprintf(szData,"%d",ValueDWORD);
					iResult =1;
				}
				break;
			case REG_BINARY:
				szSize = lbSize;
				if(RegQueryValueEx(hKey,Vname,NULL,&Type,szBytes,&szSize) == ERROR_SUCCESS)
					iResult =1;
				break;
			}
			break;
		case 1:
			while(1)
			{
				memset(ValueSz,0,sizeof(ValueSz));
				szSize   = sizeof(ValueSz);
				if(RegEnumKeyEx(hKey,dwIndex++,ValueSz,&szSize,NULL,NULL,NULL,NULL) != ERROR_SUCCESS)
					break;
				wsprintf(ValueTemp,"[%s]\r\n",ValueSz);
				strcat(szData,ValueTemp);
				iResult =1;
			}
			break;
		case 2:
			while(1)
			{
				memset(KeyName,0,sizeof(KeyName));
				memset(ValueSz,0,sizeof(ValueSz));
				memset(ValueTemp,0,sizeof(ValueTemp));
				KnSize = sizeof(KeyName);
				szSize = sizeof(ValueSz);
				if(RegEnumValue(hKey,dwIndex++,KeyName,&KnSize,NULL,&Type,(LPBYTE)ValueSz,&szSize) != ERROR_SUCCESS)
					break;
				switch(Type)
				{
				case REG_SZ:
					wsprintf(ValueTemp,ddueK3,KeyName,"REG_SZ",ValueSz);
					break;
				case REG_EXPAND_SZ:
					wsprintf(ValueTemp,ddueK3,KeyName,"REG_EXPAND_SZ",ValueSz);
					break;
				case REG_DWORD:
					wsprintf(ValueTemp,"'%','-','2','4','s',' ','%','-','1','5','s',' ','0','x','%','x','(','%','d',')',' ','\','r','\','n','\0",KeyName,"REG_DWORD",ValueSz,int(ValueSz));
					break;
				case REG_MULTI_SZ:
					wsprintf(ValueTemp,nNdzb3,KeyName,"REG_MULTI_SZ");
					break;
				case REG_BINARY:
					wsprintf(ValueTemp,nNdzb3,KeyName,"REG_BINARY");
					break;
				}
				lstrcat(szData,ValueTemp);
				iResult =1;
			}
			break;
		case 3:
			iResult =1;
			break;
		}
	}
	__finally
	{
		RegCloseKey(MainKey);
		RegCloseKey(hKey);
	}
	
	delete[] nNdzb3;
	delete[] ddueK3;
	return iResult;
}

//дע����ָ����������(Mode:0-�½������� 1-���ü����� 2-ɾ��ָ���� 3-ɾ��ָ������)
int WriteRegEx(HKEY MainKey,LPCTSTR SubKey,LPCTSTR Vname,DWORD Type,char* szData,DWORD dwData,int Mode)
{

	HKEY  hKey;
	DWORD dwDisposition;
	int   iResult =0;
	
	__try
	{
		//SetKeySecurityEx(MainKey,Subkey,KEY_ALL_ACCESS);
		switch(Mode)
		{
		case 0:
			if(RegCreateKeyEx(MainKey,SubKey,0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&hKey,&dwDisposition) != ERROR_SUCCESS)
				__leave;
		case 1:
			if(RegOpenKeyEx(MainKey,SubKey,0,KEY_READ|KEY_WRITE,&hKey) != ERROR_SUCCESS)
				__leave;
			switch(Type)
			{
			case REG_SZ:
			case REG_EXPAND_SZ:
				if(RegSetValueEx(hKey,Vname,0,Type,(LPBYTE)szData,strlen(szData)+1) == ERROR_SUCCESS)
					iResult =1;
				break;
			case REG_DWORD:
				if(RegSetValueEx(hKey,Vname,0,Type,(LPBYTE)&dwData,sizeof(DWORD)) == ERROR_SUCCESS)
					iResult =1;
				break;
			case REG_BINARY:
				break;
			}
			break;
		case 2:
			if(RegOpenKeyEx(MainKey,SubKey,NULL,KEY_READ|KEY_WRITE,&hKey) != ERROR_SUCCESS)
				__leave;
			if (RegDeleteKey(hKey,Vname) == ERROR_SUCCESS)
				iResult =1;
			break;
		case 3:
			if(RegOpenKeyEx(MainKey,SubKey,NULL,KEY_READ|KEY_WRITE,&hKey) != ERROR_SUCCESS)
				__leave;
			if (RegDeleteValue(hKey,Vname) == ERROR_SUCCESS)
				iResult =1;
			break;
		}
	}
	__finally
	{
		RegCloseKey(MainKey);
		RegCloseKey(hKey);
	}
	return iResult;
}
