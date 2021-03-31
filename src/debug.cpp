#include "debug.h"
#include "Vendor/imgui/imgui.h"
#include "Vendor/imgui/imgui.cpp"
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
	for (int i = 0; i < (int)skins.size(); i++)
	{
		names.push_back(skins[i]->getName());
	}
}

void DebugUI::renderDebug(sf::RenderWindow& window)
{
	ImGui::SFML::Update(window, deltaClock.restart());
	ImGui::Begin("Options");
	ImGui::InputInt("seed", &seed);
	//ImGui::Checkbox("enable noise", &noiseEnabled);
	
	static int currentSkin = 0;
	ImGui::ListBox("Pattern", &currentSkin, names);

	ImGui::Separator();
	
	if (ImGui::CollapsingHeader("Properties"))
	{
		ImGui::Text("Noise settings");

		ImGui::SliderFloat("frequency", skins[currentSkin]->getFreq(), 0.0f, 0.05f);
		ImGui::SliderInt("octaves", skins[currentSkin]->getOctaves(), 1, 10);
		ImGui::SliderFloat("lacunarity", skins[currentSkin]->getLacunarity(), 0.0f, 5.f);
		ImGui::SliderFloat("gain", skins[currentSkin]->getGain(), 0.0f, 3.f);
		ImGui::SliderFloat("weighted strength", skins[currentSkin]->getStrength(), -2.0f, 3.f);

		ImGui::Text("\n");

		skins[currentSkin]->displayDebug(window);
	}
	if (ImGui::Button("Render again")) {
		seed = std::rand() % 100000;
		renderer.set_sv_seed(seed);
		skins[currentSkin]->setNoise(renderer.getNoise());
		//renderer.enableNoise(noiseEnabled);
		renderer.render(skins[currentSkin]);
	}

	ImGui::End();
}
