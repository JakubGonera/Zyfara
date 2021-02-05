#pragma once
#include <SFML/Graphics.hpp>
#include "voronoi.hpp"
#include "Vendor/FastNoise/FastNoiseLite.h"

class TextureRendering {
	sf::Uint8* pixels = nullptr;
	float* noiseData = nullptr;
	slowvoronoi sv;
	sf::Texture texture;
	sf::Sprite sprite;
	FastNoiseLite noise;
	bool noiseEnabled = true;
public:
	TextureRendering(int width, int height);
	~TextureRendering();

	void render();

	sf::Sprite& getSprite();
	FastNoiseLite& getNoise();
	void enableNoise(bool state);
};