#include "KeyController.h"

KeyController & KeyController::getInstance() 
{
	static KeyController instance;
	return instance;
}

void KeyController::update() 
{
	for (KeyGroup k : fKeyBindings) 
	{
		k.update();
	}
}

const KeyGroup & KeyController::getKeyGroup(const KeyBinding & key) const 
{
	return fKeyBindings[key];
}