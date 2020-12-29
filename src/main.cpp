#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include "voronoi.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 200), "SFML works!");
    sf::CircleShape shape(100.f);
	sf::Uint8        *pixels  = new sf::Uint8[400 * 200 * 4];
    shape.setFillColor(sf::Color::Green);
	
	sf::Texture texture;
	texture.create(400, 200); 
	
	
	sf::Sprite sprite(texture);
	slowvoronoi sv;
	std::vector<std::pair<int,int>> points= sv.randpoints(20,2137,400,200);
	std::vector<float> dists = sv.slow(400,200,5,points);
	
	for(int x=0;x<400;x++)
	{
		for(int y=0;y<200;y++)
		{
			pixels[4*(y * 400+x)]   = dists[y*400+x]; // R?
			pixels[4*(y * 400+x)+1] = dists[y*400+x];  // G?
			pixels[4*(y * 400+x)+2] = dists[y*400+x];  // B?
			pixels[4*(y * 400+x)+3] = 255; // A?
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

        window.draw(sprite);
        window.display();
		/*
        window.clear();
        window.draw(shape);
        window.display();
		*/
	}

    return 0;
}