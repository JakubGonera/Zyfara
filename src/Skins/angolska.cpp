#include "angolska.h"
#include "../Vendor/imgui/imgui.h"

Angolska::Angolska()
{
	name = "Zyrafa angolska";
	primaryCol[0] = 134.f / 255;
	primaryCol[1] = 78.f / 255;
	primaryCol[2] = 14.f / 255;
	secondaryCol[0] = .96;
	secondaryCol[1] = .89;
	secondaryCol[2] = .72;
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
