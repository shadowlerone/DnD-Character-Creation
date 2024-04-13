#include "ItemContainerEditor.h"
#include "Serialize/serializeItem.h"

#include "FL/Fl_Pack.H"

using namespace serializeItem;
namespace CampaignEditor
{
	void ItemContainerEditor::populate_browser()
	{
		browser->clear();
		std::string label;
		for (ItemContainerRecord *i : *itemcontainers)
		{
			i->containerId = browser->size();
;			label = std::to_string(i->containerId);
			browser->add(label.c_str(), i);
		}
	}

	void ItemContainerEditor::load_data(){
		std::cout << "updating items" << std::endl;
		int i = browser->value();
		if (i <= itemcontainers->size() && i > 0)
		{
			std::cout << "selected: " << i << std::endl;
			currentItemContainer = (ItemContainerRecord*)browser->data(i);
			update_data();
		}
	}

	void ItemContainerEditor::update_data() {
		contents->clear();
		for (int i : currentItemContainer->itemIDs) {
			//std::string name = *items[i]);
			std::string label = std::to_string(i);// +": " + (*items)[i]->GetItemName();
			contents->add(label.c_str());
		}
	}
	ItemContainerEditor::ItemContainerEditor(int x, int y, int w, int h) : BaseEditor(x, y, w, h)
	{
		g->begin();
		item_list = new Fl_Input_Choice(0, 20, w / 2, 50);
		contents = new Fl_Hold_Browser(0, 20, w / 2, (h) * .5);

		Fl_Pack* _c = new Fl_Pack(0, 0, w * .2, 30);
		_c->type(Fl_Pack::HORIZONTAL);
		Fl_Button * remove_button = new Fl_Button(0, 0, w * .1, 30, "Remove");
		remove_button->callback(static_remove, (void*)this);
		Fl_Button *add_button = new Fl_Button(0, 0, w * .1, 30, "Add");
		add_button->callback(static_add, (void*)this);
		_c->end();
		g->end();
		itemcontainers = new std::vector<serializeItem::ItemContainerRecord*>();
		items = new std::vector<item::Item*>();
	}
	void ItemContainerEditor::create()
	{
		ItemContainerRecord *e = new ItemContainerRecord();
		e->containerId = browser->size();
		itemcontainers->push_back(e);
		//itemcontainers->back()->containerId =;
		populate_browser();
		//currentItemContainer = browser->
		browser->bottomline(browser->size());
		browser->select(browser->size());
		load_data();
	}
	std::vector<itemcontainer::ItemContainer*>* rtoc(std::vector<serializeItem::ItemContainerRecord*>& v)
	{
		std::vector<itemcontainer::ItemContainer*>* out = new std::vector<itemcontainer::ItemContainer*>();
		for (serializeItem::ItemContainerRecord* i : v) {
			ItemContainer* ic = new ItemContainer(0);
			ic->setID(i->containerId);
			ic->SetItemName(i->itemName);
			ic->SetItemType(i->itemtype);
			ic->SetItemWeight(i->weight);
			ic->SetWeightLimit(i->capacity);
			ic->itemIds = i->itemIDs;
			out->push_back(ic);
		}
		return out;
	}
}
