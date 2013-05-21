#include "PDBFileDemo.h"
#include <gl\glew.h>
#include <gl\GL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Vector3D.h"
#include "ProcessFile.h"
#include "ObjModel.h"
#include "Texture.h"
#include "cubemap.h"
#include "Defines.h"

int rotationX = 0;
int rotationY = 0;
int rotationZ = 0;

float translationX = 0.0;
float translationY = 0.0;
float translationZ = 0.0;

cProcessFile* processFile;

Cubemap* cubemap;

ObjModel* sphereModelLow;
ObjModel* sphereModelMedium;
ObjModel* sphereModelHigh;

int frameCount = 0;
unsigned long lastFrameRate;
unsigned long last_idle_time;

string fileToLoad = "";

float positioningX = 0.0f;
float positioningY = 0.0f;
float positioningZ = 0.0f;

glm::vec4 wandForw;
glm::vec4 wandPos;

PDBFileDemo::PDBFileDemo(int argc, char* argv[])
{
	for(int i = 1; i < argc; i++)
	{
		cout << i << argv[i] << endl;
		if(strcmp(argv[i], "--pdb") == 0)
		{
			i++;
			cout << i << argv[i] << endl;
			std::string filename_str = std::string(argv[i]);
			fileToLoad = filename_str;
		}
	}
}

PDBFileDemo::~PDBFileDemo(void)
{

}

void PDBFileDemo::init()
{
	

	// Initialize devices
	const std::string wand("WandPosition");
	const std::string vjhead("MainUserHead");
	const std::string but0("LeftButton");
	const std::string but1("RightButton");

	mWand.init(wand);
	mHead.init(vjhead);
	mButton0.init(but0);
	mButton1.init(but1);
	
	//tickCount = 0;

//	glutInit(&argc, argv);
	contextInit();

	last_idle_time = GetTickCount();
	lastFrameRate = last_idle_time;

}

void PDBFileDemo::initCubemap(void)
{
	float size = ((processFile->size));
	size = size/16.0f; //Cave 
	if(size < 1.5f)
		size = 1.5f;

	xSize = size + positioningX /2.0f;
	ySize = size + positioningY /2.0f;
	zSize = size + positioningZ /2.0f;
}
void PDBFileDemo::contextInit()
{
//	glewInit();
	cout << "File to load:" << fileToLoad << endl;
	//fileToLoad = fileToLoad.erase(0, 21);
	cout << "File to load2:" << fileToLoad << endl;

	if(fileToLoad.empty())
	{
		fileToLoad = "data/proteins/3PTA.pdb";
		cout << "Error loading file, loading 1DW5.pdb instead:" << fileToLoad << endl;
	}
	
	processFile = new cProcessFile(fileToLoad);

	//processFile = new cProcessFile("3FRH.pdb");
	//processFile = new cProcessFile("1DW5.pdb");
	//processFile = new cProcessFile("both2.pdb");
	//processFile = new cProcessFile("both2y.pdb");
//	sphereModelHigh = new ObjModel("data/PdbViewer/Models/detailSphere.obj");
	sphereModelMedium = new ObjModel("data/PdbViewer/Models/AtomModel.obj");
//	sphereModelLow = new ObjModel("data/PdbViewer/Models/square.obj");

	positioningX = (processFile->mid.X/10.0f);// + 2.0f);
	positioningY = (processFile->mid.Y/10.0f) + 0.8f;
	positioningZ = (processFile->mid.Z/10.0f) + ((processFile->size/10)/2.0f) + 2.0f;


	//cubetest
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	cubemap = new Cubemap("data/cubemaps/PdbViewer");
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap->textureId);
	glActiveTexture(GL_TEXTURE0);

	initCubemap();
	
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
}

glm::vec4 PDBFileDemo::collisionLinePlane(glm::vec3 A, glm::vec3 B, Plane plane)
{
    glm::vec3 AB = A - B;
    float denominator = glm::dot(AB, plane.getNormal());
    if(denominator == 0)
    	return glm::vec4(0,0,0, -1);
    float numerator = glm::dot(A, plane.getNormal()) + plane.getOffset();

    float t = - numerator / denominator;
    AB = glm::normalize(AB);
    glm::vec3 point = A + t*AB;
    return glm::vec4(point[0], point[1], point[2], t); 
}

