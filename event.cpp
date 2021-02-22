#include "event.h"



/* getters */
int Event::get_x() const
{
	return this->x;
}

int Event::get_y() const
{
	return this->y;
}

char Event::get_symbol() const
{
	return this->symbol;
}

/* setters */
void Event::set_x(int x)
{
	this->x = x;
}



void Event::set_y(int y)
{
	this->y = y;
}

void Event::set_symbol(char symbol)
{
	this->symbol = symbol;
}