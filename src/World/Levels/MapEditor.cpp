#include "MapEditor.h"
#include <iostream>

MapEditor::MapEditor(Level *lvl, sf::RenderWindow &wdw) : fWindow(wdw) {
	setLevel(lvl);
}

void MapEditor::setLevel(Level *lvl) {
	fLevel = lvl;
}

void MapEditor::handleEditorControls() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
		fMode = EditorMode::Move;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		fMode = EditorMode::Resize;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
	{
		fMode = EditorMode::Select;
	}
	else {
		fMode = EditorMode::None;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete))
	{
		if (fSelectedObject != nullptr) {
			fLevel->destroyGameObject(fSelectedObject);
			fSelectedObject = nullptr;
		}
	}

	if (!fIsLmbPressed && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		fIsLmbPressed = true;
			
			switch (fMode)
			{
			case MapEditor::None:
				break;
			case MapEditor::Resize:
				if (fSelectedObject != nullptr && fSelectedObject->getGlobalBounds().contains(fWindow.mapPixelToCoords(sf::Mouse::getPosition(fWindow)))) {
					fResizeObject = true;
				}
				break;
			case MapEditor::Move:
				if (fSelectedObject != nullptr && fSelectedObject->getGlobalBounds().contains(fWindow.mapPixelToCoords(sf::Mouse::getPosition(fWindow)))) {
					fMoveObject = true;
				}
				break;
			case MapEditor::Select:
				for (GameObject * obj : fLevel->getGameObjectList()) {
					if (obj->getGlobalBounds().contains(fWindow.mapPixelToCoords(sf::Mouse::getPosition(fWindow)))) {
						fSelectedObject = obj;
						fGhostType = Serializable::CLASS_TYPE::NONE;
						std::cout << fSelectedObject->getClassType() << std::endl;
					}
				}
				break;
			default:
				break;
			}
		
	}

	if (fIsLmbPressed && !sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		fIsLmbPressed = false;
		fResizeObject = false;
		fMoveObject = false;
	}

	if (fSelectedObject != nullptr) {
		switch (fMode)
		{
		case MapEditor::None:
			break;
		case MapEditor::Resize:
			if (fResizeObject) {
				resizeObject();
			}
			break;
		case MapEditor::Move:
			if (fMoveObject) {
				moveObject();
			}
			break;
		case MapEditor::Select:
			break;
		default:
			break;
		}

	}
	fLastMousePosition = sf::Mouse::getPosition(fWindow);
}

void MapEditor::loadGhost() {

}

void MapEditor::selectObject() {
	

}

void MapEditor::resizeObject() {
	fSelectedObject->resize(fWindow.mapPixelToCoords(sf::Mouse::getPosition(fWindow)));
}

void MapEditor::moveObject() {
	fSelectedObject->getTransformable()->move((sf::Vector2f)( sf::Mouse::getPosition(fWindow) - fLastMousePosition));
}

void MapEditor::clearMap() {

}