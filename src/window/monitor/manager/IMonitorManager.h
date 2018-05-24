#ifndef __IMONITOR_MANAGER_
#define __IMONITOR_MANAGER_

#include <vector>
#include "../Monitor.h"

namespace VF {
	namespace Window {
		class IMonitorManager {
		public:
			virtual std::vector<Monitor *> GetMonitors() = 0;
			virtual Monitor * GetPrimaryMonitor() = 0;
		protected:
			std::vector<Monitor *> monitors;
		private:
		};
	}
}

#endif