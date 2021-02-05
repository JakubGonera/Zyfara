#include "debug.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "Vendor/FastNoise/FastNoiseLite.h"

DebugUI::DebugUI(TextureRendering& _renderer) : renderer(_renderer)
{
}

void DebugUI::renderDebug(sf::RenderWindow& window)
{
	ImGui::SFML::Update(window, deltaClock.restart());

	//ImGui::Begin("My First Tool", &my_tool_active, ImGuiWindowFlags_MenuBar);
	ImGui::Begin("Noise options");
	
	ImGui::SliderFloat("frequency", &freq, 0.0f, 0.05f);
	ImGui::SliderInt("octaves", &octaves, 1, 10);
	ImGui::SliderFloat("lacunarity", &lacunarity, 0.0f, 5.f);
	ImGui::SliderFloat("gain", &gain, 0.0f, 1.f);
	ImGui::Checkbox("enable noise", &noiseEnabled);

	if (ImGui::Button("Render again")) {
		auto& noise = renderer.getNoise();
		noise.SetFrequency(freq);
		noise.SetFractalOctaves(octaves);
		noise.SetFractalLacunarity(lacunarity);
		noise.SetFractalGain(gain);
		renderer.enableNoise(noiseEnabled);
		renderer.render();
	}

	ImGui::End();
}
