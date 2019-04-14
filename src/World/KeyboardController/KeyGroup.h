#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <vector>
#include <string>


class KeyGroup {
	std::vector<sf::Keyboard::Key> fKeys;
	bool fWasPressed = false;
	bool fIsPressed = false;

	const std::string KeyGroup::getKeyName(const sf::Keyboard::Key & key) const;
	void update();

public:
	KeyGroup(const std::vector<sf::Keyboard::Key> & keys);

	bool isPressed();
	bool isReleased();
	bool wasToggled();

	std::string toString() const;
};