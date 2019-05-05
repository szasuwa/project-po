#pragma once
#include <algorithm>

#include "../Interfaces/FrameInterface.h"


class Frame : public FrameInterface
{
protected:
	sf::RenderWindow& fWindow;

	const float F_MAX_FRAME_TIME = 0.025f;

	sf::Clock fClk;
	float fLastFrameTime;
	int fFrameRate;

	FrameLayer fActiveView;
	sf::View fViewLayers[(int)(FrameLayer::num_values)];

public:
	Frame(sf::RenderWindow& w);

	virtual bool isOpen() const;
	virtual bool hasFocus() const;
	virtual void clear();
	virtual void display();
	virtual bool pollEvent(sf::Event& e);
	virtual void close();

	virtual void updateView(const sf::View& v, const FrameLayer& layer);
	virtual bool selectView(const FrameLayer& layer);

	virtual void draw(const sf::Drawable& o, const FrameLayer& layer);

	virtual void nextFrame();

	virtual sf::Vector2f getMousePosition(const FrameLayer& layer);

	virtual float getMaxFrameTime() const;
	virtual float getFrameTime() const;
	virtual int getFrameRate() const;

	virtual int getFrameWidth() const;
	virtual int getFrameHeight() const;
};

