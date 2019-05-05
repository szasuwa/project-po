#include "Portal.h"
#include "../Maps/Map.h"


Portal::Portal(MapInterface& f, Map* map) : Portal(f, sf::Vector2f(), PORTAL_RADIUS, PORTAL_COLOR, map)
{
}

Portal::Portal(MapInterface& f, const sf::Vector2f& position, Map* map) : Portal(f, sf::Vector2f(), PORTAL_RADIUS, PORTAL_COLOR, map)
{
}

Portal::Portal(MapInterface& f, const sf::Vector2f& position, const float& radius, Map* map) : Portal(f, position, radius, PORTAL_COLOR, map)
{
}

Portal::Portal(MapInterface& f, const sf::Vector2f& position, const sf::Color& color, Map* map) : Portal(f, position, PORTAL_RADIUS, PORTAL_COLOR, map)
{
}

Portal::Portal(MapInterface& f, const sf::Vector2f& position, const float& radius, const sf::Color& color, Map* map) : GameObject(f, map)
{
	fHasCollider = false;
	fHasTrigger = true;
	fDrawable = new sf::CircleShape();
	fTransformable = (sf::CircleShape*)fDrawable;
	fTransformable->setPosition(position);
	((sf::CircleShape*)fDrawable)->setRadius(radius);
	((sf::CircleShape*)fDrawable)->setPointCount(PORTAL_POINT_COUNT);
	((sf::CircleShape*)fDrawable)->setFillColor(color);
}

Portal::Portal(const Portal& obj) : GameObject(obj)
{
	fDrawable = new sf::CircleShape();
	fTransformable = (sf::CircleShape*)fDrawable;
	fTransformable->setPosition(obj.fTransformable->getPosition());
	((sf::CircleShape*)fDrawable)->setRadius(((sf::CircleShape*)obj.fDrawable)->getRadius());
	((sf::CircleShape*)fDrawable)->setPointCount(((sf::CircleShape*)obj.fDrawable)->getPointCount());
	((sf::CircleShape*)fDrawable)->setFillColor(((sf::CircleShape*)obj.fDrawable)->getFillColor());
	fLinkId = obj.fLinkId;
}

Portal::~Portal()
{
	if(fMap == nullptr)
		return;
	
	for (GameObject* o : fMap->getGameObjects())
	{
		if (o != this && o != nullptr && o->getClassType() == GameObjectClassType::PORTAL && ((Portal*)o)->fLink == this)
			((Portal*)o)->setLink(nullptr);
	}
}

void Portal::onUpdate()
{
	for (int i = 0; i < fExitingObjects.size(); ++i) 
	{
		if (fExitingObjects[i] == nullptr || !getGlobalBounds().intersects(fExitingObjects[i]->getGlobalBounds()))
		{
			fExitingObjects.erase(fExitingObjects.begin() + i);
			--i;
		}
	}
}

void Portal::onFocus()
{
	if (fMap != nullptr && ((fLink == nullptr && fLinkId >= 0) || (fLink != nullptr && fLinkId != fLink->fId)))
		setLink(fMap->getGameObject(fLinkId));
}

bool Portal::onTrigger(GameObject * o)
{
	if (fLink == nullptr)
		return false;

	if (fExitingObjects.size() > 0 && std::find(fExitingObjects.begin(), fExitingObjects.end(), o) != fExitingObjects.end())
		return false;

	(*fLink).fExitingObjects.push_back(o);
	o->setCenter(fLink->getCenter());

	return true;
}

sf::FloatRect Portal::getGlobalBounds() const
{
	return ((sf::Shape*)fDrawable)->getGlobalBounds();
}

void Portal::resize(const sf::Vector2f& p, bool gridSnap, bool vLock, bool hLock)
{
	sf::CircleShape* shape = (sf::CircleShape*)fDrawable;
	sf::Vector2f pos = fTransformable->getPosition();
	float radius = shape->getRadius();
	pos.x -= radius / 2;
	pos.y += radius / 2;

	if (hLock)
	{
		radius = p.y - pos.y;
		radius = (gridSnap ? std::abs(MapGrid::roundToGrid(p.y) - MapGrid::roundToGrid(pos.y)) : std::abs(p.y - pos.y));
	}
	else if (vLock)
	{
		radius = (gridSnap ? std::abs(MapGrid::roundToGrid(p.x) - MapGrid::roundToGrid(pos.x)) : std::abs(p.x - pos.x));
	}
	else
	{
		radius = std::max((gridSnap ? MapGrid::roundToGrid(p.y) - MapGrid::roundToGrid(pos.y) : p.y - pos.y),
			(gridSnap ? MapGrid::roundToGrid(p.x) - MapGrid::roundToGrid(pos.x) : p.x - pos.x));
	}

	shape->setRadius(radius);
}

void Portal::setColor(const sf::Color & c)
{
	((sf::Shape*)fDrawable)->setFillColor(c);
}

GameObject* Portal::getLink()
{
	return fLink;
}

void Portal::setLink(const GameObject* o)
{
	if (o == nullptr)
	{
		fLink = nullptr;
		fLinkId = -1;
		return;
	}

	if (o->getClassType() != GameObjectClassType::PORTAL)
		return;

	fLink = (Portal *)o;
	fLinkId = o->getId();
}

GameObjectClassType Portal::getClassType() const
{
	return GameObjectClassType::PORTAL;
}

void Portal::serializeObject(std::ostream & ss) const
{
	ss << (int)(getClassType()) << SERIALIZABLE_FIELD_DELIMITER;
	GameObject::serializeObject(ss);
	ss << ((sf::CircleShape*)fDrawable)->getRadius() << SERIALIZABLE_FIELD_DELIMITER;
	ss << ((sf::CircleShape*)fDrawable)->getPointCount() << SERIALIZABLE_FIELD_DELIMITER;
	ss << ((sf::CircleShape*)fDrawable)->getFillColor().toInteger() << SERIALIZABLE_FIELD_DELIMITER;
	ss << fLinkId << SERIALIZABLE_FIELD_DELIMITER;
}

void Portal::deserializeObject(std::istream & ss)
{
	GameObject::deserializeObject(ss);
	float r;
	sf::Uint32 c;
	int p, l;
	if(!(ss >> r >> p >> c >> l))
		return;

	((sf::CircleShape*)fDrawable)->setRadius(r);
	((sf::CircleShape*)fDrawable)->setPointCount(p);
	((sf::CircleShape*)fDrawable)->setFillColor(sf::Color(c));
	fLinkId = l;
}

bool Portal::checkSerializableValidity(const std::string & s)
{
	return std::regex_match(s, std::regex(
		REGEX_WHITESPACE
		+ F_REGEX_GAME_OBJECT_PATTERN
		+ REGEX_FLOAT_PATTERN + "{1}"
		+ REGEX_INT_PATTERN + "{3}"
		+ REGEX_WHITESPACE
	));
}