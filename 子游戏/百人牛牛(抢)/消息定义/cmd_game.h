#ifndef CMD_GAME_HEAD_FILE
#define CMD_GAME_HEAD_FILE

#pragma pack(1)

#define UR_GAME_CONTROL					0x20000000L				//��Ϸ�������
//////////////////////////////////////////////////////////////////////////////////
//������

//��Ϸ����
#define KIND_ID						104									//��Ϸ I D
#define GAME_NAME					TEXT("����ţţ")					//��Ϸ����

//�������
#define GAME_PLAYER					MAX_CHAIR									//��Ϸ����
#define VERSION_SERVER				PROCESS_VERSION(7,0,1)				//����汾
#define VERSION_CLIENT				PROCESS_VERSION(7,0,1)				//����汾

//////////////////////////////////////////////////////////////////////////////////
//״̬����

#define GAME_SCENE_FREE				GAME_STATUS_FREE					//�ȴ���ʼ
#define GAME_SCENE_PLACE_JETTON		GAME_STATUS_PLAY					//��ע״̬
#define GAME_SCENE_GAME_END			GAME_STATUS_PLAY+1					//����״̬


//��������
#define ID_TIAN_MEN					1									//��
#define ID_DI_MEN					2									//��
#define ID_XUAN_MEN					3									//��
#define ID_HUANG_MEN				4									//��

//�������
#define BANKER_INDEX				0									//ׯ������
#define SHUN_MEN_INDEX				1									//˳������
#define DUI_MEN_INDEX				2									//��������
#define DAO_MEN_INDEX				3									//��������
#define HUAN_MEN_INDEX				4									//��������
#define MAX_INDEX					3									//�������

#define AREA_COUNT					4									//������Ŀ
#define CONTROL_AREA				4

//���ʶ���
#define RATE_TWO_PAIR				12									//��������
#define SERVER_LEN					32									//���䳤��

//ռ��
#define SEAT_LEFT1_INDEX			0									//��һ
#define SEAT_LEFT2_INDEX			1									//���
#define SEAT_LEFT3_INDEX			2									//����
#define SEAT_RIGHT1_INDEX			3									//��һ
#define SEAT_RIGHT2_INDEX			4									//�Ҷ�
#define SEAT_RIGHT3_INDEX			5									//����
#define MAX_OCCUPY_SEAT_COUNT		6									//���ռλ����
#define SEAT_INVALID_INDEX			7									//��Ч����

////////////////////////////////////////////////////////////////////////////////////
//�궨��
#ifndef _UNICODE
#define myprintf	_snprintf
#define mystrcpy	strcpy
#define mystrlen	strlen
#define myscanf		_snscanf
#define	myLPSTR		LPCSTR
#else
#define myprintf	swprintf
#define mystrcpy	wcscpy
#define mystrlen	wcslen
#define myscanf		_snwscanf
#define	myLPSTR		LPWSTR
#endif

//������ׯ
///////////////////////////////

//������ׯ����
typedef enum
{
	SUPERBANKER_VIPTYPE,
	SUPERBANKER_CONSUMETYPE
}SUPERBANKERTYPE;

//ռλ����
typedef enum
{
	OCCUPYSEAT_VIPTYPE,
	OCCUPYSEAT_CONSUMETYPE,
	OCCUPYSEAT_FREETYPE
}OCCUPYSEATTYPE;

typedef enum
{
	VIP1_INDEX = 1,  //cbMemberOrder = 1 �����Ա
	VIP2_INDEX,		 //�����Ա
	VIP3_INDEX,		 //�����Ա
	VIP4_INDEX,		 //�����Ա
	VIP5_INDEX,		 //VIP��Ա
	VIP_INVALID		 //��Ч
}VIPINDEX;

typedef struct
{
	SUPERBANKERTYPE		superbankerType;		//��ׯ����
	VIPINDEX			enVipIndex;				//VIP����
	SCORE				lSuperBankerConsume;	//��ׯ����
}SUPERBANKERCONFIG;

typedef struct
{
	OCCUPYSEATTYPE		occupyseatType;			//ռλ����
	VIPINDEX			enVipIndex;				//VIP����
	SCORE				lOccupySeatConsume;	    //ռλ����
	SCORE				lOccupySeatFree;	    //���ռλ�������
	SCORE				lForceStandUpCondition;	//ǿ��վ������
}OCCUPYSEATCONFIG;

typedef enum
{
	ORDINARY_BANKER,		//��ͨׯ��
	SUPERROB_BANKER,		//������ׯׯ��
	INVALID_SYSBANKER		//��Ч����(ϵͳׯ��)
}CURRENT_BANKER_TYPE;

