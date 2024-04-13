#pragma once

#include <FL/Fl_Group.H>
#include <MapEditor.h>
#include <vector>

namespace GameView
{
	class MapGamer {

	public:
		void drawGame();

	private:
		Fl_Group* map_group;
		int _grid_x, _grid_y;
		std::vector<std::vector<CampaignEditor::MapCellButton*>> mcbs;

	};

}