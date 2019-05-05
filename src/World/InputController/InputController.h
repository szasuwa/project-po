#pragma once
#include "../Interfaces/InputInterface.h"
#include "KeyBindingIndex.h"
#include "KeyBinding.h"
#include "Keys/Key.h"
#include "Keys/KeyboardKey.h"
#include "Keys/MouseKey.h"


class InputController : public InputInterface {
private:
	Key* fKeyBindings[(unsigned int)KeyBindingIndex::num_values] = { nullptr };

public:
	InputController();
	~InputController();
	virtual void update();
	virtual bool isKeyPressed(const unsigned int& key) const;
	virtual bool wasKeyToggled(const unsigned int& key, const bool& desiredState) const;
};