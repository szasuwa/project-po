#pragma once


class InputInterface
{
public:
	virtual ~InputInterface() {};

	virtual void update() = 0;
	virtual bool isKeyPressed(const unsigned int& key) const = 0;
	virtual bool wasKeyToggled(const unsigned int& key, const bool & desiredState) const = 0;
};