#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "TextureManager.hpp"
#include "InputMatrix.hpp"
#include "PhysGui.hpp"
#include "SFMLObject.hpp"
#include "BoxWorld.hpp"

class SGBGame {
public:
	SGBGame();
	SGBGame(unsigned int width, unsigned int height, unsigned int x, unsigned int y);
	void StartLoop();
	void HandleEvents(sf::Event& event);
	void CreateShape(float x, float y, float width_radius, float height_pointcount);
	void ShowGround();
private:
	std::shared_ptr<sf::View> view;
	float holdX = 0;
	float holdY = 0;
	bool holding = false;
	std::shared_ptr<sf::CircleShape> holdCircle;
	std::shared_ptr<sf::RectangleShape> holdRect;
	float FPS = 60.f;
	float scale = 30.f;
	float width, height;
	std::shared_ptr<BoxWorld> world;
	PhysGui gui;
	sf::RenderWindow window;
	TextureManager& texMan;
	InputMatrix& inputMatrix;
};