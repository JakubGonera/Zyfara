#include <vector>
#include <utility>

#include "Vendor/FastNoise/FastNoiseLite.h"

#include "Vendor/imgui/imgui.h"
#include "Vendor/imgui/imgui-SFML.h"

#include <SFML/Graphics.hpp>

#include "voronoi.hpp"
#include "debug.h"
#include "textureRendering.h"
#include "Skins/siatkowa.h"
#include "Skins/zachodnio.h"
#include "Skins/numbijska.h"
#include "Skins/kordofanska.h"
#include "Skins/angolska.h"
#include "Skins/skin.h"

#define WIDTH 1280
#define HEIGHT 720

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
	ImGui::SFML::Init(window);
    window.setFramerateLimit(60);

    std::vector<Skin*> skins;

    Siatkowa* siatkowa = new Siatkowa();
    skins.push_back(static_cast<Skin*>(siatkowa));
    Zachodnio* zachodnio = new Zachodnio();
    skins.push_back(static_cast<Skin*>(zachodnio));
    Numbijska* numbijska = new Numbijska();
    skins.push_back(static_cast<Skin*>(numbijska));
    Kordofanska* kordofanska = new Kordofanska();
    skins.push_back(static_cast<Skin*>(kordofanska));
    Angolska* angolska = new Angolska();
    skins.push_back(static_cast<Skin*>(angolska));

	TextureRendering textureRendering(WIDTH, HEIGHT);
	DebugUI debugUI(textureRendering, skins);

    textureRendering.render(skins[0]);

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