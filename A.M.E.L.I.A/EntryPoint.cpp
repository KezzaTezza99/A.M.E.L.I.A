#include <iostream>
#include "src/Graphics/GameWindow.h"

const int WIDTH = 800;
const int HEIGHT = 800;

int main()
{
	GameWindow window("A.M.E.L.I.A", WIDTH, HEIGHT);

	//Game Loop
	while (!window.Closed())
	{
		window.Clear();

		//Render here

		//Update
		window.Update();
	}

	return 0;
}