#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <regex>

#include "Interfaces/GameObject.h"


class Portal : public GameObject
{
	int fLinkId = -1;
	Portal * fLink = nullptr;
	std::vector<GameObject*> fExitingObjects = std::vector<GameObject*>();

public:
	explicit Portal(Map* map = nullptr);
	Portal(const sf::Vector2f & position, Map * map = nullptr);
	Portal(const sf::Vector2f & position, const sf::Color & color, Map * map = nullptr);
	Portal(const sf::Vector2f & position, const sf::Vector2f & size, Map * map = nullptr);
	Portal(const sf::Vector2f & position, const sf::Vector2f & size, const sf::Color & color, Map * map = nullptr);
	Portal(const Portal & obj);
	~Portal();

	void onUpdate();
	void onFocus();
	bool onTrigger(GameObject * o);
	sf::FloatRect getGlobalBounds() const;
	void resize(const sf::Vector2f& p, bool gridSnap = false, bool vLock = false, bool hLock = false);
	void setColor(const sf::Color& c);

	void setLink(const GameObject * o);

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
		link
	*/
	virtual GameObjectClassType getClassType() const;
	virtual void serializeObject(std::ostream& ss) const;
	virtual void deserializeObject(std::istream& ss);
	static bool checkSerializableValidity(const std::string& s);
};

