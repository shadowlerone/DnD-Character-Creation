#pragma once

#include <FL/Fl_Group.H>
#include <MapEditor.h>
#include <vector>

namespace GameView
{
	class MapCellButton : public Fl_Button
	{
	public:
		MapCellButton(int x, int y, int w, int h, int _x, int _y);

		void cellType(Interactable::Interactable* ct) { this->ct = ct; };
		Interactable::Interactable* cellType() { return ct; }

		int X() { return x; }
		int Y() { return y; }
		int handle(int e);

	private:
		Interactable::Interactable* ct;

		int x, y;
		int current_l = 0;
	};

	class MapGamer {

	public:
		void drawGame();

	private:
		Fl_Group* map_group;
		int _grid_x, _grid_y;
		std::vector<std::vector<MapCellButton*>> mcbs;

	};

}