void PDBFileDemo::drawPointer()
{
	Plane plane(glm::vec3(0,0,-1), 1.3f);
	glm::vec4 ret = collisionLinePlane(
		glm::vec3(wandPos[0], wandPos[1], wandPos[2]),
		glm::vec3(wandForw[0], wandForw[1], wandForw[2]),
		plane);
	processFile->Menu->AutoSetButtonGlow(glm::vec2(ret[0], ret[1]));
//	glColor4f(0,0,1,1);
	
//	glTranslatef(ret[0], ret[1], ret[2]);
//	glutSolidSphere(0.1f, 6, 6);
//	glTranslatef(-ret[0], -ret[1], -ret[2]);

	glColor4f(1,1,0,1);
	glBegin(GL_LINES);
		glVertex3f(wandPos[0], wandPos[1], wandPos[2]);
		glVertex3f(ret[0], ret[1], ret[2]);
	glEnd();
}

void PDBFileDemo::glDrawCube()
{
	glColor4f(0,0,0,1);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap->textureId);
	
	glBegin(GL_QUADS);  
		//back
	//	glTexCoord3f(1, -1, -1);	glVertex3f(-xSize,ySize, 100);//	size+z - 4.0);
	//	glTexCoord3f(1, 1, -1);		glVertex3f(-xSize,-ySize,100);//	size+z - 4.0);
	//	glTexCoord3f(-1, 1, -1);	glVertex3f(xSize,-ySize, 100);//	size+z - 4.0);
	//	glTexCoord3f(-1, -1, -1);	glVertex3f(xSize,ySize,  100);//	size+z - 4.0);
		//front
		if(zSize < 8)
		{
			glTexCoord3f(1, -1, 1);		glVertex3f(-xSize,ySize,	-8);
			glTexCoord3f(1, 1, 1);		glVertex3f(-xSize,-ySize,	-8);
			glTexCoord3f(-1, 1, 1);		glVertex3f(xSize,-ySize,	-8);
			glTexCoord3f(-1, -1, 1);	glVertex3f(xSize,ySize,		-8);

			glTexCoord3f(-1, 1, -1);	glVertex3f(xSize,-ySize,	zSize);
			glTexCoord3f(-1, -1, -1);	glVertex3f(xSize,ySize,		zSize);
			glTexCoord3f(-1, -1, 1);	glVertex3f(xSize,ySize,		-8);
			glTexCoord3f(-1, 1, 1);		glVertex3f(xSize,-ySize,	-8);

			glTexCoord3f(1, 1, -1);		glVertex3f(-xSize,-ySize,	zSize);
			glTexCoord3f(1, -1, -1);	glVertex3f(-xSize,ySize,	zSize);
			glTexCoord3f(1, -1, 1);		glVertex3f(-xSize,ySize,	-8);
			glTexCoord3f(1, 1, 1);		glVertex3f(-xSize,-ySize,	-8);

			glTexCoord3f(1, -1, -1);	glVertex3f(-xSize,ySize,	zSize);
			glTexCoord3f(-1, -1, -1);	glVertex3f(xSize,ySize,		zSize);
			glTexCoord3f(-1, -1, 1);	glVertex3f(xSize,ySize,		-8);
			glTexCoord3f(1, -1, 1);		glVertex3f(-xSize,ySize,	-8);
		
			glTexCoord3f(1, 1, -1);		glVertex3f(-xSize,-ySize,	zSize);
			glTexCoord3f(-1, 1, -1);	glVertex3f(xSize,-ySize,	zSize);
			glTexCoord3f(-1, 1, 1);		glVertex3f(xSize,-ySize,	-8);
			glTexCoord3f(1, 1, 1);		glVertex3f(-xSize,-ySize,	-8);
		}
		else
		{
			glTexCoord3f(1, -1, 1);		glVertex3f(-xSize,ySize,	-zSize);
			glTexCoord3f(1, 1, 1);		glVertex3f(-xSize,-ySize,	-zSize);
			glTexCoord3f(-1, 1, 1);		glVertex3f(xSize,-ySize,	-zSize);
			glTexCoord3f(-1, -1, 1);	glVertex3f(xSize,ySize,		-zSize);

			glTexCoord3f(-1, 1, -1);	glVertex3f(xSize,-ySize,	zSize);
			glTexCoord3f(-1, -1, -1);	glVertex3f(xSize,ySize,		zSize);
			glTexCoord3f(-1, -1, 1);	glVertex3f(xSize,ySize,		-zSize);
			glTexCoord3f(-1, 1, 1);		glVertex3f(xSize,-ySize,	-zSize);

			glTexCoord3f(1, 1, -1);		glVertex3f(-xSize,-ySize,	zSize);
			glTexCoord3f(1, -1, -1);	glVertex3f(-xSize,ySize,	zSize);
			glTexCoord3f(1, -1, 1);		glVertex3f(-xSize,ySize,	-zSize);
			glTexCoord3f(1, 1, 1);		glVertex3f(-xSize,-ySize,	-zSize);

			glTexCoord3f(1, -1, -1);	glVertex3f(-xSize,ySize,	zSize);
			glTexCoord3f(-1, -1, -1);	glVertex3f(xSize,ySize,		zSize);
			glTexCoord3f(-1, -1, 1);	glVertex3f(xSize,ySize,		-zSize);
			glTexCoord3f(1, -1, 1);		glVertex3f(-xSize,ySize,	-zSize);
		
			glTexCoord3f(1, 1, -1);		glVertex3f(-xSize,-ySize,	zSize);
			glTexCoord3f(-1, 1, -1);	glVertex3f(xSize,-ySize,	zSize);
			glTexCoord3f(-1, 1, 1);		glVertex3f(xSize,-ySize,	-zSize);
			glTexCoord3f(1, 1, 1);		glVertex3f(-xSize,-ySize,	-zSize);
		}

	glEnd();

	glDisable(GL_TEXTURE_CUBE_MAP);
}

