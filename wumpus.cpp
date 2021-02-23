#include "wumpus.h"

/* constructor */
Wumpus::Wumpus()
{
	set_symbol('W');
}

/* mutators */
void Wumpus::percept()
{
	std::cout << "You smell a terrible stench.\n";
}

std::string Wumpus::encounter()
{

	return "wumpus";
}

bool Wumpus::wumpus_hit()
{
	return true;
}