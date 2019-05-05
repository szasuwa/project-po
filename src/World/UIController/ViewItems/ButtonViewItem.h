#pragma once
#include "TextViewItem.h"
#include "../ViewActions/ViewAction.h"
#include "../../Interfaces/InputInterface.h"
#include "../../InputController/KeyBindingIndex.h"


class ButtonViewItem : public TextViewItem {
protected:
	ViewAction *fOnClick = nullptr;
	ViewAction *fOnMouseEnter = nullptr;
	ViewAction* fOnMouseOver = nullptr;
	ViewAction* fOnMouseExit = nullptr;
	bool fIsMouseOver = false;

public:
	ButtonViewItem() {};
	virtual ~ButtonViewItem();

	virtual void update(UIInterface& f);
	virtual void draw(UIInterface& f) const;

	void setOnClick(ViewAction * f);
	void setOnMouseEnter(ViewAction* f);
	void setOnMouseOver(ViewAction* f);
	void setOnMouseExit(ViewAction* f);
};