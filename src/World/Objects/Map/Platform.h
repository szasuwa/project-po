#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

#include "../Bases/GameObject.h"
#include "../../Levels/MapEditorItem.h"


class Platform : public GameObject
{
public:
	Platform(Level* lvl = nullptr);
	Platform(sf::Vector2f position, Level* lvl = nullptr);
	Platform(sf::Vector2f size, sf::Vector2f position, Level* lvl = nullptr);
	Platform(sf::Vector2f size, sf::Vector2f position, sf::Color color, Level* lvl = nullptr);
	~Platform();

	void deserializeData(std::stringstream &ss);
	void serializeData(std::stringstream &ss, bool last);
	CLASS_TYPE getClassType();

	sf::FloatRect getGlobalBounds();
	static MapEditorItem *getGhostDrawable();
	void resize(sf::Vector2f rb, bool vLock, bool hLock);
	sf::Transformable *getTransformable();

	void update();

	void handleCollision(GameObject * collider);

	sf::Vector2f getSize();
	void setSize(sf::Vector2f &size);

	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f &position);

	void setColor(sf::Color color);
};

