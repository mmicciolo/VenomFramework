#include "Monitor.h"

VF::Window::Monitor::Monitor() {

}

VF::Window::Monitor::Monitor(MonitorPosition * position, MonitorSize * size, std::string name, std::vector<WindowMonitorVideoMode *> videoModes, WindowMonitorVideoMode currentVideoMode) {
	this->monitorPosition = position;
	this->monitorSize = size;
	this->monitorName = name;
	this->videoModes = videoModes;
	this->currentVideoMode = currentVideoMode;
}

VF::Window::MonitorPosition * VF::Window::Monitor::GetPosition() {
	return monitorPosition;
}

VF::Window::MonitorSize * VF::Window::Monitor::GetPhysicalSize() {
	return monitorSize;
}

std::string VF::Window::Monitor::GetName() {
	return monitorName;
}

std::vector<VF::Window::WindowMonitorVideoMode *> VF::Window::Monitor::GetVideoModes() {
	return videoModes;
}

VF::Window::WindowMonitorVideoMode VF::Window::Monitor::GetCurrentVideoMode() {
	return currentVideoMode;
}

VF::Window::MonitorPosition::MonitorPosition() {

}

VF::Window::MonitorPosition::MonitorPosition(int x, int y) {
	this->y = y;
	this->x = x;
}

VF::Window::MonitorSize::MonitorSize() {

}

VF::Window::MonitorSize::MonitorSize(int width, int height) {
	this->width = width;
	this->height = height;
}

VF::Window::WindowMonitorVideoMode::WindowMonitorVideoMode() {

}

VF::Window::WindowMonitorVideoMode::WindowMonitorVideoMode(int width, int height, int bitsPerPixel, int refreshRate) {
	this->width = width;
	this->height = height;
	this->bitsPerPixel = bitsPerPixel;
	this->refreshRate = refreshRate;
}