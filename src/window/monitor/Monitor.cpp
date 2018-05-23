#include "Monitor.h"

Monitor::Monitor() {

}

Monitor::Monitor(MonitorPosition * position, MonitorSize * size, std::string name, std::vector<WindowMonitorVideoMode *> videoModes, WindowMonitorVideoMode currentVideoMode) {
	this->monitorPosition = position;
	this->monitorSize = size;
	this->monitorName = name;
	this->videoModes = videoModes;
	this->currentVideoMode = currentVideoMode;
}

MonitorPosition * Monitor::GetPosition() {
	return monitorPosition;
}

MonitorSize * Monitor::GetPhysicalSize() {
	return monitorSize;
}

std::string Monitor::GetName() {
	return monitorName;
}

std::vector<WindowMonitorVideoMode *> Monitor::GetVideoModes() {
	return videoModes;
}

WindowMonitorVideoMode Monitor::GetCurrentVideoMode() {
	return currentVideoMode;
}

MonitorPosition::MonitorPosition() {

}

MonitorPosition::MonitorPosition(int x, int y) {
	this->y = y;
	this->x = x;
}

MonitorSize::MonitorSize() {

}

MonitorSize::MonitorSize(int width, int height) {
	this->width = width;
	this->height = height;
}

WindowMonitorVideoMode::WindowMonitorVideoMode() {

}

WindowMonitorVideoMode::WindowMonitorVideoMode(int width, int height, int bitsPerPixel, int refreshRate) {
	this->width = width;
	this->height = height;
	this->bitsPerPixel = bitsPerPixel;
	this->refreshRate = refreshRate;
}