/////////////////////////////////////////

struct tagCustomAndroid
{
	//��ׯ
	bool							nEnableRobotBanker;				//�Ƿ���ׯ
	LONGLONG						lRobotBankerCountMin;			//��ׯ����
	LONGLONG						lRobotBankerCountMax;			//��ׯ����
	LONGLONG						lRobotListMinCount;				//�б�����
	LONGLONG						lRobotListMaxCount;				//�б�����
	LONGLONG						lRobotApplyBanker;				//����������
	LONGLONG						lRobotWaitBanker;				//��������

	//��ע
	LONGLONG						lRobotMinBetTime;				//��ע�������
	LONGLONG						lRobotMaxBetTime;				//��ע�������
	LONGLONG						lRobotMinJetton;				//��ע������
	LONGLONG						lRobotMaxJetton;				//��ע������
	LONGLONG						lRobotBetMinCount;				//��ע��������
	LONGLONG						lRobotBetMaxCount;				//��ע��������
	LONGLONG						lRobotAreaLimit;				//��������

	//��ȡ��
	LONGLONG						lRobotScoreMin;					//�������
	LONGLONG						lRobotScoreMax;					//�������
	LONGLONG						lRobotBankGetMin;				//ȡ����Сֵ(��ׯ)
	LONGLONG						lRobotBankGetMax;				//ȡ�����ֵ(��ׯ)
	LONGLONG						lRobotBankGetBankerMin;			//ȡ����Сֵ(��ׯ)
	LONGLONG						lRobotBankGetBankerMax;			//ȡ�����ֵ(��ׯ)
	LONGLONG						lRobotBankStoMul;				//���ٷֱ�

	//���캯��
	tagCustomAndroid()
	{
		DefaultCustomRule();
	}

	void DefaultCustomRule()
	{
		nEnableRobotBanker = true;
		lRobotBankerCountMin = 5;
		lRobotBankerCountMax = 10;
		lRobotListMinCount = 2;
		lRobotListMaxCount = 5;
		lRobotApplyBanker = 5;
		lRobotWaitBanker = 3;

		lRobotMinBetTime = 6;
		lRobotMaxBetTime = 8;
		lRobotMinJetton = 100;
		lRobotMaxJetton = 5000000;
		lRobotBetMinCount = 4;
		lRobotBetMaxCount = 8;
		lRobotAreaLimit = 10000000;
		
		lRobotScoreMin = 1000000;
		lRobotScoreMax = 100000000;
		lRobotBankGetMin = 100;
		lRobotBankGetMax = 30000000;
		lRobotBankGetBankerMin = 10000000;
		lRobotBankGetBankerMax = 50000000;
		lRobotBankStoMul = 50;
	}
};

//��������Ϣ
struct tagRobotInfo
{
	int nChip[8];														//���붨��
	int nAreaChance[AREA_COUNT];										//������
	TCHAR szCfgFileName[MAX_PATH];										//�����ļ�
	int	nMaxTime;														//�������

	tagRobotInfo()
	{
		int nTmpChip[8] = {100, 1000, 10000, 50000, 100000, 500000, 1000000, 5000000};
		int nTmpAreaChance[AREA_COUNT] = {1, 1, 1, 1};

		nMaxTime = 10;
		memcpy(nChip, nTmpChip, sizeof(nChip));
		memcpy(nAreaChance, nTmpAreaChance, sizeof(nAreaChance));
	}
};

//��¼��Ϣ
struct tagServerGameRecord
{
	bool							bWinShunMen;						//˳��ʤ��
	bool							bWinDuiMen;							//����ʤ��
	bool							bWinDaoMen;							//����ʤ��
	bool							bWinHuang;							//����ʤ��
};

//��ע��Ϣ
struct tagUserBet
{
	TCHAR							szNickName[32];						//�û��ǳ�
	DWORD							dwUserGameID;						//�û�ID
	LONGLONG						lUserStartScore;					//�û����
	LONGLONG						lUserWinLost;						//�û����
	LONGLONG						lUserBet[AREA_COUNT+1];				//�û���ע
};

//��ע��Ϣ����
typedef CWHArray<tagUserBet,tagUserBet&> CUserBetArray;

//������
#define RQ_REFRESH_STORAGE		1
#define RQ_SET_STORAGE			2
//////////////////////////////////////////////////////////////////////////
//����������ṹ

