#pragma once

#include <SFML\Graphics.hpp>
#include "TextureManager.hpp"
#include "Object.hpp"

class SFMLShapeObject :public BObject {
public:
	SFMLShapeObject(b2World* parent, float& scale);
	virtual void Update();
	virtual void Draw(sf::RenderWindow& window);
	virtual std::shared_ptr<sf::Shape> GetShape();
protected:
	std::shared_ptr<sf::Shape> shape;
};

class SFMLConvexShapeObject : public SFMLShapeObject {
public:
	SFMLConvexShapeObject(b2World* parent, float& scale, std::size_t pointCount);
	virtual void Update();
	//virtual void Draw(sf::RenderWindow& window);
protected:
	size_t pointCount;
};

class SFMLRectangleShapeObject : public SFMLShapeObject {
public:
	SFMLRectangleShapeObject(b2World* parent, float& scale, float x, float y);
	virtual void Update();
	//virtual void Draw(sf::RenderWindow& window);
protected:
	sf::Vector2f size;
};
class SFMLCircleShapeObject : public SFMLShapeObject {
public:
	SFMLCircleShapeObject(b2World* parent, float& scale, float radius, std::size_t pointCount);
	virtual void Update();
	virtual void Draw(sf::RenderWindow& window);
	std::shared_ptr<sf::RectangleShape> GetLine();
protected:
	std::shared_ptr<sf::RectangleShape> line;
	float radius;
	size_t pointCount;
};

class SFMLSpriteObject :public BObject {
public:
	SFMLSpriteObject(b2World* parent, float& scale, const std::string& textureName, sf::IntRect textureRect = { 0,0,0,0 });
	virtual void Update();
	virtual void Draw(sf::RenderWindow& window);
	virtual sf::Sprite& GetSprite();
protected:
	std::string textureName;
	sf::IntRect textureRect;
	std::shared_ptr<sf::Sprite> sprite;
};

namespace Factory {
	struct ObjectDefinition {
		ObjectDefinition(float& scale) :scale(scale) {

		}
		struct b2Type{
			static const b2BodyType Dynamic;
			static const b2BodyType Static;
			static const b2BodyType Kinematic;
		};
		b2World* parent = nullptr;
		union {
			float width;
			float radius;
		};
		union {
			float height;
			float pointCount;
		};
		float worldX = 0;
		float worldY = 0;
		float& scale;
		float density = 0;
		float friction = 0;
		float bouncyness = 0;
		b2BodyType type;
	};

	struct ShapeDefinition :public ObjectDefinition {
		ShapeDefinition(float& scale) :ObjectDefinition(scale) {

		}
		sf::Color outlineColor;
		sf::Color fillColor;
		float outlineThickness = 0;
	};

	struct SpriteDefinition : public ObjectDefinition {
		SpriteDefinition(float& scale) :ObjectDefinition(scale) {

		}
		std::string textureName;
		sf::IntRect textureRect = { 0,0,0,0 };
	};

	struct ConvexDefinition : public ShapeDefinition {
		ConvexDefinition(float& scale) : ShapeDefinition(scale) {

		}
		inline void AddPoints(std::vector<sf::Vector2f>&& points) {
			points = std::forward<std::vector<sf::Vector2f>>(points);
		}
		std::vector<sf::Vector2f> points;
	};


	std::shared_ptr<SFMLRectangleShapeObject> MakeRect(const ShapeDefinition& def);
	std::shared_ptr<SFMLCircleShapeObject> MakeCircle(const ShapeDefinition& def);
	std::shared_ptr<SFMLConvexShapeObject> MakeConvex(const ConvexDefinition& def);
}
