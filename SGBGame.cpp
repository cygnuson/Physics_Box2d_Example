
#include "SGBGame.hpp"

SGBGame::SGBGame()
	:inputMatrix(InputMatrix::GetInstance()), texMan(TextureManager::GetInstance())
{
	window.create(sf::VideoMode(800, 600, 32), "Super Geometry Bros");
	width = 800;
	height = 600;
	world = std::make_shared<BoxWorld>(std::ref(scale));
	window.setFramerateLimit(FPS);
	view = std::make_shared<sf::View>(window.getView());
}

SGBGame::SGBGame(unsigned int width, unsigned int height, unsigned int x, unsigned int y)
	:inputMatrix(InputMatrix::GetInstance()), texMan(TextureManager::GetInstance()), width(width), height(height)
{
	window.create(sf::VideoMode(width, height, 32), "Super Geometry Bros");
	window.setPosition(sf::Vector2i(x,y));
	world = std::make_shared<BoxWorld>(std::ref(scale));
	window.setFramerateLimit(FPS);
	view = std::make_shared<sf::View>(window.getView());
}

void SGBGame::StartLoop()
{
	window.resetGLStates();
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			gui.HandleEvent(event);
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::Resized) {

			}
			inputMatrix.ProcessEvent(event);
		}

		float x = inputMatrix.MouseX();
		float y = inputMatrix.MouseY();
		HandleEvents(event);
		if (gui.play) {
			world->Step(1 / FPS, 8, 3);
		}
		window.clear();
		if (holdCircle) {
			window.draw(*holdCircle);
		}
		if (holdRect) {
			window.draw(*holdRect);
		}
		world->DrawAll(window);
		gui.Draw(window);
		window.display();
	}
}

void SGBGame::HandleEvents(sf::Event& event)
{
	if (inputMatrix.IsPressed(sf::Keyboard::Space, true)) {
		gui.TogglePlay();
	}
	if (inputMatrix.IsPressed(sf::Mouse::Button::Right, true)) {
		holdX = inputMatrix.MouseX();
		holdY = inputMatrix.MouseY();
		if (gui.GetType() == PhysGui::Type::Circle) {
			holdCircle = std::make_shared<sf::CircleShape>(5, 128);
			holdCircle->setFillColor(gui.GetFillColor());
			holdCircle->setOutlineColor(gui.GetOutlineColor());
			holdCircle->setPosition(holdX, holdY);
		}
		if (gui.GetType() == PhysGui::Type::Box) {
			holdRect = std::make_shared<sf::RectangleShape>(sf::Vector2f(5, 5));
			holdRect->setFillColor(gui.GetFillColor());
			holdRect->setOutlineColor(gui.GetOutlineColor());
			holdRect->setPosition(holdX, holdY);
		}
		holding = true;
	}

	if ((event.type == sf::Event::MouseMoved || holding) && (holdCircle || holdRect)) {
		if (inputMatrix.IsPressed(sf::Keyboard::Escape, true)) {
			holdCircle.reset();
			holdRect.reset();
			holding = false;
			return;
		}
		if (gui.GetType() == PhysGui::Type::Circle) {
			auto radius = sqrtf(powf(holdX - inputMatrix.MouseX(), 2) + powf(holdY - inputMatrix.MouseY(), 2));
			holdCircle->setRadius(radius);
			holdCircle->setOrigin(radius, radius);
			if (inputMatrix.IsPressed(sf::Mouse::Button::Left, true)) {
				CreateShape(holdX, holdY, radius, 128);
				holdCircle.reset();
				holding = false;
			}
		}
		if (gui.GetType() == PhysGui::Type::Box) {
			float width = -(holdX - inputMatrix.MouseX());
			float height = -(holdY - inputMatrix.MouseY());
			holdRect->setSize({ width,height });
			if (inputMatrix.IsPressed(sf::Mouse::Button::Left, true)) {
				CreateShape(holdX + (width / 2), holdY + (height / 2), width, height);
				holdRect.reset();
				holding = false;
			}
		}
	}
}

void SGBGame::CreateShape(float x, float y, float width_radius, float height_pointcount)
{
	if (gui.GetType() == PhysGui::Type::Circle) {
		Factory::ShapeDefinition circleDef(scale);
		circleDef.fillColor = gui.GetFillColor();;
		circleDef.bouncyness = std::stof((std::string) gui.bounceEntry->GetText());
		circleDef.density = std::stof((std::string) gui.densityEntry->GetText());
		circleDef.friction = std::stof((std::string) gui.frictionEntry->GetText());
		circleDef.radius = width_radius;
		circleDef.pointCount = height_pointcount;
		circleDef.outlineColor = gui.GetOutlineColor();
		circleDef.outlineThickness = -1;
		circleDef.parent = world->GetWorld();
		circleDef.worldX = x;
		circleDef.worldY = y;
		if (gui.selectedB2Type == b2_dynamicBody) {
			circleDef.type = Factory::ObjectDefinition::b2Type::Dynamic;
		}
		else if (gui.selectedB2Type == b2_staticBody) {
			circleDef.type = Factory::ObjectDefinition::b2Type::Static;
		}
		else if (gui.selectedB2Type == b2_kinematicBody) {
			circleDef.type = Factory::ObjectDefinition::b2Type::Kinematic;
		}
		auto circle = Factory::MakeCircle(circleDef);
		world->AddObject(circle);
	}
	if (gui.GetType() == PhysGui::Type::Box) {
		Factory::ShapeDefinition boxDef(scale);
		boxDef.fillColor = gui.GetFillColor();;
		boxDef.bouncyness = std::stof((std::string) gui.bounceEntry->GetText());
		boxDef.density = std::stof((std::string) gui.densityEntry->GetText());
		boxDef.friction = std::stof((std::string) gui.frictionEntry->GetText());
		boxDef.width = fabs(width_radius);
		boxDef.height = fabs(height_pointcount);
		boxDef.outlineColor = gui.GetOutlineColor();
		boxDef.outlineThickness = -1;
		boxDef.parent = world->GetWorld();
		boxDef.worldX = x;
		boxDef.worldY = y;
		if (gui.selectedB2Type == b2_dynamicBody) {
			boxDef.type = Factory::ObjectDefinition::b2Type::Dynamic;
		}
		else if (gui.selectedB2Type == b2_staticBody) {
			boxDef.type = Factory::ObjectDefinition::b2Type::Static;
		}
		else if (gui.selectedB2Type == b2_kinematicBody) {
			boxDef.type = Factory::ObjectDefinition::b2Type::Kinematic;
		}
		auto box = Factory::MakeRect(boxDef);
		world->AddObject(box);
	}
}

void SGBGame::ShowGround()
{
	auto ground = std::make_shared<SFMLRectangleShapeObject>(world->GetWorld(), scale, width + 100, 16);
	ground->GetShape()->setOutlineColor(sf::Color::Red);
	ground->GetShape()->setFillColor(sf::Color::Transparent);
	ground->GetShape()->setOutlineThickness(-1);
	ground->SetPosition(width / 2, height - 32);
	ground->SetStatic();
	ground->SetDensity(0);
	ground->SetFriction(1);
	world->AddObject(ground);
}
