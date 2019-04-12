#pragma once
#include <SFML/Graphics/CircleShape.hpp>

#include "../Bases/GameObject.h"
#include "../../Map/Editor/MapEditorItem.h"


class Point : public GameObject {
	sf::Drawable * createDrawable();
public:
    explicit Point(Map* map = nullptr);
    Point(const sf::Vector2f &position, Map* map = nullptr);
    Point(const float &radius, Map* map = nullptr);
    Point(const float &radius, const sf::Vector2f &position, Map* map = nullptr);
    Point(const float &radius, const sf::Vector2f &position, const sf::Color &color, Map* map = nullptr);
	Point(const Point &obj);

    ~Point();
    
    void serializeData(std::stringstream &ss, bool last = true);
	void deserializeData(std::stringstream &ss);
	CLASS_TYPE getClassType();

	sf::FloatRect getGlobalBounds();
	static MapEditorItem *getGhostDrawable();
	void resize(const sf::Vector2f &rb, bool vLock, bool hLock, bool snapToGrid);
	sf::Transformable *getTransformable();
	void update();
};