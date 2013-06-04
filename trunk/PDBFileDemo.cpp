#include "PDBFileDemo.h"
#include <gl\glew.h>
#include <gl\GL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Vector3D.h"
#include "ProcessFile.h"
#include "ObjModel.h"
#include "Texture.h"
#include "cubemap.h"
#include "Defines.h"
#include "AtomPanel.h"

int rotationX = 0;
int rotationY = 0;
int rotationZ = 0;

float translationX = 0.0;
float translationY = 0.0;
float translationZ = 0.0;

cProcessFile* processFile;

//Cubemap* cubemap;

ObjModel* sphereModelLow;
ObjModel* sphereModelMedium;
ObjModel* sphereModelHigh;

float frameCount = 0;
unsigned long lastFrameRate;
unsigned long last_idle_time;

string fileToLoad = "";

float positioningX = 0.0f;
float positioningY = 0.0f;
float positioningZ = 0.0f;

int AimedAtom=0;
float Atomselectduration=0;

glm::vec4 wandForw;
glm::vec4 wandPos;
Plane plane(glm::vec3(0,0,-1), -5.3f);

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
	const std::string butf5("MiddleButton");
	const std::string butDown("KeyPageDown");
	const std::string butUp("KeyPageUp");

	mWand.init(wand);
	mHead.init(vjhead);
	mButton0.init(but0);
	mButton1.init(but1);
	mKeyPageDown.init(butDown);
	mKeyPageUp.init(butUp);
	mKeyF5.init(butf5);
	
	selectedAtom=0, DistanceAtom1=0, DistanceAtom2=34, OrbSelect=34, Xaddjust=0, Yaddjust=0, sphereSize3DSelect=1.0;
	selectSphereView=true;

	//tickCount = 0;

//	glutInit(&argc, argv);
	contextInit();

	last_idle_time = GetTickCount();
	lastFrameRate = last_idle_time;
}

void PDBFileDemo::initCubemap(void)
{
	float size = ((processFile->size));
	cout << "size: -" << fileToLoad << endl;
	cout << size << fileToLoad << endl;
	cout << ": -" << fileToLoad << endl;
	size = size/16.0f; //Cave 
	if(size < 1.5f)
		size = 1.5f;

	xSize = size + positioningX /2.0f;
	ySize = size + positioningY /2.0f;
	zSize = size + positioningZ /2.0f;
}

