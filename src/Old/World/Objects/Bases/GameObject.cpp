#include "GameObject.h"
#include "../../Map/Bases/Map.h"

GameObject::GameObject(Map* map) : fMap(map)
{
}

GameObject::GameObject(const sf::Vector2f &position, Map* map) : fMap(map)
{
}


GameObject::GameObject(const GameObject &obj) {
	fDrawable = createDrawable();
	fMap = obj.fMap;
}

GameObject::~GameObject()
{
	delete fDrawable;
}

void GameObject::setMap(Map* map) {
	fMap = map;
}

void GameObject::serializeData(std::stringstream &ss, bool last) {
	sf::Transformable *t = getTransformable();
	ss << t->getPosition().x << SERIALIZABLE_FIELD_DELIMITER;
	ss << t->getPosition().y;
	Serializable::serializeData(ss, last);
}

void GameObject::deserializeData(std::stringstream &ss) {
	sf::Transformable *t = getTransformable();
	float x, y;
	ss >> x;
	ss >> y;
	t->setPosition(x,y);
}

sf::Drawable *GameObject::getDrawable() 
{
	return fDrawable;
}

