#ifndef MAIN_H_H
#define MAIN_H_H
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Box.H>

#include <vector>
// #include "ItemEditor.h"
// #include "MapEditor.h"
// #include "CampaignEditor.h"
// #include "MapSerializer.h"
// #include "CharacterEditor.h"
#include <filesystem>
#include <fstream>
#include <string>
#include <iostream>
#include "Map/Map.h"
#include "Builder/MapBuilder.h"
#include "gui.h"
extern Fl_Box* dice_value_output;
namespace GameView
{

	class MainView : public Fl_Window
	{
		MainView();
	};
	// dice->roll();
	void update_dice_roll_value(void *data);
	void update_dice_roll_value();
	void animate_dice_roll();
	
}
#endif