#include "GameEngine.h"
#include "World.h"

sf::Vector2u GameEngine::F_WINDOW_SIZE;
sf::Clock GameEngine::fClk;
double GameEngine::fLastFrameTime = 0;
const double GameEngine::F_MAX_FRAME_TIME = 1.0 / 120.0;

sf::Font font;

GameEngine::GameEngine(sf::RenderWindow &window) : fGameWindow(window)
{
	font.loadFromFile("res/bboron.ttf");
	F_WINDOW_SIZE = fGameWindow.getSize();

	fFpsMeter.setFont(font);
	fFpsMeter.setCharacterSize(12);
	fFpsMeter.setFillColor(sf::Color::White);

	fWorld = new World();
}

GameEngine::~GameEngine()
{
	delete fWorld;
}

void GameEngine::initGame() 
{
	fGameWindow.setFramerateLimit(120);
	fWorld->loadLevel(1);
}

void GameEngine::gameLoop()
{
	if (fGameWindow.isOpen()) {
		initGame();
	}
	
	while (fGameWindow.isOpen())
	{
		handleEvents();
		if (fGameWindow.hasFocus()) {
			updateFrame();
		}
		else
		{
			Sleep(F_MAX_FRAME_TIME * 1000);
		}
		fLastFrameTime = fClk.restart().asSeconds();
	}
}

float GameEngine::getFrameTime() {
	return std::min(fLastFrameTime, F_MAX_FRAME_TIME);
}

void GameEngine::updateFrame() 
{
	fGameWindow.clear();
	for (GameObject* object : World::getGameObjectList())
	{
		if (object == nullptr)
			continue;
		
		object->update();
		fGameWindow.draw(*(*object).getDrawable());
	}

	updateStats();
	displayStats();

	fGameWindow.display();
}

void GameEngine::handleEvents() {
	sf::Event appEvent;
	while (fGameWindow.pollEvent(appEvent))
	{
		switch (appEvent.type)
		{
			case sf::Event::KeyPressed:
				if (!fIsFpsKeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F3)) {
					fIsFpsKeyPressed = true;
					fDisplayFps = !fDisplayFps;
				}
				break;

			case sf::Event::KeyReleased:
				if (fIsFpsKeyPressed && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F3)) {
					fIsFpsKeyPressed = false;
				}
				break;

			case sf::Event::GainedFocus:
				fLastFrameTime = F_MAX_FRAME_TIME;
				fClk.restart();
				break;	

			case sf::Event::Resized:
				fLastFrameTime = F_MAX_FRAME_TIME;
				fClk.restart();
				break;

			case sf::Event::Closed:
				fGameWindow.close();
				break;

			default:
				break;
		}
	}
}

void GameEngine::updateStats() {
	fFpsMeter.setString(std::to_string((int)(1.f / getFrameTime())) + "FPS");
}

void GameEngine::displayStats() {
	if (fDisplayFps)
		fGameWindow.draw(fFpsMeter);
}

 const sf::Vector2u GameEngine::getWindowSize() {
	return F_WINDOW_SIZE;
}
