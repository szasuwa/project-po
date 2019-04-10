#pragma once
#include <SFML/Graphics/CircleShape.hpp>

#include "../Bases/GameObject.h"
#include "../../Map/Editor/MapEditorItem.h"


class Point : public GameObject {
public:
    Point(Map* map = nullptr);
    explicit Point(sf::Vector2f position, Map* map = nullptr);
    explicit Point(float radius, Map* map = nullptr);
    explicit Point(float radius, sf::Vector2f &position, Map* map = nullptr);
    explicit Point(float radius, sf::Vector2f position, sf::Color color, Map* map = nullptr);

    ~Point();
    
    void serializeData(std::stringstream &ss, bool last = true);
	void deserializeData(std::stringstream &ss);
	CLASS_TYPE getClassType();

	sf::FloatRect getGlobalBounds();
	static MapEditorItem *getGhostDrawable();
	void resize(sf::Vector2f rb, bool vLock, bool hLock, bool snapToGrid);
	sf::Transformable *getTransformable();
	void update();
};