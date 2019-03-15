#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include "GameEngineConstants.h"

class GameObject
{
protected:
	sf::Drawable *fDrawable;
	const int fId;
public:
	GameObject();
	~GameObject();

	virtual void update() {};
	sf::Drawable *getDrawable();
	int getId();

};

