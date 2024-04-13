// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "Dice/Dice.h"
#include "gui.h"
#include <chrono>
#include <thread>
#include <time.h>

extern Dice* dice;

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono;	  // nanoseconds, system_clock, seconds
using namespace std::chrono_literals;

namespace GameView
{
	int updates;
	int cu;
	int* current_update;
	void update_dice_roll_value(void* data)
	{
		update_dice_roll_value();
	}
	void update_dice_roll_value()
	{
		// int count = *((int *)data);
		(*current_update)--;
		int roll = dice->roll();
		std::string v = std::to_string(roll);
		// std::cout << v << std::endl;
		// dice_value_output->label(v.c_str());
		dice_value_output->copy_label(v.c_str());

		std::cout << *current_update << std::endl;
		if (*current_update > 0)
		{
			// count--;
			// *(int *)data = count;
			Fl::add_timeout(0.05, update_dice_roll_value);
		}
		else
		{
			// Fl::remove_timeout(update_dice_roll_value, data);
		}
	}
	void hide_roll(void* d) {

	}
	void animate_dice_roll()
	{
		updates = (rand() % 5) + 5;
		// updates = 10;
		// std::cout << updates << std::endl;
		cu = 0;
		current_update = &updates;
		/* for (int i = 0; i < updates; i++)
		{
			int roll = dice->roll();
			std::string v = std::to_string(roll);
			// std::cout << v << std::endl;
			dice_value_output->copy_label(v.c_str());
			dice_value_output->redraw_label();
			std::cout << i << std::endl;
			sleep_for(100ms);
		} */
		update_dice_roll_value();
	}
}
