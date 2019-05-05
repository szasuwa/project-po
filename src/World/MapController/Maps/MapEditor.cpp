#include "MapEditor.h"

MapEditor::MapEditor(MapInterface & m) : fMap(m)
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

void MapEditor::update(MapInterface& f)
{
	handleGrid(f);
	handleModeSelection(f);
	handleDeletion(f);
	handleClone(f);
	handleAxes(f);
	handleGhost(f);
	handleMouse(f);
	handleActions(f);
}

void MapEditor::draw(MapInterface& f)
{
	f.getFrame().draw(fGrid, Frame::FrameLayer::GameArea);

	handlePortalLinks(f);

	if(fGhost != nullptr)
		fGhost->draw(f);
}

void MapEditor::handleGrid(MapInterface& f)
{	
	float dTime = f.getFrame().getFrameTime();
	float gridSize = MapGrid::getGridDisplaySize();

	sf::Vector2f cam;
	InputInterface & input = f.getInput();

	if (input.isKeyPressed((unsigned int)KeyBindingIndex::CameraLeft))
		cam.x -= gridSize * 120 * dTime;

	if (input.isKeyPressed((unsigned int)KeyBindingIndex::CameraRight))
		cam.x += gridSize * 120 * dTime;

	if (input.isKeyPressed((unsigned int)KeyBindingIndex::CameraUp))
		cam.y -= gridSize * 120 * dTime;

	if (input.isKeyPressed((unsigned int)KeyBindingIndex::CameraDown))
		cam.y += gridSize * 120 * dTime;

	fMap.moveCamera(f, cam);
}

void MapEditor::handleModeSelection(MapInterface& f)
{
	InputInterface& input = f.getInput();

	if (input.isKeyPressed((unsigned int)KeyBindingIndex::MapEditorMove) || fMoveObject)
		fMode = EditorMode::Move;
	else if (input.isKeyPressed((unsigned int)KeyBindingIndex::MapEditorResize) || fResizeObject)
		fMode = EditorMode::Resize;
	else if (input.isKeyPressed((unsigned int)KeyBindingIndex::MapEditorLinkPortal) || fLinkObject)
		fMode = EditorMode::Link;
	else if (fGhost != nullptr)
		fMode = EditorMode::Ghost;
	else
		fMode = EditorMode::None;
}

