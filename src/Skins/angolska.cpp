#include "angolska.h"
#include "../Vendor/imgui/imgui.h"

Angolska::Angolska()
{
	name = "Zyrafa angolska";
	primaryCol[0] = 173.f / 255;
	primaryCol[1] = 122.f / 255;
	primaryCol[2] = 63.f / 255;
	secondaryCol[0] = .96;
	secondaryCol[1] = .89;
	secondaryCol[2] = .72;
	borderL = 15, borderR = 33;
	noiseScaleFactor = 20;
	poisson = false;
	poissonRadius = 150;

	freq = 0.015;
	octaves = 5;
	lacunarity = 2.0;
	gain = 0.65;
	weightedStrength = 1.f;
}
