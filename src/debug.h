#pragma once
#include <SFML/Graphics.hpp>

class DebugUI {
	sf::Clock deltaClock;
	char windowTitle[255] = "test";
	float color[3];
public:
	void renderDebug(sf::RenderWindow& window);
};