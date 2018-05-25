#ifndef __MONITOR_MANAGER_
#define __MONITOR_MANAGER_

#include "../../../platform/platform.h"
#include "Win32MonitorManager.h"

namespace VF {
	namespace Window {
		#ifdef WINDOWS
		typedef VF::Window::Win32MonitorManager MonitorManager;
		#endif
	}
}

#endif