#include "rope.h"

/* constructor */
Rope::Rope()
{
	set_symbol('R');
}

/* mutators */
void Rope::percept()
{
}

/* performs Rope version of encounter function */
std::string Rope::encounter()
{
	return "rope";
}


/* does Rope version of wumpus_hit, will return false since arrow
* hit Rope instead of wumpus
*/
bool Rope::wumpus_hit()
{
	return false;
}