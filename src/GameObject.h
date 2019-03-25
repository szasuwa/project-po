#pragma once
#include"Serializable.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

class GameObject : public Serializable
{
protected:
	sf::Drawable *fDrawable;
	const int fId;
public:
	GameObject();
	~GameObject();

	void serializeData(std::stringstream &ss, bool last = true);
	void deserializeData(std::stringstream &ss);

	virtual void update() = 0;
	virtual sf::FloatRect getGlobalBounds() = 0;
	sf::Drawable *getDrawable();
	virtual sf::Transformable *getTransformable() = 0;
	int getId();

};

