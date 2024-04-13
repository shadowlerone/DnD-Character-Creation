// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "Game/game.h"
#include "Game/gamelogger.h"
#include "Interactable/Wall.h"
#include "MainMenu.h"
#include <FL/Fl.H>
#include <iostream>

using namespace CampaignEditor;
std::vector<Map::Map*>* maps = new std::vector<Map::Map*>();
std::vector<item::Item*>* items = new std::vector<item::Item*>();
std::vector<serializeItem::ItemContainerRecord*>* itemcontainers = new std::vector<serializeItem::ItemContainerRecord*>();
campaign::CampaignRecord* currentCampaign = new CampaignRecord();

int main()
{
	MainMenu* m = new MainMenu();
	m->show();
	std::cout << "Attempting to load default campaign" << std::endl;
	m->open((fs::current_path() / "Campaign").string());
	Fl::run();
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
