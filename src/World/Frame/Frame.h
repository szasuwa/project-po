#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>
#include <algorithm>


class Frame
{
public:
	enum class FrameLayer {
		MapArea,
		Interface,
		num_values
	};

private:
	static Frame * instance;
	const float F_MAX_FRAME_TIME = 1.0/120.0;

	sf::RenderWindow * fWindow = nullptr;
	sf::Clock fClk;
	float fLastFrameTime;
	int fFrameRate;

	FrameLayer fActiveView;
	sf::View fViewLayers[(int)(FrameLayer::num_values)];

	Frame();
	Frame(const Frame &o);

public:
	static Frame & getInstance();

	void nextFrame();
	void updateView(const sf::View & v, const FrameLayer & layer);
	void draw(const sf::Drawable & o, const FrameLayer & layer);

	sf::Vector2f getMousePosition(const FrameLayer & layer);
	void setWindow(sf::RenderWindow & w);
	float getMaxFrameTime() const;
	float getFrameTime() const;
	int getFrameRate() const;
	int getFrameWidth() const;
	int getFrameHeight() const;
};

