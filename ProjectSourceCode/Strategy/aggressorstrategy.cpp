/*!
* \file aggressorstrategy.cpp
* \brief File that contains the implementations for the movement strategy pattern for hostile NPC characters
* \author Tristan Lafleur
*/

#include "..\Character\Character.h"
#include "..\Interactable\EmptyCell.h"
#include "..\Interactable\Wall.h"
#include "aggressorstrategy.h"

using namespace item;
using namespace itemcontainer;

namespace aggressorstrategy {
	std::vector<CellActionInfo> AggressorStrategy::UseMovementStrategy(std::vector<std::vector<Interactable::Interactable*>> _currentMap, const int& _row, const int& _col) const {
		std::vector<CellActionInfo> actions;

		for (int i = 0; i < 4; i++)
		{
			int rowToCheck = _row;
			int colToCheck = _col;

			if (i == 0) {
				rowToCheck -= 1;
			}
			else if (i == 1) {
				colToCheck += 1;
			}
			else if (i == 2) {
				rowToCheck += 1;
			}
			else {
				colToCheck -= 1;
			}

			if (rowToCheck < 1 || rowToCheck > _currentMap.size() || colToCheck < 1 || colToCheck > _currentMap[0].size()) {
				continue;
			}

			Interactable::Interactable* valueAtCell = _currentMap[rowToCheck - 1][colToCheck - 1];
			CellActionInfo actionInfo;

			//NPC enemy only needs to know if the cells around it are: wall (can't pass), a character (attack), empty (can move there)
			if (dynamic_cast<Wall*>(valueAtCell) || dynamic_cast<ItemContainer*>(valueAtCell)) {
				actionInfo.row = rowToCheck;
				actionInfo.col = colToCheck;
				actionInfo.cellColor = Character::WALL_CELL_COLOR;
				actionInfo.actionName = Character::WALL_CELL_ACTION;
			}
			else if (dynamic_cast<Character::Character*>(valueAtCell)) {
				actionInfo.row = rowToCheck;
				actionInfo.col = colToCheck;
				actionInfo.cellColor = Character::ATTACK_CELL_COLOR;
				actionInfo.actionName = Character::ATTACK_CELL_ACTION;
			}
			else {
				actionInfo.row = rowToCheck;
				actionInfo.col = colToCheck;
				actionInfo.cellColor = Character::EMPTY_CELL_COLOR;
				actionInfo.actionName = Character::EMPTY_CELL_ACTION;
			}

			actions.push_back(actionInfo);
		}

		return actions;
	}
}
