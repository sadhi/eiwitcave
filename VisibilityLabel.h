#pragma once
#include <cavelib/components/label.h>
class VisibilityLabel :
	public Label
{
public:
	VisibilityLabel(std::string text, bool v);
	~VisibilityLabel(void);
	
	void render(float);
	void setVisibility(bool);
	bool getVisibility(void);

private:
	bool visible;
};

