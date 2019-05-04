#pragma once
#include "InterfaceView.h"


class OverlayView : public InterfaceView {
protected:
	bool fVisible = false;

public:
	virtual void draw();

	bool getVisibility() const;
	void setVisibility(const bool& v);
	void toggleVisibility();
};