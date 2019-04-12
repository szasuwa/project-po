#include "InfoInterface.h"

InfoInterface::InfoInterface() : InfoInterface(Alignment::Left) {
}

InfoInterface::InfoInterface(Alignment align) {
	fAlignment = align;
	fMapEditorKey.setText("F2 - Map Editor");
	fDebugKey.setText("F3 - Debug");
	fItemList.push_back(&fMapEditorKey);
	fItemList.push_back(&fDebugKey);
}

void InfoInterface::update() {
}