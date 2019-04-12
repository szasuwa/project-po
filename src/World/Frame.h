#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>
#include <algorithm>


class Frame
{
	const float F_MAX_FRAME_TIME = 1.0/120.0;

	sf::RenderWindow * fWindow;
	sf::Clock fClk;
	float fLastFrameTime;
	int fFrameRate;

	Frame();
	Frame(const Frame &o);

public:
	static Frame & getInstance();

	void nextFrame();
	void updateCamera(const sf::View & v);
	void draw(const sf::Drawable & o);

	void setWindow(sf::RenderWindow & w);
	float getMaxFrameTime() const;
	float getFrameTime() const;
	int getFrameRate() const;
	int getFrameWidth() const;
	int getFrameHeight() const;
};

