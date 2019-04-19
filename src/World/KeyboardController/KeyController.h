#pragma once
#include "KeyGroup.h"
#include "KeyBinding.h"


class KeyController {
private:
	static KeyController * instance;

	std::vector<KeyGroup> fKeyBindings = std::vector<KeyGroup>{
		KeyGroup({sf::Keyboard::Key::Left}),									//CameraLeft
		KeyGroup({sf::Keyboard::Key::Right}),									//CameraRight
		KeyGroup({sf::Keyboard::Key::Up}),										//CameraUp
		KeyGroup({sf::Keyboard::Key::Down}),									//CameraDown
		KeyGroup({sf::Keyboard::Key::A}),										//MoveLeft
		KeyGroup({sf::Keyboard::Key::D}),										//MoveRight
		KeyGroup({sf::Keyboard::Key::W, sf::Keyboard::Key::Space}),				//Jump
		KeyGroup({sf::Keyboard::Key::F3}),										//Debug
		KeyGroup({sf::Keyboard::Key::R}),										//ResetMap,
		KeyGroup({sf::Keyboard::Key::F2}),										//MapEditor
		KeyGroup({sf::Keyboard::Key::F1}),										//MapEditorTime
		KeyGroup({sf::Keyboard::Key::LControl, sf::Keyboard::Key::RControl}),	//MapEditorMove
		KeyGroup({sf::Keyboard::Key::LShift, sf::Keyboard::Key::RShift}),		//MapEditorResize
		KeyGroup({sf::Keyboard::Key::Q}),										//MapEditorVLock
		KeyGroup({sf::Keyboard::Key::E}),										//MapEditorHLock
		KeyGroup({sf::Keyboard::Key::Tab}),										//MapEditorGridLock
		KeyGroup({sf::Keyboard::Key::Delete}),									//MapEditorDelete
		KeyGroup({sf::Keyboard::Key::LAlt, sf::Keyboard::Key::RAlt}),			//MapEditorClone
		KeyGroup({sf::Keyboard::Key::L}),										//MapEditorLinkPortal
		KeyGroup({sf::Keyboard::Key::Num1, sf::Keyboard::Key::Numpad1}),		//MapEditorGhostPlayer
		KeyGroup({sf::Keyboard::Key::Num2, sf::Keyboard::Key::Numpad2}),		//MapEditorGhostPlatform
		KeyGroup({sf::Keyboard::Key::Num3, sf::Keyboard::Key::Numpad3}),		//MapEditorGhostPoint
		KeyGroup({sf::Keyboard::Key::Num4, sf::Keyboard::Key::Numpad4}),		//MapEditorGhostPortal
		KeyGroup({sf::Keyboard::Key::Num5, sf::Keyboard::Key::Numpad5}),		//MapEditorGhostBox
		KeyGroup({sf::Keyboard::Key::F5}),										//MapEditorReset
		KeyGroup({sf::Keyboard::Key::F6}),										//MapEditorSave
		KeyGroup({sf::Keyboard::Key::F8}),										//MapEditorExit
		KeyGroup({sf::Keyboard::Key::F9})										//MapEditorCancel
	};

	KeyController();
	KeyController(const KeyController & o);

public:
	static KeyController & getInstance();
	KeyGroup & getKeyGroup(const KeyBinding & key);
};