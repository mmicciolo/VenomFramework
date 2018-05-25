#ifndef __ITEST_
#define __ITEST_

class ITest {
public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Shutdown() = 0;
	bool Running() { return running; }
protected:
	bool running = true;
private:
};

#endif