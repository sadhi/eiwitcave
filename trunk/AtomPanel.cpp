#include "AtomPanel.h"
#include <cavelib/LayoutManagers/TableLayout.h>
#include <cavelib/Components/Label.h>
#include <CaveLib/Components/Panel.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

AtomPanel::AtomPanel(void) : GUIPanel("")
{
	rootPanel = new Panel(new TableLayoutManager(2));
	name = element = residueN = "";
	charge = chain = residueS = 0;
	rootPanel->add(new Label("Name: " + name));
	rootPanel->add(new Label("Charge: " + charge));
	rootPanel->add(new Label("Chain number: " + chain));
	rootPanel->add(new Label("Element: " + element));
	rootPanel->add(new Label("Residue name: " + residueN));
	rootPanel->add(new Label("sequence number: " + residueS));

	rootPanel->setFont(font);
	rootPanel->reposition(0,0,1.4f,0.7f);

	renderMatrix = glm::mat4();
	renderMatrix = glm::translate(renderMatrix, glm::vec3(-0.7,-1.6f,0.0));
	renderMatrix = glm::rotate(renderMatrix, 270.0f, glm::vec3(1,0,0));
}


AtomPanel::~AtomPanel(void)
{
}
