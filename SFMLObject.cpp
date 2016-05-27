
#include "SFMLObject.hpp"

SFMLSpriteObject::SFMLSpriteObject(b2World* parent, float& scale,
	const std::string & textureName, sf::IntRect textureRect)
	:BObject(parent, scale), textureName(textureName), textureRect(textureRect)
{
	sprite->setTexture(TextureManager::GetInstance().GetTexture(textureName));
	sprite->setTextureRect(textureRect);
}

void SFMLSpriteObject::Update()
{
	sprite->setOrigin(textureRect.width / 2, textureRect.height / 2);
	sprite->setPosition(scale* body->GetPosition().x, scale* body->GetPosition().y);
	sprite->setRotation(body->GetAngle() * (180 / b2_pi));
}

void SFMLSpriteObject::Draw(sf::RenderWindow & window)
{

}
sf::Sprite & SFMLSpriteObject::GetSprite()
{
	return *sprite;
}
//------------------------------Shape Objectss------------------------------------------------------------------------
SFMLShapeObject::SFMLShapeObject(b2World* parent, float& scale)
	:BObject(parent, scale)
{

}

void SFMLShapeObject::Update()
{

}

void SFMLShapeObject::Draw(sf::RenderWindow & window)
{
	window.draw(*GetShape());
}

std::shared_ptr<sf::Shape> SFMLShapeObject::GetShape()
{
	return shape;
}

SFMLConvexShapeObject::SFMLConvexShapeObject(b2World * parent,
	float & scale, std::size_t pointCount)
	:SFMLShapeObject(parent, scale), pointCount(pointCount)
{
	shape = std::make_shared<sf::ConvexShape>(pointCount);
}

void SFMLConvexShapeObject::Update()
{
	//shape->setOrigin(radius,radius);
	shape->setPosition(scale* body->GetPosition().x, scale* body->GetPosition().y);
	shape->setRotation(body->GetAngle() * (180 / b2_pi));
}

SFMLRectangleShapeObject::SFMLRectangleShapeObject(b2World * parent,
	float & scale, float x, float y)
	:SFMLShapeObject(parent, scale), size({ x,y })
{
	shape = std::make_shared<sf::RectangleShape>(size);
	SetAsBox(size.x, size.y);
	shape->setOrigin(size.x / 2, size.y / 2);
}

void SFMLRectangleShapeObject::Update()
{
	shape->setPosition(scale* body->GetPosition().x, scale* body->GetPosition().y);
	shape->setRotation(body->GetAngle() * (180 / b2_pi));
}

SFMLCircleShapeObject::SFMLCircleShapeObject(b2World * parent, float & scale,
	float radius, std::size_t pointCount)
	:SFMLShapeObject(parent, scale), radius(radius), pointCount(pointCount)
{
	shape = std::make_shared<sf::CircleShape>(radius, pointCount);
	SetAsCircle(radius);
	shape->setOrigin(radius, radius);
	line = std::make_shared<sf::RectangleShape>(sf::Vector2f(radius, 1));
	//line->setOrigin(radius, radius);
}

void SFMLCircleShapeObject::Draw(sf::RenderWindow& window) {
	window.draw(*shape);
	window.draw(*line);
}

std::shared_ptr<sf::RectangleShape> SFMLCircleShapeObject::GetLine()
{
	return line;
}

void SFMLCircleShapeObject::Update()
{
	shape->setPosition(scale* body->GetPosition().x, scale* body->GetPosition().y);
	shape->setRotation(body->GetAngle() * (180 / b2_pi));
	line->setRotation(body->GetAngle() * (180 / b2_pi));
	line->setPosition(scale* body->GetPosition().x, scale* body->GetPosition().y);
	if (bodyCreated) {
		//std::cout << "Circle is at (" << body->GetPosition().x << "," << body->GetPosition().y << ")\n";
	}
}

//-----------------------------------------Factories--------------------------------------------------------------
const b2BodyType Factory::ObjectDefinition::b2Type::Dynamic = b2_dynamicBody;
const b2BodyType Factory::ObjectDefinition::b2Type::Static = b2_staticBody;
const b2BodyType Factory::ObjectDefinition::b2Type::Kinematic = b2_kinematicBody;

namespace Factory {
	std::shared_ptr<SFMLRectangleShapeObject> MakeRect(const ShapeDefinition& def) {
		auto box = std::make_shared<SFMLRectangleShapeObject>(def.parent, def.scale, def.width, def.height);
		box->GetShape()->setOutlineColor(def.outlineColor);
		box->GetShape()->setFillColor(def.fillColor);
		box->GetShape()->setOutlineThickness(def.outlineThickness);
		box->SetPosition(def.worldX, def.worldY);
		box->SetType(def.type);
		box->SetDensity(def.density);
		box->SetBouncyness(def.bouncyness);
		box->SetFriction(def.friction);
		return box;
	}
	std::shared_ptr<SFMLCircleShapeObject> MakeCircle(const ShapeDefinition& def) {
		auto circle = std::make_shared<SFMLCircleShapeObject>(def.parent, def.scale, def.radius, def.pointCount);
		circle->GetShape()->setOutlineColor(def.outlineColor);
		circle->GetShape()->setFillColor(def.fillColor);
		circle->GetShape()->setOutlineThickness(def.outlineThickness);
		circle->GetLine()->setOutlineColor(sf::Color::Black);
		circle->GetLine()->setFillColor(sf::Color::Black);
		circle->SetPosition(def.worldX, def.worldY);
		circle->SetType(def.type);
		circle->SetDensity(def.density);
		circle->SetBouncyness(def.bouncyness);
		circle->SetFriction(def.friction);
		return circle;
	}
	std::shared_ptr<SFMLConvexShapeObject> MakeConvex(const ConvexDefinition& def) {
		auto size = def.points.size();
		auto convex = std::make_shared<SFMLConvexShapeObject>(def.parent, def.scale, size);
		convex->GetShape()->setOutlineColor(def.outlineColor);
		convex->GetShape()->setFillColor(def.fillColor);
		convex->GetShape()->setOutlineThickness(def.outlineThickness);
		convex->SetPosition(def.worldX, def.worldY);
		convex->SetType(def.type);
		convex->SetDensity(def.density);
		convex->SetBouncyness(def.bouncyness);
		convex->SetFriction(def.friction);
		auto convexShape = std::dynamic_pointer_cast<sf::ConvexShape>(convex->GetShape());
		convexShape->setPointCount(size);
		for (std::size_t i = 0; i < size; i++) {
			convexShape->setPoint(i, def.points[i]);
		}
		return convex;
	}
}
