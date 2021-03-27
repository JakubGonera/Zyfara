#pragma once
#include "skin.h"
#include <tuple>

class Zachodnio : public Skin {
	float primaryCol[3] = { 179.f / 255,134.f / 255,80.f / 255 };
	float secondaryCol[3] = { 244.f / 255,227.f / 255,199.f / 255 };
	float stripWidth = 20;
	float borderL = 25, borderR = 25;
	float noiseScaleFactor = 10;
public:
	Zachodnio();
	void render(sf::Uint8* pixels, slowvoronoi& sv, float* noiseData) override;
	void displayDebug(sf::RenderWindow& window) override;
	const std::string& getName() override;
	std::tuple<int, int, int> getPrimaryCol();
	std::tuple<int, int, int> getSecondaryCol();
};