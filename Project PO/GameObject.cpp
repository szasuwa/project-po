#include "GameObject.h"

GameObject::GameObject():fId(GameEngineConstants::getNextGameObjectId())
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