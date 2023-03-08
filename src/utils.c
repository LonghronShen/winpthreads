#include <windows.h>

#include <stdlib.h>
#include <string.h>

#include "utils.h"

#ifdef _DEBUG
# define BUILD_TYPE     "Debug"
# define DEBUG_DEFAULT  2
#else
# define BUILD_TYPE     "Release"
# define DEBUG_DEFAULT  0
#endif

int         g_nPlatform             = MZ_NOT_INITIALIZED;
int         g_nPlatformServicePack  = 0;
int         g_nDebug                = DEBUG_DEFAULT;

int GetServicePack(const char *aVersion) {
  static const char szServicePack[] = "Service Pack ";
  static int ServicePackNumberOffset = sizeof(szServicePack) - 1;
  if (strncmp(aVersion, szServicePack, ServicePackNumberOffset))
    return 0;
  return aVersion[ServicePackNumberOffset] - '0';
}

BOOL InitializeSystemVersion() {
  OSVERSIONINFOA osvi;
  ZeroMemory(&osvi, sizeof(osvi));
  osvi.dwOSVersionInfoSize = sizeof(osvi);
  if (!GetVersionExA(&osvi))
    return FALSE;

  switch (osvi.dwMajorVersion) {
  case 3:
    g_nPlatform = MZ_PLATFORM_NT35;
    g_nPlatformServicePack = GetServicePack(osvi.szCSDVersion);
    break;

  case 4:
    switch (osvi.dwMinorVersion) {
    case 0:
      if (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT) {
        g_nPlatform = MZ_PLATFORM_NT4;
        g_nPlatformServicePack = GetServicePack(osvi.szCSDVersion);
      } else {
        g_nPlatform = MZ_PLATFORM_95;
        if (osvi.szCSDVersion[0] == 'C')
          g_nPlatformServicePack = 2; // OSR2
      }
      break;

    case 10:
      g_nPlatform = MZ_PLATFORM_98;
      if (osvi.szCSDVersion[0] == 'A')
        g_nPlatformServicePack = 2; // 98SE
      break;

    case 90:
      g_nPlatform = MZ_PLATFORM_ME;
    }
    break;

  case 5:
    switch (osvi.dwMinorVersion) {
    case 0:
      g_nPlatform = MZ_PLATFORM_2K;
      break;

    case 1:
      g_nPlatform = MZ_PLATFORM_XP;
      break;

    case 2:
      g_nPlatform = MZ_PLATFORM_2K3;
      break;
    }
    g_nPlatformServicePack = GetServicePack(osvi.szCSDVersion);
  }

  return TRUE;
}