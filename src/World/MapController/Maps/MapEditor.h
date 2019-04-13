#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include "Map.h"
#include "../../InterfaceController/InterfaceGroups/MapEditorInterface.h"

class MapController;

class MapEditor {
	enum EditorMode {
		None = 0,
		Resize = 1,
		Move = 2,
		Ghost = 3
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

	bool fIsLmbPressed = false;
	bool fCloned = false;
	bool fMoveObject = false;
	bool fResizeObject = false;
	bool fVerticalLock = false;
	bool fHorizontalLock = false;
	
	//Grid
	MapGrid fGrid;
	bool fSnapToGrid = true;

	//Handlers
	void handleGrid();
	void handleModeSelection();
	void handleDeletion();
	void handleClone();
	void handleAxes();
	void handleGhost();
	void handleMouse();
	void handleActions();

	//Edition actions
	void loadGhost(const GameObjectClassType & type);
	void selectObject();

public:
	explicit MapEditor();

	Map * loadMap(const Map & map);
	
	void update();
};