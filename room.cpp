#include "room.h"

Room::Room()
{
	event = nullptr;
}

/* destructor */
Room::~Room()
{
	if (event != nullptr) 
	{
		delete event;
	}
}

/* getters */
Event* Room::get_event() const 
{
	return event;
}

/* setters */
void Room::set_event(Event* event, int x, int y)
{
	std::cout << "inside function, printing out event symbol: " << event->get_symbol() << std::endl;
	this->event = event;
	this->event->set_x(x);
	this->event->set_y(y);
}

/* mutators */
bool Room::check_unplaced() const
{
	if (event == nullptr) {
		return true;
	}
	return false;
	//if coords are still initialized to -1 return true;
	//((event->get_x() == -1) && (event->get_y() == -1)) ? return true : return false;

}

/*
* check if arrow hits wumpus
*/
bool Room::arrow_hit_wumpus() const
{
	if (event->wumpus_hit()) return true;

	return false;
}


/*
* check if current room is empty
*/
bool Room::check_if_room_empty() const
{
	if (event == nullptr) return true;

	return false;
}

//print out room container symbol
std::ostream& operator<<(std::ostream& out, const Room& room)
{
	//check if nothing is in current event	
	if (room.event == nullptr) {
		std::cout << ' '; 
		return out;
	}
	//std::cout << 'W';
	std::cout << (room.get_event())->get_symbol();

	return out;
}