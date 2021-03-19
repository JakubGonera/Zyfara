#include "zachodnio.h"
#include "../Vendor/imgui/imgui.h"

Zachodnio::Zachodnio()
{
	name = "Zyrafa zachodnioafrykanska";
}

void Zachodnio::render(sf::Uint8* pixels, slowvoronoi& sv, float* noiseData)
{
	std::vector<std::pair<int, int>> points = sv.randpoints(30, 2137, 1280, 720, 200);
	std::vector<float>closestborder(1280*720);
	std::vector<float> dists = sv.randbordermulti(1280, 720, borderL, borderR, points,closestborder);
	int noiseIndex = 0;
	int primary[3] = {  primaryCol[0] * 255,  primaryCol[1] * 255,  primaryCol[2] * 255 };
	int secondary[3] = {  secondaryCol[0] * 255,  secondaryCol[1] * 255,  secondaryCol[2] * 255 };
	for (int x = 0; x < 1280; x++)
	{
		for (int y = 0; y < 720; y++)
		{
			dists[y * 1280 + x] += noiseData[noiseIndex] * 10;
			if (dists[y * 1280 + x] < closestborder[y * 1280 + x]) {
				pixels[4 * (y * 1280 + x)] = secondary[0];
				pixels[4 * (y * 1280 + x) + 1] = secondary[1];
				pixels[4 * (y * 1280 + x) + 2] = secondary[2];
			}
			else {
				pixels[4 * (y * 1280 + x)] = primary[0];
				pixels[4 * (y * 1280 + x) + 1] = primary[1];
				pixels[4 * (y * 1280 + x) + 2] = primary[2];
			}
			//pixels[4*(y * 1280+x)]   = dists[y*1280+x]; // R?
			//pixels[4*(y * 1280+x)+1] = dists[y*1280+x];  // G?
			//pixels[4*(y * 1280+x)+2] = dists[y*1280+x];  // B?
			pixels[4 * (y * 1280 + x) + 3] = 255; // A?
			noiseIndex++;
		}
	}
}

void Zachodnio::displayDebug(sf::RenderWindow& window)
{
	ImGui::ColorEdit3("Primary color", primaryCol);
	ImGui::ColorEdit3("Secondary color", secondaryCol);
	//ImGui::SliderFloat("Stripes width", &stripWidth, 0, 50, "%.3f");
	ImGui::SliderFloat("Border L", &borderL, 0, 100, "%.3f");
	ImGui::SliderFloat("Border R", &borderR, 0, 100, "%.3f");
}

const std::string& Zachodnio::getName()
{
	return name;
}

std::tuple<int, int, int> Zachodnio::getPrimaryCol()
{
	return {  primaryCol[0] * 255,  primaryCol[1] * 255,  primaryCol[2] * 255 };
}

std::tuple<int, int, int> Zachodnio::getSecondaryCol()
{
	return {  secondaryCol[0] * 255,  secondaryCol[1] * 255,  secondaryCol[2] * 255 };
}
