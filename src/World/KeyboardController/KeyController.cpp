#include "KeyController.h"
KeyController * KeyController::instance = nullptr;

KeyController::KeyController()
{
}

KeyController & KeyController::getInstance() 
{
	if (instance == nullptr)
		instance = new KeyController();

	return *instance;
}

KeyGroup & KeyController::getKeyGroup(const KeyBinding & key)
{
	return fKeyBindings[key];
}