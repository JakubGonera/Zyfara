#include "siatkowa.h"

Siatkowa::Siatkowa()
{
	name = "Zyrafa siatkowana";
	primaryCol[0] = 106.f / 255;
	primaryCol[1] = 54.f / 255;
	primaryCol[2] = 35.f / 255;
	secondaryCol[0] = 204.f / 255;
	secondaryCol[1] = 187.f / 255;
	secondaryCol[2] = 179.f / 255;
	borderL = 17;
	borderR = 17;
	noiseScaleFactor = 9;
	poisson = false;
	poissonRadius = 150;
}

