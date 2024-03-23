#pragma once 

namespace Interactable {

	class Interactable {

	public:

		//can the player pass through a cell of this type
		virtual bool passable();

		//the derived classes should be: empty, wall, item, character

	};
}