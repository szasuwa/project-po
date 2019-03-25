#include "GameObject.h"

int GameObject::fNextGameObjectId;
std::vector<GameObject*> GameObject::fGameObjectList;

GameObject::GameObject():fId(fNextGameObjectId)
{
	++fNextGameObjectId;
	fGameObjectList.push_back(this);
}


GameObject::~GameObject()
{
	for (int i = 0; i < fGameObjectList.size(); ++i) {
		if (fGameObjectList[i] == this) {
			fGameObjectList.erase(fGameObjectList.begin()+i);
		}
	}
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

void GameObject::broadcastOriginChange(sf::Vector2f &o) {
	for (int i = 0; i < fGameObjectList.size(); ++i) {
		if (fGameObjectList[i] != nullptr) {
			fGameObjectList[i]->getTransformable()->setOrigin(o);
		}
	}
}

void GameObject::broadcastDraw(sf::RenderWindow &w) {
	for (int i = 0; i < fGameObjectList.size(); ++i) {
		if (fGameObjectList[i] != nullptr) {
			w.draw(*fGameObjectList[i]->getDrawable());
		}
	}
}

void GameObject::broadcastUpdate() {
	for (int i = 0; i < fGameObjectList.size(); ++i) {
		if (fGameObjectList[i] != nullptr) {
			fGameObjectList[i]->update();
		}
	}
}

void GameObject::destroyAll() {
	for (int i = 0; i < fGameObjectList.size(); ++i) {
		if (fGameObjectList[i] != nullptr) {
			delete fGameObjectList[i];
		}
	}
	fGameObjectList.clear();
	fNextGameObjectId = 0;
}