#ifndef WUMPUS_H
#define WUMPUS_H

#include "event.h"
#include <iostream>

class Wumpus : public Event 
{
private:

public:

	/* destrucotr */
	~Wumpus() {}

	/* constructors */
	Wumpus();


	/* mutators */
	void percept() override;
	std::string encounter() override;
	bool wumpus_hit() override;
};

#endif