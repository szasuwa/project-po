#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>
#include <algorithm>


class Frame
{
	static const float F_MAX_FRAME_TIME;

	static sf::Vector2u fWindowSize;

	static sf::Clock fClk;
	static float fLastFrameTime;
	static int fFrameRate;


public:
	Frame();
	explicit Frame(sf::Vector2u size);
	~Frame();

	static void nextFrame();
	static float getMaxFrameTime();
	static float getFrameTime();
	static int getFrameRate();
	static void setWindowSize(sf::Vector2u size);
	static int getWindowWidth();
	static int getWindowHeight();
};

