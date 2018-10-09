#ifndef DLG_TRANSFER_PROOF_HEAD_FILE
#define DLG_TRANSFER_PROOF_HEAD_FILE

#pragma once

//////////////////////////////////////////////////////////////////////////////////
struct tagTansferProofInfo
{
  DWORD           dwSrcUserID;              //���ID
  DWORD           dwDesUserID;              //Ŀ��ID
  DWORD           dwRecordIndex;              //��¼���
  SCORE           lTransferScore;             //���ͽ��
  CTime           tRecvTime;                //����ʱ��
  TCHAR           szSrcNickName[LEN_NICKNAME];      //����ǳ�
  TCHAR           szDesNickName[LEN_NICKNAME];      //Ŀ���ǳ�
  TCHAR           szScoreCHZ[128];            //����д
};
//////////////////////////////////////////////////////////////////////////////////

//��Ϣ����
class SHARE_CONTROL_CLASS CDlgTransferProof : public CDialog
{
  //��Ϣ����
protected:
  tagTansferProofInfo *     m_pTansferProofInfo;          //ƾ֤����

  //�ؼ�����
protected:
  CSkinButton           m_btOK;               //ȷ����ť

  CSkinLayered          m_SkinLayered;            //�ֲ㴰��

  //��������
public:
  //���캯��
  CDlgTransferProof();
  //��������
  virtual ~CDlgTransferProof();

  //���غ���
protected:
  //�ؼ���
  virtual VOID DoDataExchange(CDataExchange * pDX);
  //��Ϣ����
  virtual BOOL PreTranslateMessage(MSG * pMsg);
  //��ʼ����Ϣ
  virtual BOOL OnInitDialog();
  //ȷ������
  virtual VOID OnOK();

  //���ܺ���
public:
  //������Ϣ
  VOID SetTransferProofInfo(tagTansferProofInfo *pTansferProofInfo)
  {
    m_pTansferProofInfo=pTansferProofInfo;
  }

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

  DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////
#endif