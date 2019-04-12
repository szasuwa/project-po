#include "Gui.h"

int Gui::fPoints = 0;

Gui::Gui() : Gui(Alignment::Left) {
}

Gui::Gui(Alignment align) {
	fAlignment = align;
	fItemList.push_back(&fPointsBox);
}

void Gui::update() {
	fPointsBox.setText(std::string("Points: " + std::to_string(fPoints)));
}

void Gui::setPoints(int p) {
	fPoints = p;
}

