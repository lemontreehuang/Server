#include "StdAfx.h"
#include "TableFrameSink.h"

//////////////////////////////////////////////////////////////////////////

//��̬����
//const WORD			CTableFrameSink::m_wPlayerCount=GAME_PLAYER;			//��Ϸ����
const BYTE			CTableFrameSink::m_GameStartMode=START_MODE_ALL_READY;	//��ʼģʽ
LONGLONG			CTableFrameSink::m_lStockScore=0;						//�������

//��ʱ�� 0~30
#define IDI_GAME_COMPAREEND					1									//������ʱ��
#define IDI_GAME_OPENEND					2									//������ʱ��
#define IDI_ADD_SCORE						3									//������ʱ��

#define TIME_GAME_COMPAREEND				6000								//������ʱ��
#define TIME_GAME_OPENEND					6000								//������ʱ��
#define TIME_ADD_SCORE						1000								//������ʱ��

//////////////////////////////////////////////////////////////////////////

//���캯��
CTableFrameSink::CTableFrameSink()
{
	//��Ϸ����
	m_bOperaCount=0;
	m_wBankerUser=INVALID_CHAIR;
	m_wCurrentUser=INVALID_CHAIR;
	m_lCompareCount=0;
	m_bGameEnd=false;
	ZeroMemory(m_wFlashUser,sizeof(m_wFlashUser));
	m_wPlayerCount = GAME_PLAYER;
	//�û�״̬
	ZeroMemory(&m_StGameEnd,sizeof(m_StGameEnd));
	ZeroMemory(m_cbPlayStatus,sizeof(m_cbPlayStatus));
	ZeroMemory(m_cbGiveUpUser,sizeof(m_cbGiveUpUser));
	for(int i=0;i<m_wPlayerCount;i++)
	{
		m_bMingZhu[i]=false;
		m_wCompardUser[i].RemoveAll();
	}
	ZeroMemory(m_cbRealPlayer, sizeof(m_cbRealPlayer));
	ZeroMemory(m_cbAndroidStatus, sizeof(m_cbAndroidStatus));

	//�˿˱���
	ZeroMemory(m_cbHandCardData,sizeof(m_cbHandCardData));

	//��ע��Ϣ
	m_lMaxCellScore=0L;
	m_lCellScore=0L;
	m_lCurrentTimes=0L;		
	ZeroMemory(m_lTableScore,sizeof(m_lTableScore));
	ZeroMemory(m_lUserMaxScore,sizeof(m_lUserMaxScore));

	//�������
	m_pITableFrame=NULL;
	m_pGameServiceOption=NULL;

	//���Ʊ���
	m_bUpdataStorage=false;
	m_lStorageMax = 0;
	m_nStorageMul = 0;
	m_lStockScore = 0;
	m_lStorageDeduct = 0;

	//�������
	m_hControlInst = NULL;
	m_pServerContro = NULL;
	m_hControlInst = LoadLibrary(TEXT("ZaJinHuaServerControl.dll"));
	if ( m_hControlInst )
	{
		typedef void * (*CREATE)(); 
		CREATE ServerControl = (CREATE)GetProcAddress(m_hControlInst,"CreateServerControl"); 
		if ( ServerControl )
		{
			m_pServerContro = static_cast<IServerControl*>(ServerControl());
		}
	}

	return;
}

//��������
CTableFrameSink::~CTableFrameSink(void)
{
	if( m_pServerContro )
	{
		delete m_pServerContro;
		m_pServerContro = NULL;
	}

	if( m_hControlInst )
	{
		FreeLibrary(m_hControlInst);
		m_hControlInst = NULL;
	}
}

//�ͷŶ���
VOID CTableFrameSink::Release()
{
	if( m_pServerContro )
	{
		delete m_pServerContro;
		m_pServerContro = NULL;
	}

	if( m_hControlInst )
	{
		FreeLibrary(m_hControlInst);
		m_hControlInst = NULL;
	}

	delete this;
}

//�ӿڲ�ѯ--��������Ϣ�汾
void *  CTableFrameSink::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(ITableFrameSink,Guid,dwQueryVer);
	QUERYINTERFACE(ITableUserAction,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(ITableFrameSink,Guid,dwQueryVer);
	return NULL;
}

//��ʼ��
bool  CTableFrameSink::Initialization(IUnknownEx * pIUnknownEx)
{
	//��ѯ�ӿ�
	ASSERT(pIUnknownEx!=NULL);
	m_pITableFrame=QUERY_OBJECT_PTR_INTERFACE(pIUnknownEx,ITableFrame);
	if (m_pITableFrame==NULL) return false;

	//��ʼģʽ
	m_pITableFrame->SetStartMode(START_MODE_ALL_READY);

	//��ȡ����
	m_pGameServiceOption=m_pITableFrame->GetGameServiceOption();
	ASSERT(m_pGameServiceOption!=NULL);

	//��ȡĿ¼
	TCHAR szPath[MAX_PATH]=TEXT("");
	GetCurrentDirectory(CountArray(szPath),szPath);

	//��ȡ����
	TCHAR szFileName[MAX_PATH]=TEXT("");
	_sntprintf(szFileName,CountArray(szFileName),TEXT("%s\\ZaJinHuaConfig.ini"),szPath);

	//��ʼ�洢��Ŀ
	TCHAR szServerName[MAX_PATH]=TEXT("");
	_sntprintf(szServerName,CountArray(szServerName),TEXT("%s"),m_pGameServiceOption->szServerName);
	m_lStockScore=GetPrivateProfileInt(szServerName,TEXT("StorageStart"),0,szFileName);
	m_lStorageDeduct=GetPrivateProfileInt(szServerName,TEXT("StorageDeduct"),0,szFileName);
	m_lStorageMax = GetPrivateProfileInt(szServerName, TEXT("StorageMax"), 50000000, szFileName);
	m_nStorageMul = GetPrivateProfileInt(szServerName, TEXT("StorageMul"), 50, szFileName);

	if (m_lStorageDeduct < 0 || m_lStorageDeduct > 1000) m_lStorageDeduct = 0;
	if (m_nStorageMul < 0 || m_nStorageMul > 100) m_nStorageMul = 50;
	if (m_lStorageDeduct > 1000) m_lStorageDeduct = 1000;

	return true;
}

//��λ����
void  CTableFrameSink::RepositionSink()
{
	//��Ϸ����
	m_bOperaCount=0;
	m_wCurrentUser=INVALID_CHAIR;
	m_lCompareCount=0;
	ZeroMemory(m_wFlashUser,sizeof(m_wFlashUser));

	//�û�״̬
	ZeroMemory(&m_StGameEnd,sizeof(m_StGameEnd));
	ZeroMemory(m_cbPlayStatus,sizeof(m_cbPlayStatus));
	ZeroMemory(m_cbGiveUpUser,sizeof(m_cbGiveUpUser));
	for(int i=0;i<m_wPlayerCount;i++)
	{
		m_bMingZhu[i]=false;	
		m_wCompardUser[i].RemoveAll();
	}
	ZeroMemory(m_cbRealPlayer, sizeof(m_cbRealPlayer));
	ZeroMemory(m_cbAndroidStatus, sizeof(m_cbAndroidStatus));

	//�˿˱���
	ZeroMemory(m_cbHandCardData,sizeof(m_cbHandCardData));

	//��ע��Ϣ
	m_lMaxCellScore=0L;						
	m_lCellScore=0L;						
	m_lCurrentTimes=0L;		
	ZeroMemory(m_lTableScore,sizeof(m_lTableScore));
	ZeroMemory(m_lUserMaxScore,sizeof(m_lUserMaxScore));

	return;
}

