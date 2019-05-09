#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <regex>

#include "Interfaces/DynamicObject.h"
#include "../../Frame/FrameMargin.h"
#include "../Maps/MapBoundaries.h"
#include "../../Interfaces/InputInterface.h"
#include "../../Interfaces/UIInterface.h"
#include "../../UIController/InterfaceType.h"
#include "../../InputController/KeyBindingIndex.h"


class Player : public DynamicObject
{
	//Movement
	float fSpeed = 250.f;
	float fJumpForce = 500.f;
	FrameMargin fScrollZone{ 0.3f,0.3f,0.3f,0.3f };
	int fScore = 0;
	bool fScoreChanged = false;

	void controlMovement(GameEngineInterface& f);
	virtual sf::Vector2f onTrigger(const sf::Vector2f& p, GameObject* obj, const Collision& c, const sf::FloatRect& z, const sf::FloatRect& o);
	void updateGui(GameEngineInterface& f);

public:
	Player(Map* map = nullptr);
	Player(const sf::Vector2f & position, Map * map = nullptr);
	Player(const sf::Vector2f & position, const sf::Vector2f & size, Map * map = nullptr);
	Player(const sf::Vector2f & position, const sf::Vector2f & size, const sf::Color & color, Map * map = nullptr);
	Player(const Player & obj);

	void onUpdate(GameEngineInterface& f);
	void onFocus(GameEngineInterface& f);
	sf::FloatRect getGlobalBounds() const;
	void resize(const sf::Vector2f & p, bool gridSnap = false, bool vLock = false, bool hLock = false);
	void setColor(const sf::Color & c);

	void addScore(int p = 1);
	void subScore(int p = 1);
	int getScore() const ;
	void setScore(int p);

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
		speed
		jump force
		scroll.left
		scroll.right
		scroll.top
		scroll.bottom
		score
	*/
	virtual GameObjectClassType getClassType() const;
	virtual void serializeObject(std::ostream & ss) const;
	virtual void deserializeObject(std::istream & ss);	
	static bool checkSerializableValidity(const std::string& s);
};

