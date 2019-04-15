#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "GameObjectClassType.h"
#include "../../../Frame/Frame.h"
#include "../../../../GameConstants.h"
#include "../../Maps/MapGrid.h"

class Map;

class GameObject
{
protected:
	Map * fMap = nullptr;
	sf::Drawable * fDrawable = nullptr;
	sf::Transformable * fTransformable = nullptr;
	bool fHasCollider = true;
	bool fHasTrigger = false;

public:
	explicit GameObject(Map * map = nullptr);
	GameObject(const GameObject & o);
	virtual ~GameObject();

	virtual void update() = 0;
	virtual void onFocus() = 0;
	void draw() const;

	void setMap(Map * map);
	virtual sf::FloatRect getGlobalBounds() const = 0;
	bool hasCollider() const;
	bool hasTrigger() const;
	sf::Vector2f getPosition() const;
	void setPosition(const sf::Vector2f & p, bool gridSnap = false, bool vLock = false, bool hLock = false);
	virtual void move(const sf::Vector2f & p, bool gridSnap = false, bool vLock = false, bool hLock = false);
	virtual void resize(const sf::Vector2f & p, bool gridSnap = false, bool vLock = false, bool hLock = false) = 0;
	virtual void setColor(const sf::Color & c) = 0;

	virtual GameObjectClassType getClassType() const = 0;
	virtual void serializeObject(std::ostream & ss) const;
	virtual void deserializeObject(std::istream & ss);	
};

std::ostream & operator<<(std::ostream &s, const GameObject & o);
std::istream & operator>>(std::istream &s, GameObject & o);

