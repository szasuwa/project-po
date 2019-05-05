#pragma once
#include <SFML/Window/Mouse.hpp>

#include "Key.h"


class MouseKey : public Key {
protected:
	virtual void update();
public:
	using Key::Key;
};