void PDBFileDemo::preFrame()
{	
	//FPS
	int diff = GetTickCount() - last_idle_time;

	last_idle_time = GetTickCount();

	if(last_idle_time - lastFrameRate > 5000)
	{
		std::cout << "FPS: " << frameCount / 5 << std::endl;
		frameCount = 0;
		lastFrameRate = last_idle_time;
	}

	
	glm::mat4 wandMatrix = mWand.getData();
	wandPos = wandMatrix * glm::vec4(0,0,0,1);
	wandForw = wandMatrix * glm::vec4(0,0,1,1);

	glm::mat4 headMat = mHead.getData();
	glm::vec4 headPos = headMat * glm::vec4(0,0,0,1);

	if(mButton0.getData() == TOGGLE_ON && headPos[2] > 1.3)// && tickCount == 0)
	{
		processFile->Menu->AutoSetMode();
	}
	else if(processFile != NULL && processFile->Menu->ModeRotation && mButton0.getData() == ON)
	{
		glm::vec3 gmtlVecA = glm::vec3(wandPos[0], wandPos[1], wandPos[2]);
		glm::vec3 gmtlVecB = glm::vec3(wandForw[0], wandForw[1], wandForw[2]);
		glm::vec3 vec = glm::vec3(0.0,1.0,0.0);
		glm::vec3 diff = gmtlVecB - gmtlVecA;
		diff[0] = -diff[0];
		diff[2] = -diff[2];

		float xAbs = glm::abs(diff[1]);
		float yAbs = glm::abs(diff[0]);
		float zAbs = glm::abs(diff[2]);

		if(xAbs > yAbs && xAbs > zAbs)
		{//X
			if(diff[1] > 0)
				rotationX = (rotationX + 3)%360;
			else if(diff[1] < 0)
				rotationX = (rotationX - 3)%360;
		}
		else if(yAbs > xAbs && yAbs > zAbs)
		{//Y
			if(diff[0] > 0)
				rotationY = (rotationY + 3)%360;
			else if(diff[0] < 0)
				rotationY = (rotationY - 3)%360;
		}
		else if(zAbs > yAbs && zAbs > xAbs)
		{//Z
			if(diff[2] > 0)
				rotationZ = (rotationZ + 3)%360;
			else if(diff[2] < 0)
				rotationZ = (rotationZ - 3)%360;
		}
	}
	else if(processFile != NULL && processFile->Menu->ModeTranslation && mButton0.getData() == ON)
	{
		glm::vec3 gmtlVecA = glm::vec3(wandPos[0], wandPos[1], wandPos[2]);
		glm::vec3 gmtlVecB = glm::vec3(wandForw[0], wandForw[1], wandForw[2]);
		glm::vec3 vec = glm::vec3(0.0,1.0,0.0);
		glm::vec3 diff = gmtlVecB - gmtlVecA;
		diff[0] = -diff[0];
		diff[2] = -diff[2];

		//float xAbs = gmtl::Math::abs(diff[1]);
		//float yAbs = gmtl::Math::abs(diff[0]);
		//float zAbs = gmtl::Math::abs(diff[2]);

		

		if(diff[0] > 0)
			positioningX -= glm::abs(diff[0])/50;
		else
			positioningX += glm::abs(diff[0])/50;

		if(diff[1] > 0)
			positioningY += glm::abs(diff[1])/50;
		else
			positioningY -= glm::abs(diff[1])/50;

		if(diff[2] > 0)
			positioningZ -= glm::abs(diff[2])/50;
		else
			positioningZ += glm::abs(diff[2])/50;

	}
}