//��ʼģʽ
BYTE  CTableFrameSink::GetGameStartMode()
{
	return m_GameStartMode;
}

//��Ϸ״̬
bool  CTableFrameSink::IsUserPlaying(WORD wChairID)
{
	ASSERT(wChairID<m_wPlayerCount);
	return (m_cbPlayStatus[wChairID]==TRUE)?true:false;
}

//��Ϸ��ʼ
bool  CTableFrameSink::OnEventGameStart()
{
	//���
	if(m_lStockScore>0 && NeedDeductStorage()) m_lStockScore = m_lStockScore-m_lStockScore*m_lStorageDeduct/1000;

	//���Ϳ����Ϣ
	for (WORD i=0;i< m_wPlayerCount;i++)
	{
		//��ȡ�û�
		IServerUserItem * pIServerUserItem=m_pITableFrame->GetTableUserItem(i);
		if ( pIServerUserItem == NULL )
			continue;

		if( CUserRight::IsGameCheatUser(m_pITableFrame->GetTableUserItem(i)->GetUserRight()))
		{
			CString strInfo;
			strInfo.Format(TEXT("��ǰ��棺%I64d"), m_lStockScore);

			m_pITableFrame->SendGameMessage(pIServerUserItem,strInfo,SMT_CHAT);
		}	
	}

	//д������־
	CString strInfo;
	strInfo.Format(TEXT("��ǰ��棺%I64d ��%d����"), m_lStockScore, m_pITableFrame->GetTableID() + 1);
	NcaTextOut(strInfo, m_pGameServiceOption->szServerName);

	//ɾ����ʱ��
	m_pITableFrame->KillGameTimer(IDI_ADD_SCORE);

	//����״̬
	m_pITableFrame->SetGameStatus(GAME_STATUS_PLAY);

	m_bGameEnd=false;

	//�����ע
	LONGLONG lTimes=6L;
	BYTE cbAiCount = 0;
	BYTE cbPlayCount = 0;
	
	for (WORD i=0;i<m_wPlayerCount;i++)
	{
		//��ȡ�û�
		IServerUserItem *pIServerUserItem=m_pITableFrame->GetTableUserItem(i);
		if (pIServerUserItem==NULL) continue;

		const LONGLONG lUserScore=pIServerUserItem->GetUserScore();

		//���ñ���
		m_cbPlayStatus[i]=TRUE;
		m_lUserMaxScore[i]=lUserScore;
		cbPlayCount++;
		if (pIServerUserItem->IsAndroidUser() == true) 
		{
			cbAiCount++;
			m_cbAndroidStatus[i] = TRUE;
		}
		else
		{
			m_cbRealPlayer[i] = TRUE;
		}

		//�жϵ�ע
		LONGLONG Temp=lTimes;
		if(m_lUserMaxScore[i]<10001)Temp=1L;
		else if(m_lUserMaxScore[i]<100001)Temp=2L;
		else if(m_lUserMaxScore[i]<1000001)Temp=3L;
		else if(m_lUserMaxScore[i]<10000001)Temp=4L;
		else if(m_lUserMaxScore[i]<100000001)Temp=5L;
		if(lTimes>Temp)lTimes=Temp;
	}

	m_bUpdataStorage = (cbAiCount != cbPlayCount);
	//��ע����
	m_lCellScore = 1;
	//m_lCellScore=m_pGameServiceOption->lCellScore;
	if(m_pGameServiceOption->wServerType != GAME_GENRE_PERSONAL)
	{
		while ((lTimes--) > 0) m_lCellScore *= 10;//add by yang yang 2018��9��30�� 17:25:03
	}


	//��������
	for(BYTE i=0;i< m_wPlayerCount;i++)
	{
		if(m_lUserMaxScore[i] != 0)
			m_lCellScore=__min(m_lUserMaxScore[i],m_lCellScore);
	}

	m_lCurrentTimes=1;
	m_lMaxCellScore=m_lCellScore*10;

	//�����ע
	for (WORD i=0;i<m_wPlayerCount;i++)
	{
		if(m_cbPlayStatus[i]==TRUE)
		{
			m_lUserMaxScore[i] = __min(m_lUserMaxScore[i],m_lMaxCellScore*101);
			if(m_pGameServiceOption->lRestrictScore != 0)
				m_lUserMaxScore[i]=__min(m_lUserMaxScore[i],m_pGameServiceOption->lRestrictScore);
		}
	}

	//�ַ��˿�
	m_GameLogic.RandCardList(m_cbHandCardData[0],sizeof(m_cbHandCardData)/sizeof(m_cbHandCardData[0][0]));

	//��Ϸ��ʼ
	AnalyseStartCard();

	//��������Ϣ
	for (WORD i = 0; i < m_wPlayerCount; i++)
	{
		//����������
		IServerUserItem *pServerUserItem = m_pITableFrame->GetTableUserItem(i);
		if (pServerUserItem == NULL) continue;
		if (pServerUserItem->IsAndroidUser() == true)
		{
			//����������
			CMD_S_AndroidCard AndroidCard ;
			ZeroMemory(&AndroidCard, sizeof(AndroidCard)) ;

			//���ñ���
			AndroidCard.lStockScore = m_lStockScore;
			CopyMemory(AndroidCard.cbRealPlayer, m_cbRealPlayer, sizeof(m_cbRealPlayer));
			CopyMemory(AndroidCard.cbAndroidStatus, m_cbAndroidStatus, sizeof(m_cbAndroidStatus));
			CopyMemory(AndroidCard.cbAllHandCardData, m_cbHandCardData, sizeof(m_cbHandCardData));
			m_pITableFrame->SendTableData(i, SUB_S_ANDROID_CARD, &AndroidCard, sizeof(AndroidCard));
		}
	}


	//����ׯ��
	if(m_wBankerUser==INVALID_CHAIR) m_wBankerUser=rand()%m_wPlayerCount;

	//ׯ���뿪
	if(m_wBankerUser<m_wPlayerCount && m_cbPlayStatus[m_wBankerUser]==FALSE) m_wBankerUser=rand()%m_wPlayerCount;

	//ȷ��ׯ��
	while(m_cbPlayStatus[m_wBankerUser]==FALSE)
	{
		m_wBankerUser = (m_wBankerUser+1)%m_wPlayerCount;
	}

	//�û�����
	for (WORD i=0;i<m_wPlayerCount;i++)
	{
		if (m_cbPlayStatus[i]==TRUE)
		{
			m_lTableScore[i]=m_lCellScore;
		}
	}

	//��ǰ�û�
	m_wCurrentUser=(m_wBankerUser+1)%m_wPlayerCount;
	while(m_cbPlayStatus[m_wCurrentUser]==FALSE)
	{
		m_wCurrentUser=(m_wCurrentUser+1)%m_wPlayerCount;
	}

	//��������
	CMD_S_GameStart GameStart;
	ZeroMemory(&GameStart,sizeof(GameStart));
	GameStart.lMaxScore=m_lMaxCellScore;
	GameStart.lCellScore=m_lCellScore;
	GameStart.lCurrentTimes=m_lCurrentTimes;
	GameStart.wCurrentUser=m_wCurrentUser;
	GameStart.wBankerUser=m_wBankerUser;
	CopyMemory(GameStart.cbPlayStatus, m_cbPlayStatus, sizeof(BYTE)*GAME_PLAYER);

	//��������
	for (WORD i = 0; i < m_wPlayerCount; i++)
	{
		if (m_cbPlayStatus[i] == TRUE)
		{
			GameStart.lUserMaxScore=m_lUserMaxScore[i];
			m_pITableFrame->SendTableData(i,SUB_S_GAME_START,&GameStart,sizeof(GameStart));
		}
		m_pITableFrame->SendLookonData(i,SUB_S_GAME_START,&GameStart,sizeof(GameStart));
	}

	//�������
	if (m_pServerContro && m_pGameServiceOption->wServerType != GAME_GENRE_PERSONAL)
	{
		//������Ϣ
		BYTE cbHandCardData[GAME_PLAYER][MAX_COUNT];
		CopyMemory(cbHandCardData, m_cbHandCardData, sizeof(cbHandCardData) );

		//�����˿�
		for (WORD i= 0;i < m_wPlayerCount; i++)
			m_GameLogic.SortCardList(cbHandCardData[i], MAX_COUNT);

		//��Ϣ����
		m_pServerContro->ServerControl(cbHandCardData, m_pITableFrame);
	}

	return true;
}

