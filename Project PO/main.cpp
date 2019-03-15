#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow appWindow(sf::VideoMode(1280, 720, 32), "Project PO");
	
	appWindow.clear();
	
	while (appWindow.isOpen())
	{
		sf::Event appEvent;
		while (appWindow.pollEvent(appEvent)) 
		{
			switch (appEvent.type)
			{
				case sf::Event::Closed:
					appWindow.close();
				default:
					break;
			}
		}
		appWindow.display();
	}
	return 0;
}