void PDBFileDemo::bufferPreDraw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

}

void PDBFileDemo::updateLightPosition(float x, float y, float z)
{
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { x, y, z, 1.0};

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
}

void PDBFileDemo::MediumDraw(void)
{
	if(processFile->Menu->ModeProtein)
	{
		size_t i = 0;
		do
		{
			if(processFile->Atoms.empty())
			{
				break;
			}

			if(processFile->Menu->ModeByElement)
			{
				//Color by element
				if(!processFile->Atoms.at(i)->element.compare(" C"))
				{
					glColor3f(0.5f, 0.5f, 0.5f); //Grijs
				}
				else if(!processFile->Atoms.at(i)->element.compare(" O"))
				{
					glColor3f(1.0f, 0.0f, 0.0f); //Rood
				}
				else if(!processFile->Atoms.at(i)->element.compare(" N"))
				{
					glColor3f(0.0f, 0.0f, 1.0f); //Blauw
				}
				else if(!processFile->Atoms.at(i)->element.compare(" P"))
				{
					glColor3f(1.0f, 0.5f, 0.0f); //Oranje
				}
				else if(!processFile->Atoms.at(i)->element.compare(" S"))
				{
					glColor3f(1.0f, 1.0f, 0.0f); //Geel
				}
				else if(!processFile->Atoms.at(i)->element.compare("ZN"))
				{
					glColor3f(0.5f, 1.0f, 0.0f); //Lila
				}
				else if(!processFile->Atoms.at(i)->element.compare(" H"))
				{
					if(!processFile->Menu->ModeHAtoms)
					{
					i++;
					continue;
					}
					glColor3f(1.0f, 1.0f, 1.0f); //Wit

				}
				else
				{
					glColor3f(0.0f, 0.0f, 0.0f);
				}
			}
			else
			{
				int colorNumber = processFile->Atoms.at(i)->chainNumber % 5;
				switch (colorNumber)
				{
				case 0:
					glColor3f(1.0f, 0.0f, 0.0f); //rood
					break;
				case 1:
					glColor3f(0.0f, 1.0f, 0.0f); //groen
					break;
				case 2:
					glColor3f(0.0f, 0.0f, 1.0f); //blauw
					break;
				case 3:
					glColor3f(1.0f, 1.0f, 0.0f); //geel
					break;
				case 4:
					glColor3f(1.0f, 0.0f, 1.0f); //roze
					break;
				case 5:
					glColor3f(0.0f, 1.0f, 1.0f); //cyaan
					break;
				default:
					glColor3f(1.0f, 1.0f, 1.0f); //wit
					break;
				}
			}

			//TODO Trimming spaces

			glTranslatef(processFile->Atoms.at(i)->location->X/10.0f - positioningX, 
				(processFile->Atoms.at(i)->location->Y/10.0f) - positioningY, 
				(processFile->Atoms.at(i)->location->Z/10.0f) - positioningZ);

			sphereModelMedium->draw();

			glTranslatef(-1.0f * (processFile->Atoms.at(i)->location->X/10.0f - positioningX), 
				-1.0f * ((processFile->Atoms.at(i)->location->Y/10.0f) - positioningY), 
				-1.0f * ((processFile->Atoms.at(i)->location->Z/10.0f) - positioningZ));	
			i++;
		}
		while(i < processFile->Atoms.size() );

		glTranslatef(-positioningX, -positioningY, -positioningZ);
		processFile->Sticks->draw(true);
		if(processFile->Menu->ModeSSBonds)
		{
			processFile->SSSticks->draw();
		}
		if(processFile->Menu->ModeHAtoms)
		{
			processFile->HSticks->draw(true);
		}

		glTranslatef(positioningX, positioningY, positioningZ);


	}
	if(processFile->Menu->ModeLigand)
	{
		glTranslatef(-positioningX, -positioningY, -positioningZ);
		processFile->draw();
		glTranslatef(positioningX, positioningY, positioningZ);
		size_t i = 0;
		do
		{
			if(processFile->HETAtoms.empty())
			{
				break;
			}
			if(!processFile->HETAtoms.at(i)->isPartOfLigand)
			{
				i++;
				continue;
			}
			if(processFile->Menu->ModeByElement)
			{
				//Color by element
				if(!processFile->HETAtoms.at(i)->element.compare(" C"))
				{
					glColor3f(0.5f, 0.5f, 0.5f); //Grijs
				}
				else if(!processFile->HETAtoms.at(i)->element.compare(" O"))
				{
					glColor3f(1.0f, 0.0f, 0.0f); //Rood
				}
				else if(!processFile->HETAtoms.at(i)->element.compare(" N"))
				{
					glColor3f(0.0f, 0.0f, 1.0f); //Blauw
				}
				else if(!processFile->HETAtoms.at(i)->element.compare(" P"))
				{
					glColor3f(1.0f, 0.5f, 0.0f); //Oranje
				}
				else if(!processFile->HETAtoms.at(i)->element.compare(" S"))
				{
					glColor3f(1.0f, 1.0f, 0.0f); //Geel
				}
				else if(!processFile->HETAtoms.at(i)->element.compare("ZN"))
				{
					glColor3f(0.5f, 1.0f, 0.0f); //Lila
				}
				else if(!processFile->HETAtoms.at(i)->element.compare(" H"))
				{
					glColor3f(1.0f, 1.0f, 1.0f); //Wit

				}
				else
				{
					glColor3f(0.0f, 0.0f, 0.0f);
				}
			}
			else
			{
				int colorNumber = processFile->Atoms.at(i)->chainNumber % 5;
				switch (colorNumber)
				{
				case 0:
					glColor3f(1.0f, 0.0f, 0.0f); //rood
					break;
				case 1:
					glColor3f(0.0f, 1.0f, 0.0f); //groen
					break;
				case 2:
					glColor3f(0.0f, 0.0f, 1.0f); //blauw
					break;
				case 3:
					glColor3f(1.0f, 1.0f, 0.0f); //geel
					break;
				case 4:
					glColor3f(1.0f, 0.0f, 1.0f); //roze
					break;
				case 5:
					glColor3f(0.0f, 1.0f, 1.0f); //cyaan
					break;
				default:
					glColor3f(1.0f, 1.0f, 1.0f); //wit
					break;
				}
			}

			//TODO Trimming spaces
			glTranslatef(processFile->HETAtoms.at(i)->location->X/10.0f - positioningX, 
				(processFile->HETAtoms.at(i)->location->Y/10.0f) - positioningY, 
				(processFile->HETAtoms.at(i)->location->Z/10.0f) - positioningZ);

			sphereModelMedium->draw();

			glTranslatef(-1.0f * (processFile->HETAtoms.at(i)->location->X/10.0f - positioningX), 
				-1.0f * ((processFile->HETAtoms.at(i)->location->Y/10.0f) - positioningY), 
				-1.0f * ((processFile->HETAtoms.at(i)->location->Z/10.0f) - positioningZ));	
			i++;
		}
		while(i < processFile->HETAtoms.size());
	}
}

