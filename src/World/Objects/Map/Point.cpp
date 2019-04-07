#include "Point.h"

Point::Point(Level* lvl) : Point(10, sf::Vector2f(0,0), sf::Color(255,255,255,255), lvl)
{
}

Point::Point(float radius, Level* lvl) : Point(radius, sf::Vector2f(0,0), sf::Color(255,255,255,255), lvl)
{}

Point::Point(sf::Vector2f position, Level* lvl) : Point(10, position, sf::Color(255,255,255,255), lvl)
{}

Point::Point(float radius, sf::Vector2f &position, Level* lvl) : Point(radius, position, sf::Color(255,255,255,255), lvl)
{}

Point::Point(float radius, sf::Vector2f position, sf::Color color, Level* lvl) : GameObject(lvl)
{
    fDrawable = new sf::CircleShape(radius);
    ((sf::CircleShape*)fDrawable)->setPosition(position);
	((sf::CircleShape*)fDrawable)->setFillColor(color);
}

Point::~Point()
{
}

void Point::deserializeData(std::stringstream &ss) {
	GameObject::deserializeData(ss);
    float radius;
    ss >> radius;
    ((sf::CircleShape*)fDrawable)->setRadius(radius);
}

void Point::serializeData(std::stringstream &ss, bool last) {
	ss << CLASS_TYPE::POINT << SERIALIZABLE_FIELD_DELIMITER;
	GameObject::serializeData(ss, false);
    ss << ((sf::CircleShape*)fDrawable)->getRadius();
	Serializable::serializeData(ss, last);
}

Point::CLASS_TYPE Point::getClassType() {
	return CLASS_TYPE::POINT;
}

sf::FloatRect Point::getGlobalBounds() {
	return ((sf::Shape*)fDrawable)->getGlobalBounds();
};

void Point::resize(sf::Vector2f rb, bool vLock, bool hLock) {
}

MapEditorItem *Point::getGhostDrawable() {
	sf::CircleShape *x = new sf::CircleShape(10);
	x->setFillColor(sf::Color(255, 255, 255, 255));
	MapEditorItem *out = new MapEditorItem();
	out->drawable = x;
	out->transformable = x;
	return out;
};


sf::Transformable *Point::getTransformable() {
	return ((sf::Shape*)fDrawable);
};

void Point::update() 
{
}