#include "MapEditor.h"
using namespace CampaignEditor;

MapCellButton::MapCellButton(int x, int y, int w, int h, int _x, int _y, Interactable::Interactable* c) : Fl_Button(x, y, w, h)
{
	this->x = _x;
	this->y = _y;
	if (c == nullptr) {
		ct = new EmptyCell();
	}
	else {
		ct = c;
		copy_label(ct->serialize().c_str());
	}
	// std::cout << _x << "," << _y << std::endl;
}