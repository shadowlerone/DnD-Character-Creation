// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <thread>
#include <iostream>
#include <stdlib.h>

#include "Game/game.h"
#include "MainMenu.h"
#include "Character/Character.h"
#include "Interactable/Wall.h"
#include "Game/gamelogger.h"
#include "Game/game.h"
#include <iostream>
#include "gui.h"

// using namespace CampaignEditor;
using namespace gamelogger;
using namespace game;
int main()
{
	Fl::lock();
	Fl_Double_Window *w = make_window();
	w->show();


	Game g = Game();
	std::thread thread_obj(&Game::run, &g);

	// g.run();

	// thread_obj.join();
	Fl::run();
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
