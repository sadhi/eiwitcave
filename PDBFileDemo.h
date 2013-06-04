#pragma once

#include <VrLib/Application.h>
#include <VrLib/Device.h>
#include <CaveLib/Plane.h>
#include "Atom.h"
#include <cavelib/Components/Panel.h>
#include <cavelib/Components/Label.h>
#include "MainMenu.h"
#include "AtomPanel.h"
#include "EnzymePanel.h"

class PDBFileDemo : public Application
{
	MainMenu *menuPanel;
	AtomPanel *atomPanel;
	EnzymePanel *enzymePanel;
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
	float GetDisctanceBetweenAtoms(int Atom1, int Atom2);
	void drawSphere(float size, float X, float Y, float Z);
	void drawBlinkSphere(float size, float X, float Y, float Z);
	float get3DDistance(float X1, float Y1, float Z1, float X2, float Y2, float Z2);
	float sphereSize3DSelect;
	bool selectSphereView;
	float selectedAtom;

private:
	//int tickCount;
	PositionalDevice  mWand;
	PositionalDevice  mHead;
    DigitalDevice   mButton0;
	DigitalDevice   mButton1;
 
	DigitalDevice   mKeyPageUp;
    DigitalDevice   mKeyPageDown;
    DigitalDevice   mKeyF5;

	float xSize;
	float ySize;
	float zSize;

	float DistanceAtom1, DistanceAtom2;
	float OrbSelect;
	float Xaddjust, Yaddjust;

	Panel* rootPanel;
	glm::mat4 renderMatrix;
	cAtom atom1, atom2;
	BOOL atom1selected;


};

