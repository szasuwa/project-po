#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <vector>


class KeyGroup {
	std::vector<sf::Keyboard::Key> fKeys;
	bool fWasPressed = false;
	bool fIsPressed = false;

	const std::string KeyGroup::getKeyName(const sf::Keyboard::Key & key) const;

public:
	KeyGroup(const std::vector<sf::Keyboard::Key> & keys);
	void update();
	bool isPressed() const;
	bool isReleased() const;
	bool wasToggled() const;
	std::string toString() const;
};