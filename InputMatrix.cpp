#include "InputMatrix.hpp"

#ifdef _DEBUG
#include <iostream>
#endif

InputMatrix::InputMatrix()
{
	ClearAll();
}

InputMatrix & InputMatrix::GetInstance()
{
	static InputMatrix im;
	return im;
}

void InputMatrix::ProcessEvent(sf::Event & ev)
{
		if (ev.type == sf::Event::KeyPressed&& ev.key.code != sf::Keyboard::Unknown && !IsPressed(ev.key.code)) {
			SetPressed(ev.key.code);
		}
		if (ev.type == sf::Event::KeyReleased && ev.key.code != sf::Keyboard::Unknown && IsPressed(ev.key.code)) {
			SetReleased(ev.key.code);
		}
	if (ev.type == sf::Event::MouseButtonPressed && !IsPressed(ev.mouseButton.button)) {
		SetPressed(ev.mouseButton.button);
	}
	if (ev.type == sf::Event::MouseButtonReleased && IsPressed(ev.mouseButton.button)) {
		SetReleased(ev.mouseButton.button);
	}
	if (ev.type == sf::Event::MouseMoved) {
		MouseMove(ev.mouseMove.x, ev.mouseMove.y);
	}
	if (ev.type == sf::Event::MouseWheelMoved) {
		WheelMove(ev.mouseWheel.delta);
	}
}

void InputMatrix::ClearAll()
{
	if (_DEBUG) {
		std::cout << "InputMatrix cleared.\n";
	}
	keys.fill(false);
	buttons.fill(false);
}

bool InputMatrix::operator[](sf::Keyboard::Key key)
{
	return keys[key];
}

bool InputMatrix::operator[](sf::Mouse::Button button)
{
	return buttons[button];
}
bool InputMatrix::IsPressed(sf::Keyboard::Key key, bool unpress)
{
	bool retValue = (*this)[key];
	if (retValue && unpress) {
		SetReleased(key);
	}
	return retValue;
}
bool InputMatrix::IsPressed(sf::Mouse::Button button, bool unpress)
{
	bool retValue = (*this)[button];
	if (retValue && unpress) {
		SetReleased(button);
	}
	return retValue;
}
void InputMatrix::SetPressed(sf::Keyboard::Key key)
{
	if (_DEBUG) {
		std::cout << GetKeyName(key) << " pressed.\n";
	}
	keys[key] = true;
}
void InputMatrix::SetPressed(sf::Mouse::Button button)
{
	if (_DEBUG) {
		std::cout << "Mouse button " << (int)button << " pressed @ (" << mouseState.X() << "," << mouseState.Y() << ").\n";
	}
	buttons[button] = true;
}
void InputMatrix::SetReleased(sf::Keyboard::Key key)
{
	if (_DEBUG) {
		std::cout << GetKeyName(key) << " released.\n";
	}
	keys[key] = false;
}
void InputMatrix::SetReleased(sf::Mouse::Button button)
{
	if (_DEBUG) {
		std::cout << "Mouse button " << (int)button << " released @ (" << mouseState.X() << ", " << mouseState.Y() << ").\n";
	}
	buttons[button] = false;
}

void InputMatrix::WheelMove(float dw)
{
	if (_DEBUG) {
		std::cout << "Mouse wheel moved by " << dw << ".\n";
	}
	mouseState.Wheel(dw);
}

void InputMatrix::MouseMove(float x, float y)
{
	mouseState.Set(x, y);
}

float InputMatrix::MouseX()
{
	return mouseState.X();
}

float InputMatrix::MouseY()
{
	return mouseState.Y();
}

float InputMatrix::MouseWheel()
{
	return mouseState.Wheel();
}

