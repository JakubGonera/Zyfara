#include "debug.h"
#include "imgui.h"
#include "imgui-SFML.h"

void DebugUI::renderDebug(sf::RenderWindow& window)
{
	ImGui::SFML::Update(window, deltaClock.restart());

	//ImGui::Begin("My First Tool", &my_tool_active, ImGuiWindowFlags_MenuBar);
	ImGui::Begin("Sample window");

	if (ImGui::ColorEdit3("Background color", color))
	{

	}

	ImGui::InputText("Window title", windowTitle, 500);

	ImGui::End();
}
