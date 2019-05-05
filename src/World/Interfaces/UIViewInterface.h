#pragma once
class UIInterface;

class UIViewInterface {
protected:
	bool fVisible = true;

public:
	virtual ~UIViewInterface() {};
	virtual void updateView(UIInterface& f) = 0;
	virtual void update(UIInterface& f) = 0;
	virtual void draw(UIInterface& f) = 0;

	virtual bool getVisibility() { return fVisible; }
	virtual void setVisibility(const bool& v) { fVisible = v; }
};