#pragma once
#include <vector>
#include <string>

#include "../../Interfaces/InputKey.h"


class Key {
protected:
	const InputKey fKey;

	bool fWasPressed = false;
	bool fIsPressed = false;

public:
	Key(const InputKey & key);

	virtual void update();
	virtual bool isPressed() const;
	virtual bool wasToggled(const bool& desiredState) const;

	virtual const std::string toString() const;
};