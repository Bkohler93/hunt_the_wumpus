#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include "event.h"

class Room 
{
private:
	Event* event; 

public:
	/* constructor */
	Room();

	/* destructor */
	~Room();

	/* getters */
	Event* get_event() const;

	/* setters */
	void set_event(Event*, int, int);

	/* mutators */
	bool check_unplaced() const;
	bool arrow_hit_wumpus() const;
	bool check_if_room_empty() const;

	friend std::ostream& operator<<(std::ostream& out,const Room& room);
};

#endif