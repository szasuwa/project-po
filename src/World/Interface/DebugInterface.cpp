#include "DebugInterface.h"

DebugInterface::DebugInterface() : DebugInterface(Alignment::Left) {
}

DebugInterface::DebugInterface(Alignment align) {
	fAlignment = align;
	fVersion.setText("Version: " + GAME_VERSION);

	fItemList.push_back(&fVersion);
	fItemList.push_back(&fFpsMeter);
}

void DebugInterface::update() {
	fFpsMeter.setText(std::to_string(Frame::getFrameRate()) + " FPS");
}