#ifndef __MONITOR_MANAGER_
#define __MONITOR_MANAGER_

#include "../../../platform/platform.h"
#include "Win32MonitorManager.h"

#ifdef WINDOWS
typedef Win32MonitorManager MonitorManager;
#endif

#endif