#include "Map.h"
#include <iostream>

Map::Map() 
{
	Frame & frame = Frame::getInstance();
	float w = Frame::getInstance().getFrameWidth(), h = Frame::getInstance().getFrameHeight();
	fCamera = sf::FloatRect(w/2, h/2, w, h);
}

Map::Map(const Map & o)
{
	this->clone(o);
}

Map::~Map() 
{
	destroyAllGameObjects();
}

void Map::addGameObject(GameObject* obj) 
{
	if (obj != nullptr)
	{
		obj->setMap(this);
		fGameObjectList.push_back(obj);
	}
}

void Map::addGameObjects(const std::vector<GameObject *> & list) 
{
	for (GameObject* ptr : list) 
	{
		addGameObject(ptr);
	}
}

void Map::destroyGameObject(GameObject* obj) {
	for (size_t i = 0; i < fGameObjectList.size(); ++i) 
	{
		if (fGameObjectList[i] == obj) 
		{
			fGameObjectList.erase(fGameObjectList.begin() + i);
			delete obj;
			return;
		}
	}
}

void Map::destroyAllGameObjects()
{
	for (size_t i = 0; i < fGameObjectList.size(); ++i) 
	{
		if (fGameObjectList[i] != nullptr) 
		{
			delete fGameObjectList[i];
		}
	}
	fGameObjectList.clear();
}

const std::vector<GameObject *>& Map::getGameObjects() const 
{
	return fGameObjectList;
}

MapBoundaries Map::getBoundaries() const
{
	return fMapBoundaries;
}

void Map::updateCamera()
{
	Frame & f = Frame::getInstance();

	float width = f.getFrameWidth();
	float height = f.getFrameHeight();

	fCamera.top += fCamera.height - height;
	fCamera.height = height;
	fCamera.width = width;

	if (fMapBoundaries.hasRight)
		fCamera.left = std::min(fMapBoundaries.right - fCamera.width, fCamera.left);

	if (fMapBoundaries.hasLeft)
		fCamera.left = std::max(fMapBoundaries.left, fCamera.left);

	if (fMapBoundaries.hasTop)
		fCamera.top = std::max(fMapBoundaries.top, fCamera.top);

	if (fMapBoundaries.hasBottom)
		fCamera.top = std::min(fMapBoundaries.bottom - fCamera.height, fCamera.top);

	Frame::getInstance().updateView(sf::View(fCamera), Frame::FrameLayer::MapArea);
	moveCamera(sf::Vector2f((fCamera.width - width) / 2, 0));
}

sf::FloatRect Map::getCamera() const
{
	return fCamera;
}

void Map::setCamera(const sf::FloatRect & camera)
{
	fCamera.top = camera.top;
	fCamera.left = camera.left;
	fCamera.height = camera.height;
	fCamera.width = camera.width;

	updateCamera();
}

void Map::moveCamera(const sf::Vector2f & p) 
{
	sf::Vector2f p2 = p;

	fCamera.left += p.x;
	fCamera.top += p.y;

	if (fMapBoundaries.hasRight)
		fCamera.left = std::min(fMapBoundaries.right - fCamera.width, fCamera.left);

	if (fMapBoundaries.hasLeft)
		fCamera.left = std::max(fMapBoundaries.left, fCamera.left);

	if (fMapBoundaries.hasTop)
		fCamera.top = std::max(fMapBoundaries.top, fCamera.top);

	if (fMapBoundaries.hasBottom)
		fCamera.top = std::min(fMapBoundaries.bottom - fCamera.height, fCamera.top);

	Frame::getInstance().updateView(sf::View(fCamera), Frame::FrameLayer::MapArea);
}

void Map::broadcastFocus() 
{
	updateCamera();
	for (size_t i = 0; i < fGameObjectList.size(); ++i)
	{
		if (fGameObjectList[i] != nullptr)
		{
			fGameObjectList[i]->onFocus();
		}
	}
}

void Map::broadcastUpdate() 
{
	for (size_t i = 0; i < fGameObjectList.size(); ++i) 
	{
		if (fGameObjectList[i] != nullptr) 
		{
			fGameObjectList[i]->update();
		}
	}
}

void Map::broadcastDraw() const 
{
	for (size_t i = 0; i < fGameObjectList.size(); ++i) 
	{
		if (fGameObjectList[i] != nullptr) 
		{
			fGameObjectList[i]->draw();
		}
	}
}

void Map::clone(const Map & o) 
{
	if (this == &o)
		return;

	fCamera = o.fCamera;
	fMapBoundaries = o.fMapBoundaries;
	fDecelerationRate = o.fDecelerationRate;
	fDecelerationSmoothRate = o.fDecelerationSmoothRate;
	fGravityRate = o.fGravityRate;
	fMaxGravityForce = o.fMaxGravityForce;

	destroyAllGameObjects();

	for (GameObject* obj : o.fGameObjectList)
	{
		if (obj == nullptr)
			continue;

		switch (obj->getClassType())
		{
		case GameObjectClassType::PLAYER:
			fGameObjectList.push_back(new Player(*(Player*)obj));
			break;
		case GameObjectClassType::PLATFORM:
			fGameObjectList.push_back(new Platform(*(Platform*)obj));
			break;
		case GameObjectClassType::POINT:
			fGameObjectList.push_back(new Point(*(Point*)obj));
			break;
		default:
			break;
		}

		fGameObjectList.back()->setMap(this);
	}
}

Map & Map::operator=(const Map & o)
{
	if (this == &o)
		return *this;

	this->clone(o);
	
	return *this;
}
