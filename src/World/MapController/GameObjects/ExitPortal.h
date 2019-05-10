#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include <regex>

#include "Interfaces/GameObject.h"
#include "../../Interfaces/UIInterface.h"
#include "../../UIController/InterfaceType.h"
#include "../../Interfaces/GameEngineInterface.h"
#include "../../Interfaces/MapInterface.h"


class ExitPortal : public GameObject
{
protected:
	bool fTriggered = false;

public:
	ExitPortal(Map* map = nullptr);
	ExitPortal(const sf::Vector2f& position, Map* map = nullptr);
	ExitPortal(const sf::Vector2f& position, const float& radius, Map* map = nullptr);
	ExitPortal(const sf::Vector2f& position, const sf::Color& color, Map* map = nullptr);
	ExitPortal(const sf::Vector2f& position, const float& radius, const sf::Color& color, Map* map = nullptr);
	ExitPortal(const ExitPortal& obj);

	void onUpdate(GameEngineInterface& f);
	void onFocus(GameEngineInterface& f);
	bool onTrigger(GameObject * o);
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

