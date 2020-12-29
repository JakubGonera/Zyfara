#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include "voronoi.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
    sf::CircleShape shape(100.f);
	sf::Uint8        *pixels  = new sf::Uint8[1280 * 720 * 4];
    shape.setFillColor(sf::Color::Green);
	
	sf::Texture texture;
	texture.create(1280, 720); 
	
	
	sf::Sprite sprite(texture);
	slowvoronoi sv;
	std::vector<std::pair<int,int>> points= sv.randpoints(60,2137,1280,720);
	std::vector<float> dists = sv.slow(1280,720,5,points);
	
	for(int x=0;x<1280;x++)
	{
		for(int y=0;y<720;y++)
		{
			pixels[4*(y * 1280+x)]   = dists[y*1280+x]; // R?
			pixels[4*(y * 1280+x)+1] = dists[y*1280+x];  // G?
			pixels[4*(y * 1280+x)+2] = dists[y*1280+x];  // B?
			pixels[4*(y * 1280+x)+3] = 255; // A?
		}
	}
	
	texture.update(pixels);
	
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
		window.clear();
        window.draw(sprite);
        window.display();
		/*
        
        window.draw(shape);
        window.display();
		*/
	}

    return 0;
}