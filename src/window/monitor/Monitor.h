#ifndef __IMONITOR_
#define __IMONITOR_

#include <vector>
#include <string>

namespace VF {
	namespace Window {
		class MonitorPosition {
		public:
			MonitorPosition();
			MonitorPosition(int x, int y);
			int x;
			int y;
		};

		class MonitorSize {
		public:
			MonitorSize();
			MonitorSize(int width, int height);
			int width;
			int height;
		};

		class WindowMonitorVideoMode {
		public:
			WindowMonitorVideoMode();
			WindowMonitorVideoMode(int width, int height, int bitsPerPixel, int refreshRate);
			int width;
			int height;
			int bitsPerPixel;
			int redBits;
			int greenBits;
			int blueBits;
			int refreshRate;
		private:
		};

		class Monitor {
		public:
			Monitor();
			Monitor(MonitorPosition * position, MonitorSize * size, std::string name, std::vector<WindowMonitorVideoMode *> videoModes, WindowMonitorVideoMode currentVideoMode);
			MonitorPosition * GetPosition();
			MonitorSize * GetPhysicalSize();
			std::string GetName();
			std::vector<WindowMonitorVideoMode *> GetVideoModes();
			WindowMonitorVideoMode GetCurrentVideoMode();
		protected:
			MonitorPosition * monitorPosition;
			MonitorSize * monitorSize;
			std::string monitorName;
			std::vector<WindowMonitorVideoMode *> videoModes;
			WindowMonitorVideoMode currentVideoMode;
		private:
		};
	}
}

#endif