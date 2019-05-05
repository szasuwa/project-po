#include <SFML/Graphics.hpp>
#include "World/GameEngine.h"
#include "World/Frame/Frame.h"
#include "World/InputController/InputController.h"
#include "World/MapController/MapController.h"

int main() {
	sf::RenderWindow appWindow(sf::VideoMode(1024, 576, 32), "Project PO");
	Frame frame(appWindow);
	InputController input;
	MapController map(frame, input);
	GameEngine engine(frame, input, map);
	engine.gameLoop();
	return 0;
}