//��Ϸ����
bool CTableFrameSink::OnEventGameConclude(WORD wChairID, IServerUserItem * pIServerUserItem, BYTE cbReason)
{
	switch (cbReason)
	{
	case GER_COMPARECARD:	//���ƽ���
	case GER_NO_PLAYER:		//û�����
		{
			if(m_bGameEnd)return true;
			m_bGameEnd=true;

			//�������
			CMD_S_GameEnd GameEnd;
			ZeroMemory(&GameEnd,sizeof(GameEnd));
			for (WORD i=0;i<m_wPlayerCount;i++)
				for (WORD j=0;j<4;j++)
					GameEnd.wCompareUser[i][j]=INVALID_CHAIR;

			//Ψһ���
			WORD wWinner,wUserCount=0;
			for (WORD i=0;i<m_wPlayerCount;i++)
			{	
				if(m_cbPlayStatus[i]==TRUE)
				{
					wUserCount++;
					wWinner=i;
					if(GER_COMPARECARD==cbReason)ASSERT(m_wBankerUser==i);
					m_wBankerUser=i;
				}
			}

			//ʤ����ǿ��
			if (wUserCount==0)
			{
				wWinner=m_wBankerUser;
			}

			//�ӳٿ�ʼ
			bool bDelayOverGame = false;

			//������ע
			LONGLONG lWinnerScore=0L;
			for (WORD i=0;i<m_wPlayerCount;i++) 
			{
				if(i==wWinner)continue;
				GameEnd.lGameScore[i]=-m_lTableScore[i];
				lWinnerScore+=m_lTableScore[i];
			}

			//����˰��
			GameEnd.lGameTax=m_pITableFrame->CalculateRevenue(wWinner,lWinnerScore);
			GameEnd.lGameScore[wWinner]=lWinnerScore-GameEnd.lGameTax;

			CopyMemory(GameEnd.cbCardData,m_cbHandCardData,sizeof(m_cbHandCardData));

			//�˿�����
			for (WORD i=0;i<m_wPlayerCount;i++) 
			{
				WORD wCount=0;
				while(m_wCompardUser[i].GetCount()>0)
				{
					GameEnd.wCompareUser[i][wCount++] = m_wCompardUser[i].GetAt(0);
					m_wCompardUser[i].RemoveAt(0);
				}
			}

			GameEnd.wEndState=0;

			//ʤ����ǿ��
			if (wUserCount==1)
			{
				//�޸Ļ���
				tagScoreInfo ScoreInfoArray[GAME_PLAYER];
				ZeroMemory(ScoreInfoArray,sizeof(ScoreInfoArray));
				for (WORD i=0;i<m_wPlayerCount;i++)
				{
					if(m_cbPlayStatus[i]==FALSE)continue;
					ScoreInfoArray[i].cbType =(GameEnd.lGameScore[i]>0L)?SCORE_TYPE_WIN:SCORE_TYPE_LOSE;
					ScoreInfoArray[i].lRevenue=GameEnd.lGameTax;                                  
					ScoreInfoArray[i].lScore=GameEnd.lGameScore[i];

					if (ScoreInfoArray[i].cbType == SCORE_TYPE_LOSE && bDelayOverGame == false)
					{
						IServerUserItem * pUserItem = m_pITableFrame->GetTableUserItem(i);
						if (pUserItem!=NULL && (pUserItem->GetUserScore()+GameEnd.lGameScore[i])<m_pGameServiceOption->lMinTableScore)
						{
							bDelayOverGame = true;
						}
					}
				}

				m_pITableFrame->WriteTableScore(ScoreInfoArray, m_wPlayerCount);
			}

			//���ͳ��
			for (WORD i=0; i<m_wPlayerCount; i++)
			{
				//��ȡ�û�
				IServerUserItem * pIServerUserIte=m_pITableFrame->GetTableUserItem(i);
				if (pIServerUserIte==NULL) continue;
				if(!m_cbPlayStatus[i]) continue;

				//����ۼ�
				if(!pIServerUserIte->IsAndroidUser())
					UpdateStorage(-GameEnd.lGameScore[i]);//m_lStockScore -= GameEnd.lGameScore[i];

			}
			//��������
			GameEnd.wServerType = m_pGameServiceOption->wServerType;
			//�ӳٿ�ʼ
			if(bDelayOverGame)
			{
				GameEnd.bDelayOverGame = true;
			}

			if(wChairID==GAME_PLAYER)
			{
				//��������
				CopyMemory(&m_StGameEnd,&GameEnd,sizeof(m_StGameEnd));
				m_pITableFrame->SetGameTimer(IDI_GAME_COMPAREEND,TIME_GAME_COMPAREEND,1,0);
			}
			else
			{
				//������Ϣ
				m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd));
				m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd));

				//������Ϸ
				m_pITableFrame->ConcludeGame(GAME_STATUS_FREE);
			}

			return true;
		}
	case GER_USER_LEAVE:		//�û�ǿ��
	case GER_NETWORK_ERROR:		//�����ж�
		{
			if(m_bGameEnd || m_cbPlayStatus[wChairID]==FALSE) return true;

			//Ч�����
			ASSERT(pIServerUserItem!=NULL);
			ASSERT(wChairID<m_wPlayerCount);

			//ǿ�˴���
			return OnUserGiveUp(wChairID,true);
		}
	case GER_OPENCARD:		//���ƽ���   
		{
			if(m_bGameEnd)return true;
			m_bGameEnd = true;

			//�������
			CMD_S_GameEnd GameEnd;
			ZeroMemory(&GameEnd,sizeof(GameEnd));
			for (WORD i=0;i<m_wPlayerCount;i++)
				for (WORD j=0;j<4;j++)
					GameEnd.wCompareUser[i][j]=INVALID_CHAIR;

			//ʤ�����
			WORD wWinner=m_wBankerUser;

			//�������
			LONGLONG lWinnerScore=0L;
			for (WORD i=0;i<m_wPlayerCount;i++) 
			{
				if(i==wWinner)continue;
				lWinnerScore+=m_lTableScore[i];
				GameEnd.lGameScore[i]=-m_lTableScore[i];
			}

			//����˰��
			GameEnd.lGameTax=m_pITableFrame->CalculateRevenue(wWinner,lWinnerScore);
			GameEnd.lGameScore[wWinner]=lWinnerScore-GameEnd.lGameTax;

			//���ƽ���
			GameEnd.wEndState=1;
			CopyMemory(GameEnd.cbCardData,m_cbHandCardData,sizeof(m_cbHandCardData));

			//�˿�����
			for (WORD i=0;i<m_wPlayerCount;i++) 
			{
				WORD wCount=0;
				while(m_wCompardUser[i].GetCount()>0)
				{
					GameEnd.wCompareUser[i][wCount++] = m_wCompardUser[i].GetAt(0);
					m_wCompardUser[i].RemoveAt(0);
				}
			}

			//�޸Ļ���
			tagScoreInfo ScoreInfo[GAME_PLAYER];
			ZeroMemory(ScoreInfo,sizeof(ScoreInfo));
			for (WORD i=0; i<m_wPlayerCount; i++) 
			{				
				if(i==wWinner || m_cbPlayStatus[i]==FALSE)continue;
				ScoreInfo[i].lScore=GameEnd.lGameScore[i];
				ScoreInfo[i].cbType=SCORE_TYPE_LOSE;
			}
			ScoreInfo[wWinner].lScore=GameEnd.lGameScore[wWinner];
			ScoreInfo[wWinner].cbType=SCORE_TYPE_WIN;
			ScoreInfo[wWinner].lRevenue=GameEnd.lGameTax;
	
			m_pITableFrame->WriteTableScore(ScoreInfo,m_wPlayerCount);

			//���ͳ��
			for (WORD i=0; i<m_wPlayerCount; i++)
			{
				//��ȡ�û�
				IServerUserItem * pIServerUserIte=m_pITableFrame->GetTableUserItem(i);
				if (pIServerUserIte==NULL) continue;
				if(!m_cbPlayStatus[i]) continue;

				//����ۼ�
				if(!pIServerUserIte->IsAndroidUser())
					UpdateStorage(-GameEnd.lGameScore[i]);//m_lStockScore -= GameEnd.lGameScore[i];

			}

			//��������
			GameEnd.wServerType = m_pGameServiceOption->wServerType;

			if(wChairID==GAME_PLAYER)
			{
				//��������
				CopyMemory(&m_StGameEnd,&GameEnd,sizeof(m_StGameEnd));
				m_pITableFrame->SetGameTimer(IDI_GAME_OPENEND,TIME_GAME_OPENEND,1,0);
			}
			else
			{
				//������Ϣ
				m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd));
				m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd));

				//������Ϸ
				m_pITableFrame->ConcludeGame(GAME_STATUS_FREE);
			}

			return true;
		}
	case GER_DISMISS:		//��Ϸ��ɢ
		{
			//��������
			CMD_S_GameEnd GameEnd;
			ZeroMemory(&GameEnd,sizeof(GameEnd));

			//������Ϣ
			m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd));
			m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd));

			//������Ϸ
			m_pITableFrame->ConcludeGame(GAME_STATUS_FREE);

			return true;
		}
	}

	return false;
}

