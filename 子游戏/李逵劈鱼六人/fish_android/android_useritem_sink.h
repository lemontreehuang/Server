
#ifndef ANDROID_USER_ITEM_SINK_H_
#define ANDROID_USER_ITEM_SINK_H_
#pragma once

//��������
class CAndroidUserItemSink : public IAndroidUserItemSink
{
protected:
	IAndroidUserItem *				m_pIAndroidUserItem;				//�û��ӿ�

private:
  int exchange_ratio_userscore_;
  int exchange_ratio_fishscore_;
  int exchange_count_;

  int min_bullet_multiple_;
  int max_bullet_multiple_;

  BulletKind current_bullet_kind_;
  int current_bullet_mulriple_;
  bool allow_fire_;

  SCORE exchange_fish_score_;
  SCORE fish_score_;

  float last_fire_angle_;
  int exchange_times_;

	//��������
public:
	//���캯��
	CAndroidUserItemSink();
	//��������
	virtual ~CAndroidUserItemSink();

	//�����ӿ�
public:
	//�ͷŶ���
	virtual VOID Release() { }
	//�Ƿ���Ч
	virtual bool IsValid() { return AfxIsValidAddress(this,sizeof(CAndroidUserItemSink))?true:false; }
	//�ӿڲ�ѯ
	virtual void * QueryInterface(const IID & Guid, DWORD dwQueryVer);

	//���ƽӿ�
public:
	//��ʼ�ӿ�
	virtual bool Initialization(IUnknownEx * pIUnknownEx);
	//���ýӿ�
	virtual bool RepositionSink();

	//��Ϸ�¼�
public:
	//ʱ����Ϣ
	virtual bool OnEventTimer(UINT nTimerID);
	//��Ϸ��Ϣ
	virtual bool OnEventGameMessage(WORD wSubCmdID, void * pData, WORD wDataSize);
	//��Ϸ��Ϣ
	virtual bool OnEventFrameMessage(WORD wSubCmdID, void * pData, WORD wDataSize);
	//������Ϣ
	virtual bool OnEventSceneMessage(BYTE cbGameStatus, bool bLookonOther, VOID * pData, WORD wDataSize);

	//�û��¼�
public:
	//�û�����
  virtual void OnEventUserEnter(IAndroidUserItem * pIAndroidUserItem, bool bLookonUser) {}
	//�û��뿪
	virtual void OnEventUserLeave(IAndroidUserItem * pIAndroidUserItem, bool bLookonUser) {}
	//�û�����
	virtual void OnEventUserScore(IAndroidUserItem * pIAndroidUserItem, bool bLookonUser) {}
	//�û�״̬
	virtual void OnEventUserStatus(IAndroidUserItem * pIAndroidUserItem, bool bLookonUser) {}
	//�û���λ
	virtual void OnEventUserSegment(IAndroidUserItem * pIAndroidUserItem, bool bLookonUser) {}

	// ��Ϣ����
protected:
  bool OnSubGameConfig(void* data, WORD data_size);
  bool OnSubExchangeFishScore(void* data, WORD data_size);
  bool OnSubUserFire(void* data, WORD data_size);
  bool OnSubCatchFish(void* data, WORD data_size);
  bool OnSubBulletIonTimeout(void* data, WORD data_size);
  bool OnSubCatSweepFishResult(void* data, WORD data_size);
  bool OnSubSwitchScene(void* data, WORD data_size);

private:
  void ExchangeFishScore();
  void Fire();
  float GetAngle(WORD chair_id);
};

#endif  // ANDROID_USER_ITEM_SINK_H_
