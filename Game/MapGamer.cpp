#pragma once

#include "MapGamer.h"
#include <iostream>

using namespace GameView;

MapCellButton::MapCellButton(int x, int y, int w, int h, int _x, int _y) :Fl_Button(x, y, w, h) {
	ct = nullptr;
	this->x = _x;
	this->y = _y;
}

void MapGamer::drawGame(Map::Map *map) {

	std::cout << "Drawing the map in game." << std::endl;

	map_group->clear();
	map_group->hide();
	map_group->begin();

	for (int j = 0; j < _grid_y; j++)
	{
		mcbs.push_back(std::vector<MapCellButton*>());
		for (int i = 0; i < _grid_x; i++)
		{
			MapCellButton* m = new MapCellButton(32 + 32 * i, 32 + 32 * j, 32, 32, i, j);
			//m->copy_label(cttos(current_map->getGrid()[j][i]).c_str());//TODO. error here.
			mcbs[j].push_back(m);
		}
	}
	map_group->end();
	map_group->show();
}

int MapCellButton::handle(int e)
{
	if (e == FL_RELEASE)
	{
		current_l = (current_l + 1) % 3;
		copy_label(Cell_Labels[current_l].c_str());
		this->value(current_l != 0);
		return 1;
	}
	if (e == FL_PUSH)
	{
		this->set();
		return 1;
	}
	return 0;
}
