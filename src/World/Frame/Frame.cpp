#include "Frame.h"


Frame & Frame::getInstance() 
{
	static Frame instance;
	return instance;
}

void Frame::nextFrame() 
{
	fLastFrameTime = std::min(fClk.restart().asSeconds(), F_MAX_FRAME_TIME);
	fFrameRate = int(1 / fLastFrameTime);
}

void Frame::updateCamera(const sf::View & v) 
{
	if (fWindow == nullptr)
		return;

	fWindow->setView(v);
}

void Frame::draw(const sf::Drawable & o)
{
	if (fWindow == nullptr)
		return;

	fWindow->draw(o);
}

void Frame::setWindow(sf::RenderWindow & w) 
{
	fWindow = &w;
}

float Frame::getMaxFrameTime() const 
{
	return F_MAX_FRAME_TIME;
}

float Frame::getFrameTime() const 
{
	return fLastFrameTime;
}

int Frame::getFrameRate() const 
{
	return fFrameRate;
}

int Frame::getFrameWidth() const 
{
	if (fWindow == nullptr)
		return 0;

	return fWindow->getSize().x;
}

int Frame::getFrameHeight() const 
{
	if (fWindow == nullptr)
		return 0;

	return fWindow->getSize().y;
}