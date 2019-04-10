#include "Map.h"
#include <iostream>

Map::Map() {
	fMapOrigin.x = 0;
	fMapOrigin.y = 0;
}

Map::~Map() {
}

void Map::addGameObject(GameObject* obj) {
	if (obj != nullptr) {
		obj->setMap(this);
		fGameObjectList.push_back(obj);
	}
}

void Map::addGameObjects(const std::vector<GameObject *> & list) {
	for (GameObject* ptr : list) {
		addGameObject(ptr);
	}
}

void Map::destroyGameObject(GameObject* obj) {
	for (size_t i = 0; i < fGameObjectList.size(); ++i) {
		if (fGameObjectList[i] == obj) {
			fGameObjectList.erase(fGameObjectList.begin() + i);
			delete obj;
			return;
		}
	}
}

void Map::destroyAllGameObjects() {
	for (size_t i = 0; i < fGameObjectList.size(); ++i) {
		if (fGameObjectList[i] != nullptr) {
			delete fGameObjectList[i];
		}
	}
	fGameObjectList.clear();
}

const std::vector<GameObject *>& Map::getGameObjectList() const {
	return fGameObjectList;
}

void Map::setGrid(MapGrid* g) {
	fGrid = g;
}

void Map::setMapBoundaries(float l, float r) {
	fWorldBoundaries.left = l;
	fWorldBoundaries.right = r;
}

void Map::scrollMap(float x) {
	fMapOrigin.x = std::max(fWorldBoundaries.left, std::min(fMapOrigin.x + x, fWorldBoundaries.right - Frame::getWindowWidth()));
	fGrid->setOrigin(fMapOrigin);
	broadcastOriginChange(fMapOrigin);
}

void Map::broadcastOriginChange(const sf::Vector2f &o) {
	for (size_t i = 0; i < fGameObjectList.size(); ++i) {
		if (fGameObjectList[i] != nullptr) {
			fGameObjectList[i]->getTransformable()->setOrigin(o);
		}
	}
	for (GameObject* ptr : fGameObjectList) {
		
	}
}

void Map::broadcastDraw(sf::RenderWindow &w) {
	for (size_t i = 0; i < fGameObjectList.size(); ++i) {
		if (fGameObjectList[i] != nullptr) {
			w.draw(*fGameObjectList[i]->getDrawable());
		}
	}

}

void Map::broadcastUpdate() {
	for (size_t i = 0; i < fGameObjectList.size(); ++i) {
		if (fGameObjectList[i] != nullptr) {
			fGameObjectList[i]->update();
		}
	}
}
