#include "DemoCaveWeek2.h"
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

DemoCaveWeek2::DemoCaveWeek2(void)
{

}

DemoCaveWeek2::~DemoCaveWeek2(void)
{

}

gmtl::Vec4f DemoCaveWeek2::collisionLinePlane(gmtl::Vec3f A, gmtl::Vec3f B, gmtl::Planef plane)
{
    gmtl::Vec3f AB = A - B;
    float denominator = gmtl::dot(AB, plane.getNormal());
    if(denominator == 0)
    	return gmtl::Vec4f(0,0,0, -1);
    float numerator = gmtl::dot(A, plane.getNormal()) + plane.getOffset();

    float t = - numerator / denominator;
    gmtl::normalize(AB);
    gmtl::Vec3f point = A + t*AB;
    return gmtl::Vec4f(point[0], point[1], point[2], t); 
}

gmtl::Vec3f DemoCaveWeek2::closestPoint(gmtl::Vec3f A, gmtl::Vec3f B, gmtl::Vec3f P)
{
    gmtl::Vec3f AB = B - A;
    float ab2  = gmtl::dot(AB, AB);// ab2 = length*length
    gmtl::Vec3f AP = P - A;
    float ap_dot_ab = gmtl::dot(AP, AB);
    float t  = ap_dot_ab / ab2; 
    if (t < 0.0f) 
	t = 0.0f; 
    else if (t > 1.0f) 
	t = 1.0f;
    gmtl::Vec3f Q = A + AB * t;
    return Q;
}

bool DemoCaveWeek2::pointInSphere(gmtl::Vec3f point, gmtl::Vec3f sphereLocation, float radius)
{
	float distanceBetweenPoints = 0.0f;
	float xDiff = 0.0f, yDiff = 0.0f, zDiff = 0.0f;
	xDiff = point[0] - sphereLocation[0];
	yDiff = point[1] - sphereLocation[1];
	zDiff = point[2] - sphereLocation[2];
	distanceBetweenPoints = (pow(xDiff, 2) + pow(yDiff, 2) + pow(zDiff, 2));
	if(distanceBetweenPoints < pow(radius, 2))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void DemoCaveWeek2::enableLight()
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

void DemoCaveWeek2::init()
{
	mWand.init("VJWand");
	mHead.init("VJHead");
	mButton0.init("VJButton0");
	targetObject = gmtl::Vec4f(-50.0f,0,-5,1);
}

void DemoCaveWeek2::init(int argc, char* argv[])
{
	glutInit(&argc, argv);
	mWand.init("VJWand");
	mHead.init("VJHead");
	mButton0.init("VJButton0");
	targetObject = gmtl::Vec4f(-50.0f,0,-5,1);
}

void DemoCaveWeek2::contextInit()
{
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	enableLight();
}
gmtl::Vec4f wandForward;
gmtl::Vec4f wandPosition;
void DemoCaveWeek2::preFrame()
{
	targetObject[0] += 0.2f;
	if (targetObject[0] > 50.0f)
	{
		srand(time(NULL));
		targetObject[0] = -50.0f;
		targetObject[1] = (rand() % 10) - 5.0f;
	}
	
	gmtl::Matrix44f wandMatrix = mWand->getData();
	wandPosition = wandMatrix * gmtl::Vec4f(0,0,0,1);
	wandForward = wandMatrix * gmtl::Vec4f(0,0,1,1);
}

void DemoCaveWeek2::bufferPreDraw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void DemoCaveWeek2::draw()
{
	glEnable(GL_LIGHTING);
	glClear(GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
    glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_TEXTURE_2D);

	gmtl::Planef plane(gmtl::Vec3f(0,0,-1), -5);
	gmtl::Vec4f ret = collisionLinePlane(
		gmtl::Vec3f(wandPosition[0], wandPosition[1], wandPosition[2]),
		gmtl::Vec3f(wandForward[0], wandForward[1], wandForward[2]),
		plane);

	glColor4f(0,0,1,1);
	
	glTranslatef(ret[0], ret[1], ret[2]);
	glutSolidSphere(0.5f, 10, 10);
	glTranslatef(-ret[0], -ret[1], -ret[2]);

	glTranslatef(targetObject[0], targetObject[1], targetObject[2]);
	glutSolidTeapot(0.5f);
	glTranslatef(-targetObject[0], -targetObject[1], -targetObject[2]);

	glColor4f(1,0,0,1);
	glBegin(GL_LINES);
		glVertex3f(wandPosition[0], wandPosition[1], wandPosition[2]);
		glVertex3f(ret[0], ret[1], ret[2]);
	glEnd();
	
	gmtl::Vec3f collision = closestPoint(
		gmtl::Vec3f(wandForward[0], wandForward[1], wandForward[2]),
		gmtl::Vec3f(ret[0], ret[1], ret[2]),
		gmtl::Vec3f(targetObject[0], targetObject[1], targetObject[2]));

	if(pointInSphere(collision, gmtl::Vec3f(targetObject[0], targetObject[1], targetObject[2]), 0.6f))
	{
		srand(time(NULL));
		targetObject[0] = -50.0f;
		targetObject[1] = (rand() % 10) - 5.0f;
	}
	
}

