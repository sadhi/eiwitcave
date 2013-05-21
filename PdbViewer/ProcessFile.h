#pragma once

#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include "Atom.h"
#include "Stick.h"
#include "LigandSticks.h"
#include "SSBond.h"
#include "SSBondStick.h"
#include "Vec3.h"
#include "Menu.h"

using namespace std;

class cProcessFile
{
public:
	//constructors/destructors
	cProcessFile(void);
	cProcessFile(string filePath);
	~cProcessFile(void);

	//variables
	vector<cAtom*> Atoms;
	vector<cAtom*> HETAtoms;
	vector<cSSBond*> SSBonds;
	cSSBondStick* SSSticks;
	cStick* Sticks;
	cStick* HSticks;
	cLigandSticks ligandSticks;
	cMenu* Menu;

	void draw(void);

	void calculateSize(void);

	Vec3 mid;
	float size;
private:
	//functions
	void init(string* filePath);
	//drawFuntions
	void drawLigands(void);

	//variables
	ifstream objFile;
};