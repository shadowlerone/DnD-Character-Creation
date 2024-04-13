#pragma once

#include "MapGamer.h"
#include <iostream>

void GameView::MapGamer::drawGame() {

	std::cout << "Drawing the map in game." << std::endl;

	map_group->clear();
	map_group->hide();
	map_group->begin();

	for (int j = 0; j < _grid_y; j++)
	{
		mcbs.push_back(std::vector<CampaignEditor::MapCellButton*>());
		for (int i = 0; i < _grid_x; i++)
		{
			CampaignEditor::MapCellButton* m = new CampaignEditor::MapCellButton(32 + 32 * i, 32 + 32 * j, 32, 32, i, j);
			//m->copy_label(cttos(current_map->getGrid()[j][i]).c_str());//TODO. error here.
			mcbs[j].push_back(m);
		}
	}
	map_group->end();
	map_group->show();
}