//���ͳ���
bool  CTableFrameSink::OnEventSendGameScene(WORD wChiarID, IServerUserItem * pIServerUserItem, BYTE cbGameStatus, bool bSendSecret)
{
	switch (cbGameStatus)
	{
	case GAME_STATUS_FREE:		//����״̬
		{
			//��������
			CMD_S_StatusFree StatusFree;
			ZeroMemory(&StatusFree,sizeof(StatusFree));

			//���ñ���
			StatusFree.lCellScore=0L;

			//��������
			CopyMemory(StatusFree.szGameRoomName, m_pGameServiceOption->szServerName, sizeof(StatusFree.szGameRoomName));

			//���ͳ���
			return m_pITableFrame->SendGameScene(pIServerUserItem,&StatusFree,sizeof(StatusFree));
		}
	case GAME_STATUS_PLAY:	//��Ϸ״̬
		{
			//��������
			CMD_S_StatusPlay StatusPlay;
			memset(&StatusPlay,0,sizeof(StatusPlay));

			//��ע��Ϣ
			StatusPlay.lMaxCellScore=m_lMaxCellScore;
			StatusPlay.lCellScore=m_lCellScore;
			StatusPlay.lCurrentTimes=m_lCurrentTimes;
			StatusPlay.lUserMaxScore=m_lUserMaxScore[wChiarID];

			//���ñ���
			StatusPlay.wBankerUser=m_wBankerUser;
			StatusPlay.wCurrentUser=m_wCurrentUser;
			CopyMemory(StatusPlay.bMingZhu,m_bMingZhu,sizeof(m_bMingZhu));
			CopyMemory(StatusPlay.lTableScore,m_lTableScore,sizeof(m_lTableScore));
			CopyMemory(StatusPlay.cbPlayStatus,m_cbPlayStatus,sizeof(m_cbPlayStatus));

			//��������
			CopyMemory(StatusPlay.szGameRoomName, m_pGameServiceOption->szServerName, sizeof(StatusPlay.szGameRoomName));

			//��ǰ״̬
			StatusPlay.bCompareState=(m_lCompareCount<=0)?false:true;

			//�����˿�
			if(m_bMingZhu[wChiarID])
				CopyMemory(&StatusPlay.cbHandCardData,&m_cbHandCardData[wChiarID],MAX_COUNT);

			//���ͳ���
			return m_pITableFrame->SendGameScene(pIServerUserItem,&StatusPlay,sizeof(StatusPlay));
		}
	}

	//Ч�����
	ASSERT(FALSE);

	return false;
}

//��ʱ���¼� 
bool  CTableFrameSink::OnTimerMessage(DWORD wTimerID, WPARAM wBindParam)
{
	//������ʱ
	if(wTimerID==IDI_GAME_COMPAREEND || IDI_GAME_OPENEND==wTimerID)
	{
		//ɾ��ʱ��
		if(wTimerID==IDI_GAME_COMPAREEND)m_pITableFrame->KillGameTimer(IDI_GAME_COMPAREEND);
		else m_pITableFrame->KillGameTimer(IDI_GAME_OPENEND);

		//������Ϣ
		m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_GAME_END,&m_StGameEnd,sizeof(m_StGameEnd));
		m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_GAME_END,&m_StGameEnd,sizeof(m_StGameEnd));

		//������Ϸ
		m_pITableFrame->ConcludeGame(GAME_STATUS_FREE);
	}
	if(wTimerID==IDI_ADD_SCORE)
	{
		m_pITableFrame->KillGameTimer(IDI_ADD_SCORE);
		if (m_wCurrentUser!=INVALID_CHAIR)
		{
			OnUserGiveUp(m_wCurrentUser,false);
		}		
	}

	return false;
}