#define SUB_S_GAME_FREE				99									//��Ϸ����
#define SUB_S_GAME_START			100									//��Ϸ��ʼ
#define SUB_S_PLACE_JETTON			101									//�û���ע
#define SUB_S_GAME_END				102									//��Ϸ����
#define SUB_S_APPLY_BANKER			103									//����ׯ��
#define SUB_S_CHANGE_BANKER			104									//�л�ׯ��
#define SUB_S_CHANGE_USER_SCORE		105									//���»���
#define SUB_S_SEND_RECORD			106									//��Ϸ��¼
#define SUB_S_PLACE_JETTON_FAIL		107									//��עʧ��
#define SUB_S_CANCEL_BANKER			108									//ȡ������


#define SUB_S_AMDIN_COMMAND			110									//����Ա����
#define SUB_S_UPDATE_STORAGE        111									//���¿��
#define SUB_S_SEND_USER_BET_INFO    112									//������ע
#define SUB_S_ADVANCE_OPENCARD		113									//��ǰ����

#define SUB_S_SUPERROB_BANKER		114									//������ׯ
#define SUB_S_CURSUPERROB_LEAVE		115									//������ׯ����뿪
#define SUB_S_OCCUPYSEAT			116									//ռλ
#define SUB_S_OCCUPYSEAT_FAIL		117									//ռλʧ��
#define SUB_S_UPDATE_OCCUPYSEAT		118									//����ռλ

//������ׯ
struct CMD_S_SuperRobBanker
{
	bool					bSucceed;
	WORD					wApplySuperRobUser;
	WORD					wCurSuperRobBankerUser;
};

//������ׯ����뿪
struct CMD_S_CurSuperRobLeave
{
	WORD					wCurSuperRobBankerUser;
};


//���¿��
struct CMD_S_UpdateStorage
{
	BYTE                            cbReqType;						//��������
	LONGLONG						lStorageStart;				//��ʼ���
	LONGLONG						lStorageDeduct;				//���˥��
	LONGLONG						lStorageCurrent;				//��ǰ���
	LONGLONG						lStorageMax1;					//�������1
	LONGLONG						lStorageMul1;					//ϵͳ��ָ���1
	LONGLONG						lStorageMax2;					//�������2
	LONGLONG						lStorageMul2;					//ϵͳ��ָ���2
};

//������ע
struct CMD_S_SendUserBetInfo
{
	LONGLONG						lUserStartScore[GAME_PLAYER];				//��ʼ����
	LONGLONG						lUserJettonScore[AREA_COUNT+1][GAME_PLAYER];//������ע
};

//����ظ�
struct CMD_S_CommandResult
{
	BYTE cbAckType;					//�ظ�����
#define ACK_SET_WIN_AREA  1
#define ACK_PRINT_SYN     2
#define ACK_RESET_CONTROL 3
	BYTE cbResult;
#define CR_ACCEPT  2			//����
#define CR_REFUSAL 3			//�ܾ�
	BYTE cbExtendData[20];			//��������
};
//ʧ�ܽṹ
struct CMD_S_PlaceJettonFail
{
	WORD							wPlaceUser;							//��ע���
	BYTE							lJettonArea;						//��ע����
	LONGLONG						lPlaceScore;						//��ǰ��ע
};

//���»���
struct CMD_S_ChangeUserScore
{
	WORD							wChairID;							//���Ӻ���
	DOUBLE							lScore;								//��һ���

	//ׯ����Ϣ
	WORD							wCurrentBankerChairID;				//��ǰׯ��
	BYTE							cbBankerTime;						//ׯ�Ҿ���
	DOUBLE							lCurrentBankerScore;				//ׯ�ҷ���
};

//����ׯ��
struct CMD_S_ApplyBanker
{
	WORD							wApplyUser;							//�������
};

//ȡ������
struct CMD_S_CancelBanker
{
	WORD							wCancelUser;					//ȡ�����
};

//�л�ׯ��
struct CMD_S_ChangeBanker
{
	WORD							wBankerUser;						//��ׯ���
	LONGLONG						lBankerScore;						//ׯ�ҽ��
	CURRENT_BANKER_TYPE				typeCurrentBanker;					//��ǰׯ������
};

//��Ϸ״̬
struct CMD_S_StatusFree
{
	//ȫ����Ϣ
	BYTE							cbTimeLeave;						//ʣ��ʱ��

	//�����Ϣ
	LONGLONG						lUserMaxScore;						//��ҽ��

