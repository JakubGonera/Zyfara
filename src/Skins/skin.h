#pragma once
#include "SFML/Graphics.hpp"
#include <string>

class Skin {
protected:
	std::string name;
public:
	virtual void render(sf::Uint8* pixels, std::vector<float>& dists, float* noiseData) = 0;
	virtual void displayDebug(sf::RenderWindow& window) = 0;
	virtual const std::string& getName() = 0;
};