//��Ϸ��Ϣ����
bool  CTableFrameSink::OnGameMessage(WORD wSubCmdID, VOID * pData, WORD wDataSize, IServerUserItem * pIServerUserItem)
{
	switch (wSubCmdID)
	{
	case SUB_C_GIVE_UP:			//�û�����
		{
			//�û�Ч��
			tagUserInfo * pUserData=pIServerUserItem->GetUserInfo();
			if (pUserData->cbUserStatus!=US_PLAYING) return true;

			//״̬�ж�
			ASSERT(m_cbPlayStatus[pUserData->wChairID]==TRUE);
			if (m_cbPlayStatus[pUserData->wChairID]==FALSE) return false;

			//��Ϣ����
			return OnUserGiveUp(pUserData->wChairID);
		}
	case SUB_C_LOOK_CARD:		//�û�����
		{
			//�û�Ч��
			tagUserInfo * pUserData=pIServerUserItem->GetUserInfo();
			if (pUserData->cbUserStatus!=US_PLAYING) return true;

			//״̬�ж�
			ASSERT(m_cbPlayStatus[pUserData->wChairID]==TRUE);
			if (m_cbPlayStatus[pUserData->wChairID]==FALSE) return false;

			//��Ϣ����
			return OnUserLookCard(pUserData->wChairID);
		}
	case SUB_C_COMPARE_CARD:	//�û�����
		{
		TCHAR szOut[256];
		wsprintf(szOut, TEXT("ը�� SUB_C_COMPARE_CARD  start "));
		OutputDebugString(szOut);
		
			//Ч������
			ASSERT(wDataSize==sizeof(CMD_C_CompareCard));
			if (wDataSize != sizeof(CMD_C_CompareCard))
			{
				return false;
			}
			//��������
			CMD_C_CompareCard * pCompareCard=(CMD_C_CompareCard *)pData;

			//�û�Ч��
			tagUserInfo * pUserData=pIServerUserItem->GetUserInfo();
			if (pUserData->cbUserStatus != US_PLAYING)
			{
				wsprintf(szOut, TEXT("ը�� SUB_C_COMPARE_CARD  pUserData->cbUserStatus = %d"), pUserData->cbUserStatus);
				OutputDebugString(szOut);
				return true;
			}

			//����Ч��
			ASSERT(pUserData->wChairID==m_wCurrentUser);
			if(pUserData->wChairID!=m_wCurrentUser)return false;

			//״̬�ж�
			ASSERT(m_cbPlayStatus[pUserData->wChairID]==TRUE && m_cbPlayStatus[pCompareCard->wCompareUser]==TRUE);
			if(m_cbPlayStatus[pUserData->wChairID]==FALSE || m_cbPlayStatus[pCompareCard->wCompareUser]==FALSE)
			{ 
				wsprintf(szOut, TEXT("ը�� SUB_C_COMPARE_CARD  m_cbPlayStatus[pUserData->wChairID] = %d,pUserData->wChairID = %d,m_cbPlayStatus[pCompareCard->wCompareUser] = %d,pCompareCard->wCompareUser = %d"),
					m_cbPlayStatus[pUserData->wChairID], pUserData->wChairID,m_cbPlayStatus[pCompareCard->wCompareUser], pCompareCard->wCompareUser);
				OutputDebugString(szOut);
				return false;
			}
				

			//��Ϣ����
			return OnUserCompareCard(pUserData->wChairID,pCompareCard->wCompareUser);
		}
	case SUB_C_ADD_SCORE:		//�û���ע
		{
			//CTraceService::TraceString(TEXT("zzz onSubAddScore"),TraceLevel_Normal);
			//Ч������
			ASSERT(wDataSize==sizeof(CMD_C_AddScore));
			if (wDataSize!=sizeof(CMD_C_AddScore)) 
			{
				//������ʾ
			//TCHAR szString[512]=TEXT("");
			//_sntprintf(szString,CountArray(szString),TEXT("zzz [ %d ]!=sizeof CMD_C_AddScore [ %d ]"),wDataSize,sizeof(CMD_C_AddScore));

			//��ʾ��Ϣ
			//CTraceService::TraceString(szString,TraceLevel_Normal);
				return false;
			}

			//��������
			CMD_C_AddScore * pAddScore=(CMD_C_AddScore *)pData;

			//�û�Ч��
			tagUserInfo * pUserData=pIServerUserItem->GetUserInfo();
			if (pUserData->cbUserStatus!=US_PLAYING) return true;

			//״̬�ж�
			ASSERT(m_cbPlayStatus[pUserData->wChairID]==TRUE && m_lCompareCount==0);
			if (m_cbPlayStatus[pUserData->wChairID]==FALSE || m_lCompareCount> 0)
			{
				//CTraceService::TraceString(TEXT("zzz m_cbPlayStatus[pUserData->wChairID]==FALSE || m_lCompareCount> 0"),TraceLevel_Normal);
				return false;
			}

			//��ǰ״̬
			if(pAddScore->wState>0)m_lCompareCount=pAddScore->lScore;

			//��Ϣ����
			bool isOK = OnUserAddScore(pUserData->wChairID,pAddScore->lScore,false,((pAddScore->wState>0)?true:false));
			//if(isOK)
			///{
				//CTraceService::TraceString(TEXT("zzz OK"),TraceLevel_Normal);
			//}
			//else
			//{
			//	CTraceService::TraceString(TEXT("zzz NO"),TraceLevel_Normal);
			//}
			return isOK;
		}
	case SUB_C_WAIT_COMPARE:	//�ȴ�����
		{
			//�û�Ч��
			tagUserInfo * pUserData=pIServerUserItem->GetUserInfo();
			if (pUserData->cbUserStatus!=US_PLAYING) return true;

			//״̬�ж�
			ASSERT(m_cbPlayStatus[pUserData->wChairID]==TRUE);
			if (m_cbPlayStatus[pUserData->wChairID]==FALSE) return false;

			//����Ч��
			ASSERT(pUserData->wChairID==m_wCurrentUser);
			if(pUserData->wChairID!=m_wCurrentUser)return false;

			//��Ϣ����
			CMD_S_WaitCompare WaitCompare;
			WaitCompare.wCompareUser = pUserData->wChairID;
			if(m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_WAIT_COMPARE,&WaitCompare,sizeof(WaitCompare)) &&
			m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_WAIT_COMPARE,&WaitCompare,sizeof(WaitCompare)) )

			return true;
		}
	case SUB_C_FINISH_FLASH:	//��ɶ��� 
		{
			//�û�Ч��
			tagUserInfo * pUserData=pIServerUserItem->GetUserInfo();
			if (pUserData->cbUserStatus!=US_PLAYING) return true;

			//״̬�ж�
			ASSERT(m_wFlashUser[pUserData->wChairID]==TRUE);
			if (m_wFlashUser[pUserData->wChairID]==FALSE) return true;

			//���ñ���
			m_wFlashUser[pUserData->wChairID] = FALSE;

			//������Ϸ
			WORD i = 0;
			for(i=0;i< m_wPlayerCount;i++)
			{
				if(m_wFlashUser[i] != FALSE)break;
			}
			if(i== m_wPlayerCount)
			{
				//ɾ��ʱ��
				m_pITableFrame->KillGameTimer(IDI_GAME_COMPAREEND);
				m_pITableFrame->KillGameTimer(IDI_GAME_OPENEND);

				//������Ϣ
				m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_GAME_END,&m_StGameEnd,sizeof(m_StGameEnd));
				m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_GAME_END,&m_StGameEnd,sizeof(m_StGameEnd));

				//������Ϸ
				m_pITableFrame->ConcludeGame(GAME_STATUS_FREE);
			}
			return true;
		}
	case SUB_C_ADD_SCORE_TIME:
		{
			//�û�Ч��
			tagUserInfo * pUserData=pIServerUserItem->GetUserInfo();
			if (pUserData->cbUserStatus!=US_PLAYING) return true;

			m_pITableFrame->SetGameTimer(IDI_ADD_SCORE,TIME_ADD_SCORE*30,1,0);
			return true;
		}
	}

	return false;
}

//�����Ϣ����
bool  CTableFrameSink::OnFrameMessage(WORD wSubCmdID, VOID * pData, WORD wDataSize, IServerUserItem * pIServerUserItem)
{
	return false;
}



