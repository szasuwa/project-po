#include "MapEditor.h"

MapEditor::MapEditor(GameEngineInterface & m) : fMap(m)
{
	UIInterface& ui = m.getUIInterface();
	ui.setProperty((unsigned int)InterfaceType::MapEditor, MapEditorPropertyMap::VerticalLock, fVerticalLock ? "On" : "Off");
	ui.setProperty((unsigned int)InterfaceType::MapEditor, MapEditorPropertyMap::HorizontalLock, fHorizontalLock ? "On" : "Off");
	ui.setProperty((unsigned int)InterfaceType::MapEditor, MapEditorPropertyMap::GridSnap, fSnapToGrid ? "On" : "Off");
}

Map * MapEditor::loadMap(const Map & map)
{
	fMap = map;
	fGrid.update(fMap.getBoundaries());
	return &fMap;
}

void MapEditor::update(GameEngineInterface& f)
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

void MapEditor::draw(GameEngineInterface& f)
{
	f.getFrameInterface().draw(fGrid, Frame::FrameLayer::GameArea);

	handlePortalLinks(f);

	if(fGhost != nullptr)
		fGhost->draw(f);
}

void MapEditor::handleGrid(GameEngineInterface& f)
{	
	float dTime = f.getFrameInterface().getFrameTime();
	float gridSize = MapGrid::getGridDisplaySize();

	sf::Vector2f cam;
	InputInterface & input = f.getInputInterface();

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

void MapEditor::handleModeSelection(GameEngineInterface& f)
{
	InputInterface& input = f.getInputInterface();

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

void MapEditor::handleDeletion(GameEngineInterface& f)
{
	InputInterface& input = f.getInputInterface();
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

void MapEditor::handleClone(GameEngineInterface& f)
{
	InputInterface& input = f.getInputInterface();
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

			case GameObjectClassType::TEXT_BOX:
				temp = new TextBox(*(TextBox*)fSelectedObject);
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

void MapEditor::handleAxes(GameEngineInterface& f)
{
	InputInterface& input = f.getInputInterface();
	UIInterface& ui = f.getUIInterface();

	//Axis Locking and Grid Snapping
	if (input.wasKeyToggled((unsigned int)KeyBindingIndex::MapEditorVLock, true))
	{
		fVerticalLock = !fVerticalLock;
		ui.setProperty((unsigned int)InterfaceType::MapEditor, MapEditorPropertyMap::VerticalLock, fVerticalLock ? "On" : "Off");
	}

	if (input.wasKeyToggled((unsigned int)KeyBindingIndex::MapEditorHLock, true))
	{
		fHorizontalLock = !fHorizontalLock;
		ui.setProperty((unsigned int)InterfaceType::MapEditor, MapEditorPropertyMap::HorizontalLock, fHorizontalLock ? "On" : "Off");
	}

	if (input.wasKeyToggled((unsigned int)KeyBindingIndex::MapEditorGridLock, true))
	{
		fSnapToGrid = !fSnapToGrid;
		ui.setProperty((unsigned int)InterfaceType::MapEditor, MapEditorPropertyMap::GridSnap, fSnapToGrid ? "On" : "Off");
	}
}

void MapEditor::handleGhost(GameEngineInterface& f)
{
	InputInterface& input = f.getInputInterface();
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

void MapEditor::handleMouse(GameEngineInterface& f)
{	
	InputInterface& input = f.getInputInterface();
	FrameInterface& frame = f.getFrameInterface();
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

void MapEditor::handleActions(GameEngineInterface& f)
{
	FrameInterface& frame = f.getFrameInterface();
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

void MapEditor::handleLinking(GameEngineInterface& f)
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

void MapEditor::handlePortalLinks(GameEngineInterface& f)
{
	FrameInterface& frame = f.getFrameInterface();
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

GameObject * MapEditor::selectObject(GameEngineInterface& f)
{
	FrameInterface& frame = f.getFrameInterface();
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