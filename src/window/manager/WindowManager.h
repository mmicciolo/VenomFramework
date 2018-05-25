#ifndef __WINDOW_MANAGER_
#define __WINDOW_MANAGER_

#include "Win32WindowManager.h"
#include "../../platform/platform.h"

namespace VF {
	namespace Window {
		#ifdef WINDOWS
		typedef VF::Window::Win32WindowManager WindowManager;
		#endif
	}
}

#endif
