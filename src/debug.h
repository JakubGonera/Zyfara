#pragma once
#include <SFML/Graphics.hpp>
#include "Skins/skin.h"
#include "textureRendering.h"
#include <string>

class DebugUI {
	sf::Clock deltaClock;
	TextureRendering& renderer;
	int seed=2137;
	float freq = 0.01;
	int octaves = 5;
	float lacunarity = 2.0;
	float gain = 0.5;
	bool noiseEnabled = true;
	std::vector<Skin*> skins;
	Skin* currentSkin = nullptr;
	std::vector<std::string> names;
public:
	DebugUI(TextureRendering& _renderer, std::vector<Skin*> _skins);
	void renderDebug(sf::RenderWindow& window);
};