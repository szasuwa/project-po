#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include "../Interface/MapEditorInterface.h"
#include "../Serialization/Serializable.h"
#include "../Objects/Bases/GameObject.h"
#include "../Objects/Actors/Player.h"
#include "../Objects/Map/Platform.h"
#include "../Objects/Map/Point.h"
#include "Level.h"
#include "MapEditorItem.h"


class MapEditor {
	enum EditorMode {
		None = 0,
		Resize = 1,
		Move = 2,
		Ghost = 3
	};
	Level *fLevel;
	sf::RenderWindow &fWindow;
	MapEditorItem* fGhost = nullptr;
	Serializable::CLASS_TYPE fGhostType = Serializable::CLASS_TYPE::NONE;
	sf::Vector2i fLastMousePosition;

	GameObject* fSelectedObject = nullptr;
	EditorMode fMode;

	bool fIsLmbPressed = false;
	bool fIsGhostPressed = false;
	bool fMoveObject = false;
	bool fResizeObject = false;
	bool fIsVerticalLockPressed = false;
	bool fVerticalLock = false;
	bool fIsHorizontalLockPressed = false;
	bool fHorizontalLock = false;
	bool fAxisLockUpdated = false;

	void loadGhost(Serializable::CLASS_TYPE type);
	void selectObject();
	void resizeObject();
	void moveObject();
	void clearMap();

public:
	explicit MapEditor(Level *lvl, sf::RenderWindow &wdw);

	void handleEditorControls();
	void setLevel(Level *lvl);
	MapEditorItem* getGhost();
};