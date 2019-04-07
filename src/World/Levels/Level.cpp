#include "Level.h"

Level::Level() {
	fLevelOrigin.x = 0;
	fLevelOrigin.y = 0;
}

Level::~Level() {
}

void Level::addGameObject(GameObject* obj) {
	fGameObjectList.push_back(obj);
}

void Level::destroyGameObject(GameObject* obj) {
	for (size_t i = 0; i < fGameObjectList.size(); ++i) {
		if (fGameObjectList[i] == obj) {
			fGameObjectList.erase(fGameObjectList.begin() + i);
			delete obj;
			return;
		}
	}
}

void Level::destroyAllGameObjects() {
	for (size_t i = 0; i < fGameObjectList.size(); ++i) {
		if (fGameObjectList[i] != nullptr) {
			delete fGameObjectList[i];
		}
	}
	fGameObjectList.clear();
}

const std::vector<GameObject *>& Level::getGameObjectList() const {
	return fGameObjectList;
}

void Level::setGrid(MapGrid* g) {
	fGrid = g;
}

void Level::setWorldBoundaries(float l, float r) {
	fWorldBoundaries.left = l;
	fWorldBoundaries.right = r;
}

void Level::scrollMap(float x) {
	fLevelOrigin.x = std::max(fWorldBoundaries.left, std::min(fLevelOrigin.x + x, fWorldBoundaries.right - Frame::getWindowWidth()));
	fGrid->setOrigin(fLevelOrigin);
	broadcastOriginChange(fLevelOrigin);
}

void Level::broadcastOriginChange(const sf::Vector2f &o) {
	for (int i = 0; i < fGameObjectList.size(); ++i) {
		if (fGameObjectList[i] != nullptr) {
			fGameObjectList[i]->getTransformable()->setOrigin(o);
		}
	}
}

void Level::broadcastDraw(sf::RenderWindow &w) {
	for (size_t i = 0; i < fGameObjectList.size(); ++i) {
		if (fGameObjectList[i] != nullptr) {
			w.draw(*fGameObjectList[i]->getDrawable());
		}
	}
}

void Level::broadcastUpdate() {
	for (size_t i = 0; i < fGameObjectList.size(); ++i) {
		if (fGameObjectList[i] != nullptr) {
			fGameObjectList[i]->update();
		}
	}
}
