#pragma once
#include <SFML/Window/Event.hpp>

#include "TextViewItem.h"
#include "../../Interfaces/TextWatcherInterface.h"
#include "../ViewActions/ViewAction.h"
#include "../../Interfaces/InputInterface.h"
#include "../../InputController/KeyBindingIndex.h"


class TextInputViewItem : public TextViewItem, public TextWatcherInterface {
protected:
	std::string fPlaceholder = "...";
	std::string fInputSign = "|";
	float fElapsedTime = 0;
	std::string fTextContent;
	InputInterface* fTextWatcherHandler = nullptr;
	bool fIsSelected = false;
	ViewAction* fOnEnterPressed = nullptr;

public:
	virtual ~TextInputViewItem();

	virtual void update(GameEngineInterface& f);
	virtual void draw(GameEngineInterface& f) const;

	virtual void setText(const std::string& txt);

	void setOnEnterPressed(ViewAction * f, bool persistent = false);

	virtual void onTextInput(sf::Event::TextEvent text);

};