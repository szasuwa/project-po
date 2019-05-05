#pragma once
#include "TextViewItem.h"
#include "../ViewActions/ViewAction.h"
#include "../../InputController/MouseController.h"


class ButtonViewItem : public TextViewItem {
protected:
	ViewAction *fOnClick = nullptr;
	ViewAction *fOnMouseEnter = nullptr;
	ViewAction* fOnMouseOver = nullptr;
	ViewAction* fOnMouseExit = nullptr;
	bool fIsMouseOver = false;

public:
	virtual ~ButtonViewItem();

	virtual void update();
	virtual void draw() const;

	void setOnClick(ViewAction * f);
	void setOnMouseEnter(ViewAction* f);
	void setOnMouseOver(ViewAction* f);
	void setOnMouseExit(ViewAction* f);
};