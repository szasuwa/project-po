#pragma once
#include <string>


class GameEngineInterface;

class UIViewInterface {
protected:
	bool fVisible = true;

public:
	virtual ~UIViewInterface() {};
	virtual void updateView(GameEngineInterface& f) = 0;
	virtual void update(GameEngineInterface& f) = 0;
	virtual void draw(GameEngineInterface& f) = 0;

	bool getVisibility() { return fVisible; }
	void setVisibility(const bool& v) { fVisible = v; }

	virtual std::string getProperty(const unsigned int& id) = 0;
	virtual void setProperty(const unsigned int& id, const std::string& v) = 0;
};