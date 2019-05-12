#include "ExitPortal.h"
#include "../Maps/Map.h"

ExitPortal::ExitPortal(Map* map) : ExitPortal(sf::Vector2f(), EXIT_PORTAL_RADIUS, EXIT_PORTAL_COLOR, map)
{
}

ExitPortal::ExitPortal(const sf::Vector2f& position, Map* map) : ExitPortal(sf::Vector2f(), EXIT_PORTAL_RADIUS, EXIT_PORTAL_COLOR, map)
{
}

ExitPortal::ExitPortal(const sf::Vector2f& position, const float& radius, Map* map) : ExitPortal(position, radius, EXIT_PORTAL_COLOR, map)
{
}

ExitPortal::ExitPortal(const sf::Vector2f& position, const sf::Color& color, Map* map) : ExitPortal(position, EXIT_PORTAL_RADIUS, EXIT_PORTAL_COLOR, map)
{
}

ExitPortal::ExitPortal(const sf::Vector2f& position, const float& radius, const sf::Color& color, Map* map) : GameObject(map)
{
	fHasCollider = false;
	fHasTrigger = true;
	fDrawable = new sf::CircleShape();
	fTransformable = (sf::CircleShape*)fDrawable;
	fTransformable->setPosition(position);
	((sf::CircleShape*)fDrawable)->setRadius(radius);
	((sf::CircleShape*)fDrawable)->setPointCount(EXIT_PORTAL_POINT_COUNT);
	((sf::CircleShape*)fDrawable)->setFillColor(color);
}

ExitPortal::ExitPortal(const ExitPortal& obj) : GameObject(obj)
{
	fDrawable = new sf::CircleShape();
	fTransformable = (sf::CircleShape*)fDrawable;
	fTransformable->setPosition(obj.fTransformable->getPosition());
	((sf::CircleShape*)fDrawable)->setRadius(((sf::CircleShape*)obj.fDrawable)->getRadius());
	((sf::CircleShape*)fDrawable)->setPointCount(((sf::CircleShape*)obj.fDrawable)->getPointCount());
	((sf::CircleShape*)fDrawable)->setFillColor(((sf::CircleShape*)obj.fDrawable)->getFillColor());
}

void ExitPortal::onUpdate(GameEngineInterface& f)
{
	if (fTriggered)
	{
		fTriggered = false;
		UIInterface& ui = f.getUIInterface();

		if (!ui.isViewVisible((unsigned int)InterfaceType::Gui))
			return;

		ui.broadcastVisibilityChange(false);
		ui.addUIView((unsigned int)InterfaceType::EndGame);
		ui.setProperty((unsigned int)InterfaceType::EndGame, 0, fPoints);
		ui.setProperty((unsigned int)InterfaceType::EndGame, 1, fTime);
		ui.setViewVisibility((unsigned int)InterfaceType::EndGame, true);
		f.getMapInterface().unloadMap();
	}
}

void ExitPortal::onFocus(GameEngineInterface& f)
{
}

bool ExitPortal::onTrigger(GameObject * o)
{
	if (o == this || o == nullptr)
		return false;

	if (o->getClassType() == GameObjectClassType::PLAYER)
	{
		fPoints = std::to_string(((Player*)o)->getScore());
		fTime = fMap->getElapsedTime();
		fTriggered = true;
		return true;
	}

	return true;
}

sf::FloatRect ExitPortal::getGlobalBounds() const
{
	return ((sf::Shape*)fDrawable)->getGlobalBounds();
}

void ExitPortal::resize(const sf::Vector2f& p, bool gridSnap, bool vLock, bool hLock)
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

void ExitPortal::setColor(const sf::Color & c)
{
	((sf::Shape*)fDrawable)->setFillColor(c);
}

GameObjectClassType ExitPortal::getClassType() const
{
	return GameObjectClassType::EXIT_PORTAL;
}

void ExitPortal::serializeObject(std::ostream & ss) const
{
	ss << (int)(getClassType()) << SERIALIZABLE_FIELD_DELIMITER;
	GameObject::serializeObject(ss);
	ss << ((sf::CircleShape*)fDrawable)->getRadius() << SERIALIZABLE_FIELD_DELIMITER;
	ss << ((sf::CircleShape*)fDrawable)->getPointCount() << SERIALIZABLE_FIELD_DELIMITER;
	ss << ((sf::CircleShape*)fDrawable)->getFillColor().toInteger() << SERIALIZABLE_FIELD_DELIMITER;
}

void ExitPortal::deserializeObject(std::istream & ss)
{
	GameObject::deserializeObject(ss);
	float r;
	sf::Uint32 c;
	int p;
	if(!(ss >> r >> p >> c))
		return;

	((sf::CircleShape*)fDrawable)->setRadius(r);
	((sf::CircleShape*)fDrawable)->setPointCount(p);
	((sf::CircleShape*)fDrawable)->setFillColor(sf::Color(c));
}

bool ExitPortal::checkSerializableValidity(const std::string & s)
{
	return std::regex_match(s, std::regex(
		REGEX_WHITESPACE
		+ F_REGEX_GAME_OBJECT_PATTERN
		+ REGEX_FLOAT_PATTERN + "{1}"
		+ REGEX_INT_PATTERN + "{2}"
		+ REGEX_WHITESPACE
	));
}