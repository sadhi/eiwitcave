#pragma once

#include <VrLib/Application.h>
#include <VrLib/Device.h>

#include <CaveLib/Plane.h>

class PDBFileDemo : public Application
{
public:
	PDBFileDemo(int argc, char* argv[]);
	~PDBFileDemo(void);

	void init();
	void initCubemap();
	void contextInit();

	void preFrame();
	void bufferPreDraw();
	void updateLightPosition(float x, float y, float z);
	void draw(glm::mat4 projectionMatrix);
	void LowDraw(void);
	void MediumDraw(void);
	void HighDraw(void);

	glm::vec4 collisionLinePlane(glm::vec3 A, glm::vec3 B, Plane plane);
	void drawPointer();
	void glDrawCube();
private:
	//int tickCount;
	PositionalDevice  mWand;
	PositionalDevice  mHead;
    DigitalDevice   mButton0;
	DigitalDevice   mButton1;

	float xSize;
	float ySize;
	float zSize;

};

