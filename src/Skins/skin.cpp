#include "skin.h"
#include "../Vendor/imgui/imgui.h"

void Skin::setNoise(FastNoiseLite& noise)
{
    noise.SetFrequency(freq);
    noise.SetFractalOctaves(octaves);
    noise.SetFractalLacunarity(lacunarity);
    noise.SetFractalGain(gain);
    noise.SetFractalWeightedStrength(weightedStrength);
}

void Skin::render(sf::Uint8* pixels, slowvoronoi& sv, FastNoiseLite& noise)
{
	std::vector<std::pair<int, int>> points;
	if (poisson)
		points = sv.poisson(1280, 720, poissonRadius);
	else
		points = sv.randpoints(30, 2137, 1280, 720, 200);
	std::vector<float>closestborder(1280 * 720);
	//distance for each pixel from closest edge
	std::vector<float> dists = sv.randbordermulti(1280, 720, borderL, borderR, points, closestborder);

	int primary[3] = { primaryCol[0] * 255,  primaryCol[1] * 255,  primaryCol[2] * 255 };
	int secondary[3] = { secondaryCol[0] * 255,  secondaryCol[1] * 255,  secondaryCol[2] * 255 };
	int shade[3] = { shadeCol[0] * 255,  shadeCol[1] * 255,  shadeCol[2] * 255 };
	for (int x = 0; x < 1280; x++)
	{
		for (int y = 0; y < 720; y++)
		{
			//Check whether pixel should be coloured as a gap or as a patch
			if (closestborder[y * 1280 + x] + noise.GetNoise((float)x * noiseZoom, (float)y * noiseZoom) * noiseScaleFactor <= 0)
			{
				pixels[4 * (y * 1280 + x)] = secondary[0];
				pixels[4 * (y * 1280 + x) + 1] = secondary[1];
				pixels[4 * (y * 1280 + x) + 2] = secondary[2];
			}
			else {
				if (!shaded) {
					pixels[4 * (y * 1280 + x)] = primary[0];
					pixels[4 * (y * 1280 + x) + 1] = primary[1];
					pixels[4 * (y * 1280 + x) + 2] = primary[2];
				}
				else {
					//If chosen shaded, interpolate colour based on simple sigmoid function
					float constant = 1/100.f;
					float ratio = closestborder[y * 1280 + x] * constant / (1 + abs(closestborder[y * 1280 + x] * constant));
					ratio = std::min(1.f, ratio);
					pixels[4 * (y * 1280 + x)] = (shade[0] - primary[0]) * ratio + primary[0];
					pixels[4 * (y * 1280 + x) + 1] = (-primary[1] + shade[1]) * ratio + primary[1];
					pixels[4 * (y * 1280 + x) + 2] = (-primary[2] + shade[2]) * ratio + primary[2];
				}
			}
			pixels[4 * (y * 1280 + x) + 3] = 255;
		}
	}
	if (shaded) {
		//Compute gaussian blur
		for (int x = 0; x < 1280; x++)
		{
			for (int y = 0; y < 720; y++)
			{
				if (!(closestborder[y * 1280 + x] + noise.GetNoise((float)x * noiseZoom, (float)y * noiseZoom) * noiseScaleFactor <= 0)) {
					int sum[3] = { 0,0,0 };
					int count = 0;
					int kernel[3][3] = { {1,2,1}, {2,4,2}, {1,2,1} };
					for (int i = -1; i < 1; i++)
					{
						for (int j = -1; j < 1; j++)
						{
							if (x + i >= 0 && x + i < 1280 && y + j >= 0 && y + j < 720) {
								if (!(closestborder[(y + j) * 1280 + x + i] + noise.GetNoise((float)(x + i) * noiseZoom, (float)(y + j) * noiseZoom) * noiseScaleFactor <= 0)) {
									count += kernel[i + 1][j + 1];
									sum[0] += pixels[4 * ((y + j) * 1280 + (x + i))] * kernel[i + 1][j + 1];
									sum[1] += pixels[4 * ((y + j) * 1280 + (x + i)) + 1] * kernel[i + 1][j + 1];
									sum[2] += pixels[4 * ((y + j) * 1280 + (x + i)) + 2] * kernel[i + 1][j + 1];
								}
							}
						}
					}
					for (int& col : sum)
					{
						col /= count;
					}
					pixels[4 * (y * 1280 + x)] = sum[0];
					pixels[4 * (y * 1280 + x) + 1] = sum[1];
					pixels[4 * (y * 1280 + x) + 2] = sum[2];
				}
			}
		}
	}
}

void Skin::displayDebug(sf::RenderWindow& window)
{
	ImGui::Text("Noise settings");

	ImGui::SliderFloat("frequency", &freq, 0.0f, 0.05f);
	ImGui::SliderInt("octaves", &octaves, 1, 10);
	ImGui::SliderFloat("lacunarity", &lacunarity, 0.0f, 5.f);
	ImGui::SliderFloat("gain", &gain, 0.0f, 3.f);
	ImGui::SliderFloat("weighted strength", &weightedStrength, -2.0f, 3.f);

	ImGui::Text("\n");

	ImGui::ColorEdit3("Primary color", primaryCol);
	ImGui::ColorEdit3("Secondary color", secondaryCol);
	ImGui::Checkbox("Poisson disk sampling", &poisson);
	if (poisson) {
		ImGui::SliderInt("Poisson radius", &poissonRadius, 10, 1000);
	}
	ImGui::Checkbox("Shaded", &shaded);
	if (shaded) {
		ImGui::ColorEdit3("Shaded color", shadeCol);
	}
	ImGui::SliderFloat("Border L", &borderL, 0, 100, "%.3f");
	ImGui::SliderFloat("Border R", &borderR, 0, 100, "%.3f");
	ImGui::SliderFloat("Noise scale factor", &noiseScaleFactor, 0, 100, "%.3f");
	ImGui::SliderFloat("Noise zoom", &noiseZoom, 0, 3, "%.3f");
}

const std::string& Skin::getName()
{
	return name;
}
