#pragma once
#include "SFML/Graphics.hpp"
#include <string>
#include "../voronoi.hpp"
#include "../Vendor/FastNoise/FastNoiseLite.h"

//Base class for all skin patterns, it includes all parameters, so every skin is created via specifing these parameters

class Skin {
protected:
	std::string name;

	//Noise parameters that are supplied to library FastNoiseLight that generates Simplex Noise
	float freq = 0.01;
	int octaves = 5;
	float lacunarity = 2.0;
	float gain = 0.5;
	float weightedStrength = 0.f;
	float noiseScaleFactor = 9;
	float noiseZoom = 1;
	
	//Main colour of colour patches
	float primaryCol[3] = { 105.f / 255,69.f / 255,50.f / 255 };
	//The colour that interior fades into
	float shadeCol[3] = { 105.f / 255,69.f / 255,50.f / 255 };
	//Colour of gaps
	float secondaryCol[3] = { 204.f / 255,187.f / 255,179.f / 255 };
	//Range of gaps width (setting them equal results in uniform gaps)
	float borderL = 17, borderR = 17;

	//Setting whether poisson disk sampling is enabled
	bool poisson = false;
	//Distance between patches
	int poissonRadius = 150;

	//Enable shading
	bool shaded = false;
public:
	void setNoise(FastNoiseLite& noise);
	//Main function that handles rendering our skin
	void render(sf::Uint8* pixels, slowvoronoi& sv, FastNoiseLite& noise);
	//Displaying ImGui widgets used to tweak skin's parameters
	void displayDebug(sf::RenderWindow& window);
	const std::string& getName();
};