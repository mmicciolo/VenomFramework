#include "IWindowManager.h"
#include "../../platform/platform.h"

#ifdef WINDOWS
#include <Windows.h>

namespace VF {
	namespace Window {
		class Win32WindowManager : public IWindowManager {
		public:
			void AddWindow(IWindow * window);
			void RemoveWindow(IWindow * window);
			void PollForEvents();
			void ShutDown();
			IWindow * GetWindowByHandle(void * handlePtr);
		protected:
		private:
		};
	}
}

#endif