//This helper function is from BlackHC at the forum.  I have modified it.
std::string InputMatrix::GetKeyName(sf::Keyboard::Key key)
{
	switch (key) {
	default:
	case sf::Keyboard::Unknown:
		return std::string("Unknown");
	case sf::Keyboard::A:
		return std::string("A");
	case sf::Keyboard::B:
		return std::string("B");
	case sf::Keyboard::C:
		return std::string("C");
	case sf::Keyboard::D:
		return std::string("D");
	case sf::Keyboard::E:
		return std::string("E");
	case sf::Keyboard::F:
		return std::string("F");
	case sf::Keyboard::G:
		return std::string("G");
	case sf::Keyboard::H:
		return std::string("H");
	case sf::Keyboard::I:
		return std::string("I");
	case sf::Keyboard::J:
		return std::string("J");
	case sf::Keyboard::K:
		return std::string("K");
	case sf::Keyboard::L:
		return std::string("L");
	case sf::Keyboard::M:
		return std::string("M");
	case sf::Keyboard::N:
		return std::string("N");
	case sf::Keyboard::O:
		return std::string("O");
	case sf::Keyboard::P:
		return std::string("P");
	case sf::Keyboard::Q:
		return std::string("Q");
	case sf::Keyboard::R:
		return std::string("R");
	case sf::Keyboard::S:
		return std::string("S");
	case sf::Keyboard::T:
		return std::string("T");
	case sf::Keyboard::U:
		return std::string("U");
	case sf::Keyboard::V:
		return std::string("V");
	case sf::Keyboard::W:
		return std::string("W");
	case sf::Keyboard::X:
		return std::string("X");
	case sf::Keyboard::Y:
		return std::string("Y");
	case sf::Keyboard::Z:
		return std::string("Z");
	case sf::Keyboard::Num0:
		return std::string("Num0");
	case sf::Keyboard::Num1:
		return std::string("Num1");
	case sf::Keyboard::Num2:
		return std::string("Num2");
	case sf::Keyboard::Num3:
		return std::string("Num3");
	case sf::Keyboard::Num4:
		return std::string("Num4");
	case sf::Keyboard::Num5:
		return std::string("Num5");
	case sf::Keyboard::Num6:
		return std::string("Num6");
	case sf::Keyboard::Num7:
		return std::string("Num7");
	case sf::Keyboard::Num8:
		return std::string("Num8");
	case sf::Keyboard::Num9:
		return std::string("Num9");
	case sf::Keyboard::Escape:
		return std::string("Escape");
	case sf::Keyboard::LControl:
		return std::string("LControl");
	case sf::Keyboard::LShift:
		return std::string("LShift");
	case sf::Keyboard::LAlt:
		return std::string("LAlt");
	case sf::Keyboard::LSystem:
		return std::string("LSystem");
	case sf::Keyboard::RControl:
		return std::string("RControl");
	case sf::Keyboard::RShift:
		return std::string("RShift");
	case sf::Keyboard::RAlt:
		return std::string("RAlt");
	case sf::Keyboard::RSystem:
		return std::string("RSystem");
	case sf::Keyboard::Menu:
		return std::string("Menu");
	case sf::Keyboard::LBracket:
		return std::string("LBracket");
	case sf::Keyboard::RBracket:
		return std::string("RBracket");
	case sf::Keyboard::SemiColon:
		return std::string("SemiColon");
	case sf::Keyboard::Comma:
		return std::string("Comma");
	case sf::Keyboard::Period:
		return std::string("Period");
	case sf::Keyboard::Quote:
		return std::string("Quote");
	case sf::Keyboard::Slash:
		return std::string("Slash");
	case sf::Keyboard::BackSlash:
		return std::string("BackSlash");
	case sf::Keyboard::Tilde:
		return std::string("Tilde");
	case sf::Keyboard::Equal:
		return std::string("Equal");
	case sf::Keyboard::Dash:
		return std::string("Dash");
	case sf::Keyboard::Space:
		return std::string("Space");
	case sf::Keyboard::Return:
		return std::string("Return");
	case sf::Keyboard::BackSpace:
		return std::string("BackSpace");
	case sf::Keyboard::Tab:
		return std::string("Tab");
	case sf::Keyboard::PageUp:
		return std::string("PageUp");
	case sf::Keyboard::PageDown:
		return std::string("PageDown");
	case sf::Keyboard::End:
		return std::string("End");
	case sf::Keyboard::Home:
		return std::string("Home");
	case sf::Keyboard::Insert:
		return std::string("Insert");
	case sf::Keyboard::Delete:
		return std::string("Delete");
	case sf::Keyboard::Add:
		return std::string("Add");
	case sf::Keyboard::Subtract:
		return std::string("Subtract");
	case sf::Keyboard::Multiply:
		return std::string("Multiply");
	case sf::Keyboard::Divide:
		return std::string("Divide");
	case sf::Keyboard::Left:
		return std::string("Left");
	case sf::Keyboard::Right:
		return std::string("Right");
	case sf::Keyboard::Up:
		return std::string("Up");
	case sf::Keyboard::Down:
		return std::string("Down");
	case sf::Keyboard::Numpad0:
		return std::string("Numpad0");
	case sf::Keyboard::Numpad1:
		return std::string("Numpad1");
	case sf::Keyboard::Numpad2:
		return std::string("Numpad2");
	case sf::Keyboard::Numpad3:
		return std::string("Numpad3");
	case sf::Keyboard::Numpad4:
		return std::string("Numpad4");
	case sf::Keyboard::Numpad5:
		return std::string("Numpad5");
	case sf::Keyboard::Numpad6:
		return std::string("Numpad6");
	case sf::Keyboard::Numpad7:
		return std::string("Numpad7");
	case sf::Keyboard::Numpad8:
		return std::string("Numpad8");
	case sf::Keyboard::Numpad9:
		return std::string("Numpad9");
	case sf::Keyboard::F1:
		return std::string("F1");
	case sf::Keyboard::F2:
		return std::string("F2");
	case sf::Keyboard::F3:
		return std::string("F3");
	case sf::Keyboard::F4:
		return std::string("F4");
	case sf::Keyboard::F5:
		return std::string("F5");
	case sf::Keyboard::F6:
		return std::string("F6");
	case sf::Keyboard::F7:
		return std::string("F7");
	case sf::Keyboard::F8:
		return std::string("F8");
	case sf::Keyboard::F9:
		return std::string("F9");
	case sf::Keyboard::F10:
		return std::string("F10");
	case sf::Keyboard::F11:
		return std::string("F11");
	case sf::Keyboard::F12:
		return std::string("F12");
	case sf::Keyboard::F13:
		return std::string("F13");
	case sf::Keyboard::F14:
		return std::string("F14");
	case sf::Keyboard::F15:
		return std::string("F15");
	case sf::Keyboard::Pause:
		return std::string("Pause");
	}
}

void MouseState::Set(float x, float y)
{
	X(x);
	Y(y);
}

float MouseState::X() {
	return mouseX;
}
float MouseState::DX() {
	return dx;
}
float MouseState::DY() {
	return dy;
}
float MouseState::Y() {
	return mouseY;
}
float MouseState::Wheel() {
	return wheelAxisY;
}
float MouseState::X(float newX) {
	dx = -((mouseX)-(newX));
	mouseX = newX;
	return mouseX;
}
float MouseState::Y(float newY) {
	dy = -((mouseY)-(newY));
	mouseY = newY;
	return mouseY;
}
float MouseState::Wheel(float newWheel) {
	auto old = wheelAxisY;
	wheelAxisY = newWheel;
	return old;
}