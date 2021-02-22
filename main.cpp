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

		Game game(cave_size, debug_on);

		game.play_game();
	}

	// Adventurer adventurer(4,0,0);

	// Cave cave(2);
	// cave.fill_cave();
	// std::cout << cave << std::endl;
	// for (int i = 0; i < 10; i++)
	// {
	// 	int player_choice = 0;
	// 	player_choice = cave.get_player_choice();
	// 	if (player_choice == 32) cave.fire_arrow();
	// 	else cave.move_adventurer(player_choice); 
	// 	//cave.move_adventurer(cave.get_player_choice());
	// 	std::cout << cave << std::endl;
	// 	if (cave.get_missed_shot()){
	// 		std::cout << "Your shot missed the wumpus.";
	// 		cave.set_missed_shot(false);	
	// 	}

	// 	//check if adventurer is on event
	// //	while (cave.check_if_on_event() && !(cave.get_game_over())) 
	// //	{
	// 		cave.check_if_on_event();
	// //	}

	// 	if (cave.get_game_over()) break;
	// 	else if (cave.check_for_events()) continue;
	// 	else std::cout << std::endl;
	// }

	catch(invalid_argument &arg)
	{
		std::cerr << "Error: " << arg.what() << std::endl; 
	}

	return 0;
}
