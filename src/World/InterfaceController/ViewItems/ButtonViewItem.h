#pragma once
#include "TextViewItem.h"
#include "../../KeyboardController/MouseController.h"


class ButtonViewItem : public TextViewItem {
public:
	virtual void draw() const;
};