	//ׯ����Ϣ
	WORD							wBankerUser;						//��ǰׯ��
	WORD							cbBankerTime;						//ׯ�Ҿ���
	LONGLONG						lBankerWinScore;					//ׯ�ҳɼ�
	LONGLONG						lBankerScore;						//ׯ�ҷ���
	INT								nEndGameMul;						//��ǰ���ưٷֱ�
	bool							bEnableSysBanker;					//ϵͳ��ׯ

	//������Ϣ
	LONGLONG						lApplyBankerCondition;				//��������
	LONGLONG						lAreaLimitScore;					//��������

	//������Ϣ
	TCHAR							szGameRoomName[SERVER_LEN];			//��������
	bool							bGenreEducate;						//��ϰģʽ
	
	SUPERBANKERCONFIG				superbankerConfig;					//��ׯ����
	WORD							wCurSuperRobBankerUser;
	CURRENT_BANKER_TYPE				typeCurrentBanker;					//��ǰׯ������

	OCCUPYSEATCONFIG				occupyseatConfig;							//ռλ����
	WORD							wOccupySeatChairIDArray[MAX_OCCUPY_SEAT_COUNT];	//ռλ����ID

	tagCustomAndroid				CustomAndroid;						//����������
};

//��Ϸ״̬
struct CMD_S_StatusPlay
{
	//ȫ����ע
	LONGLONG						lAllJettonScore[AREA_COUNT+1];		//ȫ����ע

	//�����ע
	LONGLONG						lUserJettonScore[AREA_COUNT+1];		//������ע

	//��һ���
	LONGLONG						lUserMaxScore;						//�����ע							

	//������Ϣ
	LONGLONG						lApplyBankerCondition;				//��������
	LONGLONG						lAreaLimitScore;					//��������

	//�˿���Ϣ
	BYTE							cbTableCardArray[5][5];				//�����˿�

	//ׯ����Ϣ
	WORD							wBankerUser;						//��ǰׯ��
	WORD							cbBankerTime;						//ׯ�Ҿ���
	LONGLONG						lBankerWinScore;					//ׯ��Ӯ��
	LONGLONG						lBankerScore;						//ׯ�ҷ���
	INT								nEndGameMul;						//��ǰ���ưٷֱ�
	bool							bEnableSysBanker;					//ϵͳ��ׯ

	//������Ϣ
	LONGLONG						lEndBankerScore;					//ׯ�ҳɼ�
	LONGLONG						lEndUserScore;						//��ҳɼ�
	LONGLONG						lEndUserReturnScore;				//���ػ���
	LONGLONG						lEndRevenue;						//��Ϸ˰��

	//ȫ����Ϣ
	BYTE							cbTimeLeave;						//ʣ��ʱ��
	BYTE							cbGameStatus;						//��Ϸ״̬

	//������Ϣ
	TCHAR							szGameRoomName[SERVER_LEN];			//��������
	bool							bGenreEducate;						//��ϰģʽ
	
	SUPERBANKERCONFIG				superbankerConfig;					//��ׯ����
	WORD							wCurSuperRobBankerUser;
	CURRENT_BANKER_TYPE				typeCurrentBanker;					//��ǰׯ������

	OCCUPYSEATCONFIG				occupyseatConfig;							//ռλ����
	WORD							wOccupySeatChairIDArray[MAX_OCCUPY_SEAT_COUNT];	//ռλ����ID

	LONGLONG						lOccupySeatUserWinScore[MAX_OCCUPY_SEAT_COUNT];	//ռλ��ҳɼ�

	tagCustomAndroid				CustomAndroid;						//����������
};

//��Ϸ����
struct CMD_S_GameFree
{
	BYTE							cbTimeLeave;						//ʣ��ʱ��
	INT64                           nListUserCount;						//�б�����
	LONGLONG						lStorageStart;						//
};

//��Ϸ��ʼ
struct CMD_S_GameStart
{
	WORD							wBankerUser;						//ׯ��λ��
	LONGLONG						lBankerScore;						//ׯ�ҽ��
	LONGLONG						lUserMaxScore;						//�ҵĽ��
	BYTE							cbTimeLeave;						//ʣ��ʱ��	
	bool							bContiueCard;						//��������
	int								nChipRobotCount;					//�������� (��ע������)
	int								nAndriodApplyCount;					//�������б�����

	TCHAR							szServerName[LEN_SERVER];			//��������
};

//�û���ע
struct CMD_S_PlaceJetton
{
	WORD							wChairID;							//�û�λ��
	BYTE							cbJettonArea;						//��������
	LONGLONG						lJettonScore;						//��ע��Ŀ
	bool							bIsAndroid;							//�Ƿ������
	bool							bAndroid;						//������ʶ
};

