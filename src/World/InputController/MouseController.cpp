#include "MouseController.h"
MouseController* MouseController::instance = nullptr;

MouseController::MouseController()
{
}

MouseController& MouseController::getInstance()
{
	if (instance == nullptr)
		instance = new MouseController();

	return *instance;
}

void MouseController::update()
{
	fWasLmbPressed = fIsLmbPressed;
	fIsLmbPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

bool MouseController::isLmbPressed() const
{
	return fIsLmbPressed;
}

bool MouseController::wasLmbToggledDown() const
{
	return !fWasLmbPressed && fIsLmbPressed;
}

bool MouseController::wasLmbToggledUp() const
{
	return fWasLmbPressed && !fIsLmbPressed;
}


