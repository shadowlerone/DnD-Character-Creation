#pragma once
#include "BaseEditor.h"
#include "Item/itemcontainer.h"
#include "Item/item.h"
#include "Serialize/serializeItem.h"

#include <FL/Fl_Input_Choice.H>

namespace CampaignEditor
{
	std::vector<itemcontainer::ItemContainer*>* rtoc(std::vector<serializeItem::ItemContainerRecord*>& v);
	class ItemContainerEditor : public BaseEditor
	{
		friend class MainMenu;
	public:
		ItemContainerEditor(int x, int y, int w, int h);
		void load_data();
		void create();
		void save() const { std::cout << "Saving Containers" << std::endl;  serializeItem::SaveItemContainersRecord(*itemcontainers, filepath); };
		void open(const std::string s) {
			filepath = s;
			*itemcontainers = serializeItem::LoadItemContainerRecords(s);
			//itemcontainers = rtoc(icr);
		}
		void open() { open(filepath.c_str()); }
		void save_as() {};
		void save_as(std::string s) { filepath = s; save(); };
		void save_data() {}
		void delete_entry() {}
		void update_data();
		void populate_browser();
		void set_items(std::vector<item::Item *> * i) {
			items = i;
		} 
		void add_item() {
			//if (contents->value() == 0) return;
			if (item_list->value() == "") return;
			currentItemContainer->itemIDs.push_back(std::stoi(item_list->value()));
			update_data();
		}
		void remove_item() {
			if (contents->value() == 0) return;
			currentItemContainer->itemIDs.erase(currentItemContainer->itemIDs.begin() + contents->value() - 1);
			update_data();
		}
		void update_dropdown()
		{
			item_list->clear();
			std::string label;
			item_list->add("");
			for (item::Item* i : *items)
			{
				label = std::to_string(i->getID());
				item_list->add(label.c_str());
			}
		}
	private:
		Fl_Hold_Browser* contents;
		Fl_Input_Choice* item_list;
		serializeItem::ItemContainerRecord* currentItemContainer;
		std::vector<serializeItem::ItemContainerRecord *> *itemcontainers;
		std::vector<item::Item *> *items;
	};
	static void static_add(Fl_Widget* w, void* f) {
		((ItemContainerEditor*)f)->add_item();
	}
	static void static_remove(Fl_Widget* w, void* f) {
		((ItemContainerEditor*)f)->remove_item();
	}
	
}