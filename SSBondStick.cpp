#include "SSBondStick.h"
#include <windows.h>
#include <gl\GLU.h>
#include "ObjModel.h"

#include <glm/glm.hpp>

ObjModel* ssBondModel;

cSSBondStick::cSSBondStick(void)
{
}

cSSBondStick::cSSBondStick(vector<cSSBond*> SSBondList, vector<cAtom*> atomList)
{
	init(SSBondList, atomList);
}

cSSBondStick::~cSSBondStick(void)
{
}

void cSSBondStick::init(vector<cSSBond*> SSBondList, vector<cAtom*> atomList)
{
	ssBondModel = new ObjModel("data/pdbviewer/Models/stickModel.obj");

	for(int i = 0; i < (int)SSBondList.size(); i++)
	{
		vector<Vec3*> list;
		for(int j = 0; j < (int)atomList.size(); j++)
		{
			if(atomList[j]->element != " S")
				continue;
			if(SSBondList[i]->residueName1 == atomList[j]->residueName && SSBondList[i]->residueSeqNumber1 == atomList[j]->residueSeqNumber)
			{				
				list.push_back(atomList[j]->location);
			}
			else if(SSBondList[i]->residueName2 == atomList[j]->residueName && SSBondList[i]->residueSeqNumber2 == atomList[j]->residueSeqNumber)
			{				
				list.push_back(atomList[j]->location);
				break;
			}
		}
		sticks.push_back(list);
	}
}
void cSSBondStick::draw(void)
{	
	glColor3f(1.0f, 1.0f, 0.0f);
	for(int i = 0; i < (int)sticks.size(); i++)
	{	
		glPushMatrix();

		glm::vec3 gmtlVecA = glm::vec3(sticks[i][0]->X, sticks[i][0]->Y, sticks[i][0]->Z);
		glm::vec3 gmtlVecB = glm::vec3(sticks[i][1]->X, sticks[i][1]->Y, sticks[i][1]->Z);

		glm::vec3 vec = glm::vec3(0.0,1.0,0.0);
		glm::vec3 diff = gmtlVecB - gmtlVecA;
		diff[0] = -diff[0];
		diff[2] = -diff[2];

		
		

		glm::vec3 vecNorm = glm::normalize(vec);
		glm::vec3 vecDiffNorm = glm::normalize(diff);
	
		float gmtlAngle = glm::dot( vecDiffNorm, vecNorm );
		gmtlAngle = acos(gmtlAngle);
		glm::vec3 cross = glm::cross(vecDiffNorm,  vecNorm);
		cross = glm::normalize(cross);

		float distance = glm::length(diff)/10.0f;

		glTranslatef(sticks[i][0]->X/10.0f,
			sticks[i][0]->Y/10.0f,
			sticks[i][0]->Z/10.0f);

		glRotatef(gmtlAngle*180.0f/(float)M_PI, cross[0], cross[1], cross[2]);

		glScalef(0.25f, distance/1.5f, 0.25f);

		ssBondModel->draw();

		glPopMatrix();
	}
	glColor3f(1.0,1.0,1.0);
}
