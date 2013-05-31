#include "EnzymePanel.h"
#include <cavelib/LayoutManagers/TableLayout.h>
#include <cavelib/LayoutManagers/FlowLayout.h>
#include <cavelib/Components/Panel.h>
#include <cavelib/Components/Label.h>
#include <CaveLib/Components/Button.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


EnzymePanel::EnzymePanel(int size, std::vector<cAtom*> Atoms) : GUIPanel("")
{
	rootPanel = new Panel(new TableLayoutManager(6));
	string tmp = "";
	for (int i = 0; i < size; i++)
	{
		if(Atoms.at(i)->residueName != tmp)
		{
			string txt = Atoms.at(i)->residueName;
			rootPanel->add(new Label(txt));
			atomBoxes.push_back(new CheckBox(false));
			rootPanel->add(atomBoxes.back());
			tmp = Atoms.at(i)->residueName;
		}
	}

	rootPanel->setFont(font);
	rootPanel->reposition(0,0,3,1.5f);

	renderMatrix = glm::mat4();
	renderMatrix = glm::translate(renderMatrix, glm::vec3(1.5,-1.0f,-2.0));
	renderMatrix = glm::rotate(renderMatrix, -90.0f, glm::vec3(0,1,0));

}


EnzymePanel::~EnzymePanel(void)
{
}
