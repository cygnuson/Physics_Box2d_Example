#pragma once

#include <vector>
#include <memory>
#include <thread>
#include <mutex>
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include "Object.hpp"
//this class is a world that will keep track of various box2d stuff
class BoxWorld {
private:
	void Initialize();
	std::mutex listMutex;
	std::vector<std::shared_ptr<BObject>> spriteList;
	std::shared_ptr<b2Vec2> gravity;
	std::shared_ptr<b2World> world;
	b2Body* worldBody = nullptr;
	float& scale; //the pixel/meter conversion factor.
public:
	BoxWorld(float& scale);
	~BoxWorld();
	template<typename...Vargs>
	void Step(const Vargs&...args);
	b2World* GetWorld();
	void DrawAll(sf::RenderWindow& window);
	void AddObject(std::shared_ptr<BObject> sprite);
};

template<typename ...Vargs>
inline void BoxWorld::Step(const Vargs&...args)
{
	world->Step(std::move(args)...);
}
