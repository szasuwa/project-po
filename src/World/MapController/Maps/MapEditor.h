#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include "../../InputController/MouseController.h"
#include "Map.h"
#include "../../InterfaceController/ViewGroups/MapEditorControlsViewGroup.h"
#include "PortalLink.h"

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
	KeyController & fKey;
	Frame & fFrame;

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
	void handleGrid();
	void handleModeSelection();
	void handleDeletion();
	void handleClone();
	void handleAxes();
	void handleGhost();
	void handleMouse();
	void handleActions();
	void handleLinking();
	void handlePortalLinks();

	//Edition actions
	void loadGhost(const GameObjectClassType & type);
	GameObject * selectObject();

public:
	explicit MapEditor();

	Map * loadMap(const Map & map);
	
	void update();
	void draw();
};