#include "bats.h"

/* constructor */
Bats::Bats()
{
	set_symbol('B');	
}


/* mutators */
void Bats::percept()
{
	std::cout << "You hear wings flapping.\n";
}

std::string Bats::encounter()
{
	std::cout << "A flock of Super Bats pick you and drop you in a new room.\n";

	return "bats"; 
}

bool Bats::wumpus_hit()
{
	return false;
}