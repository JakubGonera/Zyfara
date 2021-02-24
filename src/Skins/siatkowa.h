#pragma once
#include "skin.h"
#include <tuple>

class Siatkowa : public Skin {
	float primaryCol[3] = {105.f/255,69.f/255,50.f/255};
	float secondaryCol[3] = { 204.f / 255,187.f / 255,179.f / 255 };
	float stripWidth = 17;
public:
	Siatkowa();
	void render(sf::Uint8* pixels, std::vector<float>& dists, float* noiseData) override;
	void displayDebug(sf::RenderWindow& window) override;
	const std::string& getName() override;
	std::tuple<int, int, int> getPrimaryCol();
	std::tuple<int, int, int> getSecondaryCol();
};