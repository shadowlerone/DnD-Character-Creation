#include "Utils.h"

Identifiable* find(int id, std::vector<Identifiable*>& v) {

	for (int i = 0; i < v.size(); i++) {
		if (v[i]->getID() == id) {
			return v[i];
		}
	}
	return nullptr;
}