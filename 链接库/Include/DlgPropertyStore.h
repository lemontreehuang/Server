#ifndef DLG_PROPERTY_STORE_HEAD_FILE
#define DLG_PROPERTY_STORE_HEAD_FILE

#pragma once

#include "GamePropertyHead.h"
#include "GamePropertyItem.h"

//////////////////////////////////////////////////////////////////////////////////
#define CX_COUNT            2           //�������
#define CY_COUNT            2           //�������

//////////////////////////////////////////////////////////////////////////////////
//��Ϸ����
class GAME_PROPERTY_CLASS CDlgPropertyStore : public CDialog
{
  //��ť����
protected:
  CSkinButton           m_btCancel;             //ȡ����ť
  CSkinButton                     m_btPrev;             //���ư�ť
  CSkinButton                     m_btNext;             //���ư�ť
  CSkinButton           m_btBuy[CX_COUNT*CY_COUNT];     //����ť
  CSkinButton           m_btTransfer[CX_COUNT*CY_COUNT];  //���Ͱ�ť
  CSkinButton           m_btPageNo[10];           //ҳ�밴ť

  //��������
protected:
  BYTE              m_cbCurPageNo;            //��ǰҳ��
  BYTE              m_cbPageCount;            //����ҳ��
  BYTE              m_cbPropertyCount;          //������Ŀ
  CGamePropertyItem *             m_pCurrPropertyItem;                //��ǰ����
  CGamePropertyItem *       m_pGamePropertyItem[MAX_PROPERTY];  //��������

  //�ӿڱ���
protected:
  IGamePropertySink *       m_pIGamePropertySink;       //�ص��ӿ�

  CFont             m_FontBold;             //��������

  //��������
public:
  //���캯��
  CDlgPropertyStore();
  //��������
  virtual ~CDlgPropertyStore();

  //���ú���
protected:
  //�ؼ���
  virtual VOID DoDataExchange(CDataExchange * pDX);
  //��Ϣ����
  virtual BOOL PreTranslateMessage(MSG * pMsg);
  //��������
  virtual BOOL OnInitDialog();
  //ȷ������
  virtual VOID OnOK();
  //ȡ����Ϣ
  virtual VOID OnCancel();

  //���溯��
private:
  //�����ؼ�
  VOID RectifyControl(INT nWidth, INT nHeight);

  //���ú���
public:
  //���ýӿ�
  bool SetGamePropertySink(IUnknownEx * pIUnknownEx);
  //���õ���
  bool SetGamePropertyInfo(tagPropertyInfo PropertyInfo[], BYTE cbPropertyCount, WORD wIssueArea);
  //�ı��¼�
  VOID OnSelectedUserItemChange(IClientUserItem * pIClintUserItem);

  //�ڲ�����
protected:
  //����ж�
  WORD SwitchItemFromPoint(CPoint MousePoint);

  //��Ϣӳ��
protected:
  //�滭����
  BOOL OnEraseBkgnd(CDC * pDC);
  //���ư�ť
  VOID OnBtnClickedPrev();
  //���ư�ť
  VOID OnBtnClickedNext();
  //�������
  VOID OnBnClickedBuy(UINT nCommandID);
  //���͵���
  VOID OnBnClickedTransfer(UINT nCommandID);
  //ҳ�밴ť
  VOID OnBnClickedPageNo(UINT nCommandID);

  DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

#endif