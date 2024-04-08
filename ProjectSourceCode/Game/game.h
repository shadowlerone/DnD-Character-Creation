/*!
 * \file game.h
 * \brief File that puts in the forward declarations for the game concept
 *
 * @author Tristan Lafleur (40245238)
 */

#pragma once

#include <vector>
#include <string>
#include <filesystem>
#include <Fl/Fl_Double_Window.H>

#include "..\Observer\Observable.h"
#include "..\Campaign\campaign.h"
#include "..\Item\item.h"
#include "..\Builder\MapBuilder.h"
#include "gui.h"

using namespace observable;
using namespace campaign;
using namespace item;
namespace fs = std::filesystem;
/*!
 * \namespace game
 * \brief Namespace to partition the Game functionality
 */
namespace game
{
	/*!
	 * \class Game
	 * \brief Class to abstract the game functionality, implements the Observable interface as a concrete obserable
	 */
	class Game : public Observable
	{
	public:
		/*!
		 * \fn Game
		 * \brief No args constructor for Game
		 */
		Game(){};
		Game(fs::path fp)
		{
			std::vector<Map::Map *> maps;
			fs::path item_directory = fp / "Items" / "items.csv";
			std::vector<Item *> items = serializeItem::LoadItems(item_directory.string());
			std::vector<serializeItem::ItemContainerRecord *> itemcontainers = serializeItem::LoadItemContainerRecords(item_directory.string());
			// TODO: Add this to a database
			fs::path map_directory = fp / "Maps";
			fs::path ext(".csv");
			for (auto &p : fs::directory_iterator(map_directory))
			{
				if (p.path().extension() == ext)
				{
					std::string s = p.path().string();
					Map::Map *m = new Map::Map(MapBuilder::MapBuilder::LoadMap(s));
					maps.push_back(m);
				}
			}
			for (Map::Map *_m : maps)
			{
				MapDatabase.insert(MapDatabase.begin() + _m->GetMapID(), _m);
			}
			for (Item *_i : items)
			{
				ItemDatabase.insert(ItemDatabase.begin() + _i->GetItemId(), _i);
			}
		};

		/*!
		 * \fn ~Game
		 * \brief Destructor for Game
		 */
		virtual ~Game(){};

		void Attach(Observer *_observer) override { observers.push_back(_observer); };

		void Detach(Observer *_observer) override { observers.erase(std::remove(observers.begin(), observers.end(), _observer), observers.end()); };

		/*!
		 * \fn Notify
		 * \brief Implemented function that will use the list of this observers and call their update functions using the instances observer message
		 */
		void Notify() override;

		/*!
		 * \fn CreateObserverMessage
		 * \brief Function that will take in a message from a calling object and use it to notify the observers with that message
		 *
		 * \param _message String representing the message to pass to the observers of this game instance. Default of "Empty"
		 */
		void CreateObserverMessage(std::string);

		void run()
		{
			while (true)
			{
			}
		};

		void Attach(Fl_Double_Window *window) { this->window = window; };

		std::vector<Observer *> GetObservers() { return observers; };

		void SetObservers(const std::vector<Observer *> &_observers) { observers = _observers; };

		std::string GetObserverMessage() { return observerMessage; };

		void SetObserverMessage(const std::string &_observerMessage) { observerMessage = _observerMessage; };

		Campaign *GetGameCampaign() { return gameCampaign; };

		void SetGameCampaign(Campaign *_gameCampaign) { gameCampaign = _gameCampaign; };

		Character::Character *GetActiveCharacter() { return activeCharacter; };

		void SetActiveCharacter(Character::Character *_activeCharacter) { activeCharacter = _activeCharacter; };

		std::vector<Character::Character *> GetCharactersInMap() { return charactersInMap; };

		void SetCharactersInMap(std::vector<Character::Character *> _charactersInMap) { charactersInMap = _charactersInMap; };

		// Load in a save file likely and update campaign member(?)
		void GameSetup(const std::string &);

		// Good candidate to incorporate doors (pass a reference to the object just an ID to know what map to load from campaign member)
		Map::Map *LoadMap(/* Door or ID */);

		// Essentially use this to update the game data based on an action taken by the player or an NPC
		void EndTurn(const std::string &, const int &, const int &);

		/*!
		 * \param attacking_character attacking character
		 * \param defending_character defending character
		 */
		void Combat(Character::Character *attacking_character, Character::Character *defending_character);

		void PrintActionMenu(Character::Character *);
		void GetUserSelection(char &t_selection);
		void ProcessUserAction(const char &t_selection, Character::Character *t_playerCharacter);

		void RemoveCharacterFromMap(Character::Character *c)
		{
			charactersInMap.erase(std::remove(charactersInMap.begin(), charactersInMap.end(), c), charactersInMap.end());
		}

	private:
		/*!
		 * \var observers
		 * \brief Vector of pointers to Observer instances representing the attached objects that are to be notified of state changes
		 */
		std::vector<Observer *> observers;

		/*!
		 * \var observerMessage
		 * \brief String representing the message to pass to the observers
		 */
		std::string observerMessage;

		Campaign *gameCampaign;

		Character::Character *activeCharacter;
		Character::Character *playerCharacter;
		Map::Map *currentMap;
		std::vector<Character::Character *> charactersInMap;

		std::vector<Item *> ItemDatabase;
		std::vector<ItemContainer *> ItemContainerDatabase;
		std::vector<Map::Map *> MapDatabase;
		std::vector<Character::Character *> characterDatabase;
		Fl_Double_Window *window;
	};
}