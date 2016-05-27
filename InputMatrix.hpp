#pragma once

#include <SFML\Graphics.hpp>
#include <array>
#include <cmath>

struct MouseState {
	void Set(float x, float y);
	float X();
	float DX();
	float DY();
	float Y();
	float Wheel();
	float X(float newX);
	float Y(float newY);
	float Wheel(float newWheel);
	float mouseY = 0;
	float mouseX = 0;
	float dx = 0;
	float dy = 0;
	float wheelAxisY = 0;
};

class InputMatrix {
public:
	std::string GetKeyName(sf::Keyboard::Key key);
	static InputMatrix& GetInstance();
	void ProcessEvent(sf::Event& ev);
	void ClearAll();
	//keyboard
	bool operator[](sf::Keyboard::Key key);
	bool IsPressed(sf::Keyboard::Key key, bool unpress = false);
	void SetPressed(sf::Keyboard::Key key);
	void SetReleased(sf::Keyboard::Key key);
	//mouse
	bool operator[](sf::Mouse::Button button);
	bool IsPressed(sf::Mouse::Button button, bool unpress = false);
	void SetPressed(sf::Mouse::Button button);
	void SetReleased(sf::Mouse::Button button);
	void WheelMove(float dw);
	void MouseMove(float x, float y);
	float MouseWheel();
	float MouseX();
	float MouseY();
private:
	InputMatrix();
	//prevent all copy, assignment and moves.
	InputMatrix(const InputMatrix& other) = delete;
	InputMatrix(const InputMatrix&& other) = delete;
	void operator=(const InputMatrix& other) = delete;
	void operator=(const InputMatrix&& other) = delete;

	std::array<bool, sf::Keyboard::KeyCount> keys;
	std::array<bool, sf::Mouse::ButtonCount> buttons;
	MouseState mouseState;
};