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

/* performs Bats version of encounter function */
std::string Bats::encounter()
{
	std::cout << "A flock of Super Bats pick you and drop you in a new room.\n";

	return "bats"; 
}

/* does Bats version of wumpus_hit, will return false since arrow
* hit bats instead of wumpus
*/
bool Bats::wumpus_hit()
{
	return false;
}