#include "Game/game.h"
#include "gui.h"
using namespace abstractcomponent;
using namespace characteractionstrategy;
using namespace humanplayerstrategy;
using namespace aggressorstrategy;
using namespace friendlystrategy;
using namespace observable;

extern Dice* dice;
extern Fl_Double_Window* DiceWindow;

namespace game
{
	void Game::Combat(Character::Character* c1, Character::Character* c2)
	{
		AbstractComponent* opponentWornItems = c2->GetWornItems();
		int opponentArmorClass = opponentWornItems->Ability_Score_Natural(6, 0);

		for (int i = 0; i <= c1->Attacks_Per_Turn(); i++)
		{
			delete dice;
			dice = new Dice("1d20");

			DiceWindow->show();
			while (DiceWindow->shown());
			int hit_roll = dice->get_last_roll() + c1->GetWornItems()->Ability_Score_Natural(0, 0) + c1->GetWornItems()->Ability_Score_Natural(8, 0);
			if (hit_roll <= opponentArmorClass)
			{
				int damageValue = c1->GetWornItems()->Ability_Score_Natural(7, i + 1);
				c2->Receive_Damage(damageValue);

				if (!c1->Is_Alive())
				{
					// targetDied = true;
					c2->Receive_Damage(damageValue);
					RemoveCharacterFromMap(c2);
					// charactersInMap.erase(std::remove(charact))
					break;
				}
			}
			else
			{
				// Missed
			}
		}
	}
}