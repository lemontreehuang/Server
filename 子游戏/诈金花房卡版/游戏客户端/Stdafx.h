#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN    // �� Windows ��ͷ���ų�����ʹ�õ�����
#endif

// ���������ʹ��������ָ����ƽ̨֮ǰ��ƽ̨�����޸�����Ķ��塣
// �йز�ͬƽ̨����Ӧֵ��������Ϣ����ο� MSDN��
#ifndef WINVER        // ����ʹ�� Windows 95 �� Windows NT 4 ����߰汾���ض����ܡ�
#define WINVER 0x0501   //Ϊ Windows98 �� Windows 2000 �����°汾�ı�Ϊ�ʵ���ֵ��
#endif

#ifndef _WIN32_WINNT    // ����ʹ�� Windows NT 4 ����߰汾���ض����ܡ�
#define _WIN32_WINNT 0x0501   //Ϊ Windows98 �� Windows 2000 �����°汾�ı�Ϊ�ʵ���ֵ��
#endif

#ifndef _WIN32_WINDOWS    // ����ʹ�� Windows 98 ����߰汾���ض����ܡ�
#define _WIN32_WINDOWS 0x0501 //Ϊ Windows Me �����°汾�ı�Ϊ�ʵ���ֵ��
#endif

#ifndef _WIN32_IE     // ����ʹ�� IE 4.0 ����߰汾���ض����ܡ�
#define _WIN32_IE 0x0400  //Ϊ IE 5.0 �����°汾�ı�Ϊ�ʵ���ֵ��
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS  // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ��������������ȫ���Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ���ĺͱ�׼���
#include <afxext.h>         // MFC ��չ
#include <afxdisp.h>        // MFC �Զ�����

#include <afxdtctl.h>   // Internet Explorer 4 �����ؼ��� MFC ֧��
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>     // Windows �����ؼ��� MFC ֧��
#endif // _AFX_NO_AFXCMN_SUPPORT


#include "..\��Ϣ����\CMD_ZaJinHua.h"


//////////////////////////////////////////////////////////////////////////
//���Ӵ���

#pragma comment( lib,"strsafe.lib" )


//////////////////////////////////////////////////////////////////////////////////

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
#pragma comment (lib,"../../../���ӿ�/Ansi/ServiceCore.lib")
#pragma comment (lib,"../../../���ӿ�/Ansi/ShareControl.lib")
//#pragma comment (lib,"../../../���ӿ�/Ansi/FGuilib.lib")
//#pragma comment (lib,"../../../���ӿ�/Ansi/FGuimfcFactory.lib")
#else
#pragma comment (lib,"../../../���ӿ�/Unicode/WHImage.lib")
#pragma comment (lib,"../../../���ӿ�/Unicode/GameFrame.lib")
#pragma comment (lib,"../../../���ӿ�/Unicode/GameEngine.lib")
#pragma comment (lib,"../../../���ӿ�/Unicode/SkinControl.lib")
#pragma comment (lib,"../../../���ӿ�/Unicode/ServiceCore.lib")
#pragma comment (lib,"../../../���ӿ�/Unicode/ShareControl.lib")
//#pragma comment (lib,"../../../���ӿ�/Unicode/FGuilib.lib")
//#pragma comment (lib,"../../../���ӿ�/Unicode/FGuimfcFactory.lib")
#endif
#else
#ifndef _UNICODE
#pragma comment (lib,"../../../���ӿ�/Ansi/WHImageD.lib")
#pragma comment (lib,"../../../���ӿ�/Ansi/GameFrameD.lib")
#pragma comment (lib,"../../../���ӿ�/Ansi/GameEngineD.lib")
#pragma comment (lib,"../../../���ӿ�/Ansi/SkinControlD.lib")
#pragma comment (lib,"../../../���ӿ�/Ansi/ServiceCoreD.lib")
#pragma comment (lib,"../../../���ӿ�/Ansi/ShareControlD.lib")
//#pragma comment (lib,"../../../���ӿ�/Ansi/FGuilibD.lib")
//#pragma comment (lib,"../../../���ӿ�/Ansi/FGuimfcFactoryD.lib")
#else
#pragma comment (lib,"../../../���ӿ�/Unicode/WHImageD.lib")
#pragma comment (lib,"../../../���ӿ�/Unicode/GameFrameD.lib")
#pragma comment (lib,"../../../���ӿ�/Unicode/GameEngineD.lib")
#pragma comment (lib,"../../../���ӿ�/Unicode/SkinControlD.lib")
#pragma comment (lib,"../../../���ӿ�/Unicode/ServiceCoreD.lib")
#pragma comment (lib,"../../../���ӿ�/Unicode/ShareControlD.lib")
//#pragma comment (lib,"../../../���ӿ�/Unicode/FGuilibD.lib")
//#pragma comment (lib,"../../../���ӿ�/Unicode/FGuimfcFactoryD.lib")
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
#pragma comment (lib,"../../../���ӿ�/Ansi/ShareControl.lib")
#else
#pragma comment (lib,"../../../���ӿ�/Unicode/WHImage.lib")
#pragma comment (lib,"../../../���ӿ�/Unicode/GameFrame.lib")
#pragma comment (lib,"../../../���ӿ�/Unicode/GameEngine.lib")
#pragma comment (lib,"../../../���ӿ�/Unicode/SkinControl.lib")
#pragma comment (lib,"../../../���ӿ�/Unicode/ServiceCore.lib")
#pragma comment (lib,"../../../���ӿ�/Unicode/ShareControl.lib")
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
#pragma comment (lib,"../../../���ӿ�/Unicode/WHImageD.lib")
#pragma comment (lib,"../../../���ӿ�/Unicode/GameFrameD.lib")
#pragma comment (lib,"../../../���ӿ�/Unicode/GameEngineD.lib")
#pragma comment (lib,"../../../���ӿ�/Unicode/SkinControlD.lib")
#pragma comment (lib,"../../../���ӿ�/Unicode/ServiceCoreD.lib")
#pragma comment (lib,"../../../���ӿ�/Unicode/ShareControlD.lib")
#endif
#endif

//////////////////////////////////////////////////////////////////////////////////

#endif


//////////////////////////////////////////////////////////////////////////
