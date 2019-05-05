#pragma once
#include "TextViewItem.h"
#include "../ViewActions/ViewAction.h"
#include "../../Interfaces/InputInterface.h"
#include "../../InputController/KeyBindingIndex.h"


class ButtonViewItem : public TextViewItem {
protected:
	InputInterface& fInput;
	ViewAction *fOnClick = nullptr;
	ViewAction *fOnMouseEnter = nullptr;
	ViewAction* fOnMouseOver = nullptr;
	ViewAction* fOnMouseExit = nullptr;
	bool fIsMouseOver = false;

public:
	ButtonViewItem(UIInterface& f) : TextViewItem(f), fInput(fUIInterface.getInput()) {}
	virtual ~ButtonViewItem();

	virtual void update();
	virtual void draw() const;

	void setOnClick(ViewAction * f);
	void setOnMouseEnter(ViewAction* f);
	void setOnMouseOver(ViewAction* f);
	void setOnMouseExit(ViewAction* f);
};