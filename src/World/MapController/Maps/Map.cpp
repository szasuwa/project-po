#include "Map.h"


Map::Map(MapInterface& m) : fMapInterface(m), fFrame(fMapInterface.getFrame())
{
	float w = fFrame.getFrameWidth(), h = fFrame.getFrameHeight();
	fCamera = sf::FloatRect(w/2, h/2, w, h);
}

Map::Map(const Map & o) : fMapInterface(o.fMapInterface), fFrame(o.fFrame)
{
	this->clone(o);
}

Map::~Map() 
{
	destroyAllGameObjects();
}

void Map::addGameObject(GameObject* obj, const bool & keepId)
{
	if (obj != nullptr)
	{
		obj->setMap(this);
		fGameObjectList.push_back(obj);
		if(!keepId)
			fGameObjectList.back()->setId(calculateGameObjectId());
	}
}

void Map::addGameObject(GameObject* obj)
{
	addGameObject(obj, false);
}

void Map::addGameObjects(const std::vector<GameObject *> & list)
{
	for (GameObject* ptr : list) 
	{
		addGameObject(ptr, false);
	}
}

void Map::destroyGameObject(GameObject* obj) {
	for (size_t i = 0; i < fGameObjectList.size(); ++i) 
	{
		if (fGameObjectList[i] == obj) 
		{
			delete obj;
			fGameObjectList.erase(fGameObjectList.begin() + i);
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
			fGameObjectList[i] = nullptr;
		}
	}
	fGameObjectList.clear();
}

const GameObject* Map::getGameObject(const int& id) const {
	for (GameObject* ptr : fGameObjectList)
	{
		if (ptr != nullptr && ptr->getId() == id)
			return ptr;
	}

	return nullptr;
}

const std::vector<GameObject *>& Map::getGameObjects() const 
{
	return fGameObjectList;
}

void Map::updateLastId()
{
	for (GameObject* ptr : fGameObjectList)
	{
		if (ptr != nullptr && ptr->getId() > fLastId)
			fLastId = ptr->getId();
	}
}

int Map::calculateGameObjectId()
{
	return ++fLastId;
}


MapBoundaries Map::getBoundaries() const
{
	return fMapBoundaries;
}

void Map::updateCamera()
{
	float width = fFrame.getFrameWidth();
	float height = fFrame.getFrameHeight();

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

	fFrame.updateView(sf::View(fCamera), FrameInterface::FrameLayer::GameArea);
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

	fFrame.updateView(sf::View(fCamera), FrameInterface::FrameLayer::GameArea);
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
			fGameObjectList[i]->onUpdate();
		}
	}
}

void Map::broadcastDraw() const 
{
	for (size_t i = 0; i < fGameObjectList.size(); ++i) 
	{
		if (fGameObjectList[i] != nullptr && fCamera.intersects(fGameObjectList[i]->getGlobalBounds()))
		{
			fGameObjectList[i]->draw();
		}
	}
}

void Map::clone(const Map & o) 
{
	if (this == &o || &o == nullptr)
		return;

	fLastId = o.fLastId;
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
			case GameObjectClassType::PORTAL:
				fGameObjectList.push_back(new Portal(*(Portal*)obj));
				break;
			case GameObjectClassType::BOX:
				fGameObjectList.push_back(new Box(*(Box*)obj));
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

void Map::serializeObject(std::ostream& ss) const {
	ss << fMapBoundaries.hasLeft << SERIALIZABLE_FIELD_DELIMITER
		<< fMapBoundaries.hasRight << SERIALIZABLE_FIELD_DELIMITER
		<< fMapBoundaries.hasTop << SERIALIZABLE_FIELD_DELIMITER
		<< fMapBoundaries.hasBottom << SERIALIZABLE_FIELD_DELIMITER
		<< fMapBoundaries.left << SERIALIZABLE_FIELD_DELIMITER
		<< fMapBoundaries.right << SERIALIZABLE_FIELD_DELIMITER
		<< fMapBoundaries.top << SERIALIZABLE_FIELD_DELIMITER
		<< fMapBoundaries.bottom << SERIALIZABLE_FIELD_DELIMITER
		<< fDecelerationRate << SERIALIZABLE_FIELD_DELIMITER
		<< fDecelerationSmoothRate << SERIALIZABLE_FIELD_DELIMITER
		<< fGravityRate << SERIALIZABLE_FIELD_DELIMITER
		<< fMaxGravityForce << SERIALIZABLE_FIELD_DELIMITER
		<< fCamera.left << SERIALIZABLE_FIELD_DELIMITER
		<< fCamera.top << SERIALIZABLE_FIELD_DELIMITER
		<< fCamera.width << SERIALIZABLE_FIELD_DELIMITER
		<< fCamera.height << SERIALIZABLE_FIELD_DELIMITER;

	for (GameObject* obj : fGameObjectList)
	{
		if (obj != nullptr)
			ss << SERIALIZABLE_OBJECT_DELIMITER << *obj;
	}
}

void Map::deserializeObject(std::istream& ss) {
	ss >> fMapBoundaries.hasLeft >> 
		fMapBoundaries.hasRight >> 
		fMapBoundaries.hasTop >> 
		fMapBoundaries.hasBottom >>
		fMapBoundaries.left >>
		fMapBoundaries.right >> 
		fMapBoundaries.top >> 
		fMapBoundaries.bottom >>
		fDecelerationRate >> 
		fDecelerationSmoothRate >> 
		fGravityRate >> 
		fMaxGravityForce >>
		fCamera.left >> 
		fCamera.top >> 
		fCamera.width >> 
		fCamera.height;

	if (!ss)
		return;

	destroyAllGameObjects();

	while (ss.rdbuf()->in_avail() > 0) {
		ss.ignore(255, SERIALIZABLE_OBJECT_DELIMITER);

		int type;
		ss >> type;

		GameObject* obj = nullptr;		

		switch ((GameObjectClassType)type)
		{
		case GameObjectClassType::PLAYER:
			obj = new Player(fMapInterface);
			break;

		case GameObjectClassType::PLATFORM:
			obj = new Platform(fMapInterface);
			break;

		case GameObjectClassType::POINT:
			obj = new Point(fMapInterface);
			break;

		case GameObjectClassType::PORTAL:
			obj = new Portal(fMapInterface);
			break;

		case GameObjectClassType::BOX:
			obj = new Box(fMapInterface);
			break;

		default:
			continue;
		}

		ss >> *obj;

		if (ss)
			addGameObject(obj, true);
		else
		{
			delete obj;
			break;
		}
	}
	updateLastId();
}

bool Map::checkSerializableValidity(const std::string& s)
{
	return std::regex_match(s, std::regex(
		REGEX_WHITESPACE 
		+ REGEX_BOOL_PATTERN + "{4}" 
		+ REGEX_FLOAT_PATTERN + "{12}"
		+ REGEX_WHITESPACE
	));
}

std::ostream& operator<<(std::ostream& s, const Map& o)
{
	o.serializeObject(s);
	return s;
}

std::istream& operator>>(std::istream& s, Map& o)
{
	o.deserializeObject(s);
	return s;
}