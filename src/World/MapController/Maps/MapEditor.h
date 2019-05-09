#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include "Map.h"
#include "PortalLink.h"
#include "../../Interfaces/MapInterface.h"
#include "../../InputController/KeyBindingIndex.h"
#include "../../UIController/ViewProperties.h"

class MapController;

class MapEditor {
	enum class EditorMode {
		None = 0,
		Resize = 1,
		Move = 2,
		Ghost = 3,
		Link = 4
	};

	//Map and windows
	Map fMap;

	//Ghost
	GameObject * fGhost = nullptr;

	//Edition modes
	sf::Vector2f fLastMouseOffset;

	GameObject * fSelectedObject = nullptr;
	EditorMode fMode;

	bool fCloned = false;
	bool fMoveObject = false;
	bool fResizeObject = false;
	bool fLinkObject = false;
	bool fVerticalLock = false;
	bool fHorizontalLock = false;
	
	//Grid
	MapGrid fGrid;
	bool fSnapToGrid = true;

	//Link
	PortalLink *fLink = nullptr;

	//Handlers
	void handleGrid(GameEngineInterface& f);
	void handleModeSelection(GameEngineInterface& f);
	void handleDeletion(GameEngineInterface& f);
	void handleClone(GameEngineInterface& f);
	void handleAxes(GameEngineInterface& f);
	void handleGhost(GameEngineInterface& f);
	void handleMouse(GameEngineInterface& f);
	void handleActions(GameEngineInterface& f);
	void handleLinking(GameEngineInterface& f);
	void handlePortalLinks(GameEngineInterface& f);

	//Edition actions
	void loadGhost(const GameObjectClassType & type);
	GameObject * selectObject(GameEngineInterface& f);

public:
	explicit MapEditor(GameEngineInterface & f);

	Map * loadMap(const Map & map);
	
	void update(GameEngineInterface& f);
	void draw(GameEngineInterface& f);
};