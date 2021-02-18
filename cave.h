#ifndef CAVE_H
#define CAVE_H

#include <vector>
#include "room.h"
#include "adventurer.h"
#include "wumpus.h"
#include <iostream>
#include "error_check.h"
#include <ctime>

class Cave 
{
private:
	std::vector<std::vector<Room>> rooms;
	Adventurer adventurer;
	int cave_size;
	bool run_debug;
	bool game_over;
	bool wumpus_dead;
	bool missed_shot;

public:
	/* constructor */
	Cave(int cave_size);

	/* getters */
	bool get_game_over() const;
	bool get_missed_shot() const;

	/* setters */
	void set_missed_shot(bool); 

	/* mutators */
	int get_player_choice();
	void move_adventurer(int ascii_char);
	void fire_arrow();
	void fill_cave();
	bool check_for_events();
	bool check_if_on_event();
	void run_event(const std::string&);
	void projectile_arrow_north();
	void projectile_arrow_west();
	void projectile_arrow_east();
	void projectile_arrow_south();

	/* operator overloads */
	friend std::ostream& operator<<(std::ostream& out, const Cave& cave);
	//friend bool operator==()
};
#endif