//#pragma once
//
////////////////////////////////////////////////////////////////////////////
//
//#ifndef VC_EXTRALEAN
//#define VC_EXTRALEAN
//#endif
//
//#ifndef WINVER
//#define WINVER 0x0500
//#endif
//
//#ifndef _WIN32_WINNT
//#define _WIN32_WINNT 0x0400
//#endif
//
//#ifndef _WIN32_WINDOWS
//#define _WIN32_WINDOWS 0x0410
//#endif
//
//#ifndef _WIN32_IE
//#define _WIN32_IE 0x0400
//#endif
//
//#define _ATL_ATTRIBUTES
//#define _AFX_ALL_WARNINGS
//#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS
//
////////////////////////////////////////////////////////////////////////////
//
////MFC �ļ�
//#include <AfxWin.h>
//#include <AfxExt.h>
//#include <AfxCmn.h>
//#include <AfxDisp.h>
//#include <AtlBase.h>
//#include <AtlDbcli.h>
//#include <AfxDtctl.h>
//#include <strsafe.h>
//#pragma warning( disable : 4995 )
//
////////////////////////////////////////////////////////////////////////////
//
////�����ļ�
//#include "GameOption.h"
//
////////////////////////////////////////////////////////////////////////////
////���Ӵ���
//
//#define SDK_CONDITION
//#ifdef SDK_CONDITION
//
////////////////////////////////////////////////////////////////////////////////////
////��������
//#include "..\��Ϣ����\CMD_ZodiacBattle.h"
//#include "..\..\..\������\Include\GameFrameHead.h"
//
//#ifndef _DEBUG
//#ifndef _UNICODE
//#pragma comment (lib,"../../../���ӿ�/Ansi/WHImage.lib")
////#pragma comment (lib,"../../../���ӿ�/Ansi/D3DEngine.lib")
//#pragma comment (lib,"../../../���ӿ�/Ansi/GameFrame.lib")
//#pragma comment (lib,"../../../���ӿ�/Ansi/SkinControl.lib")
//#else
//#pragma comment (lib,"../../../���ӿ�/Unicode/WHImage.lib")
////#pragma comment (lib,"../../../���ӿ�/Unicode/D3DEngine.lib")
//#pragma comment (lib,"../../../���ӿ�/Unicode/GameFrame.lib")
//#pragma comment (lib,"../../../���ӿ�/Unicode/SkinControl.lib")
//#endif
//#else
//#ifndef _UNICODE
//#pragma comment (lib,"../../../���ӿ�/Ansi/WHImageD.lib")
////#pragma comment (lib,"../../../���ӿ�/Ansi/D3DEngineD.lib")
//#pragma comment (lib,"../../../���ӿ�/Ansi/GameFrameD.lib")
//#pragma comment (lib,"../../../���ӿ�/Ansi/SkinControlD.lib")
//#else
//#pragma comment (lib,"../../../���ӿ�/Unicode/WHImageD.lib")
////#pragma comment (lib,"../../../���ӿ�/Unicode/D3DEngineD.lib")
//#pragma comment (lib,"../../../���ӿ�/Unicode/GameFrameD.lib")
//#pragma comment (lib,"../../../���ӿ�/Unicode/SkinControlD.lib")
//#endif
//#endif
//
////////////////////////////////////////////////////////////////////////////////////
//
//#else
//
////////////////////////////////////////////////////////////////////////////////////
////ϵͳ����
//
//#include "..\��Ϣ����\CMD_ZodiacBattle.h"
//#include "..\..\..\������\Include\GameFrameHead.h"
//
//#ifndef _DEBUG
//#ifndef _UNICODE
//#pragma comment (lib,"../../../���ӿ�/Ansi/WHImage.lib")
////#pragma comment (lib,"../../../../���ӿ�/Ansi/D3DEngine.lib")
//#pragma comment (lib,"../../../���ӿ�/Ansi/GameFrame.lib")
//#pragma comment (lib,"../../../���ӿ�/Ansi/SkinControl.lib")
//#else
//#pragma comment (lib,"../../../���ӿ�/Unicode/WHImage.lib")
////#pragma comment (lib,"../../../���ӿ�/Unicode/D3DEngine.lib")
//#pragma comment (lib,"../../../���ӿ�/Unicode/GameFrame.lib")
//#pragma comment (lib,"../../../���ӿ�/Unicode/SkinControl.lib")
//#endif
//#else
//#ifndef _UNICODE
//#pragma comment (lib,"../../../���ӿ�/Ansi/WHImageD.lib")
////#pragma comment (lib,"../../../���ӿ�/Ansi/D3DEngineD.lib")
//#pragma comment (lib,"../../../���ӿ�/Ansi/GameFrameD.lib")
//#pragma comment (lib,"../../../���ӿ�/Ansi/SkinControlD.lib")
//#else
//#pragma comment (lib,"../../../���ӿ�/Unicode/WHImageD.lib")
////#pragma comment (lib,"../../../���ӿ�/Unicode/D3DEngineD.lib")
//#pragma comment (lib,"../../../���ӿ�/Unicode/GameFrameD.lib")
//#pragma comment (lib,"../../../���ӿ�/Unicode/SkinControlD.lib")
//#endif
//#endif
//
////////////////////////////////////////////////////////////////////////////////////
//
//#endif



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

