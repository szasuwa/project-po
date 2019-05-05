#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


class FrameInterface
{
public:
	enum class FrameLayer {
		GameArea,
		Interface,
		num_values
	};

	virtual bool isOpen() const = 0;
	virtual bool hasFocus() const = 0;
	virtual void clear() = 0;
	virtual void display() = 0;
	virtual bool pollEvent(sf::Event& e) = 0;
	virtual void close() = 0;

	virtual void updateView(const sf::View & v, const FrameLayer & layer) = 0;
	virtual bool selectView(const FrameLayer& layer) = 0;

	virtual void draw(const sf::Drawable & o, const FrameLayer & layer) = 0;

	virtual void nextFrame() = 0;

	virtual sf::Vector2f getMousePosition(const FrameLayer & layer) = 0;

	virtual float getMaxFrameTime() const = 0;
	virtual float getFrameTime() const = 0;
	virtual int getFrameRate() const = 0;

	virtual int getFrameWidth() const = 0;
	virtual int getFrameHeight() const = 0;
};