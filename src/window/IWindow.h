#ifndef __IWINDOW_
#define __IWINDOW_

#include <vector>
#include "monitor\Monitor.h"
#include "../input/KeyState.h"

class IWindowManager;

class IWindow {
public:
	friend class Keyboard;
	virtual void CreateNativeWindow(IWindowManager * windowManager) = 0;
	virtual void Close() = 0;
	virtual long GetWindowHandle() = 0;
	bool IsOpen() { return open; };
	void SetOpen(bool open) { this->open = open;  }
protected:
	int width;
	int height;
	std::string title;
	Monitor monitor;
	bool open;
	KeyState::State keyState[256];
private:
};

#endif