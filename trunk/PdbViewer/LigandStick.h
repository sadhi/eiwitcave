#pragma once

#include <iostream>
#include <string.h>
#include "Vec3.h"

using namespace std;

class cLigandStick
{
public:
	cLigandStick(void);
	cLigandStick(string* line);
	~cLigandStick(void);

	int serialNumber;
	int bondedSerialNumbers[4];

	Vec3* from;
	Vec3* to[4];

	void draw();
	void getLocation();
private:
	//functions
	void init(string* line);
};

