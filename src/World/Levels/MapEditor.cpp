#include "MapEditor.h"


MapEditor::MapEditor(Level *lvl, sf::RenderWindow &wdw) : fWindow(wdw) {
	setLevel(lvl);
}

void MapEditor::setLevel(Level *lvl) {
	fLevel = lvl;
}

void MapEditor::handleEditorControls() {
	//Mode Handling
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || fMoveObject)
	{
		fMode = EditorMode::Move;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || fResizeObject)
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


	//Deleting objects
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


	//Axis Locking and Grid Snapping
	if (!fIsVerticalLockPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
		fIsVerticalLockPressed = true;
		fVerticalLock = !fVerticalLock;
		MapEditorInterface::reportAxisLockStatus(fVerticalLock, fHorizontalLock);
	}

	if (fIsVerticalLockPressed && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
		fIsVerticalLockPressed = false;
	}

	if (!fIsHorizontalLockPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
		fIsHorizontalLockPressed = true;
		fHorizontalLock = !fHorizontalLock;
		MapEditorInterface::reportAxisLockStatus(fVerticalLock, fHorizontalLock);
	}

	if (fIsHorizontalLockPressed && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
		fIsHorizontalLockPressed = false;
	}

	if (!fIsGridSnapPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Tab)) {
		fIsGridSnapPressed = true;
		fSnapToGrid = !fSnapToGrid;
		MapEditorInterface::reportGridSnapStatus(fSnapToGrid);
	}

	if (fIsGridSnapPressed && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Tab)) {
		fIsGridSnapPressed = false;
	}


	//Ghost
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


	//Mouse
	if (!fIsLmbPressed && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		fIsLmbPressed = true;

		switch (fMode){
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
					fLastMouseOffset = fSelectedObject->getTransformable()->getPosition() - fWindow.mapPixelToCoords(sf::Mouse::getPosition(fWindow));
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
		fSelectedObject = nullptr;
	}


	//Actions
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
		}
	}
}

void MapEditor::resizeObject() {
	fSelectedObject->resize(fWindow.mapPixelToCoords(sf::Mouse::getPosition(fWindow)), fVerticalLock, fHorizontalLock, fSnapToGrid);
}

void MapEditor::moveObject() {
	sf::Vector2f vect = fWindow.mapPixelToCoords(sf::Mouse::getPosition(fWindow)) + fLastMouseOffset;
	if (fHorizontalLock) {
		vect.x = 0;
	}

	if (fVerticalLock) {
		vect.y = 0;
	}

	if (fSnapToGrid) {
		vect.x = MapGrid::roundToGrid(vect.x);
		vect.y = MapGrid::roundToGrid(vect.y);
	}

	fSelectedObject->getTransformable()->setPosition(vect);
}

void MapEditor::clearMap() {

}

MapEditorItem* MapEditor::getGhost() {
	return fGhost;
}