//��Ϸ����
struct CMD_S_GameEnd
{
	//�¾���Ϣ
	BYTE							cbTimeLeave;						//ʣ��ʱ��

	//�˿���Ϣ
	BYTE							cbTableCardArray[5][5];				//�����˿�
	BYTE							cbLeftCardCount;					//�˿���Ŀ

	BYTE							bcFirstCard;

	//ׯ����Ϣ
	LONGLONG						lBankerScore;						//ׯ�ҳɼ�
	LONGLONG						lBankerTotallScore;					//ׯ�ҳɼ�
	INT								nBankerTime;						//��ׯ����

	//��ҳɼ�
	LONGLONG						lUserScore;							//��ҳɼ�
	LONGLONG						lUserReturnScore;					//���ػ���

	//ȫ����Ϣ
	LONGLONG						lRevenue;							//��Ϸ˰��

	LONGLONG						lOccupySeatUserWinScore[MAX_OCCUPY_SEAT_COUNT];	//ռλ��ҳɼ�
};

//ռλ
struct CMD_S_OccupySeat
{
	WORD							wOccupySeatChairID;							//����ռλ���ID
	BYTE							cbOccupySeatIndex;							//ռλ����
	WORD							wOccupySeatChairIDArray[MAX_OCCUPY_SEAT_COUNT];	//ռλ����ID
};

//ռλʧ��
struct CMD_S_OccupySeat_Fail
{
	WORD							wAlreadyOccupySeatChairID;					//������ռλ���ID
	BYTE							cbAlreadyOccupySeatIndex;					//��ռλ����
	WORD							wOccupySeatChairIDArray[MAX_OCCUPY_SEAT_COUNT];	//ռλ����ID
};

//����ռλ
struct CMD_S_UpdateOccupySeat
{
	WORD							wOccupySeatChairIDArray[MAX_OCCUPY_SEAT_COUNT];	//ռλ����ID
	WORD							wQuitOccupySeatChairID;						//�����˳�ռλ���
};

//////////////////////////////////////////////////////////////////////////
//�ͻ�������ṹ

#define SUB_C_PLACE_JETTON			1									//�û���ע
#define SUB_C_APPLY_BANKER			2									//����ׯ��
#define SUB_C_CANCEL_BANKER			3									//ȡ������
#define SUB_C_CONTINUE_CARD			4									//��������
#define SUB_C_AMDIN_COMMAND			5									//����Ա����
#define SUB_C_UPDATE_STORAGE        6									//���¿��

#define SUB_C_SUPERROB_BANKER		7									//������ׯ
#define SUB_C_OCCUPYSEAT			8									//ռλ
#define SUB_C_QUIT_OCCUPYSEAT		9									//�˳�ռλ


//�ͻ�����Ϣ
#define IDM_ADMIN_COMMDN			WM_USER+1000
#define IDM_UPDATE_STORAGE			WM_USER+1001

//����������Ϣ
struct tagControlInfo
{
	BYTE cbControlArea[MAX_INDEX];			//��������
};

struct tagAdminReq
{
	BYTE							m_cbExcuteTimes;					//ִ�д���
	BYTE							m_cbControlStyle;					//���Ʒ�ʽ
#define		CS_BANKER_LOSE    1
#define		CS_BANKER_WIN	  2
#define		CS_BET_AREA		  3
	bool							m_bWinArea[3];						//Ӯ������
};


struct CMD_C_AdminReq
{
	BYTE cbReqType;
#define RQ_SET_WIN_AREA		1
#define RQ_RESET_CONTROL	2
#define RQ_PRINT_SYN		3
	BYTE cbExtendData[20];			//��������
};
//�û���ע
struct CMD_C_PlaceJetton
{
	BYTE							cbJettonArea;						//��������
	LONGLONG						lJettonScore;						//��ע��Ŀ
};

//���¿��
struct CMD_C_UpdateStorage
{
	BYTE                            cbReqType;						//��������
	LONGLONG						lStorageDeduct;					//���˥��
	LONGLONG						lStorageCurrent;				//��ǰ���
	LONGLONG						lStorageMax1;					//�������1
	LONGLONG						lStorageMul1;					//ϵͳ��ָ���1
	LONGLONG						lStorageMax2;					//�������2
	LONGLONG						lStorageMul2;					//ϵͳ��ָ���2
};

//ռλ
struct CMD_C_OccupySeat
{
	WORD							wOccupySeatChairID;				//ռλ���
	BYTE							cbOccupySeatIndex;				//ռλ����
};

//////////////////////////////////////////////////////////////////////////
#pragma pack()
#endif