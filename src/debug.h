#pragma once
#include <SFML/Graphics.hpp>
#include "Skins/skin.h"
#include "textureRendering.h"
#include <string>

//Class handling drawing ImGui window
class DebugUI {
	sf::Clock deltaClock;
	TextureRendering& renderer;
	int seed=2137;
	bool noiseEnabled = true;
	std::vector<Skin*> skins;
	Skin* currentSkin = nullptr;
	std::vector<std::string> names;
public:
	DebugUI(TextureRendering& _renderer, std::vector<Skin*> _skins);
	void renderDebug(sf::RenderWindow& window);
};