#include "textureRendering.h"

TextureRendering::TextureRendering(int width, int height)
{
	pixels = new sf::Uint8[width * height * 4];
	texture.create(width, height);
	sprite.setTexture(texture);

	//Setting up simplex noise
	noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
	noise.SetFractalType(FastNoiseLite::FractalType_FBm);
	noise.SetFrequency(0.01);
	noise.SetFractalLacunarity(2.8f);
	noiseData = new float[width * height];
	int noiseIndex = 0;
}

TextureRendering::~TextureRendering()
{
	delete[] pixels;
	delete[] noiseData;
}

void TextureRendering::render(Skin* skin) {
	int noiseIndex = 0;
	for (int x = 0; x < 1280; x++)
	{
		for (int y = 0; y < 720; y++)
		{
			noiseData[noiseIndex] = noise.GetNoise((float)x, (float)y);
			noiseIndex++;
		}
	}
	
	skin->render(pixels, sv, noise);

	texture.update(pixels);
}

sf::Sprite& TextureRendering::getSprite()
{
	return sprite;
}

FastNoiseLite& TextureRendering::getNoise()
{
	return noise;
}

void TextureRendering::enableNoise(bool state)
{
	noiseEnabled = state;
}

void TextureRendering::set_sv_seed(int val)
{
	sv.set_seed(val);
}
