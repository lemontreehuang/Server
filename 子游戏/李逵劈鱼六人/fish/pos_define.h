
#ifndef POS_DEFINE_H_
#define POS_DEFINE_H_

// �Լ���Ϣ�߶�
const int kBottomHeight = 40;

// �ڱ�����
const FPoint kPosBoard[GAME_PLAYER] = { {233,47}, {700,47}, {1155,47}, {1137,721-kBottomHeight}, {670,721-kBottomHeight}, {215,721-kBottomHeight} };

// �ڸ���Ȧ
const FPoint kPosDeco[GAME_PLAYER] = { {233,41}, {700,41}, {1155,41},  {1137,727-kBottomHeight}, {670,727-kBottomHeight}, {215,727-kBottomHeight} };

// �ں����
const FPoint kPosSeat[GAME_PLAYER] = { {233,21}, {700,21}, {1155,21},  {1137,748-kBottomHeight}, {670,748-kBottomHeight}, {215,748-kBottomHeight} };

// ��Ͳ��
const FPoint kPosGun[GAME_PLAYER] = { {233,67}, {700,67}, {1155,67}, {1137,701-kBottomHeight}, {670,701-kBottomHeight}, {215,701-kBottomHeight} };

// �ڱ���
const FPoint kPosCannonMul[GAME_PLAYER] = { {233,25}, {700,25}, {1155,25}, {1137,742-kBottomHeight}, {670,742-kBottomHeight}, {215,742-kBottomHeight}};

// ��ֵ��
const FPoint kPosScoreBox[GAME_PLAYER] = { {80,45}, {528,45}, {995,45},{1295,723-kBottomHeight}, {828,723-kBottomHeight}, {375,723-kBottomHeight}};

// ����
const FPoint kPosScore[GAME_PLAYER] = { {22,45}, {470,45}, {935,45}, {1353,723-kBottomHeight}, {888,723-kBottomHeight}, {434,723-kBottomHeight}};

// ��Ҷ�
const FPoint kPosStack[GAME_PLAYER] = { {358,0}, {825,0}, {1280,0},{1012,768-kBottomHeight}, {545,768-kBottomHeight}, {90,768-kBottomHeight}};

// �����ڿ�Ƭ
const FPoint kPosCardIon[GAME_PLAYER] = { {180,162}, {650,162}, {1100,162}, {1190,606-kBottomHeight}, {720,606-kBottomHeight}, {270,606-kBottomHeight} };

// ������Ƭ
const FPoint kPosLockFlag[GAME_PLAYER] = { {286,162}, {750,162}, {1210,162}, {1085,606-kBottomHeight}, {620,606-kBottomHeight}, {160,606-kBottomHeight} };

#endif	// POS_DEFINE_H_