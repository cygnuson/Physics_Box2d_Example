
#include "PhysGui.hpp"

void PhysGui::OnComboSelect() {
	switch (shapeComboBox->GetSelectedItem()) {
	case 0:
		type = Type::Circle;
		break;
	case 1:
		type = Type::Box;
		break;
	case 2:
		type = Type::Convex;
		break;
	}
};
void PhysGui::OnClickPlay() {
	play = playButton->IsActive();
}
void PhysGui::OnB2TypeComboSelect()
{
	switch (b2TypeBox->GetSelectedItem()) {
	case 0:
		selectedB2Type = b2_dynamicBody;
		break;
	case 1:
		selectedB2Type = b2_staticBody;
		break;
	case 2:
		selectedB2Type = b2_kinematicBody;
		break;
	}
}
void PhysGui::TogglePlay() {
	playButton->SetActive(!playButton->IsActive());
}
PhysGui::Type PhysGui::GetType() {
	return type;
}
void PhysGui::SliderChangeHandler(std::shared_ptr<sfg::Scale> scale, std::shared_ptr<sfg::Entry> entry) {
	entry->SetText(std::to_string((int)scale->GetValue()));
}
sf::Color PhysGui::GetFillColor() {
	return sf::Color(std::stoi((std::string) redEntry->GetText()),
		std::stoi((std::string) greenEntry->GetText()),
		std::stoi((std::string) blueEntry->GetText()),
		std::stoi((std::string) alphaEntry->GetText())
		);
}
sf::Color PhysGui::GetOutlineColor() {
	return sf::Color(std::stoi((std::string) redOutlineEntry->GetText()),
		std::stoi((std::string) greenOutlineEntry->GetText()),
		std::stoi((std::string) blueOutlineEntry->GetText()),
		std::stoi((std::string) alphaOutlineEntry->GetText())
		);
}
void PhysGui::HandleEvent(sf::Event& ev)
{
	desktop.HandleEvent(ev);
}
void PhysGui::Draw(sf::RenderWindow& window)
{
	desktop.Update(1);
	sfgui.Display(window);
}

