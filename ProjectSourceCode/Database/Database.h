#pragma once
#include <vector>

template <typename T>
class Database :
    public std::vector<T>
{
    T getID(int id) {
        for (int i = 0; i < this->size(); i++) {
            if (this[i].ID()) return this[i];
        }
    }
};

