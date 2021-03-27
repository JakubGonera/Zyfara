#pragma once
#include "SFML/Graphics.hpp"
#include <string>
#include "../voronoi.hpp"
#include "../Vendor/FastNoise/FastNoiseLite.h"


class Skin {
protected:
	std::string name;
	float freq = 0.01;
	int octaves = 5;
	float lacunarity = 2.0;
	float gain = 0.5;
	float weightedStrength = 0.f;
public:
	float* getFreq();
	float* getLacunarity();
	float* getGain();
	int* getOctaves();
	float* getStrength();
	void setNoise(FastNoiseLite& noise);
	virtual void render(sf::Uint8* pixels, slowvoronoi& sv, float* noiseData) = 0;
	virtual void displayDebug(sf::RenderWindow& window) = 0;
	virtual const std::string& getName() = 0;
};