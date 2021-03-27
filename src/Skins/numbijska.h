#pragma once
#include "skin.h"
#include <tuple>

class Numbijska : public Skin {
	float primaryCol[3] = { 164.f/255, 124.f/255, 77.f/255};
	float secondaryCol[3] = { .96, .89, .72};
	float stripWidth = 17;
	float borderL = 10.5, borderR = 19;
	float noiseScaleFactor = 10;
public:
	Numbijska();
	void render(sf::Uint8* pixels, slowvoronoi& sv, float* noiseData) override;
	void displayDebug(sf::RenderWindow& window) override;
	const std::string& getName() override;
	std::tuple<int, int, int> getPrimaryCol();
	std::tuple<int, int, int> getSecondaryCol();
};
