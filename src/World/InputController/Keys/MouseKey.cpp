#include "MouseKey.h"


void MouseKey::update() {
	Key::update();
	switch (fKey)
	{
		case InputKey::LMB:
			fIsPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
			break;

		case InputKey::MMB:
			fIsPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle);
			break;

		case InputKey::RMB:
			fIsPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
			break;

		default:
		break;
	}
}