// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <thread>
#include <iostream>
#include <stdlib.h>

#include "Game/game.h"
#include "MainMenu.h"
#include "Main.h"
#include "Character/Character.h"
#include "Interactable/Wall.h"
#include "Game/gamelogger.h"
#include "Game/game.h"
#include <iostream>
#include "gui.h"




/* #include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
extern Fl_Double_Window *game_window;
#include <FL/Fl_Pack.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Output.H>
extern Fl_Output *hp_input;
extern Fl_Output *str_input;
extern Fl_Output *dex_input;
extern Fl_Output *con_input;
extern Fl_Output *int_input;
extern Fl_Output *wis_input;
extern Fl_Output *cha_input;
extern Fl_Output *ac_input;
#include <FL/Fl_Browser.H>
extern Fl_Browser *ItemInventory;
extern Fl_Group *map_group;
extern Fl_Group *enemies_group;
extern Fl_Browser *turn_order;
Fl_Double_Window* make_window();
extern Fl_Double_Window *dice_window;
#include <FL/Fl_Return_Button.H>
extern Fl_Return_Button *dice_button;
#include <FL/Fl_Box.H>
extern Fl_Box *dice_value_output;
Fl_Double_Window* roll_dice(); */

Dice* dice;
// using namespace CampaignEditor;
using namespace gamelogger;
using namespace game;

// Fl_Double_Window* MainWindow = make_window();
// Fl_Double_Window* DiceWindow = roll_dice();

int main()
{
	// setting up screens
	make_window();
	roll_dice();
	// Fl::lock();
	// Fl_Double_Window *w = make_window();
	// w->show();
	// dice = new Dice("1d20");

	// DiceWindow->show();
	// Game g = Game();
	// currentGame->Attach(gameLogger);

	// g.Attach(w);
	// std::thread thread_obj(&Game::run, &g);

	// g.run();
	game_window->fullscreen();
	game_window->show();
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
