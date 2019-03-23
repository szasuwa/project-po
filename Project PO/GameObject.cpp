#include "GameObject.h"
#include "World.h"

GameObject::GameObject():fId(World::getNextGameObjectId())
{
}


GameObject::~GameObject()
{
	delete fDrawable;
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

int GameObject::getId()
{
	return fId;
}