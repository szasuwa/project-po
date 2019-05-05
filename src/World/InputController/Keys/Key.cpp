#include "Key.h"


Key::Key(const InputKey& key):fKey(key)
{
}

void Key::update()
{
	fWasPressed = fIsPressed;
	fIsPressed = false;
}

bool Key::isPressed() const
{
	return fIsPressed;
}

bool Key::wasToggled(const bool& desiredState) const
{
	return (fIsPressed != fWasPressed & fIsPressed == desiredState);
}

const std::string Key::toString() const
{
	return Key::toString(fKey);
}

const std::string Key::toString(InputKey fKey)
{
	switch (fKey) {
	default:
	case InputKey::Unknown:
		return "Unknown";
	case InputKey::LMB:
		return "LMB";
	case InputKey::MMB:
		return "MMB";
	case InputKey::RMB:
		return "RMB";
	case InputKey::A:
		return "A";
	case InputKey::B:
		return "B";
	case InputKey::C:
		return "C";
	case InputKey::D:
		return "D";
	case InputKey::E:
		return "E";
	case InputKey::F:
		return "F";
	case InputKey::G:
		return "G";
	case InputKey::H:
		return "H";
	case InputKey::I:
		return "I";
	case InputKey::J:
		return "J";
	case InputKey::K:
		return "K";
	case InputKey::L:
		return "L";
	case InputKey::M:
		return "M";
	case InputKey::N:
		return "N";
	case InputKey::O:
		return "O";
	case InputKey::P:
		return "P";
	case InputKey::Q:
		return "Q";
	case InputKey::R:
		return "R";
	case InputKey::S:
		return "S";
	case InputKey::T:
		return "T";
	case InputKey::U:
		return "U";
	case InputKey::V:
		return "V";
	case InputKey::W:
		return "W";
	case InputKey::X:
		return "X";
	case InputKey::Y:
		return "Y";
	case InputKey::Z:
		return "Z";
	case InputKey::Num0:
		return "Num0";
	case InputKey::Num1:
		return "Num1";
	case InputKey::Num2:
		return "Num2";
	case InputKey::Num3:
		return "Num3";
	case InputKey::Num4:
		return "Num4";
	case InputKey::Num5:
		return "Num5";
	case InputKey::Num6:
		return "Num6";
	case InputKey::Num7:
		return "Num7";
	case InputKey::Num8:
		return "Num8";
	case InputKey::Num9:
		return "Num9";
	case InputKey::Escape:
		return "Escape";
	case InputKey::LControl:
		return "LControl";
	case InputKey::LShift:
		return "LShift";
	case InputKey::LAlt:
		return "LAlt";
	case InputKey::LSystem:
		return "LSystem";
	case InputKey::RControl:
		return "RControl";
	case InputKey::RShift:
		return "RShift";
	case InputKey::RAlt:
		return "RAlt";
	case InputKey::RSystem:
		return "RSystem";
	case InputKey::Menu:
		return "Menu";
	case InputKey::LBracket:
		return "LBracket";
	case InputKey::RBracket:
		return "RBracket";
	case InputKey::SemiColon:
		return "SemiColon";
	case InputKey::Comma:
		return "Comma";
	case InputKey::Period:
		return "Period";
	case InputKey::Quote:
		return "Quote";
	case InputKey::Slash:
		return "Slash";
	case InputKey::BackSlash:
		return "BackSlash";
	case InputKey::Tilde:
		return "Tilde";
	case InputKey::Equal:
		return "Equal";
	case InputKey::Dash:
		return "Dash";
	case InputKey::Space:
		return "Space";
	case InputKey::Return:
		return "Return";
	case InputKey::BackSpace:
		return "BackSpace";
	case InputKey::Tab:
		return "Tab";
	case InputKey::PageUp:
		return "PageUp";
	case InputKey::PageDown:
		return "PageDown";
	case InputKey::End:
		return "End";
	case InputKey::Home:
		return "Home";
	case InputKey::Insert:
		return "Insert";
	case InputKey::Delete:
		return "Delete";
	case InputKey::Add:
		return "Add";
	case InputKey::Subtract:
		return "Subtract";
	case InputKey::Multiply:
		return "Multiply";
	case InputKey::Divide:
		return "Divide";
	case InputKey::Left:
		return "Left";
	case InputKey::Right:
		return "Right";
	case InputKey::Up:
		return "Up";
	case InputKey::Down:
		return "Down";
	case InputKey::Numpad0:
		return "Numpad0";
	case InputKey::Numpad1:
		return "Numpad1";
	case InputKey::Numpad2:
		return "Numpad2";
	case InputKey::Numpad3:
		return "Numpad3";
	case InputKey::Numpad4:
		return "Numpad4";
	case InputKey::Numpad5:
		return "Numpad5";
	case InputKey::Numpad6:
		return "Numpad6";
	case InputKey::Numpad7:
		return "Numpad7";
	case InputKey::Numpad8:
		return "Numpad8";
	case InputKey::Numpad9:
		return "Numpad9";
	case InputKey::F1:
		return "F1";
	case InputKey::F2:
		return "F2";
	case InputKey::F3:
		return "F3";
	case InputKey::F4:
		return "F4";
	case InputKey::F5:
		return "F5";
	case InputKey::F6:
		return "F6";
	case InputKey::F7:
		return "F7";
	case InputKey::F8:
		return "F8";
	case InputKey::F9:
		return "F9";
	case InputKey::F10:
		return "F10";
	case InputKey::F11:
		return "F11";
	case InputKey::F12:
		return "F12";
	case InputKey::F13:
		return "F13";
	case InputKey::F14:
		return "F14";
	case InputKey::F15:
		return "F15";
	case InputKey::Pause:
		return "Pause";
	}
}