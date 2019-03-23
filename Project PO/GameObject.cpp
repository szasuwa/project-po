#include "GameObject.h"
#include "World.h"

GameObject::GameObject():fId(World::getNextGameObjectId())
{
}


GameObject::~GameObject()
{
	delete fDrawable;
}

sf::Drawable *GameObject::getDrawable() 
{
	return fDrawable;
}

int GameObject::getId()
{
	return fId;
}