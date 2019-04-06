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
	else if (fGhost != nullptr)
	{
		fMode = EditorMode::Ghost;
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

		if (fGhost != nullptr) {
			delete fGhost;
		}
	}

	if (!fIsGhostPressed){
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			fIsGhostPressed = true;
			loadGhost(Serializable::CLASS_TYPE::PLAYER);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			fIsGhostPressed = true;
			loadGhost(Serializable::CLASS_TYPE::PLATFORM);
			
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		{
			fIsGhostPressed = true;
			loadGhost(Serializable::CLASS_TYPE::POINT);
		}
	}
	else {
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		{
			fIsGhostPressed = false;
		}
	}

	if (!fIsLmbPressed && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		fIsLmbPressed = true;
			
			switch (fMode)
			{
			case MapEditor::None:
				selectObject();
				break;
			case MapEditor::Resize:
				if (fSelectedObject == nullptr) {
					selectObject();
				}
				if (fSelectedObject != nullptr && fSelectedObject->getGlobalBounds().contains(fWindow.mapPixelToCoords(sf::Mouse::getPosition(fWindow)))) {
					fResizeObject = true;
				}
				break;
			case MapEditor::Move:
				if (fSelectedObject == nullptr) {
					selectObject();
				}
				if (fSelectedObject != nullptr && fSelectedObject->getGlobalBounds().contains(fWindow.mapPixelToCoords(sf::Mouse::getPosition(fWindow)))) {
					fMoveObject = true;
				}
				break;
			case MapEditor::Ghost:
				if (fGhost != nullptr) {
					GameObject * obj;
					switch (fGhostType)
					{
					case Serializable::NONE:
						break;
					case Serializable::PLAYER:
						obj = new Player(fGhost->transformable->getPosition(), fLevel);
						break;
					case Serializable::PLATFORM:
						obj = new Platform(fGhost->transformable->getPosition(), fLevel);
						break;
					case Serializable::POINT:
						obj = new Point(fGhost->transformable->getPosition(), fLevel);
						break;
					default:
						break;
					}

					if (obj != nullptr) {
						fLevel->addGameObject(obj);
						delete fGhost;
						fGhost = nullptr;
						fGhostType = Serializable::CLASS_TYPE::NONE;
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
		default:
			break;
		}

	}
	fLastMousePosition = sf::Mouse::getPosition(fWindow);
	if (fGhost != nullptr) {
		fGhost->transformable->setPosition(fWindow.mapPixelToCoords(sf::Mouse::getPosition(fWindow)));
	}
}

void MapEditor::loadGhost(Serializable::CLASS_TYPE type) {
	fSelectedObject = nullptr;
	if (fGhost != nullptr) {
		delete fGhost;
	}
	
	fGhostType = type;

	switch (type)
	{
	case Serializable::NONE:
		break;
	case Serializable::PLAYER:
		fGhost = Player::getGhostDrawable();
		break;
	case Serializable::PLATFORM:
		fGhost = Platform::getGhostDrawable();
		break;
	case Serializable::POINT:
		fGhost = Point::getGhostDrawable();
		break;
	default:
		break;
	}

	if (fGhost != nullptr) {
		fMode = EditorMode::Ghost;
	}
}

void MapEditor::selectObject() {
	for (GameObject * obj : fLevel->getGameObjectList()) {
		if (obj->getGlobalBounds().contains(fWindow.mapPixelToCoords(sf::Mouse::getPosition(fWindow)))) {
			fSelectedObject = obj;
			fGhostType = Serializable::CLASS_TYPE::NONE;
			std::cout << fSelectedObject->getClassType() << std::endl;
		}
	}
}

void MapEditor::resizeObject() {
	fSelectedObject->resize(fWindow.mapPixelToCoords(sf::Mouse::getPosition(fWindow)));
}

void MapEditor::moveObject() {
	fSelectedObject->getTransformable()->move((sf::Vector2f)( sf::Mouse::getPosition(fWindow) - fLastMousePosition));
}

void MapEditor::clearMap() {

}

MapEditorItem* MapEditor::getGhost() {
	return fGhost;
}