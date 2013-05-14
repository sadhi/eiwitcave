#include "Stick.h"
#include <Windows.h>
#include <gl\GLU.h>
#include "ObjModel.h"

#include <glm/glm.hpp>

ObjModel* stickModel;
ObjModel* stickModelLow;

cStick::cStick(void)
{
}

cStick::cStick(vector<cAtom*> atomList)
{
		std::cout<<"Calculating sticks..."<<std::endl;
	init(atomList);
}
cStick::cStick(vector<cAtom*> atomList, vector<cAtom*> hetList)
{
		std::cout<<"Calculating sticks (connected with water Atoms)..."<<std::endl;
	initH(atomList, hetList);
}

cStick::~cStick(void)
{
}

void cStick::init(vector<cAtom*> atomList)
{
	stickModel = new ObjModel("data/pdbviewer/Models/stickModel.obj");
	stickModelLow = new ObjModel("data/pdbviewer/Models/StickBox.obj");
	int decimalOfAtoms = atomList.size()/10;
	const int tenPer = decimalOfAtoms;
	int twentyPer = decimalOfAtoms * 2;
	int thirtyPer = decimalOfAtoms * 3;
	int fortyPer = decimalOfAtoms * 4;
	int fiftyPer = decimalOfAtoms * 5;
	int sixtyPer = decimalOfAtoms * 6;
	int seventyPer = decimalOfAtoms * 7;
	int eightyPer = decimalOfAtoms * 8;
	int ninetyPer = decimalOfAtoms * 9;
	for(int i = 0; i < (int)atomList.size(); i++)
	{
			
		for(int j = i+1; j < (int)atomList.size(); j++)
		{
			if(!(atomList[i]->element.compare(" H")) || !(atomList[j]->element.compare(" H")))
				continue;
			Vec3 subVec;
			subVec = atomList[i]->location->Substract(atomList[j]->location);
			if(subVec.GetLength() < 3.4225)
			{
				vector<Vec3*> list;
				list.push_back(atomList[i]->location);
				list.push_back(atomList[j]->location);
				sticks.push_back(list);
			}
		}
/*		if(i % decimalOfAtoms == 0)
		{
			std::cout<< i/decimalOfAtoms <<"0%"<<std::endl;
		}*/	
		if(tenPer == i)
			std::cout<<"10%"<<std::endl;
		else if(twentyPer == i)
			std::cout<<"20%"<<std::endl;
		else if(thirtyPer == i)
			std::cout<<"30%"<<std::endl;
		else if(fortyPer == i)
			std::cout<<"40%"<<std::endl;
		else if(fiftyPer == i)
			std::cout<<"50%"<<std::endl;
		else if(sixtyPer == i)
			std::cout<<"60%"<<std::endl;
		else if(seventyPer == i)
			std::cout<<"70%"<<std::endl;
		else if(eightyPer == i)
			std::cout<<"80%"<<std::endl;
		else if(ninetyPer == i)
			std::cout<<"90%"<<std::endl;
	}
	std::cout<<"100%"<<std::endl;
}
void cStick::initH(vector<cAtom*> atomList, vector<cAtom*> hetList)
{
	stickModel = new ObjModel("data/pdbviewer/Models/stickModel.obj");

	for(int i = 0; i < (int)atomList.size(); i++)
	{
		for(int j = i+1; j < (int)atomList.size(); j++)
		{
			if(!(atomList[i]->element.compare(" H")) ^ !(atomList[j]->element.compare(" H")))
			{
				Vec3 subVec;
				subVec = atomList[i]->location->Substract(atomList[j]->location);
				if(subVec.GetNormalLength() < 1.85)
				{
					vector<Vec3*> list;
					list.push_back(atomList[i]->location);
					list.push_back(atomList[j]->location);
					sticks.push_back(list);
				}
			}
		}
	}
}
void cStick::draw(bool high)
{	
	glColor3f(1.0f, 1.0f, 1.0f);
	int i = 0;
	do
	{	
		if(sticks.empty())
			return;
		glPushMatrix();

		glm::vec3 gmtlVecA = glm::vec3(sticks[i][0]->X, sticks[i][0]->Y, sticks[i][0]->Z);
		glm::vec3 gmtlVecB = glm::vec3(sticks[i][1]->X, sticks[i][1]->Y, sticks[i][1]->Z);

		/*glm::vec3 gmtlVecANorm = gmtl::makeNormal(gmtlVecA);
		glm::vec3 gmtlVecBNorm = gmtl::makeNormal(gmtlVecB);*/
		glm::vec3 vec = glm::vec3(0.0,1.0,0.0);
		glm::vec3 diff = gmtlVecB - gmtlVecA;
		diff[0] = -diff[0];
		diff[2] = -diff[2];

		glm::vec3 vecNorm = glm::normalize(vec);
		glm::vec3 vecDiffNorm = glm::normalize(diff);

		
		float gmtlAngle = glm::dot( vecDiffNorm, vecNorm );
		gmtlAngle = acos(gmtlAngle);
		//glm::vec3 cross = gmtl::makeCross(glm::vec3(sticks[i][0]->X, sticks[i][0]->Y, sticks[i][0]->Z),glm::vec3(sticks[i][1]->X, sticks[i][1]->Y, sticks[i][1]->Z));
		glm::vec3 cross = glm::cross(vecDiffNorm,  vecNorm);
		cross = glm::normalize(cross);
		//gmtl::cross(cross,gmtlVecA,gmtlVecB);

		//Vec3 cross = sticks[i][0]->GetCross(sticks[i][1]);

		////float angle = sticks[i][0]->Angle(sticks[i][1]);
		////float angle = sticks[i][0]->GetNormalize().Dot(&sticks[i][1]->GetNormalize());
		//float angle = atan2f(cross.GetLength(),sticks[i][0]->GetNormalize().Dot(&sticks[i][1]->GetNormalize()));
		//float angle = atan2f(gmtl::length(cross),gmtlAngle);
		float distance = glm::length(diff)/10.0f;
		
		glTranslatef(sticks[i][0]->X/10.0f, 
			sticks[i][0]->Y/10.0f, 
			sticks[i][0]->Z/10.0f);

		/*glm::vec3 diff = gmtlVecB - gmtlVecA;

		float angleX = atan2(diff[1], diff[2]);
		float angleY = atan2(diff[2], diff[0]);
		float angleZ = atan2(diff[1], diff[0]);
*/

		glRotatef(glm::degrees(gmtlAngle), cross[0], cross[1], cross[2]);

		/*
		glRotatef(angleX*180.0/M_PI, 1,0,0);
		glRotatef(angleY*180.0/M_PI, 0,1,0);
		glRotatef(angleZ*180.0/M_PI, 0,0,1);*/

		//glRotatef(atan2(gmtl::length(cross),gmtlAngle)*180.0/M_PI, cross[0], cross[1], cross[2]);
		//glRotatef(gmtlAngle*180.0/M_PI, cross[0], 0.0f, 0.0f);
		//glRotatef(gmtlAngle*180.0/M_PI, 0.0f, cross[1], 0.0f);
		//glRotatef(gmtlAngle*180.0/M_PI, 0.0f, 0.0f, cross[2]);
		glScalef(0.1f, (distance/1.5f), 0.1f);

		if(high)
			stickModel->draw();
		else
			stickModelLow->draw();

		glPopMatrix();

		/*glRotatef(-angle, -cross.X, -cross.Y, -cross.Z);

		glTranslatef(-sticks[i][0]->X, 
			-sticks[i][0]->Y, 
			-sticks[i][0]->Z);
		*/
		i++;
	}
	while( i < (int)sticks.size());
}
