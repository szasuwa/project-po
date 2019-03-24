#include <SFML/Graphics.hpp>
#include "GameEngine.h"

int main() {
	sf::RenderWindow appWindow(sf::VideoMode(1280, 720, 32), "Project PO");
	GameEngine engine(appWindow);
	engine.gameLoop();
	return 0;
}