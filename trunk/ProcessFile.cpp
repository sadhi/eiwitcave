#include <string>
#include <stdio.h>
#include <algorithm>
#include "ProcessFile.h"


bool firstModel = true;

cProcessFile::cProcessFile(void)
{
}

cProcessFile::cProcessFile(string filePath)
{
	init(&filePath);
}

cProcessFile::~cProcessFile(void)
{
}

void cProcessFile::init(string* filePath)
{
	std::cout<<"Parsing .PDB..."<<std::endl;
	objFile.open(filePath->c_str());

	int chainNumber = 0;

	while( objFile.good() ) 
    {	
		string line = "";
		getline( objFile, line );

		string indentifier = line.substr(0,6);
		//remove(indentifier.begin(),indentifier.end(),' ');
		if(!indentifier.compare("ATOM  ") && firstModel)
		{
			Atoms.push_back(new cAtom(&line, chainNumber));
		}
		else if(!indentifier.compare("TER   ") && firstModel)
		{
			chainNumber++;
		}
		else if(!indentifier.compare("HETATM") && firstModel)
		{
			HETAtoms.push_back(new cAtom(&line, chainNumber));
		}
		else if(!indentifier.compare("CONECT")) //Ligandbinding, maar ook ev.t waterstofbruggen?
		{
			ligandSticks.addLigandStick(line);
		}
		else if(!indentifier.compare("SSBOND")) //Zwavelbruggen
		{
			SSBonds.push_back(new cSSBond(&line));
		}
		else if(!indentifier.compare("LINK  "))
		{

		}
		else if(!indentifier.compare("SITE  "))
		{

		}
		else if(!indentifier.compare("ENDMDL"))
		{
			firstModel = false;
		}
	}

	objFile.close();

	Menu = new cMenu();
	Sticks = new cStick(Atoms);
	HSticks = new cStick(Atoms, HETAtoms);
	
	//MenuItem = new cMenuItem("Style");

	//SSSticks
	std::cout<<"Calculating disulfide bonds..."<<std::endl;
	SSSticks = new cSSBondStick(SSBonds, Atoms);
	
	std::cout<<"Calculating ligand..."<<std::endl;
	ligandSticks.addLocations(HETAtoms, Atoms);
	
	//Determine if atoms are part of ligand
	vector<cLigandStick*> ligands = ligandSticks.getLigandSticks();

	for(int i = 0; i < (int)ligands.size(); i++)
	{
		int serialFrom = ligands.at(i)->serialNumber;		
		for(int j = 0; j < (int)HETAtoms.size(); j++)
		{
			if(serialFrom == HETAtoms.at(j)->serialNumber)
			{
				HETAtoms.at(j)->isPartOfLigand = true;
				for(int k = 0; k < 4; k++)
				{					
					int serialTo = ligands.at(i)->bondedSerialNumbers[k];
					for(size_t l = 0; l < HETAtoms.size(); l++)
					{
						if(serialTo == HETAtoms.at(l)->serialNumber)
						{
							HETAtoms.at(l)->isPartOfLigand = true;
						}
					}
				}
			}
		}
	}
	//Calculate size
	calculateSize();
}

void cProcessFile::draw()
{
	drawLigands();
}

void cProcessFile::drawLigands()
{
	ligandSticks.draw();
}

void cProcessFile::calculateSize()
{
	std::cout<<"Calculating size and position of protein..."<<std::endl;
	float left		= 0.0f; 
	float right		= 0.0f; 
	float bottom	= 0.0f;
	float top		= 0.0f;
	float front		= 0.0f; 
	float back		= 0.0f;
	
	for(int i = 0; i < (int)Atoms.size(); i++)
	{
		float x = Atoms.at(i)->location->X;
		float y = Atoms.at(i)->location->Y;
		float z = Atoms.at(i)->location->Z;

		if(left > x)
			left = x;
		else if(right < x)
			right = x;

		if(bottom > y)
			bottom = y;
		else if(top < y)
			top = y;

		if(front > z)
			front = z;
		else if(back < z)
			back = z;		
	}
	float width = right - left;
	float heighth = top - bottom;
	float depth = back - front;

	if(width > heighth && width > depth)
		size = width;
	else if(heighth > width && heighth > depth)
		size = heighth;
	else if(depth > heighth && depth > width)
		size = depth;

	Vec3 midPoint = Vec3((right - (width/2)), (top - (heighth/2)), (back - (depth/2)));
	mid = midPoint;

	return;
}
