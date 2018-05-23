#include "Win32MonitorManager.h"

#ifdef WINDOWS

std::vector<Monitor *> Win32MonitorManager::GetMonitors() {

	monitors.clear();

	DISPLAY_DEVICE dd;
	ZeroMemory(&dd, sizeof(dd));
	dd.cb = sizeof(dd);

	for (int i = 0; EnumDisplayDevices(NULL, i, &dd, 0); i++)
	{
		if (dd.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP) {

			DEVMODE dm;
			ZeroMemory(&dm, sizeof(dm));
			dm.dmSize = sizeof(dm);

			EnumDisplaySettings(dd.DeviceName, ENUM_CURRENT_SETTINGS, &dm);

			MonitorPosition * position = new MonitorPosition(dm.dmPosition.x, dm.dmPosition.y);
			MonitorSize * size = new MonitorSize(dm.dmPelsWidth, dm.dmPelsHeight);
			std::string deviceName = dd.DeviceName;
			std::vector<WindowMonitorVideoMode *> * videoModes = new std::vector<WindowMonitorVideoMode *>();

			WindowMonitorVideoMode * currentVideoMode = new WindowMonitorVideoMode(dm.dmPelsWidth, dm.dmPelsHeight, dm.dmBitsPerPel, dm.dmDisplayFrequency);

			int modeIndex = 0;

			for (;;) {
				ZeroMemory(&dm, sizeof(dm));
				dm.dmSize = sizeof(dm);
				EnumDisplaySettings(dd.DeviceName, modeIndex, &dm);
				if (dm.dmPelsWidth == 0 && dm.dmPelsHeight == 0) {
					break;
				}
				modeIndex++;
				WindowMonitorVideoMode * videoMode = new WindowMonitorVideoMode(dm.dmPelsWidth, dm.dmPelsHeight, dm.dmBitsPerPel, dm.dmDisplayFrequency);
				videoModes->push_back(videoMode);
			}

			Monitor * monitor = new Monitor(position, size, deviceName, *videoModes, *currentVideoMode);

			monitors.push_back(monitor);
		}
	}

	return monitors;
}

Monitor * Win32MonitorManager::GetPrimaryMonitor() {
	monitors.clear();
	std::vector<Monitor *> monitors = GetMonitors();
	if (monitors.size() > 0) {
		return GetMonitors()[0];
	}
	return new Monitor();
}

#endif