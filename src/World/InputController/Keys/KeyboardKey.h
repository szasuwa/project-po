#pragma once
#include <SFML/Window/Keyboard.hpp>

#include "Key.h"


class KeyboardKey : public Key {
protected:
	virtual void update();
public:
	using Key::Key;
};