#include "KeyGroup.h"


KeyGroup::KeyGroup(const std::vector<sf::Keyboard::Key> & keys) 
{
	fKeys = keys;
}

void KeyGroup::update() 
{
	fIsPressed = fIsPressed;
	fIsPressed = false;
	for (sf::Keyboard::Key k : fKeys)
	{
		fIsPressed |= sf::Keyboard::isKeyPressed(k);
	}
}

bool KeyGroup::isPressed() const
{
	return fIsPressed;
}

bool KeyGroup::isReleased()  const
{
	return !fIsPressed;
}

bool KeyGroup::wasToggled()  const
{
	return (fIsPressed != fWasPressed);
}