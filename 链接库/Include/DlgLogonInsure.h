#ifndef DLG_LOGON_INSURE_HEAD_FILE
#define DLG_LOGON_INSURE_HEAD_FILE

#pragma once

#include "MissionManager.h"
#include "PasswordControl.h"
#include "ShareControlHead.h"

//////////////////////////////////////////////////////////////////////////////////

//��Ϣ����
class SHARE_CONTROL_CLASS CDlgLogonInsure : public CDialog, public CMissionItem
{
  //��������
protected:
  bool                        m_bVerifyInsurePass;               //У������
  TCHAR             m_szInsurePass[LEN_MD5];      //��������

  //�ؼ�����
protected:
  CSkinButton           m_btOK;               //ȷ����ť
  CSkinButton           m_btCancel;             //ȡ����ť
  CSkinButton           m_btClose;              //�رհ�ť
  CSkinEdit           m_edInsurePass;           //����ؼ�
  CPasswordKeyboardEx       m_PasswordKeyboard;         //�����

  CSkinLayered          m_SkinLayered;            //�ֲ㴰��

  //�������
protected:
  CMissionManager         m_MissionManager;         //�������

  //��������
public:
  //���캯��
  CDlgLogonInsure();
  //��������
  virtual ~CDlgLogonInsure();

  //���غ���
protected:
  //�ؼ���
  virtual VOID DoDataExchange(CDataExchange * pDX);
  //��Ϣ����
  virtual BOOL PreTranslateMessage(MSG * pMsg);
  //��ʼ����Ϣ
  virtual BOOL OnInitDialog();
  //ȷ����Ϣ
  virtual VOID OnOK();
  //ȡ����Ϣ
  virtual VOID OnCancel();

  //�¼�����
public:
  //��ʼ����
  VOID OnMissionStart();
  //��ֹ����
  VOID OnMissionConclude();

  //�����¼�
private:
  //�����¼�
  virtual bool OnEventMissionLink(INT nErrorCode);
  //�ر��¼�
  virtual bool OnEventMissionShut(BYTE cbShutReason);
  //��ȡ�¼�
  virtual bool OnEventMissionRead(TCP_Command Command, VOID * pData, WORD wDataSize);

  //��Ϣ����
protected:
  //�滭����
  BOOL OnEraseBkgnd(CDC * pDC);
  //��ʾ��Ϣ
  VOID OnShowWindow(BOOL bShow, UINT nStatus);
  //�����Ϣ
  VOID OnLButtonDown(UINT nFlags, CPoint Point);
  //λ�øı�
  VOID OnWindowPosChanged(WINDOWPOS * lpWndPos);
  //�ر���Ϣ
  VOID OnBnClickedLogonClose();

  DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////
#endif