#ifndef EVENT_H
#define EVENT_H

#include <iostream>

class Event 
{
private:
	int x = -1;	//horizontal coordinate
	int y = -1;	//vertical coordinate

	char symbol;
public:

	//virtual destructor
	virtual ~Event(){}

	/* getters */
	char get_symbol() const;
	int get_x() const;
	int get_y() const;
	

	/* setters */
	void set_x(int);
	void set_y(int);
	void set_symbol(char);

	/* mutators */
	virtual void percept() = 0;
	virtual std::string encounter() = 0;
	virtual bool wumpus_hit() = 0;
};

#endif