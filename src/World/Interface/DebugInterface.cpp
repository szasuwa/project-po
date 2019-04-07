#include "DebugInterface.h"

DebugInterface::DebugInterface() : DebugInterface(Alignment::Left) {
}

DebugInterface::DebugInterface(Alignment align) {
	fAlignment = align;
	fItemList.push_back(&fFpsMeter);
}

void DebugInterface::update() {
	fFpsMeter.setText(std::to_string(Frame::getFrameRate()) + " FPS");
}