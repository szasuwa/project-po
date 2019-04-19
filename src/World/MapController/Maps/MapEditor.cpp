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

void MapEditor::update()
{
	handleGrid();
	handleModeSelection();
	handleDeletion();
	handleClone();
	handleAxes();
	handleGhost();
	handleMouse();
	handleActions();
}

void MapEditor::draw()
{
	fFrame.draw(fGrid, Frame::FrameLayer::MapArea);

	handlePortalLinks();

	if(fGhost != nullptr)
		fGhost->draw();
}

void MapEditor::handleGrid() 
{	
	float dTime = fFrame.getFrameTime();
	float gridSize = MapGrid::getGridDisplaySize();

	sf::Vector2f cam;

	if (fKey.getKeyGroup(KeyBinding::CameraLeft).isPressed())
		cam.x -= gridSize * 120 * dTime;

	if (fKey.getKeyGroup(KeyBinding::CameraRight).isPressed())
		cam.x += gridSize * 120 * dTime;

	if (fKey.getKeyGroup(KeyBinding::CameraUp).isPressed())
		cam.y -= gridSize * 120 * dTime;

	if (fKey.getKeyGroup(KeyBinding::CameraDown).isPressed())
		cam.y += gridSize * 120 * dTime;

	fMap.moveCamera(cam);
}

void MapEditor::handleModeSelection()
{
	if (fKey.getKeyGroup(KeyBinding::MapEditorMove).isPressed() || fMoveObject)
		fMode = EditorMode::Move;
	else if (fKey.getKeyGroup(KeyBinding::MapEditorResize).isPressed() || fResizeObject)
		fMode = EditorMode::Resize;
	else if (fKey.getKeyGroup(KeyBinding::MapEditorLinkPortal).isPressed() || fLinkObject)
		fMode = EditorMode::Link;
	else if (fGhost != nullptr)
		fMode = EditorMode::Ghost;
	else
		fMode = EditorMode::None;
}

void MapEditor::handleDeletion()
{
	if (fKey.getKeyGroup(KeyBinding::MapEditorDelete).isPressed())
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

		if (fLink != nullptr)
		{
			delete fLink;
			fLink = nullptr;
		}
	}
}

void MapEditor::handleClone()
{
	if (fSelectedObject != nullptr && !fCloned && fKey.getKeyGroup(KeyBinding::MapEditorClone).isPressed())
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
			case GameObjectClassType::PORTAL:
				temp = new Portal(*(Portal*)fSelectedObject);
				break;
			case GameObjectClassType::BOX:
				temp = new Box(*(Box*)fSelectedObject);
				break;
			default:
				return;
		}
		fSelectedObject = temp;
		fMap.addGameObject(fSelectedObject);
		fMoveObject = true;
	}

	if (fCloned && fKey.getKeyGroup(KeyBinding::MapEditorClone).isReleased())
		fCloned = !fCloned;
}

void MapEditor::handleAxes()
{
	//Axis Locking and Grid Snapping
	if (fKey.getKeyGroup(KeyBinding::MapEditorVLock).wasToggled() && fKey.getKeyGroup(KeyBinding::MapEditorVLock).isPressed())
	{
		fVerticalLock = !fVerticalLock;
		MapEditorInterface::reportAxisLockStatus(fVerticalLock, fHorizontalLock);
	}

	if (fKey.getKeyGroup(KeyBinding::MapEditorHLock).wasToggled() && fKey.getKeyGroup(KeyBinding::MapEditorHLock).isPressed())
	{
		fHorizontalLock = !fHorizontalLock;
		MapEditorInterface::reportAxisLockStatus(fVerticalLock, fHorizontalLock);
	}

	if (fKey.getKeyGroup(KeyBinding::MapEditorGridLock).wasToggled() && fKey.getKeyGroup(KeyBinding::MapEditorGridLock).isPressed())
	{
		fSnapToGrid = !fSnapToGrid;
		MapEditorInterface::reportGridSnapStatus(fSnapToGrid);
	}
}

void MapEditor::handleGhost()
{
	if (fKey.getKeyGroup(KeyBinding::MapEditorGhostPlayer).wasToggled() && fKey.getKeyGroup(KeyBinding::MapEditorGhostPlayer).isPressed())
		loadGhost(GameObjectClassType::PLAYER);

	if (fKey.getKeyGroup(KeyBinding::MapEditorGhostPlatform).wasToggled() && fKey.getKeyGroup(KeyBinding::MapEditorGhostPlatform).isPressed())
		loadGhost(GameObjectClassType::PLATFORM);

	if (fKey.getKeyGroup(KeyBinding::MapEditorGhostPoint).wasToggled() && fKey.getKeyGroup(KeyBinding::MapEditorGhostPoint).isPressed())
		loadGhost(GameObjectClassType::POINT);

	if (fKey.getKeyGroup(KeyBinding::MapEditorGhostPortal).wasToggled() && fKey.getKeyGroup(KeyBinding::MapEditorGhostPortal).isPressed())
		loadGhost(GameObjectClassType::PORTAL);

	if (fKey.getKeyGroup(KeyBinding::MapEditorGhostBox).wasToggled() && fKey.getKeyGroup(KeyBinding::MapEditorGhostBox).isPressed())
		loadGhost(GameObjectClassType::BOX);

}

