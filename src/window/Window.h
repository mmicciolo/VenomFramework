#ifndef __WINDOW_
#define __WINDOW_

#include "Win32Window.h"
#include "../platform/platform.h"

namespace VF {
	namespace Window {
		#ifdef WINDOWS
		typedef VF::Window::Win32Window Window;
		#endif
	}
}

#endif