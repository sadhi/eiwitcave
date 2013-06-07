#pragma once
#include <cavelib/components/checkbox.h>
class VisibilityCheckBox :
	public CheckBox
{
public:
	VisibilityCheckBox(bool value, bool v);
	VisibilityCheckBox(bool value, bool v, fastdelegate::FastDelegate0<> onclick);
	~VisibilityCheckBox(void);

	void render(float);
	void setVisibility(bool);
	bool getVisibility(void);

private:
	bool visible;
};

