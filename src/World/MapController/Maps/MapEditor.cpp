#include "MapEditor.h"

MapEditor::MapEditor() : fKey(KeyController::getInstance()), fFrame(Frame::getInstance())
{
	MapEditorInterface::reportAxisLockStatus(fVerticalLock, fHorizontalLock);
	MapEditorInterface::reportGridSnapStatus(fSnapToGrid);
}

Map * MapEditor::loadMap(const Map & map)
{
	fMap = map;
	fGrid.update(fMap.getBoundaries());
	return &fMap;
}

void MapEditor::update() {
	handleGrid();
	handleModeSelection();
	handleDeletion();
	handleClone();
	handleAxes();
	handleGhost();
	handleMouse();
	handleActions();
}

void MapEditor::handleGrid() 
{
	fFrame.draw(fGrid, Frame::FrameLayer::MapArea);

	sf::Vector2f cam;

	if (fKey.getKeyGroup(KeyController::CameraLeft).isPressed())
		cam.x -= 10;

	if (fKey.getKeyGroup(KeyController::CameraRight).isPressed())
		cam.x += 10;

	if (fKey.getKeyGroup(KeyController::CameraUp).isPressed())
		cam.y -= 10;

	if (fKey.getKeyGroup(KeyController::CameraDown).isPressed())
		cam.y += 10;

	fMap.moveCamera(cam);
}

void MapEditor::handleModeSelection()
{
	if (fKey.getKeyGroup(KeyController::MapEditorMove).isPressed() || fMoveObject)
		fMode = EditorMode::Move;
	else if (fKey.getKeyGroup(KeyController::MapEditorResize).isPressed() || fResizeObject)
		fMode = EditorMode::Resize;
	else if (fGhost != nullptr)
		fMode = EditorMode::Ghost;
	else
		fMode = EditorMode::None;
}

void MapEditor::handleDeletion()
{
	if (fKey.getKeyGroup(KeyController::MapEditorDelete).isPressed())
	{
		if (fSelectedObject != nullptr) 
		{
			fMap.destroyGameObject(fSelectedObject);
			fSelectedObject = nullptr;
		}

		if (fGhost != nullptr) 
		{
			delete fGhost;
			fGhost = nullptr;
		}
	}
}

void MapEditor::handleClone()
{
	if (fSelectedObject != nullptr && !fCloned && fKey.getKeyGroup(KeyController::MapEditorClone).isPressed())
	{
		fCloned = true;
		GameObject * temp;
		switch (fSelectedObject->getClassType())
		{
			case GameObjectClassType::PLAYER:
				temp = new Player(*(Player*)fSelectedObject);
				break;
			case GameObjectClassType::PLATFORM:
				temp = new Platform(*(Platform*)fSelectedObject);
				break;
				case GameObjectClassType::POINT:
				temp = new Point(*(Point*)fSelectedObject);
				break;
			default:
				return;
		}
		fSelectedObject = temp;
		fMap.addGameObject(fSelectedObject);
		fMoveObject = true;
	}

	if (fCloned && fKey.getKeyGroup(KeyController::MapEditorClone).isReleased())
		fCloned = !fCloned;
}

void MapEditor::handleAxes()
{
	//Axis Locking and Grid Snapping
	if (fKey.getKeyGroup(KeyController::MapEditorVLock).wasToggled() && fKey.getKeyGroup(KeyController::MapEditorVLock).isPressed())
	{
		fVerticalLock = !fVerticalLock;
		MapEditorInterface::reportAxisLockStatus(fVerticalLock, fHorizontalLock);
	}

	if (fKey.getKeyGroup(KeyController::MapEditorHLock).wasToggled() && fKey.getKeyGroup(KeyController::MapEditorHLock).isPressed())
	{
		fHorizontalLock = !fHorizontalLock;
		MapEditorInterface::reportAxisLockStatus(fVerticalLock, fHorizontalLock);
	}

	if (fKey.getKeyGroup(KeyController::MapEditorGridLock).wasToggled() && fKey.getKeyGroup(KeyController::MapEditorGridLock).isPressed())
	{
		fSnapToGrid = !fSnapToGrid;
		MapEditorInterface::reportGridSnapStatus(fSnapToGrid);
	}
}