void PDBFileDemo::LowDraw(void)
{
	if(processFile->Menu->ModeProtein)
	{
		size_t i = 0;
		do
		{
			if(processFile->Atoms.empty())
				break;
			if(processFile->Menu->ModeByElement)
			{
				//Color by element
				if(!processFile->Atoms.at(i)->element.compare(" C"))
				{
					glColor3f(0.5f, 0.5f, 0.5f); //Grijs
				}
				else if(!processFile->Atoms.at(i)->element.compare(" O"))
				{
					glColor3f(1.0f, 0.0f, 0.0f); //Rood
				}
				else if(!processFile->Atoms.at(i)->element.compare(" N"))
				{
					glColor3f(0.0f, 0.0f, 1.0f); //Blauw
				}
				else if(!processFile->Atoms.at(i)->element.compare(" P"))
				{
					glColor3f(1.0f, 0.5f, 0.0f); //Oranje
				}
				else if(!processFile->Atoms.at(i)->element.compare(" S"))
				{
					glColor3f(1.0f, 1.0f, 0.0f); //Geel
				}
				else if(!processFile->Atoms.at(i)->element.compare("ZN"))
				{
					glColor3f(0.5f, 1.0f, 0.0f); //Lila
				}
				else if(!processFile->Atoms.at(i)->element.compare(" H"))
				{
					if(!processFile->Menu->ModeHAtoms)
					{
						i++;
						continue;
					}
					glColor3f(1.0f, 1.0f, 1.0f); //Wit

				}
				else
				{
					glColor3f(0.0f, 0.0f, 0.0f);
				}
			}
			else
			{
				int colorNumber = processFile->Atoms.at(i)->chainNumber % 5;
				switch (colorNumber)
				{
				case 0:
					glColor3f(1.0f, 0.0f, 0.0f); //rood
					break;
				case 1:
					glColor3f(0.0f, 1.0f, 0.0f); //groen
					break;
				case 2:
					glColor3f(0.0f, 0.0f, 1.0f); //blauw
					break;
				case 3:
					glColor3f(1.0f, 1.0f, 0.0f); //geel
					break;
				case 4:
					glColor3f(1.0f, 0.0f, 1.0f); //roze
					break;
				case 5:
					glColor3f(0.0f, 1.0f, 1.0f); //cyaan
					break;
				default:
					glColor3f(1.0f, 1.0f, 1.0f); //wit
					break;
				}
			}

			//TODO Trimming spaces

			glTranslatef(processFile->Atoms.at(i)->location->X/10.0f - positioningX, 
				(processFile->Atoms.at(i)->location->Y/10.0f) - positioningY, 
				(processFile->Atoms.at(i)->location->Z/10.0f) - positioningZ);

			sphereModelLow->draw();

			glTranslatef(-1.0f * (processFile->Atoms.at(i)->location->X/10.0f - positioningX), 
				-1.0f * ((processFile->Atoms.at(i)->location->Y/10.0f) - positioningY), 
				-1.0f * ((processFile->Atoms.at(i)->location->Z/10.0f) - positioningZ));	
			i++;
		}
		while (i < processFile->Atoms.size());
		

		glTranslatef(-positioningX, -positioningY, -positioningZ);
		processFile->Sticks->draw(false);
		if(processFile->Menu->ModeSSBonds)
		{
			processFile->SSSticks->draw();
		}
		if(processFile->Menu->ModeHAtoms)
		{
			processFile->HSticks->draw(false);
		}

		glTranslatef(positioningX, positioningY, positioningZ);


	}
	if(processFile->Menu->ModeLigand)
	{
		glTranslatef(-positioningX, -positioningY, -positioningZ);
		processFile->draw();
		glTranslatef(positioningX, positioningY, positioningZ);

		size_t i = 0;
		do
		{
			if(processFile->HETAtoms.empty())
				break;
			if(!processFile->HETAtoms.at(i)->isPartOfLigand)
				{
					i++;
					continue;
				}
			if(processFile->Menu->ModeByElement)
			{
				//Color by element
				if(!processFile->HETAtoms.at(i)->element.compare(" C"))
				{
					glColor3f(0.5f, 0.5f, 0.5f); //Grijs
				}
				else if(!processFile->HETAtoms.at(i)->element.compare(" O"))
				{
					glColor3f(1.0f, 0.0f, 0.0f); //Rood
				}
				else if(!processFile->HETAtoms.at(i)->element.compare(" N"))
				{
					glColor3f(0.0f, 0.0f, 1.0f); //Blauw
				}
				else if(!processFile->HETAtoms.at(i)->element.compare(" P"))
				{
					glColor3f(1.0f, 0.5f, 0.0f); //Oranje
				}
				else if(!processFile->HETAtoms.at(i)->element.compare(" S"))
				{
					glColor3f(1.0f, 1.0f, 0.0f); //Geel
				}
				else if(!processFile->HETAtoms.at(i)->element.compare("ZN"))
				{
					glColor3f(0.5f, 1.0f, 0.0f); //Lila
				}
				else if(!processFile->HETAtoms.at(i)->element.compare(" H"))
				{
					glColor3f(1.0f, 1.0f, 1.0f); //Wit

				}
				else
				{
					glColor3f(0.0f, 0.0f, 0.0f);
				}
				}
			else
			{
				int colorNumber = processFile->Atoms.at(i)->chainNumber % 5;
				switch (colorNumber)
				{
				case 0:
					glColor3f(1.0f, 0.0f, 0.0f); //rood
					break;
				case 1:
					glColor3f(0.0f, 1.0f, 0.0f); //groen
					break;
				case 2:
					glColor3f(0.0f, 0.0f, 1.0f); //blauw
					break;
				case 3:
					glColor3f(1.0f, 1.0f, 0.0f); //geel
					break;
				case 4:
					glColor3f(1.0f, 0.0f, 1.0f); //roze
					break;
				case 5:
					glColor3f(0.0f, 1.0f, 1.0f); //cyaan
					break;
				default:
					glColor3f(1.0f, 1.0f, 1.0f); //wit
					break;
				}
			}
			//TODO Trimming spaces
			glTranslatef(processFile->HETAtoms.at(i)->location->X/10.0f - positioningX, 
				(processFile->HETAtoms.at(i)->location->Y/10.0f) - positioningY, 
				(processFile->HETAtoms.at(i)->location->Z/10.0f) - positioningZ);

			sphereModelLow->draw();

			glTranslatef(-1.0f * (processFile->HETAtoms.at(i)->location->X/10.0f - positioningX), 
				-1.0f * ((processFile->HETAtoms.at(i)->location->Y/10.0f) - positioningY), 
				-1.0f * ((processFile->HETAtoms.at(i)->location->Z/10.0f) - positioningZ));	
			i++;
		}// end i for loop
		while( i < processFile->HETAtoms.size());
	}
}

