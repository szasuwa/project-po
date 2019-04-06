#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

struct MapEditorItem {
	sf::Drawable *drawable;
	sf::Transformable *transformable;
};