#pragma once

#include <memory>

#include <Box2D\Box2D.h>

#include <SFML\Graphics.hpp>

#include <SFGUI/SFGUI.hpp>
#include <SFGUI\Window.hpp>
#include <SFGUI\ComboBox.hpp>
#include <SFGUI\Button.hpp>
#include <SFGUI\CheckButton.hpp>
#include <SFGUI\Label.hpp>
#include <SFGUI\Desktop.hpp>
#include <SFGUI\Entry.hpp>
#include <SFGUI\Button.hpp>
#include <SFGUI\Box.hpp>
#include <SFGUI\Scale.hpp>
#include <SFGUI\Spinner.hpp>

class PhysGui {
public:
	enum class Type {
		Circle,
		Convex,
		Box,
	};
	PhysGui();
	void HandleEvent(sf::Event& ev);
	void Draw(sf::RenderWindow& window);
	void SliderChangeHandler(std::shared_ptr<sfg::Scale> scale, std::shared_ptr<sfg::Entry> entry);
	sf::Color GetFillColor();
	sf::Color GetOutlineColor();
	void TogglePlay();
	PhysGui::Type GetType();
	void OnComboSelect();
	void OnClickPlay();
	void OnB2TypeComboSelect();

	PhysGui::Type type = Type::Circle;
	bool play = false;
	b2BodyType selectedB2Type = b2_dynamicBody;

	sfg::SFGUI sfgui;
	sfg::Desktop desktop;
	std::shared_ptr<sfg::Box> mainBox;
	std::shared_ptr<sfg::Window> mainWindow;

	std::shared_ptr<sfg::Label> shapeLabel;
	std::shared_ptr<sfg::Box> shapeBox;
	std::shared_ptr<sfg::ComboBox> shapeComboBox;

	std::shared_ptr<sfg::Entry> frictionEntry;
	std::shared_ptr<sfg::Label> frictionLabel;
	std::shared_ptr<sfg::Box> frictionBox;

	std::shared_ptr<sfg::Entry> bounceEntry;
	std::shared_ptr<sfg::Label> bounceLabel;
	std::shared_ptr<sfg::Box>   bounceBox;

	std::shared_ptr<sfg::Entry> densityEntry;
	std::shared_ptr<sfg::Label> densityLabel;
	std::shared_ptr<sfg::Box>   densityBox;

	std::shared_ptr<sfg::Box> fillColorBox;
	std::shared_ptr<sfg::Label> fillColorLabel;
	std::shared_ptr<sfg::Box>   outlineColorBox;
	std::shared_ptr<sfg::Label> outlineColorLabel;

	std::shared_ptr<sfg::Box>   redBox;
	std::shared_ptr<sfg::Scale> redScale;
	std::shared_ptr<sfg::Entry> redEntry;

	std::shared_ptr<sfg::Box>   blueBox;
	std::shared_ptr<sfg::Scale> blueScale;
	std::shared_ptr<sfg::Entry> blueEntry;

	std::shared_ptr<sfg::Box>   greenBox;
	std::shared_ptr<sfg::Scale> greenScale;
	std::shared_ptr<sfg::Entry> greenEntry;

	std::shared_ptr<sfg::Box>   alphaBox;
	std::shared_ptr<sfg::Scale> alphaScale;
	std::shared_ptr<sfg::Entry> alphaEntry;

	std::shared_ptr<sfg::Box>   redOutlineBox;
	std::shared_ptr<sfg::Scale> redOutlineScale;
	std::shared_ptr<sfg::Entry> redOutlineEntry;

	std::shared_ptr<sfg::Box>   blueOutlineBox;
	std::shared_ptr<sfg::Scale> blueOutlineScale;
	std::shared_ptr<sfg::Entry> blueOutlineEntry;

	std::shared_ptr<sfg::Box>   greenOutlineBox;
	std::shared_ptr<sfg::Scale> greenOutlineScale;
	std::shared_ptr<sfg::Entry> greenOutlineEntry;

	std::shared_ptr<sfg::Box>   alphaOutlineBox;
	std::shared_ptr<sfg::Scale> alphaOutlineScale;
	std::shared_ptr<sfg::Entry> alphaOutlineEntry;

	std::shared_ptr<sfg::ToggleButton> playButton;
	std::shared_ptr<sfg::ComboBox> b2TypeBox;
};