#include "Player.h"
#include "../Maps/Map.h"


Player::Player(Map* map) : Player(sf::Vector2f(), PLAYER_SIZE, PLAYER_COLOR, map)
{
}

Player::Player(const sf::Vector2f & position, Map * map) : Player(position, PLAYER_SIZE, PLAYER_COLOR, map)
{
}

Player::Player(const sf::Vector2f & position, const sf::Vector2f & size, Map * map) : Player(position, size, PLAYER_COLOR, map)
{
}

Player::Player(const sf::Vector2f & position, const sf::Vector2f & size, const sf::Color & color, Map * map) : DynamicObject(position, true, true, map)
{
	fDrawable = new sf::RectangleShape();
	fTransformable = (sf::RectangleShape*)fDrawable;
	fTransformable->setPosition(position);
	((sf::RectangleShape*)fDrawable)->setSize(size);
	((sf::RectangleShape*)fDrawable)->setFillColor(color);
}

Player::Player(const Player & obj) : DynamicObject(obj)
{
	fDrawable = new sf::RectangleShape();
	fTransformable = (sf::RectangleShape*)fDrawable;
	fTransformable->setPosition(obj.fTransformable->getPosition());
	((sf::RectangleShape*)fDrawable)->setSize(((sf::RectangleShape*)obj.fDrawable)->getSize());
	((sf::RectangleShape*)fDrawable)->setFillColor(((sf::RectangleShape*)obj.fDrawable)->getFillColor());
	fSpeed = obj.fSpeed;
	fJumpForce = obj.fJumpForce;
	fScrollZone = obj.fScrollZone;
	fScore = obj.fScore;
}

void Player::controlMovement(GameEngineInterface& f)
{
	InputInterface & input = f.getInputInterface();
	//Check movement keys
	if (input.isKeyPressed((unsigned int)KeyBindingIndex::MoveLeft))
	{
		fForceVector.x -= fSpeed;
	}
	if (input.isKeyPressed((unsigned int)KeyBindingIndex::MoveRight))
	{
		fForceVector.x += fSpeed;
	}
	fForceVector.x = std::max(-fSpeed, std::min(fSpeed, fForceVector.x));

	if (input.isKeyPressed((unsigned int)KeyBindingIndex::Jump) && fCollider.getBottom())
	{
		fForceVector.y = -fJumpForce;
	}

	//Scrolling
	if (fMap == nullptr)
		return;

	MapBoundaries mbound = fMap->getBoundaries();
	float dTime = f.getFrameInterface().getFrameTime();

	sf::Vector2f cameraMove;
	sf::FloatRect camera = fMap->getCamera();

	FrameMargin fZone = fScrollZone;
	fZone.left *= camera.width;
	fZone.right *= camera.width;
	fZone.top *= camera.height;
	fZone.bottom *= camera.height;


	sf::FloatRect bounds = getGlobalBounds();	

	if (bounds.left + bounds.width + fForceVector.x*dTime > camera.left + camera.width - fZone.right)
	{
		
		cameraMove.x = bounds.left + bounds.width + fForceVector.x*dTime - camera.left - camera.width + fZone.right;
	}

	if (bounds.left + fForceVector.x*dTime < fZone.left + camera.left) 
	{
		cameraMove.x = bounds.left + fForceVector.x*dTime - fZone.left - camera.left;
	}

	
	if (bounds.top + bounds.height + fForceVector.y*dTime > camera.top + camera.height - fZone.bottom) {
		cameraMove.y = bounds.top + bounds.height + fForceVector.y*dTime - camera.top - camera.height + fZone.bottom;
	}

	if (bounds.top + fForceVector.y*dTime < fZone.top + camera.top) {
		cameraMove.y = bounds.top + fForceVector.y*dTime - fZone.top - camera.top;
	}

	fMap->moveCamera(f, cameraMove);
}

sf::Vector2f Player::onTrigger(const sf::Vector2f& p, GameObject* obj, const Collision& c, const sf::FloatRect& z, const sf::FloatRect& o)
{
	if (obj == this || obj == nullptr)
		return p;

	if (obj->getClassType() == GameObjectClassType::POINT) {
		addScore();
		fScoreChanged = true;
	}

	return p;
}

