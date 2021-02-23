#ifndef ROPE_H
#define ROPE_H

#include "event.h"
#include <iostream>

class Rope : public Event 
{
private:

public:

	/* destrucotr */
	~Rope() {}

	/* constructors */
	Rope();


	/* mutators */
	void percept() override;
	std::string encounter() override;
	bool wumpus_hit() override;
};

#endif