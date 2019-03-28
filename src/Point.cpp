#include "Point.h"
int Point::fPointCount = 0;

Point::Point() : Point(10, sf::Vector2f(0,0), sf::Color(255,255,255,255))
{
}

Point::Point(float radius) : Point(radius, sf::Vector2f(0,0), sf::Color(255,255,255,255))
{}

Point::Point(sf::Vector2f &position) : Point(10, position, sf::Color(255,255,255,255))
{}

Point::Point(float radius, sf::Vector2f &position) : Point(radius, position, sf::Color(255,255,255,255))
{}

Point::Point(float radius, sf::Vector2f position, sf::Color color)
{
    fPointCount++;
    fDrawable = new sf::CircleShape(radius);
    ((sf::CircleShape*)fDrawable)->setPosition(position);
	((sf::CircleShape*)fDrawable)->setFillColor(color);
}

Point::~Point()
{
    fPointCount--;
}

void Point::deserializeData(std::stringstream &ss) {
	GameObject::deserializeData(ss);
    float radius;
    ss >> radius;
    ((sf::CircleShape*)fDrawable)->setRadius(radius);
}

void Point::serializeData(std::stringstream &ss, bool last) {
	ss << SERIALIZABLE_CLASS_TYPE_POINT << SERIALIZABLE_FIELD_DELIMITER;
	GameObject::serializeData(ss, false);
    ss << ((sf::CircleShape*)fDrawable)->getRadius();
	Serializable::serializeData(ss, last);
}

sf::FloatRect Point::getGlobalBounds() {
	return ((sf::Shape*)fDrawable)->getGlobalBounds();
};

sf::Transformable *Point::getTransformable() {
	return ((sf::Shape*)fDrawable);
};

void Point::update() 
{
}

int Point::getPointCount(){
    return fPointCount;
}