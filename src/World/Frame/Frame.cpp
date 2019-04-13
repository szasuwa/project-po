#include "Frame.h"
Frame * Frame::instance = nullptr;

Frame::Frame()
{
	fLastFrameTime = 0;
	fClk.restart();
}

Frame & Frame::getInstance() 
{
	if (instance == nullptr)
		instance = new Frame();

	return *instance;
}

void Frame::nextFrame() 
{
	fLastFrameTime = std::min(fClk.restart().asSeconds(), F_MAX_FRAME_TIME);
	fFrameRate = int(1 / fLastFrameTime);
}

void Frame::updateView(const sf::View & v, const FrameLayer & layer) 
{
	if (layer < 0 || layer >= FrameLayer::num_values)
		return;

	fViewLayers[layer] = v;
}

void Frame::draw(const sf::Drawable & o, const FrameLayer & layer)
{
	if (fWindow == nullptr)
		return;

	if (layer < 0 || layer >= FrameLayer::num_values)
		return;

	if (fActiveView != layer)
	{
		fActiveView = layer;
		fWindow->setView(fViewLayers[layer]);
	}

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