void MapEditor::handleMouse()
{
	//Mouse
	if (!fIsLmbPressed && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) 
	{
		fIsLmbPressed = true;

		switch (fMode) {
			case EditorMode::None:
				fSelectedObject = selectObject();
				break;
			case EditorMode::Resize:
				if (fSelectedObject == nullptr) 
					fSelectedObject = selectObject();

				if (fSelectedObject != nullptr && fSelectedObject->getGlobalBounds().contains(fFrame.getMousePosition(Frame::FrameLayer::MapArea)))
				{
					fResizeObject = true;
				}

				break;
			case EditorMode::Move:
				if (fSelectedObject == nullptr)
					fSelectedObject = selectObject();
			

				if (fSelectedObject != nullptr && fSelectedObject->getGlobalBounds().contains(fFrame.getMousePosition(Frame::FrameLayer::MapArea))) 
				{
					fLastMouseOffset = fSelectedObject->getPosition() - fFrame.getMousePosition(Frame::FrameLayer::MapArea);
					fMoveObject = true;
				}
				break;
			case EditorMode::Link:
				if (fSelectedObject == nullptr)
					fSelectedObject = selectObject();

				if (fSelectedObject != nullptr && fSelectedObject->getGlobalBounds().contains(fFrame.getMousePosition(Frame::FrameLayer::MapArea)))
				{
					fLinkObject = true;
				}
				break;
			case EditorMode::Ghost:
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
		handleLinking();
		fLinkObject = false;

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
			case EditorMode::Resize:
				fSelectedObject->resize(fFrame.getMousePosition(Frame::FrameLayer::MapArea), fSnapToGrid, fVerticalLock, fHorizontalLock);
				break;
			case EditorMode::Move:
				fSelectedObject->setPosition(fFrame.getMousePosition(Frame::FrameLayer::MapArea) + fLastMouseOffset, fSnapToGrid, fVerticalLock, fHorizontalLock);
				break;
			case EditorMode::Link:
				if (fSelectedObject == nullptr || fSelectedObject->getClassType() != GameObjectClassType::PORTAL)
				{
					if (fLink != nullptr)
					{
						delete fLink;
						fLink = nullptr;
					}
					fLinkObject = false;
					break;
				}

				if (((Portal*)fSelectedObject)->getLink() != nullptr)
					((Portal*)fSelectedObject)->setLink(nullptr);

				if (fLink == nullptr)
					fLink = new  PortalLink();

				fLink->update(fSelectedObject->getCenter(), Frame::getInstance().getMousePosition(Frame::FrameLayer::MapArea));
			default:
				break;
		}

	}

	if (fGhost != nullptr) 
	{
		fGhost->setPosition(fFrame.getMousePosition(Frame::FrameLayer::MapArea));
	}
}

void MapEditor::handleLinking()
{
	if (!fLinkObject)
		return;

	if (fLink != nullptr)
	{
		delete fLink;
		fLink = nullptr;
	}

	if(fSelectedObject != nullptr && fSelectedObject->getClassType() == GameObjectClassType::PORTAL)
		((Portal*)fSelectedObject)->setLink(selectObject());
}

void MapEditor::handlePortalLinks()
{
	for (GameObject* obj : fMap.getGameObjects())
	{
		if (obj != nullptr && obj->getClassType() == GameObjectClassType::PORTAL)
		{
			GameObject* linkDest = ((Portal*)obj)->getLink();
			if (linkDest != nullptr)
			{
				fFrame.draw(PortalLink(obj->getCenter(), linkDest->getCenter()), Frame::FrameLayer::MapArea);
			}
		}
	}

	if (fLink != nullptr)
		fFrame.draw(*fLink, Frame::FrameLayer::MapArea);
}

GameObject * MapEditor::selectObject()
{
	for (GameObject * obj : fMap.getGameObjects()) 
	{
		if (obj != nullptr && obj->getGlobalBounds().contains(Frame::getInstance().getMousePosition(Frame::FrameLayer::MapArea))) 
		{
			return obj;
		}
	}
	return nullptr;
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
		case GameObjectClassType::PORTAL:
			fGhost = new Portal(&fMap);
			break;
		case GameObjectClassType::BOX:
			fGhost = new Box(&fMap);
			break;
		default:
			break;
	}

	if (fGhost != nullptr)
	{
		fMode = EditorMode::Ghost;
	}
}