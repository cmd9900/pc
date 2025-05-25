// FaderWnd.cpp : implementation file
//CFaderWnd��Ϊ͸�����ڵĽӿ���,��ʵ�ֵ�ԭ����:
//�ȴ�Ҫʵ��͸���Ĵ��ڵõ�������ָ��,��Ϊ��������CFaderWnd��
//CFaderWnd��õ�����ָ�����,����һ���͵õ��Ĵ���ָ��������ƵĴ���
//�����Ĵ������б���ָ��WS_EX_LAYERED(0x00080000)��WS_EX_TOPMOST��ʽ
//ͨ��WS_EX_TOPMOST��ʽ������,����ǰ�����Ĵ�����Ϊ�ֲ㴰�ڵ��ϲ㴰��
//�ڴ����ṹ����CFaderWnd()����һ��ʱ����
//ͨ������UpdateLayeredWindow()�������·ֲ㴰�ڵ�͸����
//ͨ��ʱ����������,ÿ��һ����ʱ��ͽ�͸���Ƚ���,����������͸��,ʵ�ִ��ڵĽ�������
//�����õ�ʱ�����˺�,�ϲ㴰���Ѿ�͸��,���ʱ��ͽ��²㴰��(Ҳ����Ҫʵ�ֽ����Ĵ���)�رջ���������
//���÷���:
//�����Ϊ�����Ĵ���ʵ�ַ���:
//new CFaderWnd(this);
//ShowWindow(WS_HIDE);
//һ����ĵ���Ĵ���(��CAboutDlg��)ʵ�ַ���:
//new CFaderWnd(this);
//EndDialog(ID);

#include "stdafx.h"
//#include "FaderWndTest.h"
#include "FaderWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFaderWnd

CFaderWnd::CFaderWnd(CWnd*pWndToFader/*=NULL*/,UINT nFaderTime/*=2000*/,BYTE ALPHA/*=255*/)
:m_pWndToFader(pWndToFader)//m_pWndtoFader��ָ��������ǽ�Ҫʵ�ֽ����Ĵ����ڵ�ǰ������ϵ����
{
	//������ĺϷ���,ֻ���ڵ��԰汾������,���а汾��û����
	ASSERT(pWndToFader);
	ASSERT_VALID(pWndToFader);
	//�õ��Ϸ���ALPHAֵ�����ȱʡ��ֵ
	if(ALPHA<5)  return;
	//����UpdateLayeredWindow()������user32.dll
	HMODULE m_hInstUser32=GetModuleHandle("user32.dll");
    m_lpfunUpdateLayeredWnd=(lpUpdateLayeredWindow)GetProcAddress(m_hInstUser32,"UpdateLayeredWindow");
	if(m_hInstUser32==NULL)
	{
		if(m_lpfunUpdateLayeredWnd==NULL)
		{
			AfxMessageBox("���ܼ���user32.dll��UpdateLayeredWindow()����������!!");
		     delete this ;
		}
	}
	else
	{
		//�����ֲ㴰��
		CPoint point(0,0);//��ʼ�������
		SIZE   size;
		CRect  pWndToFaderRect;
		//�õ����󴰿ڵľ�������
	    m_pWndToFader->GetWindowRect(&pWndToFaderRect);
		//�õ����ڵĶ�������
        size.cx=pWndToFaderRect.Width();
		size.cy=pWndToFaderRect.Height();
		point=pWndToFaderRect.TopLeft();
		//�����ֲ㴰�ڵ��ϲ㴰��
		//��ʽWS_EX_LAYERED��ҪҪ,��Ϊ��ΪUpdateLayeredWindow()�����ĵ���
		//WS_EX_TRANSPARENT allows mouse clicks through to the window "underneath",
		CreateEx(WS_EX_LAYERED|WS_EX_TOOLWINDOW|WS_EX_TOPMOST|WS_EX_TRANSPARENT,
			"STATIC","",WS_VISIBLE|WS_POPUP,pWndToFaderRect,AfxGetMainWnd(),0); 
		//����BLENDFUNCTION�ṹ��ΪUpdateLayeredWindow()����
        m_Blend.BlendOp=AC_SRC_OVER;  //Ψһ������־
		m_Blend.BlendFlags=0;
		m_Blend.SourceConstantAlpha=ALPHA; //�����ʼʱ���͸����
		m_Blend.AlphaFormat=0;
		//��Ƴ�ʼʱ��ķֲ㴰�ڵ�͸����
        m_lpfunUpdateLayeredWnd(GetSafeHwnd(),NULL,NULL,&size,::GetDC(m_pWndToFader->GetSafeHwnd()),&point,0,&m_Blend, 0x00000002);
		//���ý������ڵ�ʱ����
		UINT nFaderTimeUnit=nFaderTime/(ALPHA/5);//���嵥λʱ����
		SetTimer(FaderWndTimer,nFaderTimeUnit,NULL);

	}
}

CFaderWnd::~CFaderWnd()
{
}


BEGIN_MESSAGE_MAP(CFaderWnd, CWnd)
	//{{AFX_MSG_MAP(CFaderWnd)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CFaderWnd message handlers

void CFaderWnd::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent== FaderWndTimer)
	{
		//���Ǵ��ڵĽ���ʱ�����Ļ�
		if(m_Blend.SourceConstantAlpha>=5)
		{
			//͸���ȱ�����ڻ����5,����Ļ�͸���ȼ��ٵ�����ʱ�ִ�Ĭ�ϵ�ֵ��ʼ,�ﲻ��͸����Ч��
         m_Blend.SourceConstantAlpha-=5; //�𽥼���͸����,��������͸��
		 //���·ֲ㴰�ڵ�͸���̶�
         m_lpfunUpdateLayeredWnd(GetSafeHwnd(),NULL,NULL,NULL,NULL,NULL,NULL,&m_Blend,  0x00000002);
		}
		else
		{
			KillTimer(FaderWndTimer);//���ٴ���ʱ����
			DestroyWindow();//���ٴ���
		}
	}
//	CWnd::OnTimer(nIDEvent);
}


