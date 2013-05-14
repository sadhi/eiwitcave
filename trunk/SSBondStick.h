#pragma once

#include <iostream>
#include <string.h>
#include "Vec3.h"
#include <vector>
#include "Atom.h"
#include "SSBond.h"

using namespace std;

class cSSBondStick
{
public:
	cSSBondStick(void);
	cSSBondStick(vector<cSSBond*> ssBondList, vector<cAtom*> atomList);
	~cSSBondStick(void);

	vector<vector<Vec3*>> sticks;

	void draw();

private:
	//functions
	void init(vector<cSSBond*>, vector<cAtom*> atomList);
};

