#include "DemoCaveApplication.h"
#include <gl\GL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <gmtl/Generate.h>
#include <gmtl/Vec.h>
#include <gmtl/VecOps.h>
#include <gmtl/Matrix.h>
#include <gmtl/MatrixOps.h>

#include "Vector3D.h"

gmtl::Vec4f cubes [100];

DemoCaveApplication::DemoCaveApplication(void)
{
}

DemoCaveApplication::~DemoCaveApplication(void)
{
}

void enableLight()
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 0.0, 0.0, -1.0, 0.0 };
	GLfloat ambient[] = {0.0, 0.0, 0.0, 1.0};
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void DemoCaveApplication::init()
{
	mWand.init("WandPosition");
	mHead.init("MainUserHead");
	mButton0.init("LeftButton");

	for(int i = 0; i < 100; i++)
	{
		srand ( i );
		cubes[i][0] = 0.0f;
		cubes[i][1] = 0.0f;
		cubes[i][2] = 0.0f;
	}
}

void DemoCaveApplication::init(int argc, char* argv[])
{
	//glutInit(&argc, argv);

	contextInit();
}

void DemoCaveApplication::contextInit()
{
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	enableLight();
}

void DemoCaveApplication::preFrame()
{
	mWand->updateData();
	gmtl::Matrix44f wandMat = mWand->getData();
	gmtl::Vec4f pos = wandMat * gmtl::Vec4f(0,0,0,1);
	for(int i = 0; i < 100; i++)
	{
		cubes[i][1] -= 0.05;
		if(cubes[i][1] < -10.0f)
		{
			cubes[i][0] = pos.mData[0];
			cubes[i][1] = pos.mData[1];
			cubes[i][2] = pos.mData[2];
		}
	}
}
/*
void DemoCaveApplication::bufferPreDraw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}
*/
void DemoCaveApplication::draw()
{
	glEnable(GL_LIGHTING);
	//glClear(GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
    glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_TEXTURE_2D);
	
	//Drawing
	glColor3f(1.0f, 0.0f, 0.0f);
	for(int i = 0; i < 100; i++)
	{
		glTranslatef(cubes[i][0], cubes[i][1], cubes[i][2]);
		//glutSolidCube(0.1f);
		glTranslatef(-cubes[i][0], -cubes[i][1], -cubes[i][2]);
	}
}

