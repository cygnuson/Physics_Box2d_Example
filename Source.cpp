
#include <fstream>
#include <memory>
#include <array>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <SFGUI/SFGUI.hpp>
#include <SFGUI\Window.hpp>
#include <SFGUI\ComboBox.hpp>
#include <SFGUI\Button.hpp>
#include <SFGUI\CheckButton.hpp>
#include <SFGUI\Label.hpp>
#include <SFGUI\Desktop.hpp>
#include <SFGUI\Entry.hpp>
#include <SFGUI\Box.hpp>
#include <SFGUI\Scale.hpp>
#include <SFGUI\Spinner.hpp>

#include <Box2D\Box2D.h>

#include "SGBGame.hpp"

const int WIDTH = 1440;
const int HEIGHT = 900;

#define RadToDeg(X) (X * (180 / b2_pi))
#define DegToRad(X) (X * (b2_pi / 180))

int main()
{
	SGBGame game(1440,900,50,50);

	game.ShowGround();
	game.StartLoop();

	

	return 0;
}
