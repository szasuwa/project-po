#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <regex>

#include "Interfaces/DynamicObject.h"


class Box : public DynamicObject {
protected:
	virtual sf::Vector2f onTrigger(const sf::Vector2f& p, GameObject* obj, const Collision& c, const sf::FloatRect& z, const sf::FloatRect& o);
public:
	Box(Map* map = nullptr);
	Box(const sf::Vector2f& position, Map* map = nullptr);
	Box(const sf::Vector2f& position, const sf::Color& color, Map* map = nullptr);
	Box(const sf::Vector2f& position, const sf::Vector2f& size, Map* map = nullptr);
	Box(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color, Map* map = nullptr);
	Box(const Box& obj);

	void onUpdate(MapInterface& f);
	void onFocus(MapInterface& f);
	sf::FloatRect getGlobalBounds() const;
	void resize(const sf::Vector2f& p, bool gridSnap = false, bool vLock = false, bool hLock = false);
	void setColor(const sf::Color& c);

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
		mass
		force.x
		force.y
		collider.left
		collider.right
		collider.top
		collider.bottom
		size.x
		size.y
		color
	*/
	virtual GameObjectClassType getClassType() const;
	virtual void serializeObject(std::ostream& ss) const;
	virtual void deserializeObject(std::istream& ss);
	static bool checkSerializableValidity(const std::string& s);
};