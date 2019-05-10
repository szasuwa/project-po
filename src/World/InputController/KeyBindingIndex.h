#pragma once
#include "../Interfaces/InputKey.h"
#include "Keys/MouseKey.h"

enum class KeyBindingIndex : unsigned int {
	LeftClick,
	CameraLeft,
	CameraRight,
	CameraUp,
	CameraDown,
	MoveLeft,
	MoveRight,
	Jump,
	Debug,
	ResetMap,
	MapEditor,
	MapEditorTime,
	MapEditorMove,
	MapEditorResize,
	MapEditorVLock,
	MapEditorHLock,
	MapEditorGridLock,
	MapEditorDelete,
	MapEditorClone,
	MapEditorLinkPortal,
	MapEditorGhostPlayer,
	MapEditorGhostPlatform,
	MapEditorGhostPoint,
	MapEditorGhostPortal,
	MapEditorGhostBox,
	MapEditorGhostExitPortal,
	MapEditorReset,
	MapEditorSave,
	MapEditorExit,
	MapEditorCancel,
	num_values
};