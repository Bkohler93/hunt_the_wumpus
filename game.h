#include "cave.h"
#include "error_check.h"
#include <string>
#include <iostream>
#include <cstring>
#include <stdexcept>

class Game 
{
private:
	Cave cave;

public:
	Game(int cave_size, bool debug_on);

	
	//reset
	void reset_cave();

	//game funcs
	void play_game();
	bool continue_playing();
	bool new_cave();
	void print_endgame();


	//check game parameters
	static void check_valid_parameters(int argc, char* cave_size, char* bool_value);
	static bool set_debug_mode(char* bool_arg);
};