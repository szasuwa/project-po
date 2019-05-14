#pragma once
#include <vector>

#include "../Interfaces/InputInterface.h"
#include "KeyBindingIndex.h"
#include "KeyBinding.h"
#include "Keys/Key.h"
#include "Keys/KeyboardKey.h"
#include "Keys/MouseKey.h"


class InputController : public InputInterface {
private:
	Key* fKeyBindings[(unsigned int)KeyBindingIndex::num_values] = { nullptr };
	std::vector<TextWatcherInterface*> fTextWatchers;

public:
	InputController();
	~InputController();
	virtual void update();

	virtual bool isKeyPressed(const unsigned int&key) const;
	virtual bool wasKeyToggled(const unsigned int& key, const bool& desiredState) const;

	virtual void reportKeyEnteredEvent(const sf::Event& event);
	virtual void addTextWatcher(TextWatcherInterface* watcher);
	virtual void removeTextWatcher(TextWatcherInterface* watcher);
};