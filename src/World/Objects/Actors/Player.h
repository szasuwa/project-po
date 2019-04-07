#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>

#include "../Bases/PhysicalObject.h"
#include "../../Levels/WorldBoundaries.h"
#include "../../Levels/MapEditorItem.h"
#include "../../Frame.h"
#include "../../Menus/Gui.h"

class Player : public PhysicalObject
{
	//Movement
	float fSpeed = 250.f;
	float fJumpForce = 500.f;
	float fScrollOffsetRight = 400.f;
	float fScrollOffsetLeft = 400.f;

	static int fPoints;

	void controlMovement();
	void checkCollision(GameObject* obj);
	void updateGuiInfo();

public:
	Player(Level* lvl = nullptr);
	Player(sf::Vector2f position, Level* lvl = nullptr);
	~Player();

	void serializeData(std::stringstream &ss, bool last = true);
	void deserializeData(std::stringstream &ss);
	CLASS_TYPE getClassType();

	sf::FloatRect getGlobalBounds();
	sf::Transformable *getTransformable();
	static MapEditorItem *getGhostDrawable();
	void resize(sf::Vector2f rb, bool vLock, bool hLock);
	void update();	

	void addPoint(int p = 1);
	void subPoint(int p = 1);
	int getPoints();
	void setPoints(int p);
};

