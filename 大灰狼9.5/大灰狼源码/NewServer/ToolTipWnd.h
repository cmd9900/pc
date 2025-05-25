#if !defined(AFX_TOOLTIPWND_H__2C52D3E4_2F5B_11D2_8FC9_000000000000__INCLUDED_)
#define AFX_TOOLTIPWND_H__2C52D3E4_2F5B_11D2_8FC9_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// ToolTipWnd.h : header file
//
// ���ߣ���ǿ��
// Email:kuge3907@sina.com
// �������:2003-3-22
// Copyright (c) 2003.
//���������ʵ��������ʽ:
//1.��ͨ������ʽ
//2.Բ�Ǿ�����ʽ
//3.��Բ��ʽ
//4.������ʽ
//5.������ʽ
//6.������ʽ
/////////////////////////////////////////////////////////////////////////////
// CToolTipWnd window
struct BTOOLINFO {

	HWND	hwndTool;
	CString strToolText;
	COLORREF clrToolTextClr;
};
#define TTWS_RECT      0x00000001 //��ͨ������ʽ
#define TTWS_ROUNDRECT 0x00000002 //Բ�Ǿ�����ʽ
#define TTWS_ELLIPSE   0x00000003 //��Բ��ʽ
#define TTWS_BALLOON   0x00000004 //������ʽ
#define TTWS_NACELLE   0x00000005 //������ʽ
#define TTWS_HEART     0x00000006 //������ʽ
class CToolTipWnd : public CWnd
{

private:
// Construction
	LPCTSTR lpWndCls;
public:
	CToolTipWnd();
	HWND pCurrwnd;//ӵ�е�ǰToolTipWnd�Ĵ���Ĵ��ھ��
	// Attributes
public:
	void RelayEvent(LPMSG);//�¼��ӳ�
	BOOL Create(CWnd*,DWORD);//���崴��
	bool m_bStuck;         //�Ƿ���ʾtooltip����

    BOOL SetTTWStyle(DWORD nStyle);//���ô�����ʽ
	DWORD GetCurrentTTWStyle(){return nCurntTTWStyle;}//�õ���ǰ��ʽ
	void SetCurrentTTWStyle(DWORD nStyle){nCurntTTWStyle=nStyle;}//���õ�ǰ��ʽ

	void AddTool(CWnd *pWnd, CString strText, COLORREF clrTextColor=NULL);
	void SetWidth(int iWidth) { m_iWidth = iWidth; }
	void SetHeight(int iHeight) { m_iHeight = iHeight; }
	void SetBkColor(COLORREF clrRef) { m_clrBkColor = clrRef; }
	void SetFrameColor(COLORREF clrRef) { m_clrFrameColor = clrRef; }
	void SetDefTextColor(COLORREF clrRef) { m_clrTextColor = clrRef; }
	void SetFontHeight(int iHeight) { m_iFontHeight = iHeight; }
	void SetFontName(CString strFontName) { m_strFontName = strFontName; }

    BYTE GetWndAlpha()const{return m_hWndAlpha;}//�õ�����͸����
	void SetWndAlpha(BYTE nWndAlpha){m_hWndAlpha=nWndAlpha;}//����͸���� 
public:
	CRgn rgn;
	CRgn rgnComb;           //�ϲ�������
	CRgn rgnTri;
	CRect m_RectText;       //�ı�����
	CFont m_fontText;       //Ҫ��ʾ���ı�����
	BYTE m_hWndAlpha;       //����͸����(<=255)
	CString m_strText;      //Ҫ��ʾ���ı�
	bool m_bMouseIn;        //����Ƿ���ĳ���ؼ���
	COLORREF m_clrTextColor;//�ı���ɫ
	COLORREF m_clrBkColor;  //������ɫ
	COLORREF m_clrFrameColor;//�߿���ɫ
	CMapPtrToPtr m_ToolPtr;  //ӳ����� 
	int m_iWidth;            //���ڿ��
	int m_iHeight;           //���ڸ߶�
	int m_iFontHeight;       //����߶�
	CString m_strFontName;   //��������
    static DWORD nCurntTTWStyle; //��ǰʹ�õ���ʽ,��ֵֻ���Ƕ������Щ
	HWND m_hParentWnd;       //�����ھ��
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolTipWnd)
	//}}AFX_VIRTUAL
	

// Implementation
public:
	
	virtual ~CToolTipWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CToolTipWnd)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLTIPWND_H__2C52D3E4_2F5B_11D2_8FC9_000000000000__INCLUDED_)
