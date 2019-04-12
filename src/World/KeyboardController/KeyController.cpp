#include "KeyController.h"


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