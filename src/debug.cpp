#include "debug.h"
#include "Vendor/imgui/imgui.h"
#include "Vendor/imgui/imgui-SFML.h"
#include "Vendor/FastNoise/FastNoiseLite.h"

//wrapper for vector usage in some ImGui widgets
namespace ImGui
{
	static auto vector_getter = [](void* vec, int idx, const char** out_text)
	{
		auto& vector = *static_cast<std::vector<std::string>*>(vec);
		if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
		*out_text = vector.at(idx).c_str();
		return true;
	};

	bool Combo(const char* label, int* currIndex, std::vector<std::string>& values)
	{
		if (values.empty()) { return false; }
		return Combo(label, currIndex, vector_getter,
			static_cast<void*>(&values), values.size());
	}

	bool ListBox(const char* label, int* currIndex, std::vector<std::string>& values)
	{
		if (values.empty()) { return false; }
		return ListBox(label, currIndex, vector_getter,
			static_cast<void*>(&values), values.size());
	}

}

DebugUI::DebugUI(TextureRendering& _renderer, std::vector<Skin*> _skins) : renderer(_renderer), skins(_skins)
{
	currentSkin = skins[0];
	for (int i = 0; i < skins.size(); i++)
	{
		names.push_back(skins[i]->getName());
	}
}

void DebugUI::renderDebug(sf::RenderWindow& window)
{
	ImGui::SFML::Update(window, deltaClock.restart());

	ImGui::Begin("Noise options");
	
	ImGui::SliderFloat("frequency", &freq, 0.0f, 0.05f);
	ImGui::SliderInt("octaves", &octaves, 1, 10);
	ImGui::SliderFloat("lacunarity", &lacunarity, 0.0f, 5.f);
	ImGui::SliderFloat("gain", &gain, 0.0f, 1.f);
	//ImGui::Checkbox("enable noise", &noiseEnabled);
	
	static int currentSkin = 0;
	ImGui::ListBox("Pattern", &currentSkin, names);

	skins[currentSkin]->displayDebug(window);

	if (ImGui::Button("Render again")) {
		auto& noise = renderer.getNoise();
		noise.SetFrequency(freq);
		noise.SetFractalOctaves(octaves);
		noise.SetFractalLacunarity(lacunarity);
		noise.SetFractalGain(gain);
		//renderer.enableNoise(noiseEnabled);
		renderer.render(skins[currentSkin]);
	}

	ImGui::End();
}
