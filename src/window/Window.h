#ifndef __WINDOW_
#define __WINDOW_

#include "Win32Window.h"
#include "../platform/platform.h"

#ifdef WINDOWS
typedef VF::Window::Win32Window Window;
#endif

#endif