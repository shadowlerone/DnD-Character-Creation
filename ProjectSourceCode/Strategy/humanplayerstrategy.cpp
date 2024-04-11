/*!
* \file humanplayerstrategy.cpp
* \brief File that contains the implementations for the movement strategy pattern for player characters
* \author Tristan Lafleur
*/

#include "humanplayerstrategy.h"
#include "..\Character\Character.h"
#include "..\Interactable\Wall.h"
#include "..\Interactable\EmptyCell.h"
#include "..\Door\door.h"

using namespace item;
using namespace itemcontainer;
using namespace door;

namespace {

}

namespace humanplayerstrategy {
    std::vector<CellActionInfo> HumanPlayerStrategy::UseMovementStrategy(std::vector<std::vector<Interactable::Interactable*>> _currentMap, const int& _row, const int& _col) const {
        std::vector<CellActionInfo> actions;

        //check 4 directions to see where the Player can the player do
        for (int i = 0; i < 4; i++)
        {
            int rowToCheck = _row;
            int colToCheck = _col;
            
            if (i == 0) {
                rowToCheck -= 1; // up
            }
            else if (i == 1) {
                colToCheck += 1;// right
            }
            else if (i == 2) {
                rowToCheck += 1; // down
            }
            else {
                colToCheck -= 1; // left 
            }
            // cell out of bounds
            if (rowToCheck < 1 || rowToCheck > _currentMap.size() || colToCheck < 1 || colToCheck > _currentMap[0].size()) {
                continue;
            }

            Interactable::Interactable* valueAtCell = _currentMap[rowToCheck - 1][colToCheck - 1];
            CellActionInfo actionInfo;
            
            //if the cell being checked is: a wall
            if (dynamic_cast<Wall*>(valueAtCell)) {
                actionInfo.row = rowToCheck;
                actionInfo.col = colToCheck;
                actionInfo.cellColor = Character::WALL_CELL_COLOR; // = "none"
                actionInfo.actionName = Character::WALL_CELL_ACTION; // = "n/a"
            }//a character
            else if (dynamic_cast<Character::Character*>(valueAtCell)) {
                actionInfo.row = rowToCheck;
                actionInfo.col = colToCheck;
                actionInfo.cellColor = Character::ATTACK_CELL_COLOR; // = "red"
                actionInfo.actionName = Character::ATTACK_CELL_ACTION; // = "attack"
            }//an item
            else if (dynamic_cast<Item*>(valueAtCell)) {
                actionInfo.row = rowToCheck;
                actionInfo.col = colToCheck;
                actionInfo.cellColor = Character::PICKUP_CELL_COLOR; // ="green"
                actionInfo.actionName = Character::PICKUP_CELL_ACTION;// = "pickup"
            }//a door
            else if (dynamic_cast<Door*>(valueAtCell)) {
                actionInfo.row = rowToCheck;
                actionInfo.col = colToCheck;
                actionInfo.cellColor = Character::PICKUP_CELL_COLOR; // = "green"
                actionInfo.actionName = Character::DOOR_CELL_ACTION; // = "door"
            }//empty
            else {
                actionInfo.row = rowToCheck;
                actionInfo.col = colToCheck;
                actionInfo.cellColor = Character::EMPTY_CELL_COLOR; // = "blue"
                actionInfo.actionName = Character::EMPTY_CELL_ACTION; // = "move"
            }

            actions.push_back(actionInfo);
        }

        return actions;
    }
}
