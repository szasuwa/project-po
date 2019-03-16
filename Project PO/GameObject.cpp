#include "GameObject.h"
#include "GameEngine.h"

GameObject::GameObject():fId(GameEngine::getNextGameObjectId())
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