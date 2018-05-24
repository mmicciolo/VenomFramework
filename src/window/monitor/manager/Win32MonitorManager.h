#ifndef __WIN32_MONITOR_MANAGER_
#define __WIN32_MONITOR_MANAGER_

#include "IMonitorManager.h"
#include "../../../platform/platform.h"

#ifdef WINDOWS
#include <Windows.h>

namespace VF {
	namespace Window {
		class Win32MonitorManager : public IMonitorManager {
		public:
			std::vector<Monitor *> GetMonitors();
			Monitor * GetPrimaryMonitor();
		protected:
		private:
		};
	}
}

#endif

#endif