void Player::updateGui(GameEngineInterface& f) 
{
	f.getUIInterface().setProperty((unsigned int)InterfaceType::Gui, 0, std::to_string(fScore));
}

void Player::onUpdate(GameEngineInterface& f)
{
	controlMovement(f);
	DynamicObject::onUpdate(f);

	if (fScoreChanged)
	{
		fScoreChanged = false;
		updateGui(f);
	}
}

void Player::onFocus(GameEngineInterface& f)
{
	updateGui(f);
}

sf::FloatRect Player::getGlobalBounds() const
{
	return ((sf::Shape*)fDrawable)->getGlobalBounds();
}

void Player::resize(const sf::Vector2f & p, bool gridSnap, bool vLock, bool hLock)
{
	sf::RectangleShape * shape = ((sf::RectangleShape*)fDrawable);
	sf::Vector2f position = fTransformable->getPosition();
	sf::Vector2f size = shape->getSize();

	if (!hLock)
		size.x = (gridSnap ? MapGrid::roundToGrid(p.x - position.x) : (p.x - position.x));

	if (!vLock)
		size.y = (gridSnap ? MapGrid::roundToGrid(p.y - position.y) : (p.y - position.y));

	shape->setSize(size);
}

void Player::setColor(const sf::Color & c)
{
	((sf::Shape*)fDrawable)->setFillColor(c);
}

void Player::addScore(int p) {
	fScore += p;
}

void Player::subScore(int p) {
	fScore -= p;
}

int Player::getScore() const {
	return fScore;
}

void Player::setScore(int p) {
	fScore = p;
}

GameObjectClassType Player::getClassType() const
{
	return GameObjectClassType::PLAYER;
}

void Player::serializeObject(std::ostream & ss) const
{
	ss << (int)(getClassType()) << SERIALIZABLE_FIELD_DELIMITER;
	DynamicObject::serializeObject(ss);
	ss << ((sf::RectangleShape *)fDrawable)->getSize().x << SERIALIZABLE_FIELD_DELIMITER;
	ss << ((sf::RectangleShape *)fDrawable)->getSize().y << SERIALIZABLE_FIELD_DELIMITER;
	ss << ((sf::RectangleShape *)fDrawable)->getFillColor().toInteger() << SERIALIZABLE_FIELD_DELIMITER;
	ss << fSpeed << SERIALIZABLE_FIELD_DELIMITER;
	ss << fJumpForce << SERIALIZABLE_FIELD_DELIMITER;
	ss << fScrollZone.left << SERIALIZABLE_FIELD_DELIMITER;
	ss << fScrollZone.right << SERIALIZABLE_FIELD_DELIMITER;
	ss << fScrollZone.top << SERIALIZABLE_FIELD_DELIMITER;
	ss << fScrollZone.bottom << SERIALIZABLE_FIELD_DELIMITER;
	ss << fScore << SERIALIZABLE_FIELD_DELIMITER;
}

void Player::deserializeObject(std::istream & ss)
{
	DynamicObject::deserializeObject(ss);
	float x, y, s, j, sl, sr, st, sb;
	sf::Uint32 c;
	int sc;

	if (!(ss >> x >> y >> c >> s >> j >> sl >> sr >> st >> sb >> sc))
		return;

	((sf::RectangleShape *)fDrawable)->setSize(sf::Vector2f(x, y));
	((sf::RectangleShape *)fDrawable)->setFillColor(sf::Color(c));
	fSpeed = s;
	fJumpForce = j;
	fScrollZone.left = sl;
	fScrollZone.right = sr;
	fScrollZone.top = st;
	fScrollZone.bottom = sb;
	fScore = sc;
}

bool Player::checkSerializableValidity(const std::string& s)
{
	return std::regex_match(s, std::regex(
		REGEX_WHITESPACE 
		+ F_REGEX_GAME_OBJECT_PATTERN
		+ F_REGEX_DYNAMIC_OBJECT_PATTERN
		+ REGEX_FLOAT_PATTERN + "{2}"
		+ REGEX_INT_PATTERN + "{1}"
		+ REGEX_FLOAT_PATTERN + "{6}"
		+ REGEX_INT_PATTERN + "{1}"
		+ REGEX_WHITESPACE
	));
}