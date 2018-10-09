// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���ǳ��õ��������ĵ���Ŀ�ض��İ����ļ�
//

#pragma once

#define WIN32_LEAN_AND_MEAN		// �� Windows ͷ���ų�����ʹ�õ�����

// Windows ͷ�ļ�:
#include <windows.h>
#include <Mmsystem.h>
// C ����ʱͷ�ļ�
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdio.h>
#include <assert.h>

#ifndef ASSERT
#define ASSERT(x) assert(x) // for mfc ASSERT
#endif
#include <WTypes.h> // for DOUBLE

#ifdef _DEBUG
//#include <vld.h>
#endif

//#define TEST  // ���������ʾ��Χ��

// ArraySizeHelper��һ����������Ϊchar[N]�ĺ���,���β�����Ϊ T[N].
// ����û��Ҫʵ��, ��Ϊsizeofֻ��Ҫ����.
template <typename T, size_t N>
char (&ArraySizeHelper(T (&array)[N]))[N];

// arraysize(arr)����array�����Ԫ�ظ���. �ñ��ʽ�Ǳ���ʱ����,
// �������ڶ����µ�����. �������һ��ָ��ᱨ����ʱ����.
#define arraysize(array) (sizeof(ArraySizeHelper(array)))

#define SAFE_DELETE(x) { if (NULL != (x)) { delete (x); (x) = NULL; } }

#include "..\command\CMD_Fish.h"

//���뻷��
#include "..\..\..\SDKCondition.h"

//////////////////////////////////////////////////////////////////////////////////
#ifdef SDK_CONDITION

#include "..\..\..\������\Include\Macro.h"
#include "..\..\..\������\Include\Define.h"
#include "..\..\..\������\Include\Struct.h"
#include "..\..\..\������\Include\Packet.h"
#include "..\..\..\������\Include\Property.h"
#include "..\..\..\������\Include\PacketAide.h"
#include "..\..\..\������\Include\RightDefine.h"
#include "..\..\..\������\Include\CMD_Commom.h"
#include "..\..\..\������\Include\CMD_GameServer.h"
#include "..\..\..\������\Include\IPC_GameFrame.h"

#else

#include "..\..\..\..\ϵͳģ��\ȫ�ֶ���\Macro.h"
#include "..\..\..\..\ϵͳģ��\ȫ�ֶ���\Define.h"
#include "..\..\..\..\ϵͳģ��\ȫ�ֶ���\Struct.h"
#include "..\..\..\..\ϵͳģ��\ȫ�ֶ���\Packet.h"
#include "..\..\..\..\ϵͳģ��\ȫ�ֶ���\Property.h"
#include "..\..\..\..\ϵͳģ��\ȫ�ֶ���\PacketAide.h"
#include "..\..\..\..\ϵͳģ��\ȫ�ֶ���\RightDefine.h"
#include "..\..\..\..\ϵͳģ��\��Ϣ����\CMD_Commom.h"
#include "..\..\..\..\ϵͳģ��\��Ϣ����\CMD_GameServer.h"
#include "..\..\..\..\ϵͳģ��\��Ϣ����\IPC_GameFrame.h"

#endif

//#define VERSION_FRAME   PROCESS_VERSION(11,0,3)   // ��ܰ汾
#define VERSION_FRAME   101384195       // �������ΪPROCESS_VERSION(11,0,3)��ֵ,�Լ�ת��һ��
