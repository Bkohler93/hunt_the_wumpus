#include "pitfall.h"

/* constructor */
Pitfall::Pitfall()
{
	set_symbol('P');	
}


/* mutators */
void Pitfall::percept()
{
	std::cout << "You feel a breeze.\n";
}

/* performs Pitfall version of encounter function */
std::string Pitfall::encounter()
{

	return "pitfall"; 
}

/* does Pitfall version of wumpus_hit, will return false since arrow
* hit Pitfall instead of wumpus
*/
bool Pitfall::wumpus_hit()
{
	return false;
}