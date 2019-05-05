#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include "Map.h"
#include "PortalLink.h"
#include "../../Interfaces/MapInterface.h"
#include "../../InputController/KeyBindingIndex.h"

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
	void handleGrid(MapInterface& f);
	void handleModeSelection(MapInterface& f);
	void handleDeletion(MapInterface& f);
	void handleClone(MapInterface& f);
	void handleAxes(MapInterface& f);
	void handleGhost(MapInterface& f);
	void handleMouse(MapInterface& f);
	void handleActions(MapInterface& f);
	void handleLinking(MapInterface& f);
	void handlePortalLinks(MapInterface& f);

	//Edition actions
	void loadGhost(const GameObjectClassType & type);
	GameObject * selectObject(MapInterface& f);

public:
	explicit MapEditor(MapInterface & f);

	Map * loadMap(const Map & map);
	
	void update(MapInterface& f);
	void draw(MapInterface& f);
};