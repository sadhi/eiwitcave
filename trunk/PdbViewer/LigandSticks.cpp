#include "LigandSticks.h"
#include <Windows.h>
#include <gl\GLU.h>
#include "ObjModel.h"
#include <glm/glm.hpp>

ObjModel* ligandStickModel;

cLigandSticks::cLigandSticks(void)
{
	ligandStickModel = new ObjModel("data/pdbviewer/Models/stickModel.obj");
}

cLigandSticks::~cLigandSticks(void)
{
}

void cLigandSticks::addLigandStick(string line)
{
	ligandSticks.push_back(new cLigandStick(&line));
}
vector<cLigandStick*> cLigandSticks::getLigandSticks(void)
{
	return ligandSticks;
}

void cLigandSticks::addLocations(vector<cAtom*> HETAtoms, vector<cAtom*> Atoms)
{
	vector<cAtom*> AllAtoms = Atoms;
	for(int i = 0; i < (int)HETAtoms.size(); i++)
	{
		AllAtoms.push_back(HETAtoms.at(i));
	}
	for(int i = 0; i < (int)ligandSticks.size(); i++)
	{
		int serialFrom = ligandSticks.at(i)->serialNumber;		
		for(int j = 0; j < (int)AllAtoms.size(); j++)
		{
			if(serialFrom == AllAtoms.at(j)->serialNumber)
			{
				ligandSticks.at(i)->from = AllAtoms.at(j)->location;
				for(int k = 0; k < 4; k++)
				{					
					int serialTo = ligandSticks.at(i)->bondedSerialNumbers[k];
					for(int l = 0; l < (int)AllAtoms.size(); l++)
					{
						if(serialTo == AllAtoms.at(l)->serialNumber)
						{
							ligandSticks.at(i)->to[k] = AllAtoms.at(l)->location;
						}
					}
				}
			}
		}
	}
}

void cLigandSticks::draw()
{
	for(int i = 0; i < (int)ligandSticks.size(); i++)
	{
		Vec3* from = ligandSticks.at(i)->from;
		for(int k = 0; k < 4; k++)
		{
			Vec3* to = ligandSticks.at(i)->to[k];
			if(ligandSticks.at(i)->bondedSerialNumbers[k] != 0)
			{	
				Vec3 subVec;
				subVec = from->Substract(to);
				if(subVec.GetNormalLength() < 3.0)
				{
					/*glLineWidth(1);
					glBegin(GL_LINES);
						glColor3f(1.0f,1.0f,1.0f);
						glVertex3f(from->X/10.0, from->Y/10.0, from->Z/10.0);
						glVertex3f(to->X/10.0, to->Y/10.0, to->Z/10.0);
					glEnd();*/
					glPushMatrix();
					glm::vec3 gmtlVecA = glm::vec3(from->X, from->Y, from->Z);
					glm::vec3 gmtlVecB = glm::vec3(to->X, to->Y, to->Z);
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
		
					glTranslatef(from->X/10.0f, 
						from->Y/10.0f, 
						from->Z/10.0f);

					glRotatef(gmtlAngle*180.0f/(float)M_PI, cross[0], cross[1], cross[2]);
					glScalef(0.1f, (distance/1.5f), 0.1f);
					ligandStickModel->draw();
					glPopMatrix();
				}
			}
		}
	}
}
