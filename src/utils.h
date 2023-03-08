#ifndef _UTILS_H
#define _UTILS_H

enum MzPlatformType {
  MZ_NOT_INITIALIZED = 0,

  // native unicode == FALSE
  MZ_PLATFORM_95 = -3, // 95 == SP0, OSR2 == SP2
  MZ_PLATFORM_98 = -2, // 98 == SP0, SE == SP2
  MZ_PLATFORM_ME = -1,

  // native unicode == TRUE
  MZ_PLATFORM_NT35 = 1,
  MZ_PLATFORM_NT4 = 2,
  MZ_PLATFORM_2K = 3,
  MZ_PLATFORM_XP = 4,
  MZ_PLATFORM_2K3 = 5
};

extern int g_nPlatform;
extern int g_nPlatformServicePack;

#endif