void MapEditor::handleGhost()
{
	if (fKey.getKeyGroup(KeyController::MapEditorGhostPlayer).wasToggled() && fKey.getKeyGroup(KeyController::MapEditorGhostPlayer).isPressed())
		loadGhost(GameObjectClassType::PLAYER);

	if (fKey.getKeyGroup(KeyController::MapEditorGhostPlatform).wasToggled() && fKey.getKeyGroup(KeyController::MapEditorGhostPlatform).isPressed())
		loadGhost(GameObjectClassType::PLATFORM);

	if (fKey.getKeyGroup(KeyController::MapEditorGhostPoint).wasToggled() && fKey.getKeyGroup(KeyController::MapEditorGhostPoint).isPressed())
		loadGhost(GameObjectClassType::POINT);
}

void MapEditor::handleMouse()
{
	//Mouse
	if (!fIsLmbPressed && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) 
	{
		fIsLmbPressed = true;

		switch (fMode) {
			case MapEditor::None:
				selectObject();
				break;
			case MapEditor::Resize:
				if (fSelectedObject == nullptr) 
					selectObject();

				if (fSelectedObject != nullptr && fSelectedObject->getGlobalBounds().contains(fFrame.getMousePosition(Frame::FrameLayer::MapArea)))
				{
					fResizeObject = true;
				}

				break;
			case MapEditor::Move:
				if (fSelectedObject == nullptr)
					selectObject();
			

				if (fSelectedObject != nullptr && fSelectedObject->getGlobalBounds().contains(fFrame.getMousePosition(Frame::FrameLayer::MapArea))) 
				{
					fLastMouseOffset = fSelectedObject->getPosition() - fFrame.getMousePosition(Frame::FrameLayer::MapArea);
					fMoveObject = true;
				}
				break;
			case MapEditor::Ghost:
				if (fGhost != nullptr) 
				{
					fMap.addGameObject(fGhost);
					fGhost = nullptr;
				}
				break;
			default:
				break;
		}
	}

	if (fIsLmbPressed && !sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) 
	{
		fIsLmbPressed = false;
		fCloned = false;
		fResizeObject = false;
		fMoveObject = false;
		fSelectedObject = nullptr;
	}
}

void MapEditor::handleActions()
{
	if (fSelectedObject != nullptr) 
	{
		switch (fMode)
		{
			case MapEditor::Resize:
				fSelectedObject->resize(fFrame.getMousePosition(Frame::FrameLayer::MapArea), fSnapToGrid, fVerticalLock, fHorizontalLock);
				break;
			case MapEditor::Move:
				fSelectedObject->setPosition(fFrame.getMousePosition(Frame::FrameLayer::MapArea) + fLastMouseOffset, fSnapToGrid, fVerticalLock, fHorizontalLock);
				break;
			default:
				break;
		}

	}

	if (fGhost != nullptr) 
	{
		fGhost->setPosition(fFrame.getMousePosition(Frame::FrameLayer::MapArea));
		fGhost->draw();
	}
}

void MapEditor::selectObject() 
{
	for (GameObject * obj : fMap.getGameObjects()) 
	{
		if (obj->getGlobalBounds().contains(Frame::getInstance().getMousePosition(Frame::FrameLayer::MapArea))) 
		{
			fSelectedObject = obj;
		}
	}
}

void MapEditor::loadGhost(const GameObjectClassType & type)
{
	fSelectedObject = nullptr;
	if (fGhost != nullptr) 
	{
		delete fGhost;
	}

	switch (type)
	{
		case GameObjectClassType::PLAYER:
			fGhost = new Player(&fMap);
			break;
		case GameObjectClassType::PLATFORM:
			fGhost = new Platform(&fMap);
			break;
		case GameObjectClassType::POINT:
			fGhost = new Point(&fMap);
			break;
		default:
			break;
	}

	if (fGhost != nullptr)
	{
		fMode = EditorMode::Ghost;
	}
}