#pragma once
#include"Serializable.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Level;

class GameObject : public Serializable
{
protected:
	Level* fLevel;
	sf::Drawable *fDrawable;

public:
	explicit GameObject(Level* lvl = nullptr);
	~GameObject();

	void setLevel(Level* lvl);

	void serializeData(std::stringstream &ss, bool last = true);
	void deserializeData(std::stringstream &ss);

	virtual void update() = 0;
	virtual sf::FloatRect getGlobalBounds() = 0;
	sf::Drawable *getDrawable();
	virtual sf::Transformable *getTransformable() = 0;
};

