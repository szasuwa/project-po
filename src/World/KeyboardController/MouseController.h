#pragma once
#include <SFML/Window/Mouse.hpp>


class MouseController
{
private:
	static MouseController* instance;

	bool fWasLmbPressed = false;
	bool fIsLmbPressed = false;

	MouseController();
	MouseController(const MouseController& o);

public:
	static MouseController & getInstance();

	void update();
	bool isLmbPressed() const;
	bool wasLmbToggledDown() const;
	bool wasLmbToggledUp() const;
};