#pragma once
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Tabs.H>
#include <vector>
#include "ItemEditor.h"
#include "MapEditor.h"
#include "CampaignEditor.h"
#include "MapSerializer.h"
#include "CharacterEditor.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include "Map/Map.h"
#include "Builder/MapBuilder.h"
#include "gui.h"

namespace GameView {

class MainView : public Fl_Window
{
	MainView();
};
	
}