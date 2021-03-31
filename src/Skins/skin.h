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

	float primaryCol[3] = { 105.f / 255,69.f / 255,50.f / 255 };
	float shadeCol[3] = { 105.f / 255,69.f / 255,50.f / 255 };
	float secondaryCol[3] = { 204.f / 255,187.f / 255,179.f / 255 };
	float borderL = 17, borderR = 17;
	float noiseScaleFactor = 9;
	float noiseZoom = 1;
	bool poisson = false;
	int poissonRadius = 150;
	bool shaded = false;
public:
	float* getFreq();
	float* getLacunarity();
	float* getGain();
	int* getOctaves();
	float* getStrength();
	void setNoise(FastNoiseLite& noise);
	void render(sf::Uint8* pixels, slowvoronoi& sv, FastNoiseLite& noise);
	void displayDebug(sf::RenderWindow& window);
	const std::string& getName();
};