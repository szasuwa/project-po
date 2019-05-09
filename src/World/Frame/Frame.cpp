#include "Frame.h"

Frame::Frame(sf::RenderWindow& w) : fWindow(w), fLastFrameTime(F_MAX_FRAME_TIME)
{
	fClk.restart();
}

bool Frame::isOpen() const
{
	return fWindow.isOpen();
}

bool Frame::hasFocus() const
{
	return fWindow.hasFocus();
}

void Frame::clear()
{
	return fWindow.clear();
}

void Frame::display()
{
	return fWindow.display();
}

bool Frame::pollEvent(sf::Event& e)
{
	return fWindow.pollEvent(e);
}

void Frame::close()
{
	fWindow.close();
}

void Frame::updateView(const sf::View & v, const FrameLayer & layer) 
{
	if (layer == FrameLayer::num_values)
		throw std::out_of_range("Requested FrameLayer num_values");;

	fViewLayers[(int)layer] = v;
	fActiveView = FrameLayer::num_values;
}

void Frame::selectView(const FrameLayer& layer)
{
	if (layer == FrameLayer::num_values)
		throw std::out_of_range("Requested FrameLayer num_values");;

	if (fActiveView != layer)
	{
		fActiveView = layer;
		fWindow.setView(fViewLayers[(int)layer]);
	}
}

void Frame::draw(const sf::Drawable & o, const FrameLayer & layer)
{
	selectView(layer);

	fWindow.draw(o);
}

void Frame::nextFrame()
{
	fLastFrameTime = std::max(0.f, std::min(F_MAX_FRAME_TIME, fClk.restart().asSeconds()));
	fFrameRate = int(1 / fLastFrameTime);
}

sf::Vector2f Frame::getMousePosition(const FrameLayer & layer) 
{
	selectView(layer);

	return fWindow.mapPixelToCoords(sf::Mouse::getPosition(fWindow));
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
	return fWindow.getSize().x;
}

int Frame::getFrameHeight() const 
{
	return fWindow.getSize().y;
}