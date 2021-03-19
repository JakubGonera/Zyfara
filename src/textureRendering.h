#pragma once
#include <SFML/Graphics.hpp>
#include "voronoi.hpp"
#include "Vendor/FastNoise/FastNoiseLite.h"
#include "Skins/skin.h"

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

	void render(Skin* skin);
	void set_sv_seed(int val);
	int get_sv_seed();
	sf::Sprite& getSprite();
	FastNoiseLite& getNoise();
	void enableNoise(bool state);
};