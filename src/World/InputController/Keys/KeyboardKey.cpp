#include "KeyboardKey.h"

void KeyboardKey::update() {
	Key::update();
	switch (fKey)
	{
		case InputKey::A:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
			break;

		case InputKey::B:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::B);
			break;

		case InputKey::C:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::C);
			break;

		case InputKey::D:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
			break;

		case InputKey::E:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::E);
			break;

		case InputKey::F:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::F);
			break;

		case InputKey::G:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::G);
			break;

		case InputKey::H:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::H);
			break;

		case InputKey::I:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::I);
			break;

		case InputKey::J:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::J);
			break;

		case InputKey::K:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::K);
			break;

		case InputKey::L:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::L);
			break;

		case InputKey::M:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::M);
			break;

		case InputKey::N:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::N);
			break;

		case InputKey::O:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::O);
			break;

		case InputKey::P:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::P);
			break;

		case InputKey::Q:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
			break;

		case InputKey::R:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::R);
			break;

		case InputKey::S:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
			break;

		case InputKey::T:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::T);
			break;

		case InputKey::U:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::U);
			break;

		case InputKey::V:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::V);
			break;

		case InputKey::W:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
			break;

		case InputKey::X:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::X);
			break;

		case InputKey::Y:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Y);
			break;

		case InputKey::Z:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
			break;

		case InputKey::Num0:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Num0);
			break;

		case InputKey::Num1:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Num1);
			break;

		case InputKey::Num2:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Num2);
			break;

		case InputKey::Num3:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Num3);
			break;

		case InputKey::Num4:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Num4);
			break;

		case InputKey::Num5:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Num5);
			break;

		case InputKey::Num6:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Num6);
			break;

		case InputKey::Num7:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Num7);
			break;

		case InputKey::Num8:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Num8);
			break;

		case InputKey::Num9:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Num9);
			break;

		case InputKey::Escape:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
			break;

		case InputKey::LControl:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl);
			break;

		case InputKey::LShift:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
			break;

		case InputKey::LAlt:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt);
			break;

		case InputKey::LSystem:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LSystem);
			break;

		case InputKey::RControl:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::RControl);
			break;

		case InputKey::RShift:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);
			break;

		case InputKey::RAlt:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt);
			break;

		case InputKey::RSystem:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::RSystem);
			break;

		case InputKey::Menu:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Menu);
			break;

		case InputKey::LBracket:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LBracket);
			break;

		case InputKey::RBracket:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::RBracket);
			break;

		case InputKey::SemiColon:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::SemiColon);
			break;

		case InputKey::Comma:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Comma);
			break;

		case InputKey::Period:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Period);
			break;

		case InputKey::Quote:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Quote);
			break;

		case InputKey::Slash:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Slash);
			break;

		case InputKey::BackSlash:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::BackSlash);
			break;

		case InputKey::Tilde:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Tilde);
			break;

		case InputKey::Equal:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Equal);
			break;

		case InputKey::Dash:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Dash);
			break;

		case InputKey::Space:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
			break;

		case InputKey::Return:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Return);
			break;

		case InputKey::BackSpace:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace);
			break;

		case InputKey::Tab:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Tab);
			break;

		case InputKey::PageUp:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp);
			break;

		case InputKey::PageDown:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown);
			break;

		case InputKey::End:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::End);
			break;

		case InputKey::Home:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Home);
			break;

		case InputKey::Insert:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Insert);
			break;

		case InputKey::Delete:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Delete);
			break;

		case InputKey::Add:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Add);
			break;

		case InputKey::Subtract:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract);
			break;

		case InputKey::Multiply:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Multiply);
			break;

		case InputKey::Divide:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Divide);
			break;

		case InputKey::Left:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
			break;

		case InputKey::Right:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
			break;

		case InputKey::Up:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
			break;

		case InputKey::Down:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
			break;

		case InputKey::Numpad0:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0);
			break;

		case InputKey::Numpad1:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1);
			break;

		case InputKey::Numpad2:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2);
			break;

		case InputKey::Numpad3:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3);
			break;

		case InputKey::Numpad4:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4);
			break;

		case InputKey::Numpad5:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5);
			break;

		case InputKey::Numpad6:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6);
			break;

		case InputKey::Numpad7:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7);
			break;

		case InputKey::Numpad8:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8);
			break;

		case InputKey::Numpad9:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9);
			break;

		case InputKey::F1:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::F1);
			break;

		case InputKey::F2:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::F2);
			break;

		case InputKey::F3:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::F3);
			break;

		case InputKey::F4:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::F4);
			break;

		case InputKey::F5:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::F5);
			break;

		case InputKey::F6:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::F6);
			break;

		case InputKey::F7:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::F7);
			break;

		case InputKey::F8:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::F8);
			break;

		case InputKey::F9:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::F9);
			break;

		case InputKey::F10:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::F10);
			break;

		case InputKey::F11:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::F11);
			break;

		case InputKey::F12:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::F12);
			break;

		case InputKey::F13:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::F13);
			break;

		case InputKey::F14:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::F14);
			break;

		case InputKey::F15:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::F15);
			break;

		case InputKey::Pause:
			fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Pause);
			break;

		default:
			break;
	}
}