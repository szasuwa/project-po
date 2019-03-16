#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
class GameEngine;

class GameObject
{
protected:
	sf::Drawable *fDrawable;
	const int fId;
public:
	GameObject();
	~GameObject();

	virtual void update() = 0;
	virtual sf::FloatRect getGlobalBounds() = 0;
	sf::Drawable *getDrawable();
	virtual sf::Transformable *getTransformable() = 0;
	int getId();

};

