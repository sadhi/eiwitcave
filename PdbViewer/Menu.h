#pragma once
#include <windows.h>
#include <gl/glew.h>
#include <gl/GL.h>
#include "Texture.h"
#include <iostream>
#include <math.h>
#include "Defines.h"
//#include <fmod/fmod.hpp>
//#include <fmod/fmod_errors.h>

#include <glm/glm.hpp>

using namespace std;

class cMenu
{
	
public:
	//de/con-structors
	cMenu(void);
	~cMenu(void);

	//functions
	//void InitSound(void);
	void ButtonInit(void);
	void Draw(void);
	//void Key(char key);

	void AutoSetButtonGlow(glm::vec2 pos);
	void AutoSetMode(void);
	void SetButtonGlow(int button);
	int WhichButtonIsActive(void);

	//vars
	bool ModeRotation;
	bool ModeLigand;
	bool ModeSSBonds;
	bool ModeHAtoms;
	bool ModeTranslation;
	//bool ModeDomains;
	bool ModeProtein;
	bool ModeByElement;
	bool ModeByDomain;
	bool ModeHigh;
	bool ModeMedium;
	bool ModeLow;
	bool Mode3DSelectie;
	bool ModeSelectSingelAtom;

private:
	//init functions
	void resetButtons(void);
	void resetModes(void);
	//functions
	void menuDraw(float x, float y, float z, float width, float height);
	void filterDraw(float x, float y, float z, float width, float height);
	void zoomDraw(float x, float y, float z, float width, float height);
	void rotationDraw(float x, float y, float z, float width, float height);
	void ligandDraw(float x, float y, float z, float width, float height);
	void ssBondDraw(float x, float y, float z, float width, float height);
	void hAtomsDraw(float x, float y, float z, float width, float height);
	//void domainsDraw(float x, float y, float z, float width, float height);
	void backDraw(float x, float y, float z, float width, float height);
	void byElementDraw(float x, float y, float z, float width, float height);
	void byDomainDraw(float x, float y, float z, float width, float height);
	void proteinDraw(float x, float y, float z, float width, float height);
	void settingsDraw(float x, float y, float z, float width, float height);
	void highDraw(float x, float y, float z, float width, float height);
	void mediumDraw(float x, float y, float z, float width, float height);
	void lowDraw(float x, float y, float z, float width, float height);
	void translationDraw(float x, float y, float z, float width, float height);

	void playClickSound(void);

	//vars
	Texture *textures[NUMBER_OF_TEXTURES];

	//button states
	bool buttonFilterGlow;
	bool buttonColorGlow;
	bool buttonRotationGlow;
	bool buttonLigandGlow;
	bool buttonSSBondsGlow;
	bool buttonHATOMSGLow;
	//bool buttonDomainsGlow;
	bool buttonProteinGlow;
	bool buttonBackGlow;
	bool buttonByElementGlow;
	bool buttonByDomainGlow;
	bool buttonSettingsGlow;
	bool buttonHighGlow;
	bool buttonMediumGlow;
	bool buttonLowGlow;
	bool buttonTranslationGlow;

	//menu states
	int MenuState;

	////sound stuff
	//FMOD::System     *system;
 //   FMOD::Sound      *clickSound;
 //   FMOD::Channel    *channel;
};

