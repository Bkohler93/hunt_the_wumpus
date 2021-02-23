#include "cave.h"


//constructor
Cave::Cave(int cave_size, bool debug_on) : adventurer(cave_size, 0, 0)
{
	int room_count = 0;

	//fill in rooms
	for (int i = 0; i < cave_size; ++i)
	{
		std::vector<Room> row_of_rooms;	//create vector of rooms, one row of rooms

		rooms.push_back(row_of_rooms); //add row of rooms to cave system

		for (int j = 0; j < cave_size; ++j)
		{
			rooms[i].push_back(Room());
			room_count++;
		}
	}

	//take in cave size
	this->cave_size = cave_size;
	this->run_debug = debug_on;
	this->game_over = false;
	this->game_won = false;
	this->fell_to_death = false;
	this->eaten = false;
	this->missed_shot = false;
	this->wumpus_dead = false;
}

/* getters */
bool Cave::get_game_over() const
{
	
	return game_over;
}

bool Cave::get_missed_shot() const
{
	return missed_shot;
}

bool Cave::get_game_won() const
{
	return game_won;
}

bool Cave::get_fell_to_death() const
{
	return fell_to_death;
}

bool Cave::get_eaten() const
{
	return eaten;
}

/* setters */
void Cave::set_missed_shot(bool missed_shot)
{
	this->missed_shot = missed_shot;
}

void Cave::set_game_over(bool game_over)
{
	this->game_over = game_over;
}

//reset position of adventurer
void Cave::reset_adventurer()
{
	srand(time(NULL));
	do
	{
		adventurer.set_x(rand() % cave_size);
		adventurer.set_y(rand() % cave_size);
	} while (!rooms[adventurer.get_x()][adventurer.get_y()].check_if_room_empty());

	set_game_over(false);

	//print out new location of adventurer
	std::cout << *this << std::endl;
}

/* mutators */
int Cave::get_player_choice() 
{
	int choice = 0;

	//'W' = 87, 'A' = 65, 'S' = 83, 'D' = 68
	while ( choice != 87 && choice != 65 && choice != 83 && choice != 68 && choice != 32)
	{
		choice = getch();	//grab choice from user without pressing enter
		if (choice > 96) choice -= 32;
	}
	
	return choice;
}


/*
* move adventurer based on which key was pressed
* 87 = 'W' 65 = 'A' 83 = 'S' 68 = 'D'
*/
void Cave::move_adventurer(int ascii_char)
{
	switch(ascii_char)
	{
		case 87: adventurer.move_north();break;
		case 65: adventurer.move_west();break;
		case 83: adventurer.move_south();break;
		case 68: adventurer.move_east();break; 
	}
}

/*
* fire arrow a direction
* show arrow flying in direction for 3 spaces
* if arrow hits wumpus
* print out message and set wumpus dead to true, delete wumpus from heap
* and set event pointer to null
*/
void Cave::fire_arrow()
{
	int choice = 0; 	//variable to store direction for arrow
	if (adventurer.get_num_arrows() > 0){
	//get user choice of what direction to fire arrow
		do
		{
			choice = get_player_choice();
		} while (choice == 0 || choice == 32);
		//fire arrow in direction, check if wumpus is hit
		switch(choice)
		{
			case 87: projectile_arrow_north();break;
			case 65: projectile_arrow_west();break;
			case 83: projectile_arrow_south();break;
			case 68: projectile_arrow_east();break;
		}
	}

	else {std::cout << "Your quiver is empty.\n";}
	
	//decrease arrow amount in adventurer's quiver
	adventurer.adventurer_shoots();

	//chance to teleport wumpus if missed
	if (this->missed_shot)
		teleport_wumpus();

	this->missed_shot = false;
}


/*
* show arrow flying north, check if wumpus is hit
*/
void Cave::projectile_arrow_north()
{
	//set point arrow flies from where adventurer currently is
	int x = adventurer.get_x();
	int y = adventurer.get_y();
	std::cout << "firing arrow north" << std::endl;
	
	//arrow flies through 3 rooms
	for (int i = 1; i < 4; i++)
	{
		if ((y - i >= 0) && !rooms[x][y - i].check_if_room_empty() && rooms[x][y - i].arrow_hit_wumpus())
		{ 
			rooms[x][y-i].nullify_event();
			wumpus_dead = true;
			return;
		}
	}

	missed_shot = true;
}


/*
* show arrow flying north, check if wumpus is hit
*/
void Cave::projectile_arrow_west()
{
	//set point arrow flies from where adventurer currently is
	int x = adventurer.get_x();
	int y = adventurer.get_y();
	std::cout << "firing arrow west" << std::endl;
	
	//arrow flies through 3 rooms
	for (int i = 1; i < 4; i++)
	{
		if ((x - i >= 0) && !rooms[x - i][y].check_if_room_empty() && rooms[x - i][y].arrow_hit_wumpus())
		{
			std::cout << "Your pierced the Wumpus' heart! She's dead!" << std::endl;
			rooms[x - i][y].nullify_event();
			wumpus_dead = true;
			return;
		}	
	}
	missed_shot= true;
}


