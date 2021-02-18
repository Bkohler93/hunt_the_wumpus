#include "cave.h"

Cave::Cave(int cave_size) : adventurer(cave_size, 0, 0)
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
	this->run_debug = true;
	this->game_over = false;
}

/* getters */
bool Cave::get_game_over() const
{
	if (wumpus_dead) 
		std::cout << "You hit the wumpus!" << std::endl;
	return game_over;
}

bool Cave::get_missed_shot() const
{
	return missed_shot;
}

/* setters */
void Cave::set_missed_shot(bool missed_shot)
{
	this->missed_shot = missed_shot;
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
	
	//get user choice of what direction to fire arrow
	do
	{
		choice = get_player_choice();
	} while (choice == 32);
	//fire arrow in direction, check if wumpus is hit
	switch(choice)
	{
		case 87: projectile_arrow_north();break;
		case 65: projectile_arrow_west();break;
		case 83: projectile_arrow_south();break;
		case 68: projectile_arrow_east();break;
	}

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
			wumpus_dead = true;
			game_over = true;
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
			wumpus_dead = true;
			game_over = true;
			return;
		}
	
	missed_shot = true;
	}
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
			wumpus_dead = true;
			game_over = true;
			return;
		}
	
	missed_shot = true;
	}
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
			wumpus_dead = true;
			game_over = true;
			return;
		}
	
	missed_shot = true;
	}
}


//fills cave with events
void Cave::fill_cave()
{
	srand(time(NULL)); //ensure random rand() seed
	int x = -1;
	int y = -1;
	Event* event = nullptr; 	//used to point to new events being added

	//place adventurer
	adventurer.set_x(rand() % cave_size); 
	adventurer.set_y(rand() % cave_size);

	//place wumpus
	event = new Wumpus;
	
	do
	{
		x = rand() % cave_size; y = rand() % cave_size;
	} while (y == adventurer.get_x() && x == adventurer.get_y());

	if (rooms[y][x].check_unplaced()) 
	{
		rooms[y][x].set_event(event, y, x);
	}

	//place bats
}

//checks around adventurer for events, uses correct percept if there is an event
bool Cave::check_for_events()
{
	//get coordinates of adventurer
	int x = adventurer.get_x();
	int y = adventurer.get_y();
	//check north of adventurer, make sure adventurer not on top row (y = 0)
	if ( !(y == 0) && (rooms[x][y - 1].get_event() != nullptr) ) 
	{
		(rooms[x][y - 1].get_event()->percept()); return true;
	}
	
	//check south of adventurer
	if ( !(y == (cave_size - 1)) && (rooms[x][y + 1].get_event() != nullptr) )
	{
		(rooms[x][y + 1].get_event()->percept()); return true;
	}

	//check east of adventurer
	if ( !(x == (cave_size - 1)) && (rooms[x + 1][y].get_event() != nullptr) )
	{
		(rooms[x + 1][y].get_event()->percept()); return true;
	}

	//check west of adventurer
	if ( !(x == (0)) && (rooms[x - 1][y].get_event() != nullptr) )
	{
		(rooms[x - 1][y].get_event()->percept()); return true;
	}

	return false;
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
	//perform results of Wumpus
	if (event_name == "wumpus")
	{
		game_over = true; return;
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
				std::cout << 'O' << ' '; col_it++;
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