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

void TextureRendering::render()
{
	std::vector<std::pair<int, int>> points = sv.randpoints(30, 2137, 1280, 720, 200);
	std::vector<float> dists = sv.multi(1280, 720, 5, points);

	int noiseIndex = 0;
	for (int x = 0; x < 1280; x++)
	{
		for (int y = 0; y < 720; y++)
		{
			noiseData[noiseIndex] = noise.GetNoise((float)x, (float)y);
			if(noiseEnabled)
				dists[y * 1280 + x] += noiseData[noiseIndex] * 10;
			if (dists[y * 1280 + x] < 17) {
				pixels[4 * (y * 1280 + x)] = 227;
				pixels[4 * (y * 1280 + x) + 1] = 223;
				pixels[4 * (y * 1280 + x) + 2] = 212;
			}
			else {
				pixels[4 * (y * 1280 + x)] = 128;
				pixels[4 * (y * 1280 + x) + 1] = 79;
				pixels[4 * (y * 1280 + x) + 2] = 54;
			}
			//pixels[4*(y * 1280+x)]   = dists[y*1280+x]; // R?
			//pixels[4*(y * 1280+x)+1] = dists[y*1280+x];  // G?
			//pixels[4*(y * 1280+x)+2] = dists[y*1280+x];  // B?
			pixels[4 * (y * 1280 + x) + 3] = 255; // A?
			noiseIndex++;
		}
	}

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
