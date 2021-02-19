#ifndef BATS_H
#define BATS_H

#include "event.h"
#include <iostream>

class Bats : public Event
{
private:

public:

	/* destrucotr */
	~Bats() {}

	/* constructors */
	Bats();


	/* mutators */
	void percept() override;
	std::string encounter() override;
	bool wumpus_hit() override;	
};

#endif