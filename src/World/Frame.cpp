#include "Frame.h"

const float Frame::F_MAX_FRAME_TIME = 1.0/120.0;
sf::Vector2u Frame::fWindowSize;
sf::Clock Frame::fClk;
float Frame::fLastFrameTime;
int Frame::fFrameRate;


Frame::Frame()
{
}

Frame::Frame(sf::Vector2u size)
{
	fWindowSize = size;
}


Frame::~Frame()
{
}

void Frame::nextFrame() {
	fLastFrameTime = std::min(fClk.restart().asSeconds(), F_MAX_FRAME_TIME);
	fFrameRate = int(1 / fLastFrameTime);
}

float Frame::getMaxFrameTime() {
	return F_MAX_FRAME_TIME;
}

float Frame::getFrameTime() {
	return fLastFrameTime;
}

int Frame::getFrameRate() {
	return fFrameRate;
}
void Frame::setWindowSize(sf::Vector2u size) {
	fWindowSize = size;
}

int Frame::getWindowWidth() {
	return fWindowSize.x;
}

int Frame::getWindowHeight() {
	return fWindowSize.y;
}