void PDBFileDemo::HighDraw(void)
{
	if(processFile->Menu->ModeProtein)
	{
		size_t i = 0;
		do
		{
			if(processFile->Atoms.empty())
				break;
			if(processFile->Menu->ModeByElement)
			{
				//Color by element
				if(!processFile->Atoms.at(i)->element.compare(" C"))
				{
					glColor3f(0.5f, 0.5f, 0.5f); //Grijs
				}
				else if(!processFile->Atoms.at(i)->element.compare(" O"))
				{
					glColor3f(1.0f, 0.0f, 0.0f); //Rood
				}
				else if(!processFile->Atoms.at(i)->element.compare(" N"))
				{
					glColor3f(0.0f, 0.0f, 1.0f); //Blauw
				}
				else if(!processFile->Atoms.at(i)->element.compare(" P"))
				{
					glColor3f(1.0f, 0.5f, 0.0f); //Oranje
				}
				else if(!processFile->Atoms.at(i)->element.compare(" S"))
				{
					glColor3f(1.0f, 1.0f, 0.0f); //Geel
				}
				else if(!processFile->Atoms.at(i)->element.compare("ZN"))
				{
					glColor3f(0.5f, 1.0f, 0.0f); //Lila
				}
				else if(!processFile->Atoms.at(i)->element.compare(" H"))
				{
					if(!processFile->Menu->ModeHAtoms)
						{
							i++;
							continue;
						}
					glColor3f(1.0f, 1.0f, 1.0f); //Wit

				}
				else
				{
					glColor3f(0.0f, 0.0f, 0.0f);
				}
				}
			else
			{
				int colorNumber = processFile->Atoms.at(i)->chainNumber % 5;
				switch (colorNumber)
				{
				case 0:
					glColor3f(1.0f, 0.0f, 0.0f); //rood
					break;
				case 1:
					glColor3f(0.0f, 1.0f, 0.0f); //groen
					break;
				case 2:
					glColor3f(0.0f, 0.0f, 1.0f); //blauw
					break;
				case 3:
					glColor3f(1.0f, 1.0f, 0.0f); //geel
					break;
				case 4:
					glColor3f(1.0f, 0.0f, 1.0f); //roze
					break;
				case 5:
					glColor3f(0.0f, 1.0f, 1.0f); //cyaan
					break;
				default:
					glColor3f(1.0f, 1.0f, 1.0f); //wit
					break;
				}
			}

			//TODO Trimming spaces

			glTranslatef(processFile->Atoms.at(i)->location->X/10.0f - positioningX, 
				(processFile->Atoms.at(i)->location->Y/10.0f) - positioningY, 
				(processFile->Atoms.at(i)->location->Z/10.0f) - positioningZ);

			sphereModelHigh->draw();

			glTranslatef(-1.0f * (processFile->Atoms.at(i)->location->X/10.0f - positioningX), 
				-1.0f * ((processFile->Atoms.at(i)->location->Y/10.0f) - positioningY), 
				-1.0f * ((processFile->Atoms.at(i)->location->Z/10.0f) - positioningZ));	
			i++;
		}
		while (i < processFile->Atoms.size());

		glTranslatef(-positioningX, -positioningY, -positioningZ);
		processFile->Sticks->draw(true);
		if(processFile->Menu->ModeSSBonds)
		{
			processFile->SSSticks->draw();
		}
		if(processFile->Menu->ModeHAtoms)
		{
			processFile->HSticks->draw(true);
		}

		glTranslatef(positioningX, positioningY, positioningZ);
	}
	if(processFile->Menu->ModeLigand)
	{
		glTranslatef(-positioningX, -positioningY, -positioningZ);
		processFile->draw();
		glTranslatef(positioningX, positioningY, positioningZ);
		size_t i = 0;
		do
		{
			if(processFile->HETAtoms.empty())
				break;
			if(!processFile->HETAtoms.at(i)->isPartOfLigand)
				{
					i++;
					continue;
				}
			if(processFile->Menu->ModeByElement)
			{
				//Color by element
				if(!processFile->HETAtoms.at(i)->element.compare(" C"))
				{
					glColor3f(0.5f, 0.5f, 0.5f); //Grijs
				}
				else if(!processFile->HETAtoms.at(i)->element.compare(" O"))
				{
					glColor3f(1.0f, 0.0f, 0.0f); //Rood
				}
				else if(!processFile->HETAtoms.at(i)->element.compare(" N"))
				{
					glColor3f(0.0f, 0.0f, 1.0f); //Blauw
				}
				else if(!processFile->HETAtoms.at(i)->element.compare(" P"))
				{
					glColor3f(1.0f, 0.5f, 0.0f); //Oranje
				}
				else if(!processFile->HETAtoms.at(i)->element.compare(" S"))
				{
					glColor3f(1.0f, 1.0f, 0.0f); //Geel
				}
				else if(!processFile->HETAtoms.at(i)->element.compare("ZN"))
				{
					glColor3f(0.5f, 1.0f, 0.0f); //Lila
				}
				else if(!processFile->HETAtoms.at(i)->element.compare(" H"))
				{
					glColor3f(1.0f, 1.0f, 1.0f); //Wit

				}
				else
				{
					glColor3f(0.0f, 0.0f, 0.0f);
				}
				}
			else
			{
				int colorNumber = processFile->Atoms.at(i)->chainNumber % 5;
				switch (colorNumber)
				{
				case 0:
					glColor3f(1.0f, 0.0f, 0.0f); //rood
					break;
				case 1:
					glColor3f(0.0f, 1.0f, 0.0f); //groen
					break;
				case 2:
					glColor3f(0.0f, 0.0f, 1.0f); //blauw
					break;
				case 3:
					glColor3f(1.0f, 1.0f, 0.0f); //geel
					break;
				case 4:
					glColor3f(1.0f, 0.0f, 1.0f); //roze
					break;
				case 5:
					glColor3f(0.0f, 1.0f, 1.0f); //cyaan
					break;
				default:
					glColor3f(1.0f, 1.0f, 1.0f); //wit
					break;
				}
			}
			//TODO Trimming spaces
			glTranslatef(processFile->HETAtoms.at(i)->location->X/10.0f - positioningX, 
				(processFile->HETAtoms.at(i)->location->Y/10.0f) - positioningY, 
				(processFile->HETAtoms.at(i)->location->Z/10.0f) - positioningZ);

			sphereModelHigh->draw();

			glTranslatef(-1.0f * (processFile->HETAtoms.at(i)->location->X/10.0f - positioningX), 
				-1.0f * ((processFile->HETAtoms.at(i)->location->Y/10.0f) - positioningY), 
				-1.0f * ((processFile->HETAtoms.at(i)->location->Z/10.0f) - positioningZ));	
			i++;
		}// end i for loop
		while (i < processFile->HETAtoms.size());
	}
}

