#include "InputController.h"

InputController::InputController()
{
	fKeyBindings[(unsigned int)KeyBindingIndex::LeftClick] = new MouseKey((InputKey)KeyBinding::LeftClick);
	fKeyBindings[(unsigned int)KeyBindingIndex::CameraLeft] = new KeyboardKey((InputKey)KeyBinding::CameraLeft);
	fKeyBindings[(unsigned int)KeyBindingIndex::CameraRight] = new KeyboardKey((InputKey)KeyBinding::CameraRight);
	fKeyBindings[(unsigned int)KeyBindingIndex::CameraUp] = new KeyboardKey((InputKey)KeyBinding::CameraUp);
	fKeyBindings[(unsigned int)KeyBindingIndex::CameraDown] = new KeyboardKey((InputKey)KeyBinding::CameraDown);
	fKeyBindings[(unsigned int)KeyBindingIndex::MoveLeft] = new KeyboardKey((InputKey)KeyBinding::MoveLeft);
	fKeyBindings[(unsigned int)KeyBindingIndex::MoveRight] = new KeyboardKey((InputKey)KeyBinding::MoveRight);
	fKeyBindings[(unsigned int)KeyBindingIndex::Jump] = new KeyboardKey((InputKey)KeyBinding::Jump);
	fKeyBindings[(unsigned int)KeyBindingIndex::Debug] = new KeyboardKey((InputKey)KeyBinding::Debug);
	fKeyBindings[(unsigned int)KeyBindingIndex::ResetMap] = new KeyboardKey((InputKey)KeyBinding::ResetMap);
	fKeyBindings[(unsigned int)KeyBindingIndex::MapEditor] = new KeyboardKey((InputKey)KeyBinding::MapEditor);
	fKeyBindings[(unsigned int)KeyBindingIndex::MapEditorTime] = new KeyboardKey((InputKey)KeyBinding::MapEditorTime);
	fKeyBindings[(unsigned int)KeyBindingIndex::MapEditorMove] = new KeyboardKey((InputKey)KeyBinding::MapEditorMove);
	fKeyBindings[(unsigned int)KeyBindingIndex::MapEditorResize] = new KeyboardKey((InputKey)KeyBinding::MapEditorResize);
	fKeyBindings[(unsigned int)KeyBindingIndex::MapEditorVLock] = new KeyboardKey((InputKey)KeyBinding::MapEditorVLock);
	fKeyBindings[(unsigned int)KeyBindingIndex::MapEditorHLock] = new KeyboardKey((InputKey)KeyBinding::MapEditorHLock);
	fKeyBindings[(unsigned int)KeyBindingIndex::MapEditorGridLock] = new KeyboardKey((InputKey)KeyBinding::MapEditorGridLock);
	fKeyBindings[(unsigned int)KeyBindingIndex::MapEditorDelete] = new KeyboardKey((InputKey)KeyBinding::MapEditorDelete);
	fKeyBindings[(unsigned int)KeyBindingIndex::MapEditorClone] = new KeyboardKey((InputKey)KeyBinding::MapEditorClone);
	fKeyBindings[(unsigned int)KeyBindingIndex::MapEditorLinkPortal] = new KeyboardKey((InputKey)KeyBinding::MapEditorLinkPortal);
	fKeyBindings[(unsigned int)KeyBindingIndex::MapEditorGhostPlayer] = new KeyboardKey((InputKey)KeyBinding::MapEditorGhostPlayer);
	fKeyBindings[(unsigned int)KeyBindingIndex::MapEditorGhostPlatform] = new KeyboardKey((InputKey)KeyBinding::MapEditorGhostPlatform);
	fKeyBindings[(unsigned int)KeyBindingIndex::MapEditorGhostPoint] = new KeyboardKey((InputKey)KeyBinding::MapEditorGhostPoint);
	fKeyBindings[(unsigned int)KeyBindingIndex::MapEditorGhostPortal] = new KeyboardKey((InputKey)KeyBinding::MapEditorGhostPortal);
	fKeyBindings[(unsigned int)KeyBindingIndex::MapEditorGhostBox] = new KeyboardKey((InputKey)KeyBinding::MapEditorGhostBox);
	fKeyBindings[(unsigned int)KeyBindingIndex::MapEditorReset] = new KeyboardKey((InputKey)KeyBinding::MapEditorReset);
	fKeyBindings[(unsigned int)KeyBindingIndex::MapEditorSave] = new KeyboardKey((InputKey)KeyBinding::MapEditorSave);
	fKeyBindings[(unsigned int)KeyBindingIndex::MapEditorExit] = new KeyboardKey((InputKey)KeyBinding::MapEditorExit);
	fKeyBindings[(unsigned int)KeyBindingIndex::MapEditorCancel] = new KeyboardKey((InputKey)KeyBinding::MapEditorCancel);
}

InputController::~InputController()
{
	for (int i = 0; i < (unsigned int)KeyBindingIndex::num_values; ++i) {
		delete fKeyBindings[i];
	}
}

void InputController::update()
{
	for (int i = 0; i < (unsigned int)KeyBindingIndex::num_values; ++i) {
		fKeyBindings[i]->update();
	}

}
bool InputController::isKeyPressed(const unsigned int& key) const
{
	if (key >= (unsigned int)KeyBindingIndex::num_values)
		return false;

	return fKeyBindings[key]->isPressed();
}

bool InputController::wasKeyToggled(const unsigned int& key, const bool& desiredState) const
{
	if (key >= (unsigned int)KeyBindingIndex::num_values)
		return false;

	return fKeyBindings[key]->wasToggled(desiredState);
}