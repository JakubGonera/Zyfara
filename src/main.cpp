#include <vector>
#include <utility>

#include "Vendor/FastNoise/FastNoiseLite.h"

#include "Vendor/imgui/imgui.h"
#include "Vendor/imgui/imgui-SFML.h"

#include <SFML/Graphics.hpp>

#include "voronoi.hpp"
#include "debug.h"
#include "textureRendering.h"

#define WIDTH 1280
#define HEIGHT 720

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
	ImGui::SFML::Init(window);

	TextureRendering textureRendering(WIDTH, HEIGHT);
	DebugUI debugUI(textureRendering);

    textureRendering.render();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
			ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed)
                window.close();
        }

		debugUI.renderDebug(window);

		window.clear();
        window.draw(textureRendering.getSprite());
		ImGui::SFML::Render(window);
        window.display();
	}
	ImGui::SFML::Shutdown();

    return 0;
}