#pragma once

#include <VrLib/Application.h>
#include <VrLib/Device.h>

class DemoCaveApplication : public Application
{
public:
	DemoCaveApplication(void);
	~DemoCaveApplication(void);

	void init();
	void init(int argc, char* argv[]);
	void contextInit();

	void preFrame();
	void bufferPreDraw();
	void draw(glm::mat4 projectionMatrix);
private:
	PositionalDevice  mWand;
	PositionalDevice  mHead;
    DigitalDevice   mButton0;

};
