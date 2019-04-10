#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../../Serialization/Serializable.h"
#include "../../Map/Editor/MapGrid.h"


class Map;

class GameObject : public Serializable
{
protected:
	Map* fMap;
	sf::Drawable *fDrawable;

public:
	explicit GameObject(Map* map = nullptr);
	~GameObject();

	void setMap(Map* map);

	void serializeData(std::stringstream &ss, bool last = true);
	void deserializeData(std::stringstream &ss);

	virtual void update() = 0;
	virtual sf::FloatRect getGlobalBounds() = 0;
	sf::Drawable *getDrawable();
	virtual void resize(sf::Vector2f rb, bool vLock, bool hLock, bool snapToGrid) = 0;
	virtual sf::Transformable *getTransformable() = 0;
};

