#pragma once
#include <vector>

#include "../InterfaceItems/InterfaceItem.h"
#include "../../Frame/FrameMargin.h"
#include "../../Frame/Frame.h"


class InterfaceGroup {
public:
	enum Alignment {
		Left,
		Right,
		Center
	};

protected:
	FrameMargin fMargin{ 5,5,5,0 };
	bool fVisible = true;
	Alignment fAlignment;
	std::vector<InterfaceItem *> fItemList;

public:
	InterfaceGroup(const Alignment &a = Alignment::Left);
	virtual void update() = 0;
	void drawGroup() const;

	float calculateHeight() const;
	float calculateWidth() const;
	void calculatePositions(float offset);

	bool getVisibility() const;
	void setVisibility(const bool &v);
	void toggleVisibility();
	Alignment getAlignment() const;
	void setAlignment(const Alignment &align);
};