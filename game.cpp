#include "game.h"
#include "error_check.h"

//constructor
Game::Game(int cave_size, bool debug_on) : cave(cave_size, debug_on) 
{
	Cave cave(int cave_size, bool debug_on);
}


//game funcs
void Game::play_game()
{
	cave.fill_cave();

	int player_choice = 0;
	std::cout << cave << std::endl;

	while (true)
	{
		player_choice = cave.get_player_choice();

		if (player_choice != 32) cave.move_adventurer(player_choice);
		else {cave.fire_arrow();}

		//if not on event (runs events too), continue to next loop
		cave.check_if_on_event(); 
	
		//if adventurere dead
		if (cave.get_game_over())
		{
			print_endgame();

			if (!cave.get_game_won() && continue_playing())
			{
				if (new_cave())
					cave.clear_and_fill_cave();
				else (cave.reset_adventurer());	
			}
			else return;
		}	

		cave.check_for_events();
		std::cout << cave << std::endl;
	}
}

//ask if use wants to keep playing
bool Game::continue_playing()
{
	int player_choice = 0;
	std::string player_choice_str;


	while(player_choice == 0)
	{
		std::cout << "Do you want to keep playing? '1' for yes, '2' for no: ";
		getline(std::cin, player_choice_str);

		player_choice = check_choice_in_range(player_choice_str, 1, 2);	
	}

	if (player_choice == 1) return true;
	return false;
}

//ask if use wants to play with new cave
bool Game::new_cave()
{
	int player_choice = 0;
	std::string player_choice_str;

	while(player_choice ==0)
	{
		std::cout << "Do you want to play with a new cave setup? '1' for yes, '2' for no: ";
		getline(std::cin, player_choice_str);

		player_choice = check_choice_in_range(player_choice_str, 1, 2);
	}

	if (player_choice == 1) return true;
	return false;
}
//check game parameters
void Game::check_valid_parameters(int argc, char* cave_size,char* bool_value)
{

	if (argc != 3)
		throw invalid_argument("You must enter an integer for number of rooms in cave as first command line arg, and another arg as 'true' to run in debug mode, or 'false' to run in normal mode.");
	char* true_str = (char* )"true";
	char* false_str = (char* )"false";
	
	size_t i = 0;
	//set second argument to lower case
	for (i = 0; i < strlen(bool_value); i++)
	{
		if (bool_value[i] < 97) bool_value[i] -= 32;
	}

	//check cave_size
	if (! (atoi(cave_size) >= 4) )
		throw invalid_argument("Cave size must an integer greater than or equal to 4.");

	if ( (strlen(bool_value) != strlen("true")) && (strlen(bool_value) != strlen("false")))
		throw invalid_argument("Second command line argument should be 'true' to play game in debug mode, or 'false' to play in normal mode.");

	for (i = 0; i < strlen(bool_value); i++)
	{
		if ( (bool_value[i] != true_str[i]) && (bool_value[i] != false_str[i]) )
			throw invalid_argument("Second command line argument should be 'true' to play game in debug mode, or 'false' to play in normal mode.");
	}
}

//print out endgame message
void Game::print_endgame()
{
	std::cout << cave << std::endl;

	if (cave.get_game_won()) std::cout << "You've managed to evade the Wumpus and escape with the gold! You Win!\n";

	else if (cave.get_fell_to_death()) std::cout << "AHHHHhhhhh... you fell into a bottomless pit.\n";

	else if (cave.get_eaten()) std::cout << "You walked into the Wumpus' room... She woke up and ate you.\n";

}


//fill in if game is in debug mode or not
bool Game::set_debug_mode(char* bool_arg)
{

	char* true_str = (char*) "true";
	size_t i = 0;	//iterate through bool_arg

	//check if arg is "true"
	for (i = 0; i < strlen(true_str); i++)
	{
		if (bool_arg[i] != true_str[i])
			return false;
	}

	return true;
}