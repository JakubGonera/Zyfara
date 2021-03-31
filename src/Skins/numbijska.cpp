#include "numbijska.h"
#include "../Vendor/imgui/imgui.h"

Numbijska::Numbijska()
{
	name = "Zyrafa numbijska";
	primaryCol[0] = 173.f / 255;
	primaryCol[1] = 122.f / 255;
	primaryCol[2] = 63.f / 255;
	secondaryCol[0] = .96;
	secondaryCol[1] = .89;
	secondaryCol[2] = .72;
	borderL = 10.5, borderR = 19;
	noiseScaleFactor = 7.5;
	poisson = false;
	poissonRadius = 150;

}
