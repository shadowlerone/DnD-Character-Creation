#include "../ProjectSourceCode/Character/Character.h"
#include "../ProjectSourceCode/Interactable/EmptyCell.h"
#include "../ProjectSourceCode/Interactable/Wall.h"
#include "../ProjectSourceCode/Item/Item.h"
#include "MapBuilder.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

bool MapBuilder::MapBuilder::SaveMap(Map::Map* map, std::string& filename) {
	//create file
	std::ofstream file(filename);
	try {
		//open file
		if (!file.is_open()) {
			std::cout << "Could not open file: " << filename << std::endl;
			return false;
		}
		else {
			file << map->getRows() << "," << map->getCols() << "," << map->getStartCell()[0] << "," << map->getStartCell()[1] << "," << map->getEndCell()[0] << "," << map->getEndCell()[1] << std::endl;

			//loop throug the map and save each non-empty cell

			for (int i = 0; i < map->getGrid().size(); i++) {
				for (int j = 0; j < map->getGrid()[i].size(); j++) {
					file << i << "," << j << "," << (map->getGrid()[i][j])->serialize() << std::endl;
				}
			}//end loop
		}//end file writing
	}
	catch (const std::ofstream::failure& e) {
		std::cout << "Exception caught while opening file: " << filename << std::endl;
	}

	file.close();
	return true;
}

Map::Map MapBuilder::MapBuilder::LoadMap(std::string& filename) {

	Map::Map mapload = Map::Map();

	std::ifstream file(filename);

	int lines = 0; //number of lines read
	int row = 0;
	int col = 0;
	std::string type;

	try {
		//open file
		if (!file.is_open()) {
			std::cout << "Could not open file: " << filename << std::endl;
		}
		else {
			std::string line;
			//while there is content in the file
			while (getline(file, line)) {
				lines++;

				//first line create the num of rows and cols
				if (lines == 1) {
					std::vector<std::string> split;
					std::stringstream ss(line);

					while (ss.good()) {
						std::string sub;
						getline(ss, sub, ',');
						split.push_back(sub);
					}
					//row,col,SCrow,SCcol,ECrow,ECcol
					// 0 , 1 ,  2  ,  3  ,  4  , 5
					row = std::stoi(split[0]);
					col = std::stoi(split[1]);

					mapload.setCols(col);
					mapload.setRows(row);
					mapload.setGrid();
					//mapload.setStartCell(std::stoi(split[2]), std::stoi(split[3]));
					//mapload.setEndCell(std::stoi(split[4]), std::stoi(split[5]));
				}

				else {
					std::vector<std::string> split;
					std::stringstream ss(line);

					while (ss.good()) {
						std::string sub;
						getline(ss, sub, ',');
						split.push_back(sub);
					}

					row = std::stoi(split[0]);
					col = std::stoi(split[1]);
					type = split[2];

					if (type == "w") {
						mapload.setWall(row, col);
					}
					else if (type == "i") {
						item::Item* i = new item::Item();
						i->setID(std::stoi(split[3]));
						mapload.setItem(row, col, i);
					}
					else if (type == "c") {
						Character::Character* c = new Character::Character(std::stoi(split[3]));
						mapload.setCharacter(row, col, c);
					}
					else {
						mapload.setEmpty(row, col);
					}

				}

			}
		}

	}
	catch (const std::ifstream::failure& e) {
		std::cout << "Exception caught while opening file: " << filename << std::endl;
	}

	return mapload;
}