/*
* show arrow flying north, check if wumpus is hit
*/
void Cave::projectile_arrow_east()
{
	//set point arrow flies from where adventurer currently is
	int x = adventurer.get_x();
	int y = adventurer.get_y();
	std::cout << "firing east" << std::endl;
	
	//arrow flies through 3 rooms
	for (int i = 1; i < 4; i++)
	{
		if ((x + i < cave_size) && !rooms[x + i][y].check_if_room_empty() && rooms[x + i][y].arrow_hit_wumpus())
		{
			std::cout << "Your pierced the Wumpus' heart! She's dead!" << std::endl;
			rooms[x + i][y].nullify_event();
			wumpus_dead = true;
			return;
		}
	}
	missed_shot = true;
}

/*
* show arrow flying north, check if wumpus is hit
*/
void Cave::projectile_arrow_south()
{

	std::cout << "firing arrow south" << std::endl;
	//set point arrow flies from where adventurer currently is
	int x = adventurer.get_x();
	int y = adventurer.get_y();
	
	//arrow flies through 3 rooms
	for (int i = 1; i < 4; i++)
	{
		if ((y + i >= 0) && !rooms[x][y + i].check_if_room_empty() && rooms[x][y + i].arrow_hit_wumpus())
		{
			std::cout << "Your pierced the Wumpus' heart! She's dead!" << std::endl;
			rooms[x][y+i].nullify_event();
			wumpus_dead = true;
			return;
		}
		//check if a different room was hit
		if ((y + i >= 0) && !rooms[x][y + i].check_if_room_empty()) break;
	}
	missed_shot = true;
}


//fills cave with events
void Cave::fill_cave()
{
	srand(time(NULL)); //ensure random rand() seed
	Event* event = nullptr; 	//used to point to new events being added

	//place adventurer
	adventurer.set_x(rand() % cave_size); 
	adventurer.set_y(rand() % cave_size);

	//place wumpu
	event = new Wumpus;
	
	fill_room_event(event);

	//place 2 bats
	for (int i = 0; i < 2; i++)
	{
		event = new Bats;

		//fill room with bat, requires different room each loop
		fill_room_event(event);
	}


	//place 2 pitfall
	for (int i = 0; i < 2; i++)
	{
		event = new Pitfall;

		//fill room with bat, requires different room each loop
		fill_room_event(event);
	}

	//place 1 gold
	event = new Gold;
	fill_room_event(event);

	//place 1 Rope
	event = new Rope;
	rooms[adventurer.get_x()][adventurer.get_y()].set_event(event, adventurer.get_x(), adventurer.get_y());

}

//fill room in cave with event pointer
void Cave::fill_room_event(Event* add_event)
{
	int x = -1;
	int y = -1;
	//ensure that new coordinate will not replace other events
	do
	{
		x = rand() % cave_size; y = rand() % cave_size;

	} while ( (x == adventurer.get_x() && y == adventurer.get_y()) || !rooms[x][y].check_if_room_empty());

	//fill room with event
	rooms[x][y].set_event(add_event, x, y);
}

//checks around adventurer for events, uses correct percept if there is an event
void Cave::check_for_events()
{
	//get coordinates of adventurer
	int x = adventurer.get_x();
	int y = adventurer.get_y();
	
	//print out cave before printing out a percept

	//check north of adventurer, make sure adventurer not on top row (y = 0)
	if ( !(y == 0) && (rooms[x][y - 1].get_event() != nullptr) ) 
	{
		(rooms[x][y - 1].get_event()->percept());
	}
	
	//check south of adventurer
	if ( !(y == (cave_size - 1)) && (rooms[x][y + 1].get_event() != nullptr) )
	{
		(rooms[x][y + 1].get_event()->percept());
	}

	//check east of adventurer
	if ( !(x == (cave_size - 1)) && (rooms[x + 1][y].get_event() != nullptr) )
	{
		(rooms[x + 1][y].get_event()->percept());
	}

	//check west of adventurer
	if ( !(x == (0)) && (rooms[x - 1][y].get_event() != nullptr) )
	{
		(rooms[x - 1][y].get_event()->percept());
	}
}

//checks if adventurer is on event
bool Cave::check_if_on_event()
{
	//get coordinates of adventurer
	int x = adventurer.get_x();
	int y = adventurer.get_y();
	
	//check if adventurer is on event
	if ( rooms[x][y].get_event() != nullptr){
		run_event(rooms[x][y].get_event()->encounter());
		return true;	//event found
	}

	return false;	//no event found
}

//does repurcussions from landing on event
void Cave::run_event(const std::string& event_name)
{
	//perform results of Wumpus ***MAYBE REPACKAGE?***
	if (event_name == "wumpus")
	{
		eaten = true;
		game_over = true; 
		return;
	}

	//perform results of Bats ***MAYBE REPACKAGE?***
	else if (event_name == "bats")
	{	
		std::cout << "A flock of Super Bats picked you up and dropped you in a new room.\n";
		displace_adventurer();
		return;
	}

	//perform results of Pitfall
	else if (event_name == "pitfall")
	{
		std::cout << "AHHHhhhh... you fell down a bottomless pit.\n";
		fell_to_death = true;
		game_over = true;
		return;	
	}

	//perform results of Gold
	else if (event_name == "gold")
	{	
		std::cout <<"You've found the gold! Now get out of there!\n";
		adventurer.set_has_gold(true);
		rooms[adventurer.get_x()][adventurer.get_y()].nullify_event();	
	}

	else if (event_name == "rope" && adventurer.get_has_gold())
	{
		this->game_won = true;
		game_over = true;
		return;
	}
}