PhysGui::PhysGui()
{
	mainBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
	mainBox->SetId("main_box");
	mainWindow = sfg::Window::Create();
	mainWindow->SetTitle("Menu - Right click to create!");
	mainWindow->SetId("main_window");

	shapeBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5);
	shapeLabel = sfg::Label::Create("Type");
	shapeComboBox = sfg::ComboBox::Create();
	shapeComboBox->AppendItem("Circle");
	shapeComboBox->AppendItem("Box");
	shapeComboBox->AppendItem("Convex");
	shapeBox->Pack(shapeLabel);
	shapeBox->Pack(shapeComboBox);

	b2TypeBox = sfg::ComboBox::Create();
	b2TypeBox->AppendItem("Dynamic");
	b2TypeBox->AppendItem("Static");
	b2TypeBox->AppendItem("Kinematic");

	frictionEntry = sfg::Entry::Create();
	frictionEntry->SetRequisition({ 40,0 });
	frictionLabel = sfg::Label::Create("Friction");
	frictionBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5);
	frictionEntry->SetText("0.7");
	frictionBox->Pack(frictionLabel);
	frictionBox->Pack(frictionEntry);

	bounceEntry = sfg::Entry::Create();
	bounceEntry->SetRequisition({ 40,0 });
	bounceLabel = sfg::Label::Create("Bounceyness");
	bounceBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5);
	bounceEntry->SetText("0.2");
	bounceBox->Pack(bounceLabel);
	bounceBox->Pack(bounceEntry);

	densityEntry = sfg::Entry::Create();
	densityEntry->SetRequisition({ 40,0 });
	densityLabel = sfg::Label::Create("Density");
	densityBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5);
	densityEntry->SetText("1.0");
	densityBox->Pack(densityLabel);
	densityBox->Pack(densityEntry);

	fillColorBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5);
	fillColorBox->SetId("fill_color_box");
	fillColorLabel = sfg::Label::Create("Fill Color");

	redBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5);
	redBox->SetId("red_box");
	redScale = sfg::Scale::Create();
	redScale->SetId("red_fill_scale");
	sfg::Context::Get().GetEngine().SetProperty("Window#main_window > Box#main_box > Box#fill_color_box > Box#red_box > Scale#red_fill_scale", "BorderColor", sf::Color::Red);
	redScale->SetRequisition({ 128,0 });
	redScale->SetIncrements(1, 10);
	redScale->SetRange(0, 255);
	redEntry = sfg::Entry::Create();
	redEntry->SetRequisition({ 40,0 });
	redBox->Pack(redScale);
	redBox->Pack(redEntry);

	greenBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5);
	greenBox->SetId("green_box");
	greenScale = sfg::Scale::Create();
	greenScale->SetId("green_fill_scale");
	sfg::Context::Get().GetEngine().SetProperty("Window#main_window > Box#main_box > Box#fill_color_box > Box#green_box > Scale#green_fill_scale", "BorderColor", sf::Color::Green);
	greenScale->SetRequisition({ 128,0 });
	greenScale->SetIncrements(1, 10);
	greenScale->SetRange(0, 255);
	greenEntry = sfg::Entry::Create();
	greenEntry->SetRequisition({ 40,0 });
	greenBox->Pack(greenScale);
	greenBox->Pack(greenEntry);

	blueBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5);
	blueBox->SetId("blue_box");
	blueScale = sfg::Scale::Create();
	blueScale->SetId("blue_fill_scale");
	sfg::Context::Get().GetEngine().SetProperty("Window#main_window > Box#main_box > Box#fill_color_box > Box#blue_box > Scale#blue_fill_scale", "BorderColor", sf::Color::Blue);
	blueScale->SetRequisition({ 128,0 });
	blueScale->SetIncrements(1, 10);
	blueScale->SetRange(0, 255);
	blueEntry = sfg::Entry::Create();
	blueEntry->SetRequisition({ 40,0 });
	blueBox->Pack(blueScale);
	blueBox->Pack(blueEntry);

	alphaBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5);
	alphaBox->SetId("alpha_box");
	alphaScale = sfg::Scale::Create();
	alphaScale->SetId("alpha_fill_scale");
	sfg::Context::Get().GetEngine().SetProperty("Window#main_window > Box#main_box > Box#fill_color_box > Box#alpha_box > Scale#alpha_fill_scale", "SliderColor", sf::Color(104, 106, 101, 50));
	alphaScale->SetRequisition({ 128,0 });
	alphaScale->SetIncrements(1, 10);
	alphaScale->SetRange(0, 255);
	alphaEntry = sfg::Entry::Create();
	alphaEntry->SetRequisition({ 40,0 });
	alphaBox->Pack(alphaScale);
	alphaBox->Pack(alphaEntry);

	fillColorBox->Pack(fillColorLabel);
	fillColorBox->Pack(redBox);
	fillColorBox->Pack(greenBox);
	fillColorBox->Pack(blueBox);
	fillColorBox->Pack(alphaBox);

	outlineColorBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5);
	outlineColorBox->SetId("Outline_color_box");
	outlineColorLabel = sfg::Label::Create("Outline Color");

	redOutlineBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5);
	redOutlineBox->SetId("red_Outlinebox");
	redOutlineScale = sfg::Scale::Create();
	redOutlineScale->SetId("red_Outline_scale");
	sfg::Context::Get().GetEngine().SetProperty("Window#main_window > Box#main_box > Box#Outline_color_box > Box#red_Outlinebox > Scale#red_Outline_scale", "BorderColor", sf::Color::Red);
	redOutlineScale->SetRequisition({ 128,0 });
	redOutlineScale->SetIncrements(1, 10);
	redOutlineScale->SetRange(0, 255);
	redOutlineEntry = sfg::Entry::Create();
	redOutlineEntry->SetRequisition({ 40,0 });
	redOutlineBox->Pack(redOutlineScale);
	redOutlineBox->Pack(redOutlineEntry);

	greenOutlineBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5);
	greenOutlineBox->SetId("green_Outlinebox");
	greenOutlineScale = sfg::Scale::Create();
	greenOutlineScale->SetId("green_Outline_scale");
	sfg::Context::Get().GetEngine().SetProperty("Window#main_window > Box#main_box > Box#Outline_color_box > Box#green_Outlinebox > Scale#green_Outline_scale", "BorderColor", sf::Color::Green);
	greenOutlineScale->SetRequisition({ 128,0 });
	greenOutlineScale->SetIncrements(1, 10);
	greenOutlineScale->SetRange(0, 255);
	greenOutlineEntry = sfg::Entry::Create();
	greenOutlineEntry->SetRequisition({ 40,0 });
	greenOutlineBox->Pack(greenOutlineScale);
	greenOutlineBox->Pack(greenOutlineEntry);

	blueOutlineBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5);
	blueOutlineBox->SetId("blue_Outlinebox");
	blueOutlineScale = sfg::Scale::Create();
	blueOutlineScale->SetId("blue_Outline_scale");
	sfg::Context::Get().GetEngine().SetProperty("Window#main_window > Box#main_box > Box#Outline_color_box > Box#blue_Outlinebox > Scale#blue_Outline_scale", "BorderColor", sf::Color::Blue);
	blueOutlineScale->SetRequisition({ 128,0 });
	blueOutlineScale->SetIncrements(1, 10);
	blueOutlineScale->SetRange(0, 255);
	blueOutlineEntry = sfg::Entry::Create();
	blueOutlineEntry->SetRequisition({ 40,0 });
	blueOutlineBox->Pack(blueOutlineScale);
	blueOutlineBox->Pack(blueOutlineEntry);

	alphaOutlineBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5);
	alphaOutlineBox->SetId("alpha_Outlinebox");
	alphaOutlineScale = sfg::Scale::Create();
	alphaOutlineScale->SetId("alpha_Outline_scale");
	sfg::Context::Get().GetEngine().SetProperty("Window#main_window > Box#main_box > Box#Outline_color_box > Box#alpha_Outlinebox > Scale#alpha_Outline_scale", "SliderColor", sf::Color(104, 106, 101, 50));
	alphaOutlineScale->SetRequisition({ 128,0 });
	alphaOutlineScale->SetIncrements(1, 10);
	alphaOutlineScale->SetRange(0, 255);
	alphaOutlineEntry = sfg::Entry::Create();
	alphaOutlineEntry->SetRequisition({ 40,0 });
	alphaOutlineBox->Pack(alphaOutlineScale);
	alphaOutlineBox->Pack(alphaOutlineEntry);

	outlineColorBox->Pack(outlineColorLabel);
	outlineColorBox->Pack(redOutlineBox);
	outlineColorBox->Pack(greenOutlineBox);
	outlineColorBox->Pack(blueOutlineBox);
	outlineColorBox->Pack(alphaOutlineBox);

	playButton = sfg::ToggleButton::Create("Play");

	mainBox->Pack(playButton);
	mainBox->Pack(shapeBox);
	mainBox->Pack(b2TypeBox);
	mainBox->Pack(bounceBox);
	mainBox->Pack(frictionBox);
	mainBox->Pack(densityBox);
	mainBox->Pack(fillColorBox);
	mainBox->Pack(outlineColorBox);

	mainBox->SetSpacing(5);
	mainWindow->Add(mainBox);
	desktop.Add(mainWindow);

	//---------------------------------------------------Callbacks
	b2TypeBox->GetSignal(sfg::ComboBox::OnSelect).Connect(std::bind(&PhysGui::OnB2TypeComboSelect, this));
	b2TypeBox->SelectItem(0);
	shapeComboBox->GetSignal(sfg::ComboBox::OnSelect).Connect(std::bind(&PhysGui::OnComboSelect, this));
	shapeComboBox->SelectItem(0);
	type = Type::Circle;

	playButton->GetSignal(sfg::ToggleButton::OnToggle).Connect(std::bind(&PhysGui::OnClickPlay, this));

	redScale->GetSignal(sfg::Scale::OnMouseMove).Connect(std::bind(&PhysGui::SliderChangeHandler, this, redScale, redEntry));
	greenScale->GetSignal(sfg::Scale::OnMouseMove).Connect(std::bind(&PhysGui::SliderChangeHandler, this, greenScale, greenEntry));
	blueScale->GetSignal(sfg::Scale::OnMouseMove).Connect(std::bind(&PhysGui::SliderChangeHandler, this, blueScale, blueEntry));
	alphaScale->GetSignal(sfg::Scale::OnMouseMove).Connect(std::bind(&PhysGui::SliderChangeHandler, this, alphaScale, alphaEntry));

	redOutlineScale->GetSignal(sfg::Scale::OnMouseMove).Connect(std::bind(&PhysGui::SliderChangeHandler, this, redOutlineScale, redOutlineEntry));
	greenOutlineScale->GetSignal(sfg::Scale::OnMouseMove).Connect(std::bind(&PhysGui::SliderChangeHandler, this, greenOutlineScale, greenOutlineEntry));
	blueOutlineScale->GetSignal(sfg::Scale::OnMouseMove).Connect(std::bind(&PhysGui::SliderChangeHandler, this, blueOutlineScale, blueOutlineEntry));
	alphaOutlineScale->GetSignal(sfg::Scale::OnMouseMove).Connect(std::bind(&PhysGui::SliderChangeHandler, this, alphaOutlineScale, alphaOutlineEntry));

	redEntry->SetText(std::to_string((int)redScale->GetValue()));
	greenEntry->SetText(std::to_string((int)greenScale->GetValue()));
	blueEntry->SetText(std::to_string((int)blueScale->GetValue()));
	alphaEntry->SetText(std::to_string((int)alphaScale->GetValue()));

	redOutlineEntry->SetText(std::to_string((int)redOutlineScale->GetValue()));
	greenOutlineEntry->SetText(std::to_string((int)greenOutlineScale->GetValue()));
	blueOutlineEntry->SetText(std::to_string((int)blueOutlineScale->GetValue()));
	alphaOutlineEntry->SetText(std::to_string((int)alphaOutlineScale->GetValue()));

}