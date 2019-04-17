#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include <regex>

#include "Interfaces/GameObject.h"


class Point : public GameObject {
public:
    explicit Point(Map * map = nullptr);
    Point(const sf::Vector2f & position, Map * map = nullptr);
	Point(const sf::Vector2f & position, const float & radius, Map * map = nullptr);
    Point(const sf::Vector2f & position, const sf::Color & color, Map * map = nullptr);
	Point(const sf::Vector2f & position, const float & radius, const sf::Color & color, Map * map = nullptr);
	Point(const Point & obj);
    ~Point();

	void onUpdate();
	void onFocus();
	bool onTrigger(GameObject * o);
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
		radius
		color
	*/
	virtual GameObjectClassType getClassType() const;
	virtual void serializeObject(std::ostream & ss) const;
	virtual void deserializeObject(std::istream & ss);
	static bool checkSerializableValidity(const std::string& s);
};