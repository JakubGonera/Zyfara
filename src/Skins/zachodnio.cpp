#include "zachodnio.h"

Zachodnio::Zachodnio()
{
	name = "Zyrafa zachodnioafrykanska";
	primaryCol[0] = 179.f / 255;
	primaryCol[1] = 134.f / 255;
	primaryCol[2] = 80.f / 255;
	secondaryCol[0] = 244.f / 255;
	secondaryCol[1] = 227.f / 255;
	secondaryCol[2] = 199.f / 255;
	borderL = 25, borderR = 25;
	noiseScaleFactor = 10;
	poisson = true;
	poissonRadius = 230;
	shaded = true;
}
