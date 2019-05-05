#include <SFML/Graphics.hpp>
#include "World/GameEngine.h"
#include "World/Frame/Frame.h"
#include "World/InputController/InputController.h"
#include "World/MapController/MapController.h"
#include "World/UIController/UIController.h"

int main() {
	sf::RenderWindow appWindow(sf::VideoMode(1024, 576, 32), "Project PO");
	Frame frame(appWindow);
	InputController input;
	MapController map(frame, input);
	UIController ui(frame, input, map);
	GameEngine engine(frame, input, map, ui);
	engine.gameLoop();
	return 0;
}