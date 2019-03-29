#pragma once
#include <SFML/Graphics/CircleShape.hpp>

#include "../Bases/GameObject.h"


class Point : public GameObject {
public:
    Point(Level* lvl = nullptr);
    explicit Point(sf::Vector2f &position, Level* lvl = nullptr);
    explicit Point(float radius, Level* lvl = nullptr);
    explicit Point(float radius, sf::Vector2f &position, Level* lvl = nullptr);
    explicit Point(float radius, sf::Vector2f position, sf::Color color, Level* lvl = nullptr);

    ~Point();
    
    void serializeData(std::stringstream &ss, bool last = true);
	void deserializeData(std::stringstream &ss);
	CLASS_TYPE getClassType();

	sf::FloatRect getGlobalBounds();
	sf::Transformable *getTransformable();
	void update();
};