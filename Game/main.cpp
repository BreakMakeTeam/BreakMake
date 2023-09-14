#include <OGL3D/Game/OGame.h>
#include <exception>
#include <iostream>

using std::cout;

int main()
{
	try {
		OGame game;
		game.run();
	}
	catch (const std::exception e) {
		cout << "Eror: " << e.what() << "\n";
		return 1;
	}
	return 0;
}