#pragma once

//////////////////////////////////////////////////////////////////////////////////

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN
#endif

#ifndef WINVER
#define WINVER 0x0501
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif

#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS 0x0501
#endif

#ifndef _WIN32_IE
#define _WIN32_IE 0x0400
#endif

#define _ATL_ATTRIBUTES
#define _AFX_ALL_WARNINGS
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS

//////////////////////////////////////////////////////////////////////////////////

//MFC �ļ�
#include <AfxWin.h>
#include <AfxExt.h>
#include <AfxCmn.h>
#include <AfxDisp.h>
#include <AtlBase.h>
#include <AtlDbcli.h>
#include <AfxDtctl.h>

//���뻷��
#include "..\..\..\SDKCondition.h"

//�����ļ�
#include "Other\SkinSB.h"
#include "Other\Detours.h"
//���Ӵ���
#pragma comment (lib,"Other/SkinSB.lib")
#pragma comment (lib,"Other/Detours.lib")
#pragma comment( lib,"strsafe.lib" )

#define __BANKER___
///////////////////////////////////////////////////////////////////////////////////


#ifdef SDK_CONDITION

//////////////////////////////////////////////////////////////////////////////////
//��������

#include "..\..\..\�ͻ������\��Ϸ���\GameFrameHead.h"

#ifndef _DEBUG
#ifndef _UNICODE
#pragma comment (lib,"../../../���ӿ�/Ansi/WHImage.lib")
#pragma comment (lib,"../../../���ӿ�/Ansi/GameFrame.lib")
#pragma comment (lib,"../../../���ӿ�/Ansi/GameEngine.lib")
#pragma comment (lib,"../../../���ӿ�/Ansi/SkinControl.lib")
#pragma comment (lib,"../../../���ӿ�/Ansi/ServiceCore.lib")
#pragma comment (lib,"../../../���ӿ�/Ansi/ShareControl.lib")
#else
#pragma comment (lib,"../../../���ӿ�/unicode/WHImage.lib")
#pragma comment (lib,"../../../���ӿ�/unicode/GameFrame.lib")
#pragma comment (lib,"../../../���ӿ�/unicode/GameEngine.lib")
#pragma comment (lib,"../../../���ӿ�/unicode/SkinControl.lib")
#pragma comment (lib,"../../../���ӿ�/unicode/ServiceCore.lib")
#pragma comment (lib,"../../../���ӿ�/unicode/ShareControl.lib")

#endif
#else
#ifndef _UNICODE
#pragma comment (lib,"../../../���ӿ�/Ansi/WHImageD.lib")
#pragma comment (lib,"../../../���ӿ�/Ansi/GameFrameD.lib")
#pragma comment (lib,"../../../���ӿ�/Ansi/GameEngineD.lib")
#pragma comment (lib,"../../../���ӿ�/Ansi/SkinControlD.lib")
#pragma comment (lib,"../../../���ӿ�/Ansi/ServiceCoreD.lib")
#pragma comment (lib,"../../../���ӿ�/Ansi/ShareControlD.lib")
#else
#pragma comment (lib,"../../../���ӿ�/unicode/WHImageD.lib")
#pragma comment (lib,"../../../���ӿ�/unicode/GameFrameD.lib")
#pragma comment (lib,"../../../���ӿ�/unicode/GameEngineD.lib")
#pragma comment (lib,"../../../���ӿ�/unicode/SkinControlD.lib")
#pragma comment (lib,"../../../���ӿ�/unicode/ServiceCoreD.lib")
#pragma comment (lib,"../../../���ӿ�/unicode/ShareControlD.lib")
#endif
#endif

//////////////////////////////////////////////////////////////////////////////////

#else

//////////////////////////////////////////////////////////////////////////////////
//ϵͳ����

#include "..\..\..\�ͻ������\��Ϸ���\GameFrameHead.h"

#ifndef _DEBUG
#ifndef _UNICODE
#pragma comment (lib,"../../../���ӿ�/Ansi/WHImage.lib")
#pragma comment (lib,"../../../���ӿ�/Ansi/GameFrame.lib")
#pragma comment (lib,"../../../���ӿ�/Ansi/GameEngine.lib")
#pragma comment (lib,"../../../���ӿ�/Ansi/SkinControl.lib")
#pragma comment (lib,"../../../���ӿ�/Ansi/ServiceCore.lib")
#else
#pragma comment (lib,"../../../���ӿ�/unicode/WHImage.lib")
#pragma comment (lib,"../../../���ӿ�/unicode/GameFrame.lib")
#pragma comment (lib,"../../../���ӿ�/unicode/GameEngine.lib")
#pragma comment (lib,"../../../���ӿ�/unicode/SkinControl.lib")
#pragma comment (lib,"../../../���ӿ�/unicode/ServiceCore.lib")
#endif
#else
#ifndef _UNICODE
#pragma comment (lib,"../../../���ӿ�/Ansi/WHImageD.lib")
#pragma comment (lib,"../../../���ӿ�/Ansi/GameFrameD.lib")
#pragma comment (lib,"../../../���ӿ�/Ansi/GameEngineD.lib")
#pragma comment (lib,"../../../���ӿ�/Ansi/SkinControlD.lib")
#pragma comment (lib,"../../../���ӿ�/Ansi/ServiceCoreD.lib")
#else
#pragma comment (lib,"../../../���ӿ�/unicode/WHImageD.lib")
#pragma comment (lib,"../../../���ӿ�/unicode/GameFrameD.lib")
#pragma comment (lib,"../../../���ӿ�/unicode/GameEngineD.lib")
#pragma comment (lib,"../../../���ӿ�/unicode/SkinControlD.lib")
#pragma comment (lib,"../../../���ӿ�/unicode/ServiceCoreD.lib")
#endif
#endif

//////////////////////////////////////////////////////////////////////////////////
#endif

//////////////////////////////////////////////////////////////////////////////////

#include "..\��Ϣ����\CMD_Game.h"

//////////////////////////////////////////////////////////////////////////////////