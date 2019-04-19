#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <typeinfo>

#include "GameObjectClassType.h"
#include "../../../Frame/Frame.h"
#include "../../../../GameConstants.h"
#include "../../Maps/MapGrid.h"

class Map;

class GameObject
{
protected:
	static const std::string F_REGEX_GAME_OBJECT_PATTERN;
	Map * fMap = nullptr;
	sf::Drawable * fDrawable = nullptr;
	sf::Transformable * fTransformable = nullptr;
	bool fHasCollider = true;
	bool fHasTrigger = false;
	int fId = -1;

public:
	explicit GameObject(Map * map = nullptr);
	GameObject(const GameObject & o);
	virtual ~GameObject();

	virtual void onUpdate() = 0;
	virtual void onFocus() = 0;
	virtual bool onCollision(GameObject* obj);
	virtual bool onTrigger(GameObject* obj);

	void draw() const;

	int getId() const;
	void setId(const int & id);
	void setMap(Map * map);
	virtual sf::FloatRect getGlobalBounds() const = 0;
	bool hasCollider() const;
	bool hasTrigger() const;
	sf::Vector2f getPosition() const;
	void setPosition(const sf::Vector2f & p, bool gridSnap = false, bool vLock = false, bool hLock = false);
	sf::Vector2f getCenter() const;
	virtual void move(const sf::Vector2f & p);
	virtual void resize(const sf::Vector2f & p, bool gridSnap = false, bool vLock = false, bool hLock = false) = 0;
	virtual void setColor(const sf::Color & c) = 0;

	virtual const std::type_info & getParrentType() const;
	virtual GameObjectClassType getClassType() const = 0;
	virtual void serializeObject(std::ostream & ss) const;
	virtual void deserializeObject(std::istream & ss);	
};

std::ostream & operator<<(std::ostream &s, const GameObject & o);
std::istream & operator>>(std::istream &s, GameObject & o);

