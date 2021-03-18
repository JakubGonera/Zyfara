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

void TextureRendering::render(Skin* skin)
{
	std::vector<std::pair<int, int>> points = sv.randpoints(30, 2137, 1280, 720, 200);
	
	std::vector<float> dists = sv.randbordermulti(1280, 720, 10,70, points);

	int noiseIndex = 0;
	for (int x = 0; x < 1280; x++)
	{
		for (int y = 0; y < 720; y++)
		{
			noiseData[noiseIndex] = noise.GetNoise(1.0,1.0);//((float)x, (float)y);
			noiseIndex++;
		}
	}
	
	skin->render(pixels, dists, noiseData);

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
