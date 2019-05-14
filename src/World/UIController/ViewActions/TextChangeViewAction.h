#pragma once
#include <string>

#include "ViewAction.h"
#include "../ViewItems/TextViewItem.h"


class TextChangeViewAction : public ViewAction {
	std::string fText;
	TextViewItem& fItem;

public:
	explicit TextChangeViewAction(const std::string& t, TextViewItem & i):fText(t), fItem(i) {};
	virtual void operator() () { fItem.setText(fText); };
};