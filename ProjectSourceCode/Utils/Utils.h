#pragma once
#include "Identifiable/Identifiable.h"
#include <vector>
namespace Utils {

	Identifiable* find(int id, std::vector<Identifiable*>& v);

}