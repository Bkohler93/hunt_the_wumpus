#ifndef GOLD_H
#define GOLD_H

#include "event.h"
#include <iostream>

class Gold : public Event 
{
private:

public:

	/* destrucotr */
	~Gold() {}

	/* constructors */
	Gold();


	/* mutators */
	void percept() override;
	std::string encounter() override;
	bool wumpus_hit() override;
};

#endif