//�û�����
bool CTableFrameSink::OnActionUserSitDown(WORD wChairID,IServerUserItem * pIServerUserItem, bool bLookonUser)
{
	return true;
}

//�û�����
bool CTableFrameSink::OnActionUserStandUp(WORD wChairID,IServerUserItem * pIServerUserItem, bool bLookonUser)
{
	return true;
}

//�����¼�
bool CTableFrameSink::OnUserGiveUp(WORD wChairID,bool bExit)
{
	//��������
	m_cbGiveUpUser[wChairID] = TRUE;
	m_cbPlayStatus[wChairID] = FALSE;

	//������Ϣ
	CMD_S_GiveUp GiveUp;
	GiveUp.wGiveUpUser=wChairID;
	m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_GIVE_UP,&GiveUp,sizeof(GiveUp));
	m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_GIVE_UP,&GiveUp,sizeof(GiveUp));

	//�޸Ļ���
	tagScoreInfo ScoreInfoArray[GAME_PLAYER];
	ZeroMemory(ScoreInfoArray,sizeof(ScoreInfoArray));
	ScoreInfoArray[wChairID].cbType =(bExit)?SCORE_TYPE_FLEE:SCORE_TYPE_LOSE;
	ScoreInfoArray[wChairID].lRevenue=0;  
	ScoreInfoArray[wChairID].lScore=-m_lTableScore[wChairID];

	m_pITableFrame->WriteTableScore(ScoreInfoArray,m_wPlayerCount);

	//��ȡ�û�
	IServerUserItem * pIServerUserIte=m_pITableFrame->GetTableUserItem(wChairID);

	//���ͳ��
	if ((pIServerUserIte!=NULL)&&(!pIServerUserIte->IsAndroidUser())) 
		UpdateStorage(m_lTableScore[wChairID]);//m_lStockScore += m_lTableScore[wChairID];

	//����ͳ��
	WORD wPlayerCount=0;
	for (WORD i=0;i<m_wPlayerCount;i++)
	{
		if (m_cbPlayStatus[i]==TRUE) wPlayerCount++;
	}

	//�жϽ���
	if (wPlayerCount>=2)
	{
		if (m_wCurrentUser==wChairID) OnUserAddScore(wChairID,0L,true,false);
	}
	else OnEventGameConclude(INVALID_CHAIR,NULL,GER_NO_PLAYER);

	return true;
}

//�����¼�
bool CTableFrameSink::OnUserLookCard(WORD wChairID)
{
	//״̬Ч��
	ASSERT(m_wCurrentUser==wChairID);
	if (m_wCurrentUser!=wChairID) return false;

	//����Ч��
	ASSERT(!m_bMingZhu[wChairID]);
	if (m_bMingZhu[wChairID]) return true;

	//���ò���
	m_bMingZhu[wChairID]=true;
	//��������
	CMD_S_LookCard LookCard;
	ZeroMemory(&LookCard,sizeof(LookCard));
	LookCard.wLookCardUser=wChairID;

	m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_LOOK_CARD,&LookCard,sizeof(LookCard));

	for(WORD i = 0;i< m_wPlayerCount;i++)
	{
		IServerUserItem * pIServerUserItem = m_pITableFrame->GetTableUserItem(i);
		if(pIServerUserItem == NULL ) continue;
		if(i == wChairID)
		{
			CopyMemory(LookCard.cbCardData,m_cbHandCardData[wChairID],sizeof(m_cbHandCardData[0]));
		}
		else
		{
			ZeroMemory(LookCard.cbCardData,sizeof(LookCard.cbCardData));
		}
		m_pITableFrame->SendTableData(i,SUB_S_LOOK_CARD,&LookCard,sizeof(LookCard));
	}

	return true;
}

//�����¼�
bool CTableFrameSink::OnUserCompareCard(WORD wFirstChairID,WORD wNextChairID)
{
	//Ч�����
	ASSERT(m_lCompareCount>0);
	if(!(m_lCompareCount>0))return false;
	//LONGLONG lTemp=(m_bMingZhu[m_wCurrentUser])?6:5;
	//ASSERT((m_lUserMaxScore[m_wCurrentUser]-m_lTableScore[m_wCurrentUser]+m_lCompareCount) >= (m_lMaxCellScore*lTemp));
	//if((m_lUserMaxScore[m_wCurrentUser]-m_lTableScore[m_wCurrentUser]+m_lCompareCount) < (m_lMaxCellScore*lTemp))return false;
	//ԭ��>=2*m_lCellScore�������һ�ֶ��Ļ��ֶ�û�ܴﵽ��ע��ע����������ôֻ�ܿ��ƣ�����ע����m_lCellScore��
	//��ô���ƾ�һ������ߣ���ʱm_lTableScore[m_wCurrentUser]Ϊ��ע+m_lCompareCount��
	//����ΪʲôҪ���ڵ���2*m_lCellScore��ԭ����
	ASSERT(m_wCurrentUser==m_wBankerUser || m_lTableScore[m_wCurrentUser]-m_lCompareCount>=m_lCellScore);	
	if (!(m_wCurrentUser == m_wBankerUser || m_lTableScore[m_wCurrentUser] - m_lCompareCount >= m_lCellScore))
	{
		TCHAR szOut[256];
		wsprintf(szOut, TEXT("ը�� OnUserCompareCard m_wCurrentUser = %d,m_wBankerUser = %d,m_lTableScore[m_wCurrentUser] = %64d,m_lCompareCount = %64d,m_lCellScore = %64d"),
			m_wCurrentUser, m_wBankerUser, m_lTableScore[m_wCurrentUser], m_lCompareCount, m_lCellScore);
		OutputDebugString(szOut);
		return false;
	}
	//ɾ����ʱ��
	m_pITableFrame->KillGameTimer(IDI_ADD_SCORE);

	//�Ƚϴ�С
	BYTE cbWin=m_GameLogic.CompareCard(m_cbHandCardData[wFirstChairID],m_cbHandCardData[wNextChairID],MAX_COUNT);

	//״̬����
	m_lCompareCount=0;

	//ʤ���û�
	WORD wLostUser,wWinUser;
	if(cbWin==TRUE) 
	{
		wWinUser=wFirstChairID;
		wLostUser=wNextChairID;
	}
	else
	{
		wWinUser=wNextChairID;
		wLostUser=wFirstChairID;
	}

	//��������
	m_wCompardUser[wLostUser].Add(wWinUser);
	m_wCompardUser[wWinUser].Add(wLostUser);
	m_cbPlayStatus[wLostUser]=FALSE;

	//����ͳ��
	WORD wPlayerCount=0;
	for (WORD i=0;i<m_wPlayerCount;i++)
	{
		if (m_cbPlayStatus[i]==TRUE) wPlayerCount++;
	}

	//������Ϸ
	if(wPlayerCount>=2)
	{
		//�û��л�
		WORD wNextPlayer=INVALID_CHAIR;
		for (WORD i=1;i<m_wPlayerCount;i++)
		{
			//���ñ���
			wNextPlayer=(m_wCurrentUser+i)%m_wPlayerCount;

			//�����ж�
			if (m_cbPlayStatus[wNextPlayer]==TRUE) break;
		}
		//�����û�
		m_wCurrentUser=wNextPlayer;
	}
	else m_wCurrentUser=INVALID_CHAIR;

	//��������
	CMD_S_CompareCard CompareCard;
	CompareCard.wCurrentUser = m_wCurrentUser;
	CompareCard.wLostUser = wLostUser;
	CompareCard.wCompareUser[0] = wFirstChairID;
	CompareCard.wCompareUser[1] = wNextChairID;

	//��������
	m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_COMPARE_CARD,&CompareCard,sizeof(CompareCard));
	m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_COMPARE_CARD,&CompareCard,sizeof(CompareCard));

	//�޸Ļ���
	tagScoreInfo ScoreInfoArray[GAME_PLAYER];
	ZeroMemory(ScoreInfoArray,sizeof(ScoreInfoArray));
	ScoreInfoArray[wLostUser].cbType =SCORE_TYPE_LOSE;
	ScoreInfoArray[wLostUser].lRevenue=0;
	ScoreInfoArray[wLostUser].lScore=-m_lTableScore[wLostUser];

	m_pITableFrame->WriteTableScore(ScoreInfoArray, m_wPlayerCount);
	
	//���ͳ��
	IServerUserItem * pIServreUserItemLost=m_pITableFrame->GetTableUserItem(wLostUser);
	if ((pIServreUserItemLost!=NULL)&&(!pIServreUserItemLost->IsAndroidUser())) 
		UpdateStorage(m_lTableScore[wLostUser]);//m_lStockScore += m_lTableScore[wLostUser];

	//������Ϸ
	if (wPlayerCount<2)
	{
		m_wBankerUser=wWinUser;
		m_wFlashUser[wNextChairID] = TRUE;
		m_wFlashUser[wFirstChairID] = TRUE;
		OnEventGameConclude(m_wPlayerCount,NULL,GER_COMPARECARD);
	}

	return true;
}

