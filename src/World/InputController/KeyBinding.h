#pragma once
#include "../Interfaces/InputKey.h"


enum class KeyBinding : unsigned int {
	LeftClick					= (unsigned int)InputKey::LMB,
	CameraLeft					= (unsigned int)InputKey::Left,
	CameraRight					= (unsigned int)InputKey::Right,
	CameraUp					= (unsigned int)InputKey::Up,
	CameraDown					= (unsigned int)InputKey::Down,
	MoveLeft					= (unsigned int)InputKey::A,
	MoveRight					= (unsigned int)InputKey::D,
	Jump						= (unsigned int)InputKey::Space,
	Debug						= (unsigned int)InputKey::F3,
	ResetMap					= (unsigned int)InputKey::R,
	MapEditor					= (unsigned int)InputKey::F2,
	MapEditorTime				= (unsigned int)InputKey::F1,
	MapEditorMove				= (unsigned int)InputKey::LControl,
	MapEditorResize				= (unsigned int)InputKey::LShift,
	MapEditorVLock				= (unsigned int)InputKey::Q,
	MapEditorHLock				= (unsigned int)InputKey::E,
	MapEditorGridLock			= (unsigned int)InputKey::Tab,
	MapEditorDelete				= (unsigned int)InputKey::Delete,
	MapEditorClone				= (unsigned int)InputKey::C,
	MapEditorLinkPortal			= (unsigned int)InputKey::L,
	MapEditorGhostPlayer		= (unsigned int)InputKey::Num1,
	MapEditorGhostPlatform		= (unsigned int)InputKey::Num2,
	MapEditorGhostPoint			= (unsigned int)InputKey::Num3,
	MapEditorGhostPortal		= (unsigned int)InputKey::Num4,
	MapEditorGhostBox			= (unsigned int)InputKey::Num5,
	MapEditorGhostExitPortal	= (unsigned int)InputKey::Num6,
	MapEditorReset				= (unsigned int)InputKey::F5,
	MapEditorSave				= (unsigned int)InputKey::F6,
	MapEditorExit				= (unsigned int)InputKey::F8,
	MapEditorCancel				= (unsigned int)InputKey::F9
};