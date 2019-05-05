#include "MapEditor.h"

MapEditor::MapEditor(MapInterface & m) : fMapInterface(m), fInput(fMapInterface.getInput()), fFrame(fMapInterface.getFrame()), fMap(fMapInterface)
{
	//MapEditorControlsViewGroup::reportAxisLockStatus(fVerticalLock, fHorizontalLock);
	//MapEditorControlsViewGroup::reportGridSnapStatus(fSnapToGrid);
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
	fFrame.draw(fGrid, Frame::FrameLayer::GameArea);

	handlePortalLinks();

	if(fGhost != nullptr)
		fGhost->draw();
}

void MapEditor::handleGrid() 
{	
	float dTime = fFrame.getFrameTime();
	float gridSize = MapGrid::getGridDisplaySize();

	sf::Vector2f cam;

	if (fInput.isKeyPressed((unsigned int)KeyBindingIndex::CameraLeft))
		cam.x -= gridSize * 120 * dTime;

	if (fInput.isKeyPressed((unsigned int)KeyBindingIndex::CameraRight))
		cam.x += gridSize * 120 * dTime;

	if (fInput.isKeyPressed((unsigned int)KeyBindingIndex::CameraUp))
		cam.y -= gridSize * 120 * dTime;

	if (fInput.isKeyPressed((unsigned int)KeyBindingIndex::CameraDown))
		cam.y += gridSize * 120 * dTime;

	fMap.moveCamera(cam);
}

void MapEditor::handleModeSelection()
{
	if (fInput.isKeyPressed((unsigned int)KeyBindingIndex::MapEditorMove) || fMoveObject)
		fMode = EditorMode::Move;
	else if (fInput.isKeyPressed((unsigned int)KeyBindingIndex::MapEditorResize) || fResizeObject)
		fMode = EditorMode::Resize;
	else if (fInput.isKeyPressed((unsigned int)KeyBindingIndex::MapEditorLinkPortal) || fLinkObject)
		fMode = EditorMode::Link;
	else if (fGhost != nullptr)
		fMode = EditorMode::Ghost;
	else
		fMode = EditorMode::None;
}

void MapEditor::handleDeletion()
{
	if (fInput.isKeyPressed((unsigned int)KeyBindingIndex::MapEditorDelete))
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
	if (fSelectedObject != nullptr && !fCloned && fInput.isKeyPressed((unsigned int)KeyBindingIndex::MapEditorClone))
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
				((Portal*)temp)->onFocus();
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

	if (fCloned && !fInput.isKeyPressed((unsigned int)KeyBindingIndex::MapEditorClone))
		fCloned = !fCloned;
}

void MapEditor::handleAxes()
{
	//Axis Locking and Grid Snapping
	if (fInput.wasKeyToggled((unsigned int)KeyBindingIndex::MapEditorVLock, true))
	{
		fVerticalLock = !fVerticalLock;
		//MapEditorControlsViewGroup::reportAxisLockStatus(fVerticalLock, fHorizontalLock);
	}

	if (fInput.wasKeyToggled((unsigned int)KeyBindingIndex::MapEditorHLock, true))
	{
		fHorizontalLock = !fHorizontalLock;
		//MapEditorControlsViewGroup::reportAxisLockStatus(fVerticalLock, fHorizontalLock);
	}

	if (fInput.wasKeyToggled((unsigned int)KeyBindingIndex::MapEditorGridLock, true))
	{
		fSnapToGrid = !fSnapToGrid;
		//MapEditorControlsViewGroup::reportGridSnapStatus(fSnapToGrid);
	}
}

