#pragma once
#include <SFML/Graphics.hpp>

#include "textureRendering.h"

class DebugUI {
	sf::Clock deltaClock;
	TextureRendering& renderer;
	float freq = 0.01;
	int octaves = 5;
	float lacunarity = 2.0;
	float gain = 0.5;
	bool noiseEnabled = true;
public:
	DebugUI(TextureRendering& _renderer);
	void renderDebug(sf::RenderWindow& window);
};