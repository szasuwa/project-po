#include <SFML/Graphics.hpp>
#include "World/GameEngine.h"

int main() {
	sf::RenderWindow appWindow(sf::VideoMode(1024, 576, 32), "Project PO");
	GameEngine engine(appWindow);
	engine.gameLoop();
	return 0;
}