#pragma once

#include <iostream>
#include <string.h>
#include "Vec3.h"

using namespace std;

class cAtom
{
public:
	//constructors/destructors
	cAtom(void);
	cAtom(string* line, int _chainNumber);
	~cAtom(void);

	//variables
	int serialNumber;
	string atomName;
	string residueName;
	int residueSeqNumber;
	Vec3* location;
	string element;
	int chainNumber;
	float tempuratureFactor;
	int charge;

	bool isPartOfLigand;
	bool draw;

private:
	//functions
	void init(string* line);

};

