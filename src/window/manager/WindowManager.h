#ifndef __WINDOW_MANAGER_
#define __WINDOW_MANAGER_

#include "Win32WindowManager.h"
#include "../../platform/platform.h"

#ifdef WINDOWS
typedef VF::Window::Win32WindowManager WindowManager;
#endif

#endif