void MapEditor::handleDeletion(MapInterface& f)
{
	InputInterface& input = f.getInput();
	if (input.isKeyPressed((unsigned int)KeyBindingIndex::MapEditorDelete))
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

void MapEditor::handleClone(MapInterface& f)
{
	InputInterface& input = f.getInput();
	if (fSelectedObject != nullptr && !fCloned && input.isKeyPressed((unsigned int)KeyBindingIndex::MapEditorClone))
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
				((Portal*)temp)->onFocus(f);
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

	if (fCloned && !input.isKeyPressed((unsigned int)KeyBindingIndex::MapEditorClone))
		fCloned = !fCloned;
}

void MapEditor::handleAxes(MapInterface& f)
{
	InputInterface& input = f.getInput();
	//Axis Locking and Grid Snapping
	if (input.wasKeyToggled((unsigned int)KeyBindingIndex::MapEditorVLock, true))
	{
		fVerticalLock = !fVerticalLock;
		//MapEditorControlsViewGroup::reportAxisLockStatus(fVerticalLock, fHorizontalLock);
	}

	if (input.wasKeyToggled((unsigned int)KeyBindingIndex::MapEditorHLock, true))
	{
		fHorizontalLock = !fHorizontalLock;
		//MapEditorControlsViewGroup::reportAxisLockStatus(fVerticalLock, fHorizontalLock);
	}

	if (input.wasKeyToggled((unsigned int)KeyBindingIndex::MapEditorGridLock, true))
	{
		fSnapToGrid = !fSnapToGrid;
		//MapEditorControlsViewGroup::reportGridSnapStatus(fSnapToGrid);
	}
}

void MapEditor::handleGhost(MapInterface& f)
{
	InputInterface& input = f.getInput();
	if (input.wasKeyToggled((unsigned int)KeyBindingIndex::MapEditorGhostPlayer, true))
		loadGhost(GameObjectClassType::PLAYER);

	if (input.wasKeyToggled((unsigned int)KeyBindingIndex::MapEditorGhostPlatform, true))
		loadGhost(GameObjectClassType::PLATFORM);

	if (input.wasKeyToggled((unsigned int)KeyBindingIndex::MapEditorGhostPoint, true))
		loadGhost(GameObjectClassType::POINT);

	if (input.wasKeyToggled((unsigned int)KeyBindingIndex::MapEditorGhostPortal, true))
		loadGhost(GameObjectClassType::PORTAL);

	if (input.wasKeyToggled((unsigned int)KeyBindingIndex::MapEditorGhostBox, true))
		loadGhost(GameObjectClassType::BOX);

}

void MapEditor::handleMouse(MapInterface& f)
{	
	InputInterface& input = f.getInput();
	FrameInterface& frame = f.getFrame();
	if (input.wasKeyToggled((unsigned int)KeyBindingIndex::LeftClick, true))
	{
		switch (fMode) {
			case EditorMode::None:
				fSelectedObject = selectObject(f);
				break;
			case EditorMode::Resize:
				if (fSelectedObject == nullptr) 
					fSelectedObject = selectObject(f);

				if (fSelectedObject != nullptr && fSelectedObject->getGlobalBounds().contains(frame.getMousePosition(Frame::FrameLayer::GameArea)))
				{
					fResizeObject = true;
				}

				break;
			case EditorMode::Move:
				if (fSelectedObject == nullptr)
					fSelectedObject = selectObject(f);
			

				if (fSelectedObject != nullptr && fSelectedObject->getGlobalBounds().contains(frame.getMousePosition(Frame::FrameLayer::GameArea))) 
				{
					fLastMouseOffset = fSelectedObject->getPosition() - frame.getMousePosition(Frame::FrameLayer::GameArea);
					fMoveObject = true;
				}
				break;
			case EditorMode::Link:
				if (fSelectedObject == nullptr)
					fSelectedObject = selectObject(f);

				if (fSelectedObject != nullptr && fSelectedObject->getGlobalBounds().contains(frame.getMousePosition(Frame::FrameLayer::GameArea)))
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

	if (input.wasKeyToggled((unsigned int)KeyBindingIndex::LeftClick, false))
	{
		handleLinking(f);
		fLinkObject = false;

		fCloned = false;
		fResizeObject = false;
		fMoveObject = false;
		fSelectedObject = nullptr;
	}
}

void MapEditor::handleActions(MapInterface& f)
{
	FrameInterface& frame = f.getFrame();
	if (fSelectedObject != nullptr) 
	{
		switch (fMode)
		{
			case EditorMode::Resize:
				fSelectedObject->resize(frame.getMousePosition(Frame::FrameLayer::GameArea), fSnapToGrid, fVerticalLock, fHorizontalLock);
				break;
			case EditorMode::Move:
				fSelectedObject->setPosition(frame.getMousePosition(Frame::FrameLayer::GameArea) + fLastMouseOffset, fSnapToGrid, fVerticalLock, fHorizontalLock);
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

				fLink->update(fSelectedObject->getCenter(), frame.getMousePosition(Frame::FrameLayer::GameArea));
			default:
				break;
		}

	}

	if (fGhost != nullptr) 
	{
		fGhost->setPosition(frame.getMousePosition(Frame::FrameLayer::GameArea));
	}
}

void MapEditor::handleLinking(MapInterface& f)
{
	if (!fLinkObject)
		return;

	if (fLink != nullptr)
	{
		delete fLink;
		fLink = nullptr;
	}

	if(fSelectedObject != nullptr && fSelectedObject->getClassType() == GameObjectClassType::PORTAL)
		((Portal*)fSelectedObject)->setLink(selectObject(f));
}

void MapEditor::handlePortalLinks(MapInterface& f)
{
	FrameInterface& frame = f.getFrame();
	for (GameObject* obj : fMap.getGameObjects())
	{
		if (obj != nullptr && obj->getClassType() == GameObjectClassType::PORTAL)
		{
			GameObject* linkDest = ((Portal*)obj)->getLink();
			if (linkDest != nullptr)
			{
				frame.draw(PortalLink(obj->getCenter(), linkDest->getCenter()), Frame::FrameLayer::GameArea);
			}
		}
	}

	if (fLink != nullptr)
		frame.draw(*fLink, Frame::FrameLayer::GameArea);
}

GameObject * MapEditor::selectObject(MapInterface& f)
{
	FrameInterface& frame = f.getFrame();
	for (GameObject * obj : fMap.getGameObjects()) 
	{
		if (obj != nullptr && obj->getGlobalBounds().contains(frame.getMousePosition(Frame::FrameLayer::GameArea))) 
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