void PDBFileDemo::contextInit()
{

	if(fileToLoad.empty())
	{
		fileToLoad = "data/proteins/1DW5.pdb"; //3PTA //1DW5 //CutDNMT1
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
//	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
//	cubemap = new Cubemap("data/cubemaps/PdbViewer");
//	glActiveTexture(GL_TEXTURE3);
//	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap->textureId);
//	glActiveTexture(GL_TEXTURE0);

//	initCubemap();
	
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	menuPanel = new MainMenu();
	atomPanel = new AtomPanel();
	enzymePanel = new EnzymePanel(processFile->Atoms.size(), processFile->Atoms);
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
	Plane plane(glm::vec3(0,0,-1), -5.3f);
	glm::vec4 ret = collisionLinePlane(
		glm::vec3(wandPos[0], wandPos[1], wandPos[2]),
		glm::vec3(wandForw[0], wandForw[1], wandForw[2]),
		plane);
	processFile->Menu->AutoSetButtonGlow(glm::vec2(ret[0], ret[1]));

	glColor4f(1.0f,1.0f,0.0f,1.0f);
	glBegin(GL_LINES);
		glVertex3f(wandPos[0], wandPos[1], wandPos[2]);
		glVertex3f(ret[0], ret[1], ret[2]);
		//glVertex3f(wandForw[0],wandForw[1],wandForw[2]);
	glEnd();
}

void PDBFileDemo::glDrawCube()
{
	glColor4f(1,1,1,1);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_CUBE_MAP);
//	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap->textureId);
	
	glBegin(GL_QUADS);  
		//back
//		glTexCoord3f(1, -1, -1);	glVertex3f(-xSize,ySize, 100);//	size+z - 4.0);
//		glTexCoord3f(1, 1, -1);		glVertex3f(-xSize,-ySize,100);//	size+z - 4.0);
//		glTexCoord3f(-1, 1, -1);	glVertex3f(xSize,-ySize, 100);//	size+z - 4.0);
//		glTexCoord3f(-1, -1, -1);	glVertex3f(xSize,ySize,  100);//	size+z - 4.0);
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
	if(processFile->Menu->ModeSelectSingleAtom && processFile->Menu->Mode3DSelectie)
	{OrbSelect=selectedAtom;}

	if(processFile->Menu->ModeSelectSingleAtom &&  processFile->Menu->ModeDistanceMeasure)
	{ if(mButton0.getData() == ON){
		DistanceAtom1=selectedAtom;
	}else if(mButton1.getData() == ON){
		DistanceAtom2=selectedAtom;
	}
		}

//	if(processFile->Menu->

	if(Atomselectduration<25)
	{Atomselectduration+=1;}

	OrbSelect=selectedAtom;
	//FPS
	int diff = GetTickCount() - last_idle_time;

	last_idle_time = GetTickCount();

	if(last_idle_time - lastFrameRate > 5000)
	{
	//	std::cout << "FPS: " << frameCount / 5 << std::endl;
	//	frameCount = 0;
		lastFrameRate = last_idle_time;
	}

	glm::mat4 wandMatrix = mWand.getData();
	wandPos = wandMatrix * glm::vec4(0,0,0,1);
	wandForw = wandMatrix * glm::vec4(0,0,-1,1);

	glm::mat4 headMat = mHead.getData();
	glm::vec4 headPos = headMat * glm::vec4(0,0,0,1);

	//Main menu actions
	if(menuPanel)
	{
		glm::mat4 mat = mWand.getData();

		glm::vec4 origin = mat * glm::vec4(0,0,0,1);
		glm::vec4 point = mat * glm::vec4(0,0,-1,1);
		glm::vec4 diff = point - origin;

		menuPanel->setSelector(Ray(glm::vec3(origin[0], origin[1], origin[2]), glm::vec3(diff[0], diff[1], diff[2])));

		DigitalState data = mButton0.getData();
		

		if(data == TOGGLE_ON)
		{
			menuPanel->mouseDown();
		}
		else if(data == TOGGLE_OFF)
		{
			menuPanel->mouseUp();
		}
		else if (data == ON)
		{
		}
	}

	if(processFile->Menu->ModeCenterAtom){
		if(processFile->Atoms.at(selectedAtom)->location->X/10.0f >headPos[0]+positioningX+0.01f){
				positioningX+=abs(((processFile->Atoms.at(selectedAtom)->location->X/10.0f)-(headPos[0]+positioningX+0.01f))/20);
				
		}else if(processFile->Atoms.at(selectedAtom)->location->X/10.0f<headPos[0]+positioningX-0.01f){
			positioningX-=abs(((processFile->Atoms.at(selectedAtom)->location->X/10.0f)-(headPos[0]+positioningX-0.01f))/20);	
		}
		if(processFile->Atoms.at(selectedAtom)->location->Y/10.0f>headPos[1]+positioningY+0.01f){
			positioningY+=abs(((processFile->Atoms.at(selectedAtom)->location->Y/10.0f)-(headPos[1]+positioningY+0.01f))/20);
			
		} else if(processFile->Atoms.at(selectedAtom)->location->Y/10.0f<headPos[1]+positioningY-0.01f){
			positioningY-=abs(((processFile->Atoms.at(selectedAtom)->location->Y/10.0f)-(headPos[1]+positioningY-0.01f))/20);
		}
	}

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

		glm::vec4 ret = collisionLinePlane(
		glm::vec3(wandPos[0], wandPos[1], wandPos[2]),
		glm::vec3(wandForw[0], wandForw[1], wandForw[2]),
		plane);
	DistanceAtom2=selectedAtom;

	if(processFile->Menu->Mode3DSelectie){
	glDisable(GL_DEPTH_TEST);	
	glColor4f(0.0f,0.3f,0.7f,0.1f);

	 drawSphere(1.0, processFile->Atoms.at(OrbSelect)->location->X/10,processFile->Atoms.at(OrbSelect)->location->Y/10,processFile->Atoms.at(OrbSelect)->location->Z/10);
	}
	glEnable(GL_DEPTH_TEST);

	if(processFile->Menu->ModeDistanceMeasure){
	GetDisctanceBetweenAtoms(DistanceAtom1,DistanceAtom2);
	}

	float WandToClostAtomD=-1;

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
					glColor4f(0.5f, 0.5f, 0.5f, 1.0f); //Grijs
				}
				else if(!processFile->Atoms.at(i)->element.compare(" O"))
				{
					glColor4f(1.0f, 0.0f, 0.0f, 1.0f); //Rood
				}
				else if(!processFile->Atoms.at(i)->element.compare(" N"))
				{
					glColor4f(0.0f, 0.0f, 1.0f, 1.0f); //Blauw
				}
				else if(!processFile->Atoms.at(i)->element.compare(" P"))
				{
					glColor4f(1.0f, 0.5f, 0.0f, 1.0f); //Oranje
				}
				else if(!processFile->Atoms.at(i)->element.compare(" S"))
				{
					glColor4f(1.0f, 1.0f, 0.0f, 1.0f); //Geel
				}
				else if(!processFile->Atoms.at(i)->element.compare("ZN"))
				{
					glColor4f(0.5f, 1.0f, 0.0f, 1.0f); //Lila
				}
				else if(!processFile->Atoms.at(i)->element.compare(" H"))
				{
					if(!processFile->Menu->ModeHAtoms)
					{
					processFile->Atoms.at(i)->draw=false;
					i++;
					continue;
					}
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f); //Wit
					processFile->Atoms.at(i)->draw=true;

				}
				else
				{
					glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
				}
			}
			else
			{
				int colorNumber = processFile->Atoms.at(i)->chainNumber % 5;
				switch (colorNumber)
				{
				case 0:
					glColor4f(1.0f, 0.0f, 0.0f, 1.0f); //rood
					break;
				case 1:
					glColor4f(0.0f, 1.0f, 0.0f, 1.0f); //groen
					break;
				case 2:
					glColor4f(0.0f, 0.0f, 1.0f, 1.0f); //blauw
					break;
				case 3:
					glColor4f(1.0f, 1.0f, 0.0f, 1.0f); //geel
					break;
				case 4:
					glColor4f(1.0f, 0.0f, 1.0f, 1.0f); //roze
					break;
				case 5:
					glColor4f(0.0f, 1.0f, 1.0f, 1.0f); //cyaan
					break;
				default:
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f); //wit
					break;
				}
			}

			float DistanceFromAtoomToHead=0;
			if(processFile->Menu->Mode3DSelectie){
				DistanceFromAtoomToHead = get3DDistance(processFile->Atoms.at(i)->location->X/10.0f,processFile->Atoms.at(i)->location->Y/10.0f,processFile->Atoms.at(i)->location->Z/10.0f,processFile->Atoms.at(OrbSelect)->location->X/10,processFile->Atoms.at(OrbSelect)->location->Y/10,processFile->Atoms.at(OrbSelect)->location->Z/10);
			} else {
					processFile->Atoms.at(i)->draw=true;
			}
			if(DistanceFromAtoomToHead<sphereSize3DSelect || !selectSphereView){
					processFile->Atoms.at(i)->draw=true; //yea
					
			glTranslatef((processFile->Atoms.at(i)->location->X/10.0f - positioningX), 
				((processFile->Atoms.at(i)->location->Y/10.0f) - positioningY), 
				((processFile->Atoms.at(i)->location->Z/10.0f) - positioningZ));

			sphereModelMedium->draw();

			glTranslatef((-1.0f * (processFile->Atoms.at(i)->location->X/10.0f - positioningX)), 
				(-1.0f * ((processFile->Atoms.at(i)->location->Y/10.0f) - positioningY)), 
				(-1.0f * ((processFile->Atoms.at(i)->location->Z/10.0f) - positioningZ)));	
				}else{
					processFile->Atoms.at(i)->draw=false;
			}
			if(processFile->Menu->ModeSelectSingleAtom){
				//yea
				
				int checkdensity=30;
				for(int cnt = 0; cnt <= checkdensity; cnt++) 
				{
	
					//2D
				//	float tempdistance = get3DDistance((processFile->Atoms.at(i)->location->X/10.0f),(processFile->Atoms.at(i)->location->Y/10.0f),-5.3,positioningX+(wandForw[0])+((ret[0]-wandForw[0])/30)*30,positioningY+(wandForw[1])+((ret[1]-wandForw[1])/30)*30,-5.3);
					//3D
					float tempdistance = get3DDistance((processFile->Atoms.at(i)->location->X/10.0f),(processFile->Atoms.at(i)->location->Y/10.0f),(processFile->Atoms.at(i)->location->Z/10.0f),positioningX+(wandForw[0])+((ret[0]-wandForw[0])/checkdensity)*cnt,positioningY+(wandForw[1])+((ret[1]-wandForw[1])/checkdensity)*cnt,positioningZ+(wandForw[2])+((ret[2]-wandForw[2])/checkdensity)*cnt);
					if(DistanceFromAtoomToHead==0){
					DistanceFromAtoomToHead=tempdistance;}
					if(tempdistance<DistanceFromAtoomToHead)
					{DistanceFromAtoomToHead=tempdistance;}
				}

				if(WandToClostAtomD<0){
				WandToClostAtomD=DistanceFromAtoomToHead;
				}

			//	drawSphere(0.1,wandPos[0]+positioningX,wandPos[1]+positioningY,wandPos[2]+positioningZ);
				if( DistanceFromAtoomToHead<WandToClostAtomD && processFile->Atoms.at(i)->draw){
					if(mButton0.getData() == ON ){
					Atomselectduration=0;
					selectedAtom=i;}
					WandToClostAtomD=DistanceFromAtoomToHead;
					AimedAtom=i;
			//		glm::vec3 gmtlCor = glm::vec3(wandPos[0], wandPos[1], wandPos[2]);
			//		glm::vec3 gmtlVec = glm::vec3(wandForw[0], wandForw[1], wandForw[2]);
				}
				
			}
			i++;
		}
		while(i < processFile->Atoms.size() );

		cout << "AimedAtom: |" << AimedAtom  << endl;
					if(processFile->Menu->ModeSelectSingleAtom ){

				glPushAttrib(GL_CURRENT_BIT);
				glDisable(GL_DEPTH_TEST);
				glEnable(GL_BLEND); 
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Set the blend function
				glColor4f(1.0f,1.0f,0.2f,0.5f);

				cout << Atomselectduration << endl;
				//wtf!?!
		//		float whut = (sin((((Atomselectduration+75)/200)*M_PI)+((75/200)*M_PI))-0.75)*6;
		//		float whut2 = (sin(((Atomselectduration/200)*M_PI))-0.75)*6;
		//		cout << whut << endl;
		//		cout << whut2 << endl;

				float firstselecthop = ((sin((((Atomselectduration+37.5)/100)*M_PI))-0.75)*6);
				cout << pow(firstselecthop,2) << endl;
	drawBlinkSphere(0.1*pow(firstselecthop,2), processFile->Atoms.at(selectedAtom)->location->X/10.0f,processFile->Atoms.at(selectedAtom)->location->Y/10.0f,processFile->Atoms.at(selectedAtom)->location->Z/10.0f);
	//pre Select Atom
	drawBlinkSphere(0.05,  processFile->Atoms.at(AimedAtom)->location->X/10.0f,   processFile->Atoms.at(AimedAtom)->location->Y/10.0f,   processFile->Atoms.at(AimedAtom)->location->Z/10.0f);

		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);	
		glPopAttrib();
			}

		//float test = processFile->Sticks->sticks[1][0]->X;
		glTranslatef(-positioningX, -positioningY, -positioningZ);

		i = 0;
		do
		{
					float DistanceFromStickToHead=0;
			if(processFile->Menu->Mode3DSelectie){

				DistanceFromStickToHead = get3DDistance(processFile->Sticks->sticks[i][0]->X/10.0f,processFile->Sticks->sticks[i][0]->Y/10.0f,processFile->Sticks->sticks[i][0]->Z/10.0f,processFile->Atoms.at(OrbSelect)->location->X/10,processFile->Atoms.at(OrbSelect)->location->Y/10,processFile->Atoms.at(OrbSelect)->location->Z/10);
				float DistanceFromStickToHead2 = get3DDistance(processFile->Sticks->sticks[i][1]->X/10.0f,processFile->Sticks->sticks[i][1]->Y/10.0f,processFile->Sticks->sticks[i][1]->Z/10.0f,processFile->Atoms.at(OrbSelect)->location->X/10,processFile->Atoms.at(OrbSelect)->location->Y/10,processFile->Atoms.at(OrbSelect)->location->Z/10);
				if(DistanceFromStickToHead2>DistanceFromStickToHead)
				{DistanceFromStickToHead=DistanceFromStickToHead2;}
			}
			if(DistanceFromStickToHead<sphereSize3DSelect ){
				processFile->Sticks[0].draw(true, i);
			}else if (!selectSphereView) {
				processFile->Sticks[0].draw(true, i);
			}
			i++;}
		while(i < processFile->Sticks->sticks.size());
		
		//processFile->Sticks->draw(false);
		if(processFile->Menu->ModeSSBonds)
		{
	//		processFile->SSSticks->draw(); TODO
		}
		if(processFile->Menu->ModeHAtoms)
		{
	//		processFile->HSticks->draw(true); TODO
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
			glTranslatef(((processFile->HETAtoms.at(i)->location->X/10.0f) - positioningX), 
				((processFile->HETAtoms.at(i)->location->Y/10.0f) - positioningY), 
				((processFile->HETAtoms.at(i)->location->Z/10.0f) - positioningZ));

			sphereModelMedium->draw();

			glTranslatef(-1.0f * ((processFile->HETAtoms.at(i)->location->X/10.0f - positioningX)), 
				(-1.0f * ((processFile->HETAtoms.at(i)->location->Y/10.0f) - positioningY)), 
				(-1.0f * ((processFile->HETAtoms.at(i)->location->Z/10.0f) - positioningZ)));	
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
//		processFile->Sticks->draw(false); TODO
		if(processFile->Menu->ModeSSBonds)
		{
//			processFile->SSSticks->draw(); TODO
		}
		if(processFile->Menu->ModeHAtoms)
		{
//			processFile->HSticks->draw(false); TODO
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
//		processFile->Sticks->draw(true); TODO
		if(processFile->Menu->ModeSSBonds)
		{
//			processFile->SSSticks->draw(); TODO
		}
		if(processFile->Menu->ModeHAtoms)
		{
//			processFile->HSticks->draw(true); TODO
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

void PDBFileDemo::drawBlinkSphere(float size, float X, float Y, float Z)
{
	glTranslatef(X,Y,Z);
	glTranslatef(-positioningX, -positioningY, -positioningZ);
	  int i1, j1;
        for(i1 = 0; i1 <= 16; i1++) {
           double lat0 = 3.14 * (-0.5 + (double) (i1 - 1) / 16);
           double z0  = sin(lat0);
           double zr0 =  cos(lat0);
    
           double lat1 = 3.14 * (-0.5 + (double) i1 / 16);
           double z1 = sin(lat1);
           double zr1 = cos(lat1);
    
           glBegin(GL_QUAD_STRIP);
          for(j1 = 0; j1 <= 16; j1++) {
               double lng = 2 * 3.14 * (double) (j1 - 1) / 16;
               double x = cos(lng);
               double y = sin(lng);

			  glNormal3f(x*size * zr0, y*size * zr0, z0*size);
              glVertex3f(x*sin(frameCount/12)*size * zr0, y*sin(frameCount/12)*size * zr0, z0*sin(frameCount/12)*size);
              glNormal3f(x*size * zr1, y*size * zr1, z1*size);
              glVertex3f(x*sin(frameCount/12)*size * zr1, y*sin(frameCount/12)*size * zr1, z1*sin(frameCount/12)*size);
          }
          glEnd();
       }
		glTranslatef(positioningX, positioningY, positioningZ);
		glTranslatef(-X,-Y,-Z);
}

void PDBFileDemo::drawSphere(float size, float X, float Y, float Z)
{
	glTranslatef(X,Y,Z);
	glTranslatef(-positioningX, -positioningY, -positioningZ);
	  int i1, j1;
        for(i1 = 0; i1 <= 16; i1++) {
           double lat0 = 3.14 * (-0.5 + (double) (i1 - 1) / 16);
           double z0  = sin(lat0);
           double zr0 =  cos(lat0);
    
           double lat1 = 3.14 * (-0.5 + (double) i1 / 16);
           double z1 = sin(lat1);
           double zr1 = cos(lat1);
    
           glBegin(GL_QUAD_STRIP);
          for(j1 = 0; j1 <= 16; j1++) {
               double lng = 2 * 3.14 * (double) (j1 - 1) / 16;
               double x = cos(lng);
               double y = sin(lng);

			  glNormal3f(x*size * zr0, y*size * zr0, z0*size);
              glVertex3f(x*size * zr0, y*size * zr0, z0*size);
              glNormal3f(x*size * zr1, y*size * zr1, z1*size);
              glVertex3f(x*size * zr1, y*size * zr1, z1*size);
          }
          glEnd();
       }
		glTranslatef(positioningX, positioningY, positioningZ);
		glTranslatef(-X,-Y,-Z);
}

float PDBFileDemo::GetDisctanceBetweenAtoms(int Atom1, int Atom2)
{
	float Distance = get3DDistance(processFile->Atoms.at(Atom1)->location->X/10.0f,processFile->Atoms.at(Atom1)->location->Y/10.0f,processFile->Atoms.at(Atom1)->location->Z/10.0f,processFile->Atoms.at(Atom2)->location->X/10.0f,processFile->Atoms.at(Atom2)->location->Y/10.0f,processFile->Atoms.at(Atom2)->location->Z/10.0f);

				glColor4f(0.0f,1.0f,0.0f,1.0f);
		drawBlinkSphere(0.06, processFile->Atoms.at(Atom1)->location->X/10.0f, processFile->Atoms.at(Atom1)->location->Y/10.0f, processFile->Atoms.at(Atom1)->location->Z/10.0f);
		drawBlinkSphere(0.06, processFile->Atoms.at(Atom2)->location->X/10.0f, processFile->Atoms.at(Atom2)->location->Y/10.0f, processFile->Atoms.at(Atom2)->location->Z/10.0f);

				glTranslatef(processFile->Atoms.at(Atom1)->location->X/10.0f - positioningX, 
				(processFile->Atoms.at(Atom1)->location->Y/10.0f) - positioningY, 
				(processFile->Atoms.at(Atom1)->location->Z/10.0f) - positioningZ);

	glBegin(GL_LINES);
		  glVertex3f(processFile->Atoms.at(Atom2)->location->X/10.0f-(processFile->Atoms.at(Atom1)->location->X/10.0f), processFile->Atoms.at(Atom2)->location->Y/10.0f-(processFile->Atoms.at(Atom1)->location->Y/10.0f), processFile->Atoms.at(Atom2)->location->Z/10.0f-(processFile->Atoms.at(Atom1)->location->Z/10.0f));
		  glVertex3f(0,0,0);
		 glEnd();

			glTranslatef(-1.0f * (processFile->Atoms.at(Atom1)->location->X/10.0f - positioningX), 
				-1.0f * ((processFile->Atoms.at(Atom1)->location->Y/10.0f) - positioningY), 
				-1.0f * ((processFile->Atoms.at(Atom1)->location->Z/10.0f) - positioningZ));

			//std::cout << "Distance:" << Distance*10 << endl;
		return Distance*10;
}

float PDBFileDemo::get3DDistance(float X1, float Y1, float Z1, float X2, float Y2, float Z2)
{
				float DeltaX=pow(abs(X1-X2),2);
				float DeltaY=pow(abs(Y1-Y2),2);
				float DeltaZ=pow(abs(Z1-Z2),2);
				return sqrtf(DeltaX+DeltaY+DeltaZ);
}

void PDBFileDemo::draw(glm::mat4 projectionMatrix)
{
	
	glEnable(GL_BLEND); //Enable alpha blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Set the blend function

	//updateLightPosition(0.0f, 0.0f, 0.0f);
	glm::mat4 headMat = mHead.getData();
	glm::vec4 headPos = headMat * glm::vec4(0,0,0,1);
	glEnable(GL_COLOR_MATERIAL);	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	updateLightPosition(headPos[0],headPos[1],headPos[2]);

	menuPanel->draw();
	if(menuPanel->ModeAtomInfo)
		atomPanel->draw();
	enzymePanel->draw();

	glClear(GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_TEXTURE_2D);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

//	processFile->Menu->Draw();
	glDisable(GL_DEPTH_TEST);
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
//	glDrawCube();
//	if(headPos[2] > 1.3)
//	{
		drawPointer();
//	}
	frameCount++;
}

