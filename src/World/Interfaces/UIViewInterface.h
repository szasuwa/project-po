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

	bool getVisibility() { return fVisible; }
	void setVisibility(const bool& v) { fVisible = v; }

	virtual std::string getProperty(const unsigned int& id) = 0;
	virtual void setProperty(const unsigned int& id, const std::string& v) = 0;
};