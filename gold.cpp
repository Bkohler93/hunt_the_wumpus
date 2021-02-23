#include "gold.h"

/* constructor */
Gold::Gold()
{
	set_symbol('$');
}

/* mutators */
void Gold::percept()
{
	std::cout << "You see a glimmer nearby.\n";
}

/* performs Gold version of encounter function */
std::string Gold::encounter()
{

	return "gold";
}


/* does Gold version of wumpus_hit, will return false since arrow
* hit Gold instead of wumpus
*/
bool Gold::wumpus_hit()
{
	return false;
}