#pragma once
#include "GameObject.h"
#include <SFML/Graphics/CircleShape.hpp>

class Point : public GameObject {
    static int fPointCount;

public:
    Point(Level* lvl = nullptr);
    explicit Point(sf::Vector2f &position, Level* lvl = nullptr);
    explicit Point(float radius, Level* lvl = nullptr);
    explicit Point(float radius, sf::Vector2f &position, Level* lvl = nullptr);
    explicit Point(float radius, sf::Vector2f position, sf::Color color, Level* lvl = nullptr);

    ~Point();
    
    void serializeData(std::stringstream &ss, bool last = true);
	void deserializeData(std::stringstream &ss);

	sf::FloatRect getGlobalBounds();
	sf::Transformable *getTransformable();
	void update();

    static int getPointCount();
};