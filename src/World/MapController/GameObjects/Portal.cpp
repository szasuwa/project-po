#include "Portal.h"
#include "../Maps/Map.h"


Portal::Portal(Map* map) : Portal(sf::Vector2f(), PORTAL_SIZE, PORTAL_COLOR, map)
{
}

Portal::Portal(const sf::Vector2f& position, Map* map) : Portal(position, PORTAL_SIZE, PORTAL_COLOR, map)
{
}

Portal::Portal(const sf::Vector2f& position, const sf::Color& color, Map* map) : Portal(position, PORTAL_SIZE, color, map)
{
}

Portal::Portal(const sf::Vector2f& position, const sf::Vector2f& size, Map* map) : Portal(position, size, PORTAL_COLOR, map)
{
}

Portal::Portal(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color, Map* map) : GameObject(map)
{
	fHasCollider = false;
	fHasTrigger = true;
	fDrawable = new sf::RectangleShape();
	fTransformable = (sf::RectangleShape*)fDrawable;
	fTransformable->setPosition(position);
	((sf::RectangleShape*)fDrawable)->setSize(size);
	((sf::RectangleShape*)fDrawable)->setFillColor(color);
}

Portal::Portal(const Portal& obj) : GameObject(obj)
{
	fDrawable = new sf::RectangleShape();
	fTransformable = (sf::RectangleShape*)fDrawable;
	fTransformable->setPosition(obj.fTransformable->getPosition());
	((sf::RectangleShape*)fDrawable)->setSize(((sf::RectangleShape*)obj.fDrawable)->getSize());
	((sf::RectangleShape*)fDrawable)->setFillColor(((sf::RectangleShape*)obj.fDrawable)->getFillColor());
	fLink = obj.fLink;
	fLinkId = obj.fLinkId;
}

Portal::~Portal()
{
	fTransformable = nullptr;
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
	if (fMap != nullptr && fLink == nullptr && fLinkId >= 0)
		setLink(fMap->getGameObject(fLinkId));
}

bool Portal::onTrigger(GameObject * o)
{
	if (fLink == nullptr)
		return false;

	if (fExitingObjects.size() > 0 && std::find(fExitingObjects.begin(), fExitingObjects.end(), o) != fExitingObjects.end())
		return false;

	(*fLink).fExitingObjects.push_back(o);
	o->setPosition(fLink->getPosition());

	return true;
}

sf::FloatRect Portal::getGlobalBounds() const
{
	return ((sf::Shape*)fDrawable)->getGlobalBounds();
}

void Portal::resize(const sf::Vector2f& p, bool gridSnap, bool vLock, bool hLock)
{
	sf::RectangleShape* shape = ((sf::RectangleShape*)fDrawable);
	sf::Vector2f position = fTransformable->getPosition();
	sf::Vector2f size = shape->getSize();

	if (!hLock)
		size.x = (gridSnap ? MapGrid::roundToGrid(p.x - position.x) : (p.x - position.x));

	if (!vLock)
		size.y = (gridSnap ? MapGrid::roundToGrid(p.y - position.y) : (p.y - position.y));

	shape->setSize(size);
}

void Portal::setColor(const sf::Color & c)
{
	((sf::RectangleShape*)fDrawable)->setFillColor(c);
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
	ss << ((sf::RectangleShape*)fDrawable)->getSize().x << SERIALIZABLE_FIELD_DELIMITER;
	ss << ((sf::RectangleShape*)fDrawable)->getSize().y << SERIALIZABLE_FIELD_DELIMITER;
	ss << ((sf::RectangleShape*)fDrawable)->getFillColor().toInteger() << SERIALIZABLE_FIELD_DELIMITER;
	ss << fLinkId << SERIALIZABLE_FIELD_DELIMITER;
}

void Portal::deserializeObject(std::istream & ss)
{
	GameObject::deserializeObject(ss);
	float x, y;
	ss >> x;
	ss >> y;
	sf::Uint32 c;
	ss >> c;
	((sf::RectangleShape*)fDrawable)->setSize(sf::Vector2f(x, y));
	((sf::RectangleShape*)fDrawable)->setFillColor(sf::Color(c));
	ss >> fLinkId;
}

bool Portal::checkSerializableValidity(const std::string & s)
{
	return std::regex_match(s, std::regex(
		REGEX_WHITESPACE
		+ F_REGEX_GAME_OBJECT_PATTERN
		+ REGEX_FLOAT_PATTERN + "{2}"
		+ REGEX_INT_PATTERN + "{2}"
		+ REGEX_WHITESPACE
	));
}