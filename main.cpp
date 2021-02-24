#include "adventurer.h"
#include "cave.h"
#include "room.h"
#include "event.h"
#include "wumpus.h"
#include "game.h"
#include <stdexcept>

int main(int argc, char* argv[])
{
	try 
	{
		//check if command line args are valid
		Game::check_valid_parameters(argc, argv[1], argv[2]);	
		
		int cave_size = atoi(argv[1]);
		bool debug_on = Game::set_debug_mode(argv[2]);
		bool auto_play = Game::get_auto_play();
		
		//start game with debug mode on/off
		Game game(cave_size, debug_on);

		auto_play ? game.play_ai_game() : game.play_game();
	}

	catch(invalid_argument &arg)
	{
		std::cerr << "Error: " << arg.what() << std::endl; 
	}

	return 0;
}