//�����¼�
bool CTableFrameSink::OnUserOpenCard(WORD wUserID)
{
	//Ч�����
	ASSERT(m_lCompareCount>0);
	if(!(m_lCompareCount>0))return false;
	ASSERT(m_wCurrentUser==wUserID);
	if(m_wCurrentUser!=wUserID)return false;
	//LONGLONG lTemp=(m_bMingZhu[wUserID])?6:5;
	//ASSERT((m_lUserMaxScore[wUserID]-m_lTableScore[wUserID]+m_lCompareCount) < (m_lMaxCellScore*lTemp));
	//if((m_lUserMaxScore[wUserID]-m_lTableScore[wUserID]+m_lCompareCount) >= (m_lMaxCellScore*lTemp))return false;

	//��������
	m_wCurrentUser=INVALID_CHAIR;
	m_lCompareCount = 0;

	//�����˿�
	BYTE cbUserCardData[GAME_PLAYER][MAX_COUNT];
	CopyMemory(cbUserCardData,m_cbHandCardData,sizeof(cbUserCardData));

	//�������
	WORD wWinner=wUserID;

	//����������
	for (WORD i=1;i<m_wPlayerCount;i++)
	{
		WORD w=(wUserID+i)%m_wPlayerCount;

		//�û�����
		if (m_cbPlayStatus[w]==FALSE) continue;

		//�Ա��˿�
		if (m_GameLogic.CompareCard(cbUserCardData[w],cbUserCardData[wWinner],MAX_COUNT)>=TRUE) 
		{
			wWinner=w;
		}
	}
	ASSERT(m_cbPlayStatus[wWinner]==TRUE);
	if(m_cbPlayStatus[wWinner]==FALSE)return false;

	//ʤ�����
	m_wBankerUser = wWinner;

	//��������
	CMD_S_OpenCard OpenCard;
	OpenCard.wWinner=wWinner;

	//��������
	m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_OPEN_CARD,&OpenCard,sizeof(OpenCard));
	m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_OPEN_CARD,&OpenCard,sizeof(OpenCard));

	//������Ϸ
	for(WORD i=0;i< m_wPlayerCount;i++)if(m_cbPlayStatus[i]==TRUE)m_wFlashUser[i] = TRUE;
	OnEventGameConclude(m_wPlayerCount,NULL,GER_OPENCARD);

	return true;
}

//��ע�¼�
bool CTableFrameSink::OnUserAddScore(WORD wChairID, LONGLONG lScore, bool bGiveUp, bool bCompareCard)
{
	//CTraceService::TraceString(TEXT("zzz 00"),TraceLevel_Normal);
	if (bGiveUp==false)				//��������
	{
		//״̬Ч��
		ASSERT(m_wCurrentUser==wChairID);
		if (m_wCurrentUser!=wChairID) 
		{
			//��ʾ��Ϣ
			//CTraceService::TraceString(TEXT("zzz 11"),TraceLevel_Normal);
			return false;
		}
			
		if (m_pITableFrame->GetGameServiceOption()->wServerType != GAME_GENRE_PERSONAL)
		{


			//���Ч��
			ASSERT(lScore >= 0 && lScore%m_lCellScore == 0);
			ASSERT((lScore + m_lTableScore[wChairID]) <= m_lUserMaxScore[wChairID]);
			if (lScore < 0 || lScore % m_lCellScore != 0)
			{
				//��ʾ��Ϣ
				//CTraceService::TraceString(TEXT("zzz 22"),TraceLevel_Normal);
				return false;
			}
			if ((lScore + m_lTableScore[wChairID]) > m_lUserMaxScore[wChairID])
			{
				//��ʾ��Ϣ
				//CTraceService::TraceString(TEXT("zzz 33"),TraceLevel_Normal);
				return false;
			}

			IServerUserItem *pIserberUser = m_pITableFrame->GetTableUserItem(wChairID);
			if (pIserberUser->GetUserScore() < m_lTableScore[wChairID] + lScore)
			{
				//��ʾ��Ϣ
				//CTraceService::TraceString(TEXT("zzz 44"),TraceLevel_Normal);
				return false;
			}
		}
		//��ǰ����
		LONGLONG lTimes=(m_bMingZhu[wChairID] || bCompareCard)?2:1;
		if(m_bMingZhu[wChairID] && bCompareCard)lTimes=4;
		LONGLONG lTemp=lScore/m_lCellScore/lTimes;
		ASSERT(m_lCurrentTimes<=lTemp && m_lCurrentTimes<=m_lMaxCellScore/m_lCellScore);
		if(!(m_lCurrentTimes<=lTemp && m_lCurrentTimes<=m_lMaxCellScore/m_lCellScore))
		{
			//��ʾ��Ϣ
			//CTraceService::TraceString(TEXT("zzz 55"),TraceLevel_Normal);
			return false;
		}
		m_lCurrentTimes = lTemp;

		//�û�ע��
		m_lTableScore[wChairID]+=lScore;
	}

	//�����û�
	if(!bCompareCard)
	{
		//�û��л�
		WORD wNextPlayer=INVALID_CHAIR;
		for (WORD i=1;i<m_wPlayerCount;i++)
		{
			//���ñ���
			wNextPlayer=(m_wCurrentUser+i)%m_wPlayerCount;

			//�����ж�
			if (m_cbPlayStatus[wNextPlayer]==TRUE) break;
		}
		m_wCurrentUser=wNextPlayer;
	}

	//��������
	CMD_S_AddScore AddScore;
	AddScore.lCurrentTimes=m_lCurrentTimes;
	AddScore.wCurrentUser=m_wCurrentUser;
	AddScore.wAddScoreUser=wChairID;
	AddScore.lAddScoreCount=lScore;

	//�ж�״̬
	AddScore.wCompareState=( bCompareCard )?TRUE:FALSE;

	//��������
	m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_ADD_SCORE,&AddScore,sizeof(AddScore));
	m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_ADD_SCORE,&AddScore,sizeof(AddScore));

	//���ö�ʱ��
	m_pITableFrame->SetGameTimer(IDI_ADD_SCORE,TIME_ADD_SCORE*30,1,0);

	return true;
}

