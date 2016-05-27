
#include "Object.hpp"

BObject::BObject(b2World* parent, float& scale)
	:parent(parent), scale(scale)
{

}

void BObject::SetPosition(float x, float y)
{
	float positionX = x / scale;
	float positionY = y / scale;
	bodyDef.position.Set(positionX, positionY);
}

void BObject::SetDynamic()
{
	bodyDef.type = b2_dynamicBody;
}

void BObject::SetStatic()
{
	bodyDef.type = b2_staticBody;
}

void BObject::SetType(b2BodyType type)
{
	bodyDef.type = type;
}

void BObject::SetDensity(float density)
{
	fixtureDef.density = density;
}

void BObject::SetFriction(float friction)
{
	fixtureDef.friction = friction;
}

void BObject::SetBouncyness(float restitution)
{
	fixtureDef.restitution = restitution;
}

void BObject::SetAsBox(float w, float h)
{
	type = Type::Polygon;
	auto localShape = std::make_shared<b2PolygonShape>();
	shape = localShape;
	localShape->SetAsBox(w / 2 / scale, h / 2 / scale); //w/2 and h/2 are distance from center to edges.
}

void BObject::SetAsCircle(float radius)
{
	type = Type::Circle;
	auto localShape = std::make_shared<b2CircleShape>();
	shape = localShape;
	localShape->m_p.Set(0,0);
	localShape->m_radius = radius/scale;
}

std::shared_ptr<b2Shape> BObject::GetBox2DShape()
{
	return shape;
}

b2Body * BObject::GetBody()
{
	return body;
}

void BObject::CreateBody(b2World * world)
{
	//std::lock_guard<std::mutex> lock(bodyLock);
	body = world->CreateBody(&bodyDef);
	fixtureDef.shape = shape.get();
	body->CreateFixture(&fixtureDef);
	bodyCreated = true;
}