void MapEditor::handleGhost()
{
	if (fInput.wasKeyToggled((unsigned int)KeyBindingIndex::MapEditorGhostPlayer, true))
		loadGhost(GameObjectClassType::PLAYER);

	if (fInput.wasKeyToggled((unsigned int)KeyBindingIndex::MapEditorGhostPlatform, true))
		loadGhost(GameObjectClassType::PLATFORM);

	if (fInput.wasKeyToggled((unsigned int)KeyBindingIndex::MapEditorGhostPoint, true))
		loadGhost(GameObjectClassType::POINT);

	if (fInput.wasKeyToggled((unsigned int)KeyBindingIndex::MapEditorGhostPortal, true))
		loadGhost(GameObjectClassType::PORTAL);

	if (fInput.wasKeyToggled((unsigned int)KeyBindingIndex::MapEditorGhostBox, true))
		loadGhost(GameObjectClassType::BOX);

}

void MapEditor::handleMouse()
{	
	if (fInput.wasKeyToggled((unsigned int)KeyBindingIndex::LeftClick, true))
	{
		switch (fMode) {
			case EditorMode::None:
				fSelectedObject = selectObject();
				break;
			case EditorMode::Resize:
				if (fSelectedObject == nullptr) 
					fSelectedObject = selectObject();

				if (fSelectedObject != nullptr && fSelectedObject->getGlobalBounds().contains(fFrame.getMousePosition(Frame::FrameLayer::GameArea)))
				{
					fResizeObject = true;
				}

				break;
			case EditorMode::Move:
				if (fSelectedObject == nullptr)
					fSelectedObject = selectObject();
			

				if (fSelectedObject != nullptr && fSelectedObject->getGlobalBounds().contains(fFrame.getMousePosition(Frame::FrameLayer::GameArea))) 
				{
					fLastMouseOffset = fSelectedObject->getPosition() - fFrame.getMousePosition(Frame::FrameLayer::GameArea);
					fMoveObject = true;
				}
				break;
			case EditorMode::Link:
				if (fSelectedObject == nullptr)
					fSelectedObject = selectObject();

				if (fSelectedObject != nullptr && fSelectedObject->getGlobalBounds().contains(fFrame.getMousePosition(Frame::FrameLayer::GameArea)))
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

	if (fInput.wasKeyToggled((unsigned int)KeyBindingIndex::LeftClick, false))
	{
		handleLinking();
		fLinkObject = false;

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
				fSelectedObject->resize(fFrame.getMousePosition(Frame::FrameLayer::GameArea), fSnapToGrid, fVerticalLock, fHorizontalLock);
				break;
			case EditorMode::Move:
				fSelectedObject->setPosition(fFrame.getMousePosition(Frame::FrameLayer::GameArea) + fLastMouseOffset, fSnapToGrid, fVerticalLock, fHorizontalLock);
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

				fLink->update(fSelectedObject->getCenter(), fFrame.getMousePosition(Frame::FrameLayer::GameArea));
			default:
				break;
		}

	}

	if (fGhost != nullptr) 
	{
		fGhost->setPosition(fFrame.getMousePosition(Frame::FrameLayer::GameArea));
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
				fFrame.draw(PortalLink(obj->getCenter(), linkDest->getCenter()), Frame::FrameLayer::GameArea);
			}
		}
	}

	if (fLink != nullptr)
		fFrame.draw(*fLink, Frame::FrameLayer::GameArea);
}

GameObject * MapEditor::selectObject()
{
	for (GameObject * obj : fMap.getGameObjects()) 
	{
		if (obj != nullptr && obj->getGlobalBounds().contains(fFrame.getMousePosition(Frame::FrameLayer::GameArea))) 
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
			fGhost = new Player(fMapInterface, &fMap);
			break;
		case GameObjectClassType::PLATFORM:
			fGhost = new Platform(fMapInterface, &fMap);
			break;
		case GameObjectClassType::POINT:
			fGhost = new Point(fMapInterface, &fMap);
			break;
		case GameObjectClassType::PORTAL:
			fGhost = new Portal(fMapInterface, &fMap);
			break;
		case GameObjectClassType::BOX:
			fGhost = new Box(fMapInterface, &fMap);
			break;
		default:
			break;
	}

	if (fGhost != nullptr)
	{
		fMode = EditorMode::Ghost;
	}
}