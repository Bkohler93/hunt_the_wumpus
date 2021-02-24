#ifndef CAVE_H
#define CAVE_H

#include <vector>
#include "room.h"
#include "adventurer.h"
#include "wumpus.h"
#include "bats.h"
#include "pitfall.h"
#include "gold.h"
#include "rope.h"
#include <iostream>
#include "error_check.h"

class Cave 
{
private:
	std::vector<std::vector<Room>> rooms;
	Adventurer adventurer;
	int cave_size;
	bool run_debug;
	bool game_over;
	bool game_won;
	bool fell_to_death;
	bool eaten;
	bool wumpus_dead;
	bool missed_shot;

public:
	/* constructor */
	Cave(int cave_size, bool debug_on);

	/* getters */
	bool get_game_over() const;
	bool get_missed_shot() const;
	bool get_game_won() const;
	bool get_fell_to_death() const;
	bool get_eaten() const;

	/* setters */
	void set_missed_shot(bool);
	void set_game_over(bool);
	void reset_adventurer(); 

	/* mutators */
	int get_player_choice();
	void move_adventurer(int ascii_char);
	void fire_arrow();
	void fill_cave();		//fills cave with all events and adventurer randomly
	void fill_room_event(Event*);
	void check_for_events();
	bool check_if_on_event();
	void run_event(const std::string&);
	void displace_adventurer();
	void find_wump_coords(std::vector<int> &);
	void projectile_arrow_north();
	void projectile_arrow_west();
	void projectile_arrow_east();
	void projectile_arrow_south();
	void clear_and_fill_cave();
	void teleport_wumpus();


	/* AI functions */
	void ai_random_move();
	bool ai_random_right_border();
	bool ai_random_left_border();
	bool ai_random_bot_border();
	bool ai_random_top_border();
	bool ai_check_gold();
	bool ai_check_rope();
	bool ai_check_wumpus();
	bool ai_check_pitfall();
	bool ai_check_bats();
	bool check_adventurer_gold();	
	/* operator overloads */
	friend std::ostream& operator<<(std::ostream& out, const Cave& cave);
	//friend bool operator==()
};



#endif