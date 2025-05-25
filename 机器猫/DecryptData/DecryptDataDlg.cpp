// DecryptDataDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DecryptData.h"
#include "DecryptDataDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDecryptDataDlg dialog

CDecryptDataDlg::CDecryptDataDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDecryptDataDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDecryptDataDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDecryptDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDecryptDataDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDecryptDataDlg, CDialog)
	//{{AFX_MSG_MAP(CDecryptDataDlg)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK1, OnOk1)
	ON_BN_CLICKED(IDOK2, OnOk2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDecryptDataDlg message handlers
///��ɫ��ʾ
void CDecryptDataDlg::LogOut(LPCSTR outtext)
{
	int length = m_edit_log.GetWindowTextLength();
	m_edit_log.SetSel(length, length);
	m_edit_log.ReplaceSel (outtext); 
}
HBRUSH CDecryptDataDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	int nCtrlID = pWnd->GetDlgCtrlID();
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if ((nCtrlID == IDC_EDIT1) ||(nCtrlID == IDC_EDIT2)&& (nCtlColor == CTLCOLOR_EDIT))
	{
		COLORREF clr = RGB(0,255,0);
		pDC->SetTextColor(clr); //������ɫ���ı�
		clr = RGB(0,0,0);
		pDC->SetBkColor(clr); //���ú�ɫ�ı���
		hbr = CreateSolidBrush(clr); //��ΪԼ�������ر���ɫ��Ӧ��ˢ�Ӿ��
	}
	return hbr;
}
BOOL CDecryptDataDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	SetDlgItemText(IDC_EDIT2,"1024");
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDecryptDataDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CDecryptDataDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//�����ַ���
void DecryptData(char *szRec, unsigned long nLen, unsigned long key)
{
	unsigned long i;
	unsigned char p;
	p = (unsigned char ) key % 1451 + 61;
	
	for(i = 0; i < nLen; i++)
	{
		*szRec -= p;
		*szRec++ ^= p;
	}
}
//�����ַ���
void EncryptData(char*szRec, unsigned long nLen, unsigned long key) //���ܲ��
{
	unsigned long i;
	unsigned char p;
	p = (unsigned char ) key % 1451 + 61;
	for(i = 0; i < nLen; i++)
	{
		*szRec ^= p;
		*szRec += p;
		szRec++;
	}
}
void CDecryptDataDlg::OnOk1() 
{
	CString cstr;
	GetDlgItem(IDC_EDIT1)->GetWindowText(cstr); //��ȡ�༭��Ҫ���ܵ�����
	CString strText(_T(""));
	GetDlgItemText(IDC_EDIT2, strText);
	short val2 = _ttoi(strText); //��ȡ�༭��keyת������
	const char* ch = (LPCTSTR)cstr;  //CStringתchar
	DecryptData((char *)ch,strlen(ch),val2); //����
	SetDlgItemText(IDC_EDIT1,ch); //��ʾ��������
	DWORD nr = strlen(ch);
	if (nr == 0)
		SetDlgItemText(IDC_STATIC1,"������Ҫ���ܵ�����...");
	else
		SetDlgItemText(IDC_STATIC1,"���ܳɹ�...");
}

void CDecryptDataDlg::OnOk2() 
{
	CString cstr;
	GetDlgItem(IDC_EDIT1)->GetWindowText(cstr);
	CString strText(_T(""));    
	GetDlgItemText(IDC_EDIT2, strText);
	short val2 = _ttoi(strText);
	const char* ch = (LPCTSTR)cstr;
	EncryptData((char*)ch,strlen(ch),val2);
	SetDlgItemText(IDC_EDIT1,ch);
	DWORD nr = strlen(ch);
	if (nr == 0)
		SetDlgItemText(IDC_STATIC1,"������Ҫ���ܵ�����...");
	else
		SetDlgItemText(IDC_STATIC1,"���ܳɹ�...");
}