//�˿˷���
void CTableFrameSink::AnalyseStartCard()
{
	//��������
	WORD wAiCount = 0;
	WORD wPlayerCount = 0;
	for (WORD i=0; i<m_wPlayerCount; i++)
	{
		//��ȡ�û�
		IServerUserItem * pIServerUserItem=m_pITableFrame->GetTableUserItem(i);
		if (pIServerUserItem!=NULL)
		{
			if(m_cbPlayStatus[i]==FALSE)continue;
			if(pIServerUserItem->IsAndroidUser()) 
			{
				wAiCount++ ;
			}
			wPlayerCount++;
		}
	}

	//ȫ������
	if(wPlayerCount == wAiCount || wAiCount==0) return;

	//�˿˱���
	BYTE cbUserCardData[GAME_PLAYER][MAX_COUNT];
	CopyMemory(cbUserCardData, m_cbHandCardData, sizeof(m_cbHandCardData));

	//�����˿�
	for (WORD i=0;i<m_wPlayerCount;i++)
	{
		m_GameLogic.SortCardList(cbUserCardData[i], MAX_COUNT);
	}

	//��������
	WORD wWinUser = INVALID_CHAIR;

	//��������
	for (WORD i = 0; i < m_wPlayerCount; i++)
	{
		//�û�����
		if (m_cbPlayStatus[i] == FALSE) continue;

		//�����û�
		if (wWinUser == INVALID_CHAIR)
		{
			wWinUser=i;
			continue;
		}

		//�Ա��˿�
		if (m_GameLogic.CompareCard(cbUserCardData[i], cbUserCardData[wWinUser], MAX_COUNT) >= TRUE)
		{
			wWinUser = i;
		}
	}

	//����ж�
	if (m_lStockScore - m_lCellScore*10*wAiCount < 0)
	{
		//���Ӯ��
		WORD wBeWinAndroid = INVALID_CHAIR;

		do 
		{
			wBeWinAndroid = rand()%GAME_PLAYER;
		} while (m_pITableFrame->GetTableUserItem(wBeWinAndroid) == NULL || !m_pITableFrame->GetTableUserItem(wBeWinAndroid)->IsAndroidUser());

		if(wBeWinAndroid != wWinUser)
		{
			//��������
			BYTE cbTempData[MAX_COUNT];
			CopyMemory(cbTempData, m_cbHandCardData[wBeWinAndroid], sizeof(BYTE)*MAX_COUNT);
			CopyMemory(m_cbHandCardData[wBeWinAndroid], m_cbHandCardData[wWinUser], sizeof(BYTE)*MAX_COUNT);
			CopyMemory(m_cbHandCardData[wWinUser], cbTempData, sizeof(BYTE)*MAX_COUNT);
		}
	}
	//�������
	else if (m_lStockScore > m_lStorageMax && rand()%100 <= m_nStorageMul)
	{
		//���Ӯ��
		WORD wWinPlayer = INVALID_CHAIR;

		do 
		{
			wWinPlayer = rand()%GAME_PLAYER;
		} while (m_pITableFrame->GetTableUserItem(wWinPlayer) == NULL || m_pITableFrame->GetTableUserItem(wWinPlayer)->IsAndroidUser());

		if(wWinPlayer != wWinUser)
		{
			//��������
			BYTE cbTempData[MAX_COUNT];
			CopyMemory(cbTempData, m_cbHandCardData[wWinPlayer], sizeof(BYTE)*MAX_COUNT);
			CopyMemory(m_cbHandCardData[wWinPlayer], m_cbHandCardData[wWinUser], sizeof(BYTE)*MAX_COUNT);
			CopyMemory(m_cbHandCardData[wWinUser], cbTempData, sizeof(BYTE)*MAX_COUNT);
		}
	}

	return;
}

//�Ƿ�˥��
bool CTableFrameSink::NeedDeductStorage()
{
	//��������
	WORD wAiCount = 0;
	WORD wPlayerCount = 0;
	for (WORD i=0; i<m_wPlayerCount; i++)
	{
		//��ȡ�û�
		IServerUserItem * pIServerUserItem=m_pITableFrame->GetTableUserItem(i);
		if (pIServerUserItem!=NULL)
		{
			if(m_cbPlayStatus[i]==FALSE)continue;
			if(pIServerUserItem->IsAndroidUser()) 
			{
				wAiCount++ ;
			}
			wPlayerCount++;
		}
	}

	return wPlayerCount != wAiCount && wAiCount > 0;

}

//�޸Ŀ��
bool CTableFrameSink::UpdateStorage(LONGLONG lScore)
{
	if(!m_bUpdataStorage) return true;

//	ASSERT(lScore >= 0);
	LONGLONG lStockScore = m_lStockScore;
	m_lStockScore += lScore;

	//���Ϊ��
	if (m_lStockScore < 0)
	{
		CString str;
		CString strTemp;
		strTemp.Format(TEXT("%d�� �����ע%I64d ���Ϊ��%I64dԭ���%I64d"), m_pITableFrame->GetTableID() + 1, m_lMaxCellScore, m_lStockScore, lStockScore);
		str += strTemp;
		for (WORD i=0;i<m_wPlayerCount;i++)
		{
			if(m_lUserMaxScore[i] > 0)
			{
				strTemp.Format(TEXT("��%d�����������ע%I64d��"), i, m_lUserMaxScore[i]);
				str += strTemp;
				//��ȡ�û�
				IServerUserItem *pIServerUserItem=m_pITableFrame->GetTableUserItem(i);
				if (pIServerUserItem!=NULL)
				{
					strTemp.Format(TEXT("UserID=%ld��������%d������%I64d����עΪ%I64d������%d������%d���˿ˣ�"), pIServerUserItem->GetUserID(), pIServerUserItem->IsAndroidUser(), pIServerUserItem->GetUserScore(), m_lTableScore[i], m_bMingZhu[i], m_cbGiveUpUser[i]);
					str += strTemp;
				}
				else
				{
					strTemp.Format(TEXT("�Ѿ��뿪���ӣ���עΪ%I64d ����%d������%d���˿ˣ�"), m_lTableScore[i], m_bMingZhu[i], m_cbGiveUpUser[i]);
					str += strTemp;
				}

				for (int j = 0; j < MAX_COUNT; j++)
				{
					strTemp.Format(TEXT("%02x "), m_cbHandCardData[i][j]);
					str += strTemp;
				}
			}
		}
		NcaTextOut(str, m_pGameServiceOption->szServerName);
		return false;
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//˽�˷�����
VOID CTableFrameSink::SetPersonalGameRule()
{
	OutputDebugString(TEXT("CTableFrameSink::SetPersonalGameRule"));

	BYTE cbRulle[RULE_LEN];
	memset(cbRulle, 0, sizeof(cbRulle));
	memcpy(cbRulle, m_pITableFrame->GetGameRule(), RULE_LEN);

	//���ò�������
	if (cbRulle[1] >= 2)
	{
		m_pITableFrame->SetTableChairCount(cbRulle[1]);
		m_wPlayerCount = cbRulle[1];
	}
	return;
}
