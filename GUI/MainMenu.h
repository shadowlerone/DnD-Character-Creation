#pragma once
#include "Builder/MapBuilder.h"
#include "CampaignEditor.h"
#include "CharacterEditor.h"
#include "Globals.h"
#include "ItemContainerEditor.h"
#include "ItemEditor.h"
#include "Map/Map.h"
#include "MapEditor.h"
#include <filesystem>
#include <FL/Fl_Group.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Window.H>
#include <fstream>
#include <iostream>
#include <vector>

namespace fs = std::filesystem;

namespace CampaignEditor
{
	bool hasEnding(std::string const& fullString, std::string const& ending);
	class MainMenu : public Fl_Window
	{
		friend class MainMenu;
	public:
		MainMenu();
		void start();
		static void static_save(Fl_Widget* w, void* f)
		{
			((MainMenu*)f)->save();
		};
		static void static_save_as(Fl_Widget* w, void* f)
		{
			((MainMenu*)f)->save_as();
		};
		static void static_open(Fl_Widget* w, void* f)
		{
			((MainMenu*)f)->open();
		};
		static void static_reload(Fl_Widget* w, void* f)
		{
			((MainMenu*)f)->reload();
		};
		// static void static_save_as(Fl_Widget *w, void * f) {
		// 	((MainMenu*)f)->save_as();
		// };
		void reload() {
			open(campaign_dir.string());
		}
		void save()
		{
			std::cout << "Saving in Campaign Editor" << std::endl;
			// ie->save_as();

			if (!ce->save()) {
				return;
			}

			// for (Map::Map *_m: *me->maps)
			fs::create_directories(map_directory);
			for (int index = 0; index < maps->size(); index++)
			{
				Map::Map* _m = (*maps)[index];
				fs::path fp = map_directory / ("Map" + std::to_string(_m->getID()) + ".csv");
				std::string s = fp.string();
				MapBuilder::MapBuilder::SaveMap(_m, s);
				// MapSerializer::save_map(fp, _m);
			}
			fs::create_directories(item_directory.parent_path());
			ie->save();
			std::cout << "Updating containers" << std::endl;
			ice->save();
			return;
		};
		void open()
		{
			// tabs->value()->save();
			std::cout << "Opening in Campaign Editor" << std::endl;
			maps->clear();

			// ie->save_as();
			if (ce->open())
			{
				campaign_dir = fs::path(ce->filepath);
				std::cout << "Updating directories" << std::endl;

				update_directories();
				std::cout << "Updating Items" << std::endl;
				if (fs::exists(item_directory))
				{
					std::cout << "items exist, loading items" << std::endl;
					ie->open(item_directory.string());
				}
				else
				{
					std::cout << "items don't exist, creating directory" << std::endl;

					fs::create_directories(item_directory.parent_path());
				}

				if (fs::exists(map_directory))
				{
					std::cout << "maps exist, loading maps" << std::endl;

					std::string ext(".csv");
					std::string path(map_directory.string());
					for (auto& p : fs::directory_iterator(path))
					{
						if (p.path().extension() == ext)
						{
							std::cout << "Loading map: " << p.path() << std::endl;
							std::string s = p.path().string();
							Map::Map* m = new Map::Map(MapBuilder::MapBuilder::LoadMap(s));
							maps->push_back(m);
						}
					}
					me->populate_browser();
				}
				else
				{
					std::cout << "maps don't exist, creating directory" << std::endl;

					fs::create_directory(map_directory);
				}
				if (fs::exists(item_container_directory))
				{
					std::cout << "item containers exist, loading item containers" << std::endl;

					std::string ext(".csv");
					std::string path(item_container_directory.string());
					ice->open(path);
				}
				else
				{
					std::cout << "item_containers don't exist, creating directory" << std::endl;

					fs::create_directory(item_container_directory);
				}

				//ce->maps = maps;
				//me->set_maps(ce->maps);
				//items = &ie->items;
				//ice->set_items(items);
				ice->update_dropdown();
			}


			return;
		};
		void open(std::string s) {
			maps->clear();
			if (ce->open(s))
			{
				campaign_dir = fs::path(ce->filepath);
				std::cout << "Updating directories" << std::endl;

				update_directories();
				std::cout << "Updating Items" << std::endl;
				if (fs::exists(item_directory))
				{
					std::cout << "items exist, loading items" << std::endl;
					ie->open(item_directory.string());
				}
				else
				{
					std::cout << "items don't exist, creating directory" << std::endl;

					fs::create_directories(item_directory.parent_path());
				}

				if (fs::exists(map_directory))
				{
					std::cout << "maps exist, loading maps" << std::endl;

					std::string ext(".csv");
					std::string path(map_directory.string());
					for (auto& p : fs::directory_iterator(path))
					{
						if (p.path().extension() == ext)
						{
							std::cout << "Loading map: " << p.path() << std::endl;
							std::string s = p.path().string();
							Map::Map* m = new Map::Map(MapBuilder::MapBuilder::LoadMap(s));
							maps->push_back(m);
						}
					}
				}
				else
				{
					std::cout << "maps don't exist, creating directory" << std::endl;

					fs::create_directory(map_directory);
				}
				ice->update_dropdown();
				me->populate_browser();
			}
		}
		void save_as()
		{
			// tabs->value()->save();
			// Fl_Native_File_Chooser::Type t;
			int o;
			Fl_Native_File_Chooser fnfc;
			fnfc.title("");
			// fnfc.filter("*.csv");
			fnfc.type(Fl_Native_File_Chooser::BROWSE_SAVE_DIRECTORY);
			fnfc.options(0);
			fnfc.directory("./");
			switch (fnfc.show())
			{
			case -1:
				printf("ERROR: %s\n", fnfc.errmsg());
				// throw std::invalid_argument("");
				break; // ERROR
			case 1:
				printf("CANCEL\n");
				break; // CANCEL
			default:
				// printf("PICKED: %s\n", fnfc.filename());
				campaign_dir = fs::path(fnfc.filename());
				update_directories();
				save();
				break; // FILE CHOSEN
			}
		};

		void update_directories()
		{
			// campaign_dir = fs::path(ce->filepath);
			ce->filepath = campaign_dir.string();
			item_directory = campaign_dir / "Items" / "items.csv";
			map_directory = campaign_dir / "Maps";

			item_container_directory = campaign_dir / "ItemContainers" / "containers.csv";
			fs::create_directories(item_directory.parent_path());
			fs::create_directories(map_directory);

			fs::create_directories(item_container_directory.parent_path());

			ie->filepath = item_directory.string();
			me->filepath = map_directory.string();
			ice->filepath = item_container_directory.string();
		}

	private:
		Fl_Tabs* tabs;
		Fl_Menu_Bar* menu;
		ItemEditor* ie;
		MapEditor* me;
		CharacterEditor* chare;
		CampaignEditor* ce;
		ItemContainerEditor* ice;

		Fl_Group* ig;
		Fl_Group* mg;
		Fl_Group* cg;
		Fl_Group* icg;


		fs::path map_directory;
		fs::path item_directory;
		fs::path item_container_directory;
		fs::path character_directory;
		fs::path campaign_dir;
		// std::vector<Map::Map *> maps;
		// std::vector<Character::Character *> *characters;
	};

}
