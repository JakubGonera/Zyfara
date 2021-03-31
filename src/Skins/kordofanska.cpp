#include "kordofanska.h"
#include "../Vendor/imgui/imgui.h"

Kordofanska::Kordofanska()
{
	name = "Zyrafa kordofanska";
	primaryCol[0] = 135.f / 255;
	primaryCol[1] = 95.f / 255;
	primaryCol[2] = 48.f / 255;
	secondaryCol[0] = 219.f / 255;
	secondaryCol[1] = 206.f / 255;
	secondaryCol[2] = 176.f / 255;
	shadeCol[0] = 0;
	shadeCol[1] = 0;
	shadeCol[2] = 0;
	borderL = 15, borderR = 33;
	noiseScaleFactor = 20;
	poisson = false;
	poissonRadius = 150;

	freq = 0.015;
	octaves = 5;
	lacunarity = 1.76;
	gain = 0.67;
	weightedStrength = 2.4f;

	shaded = true;
}
