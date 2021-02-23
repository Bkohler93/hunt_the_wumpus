#ifndef PITFALL_H
#define PITFALL_H

#include "event.h"
#include <iostream>

class Pitfall : public Event 
{
private:

public:

	/* destrucotr */
	~Pitfall() {}

	/* constructors */
	Pitfall();


	/* mutators */
	void percept() override;
	std::string encounter() override;
	bool wumpus_hit() override;
};

#endif