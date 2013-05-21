#pragma comment(lib, "opengl32")

#include "DemoCaveApplication.h"
#include "DemoCaveWeek2.h"
#include "PDBFileDemo.h"
#include <VrLib/Kernel.h>

int main(int argc, char* argv[])
{
	Kernel* kernel = Kernel::getInstance();
	for(int i =1; i < argc; i++)
	{
		if(strcmp(argv[i], "--config") == 0)
		{
			i++;
			kernel->loadConfig(argv[i]);
		}
	}

	PDBFileDemo* application = new PDBFileDemo(argc, argv);
	kernel->setApp(application);
	kernel->start();
	delete application;

	return 0;
}