void PDBFileDemo::draw(glm::mat4 projectionMatrix)
{
	//updateLightPosition(0.0f, 0.0f, 0.0f);
	glm::mat4 headMat = mHead.getData();
	glm::vec4 headPos = headMat * glm::vec4(0,0,0,1);
	glEnable(GL_COLOR_MATERIAL);	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	updateLightPosition(headPos[0],headPos[1],headPos[2]);

	glClear(GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_TEXTURE_2D);

	glColor3f(1.0f, 1.0f, 1.0f);

	processFile->Menu->Draw();


	glPushMatrix();
	//Translate to mid
	glTranslatef(-positioningX, -positioningY, -positioningZ);
	glRotatef((float)rotationX, 1.0f, 0.0f, 0.0f);
	glRotatef((float)rotationY, 0.0f, 1.0f, 0.0f);
	glRotatef((float)rotationZ, 0.0f, 0.0f, 1.0f);
	glTranslatef(positioningX, positioningY, positioningZ);
	
	if(processFile->Menu->ModeMedium)
	{
		MediumDraw();
	}
	else if(processFile->Menu->ModeLow)
	{
		
		LowDraw();
	}
	else if(processFile->Menu->ModeHigh)
	{
		HighDraw();
	}

	glPopMatrix();

	glDisable(GL_COLOR_MATERIAL);	
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDrawCube();
	if(headPos[2] > 1.3)
	{
		drawPointer();
	}
	frameCount++;
}

