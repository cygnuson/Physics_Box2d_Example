#include "BoxWorld.hpp"

void BoxWorld::Initialize()
{
	gravity = std::make_shared<b2Vec2>(0.f, 9.8f);
	world = std::make_shared<b2World>(*gravity);
}

BoxWorld::BoxWorld(float& scale)
	:scale(scale)
{
	Initialize();
}

BoxWorld::~BoxWorld()
{
	while (!spriteList.empty()) {
		spriteList.pop_back();
	}
}

b2World * BoxWorld::GetWorld()
{
	return world.get();
}

void BoxWorld::DrawAll(sf::RenderWindow & window)
{
	for (auto& sprite : spriteList) {
		sprite->Update();
		sprite->Draw(window);
	}
}

void BoxWorld::AddObject(std::shared_ptr<BObject> boxSprite)
{
	//std::lock_guard<std::mutex> listLock(listMutex);
	boxSprite->CreateBody(world.get());
	spriteList.push_back(boxSprite);
}


