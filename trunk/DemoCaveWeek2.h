#pragma once

#include <VrLib/Application.h>
#include <VrLib/Device.h>
#include <CaveLib/Plane.h>

class DemoCaveWeek2 :public Application
{
public:
	DemoCaveWeek2(void);
	~DemoCaveWeek2(void);

	void init();
	void init(int argc, char* argv[]);
	void contextInit();

	void preFrame();
	void bufferPreDraw();
	void draw(glm::mat4 projectionMatrix);

	void enableLight();
	glm::vec4 collisionLinePlane(glm::vec3 A, glm::vec3 B, Plane plane);
	glm::vec3 closestPoint(glm::vec3 A, glm::vec3 B, glm::vec3 P);
	bool pointInSphere(glm::vec3 point, glm::vec3 sphereLocation, float radius);

private:
	PositionalDevice  mWand;
	PositionalDevice  mHead;
    DigitalDevice   mButton0;

	glm::vec4 targetObject;
};

