#include "Frame.h"
Frame * Frame::instance = nullptr;

Frame::Frame()
{
	fLastFrameTime = F_MAX_FRAME_TIME;
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
	if (layer == FrameLayer::num_values)
		return;

	fViewLayers[(int)layer] = v;
}

void Frame::draw(const sf::Drawable & o, const FrameLayer & layer)
{
	if (fWindow == nullptr || layer == FrameLayer::num_values)
		return;

	if (fActiveView != layer)
	{
		fActiveView = layer;
		fWindow->setView(fViewLayers[(int)layer]);
	}

	fWindow->draw(o);
}

sf::Vector2f Frame::getMousePosition(const FrameLayer & layer) 
{
	if (fWindow == nullptr || layer == FrameLayer::num_values)
		return sf::Vector2f();

	if (fActiveView != layer)
	{
		fActiveView = layer;
		fWindow->setView(fViewLayers[(int)layer]);
	}

	return fWindow->mapPixelToCoords(sf::Mouse::getPosition(*fWindow));
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