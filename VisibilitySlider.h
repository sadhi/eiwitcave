#pragma once
#include <cavelib\components\slider.h>
class VisibilitySlider :
	public Slider
{
public:
	VisibilitySlider(float min, float max, float value, bool v);
	~VisibilitySlider(void);

	void render(float);
	bool getVisibility(void);
	void setVisibility(bool);

private:
	bool visible;
};

