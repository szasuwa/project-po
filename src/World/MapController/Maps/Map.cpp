#include "Map.h"
#include <iostream>

Map::Map() 
{
	Frame & frame = Frame::getInstance();
	float w = Frame::getInstance().getFrameWidth(), h = Frame::getInstance().getFrameHeight();
	fCamera = sf::FloatRect(w/2, h/2, w, h);
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

	fCamera.top += height - fCamera.height;
	fCamera.height = height;

	fCamera.left += (width - fCamera.width)/2;
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
}

sf::FloatRect Map::getCamera() const
{
	return fCamera;
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
