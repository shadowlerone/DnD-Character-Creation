#include "CampaignEditor.h"
#include <FL/fl_ask.H>

namespace CampaignEditor
{
	MapButton::MapButton(int x, int y, int w, int h, int _x, int _y) : Fl_Button(x, y, w, h)
	{
		this->x = _x;
		this->y = _y;
	}
	// int MapButton::handle(int e)
	// {
	// 	if (e == FL_RELEASE)
	// 	{
	// 		std::cout<< "Map button release" << std::endl;
	// 		CampaignEditor *p = (CampaignEditor *)parent();
	// 		std::cout<< "Updated the sidebar" << std::endl;
	// 		value(0);
	// 		return 1;
	// 	}
	// 	if (e == FL_PUSH)
	// 	{
	// 		this->set();
	// 		return 1;
	// 	}
	// 	return 0;
	// }
	void CampaignEditor::load_data()
	{
		/* std::cout << "updating map" << std::endl;
		// int i = this->get_item();
		int i = browser->value();
		if (i <= maps.size() && i > 0)
		{
			std::cout << "selected: " << i << std::endl;
			current_map = (Map::Map *)browser->data(i);

			update_data();
		}
		// TODO: load map from file */
	}
	void CampaignEditor::save_data() {}
	void CampaignEditor::populate_browser()
	{
		browser->clear();
		std::string label;
		for (Map::Map* i : *maps)
		{
			label = std::to_string(i->getID());
			browser->add(label.c_str(), i);
		}
	}
	void CampaignEditor::CampaignEditor::update_data() {}
	void CampaignEditor::redraw_map()
	{
		map_grid->hide();
		map_grid->clear();
		map_grid->begin();
		mbs.clear();
		for (int j = 0; j < currentCampaign->numCols; j++)
		{
			// Fl_Pack * r = new Fl_Pack(0,0,50*_grid_x, 50);
			// r->type(Fl_Pack::HORIZONTAL);
			mbs.push_back(std::vector<MapButton*>());
			for (int i = 0; i < currentCampaign->numRows; i++)
			{
				MapButton* m = new MapButton(30 + 30 * i, 30 + 30 * j, 30, 30, i, j);
				m->callback(button_cb, (void*)this);
				try {
					int id = currentCampaign->mapIDs[i][j];
					if (id > 0) {
						m->copy_label(std::to_string(id).c_str());
					}
					else {
						m->copy_label(" ");
					}

				}
				catch (std::exception& e) {
					std::cerr << e.what() << std::endl;
					m->copy_label("");
				}
				// m->copy_label(std::to_string(id).c_str());
				mbs[j].push_back(m);
			}
			// r->end();
		}
		map_grid->end();
		map_grid->show();
		map_grid->scroll_to(0, 0);
	}
	void CampaignEditor::create() {}
	void CampaignEditor::delete_entry() {}
	void CampaignEditor::update_sidebar()
	{
		std::string label = "Map: " + std::to_string(_c_x) + ", " + std::to_string(_c_y);
		sidebar_title->copy_label(label.c_str());
		update_dropdown();
	}

	void CampaignEditor::update_dropdown()
	{
		map_list->clear();
		std::string label;
		map_list->add("");
		if (get_cell(_c_x, _c_y)->ID() != 0) {
			map_list->value(std::to_string(get_cell(_c_x, _c_y)->ID()).c_str());
		}
		else {
			map_list->value("");
		}
		for (Map::Map* i : *maps)
		{
			label = std::to_string(i->getID());
			map_list->add(label.c_str());
		}
	}
	void CampaignEditor::show()
	{
		BaseEditor::show();
		// populate_browser();
		update_dropdown();
		std::cout << "attempting to update the browser" << std::endl;
	}
	void CampaignEditor::handle_dropdown() {
		MapButton* b = get_cell(_c_x, _c_y);
		b->ID(std::stoi(map_list->value()));
		b->label(map_list->value());
		bool found = false;
		Map::Map* m = NULL;
		for (Map::Map* _m : *maps) {
			if (_m->getID() == std::stoi(map_list->value())) {
				found = true;
				m = _m;
				break;
			}
		}
		if (!found) {
			// TODO:  Map not found error
			return;
		}
		currentCampaign->mapIDs[_c_y][_c_x] = m->getID();
		std::cout << "campaign modified" << std::endl;

		// redraw_map();
	}
	bool CampaignEditor::save() {
		if (filepath.empty())
		{
			save_as();
		}
		else {
			try
			{
				SaveCampaignRecord(this->filepath, *currentCampaign);
			}
			catch (const std::exception& e)
			{
				fl_alert("There was an error saving the file. Try using 'save as'");
				return false;
			}
			try
			{
				// Campaign c = LoadCampaign(0, filepath);

				populate_browser();
				/* code */
			}
			catch (const std::exception& e)
			{
				std::cerr << e.what() << '\n';
				return false;
			}
		}
		return true;
	}

	void CampaignEditor::save_as() {
		if (BaseEditor::File_Chooser("Save as", Fl_Native_File_Chooser::BROWSE_SAVE_DIRECTORY))
		{
			try
			{
				save();
			}
			catch (const std::exception& e)
			{
				std::cerr << e.what() << '\n';
			}
		};
	}
	bool CampaignEditor::open(std::string s) {
		filepath = s;
		try {
			std::cout << "Opening campaign " << s << std::endl;
			CampaignRecord* cr = campaign::LoadCampaign(1, filepath);
			CampaignMap cp;
			cp.mapID = 0;
			cp.coorX = cp.coorY = 0;
			maps->clear();
			*currentCampaign = *cr;
			redraw_map();
			return true;
		}
		catch (const std::exception& e) {
			return false;
		}
		redraw_map();
	}
	bool CampaignEditor::open() {
		if (BaseEditor::File_Chooser("Open", Fl_Native_File_Chooser::BROWSE_DIRECTORY))
		{
			open(filepath);
		}
		return false;
	}
	void CampaignEditor::save_all() {
		for (Map::Map* _m : *maps) {

		}
	}
}