//place adventurer in random spot
void Cave::displace_adventurer() 
{
	srand(time(NULL));
	//store adventurer's current location and create new location
	int x = adventurer.get_x(); int new_x;
	int y = adventurer.get_y(); int new_y;

	//continue to reassign adventurer coordinates if same coordinates are 
	//populated
	do
	{
		new_x = rand() % cave_size; new_y = rand() % cave_size;
	}	
	while ( (new_x == x && new_y == y) || !rooms[new_x][new_y].check_if_room_empty());
	
	//set new adventurer position from bats teleporting character
	adventurer.set_x(new_x); adventurer.set_y(new_y);

	//pause for user to press enter before continue
	user_pause();
	std::cout << *this << std::endl;	//print cave with new location
}

//clear and fill cave for if user wants to play again but with different layout
void Cave::clear_and_fill_cave()
{
	for (int i = 0; i < cave_size; i++)
	{
		for (int j = 0; j < cave_size; j++)
			rooms[i][j].nullify_event();	
	}

	//set up cave system, because new layout, reset all game tracking variables
	this->fill_cave();
	this->eaten = false;
	this->fell_to_death = false;
	this->missed_shot = false;
	this->game_over = false;
	this->wumpus_dead = false;
	this->adventurer.set_num_arrows(3);	
	this->adventurer.set_has_gold(false);

	//print out new cave
	std::cout << *this << std::endl;
}


//chance to teleport wumpus
void Cave::teleport_wumpus()
{
	int choice = 0;
	int new_x;
	int new_y;

	srand(time(NULL));
	choice = rand() % 4;

	//75% chance to teleport, choice can be int 0-3, meaning 0,1, or 2 causes wumpus to teleport
	if (choice < 3) {

		std::cout << "The Wumpus heard your shot miss, and has ran into a new room.\n";

		do
		{
			new_x = rand() % cave_size;
			new_y = rand() % cave_size;
		} while ( (new_x == adventurer.get_x() && new_y == adventurer.get_y()) || !rooms[new_x][new_y].check_if_room_empty());
	
		//move wumpus to new coordinates
		std::vector<int> wump_coords;
		find_wump_coords(wump_coords);
		rooms[wump_coords[0]][wump_coords[1]].nullify_event();
		Event* new_wump = new Wumpus;

		rooms[new_x][new_y].set_event(new_wump, new_x, new_y);
	}
}


//find wumpus coordinates
void Cave::find_wump_coords(std::vector<int> &wump_coords)
{
	//loop through each row
	for (int i = 0; i < cave_size; i++)
	{
		//loop through columns
		for (int j = 0; j < cave_size; j++)
		{
			if (!rooms[i][j].check_if_room_empty() && rooms[i][j].get_event()->encounter() == "wumpus")
			{
				wump_coords.push_back(i);
				wump_coords.push_back(j);
			}
		}
	}
}

/* operator overloads */

/*
used to print out the cave system
 */
std::ostream& operator<<(std::ostream& out, const Cave& cave)
{
	// cave.print_
	int row_it = 0; //iterate through rows of rooms
	int col_it = 0; //iterate through columns of rooms

	for (int j = 0; j < cave.cave_size; j++) {	//loop through rows of cave
		//print out top line of each room
		for (int i = 0; i < cave.cave_size; i++) std::cout << "+---";
			std::cout << "+\n";
		//print out second line of each room
		for (int i = 0; i < cave.cave_size; i++) std::cout << "|   ";
			std::cout << "|\n";
		//print out third line, containing event value
		for (int i = 0; i < cave.cave_size; i++) 
		{
			std::cout << "| ";

			//check if current space is same coordinates as adventurer
			if (row_it == cave.adventurer.get_y() && col_it == cave.adventurer.get_x())
			{
				std::cout << 'A' << ' '; col_it++;
			}
			else if (row_it == cave.adventurer.get_y() && col_it == cave.adventurer.get_x() && cave.get_game_over())
			{
				std::cout << '!' << ' '; col_it++;
			}
				
			else if (!cave.run_debug) { std::cout <<  "  "; col_it++;}
			else { std::cout << cave.rooms[col_it][row_it] << ' '; col_it++;}
	
		}
			std::cout << "|\n";
			col_it = 0; row_it++;
		
		//print out 4th line
	 	for (int i = 0; i < cave.cave_size; i++) std::cout << "|   ";
			std::cout << "|\n";
	}
	
	//print out final last line
	for (int i = 0; i < cave.cave_size; i++) std::cout << "+---";
		std::cout << "+\n";


	return out;	
}