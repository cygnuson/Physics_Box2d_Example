#pragma once

#include <mutex>
#include <thread>
#include <iostream>
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
//this is an object interface
class BObject {
public:
	BObject(b2World* parent, float& scale);
	void SetPosition(float x, float y);
	void SetDynamic();
	void SetStatic();
	void SetType(b2BodyType type);
	void SetDensity(float density);
	void SetFriction(float friction);
	void SetBouncyness(float restitution);
	void SetAsBox(float w, float h);
	void SetAsCircle(float radius);
	std::shared_ptr<b2Shape> GetBox2DShape();
	virtual b2Body* GetBody();
	virtual void Update()=0;
	virtual void Draw(sf::RenderWindow& window)=0;
protected:
	enum Type {
		Polygon = 1,
		Circle = 2,
	};
	std::mutex bodyLock;
	BObject::Type type;
	bool bodyCreated = false;
	std::shared_ptr<b2Shape> shape;
	void CreateBody(b2World* world);
	float& scale;
	b2World* parent;
	b2Body* body;
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	friend class BoxWorld;
};

