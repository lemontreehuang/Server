
#ifndef FISH_ANDROID_MANAGER_H_
#define FISH_ANDROID_MANAGER_H_
#pragma once

class CGameServiceManager : public IGameServiceManager {
 public:
  CGameServiceManager();
  virtual ~CGameServiceManager();

 public:
  virtual void Release() { return; }
  virtual void* QueryInterface(REFGUID guid, DWORD query_ver);

  // �����ӿ�
 public:
  // ��������
  virtual void* CreateTableFrameSink(REFGUID guid, DWORD query_ver);
  // ��������
  virtual void* CreateAndroidUserItemSink(REFGUID guid, DWORD query_ver);
  // ��������
  virtual void* CreateGameDataBaseEngineSink(REFGUID guid, DWORD query_ver);

  // �����ӿ�
 public:
  // �������
  virtual bool GetServiceAttrib(tagGameServiceAttrib& game_service_attrib);
  // ��������
  virtual bool RectifyParameter(tagGameServiceOption& game_service_option);
};

#endif  // FISH_ANDROID_MANAGER_H_
