#ifndef MAIN_H_H
#define MAIN_H_H
#include "Builder/MapBuilder.h"
#include "gui.h"
#include "Map/Map.h"
#include <filesystem>
#include <FL/Fl_Box.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Window.H>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

extern Fl_Box* dice_value_output;

namespace GameView
{
	class MainView : public Fl_Window
	{
		MainView();
	};
	// dice->roll();
	void update_dice_roll_value(void* data);
	void update_dice_roll_value();
	void animate_dice_roll();
}
#endif