#pragma once
class UIInterface;

class UIViewInterface {
protected:
	UIInterface& fUIViewInterface;
	bool fVisible = true;

public:
	UIViewInterface(UIInterface& f) : fUIViewInterface(f) {};
	virtual ~UIViewInterface() {};
	virtual void updateView() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;

	virtual bool getVisibility() { return fVisible; }
	virtual void setVisibility(const bool& v) { fVisible = v; }
};