//////////////////////////////////////////////////////////////////////////////////


//�����ļ�
#include "Other\SkinSB.h"
#include "Other\Detours.h"

//ͼƬ�ؼ�
#import "ImageOle.dll" named_guids

//////////////////////////////////////////////////////////////////////////////////
//���Ӵ���

#pragma comment (lib,"Other/SkinSB.lib")
#pragma comment (lib,"Other/Detours.lib")

//���뻷��
#include "..\..\..\SDKCondition.h"

//////////////////////////////////////////////////////////////////////////////////
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
#pragma comment (lib,"../../../���ӿ�/Ansi/ShareControl.lib")
#pragma comment (lib,"../../../���ӿ�/Ansi/ServiceCore.lib")
#pragma comment (lib,"../../../���ӿ�/Ansi/GameProperty.lib")

#else
#pragma comment (lib,"../../../���ӿ�/Unicode/WHImage.lib")
#pragma comment (lib,"../../../���ӿ�/Unicode/GameFrame.lib")
#pragma comment (lib,"../../../���ӿ�/Unicode/GameEngine.lib")
#pragma comment (lib,"../../../���ӿ�/Unicode/SkinControl.lib")
#pragma comment (lib,"../../../���ӿ�/Unicode/ShareControl.lib")
#pragma comment (lib,"../../../���ӿ�/Unicode/ServiceCore.lib")
#pragma comment (lib,"../../../���ӿ�/Unicode/GameProperty.lib")
#endif
#else
#ifndef _UNICODE
#pragma comment (lib,"../../../���ӿ�/Ansi/WHImageD.lib")
#pragma comment (lib,"../../../���ӿ�/Ansi/GameFrameD.lib")
#pragma comment (lib,"../../../���ӿ�/Ansi/GameEngineD.lib")
#pragma comment (lib,"../../../���ӿ�/Ansi/SkinControlD.lib")
#pragma comment (lib,"../../../���ӿ�/Ansi/ShareControlD.lib")
#pragma comment (lib,"../../../���ӿ�/Ansi/ServiceCoreD.lib")
#pragma comment (lib,"../../../���ӿ�/Ansi/GamePropertyD.lib")

#else
#pragma comment (lib,"../../../���ӿ�/Unicode/WHImageD.lib")
#pragma comment (lib,"../../../���ӿ�/Unicode/GameFrameD.lib")
#pragma comment (lib,"../../../���ӿ�/Unicode/GameEngineD.lib")
#pragma comment (lib,"../../../���ӿ�/Unicode/SkinControlD.lib")
#pragma comment (lib,"../../../���ӿ�/Unicode/ShareControlD.lib")
#pragma comment (lib,"../../../���ӿ�/Unicode/ServiceCoreD.lib")
#pragma comment (lib,"../../../���ӿ�/Unicode/GamePropertyD.lib")
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
#pragma comment (lib,"../../../���ӿ�/Unicode/WHImage.lib")
#pragma comment (lib,"../../../���ӿ�/Unicode/GameFrame.lib")
#pragma comment (lib,"../../../���ӿ�/Unicode/GameEngine.lib")
#pragma comment (lib,"../../../���ӿ�/Unicode/SkinControl.lib")
#pragma comment (lib,"../../../���ӿ�/Unicode/ServiceCore.lib")
#endif
#else
#ifndef _UNICODE
#pragma comment (lib,"../../../���ӿ�/Ansi/WHImageD.lib")
#pragma comment (lib,"../../../���ӿ�/Ansi/GameFrameD.lib")
#pragma comment (lib,"../../../���ӿ�/Ansi/GameEngineD.lib")
#pragma comment (lib,"../../../���ӿ�/Ansi/SkinControlD.lib")
#pragma comment (lib,"../../../���ӿ�/Ansi/ServiceCoreD.lib")
#else
#pragma comment (lib,"../../../���ӿ�/Unicode/WHImageD.lib")
#pragma comment (lib,"../../../���ӿ�/Unicode/GameFrameD.lib")
#pragma comment (lib,"../../../���ӿ�/Unicode/GameEngineD.lib")
#pragma comment (lib,"../../../���ӿ�/Unicode/SkinControlD.lib")
#pragma comment (lib,"../../../���ӿ�/Unicode/ServiceCoreD.lib")
#endif
#endif

//////////////////////////////////////////////////////////////////////////////////

#endif

#define  __TEST__  1
#define  __BANKER___
#define  __SPECIAL___

//////////////////////////////////////////////////////////////////////////
#include "..\��Ϣ����\CMD_ZodiacBattle.h"


//////////////////////////////////////////////////////////////////////////
