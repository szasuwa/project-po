#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <regex>

#include "Interfaces/GameObject.h"


class Platform : public GameObject
{
public:
	explicit Platform(Map * map = nullptr);
	Platform(const sf::Vector2f & position, Map * map = nullptr);
	Platform(const sf::Vector2f& position, const sf::Color& color, Map* map = nullptr);
	Platform(const sf::Vector2f & position, const sf::Vector2f & size, Map * map = nullptr);
	Platform(const sf::Vector2f & position, const sf::Vector2f & size, const sf::Color & color, Map * map = nullptr);
	Platform(const Platform & obj);

	void onUpdate();
	void onFocus();
	sf::FloatRect getGlobalBounds() const;
	void resize(const sf::Vector2f & p, bool gridSnap = false, bool vLock = false, bool hLock = false);
	void setColor(const sf::Color & c);

	/*
		<<Data format>>
		Properties separated using SERIALIZABLE_FIELD_DELIMITER.

		<<Data order>>
		class type
		id
		position.x
		position.y
		has hollider
		has trigger
		size.x
		size.y
		color
	*/
	virtual GameObjectClassType getClassType() const;
	virtual void serializeObject(std::ostream & ss) const;
	virtual void deserializeObject(std::istream & ss);
	static bool checkSerializableValidity(const std::string& s);
};

