#pragma once
#include "../Objects/Bases/GameObject.h"
#include "Level.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include "../Serialization/Serializable.h"

class MapEditor {
	enum EditorMode {
		None = 0,
		Resize = 1,
		Move = 2,
		Select = 3
	};
	Level *fLevel;
	sf::RenderWindow &fWindow;
	sf::Drawable* fGhost;
	Serializable::CLASS_TYPE fGhostType = Serializable::CLASS_TYPE::NONE;
	sf::Vector2i fLastMousePosition;

	GameObject* fSelectedObject = nullptr;
	EditorMode fMode;

	bool fIsLmbPressed = false;
	bool fMoveObject = false;
	bool fResizeObject = false;

	void loadGhost();
	void selectObject();
	void resizeObject();
	void moveObject();
	void clearMap();

public:
	explicit MapEditor(Level *lvl, sf::RenderWindow &wdw);

	void handleEditorControls();
	void setLevel(Level *lvl);
};